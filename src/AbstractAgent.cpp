#include "AbstractAgent.hpp"
#include "utils/Misc.hpp"

namespace mcmas {

  AbstractAgent::AbstractAgent(const AgentState& state, const SwarmAgent& concrete_agent, int id) 
  : SwarmAgent(concrete_agent.max_x, concrete_agent.max_y, concrete_agent.comm_distance),
    state(state),
    concrete_agent(concrete_agent) 
  {
    name = concrete_agent.name + "__" + std::to_string(id);
    
    auto actions_power_set = power_set(concrete_agent.actions);
    std::vector<std::string> abstract_actions;

    for (const auto& actions_subset : actions_power_set) {
      std::string abstract_action;

      for (const auto& action : actions_subset) {
        if (abstract_action.size() == 0) {
          abstract_action += action;
        } else {
          abstract_action += "__" + action;
        }
      }

      for (const auto& action : actions_subset) {
        action_register[action].push_back(abstract_action);
      }

      abstract_actions.emplace_back(std::move(abstract_action));
    }

    add_actions(abstract_actions);
  }

}