#ifndef MCMAS_SWARMAGENT_HPP
#define MCMAS_SWARMAGENT_HPP
#include <string>
#include <vector>
#include <set>
#include <map>
#include "AgentState.hpp"
#include "BaseType.hpp"
#include "Protocol.hpp"
#include "Evolution.hpp"

namespace mcmas {
  class GlobalActionVisitor;
  class AbstractAgent;

  class SwarmAgent {
    public:
      std::string name;
      //std::set<std::string> lobsvars;
      std::map<std::string, BaseType> vars;
      std::vector<std::string> actions;

      Expression::Ptr init_condition;
      Protocol protocol;
      Evolution evolution;

      SwarmAgent();

      void add_2d_position_variables(int max_x, int max_y);
      void add_variable(const std::string& var_name, BaseType var_type);
      void add_actions(const std::vector<std::string>& actions);
      void add_protocol_line(Expression::Ptr&& condition, const std::vector<std::string>& actions);
      void add_evolution_line(Expression::Ptr&& result, Expression::Ptr&& condition);
      void add_init_condition(Expression::Ptr&& init_condition);

      void apply_local_action_transform(int comm_distance);
      void apply_global_action_transform(mcmas::GlobalActionVisitor& visitor);
      std::vector<AgentState> get_all_states() const;

      std::vector<AbstractAgent> generate_abstract_agents() const;

      std::string to_string() const;

      SwarmAgent clone() const;
  };

}

#endif