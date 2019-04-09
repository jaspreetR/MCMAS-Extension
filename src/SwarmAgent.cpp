#include "SwarmAgent.hpp"
#include "utils/Misc.hpp"

namespace mcmas {

  std::vector<AgentState> variable_cartesian_product(const std::vector<AgentState>& current_states, 
                                                const std::string& var_name, 
                                                const IntBoolVector& values);

  SwarmAgent::SwarmAgent(int max_x, int max_y, int comm_distance) 
  : comm_distance(comm_distance),
    max_x(max_x),
    max_y(max_y) 
  {
    add_variable("pos_x", RANGED_INT(1, max_x));  
    add_variable("pos_y", RANGED_INT(1, max_y));  
  }

  void SwarmAgent::add_variable(const std::string& var_name, BaseType var_type) {
    vars[var_name] = var_type;
  }

  void SwarmAgent::add_actions(const std::vector<std::string>& actions) {
    this->actions = actions;
  }

  void SwarmAgent::add_protocol_line(Expression::Ptr&& condition, const std::vector<std::string>& actions) {
    ProtocolLine protocol_line(std::move(condition), actions);
    protocol.lines.emplace_back(std::move(protocol_line));
  }

  void SwarmAgent::add_evolution_line(Expression::Ptr&& result, Expression::Ptr&& condition) {
    EvolutionLine evolution_line(std::move(result), std::move(condition));
    evolution.lines.emplace_back(std::move(evolution_line));
  }

  void SwarmAgent::apply_local_action_transform() {
    std::vector<std::string> new_actions;
    for (const auto& action : actions) {
      for (int i = 1; i <= max_x; ++i) {
        for (int j = 1; j <= max_y; ++j) {
          auto local_action = generate_local_action(action, i, j);
          new_actions.emplace_back(std::move(local_action));
        }
      }
    }
    actions = std::move(new_actions);

    protocol.apply_local_action_transform(max_x, max_y, comm_distance);
  }

  std::vector<AgentState> SwarmAgent::get_all_states() {
    std::vector<AgentState> states(1);    
    for (const auto& [name, type] : vars) {
      auto possible_values = ::mcmas::generate_possible_values(type);
      states = variable_cartesian_product(states, name, possible_values);
    }
    return states;
  }

  std::vector<AgentState> variable_cartesian_product(const std::vector<AgentState>& current_states, 
                                                const std::string& var_name, 
                                                const IntBoolVector& values)
  {
    std::vector<AgentState> new_states;
    for (const auto& current_state : current_states) {
      std::visit([&](auto&& values) {
        for (auto value : values) {
          auto new_state = current_state.get();
          new_state[var_name] = value;
          new_states.emplace_back(std::move(new_state));
        }
      }, values);
    }
    return new_states;
  }

  std::string SwarmAgent::to_string() const {
    std::string var_string = "Vars : \n";
    for (auto& [id, type] : vars) {
      std::string type_string = ::mcmas::to_string(type);
      var_string += id + " : " + type_string + ";\n";
    };
    var_string += "end Vars \n";

    std::string action_string = "Actions = { ";
    for (auto it = actions.begin(); it != actions.end(); ++it) {
      if (it != --actions.end()) {
        action_string += *it + ", ";
      } else {
        action_string += *it + " ";
      }
    }
    action_string += "};\n";

    std::string protocol_string = protocol.to_string();

    std::string evolution_string = evolution.to_string();
    
    return "Agent " + name + "\n" + 
           var_string + 
           action_string + 
           protocol_string + 
           evolution_string +
           "end Agent\n";
  }

}