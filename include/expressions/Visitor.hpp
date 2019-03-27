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

  class CountingVisitor : public ConstVisitor {
    public:
      int value = 0;

      void visit(const BoolLiteral& expr) {
        ++value;
      }
  };

  class EvalVisitor : public ConstVisitor {
    public:
      EvalType result;

      void visit(const IntLiteral& expr) {
        result = expr.value;
      }

      void visit(const BoolLiteral& expr) {
        result = expr.value;
      }

      void visit(const Identifier& expr) {
        result = 6;
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

  class StringVisitor : public ConstVisitor {
    public:
      std::string result;

      void visit(const IntLiteral& expr) {
        result = std::to_string(expr.value);
      }

      void visit(const BoolLiteral& expr) {
        result = expr.value ? "true" : "false";
      }

      void visit(const Identifier& expr) {
        result = expr.value;
      }

      void visit(const UnaryExpression& expr) {
        expr.child->accept(*this);
        auto child_result = std::move(result);

        result = "(" + expr.op->getToken() + child_result + ")";
      } 

      void visit(const BinaryExpression& expr) {
        expr.left->accept(*this);
        auto left_result = std::move(result);

        expr.right->accept(*this);
        auto right_result = std::move(result);

        result = "(" + left_result + " " + expr.op->getToken() + " " + right_result + ")";
      }
  };
}

#endif