#ifndef MCMAS_PROTOCOLLINE_HPP
#define MCMAS_PROTOCOLLINE_HPP
#include <string>
#include <vector>
#include "expressions/Expression.hpp"

namespace mcmas {
  class ProtocolLine {
    public:
      Expression::Ptr condition;
      std::vector<std::string> enabled_actions;

      ProtocolLine(Expression::Ptr&& condition, const std::vector<std::string>& enabled_actions) 
      : condition(std::move(condition)),
        enabled_actions(enabled_actions)
      {}

      std::string to_string() const;

      ProtocolLine clone() const;
  };
}

#endif