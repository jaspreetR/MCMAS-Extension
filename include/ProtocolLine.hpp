#ifndef MCMAS_PROTOCOLLINE_HPP
#define MCMAS_PROTOCOLLINE_HPP
#include <vector>
#include "expressions/Expression.hpp"

namespace mcmas {
  class ProtocolLine {
    public:
      Expression::Ptr condition;
      std::vector<std::string> enabled_actions;

      ProtocolLine(Expression::Ptr&& condition, const std::vector<std::string> enabled_actions) 
      : condition(std::move(condition)),
        enabled_actions(enabled_actions)
      {}
  };
}

#endif