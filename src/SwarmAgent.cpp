#include "SwarmAgent.hpp"
#include <cassert>
#include "utils/Misc.hpp"
#include "visitors/GlobalActionVisitor.hpp"
#include "AbstractAgent.hpp"

namespace mcmas {

  std::vector<AgentState> variable_cartesian_product(const std::vector<AgentState>& current_states, 
                                                const std::string& var_name, 
                                                const IntBoolVector& values);

  SwarmAgent::SwarmAgent() {
    init_condition = Expression::Bool(true);
  }

  void SwarmAgent::add_2d_position_variables(int max_x, int max_y) {
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

  void SwarmAgent::add_init_condition(Expression::Ptr&& init_condition) {
    this->init_condition = std::move(init_condition);
  }

  void SwarmAgent::apply_local_action_transform(int comm_distance) {
    assert(vars.find("pos_x") != vars.end() && vars.find("pos_x") != vars.end());

    int max_x = std::get<RANGED_INT>(vars["pos_x"]).max;
    int max_y = std::get<RANGED_INT>(vars["pos_y"]).max;

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
    evolution.apply_local_action_transform(max_x, max_y, comm_distance);
  }

  void SwarmAgent::apply_global_action_transform(GlobalActionVisitor& visitor) {
    evolution.apply_global_action_transform(visitor);
  }

  std::vector<AgentState> SwarmAgent::get_all_states() {
    std::vector<AgentState> states(1);    
    for (const auto& [name, type] : vars) {
      auto possible_values = ::mcmas::generate_possible_values(type);
      states = variable_cartesian_product(states, name, possible_values);
    }
    return states;
  }

  std::vector<AbstractAgent> SwarmAgent::generate_abstract_agents() {

    std::vector<Expression*> ev_transitions;
    ev_transitions.reserve(evolution.lines.size());
    
    std::vector<Expression*> ev_conditions;
    ev_conditions.reserve(evolution.lines.size());

    for (const auto& line : evolution.lines) {
      ev_transitions.push_back(line.result.get());
      ev_conditions.push_back(line.condition.get());
    }

    auto states = get_all_states();

    std::vector<std::vector<Expression::Ptr>> activation_conditions(states.size());

    for (const auto& state : states) {
      for (size_t i = 0; i < ev_transitions.size(); ++i) {
        auto* transition = ev_transitions[i];
        auto new_state = state.apply(transition);

        // TODO: quadratic complexity could be n log n
        for (size_t j = 0; j < states.size(); ++j) {
          if (new_state == states[j]) {
            activation_conditions[j].push_back(state.substitute(ev_conditions[i]));
            break;
          }
        }
      }
    }

    std::vector<Expression::Ptr> disjunct_activation_conditions;
    disjunct_activation_conditions.reserve(activation_conditions.size());
    for (auto& conditions : activation_conditions) {
      Expression::Ptr disjunct_activation_condition;

      if (conditions.size() >= 2) {
        disjunct_activation_condition = Expression::Or(std::move(conditions));
      } else if (conditions.size() == 1) {
        disjunct_activation_condition = std::move(conditions[0]);
      } else if (conditions.size() == 0) {
        disjunct_activation_condition = Expression::Bool(false);
      } else {
        std::cout << "should not reach here" << std::endl;
      }

      disjunct_activation_conditions.emplace_back(std::move(disjunct_activation_condition));
    }

    std::vector<AbstractAgent> result;
    result.reserve(states.size());

    for (size_t i = 0; i < states.size(); ++i) {
      auto agent = AbstractAgent(states[i], *this, std::move(disjunct_activation_conditions[i]), i);
      result.emplace_back(std::move(agent));
    }

    return result;
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

  SwarmAgent SwarmAgent::clone() const {
    SwarmAgent result;
    result.name = name;
    result.vars = vars;
    result.actions = actions;
    result.protocol = protocol.clone();
    result.evolution = evolution.clone();

    return result;
  }

}