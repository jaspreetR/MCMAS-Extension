#include "AgentState.hpp"
#include "visitors/EvalVisitor.hpp"
#include "visitors/ApplyVisitor.hpp"
#include "visitors/SubstVisitor.hpp"

namespace mcmas {

  AgentState::State& AgentState::get() {
    return state;
  }

  const AgentState::State& AgentState::get() const {
    return state;
  }

  void AgentState::set_value(const std::string& var_name, std::variant<int, bool> value) {
    state[var_name] = value;
  }

  std::variant<int, bool> AgentState::get_value(const std::string& var_name) const {
    return state.at(var_name);
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

  Expression::Ptr AgentState::substitute(const Expression* expr) const {
    SubstVisitor visitor(this);
    expr->accept(visitor);
    return std::move(visitor.result);
  }

  bool AgentState::operator==(const AgentState& rhs) const {
    return state == rhs.state;
  }

}