#ifndef MCMAS_EVALVISITOR_HPP
#define MCMAS_EVALVISITOR_HPP
#include "Visitor.hpp"
#include "AgentState.hpp"

namespace mcmas {

  class EvalVisitor : public ConstVisitor {
    public:
      EvalType result;
      const AgentState* context;

      EvalVisitor() = default;
      EvalVisitor(const AgentState* state) : context(state) {}

      void visit(const IntLiteral& expr) {
        result = expr.value;
      }

      void visit(const BoolLiteral& expr) {
        result = expr.value;
      }

      void visit(const Identifier& expr) {
        result = context->get().at(expr.id);
      }

      void visit(const UnaryExpression& expr) {
        expr.child->accept(*this);
        auto child_result = result;

        result = expr.op->apply(child_result);
      }

      void visit(const BinaryExpression& expr) {
        expr.left->accept(*this);
        auto left_result = result;

        expr.right->accept(*this);
        auto right_result = result;

        result = expr.op->apply(left_result, right_result);
      }
  };

}

#endif