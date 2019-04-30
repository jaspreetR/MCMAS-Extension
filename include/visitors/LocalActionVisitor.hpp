#ifndef MCMAS_LOCALACTIONVISITOR_HPP
#define MCMAS_LOCALACTIONVISITOR_HPP
#include <iostream>
#include <memory>
#include "expressions/Expression.hpp"
#include "Visitor.hpp"
#include "utils/Misc.hpp"

namespace mcmas {

  class LocalActionVisitor : public ConstVisitor {
    public:
      int i;
      int j;
      int max_x;
      int max_y;
      int comm_distance;
      Expression::Ptr result;

      LocalActionVisitor(int i, int j, int max_x, int max_y, int comm_distance) 
      : i(i), j(j), max_x(max_x), max_y(max_y), 
        comm_distance(comm_distance) {}

      void visit(const IntLiteral& expr) {
        result = expr.clone();
      }

      void visit(const BoolLiteral& expr) {
        result = expr.clone();
      }

      void visit(const Identifier& expr) {
        result = expr.clone();
      }

      void visit(const UnaryExpression& expr) {
        expr.child->accept(*this);
        result = Expression::Ptr(new UnaryExpression(std::move(result), expr.op->clone()));
      }

      void visit(const BinaryExpression& expr) {
        // check if current expr is a local action assignment
        if (dynamic_cast<EqOperator*>(expr.op.get())) {
          auto* left_id = dynamic_cast<Identifier*>(expr.left.get());
          if (left_id && left_id->is_local_action()) {
            auto* action_id = static_cast<Identifier*>(expr.right.get());
            result = generate_local_action_expression(action_id->id, i, j, max_x, max_y, comm_distance);
            return;
          }
        }

        expr.left->accept(*this);
        auto left_result = std::move(result);

        expr.right->accept(*this);
        auto right_result = std::move(result);

        result = Expression::Ptr(new BinaryExpression(std::move(left_result), std::move(right_result), expr.op->clone()));
      }
  };

}

#endif