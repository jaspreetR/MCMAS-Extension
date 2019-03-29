#ifndef MCMAS_SWARMAGENT_HPP
#define MCMAS_SWARMAGENT_HPP
#include <string>
#include <vector>
#include <set>
#include <map>
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

      void add_variable(const std::string& var_name, BaseType var_type);
      void add_actions(const std::vector<std::string>& actions);
      void add_protocol_line(Expression::Ptr&& condition, const std::vector<std::string>& actions);
      void add_evolution_line(Expression::Ptr&& result, Expression::Ptr&& condition);

      std::string to_string() const;
  };

}

#endif