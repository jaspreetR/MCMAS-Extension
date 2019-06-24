#include "AbstractAgent.hpp"
#include <algorithm>
#include "utils/Misc.hpp"
#include "utils/Overload.hpp"
#include "visitors/OwnerActionVisitor.hpp"

namespace mcmas {

  AbstractAgent::AbstractAgent(const AgentState& state, const SwarmAgent& concrete_agent, 
                               std::map<int, Expression::Ptr>&& transition_set, int id) 
  : state(state)
  {
    bool with_metadata = true;
    name = generate_abstract_agent_name(concrete_agent.name, id);

    add_variable("is_active", BOOL());

    // set init_condition to set vars with state values
    for (const auto& [var_name, var_type] : concrete_agent.vars) {
      add_variable(var_name, var_type);
    }

    std::vector<Expression::Ptr> init_var_conditions;
    if (with_metadata) {
      for (const auto& [id, expr] : transition_set) {
        (void)expr;
        std::string var_name = "from_" + std::to_string(id);
        add_variable(var_name, BOOL());
        init_var_conditions.emplace_back(Expression::Eq(Expression::Id(var_name), Expression::Bool(false)));
      }
    }

    for (const auto& [var_name, value] : state.get()) {
      Expression::Ptr value_expr = std::visit(Overload{
        [](int x){ return Expression::Int(x); },
        [](bool b){ return Expression::Bool(b); }
      }, value);
      init_var_conditions.emplace_back(Expression::Eq(Expression::Id(var_name), std::move(value_expr)));
    }

    init_condition = Expression::And(std::move(init_var_conditions));

    auto concrete_agent_actions = concrete_agent.actions;
    std::sort(concrete_agent_actions.begin(), concrete_agent_actions.end());
    
    auto actions_power_set = power_set(concrete_agent_actions);

    std::vector<std::string> abstract_actions = {"null"};

    for (const auto& actions_subset : actions_power_set) {
      auto abstract_action = concat_strings(actions_subset);

      for (const auto& action : actions_subset) {
        action_register[action].push_back(abstract_action);
      }

      abstract_actions.emplace_back(std::move(abstract_action));
    }

    add_actions(abstract_actions);

    if (with_metadata) {
      add_transitions_power_set(transition_set);
    } else {
      add_single_transition(transition_set);
    }

    auto protocol_lines_power_set = power_set(concrete_agent.protocol.lines);
    for (const auto& line_set : protocol_lines_power_set) {
      std::vector<Expression::Ptr> conditions;
      conditions.reserve(line_set.size());
      std::set<std::string> actions;

      for (auto& line : line_set) {
        conditions.emplace_back(line.condition->clone());
        for (auto& action : line.enabled_actions) {
          actions.emplace(std::move(action));
        }
      }

      std::vector<std::string> action_vec;
      action_vec.reserve(actions.size());
      for (auto& action : actions) {
        action_vec.emplace_back(std::move(action));
      }
      auto action_power_set = power_set(action_vec);

      std::vector<std::string> new_enabled_actions;
      new_enabled_actions.reserve(actions_power_set.size());

      for (const auto& subset : action_power_set) {
        new_enabled_actions.emplace_back(concat_strings(subset));
      }

      auto new_condition = conditions.size() >= 2 ? Expression::And(std::move(conditions)) : std::move(conditions[0]);
      new_condition = Expression::And(
                        Expression::Eq(Expression::Id("is_active"), Expression::Bool(true)), 
                        std::move(new_condition)
                      );

      add_protocol_line(std::move(new_condition), std::move(new_enabled_actions));
    } 

    add_protocol_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(false)), std::vector<std::string>{"null"});
  }

  std::string AbstractAgent::generate_abstract_agent_name(const std::string& concrete_name, int i) {
    return "Abs__" + concrete_name + "__" + std::to_string(i);
  }

  void AbstractAgent::add_single_transition(std::map<int, Expression::Ptr>& transition_set) {
    if (transition_set.size() == 0) {
      auto transition = Expression::Not(Expression::Eq(Expression::Id("is_active"), Expression::Id("is_active")));
      add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(true)), transition->clone());
      add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(false)), Expression::Not(transition->clone()));
      return;
    } 

    std::vector<Expression::Ptr> conditions;
    for (auto& [id, condition] : transition_set) {
      (void)id;
      conditions.emplace_back(std::move(condition));
    }

    Expression::Ptr disjunct_condition = Expression::Or(std::move(conditions));
    add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(true)), disjunct_condition->clone());
    add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(false)), Expression::Not(disjunct_condition->clone()));

  }

  void AbstractAgent::add_transitions_power_set(std::map<int, Expression::Ptr>& transition_set) {
    if (transition_set.size() == 0) {
      auto transition = Expression::Not(Expression::Eq(Expression::Id("is_active"), Expression::Id("is_active")));
      add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(true)), transition->clone());
      add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(false)), Expression::Not(transition->clone()));
      return;
    } 

    std::vector<int> ids;
    std::vector<Expression::Ptr> transitions;
    for (auto& [id, transition] : transition_set) {
      ids.emplace_back(id);
      transitions.emplace_back(std::move(transition));
    }

    std::vector<std::vector<Expression::Ptr>> results;
    std::vector<std::vector<Expression::Ptr>> conditions;

    DynamicBitset bits(transition_set.size());
    do {
      std::vector<Expression::Ptr> result;
      std::vector<Expression::Ptr> condition;

      int i = 0;
      for (auto bit : bits) {
        if (bit) {
          result.emplace_back(Expression::Eq(Expression::Id("from_" + std::to_string(ids[i])), Expression::Bool(true)));
          condition.emplace_back(transitions[i]->clone());
        } else {
          result.emplace_back(Expression::Eq(Expression::Id("from_" + std::to_string(ids[i])), Expression::Bool(false)));
          condition.emplace_back(Expression::Not(transitions[i]->clone()));
        }
        ++i;
      }

      if (bits.some()) {
        result.emplace_back(Expression::Eq(Expression::Id("is_active"), Expression::Bool(true)));
      } else {
        result.emplace_back(Expression::Eq(Expression::Id("is_active"), Expression::Bool(false)));
      }

      results.emplace_back(std::move(result));
      conditions.emplace_back(std::move(condition));

      ++bits;
    } while (bits.some());

    std::vector<Expression::Ptr> conjunct_results;
    std::vector<Expression::Ptr> conjunct_conditions;

    for (auto& results_set : results) {
      conjunct_results.emplace_back(Expression::And(std::move(results_set)));
    }

    for (auto& conditions_set : conditions) {
      conjunct_conditions.emplace_back(Expression::And(std::move(conditions_set)));
    }

    for (size_t i = 0; i < conjunct_results.size(); ++i) {
      add_evolution_line(std::move(conjunct_results[i]), std::move(conjunct_conditions[i]));
    }
  }
}