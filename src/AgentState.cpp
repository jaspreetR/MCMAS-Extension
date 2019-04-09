#include "AgentState.hpp"
#include "visitors/EvalVisitor.hpp"
#include "visitors/ApplyVisitor.hpp"

namespace mcmas {

  AgentState::State& AgentState::get() {
    return state;
  }

  const AgentState::State& AgentState::get() const {
    return state;
  }

  void AgentState::set_value(std::string var_name, std::variant<int, bool> value) {
    state[var_name] = value;
  }

  EvalType AgentState::evaluate(const Expression* expr) const {
    EvalVisitor visitor(this);
    expr->accept(visitor);
    return visitor.result;
  }

  AgentState AgentState::apply(const Expression* expr) const {
    ApplyVisitor visitor(this);
    expr->accept(visitor);
    return visitor.result;
  }

  bool AgentState::operator==(const AgentState& rhs) const {
    return state == rhs.state;
  }

}