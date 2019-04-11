#ifndef MCMAS_AGENTSTATE_HPP
#define MCMAS_AGENTSTATE_HPP
#include <map>
#include <string>
#include "expressions/Expression.hpp"

namespace mcmas {

  class AgentState {
    public:
      using State = std::map<std::string, std::variant<int, bool>>;
      State state;

      AgentState() = default;
      AgentState(const State& state) : state(state)
      {
      }

      State& get();
      const State& get() const;

      void set_value(const std::string& var_name, std::variant<int, bool> value);
      std::variant<int, bool> get_value(const std::string& var_name) const;

      // Assume expr does not contain any vars of type "Environment.ID" 
      // since this could always be extracted out of evalution condition
      EvalType evaluate(const Expression* expr) const;
      AgentState apply(const Expression* expr) const;
      Expression::Ptr substitute(const Expression* expr) const;

      bool operator==(const AgentState& rhs) const;
  };

}

#endif
