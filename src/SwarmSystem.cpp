#include "SwarmSystem.hpp"
#include "visitors/OwnerReplaceVisitor.hpp"
#include "visitors/GlobalActionVisitor.hpp"

namespace mcmas {

  SwarmSystem::SwarmSystem(const SwarmAgent& environment, 
                           const SwarmAgent& agent, 
                           int num_agents, 
                           const Evaluation& evaluation) {
    
    this->environment = environment.clone();

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

    for (auto& concrete_agent : concrete_agents) {
      init_conditions.emplace_back(std::move(concrete_agent.init_condition));
    }

    std::vector<Expression::Ptr> abstract_active_exprs;
    abstract_active_exprs.reserve(abstract_agents.size());

    for (auto& abstract_agent : abstract_agents) {
      auto subbed_init_condition = abstract_agent.state.substitute(agent.init_condition.get());
      auto init_condition = Expression::Or(
                              Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(false)),
                              Expression::And(
                                std::move(subbed_init_condition),
                                Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(true))
                              )
                            );
      init_conditions.emplace_back(std::move(init_condition));

      abstract_active_exprs.emplace_back(Expression::Eq(Expression::Id(abstract_agent.name, "is_active"), Expression::Bool(true)));
    }

    std::cout << "hello" << agent.get_all_states().size() << std::endl;
    init_conditions.emplace_back(Expression::Or(std::move(abstract_active_exprs)));
    init_states = Expression::And(std::move(init_conditions));
    std::cout << "hello2" << std::endl;

    Evaluation new_evaluation;
    new_evaluation.lines.reserve(concrete_agents.size() * evaluation.lines.size());
    for (const auto& line : evaluation.lines) {
      for (size_t i = 0; i < concrete_agents.size(); ++i) {
        const auto& concrete_agent = concrete_agents[i];
        auto new_atom_name = line.name + "__" + std::to_string(i);
        auto new_condition = line.condition->clone();
        OwnerReplaceVisitor visitor(concrete_agent.name, agent.name);
        new_condition->accept(visitor);

        new_evaluation.lines.emplace_back(EvaluationLine(std::move(new_atom_name), std::move(new_condition)));
      }
    }

    this->evaluation = new_evaluation;

    // add new visitor for changing owner in ids - needed for init states
    // generate new concrete_agents and change ids - need to change name and init states
    // generate abstract agents
    // apply global action transform to all agents
    // generate init states condition - abstract agent: 1.false or (sub and 1.true) and ... (1.true or 2.true or 3.true)
    // generate new atoms for each concrete agent - maybe check if atom contains agent name
    // given formulae with given placeholders, substitute with agent1, agent2 etc
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

    return result;
  }

}