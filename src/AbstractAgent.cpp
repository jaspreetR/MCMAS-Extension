#include "AbstractAgent.hpp"
#include <algorithm>
#include "utils/Misc.hpp"

namespace mcmas {

  AbstractAgent::AbstractAgent(const AgentState& state, const SwarmAgent& concrete_agent, Expression::Ptr&& transition, int id) 
  : state(state)
  {
    name = concrete_agent.name + "__" + std::to_string(id);

    add_variable("is_active", BOOL());

    auto concrete_agent_actions = concrete_agent.actions;
    std::sort(concrete_agent_actions.begin(), concrete_agent_actions.end());
    
    auto actions_power_set = power_set(concrete_agent_actions);
    std::vector<std::string> abstract_actions;

    for (const auto& actions_subset : actions_power_set) {
      auto abstract_action = concat_strings(actions_subset);

      for (const auto& action : actions_subset) {
        action_register[action].push_back(abstract_action);
      }

      abstract_actions.emplace_back(std::move(abstract_action));
    }

    add_actions(abstract_actions);

    auto protocol_lines_power_set = power_set(concrete_agent.protocol.lines);
    for (const auto& line_set : protocol_lines_power_set) {
      std::vector<Expression::Ptr> conditions;
      conditions.reserve(line_set.size());
      std::set<std::string> actions;

      for (auto& line : line_set) {
        auto subst_condition = state.substitute(line.condition.get());
        conditions.emplace_back(std::move(subst_condition));
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
      add_protocol_line(std::move(new_condition), std::move(new_enabled_actions));
    } 

    add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(true)), transition->clone());
    add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(false)), Expression::Not(transition->clone()));
  }

}