#include "SwarmSystem.hpp"
#include "visitors/OwnerReplaceVisitor.hpp"
#include "visitors/GlobalActionVisitor.hpp"
#include <limits>
#include <algorithm>

namespace mcmas {

  // add new visitor for changing owner in ids - needed for init states
  // generate new concrete_agents and change ids - need to change name and init states
  // generate abstract agents
  // apply global action transform to all agents
  // generate init states condition - abstract agent: 1.false or (sub and 1.true) and ... (1.true or 2.true or 3.true)
  // generate new atoms for each concrete agent - maybe check if atom contains agent name
  // given formulae with given placeholders, substitute with agent1, agent2 etc
  SwarmSystem::SwarmSystem(const SwarmAgent& environment, 
                           const SwarmAgent& agent, 
                           int num_agents, 
                           const Evaluation& evaluation,
                           std::vector<IndexedFormula>&& formulas) {
    
    this->environment = environment.clone();

    // TODO: get rid of this hacky stuff by allowing mcmas to accept const expressions in its conditions
    this->environment.add_obs_variable("env_val_true", BOOL());
    this->environment.init_condition = Expression::And (
                                         Expression::Eq(Expression::Id("env_val_true"), Expression::Bool(true)),
                                         std::move(this->environment.init_condition)
                                       );
    this->environment.add_obs_variable("env_val_false", BOOL());
    this->environment.init_condition = Expression::And (
                                         Expression::Eq(Expression::Id("env_val_false"), Expression::Bool(false)),
                                         std::move(this->environment.init_condition)
                                       );

    int min_int_range = std::numeric_limits<int>::max();
    int max_int_range = std::numeric_limits<int>::min();
    for (const auto& var : agent.vars) {
      auto var_type = var.second;
      if (auto* int_type = std::get_if<RANGED_INT>(&var_type)) {
        min_int_range = std::min(int_type->min, min_int_range); 
        max_int_range = std::max(int_type->max, max_int_range); 
      }
    }

    for (int i = min_int_range; i <= max_int_range; ++i) {
      auto val_string = "env_val_" + std::to_string(i);
      this->environment.add_obs_variable(val_string, RANGED_INT(min_int_range, max_int_range));
      this->environment.init_condition = Expression::And (
                                           Expression::Eq(Expression::Id(val_string), Expression::Int(i)),
                                           std::move(this->environment.init_condition)
                                         );
    }

    GlobalActionVisitor ga_visitor;
    
    concrete_agents.reserve(num_agents);
    for (int i = 0; i < num_agents; ++i) {
      concrete_agents.emplace_back(agent.clone());
      auto& new_agent = concrete_agents[i];

      std::string new_name = agent.name + "__" + std::to_string(i);
      new_agent.name = new_name;

      // put new name into init_state
      OwnerReplaceVisitor or_visitor(new_name);
      new_agent.init_condition->accept(or_visitor);

      ga_visitor.add_actions_from_sa(new_agent);
    }

    abstract_agents = agent.generate_abstract_agents();
    for (const auto& abstract_agent : abstract_agents) {
      ga_visitor.add_actions_from_aa(abstract_agent);
    }

    for (auto& concrete_agent : concrete_agents) {
      concrete_agent.apply_global_action_transform(ga_visitor);
    }

    for (auto& abstract_agent : abstract_agents) {
      abstract_agent.apply_global_action_transform(ga_visitor);
    }

    std::vector<Expression::Ptr> init_conditions;
    init_conditions.reserve(concrete_agents.size() + abstract_agents.size() + 1);
    OwnerReplaceVisitor env_or_visitor(this->environment.name);
    this->environment.init_condition->accept(env_or_visitor);
    init_conditions.emplace_back(std::move(this->environment.init_condition));

    for (auto& concrete_agent : concrete_agents) {
      init_conditions.emplace_back(std::move(concrete_agent.init_condition));
    }

    std::vector<Expression::Ptr> abstract_active_exprs;
    abstract_active_exprs.reserve(abstract_agents.size());

    for (auto& abstract_agent : abstract_agents) {
      // eval init condition when given abstract agent state and simply allow those agents where it holds to be optionally active
      auto result = abstract_agent.state.evaluate(agent.init_condition.get());
      auto* bool_result = std::get_if<bool>(&result);

      if (bool_result == nullptr) {
        std::cout << "invalid agent init condition" << std::endl;
        throw new std::exception();
      }

      Expression::Ptr init_condition = std::move(abstract_agent.init_condition);
      OwnerReplaceVisitor abs_or_visitor(abstract_agent.name);
      init_condition->accept(abs_or_visitor);

      if (*bool_result) {
        init_condition = Expression::And(
                           std::move(init_condition),  
                           Expression::Or(
                             Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(false)),
                             Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(true))
                           )
                         );
      } else {
        init_condition = Expression::And(
                           std::move(init_condition),
                           Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(false))
                         );
      }

      /*
      auto init_condition = Expression::Or(
                              Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(false)),
                              Expression::And(
                                std::move(subbed_init_condition),
                                Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(true))
                              )
                            );
      */

      init_conditions.emplace_back(std::move(init_condition));

      abstract_active_exprs.emplace_back(Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(true)));
    }

    init_conditions.emplace_back(Expression::Or(std::move(abstract_active_exprs)));
    init_states = Expression::And(std::move(init_conditions));

    Evaluation new_evaluation;
    new_evaluation.lines.reserve(concrete_agents.size() * evaluation.lines.size());
    for (const auto& line : evaluation.lines) {
      for (const auto& concrete_agent : concrete_agents) {
        
        auto new_atom_name = line.name + "__" + concrete_agent.name;
        auto new_condition = line.condition->clone();
        OwnerReplaceVisitor visitor(concrete_agent.name, agent.name);
        new_condition->accept(visitor);

        new_evaluation.lines.emplace_back(EvaluationLine(std::move(new_atom_name), std::move(new_condition)));
      }
    }

    this->evaluation = new_evaluation;

    this->formulas = std::move(formulas);
    for (auto& formula : this->formulas) {
      formula.insert_agent_names(concrete_agents); 
    }
  }

  std::string SwarmSystem::to_string() const {
    std::string result = "Semantics=MultiAssignment;\n";

    result += environment.to_string() + "\n";

    for (const auto& concrete_agent : concrete_agents) {
      result += concrete_agent.to_string() + "\n";
    }
    
    for (const auto& abstract_agent : abstract_agents) {
      result += abstract_agent.to_string() + "\n";
    }

    result += evaluation.to_string() + "\n";

    result += "InitStates\n";
    result += init_states->to_string() + ";\n";
    result += "end InitStates\n\n";

    result += "Formulae\n";
    for (auto& formula : formulas) {
      result += formula.formula->to_string() + ";\n";
    }
    result += "end Formulae\n";

    return result;
  }

}