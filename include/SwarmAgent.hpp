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

  class SwarmAgent {
    public:
      std::string name;
      //std::set<std::string> lobsvars;
      std::map<std::string, BaseType> vars;
      std::vector<std::string> actions;
      Protocol protocol;
      Evolution evolution;

      const int comm_distance;
      const int max_x;
      const int max_y;

      SwarmAgent(int max_x, int max_y, int comm_distance);

      void add_variable(const std::string& var_name, BaseType var_type);
      void add_actions(const std::vector<std::string>& actions);
      void add_protocol_line(Expression::Ptr&& condition, const std::vector<std::string>& actions);
      void add_evolution_line(Expression::Ptr&& result, Expression::Ptr&& condition);

      void apply_local_action_transform();
      std::vector<AgentState> get_all_states();

      std::string to_string() const;
  };

}

#endif