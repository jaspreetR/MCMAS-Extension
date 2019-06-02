#include "AbstractAgent.hpp"
#include <algorithm>
#include "utils/Misc.hpp"
#include "utils/Overload.hpp"
#include "visitors/OwnerActionVisitor.hpp"

namespace mcmas {

  AbstractAgent::AbstractAgent(const AgentState& state, const SwarmAgent& concrete_agent, Expression::Ptr&& transition, int id) 
  : state(state)
  {
    name = generate_abstract_agent_name(concrete_agent.name, id);

    add_variable("is_active", BOOL());

    // set init_condition to set vars with state values
    for (const auto& [var_name, var_type] : concrete_agent.vars) {
      add_variable(var_name, var_type);
    }

    std::vector<Expression::Ptr> init_var_conditions;
    init_var_conditions.reserve(state.get().size());
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
    
    // TODO: generate these actions outside the constructor and store as shared pointer
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

    // replace owner actions of transition with compound actions of abstract agent
    OwnerActionVisitor visitor(action_register);
    transition->accept(visitor);
    transition = std::move(visitor.result);

    auto protocol_lines_power_set = power_set(concrete_agent.protocol.lines);
    for (const auto& line_set : protocol_lines_power_set) {
      std::vector<Expression::Ptr> conditions;
      conditions.reserve(line_set.size());
      std::set<std::string> actions;

      for (auto& line : line_set) {
        //auto subst_condition = state.substitute(line.condition.get());
        //conditions.emplace_back(std::move(subst_condition));
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

    add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(true)), transition->clone());
    add_evolution_line(Expression::Eq(Expression::Id("is_active"), Expression::Bool(false)), Expression::Not(transition->clone()));

  }

  std::string AbstractAgent::generate_abstract_agent_name(const std::string& concrete_name, int i) {
    return "Abs__" + concrete_name + "__" + std::to_string(i);
  }

}