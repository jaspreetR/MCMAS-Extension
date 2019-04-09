#ifndef MCMAS_VISITOR_HPP
#define MCMAS_VISITOR_HPP
#include "expressions/Expression.hpp"

namespace mcmas {

  class Visitor {
    public:
      virtual void visit(UnaryExpression& expr);
      virtual void visit(BinaryExpression& expr);
      virtual void visit(BoolLiteral& expr);
      virtual void visit(IntLiteral& expr);
      virtual void visit(Identifier& expr);
  };

  class ConstVisitor {
    public:
      virtual void visit(const UnaryExpression& expr);
      virtual void visit(const BinaryExpression& expr);
      virtual void visit(const BoolLiteral& expr);
      virtual void visit(const IntLiteral& expr);
      virtual void visit(const Identifier& expr);
  };

/*
  class CountingVisitor : public ConstVisitor {
    public:
      int value = 0;

      void visit(const BoolLiteral& expr) {
        ++value;
      }
  };


  class FlipVisitor : public Visitor {
    public:
      void visit(BoolLiteral& expr) {
        expr.value = !expr.value;
      }
  };

  class FlipExprVisitor : public Visitor {
    public:
      void visit(BinaryExpression& expr) {
        expr.left->accept(*this);
        if (dynamic_cast<BoolLiteral*>(expr.left.get())) {
          expr.left = Expression::Not(std::move(expr.left));
        }

        expr.right->accept(*this);
        if (dynamic_cast<BoolLiteral*>(expr.right.get())) {
          expr.right = Expression::Not(std::move(expr.right));
        }
      }

      void visit(UnaryExpression& expr) {
        expr.child->accept(*this);
        if (dynamic_cast<BoolLiteral*>(expr.child.get())) {
          expr.child = Expression::Not(std::move(expr.child));
        }
      }
  };
*/

}

#endif