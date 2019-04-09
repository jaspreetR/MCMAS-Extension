#ifndef MCMAS_APPLYVISITOR_HPP
#define MCMAS_APPLYVISITOR_HPP
#include <iostream>
#include "expressions/Expression.hpp"
#include "EvalVisitor.hpp"
#include "AgentState.hpp"

namespace mcmas {

  class ApplyVisitor : public ConstVisitor {
    public:
      AgentState result;
      const AgentState* context;

      ApplyVisitor() = default;
      ApplyVisitor(const AgentState* state) : result(*state), context(state) {}

/*
      void visit(const IntLiteral& expr) {
      }

      void visit(const BoolLiteral& expr) {
      }

      void visit(const Identifier& expr) {
      }

      void visit(const UnaryExpression& expr) {
      }
*/

      void visit(const BinaryExpression& expr) {
        if (dynamic_cast<EqOperator*>(expr.op.get())) { // is assignment expr
          // TODO: could crash here if expr is of incorrect form
          auto* identifier = static_cast<Identifier*>(expr.left.get());
          EvalVisitor eval_visitor(context);
          expr.right->accept(eval_visitor);
          result.set_value(identifier->id, eval_visitor.result);
        } else { // is and expr
          expr.left->accept(*this);
          expr.right->accept(*this);
        }
      }
  };

}

#endif