#ifndef MCMAS_EXPRESSIONS_HPP
#define MCMAS_EXPRESSIONS_HPP
#include <variant>
#include <string>
#include "utils/DeepPtr.hpp"

namespace mcmas {
  
  using EvalType = std::variant<int, bool>;

  class Visitor;
  class UnaryExpression;
  class BinaryExpression;
  class UnaryOperator;
  class BinaryOperator;
  class BoolLiteral;

  class Visitor {
    public:
      virtual void visit(UnaryExpression& expr);
      virtual void visit(BinaryExpression& expr);
      virtual void visit(BoolLiteral& expr);
  };

  class CountingVisitor : public Visitor {
    public:
      int value = 0;

      void visit(BoolLiteral& expr) {
        ++value;
      }
  };


  class UnaryOperator {
    public:
      using Ptr = std::unique_ptr<UnaryOperator>;
      virtual EvalType apply(EvalType arg) = 0;
      virtual std::string getToken() = 0;
  };

  class BinaryOperator {
    public:
      using Ptr = std::unique_ptr<BinaryOperator>;
      virtual EvalType apply(EvalType left, EvalType right) = 0;
      virtual std::string getToken() = 0;
  };

  class AndOperator : public BinaryOperator{
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<bool>(left) && std::get<bool>(right)};
      }

      std::string getToken() {
        return "and";
      } 
  };

  class OrOperator : public BinaryOperator {
    public:
      EvalType apply(EvalType left, EvalType right) {
        return {std::get<bool>(left) || std::get<bool>(right)};
      }

      std::string getToken() {
        return "or";
      } 
  };

  class NotOperator : public UnaryOperator {
    public:
      EvalType apply(EvalType child) {
        return {!std::get<bool>(child)};
      }

      std::string getToken() {
        return "!";
      } 
  };

  class Expression {
    public:
      using Ptr = std::unique_ptr<Expression>;
      virtual void accept(Visitor& visitor) = 0;

      static Ptr And(Ptr&& left, Ptr&& right);
      static Ptr Or(Ptr&& left, Ptr&& right);
      static Ptr Not(Ptr&& child);
      static Ptr Bool(bool value);
  };

  class BinaryExpression : public Expression {
    private:
      BinaryExpression(Expression::Ptr&& left, Expression::Ptr&& right, BinaryOperator::Ptr&& op)
      : left(std::move(left)),
        right(std::move(right)),
        op(std::move(op))
      {}

    public:
      friend class Expression;
      Expression::Ptr left;
      Expression::Ptr right;
      BinaryOperator::Ptr op;

      void accept(Visitor& visitor) {
        visitor.visit(*this);
      }
  };

  class UnaryExpression : public Expression {
    private:
      UnaryExpression(Expression::Ptr&& child, UnaryOperator::Ptr&& op)
      : child(std::move(child)),
        op(std::move(op))
      {}

    public:
      friend class Expression;
      Expression::Ptr child;
      UnaryOperator::Ptr op;

      void accept(Visitor& visitor) {
        visitor.visit(*this);
      }
  };

  class BoolLiteral : public Expression {
    private:
      BoolLiteral(bool value) : value(value) {}

    public:
      friend class Expression;
      bool value;

      void accept(Visitor& visitor) {
        visitor.visit(*this);
      }
  };

  class EvalVisitor : public Visitor {
    public:
      EvalType result;

      void visit(BoolLiteral& expr) {
        result = expr.value;
      }

      void visit(UnaryExpression& expr) {
        expr.child->accept(*this);
        auto child_result = result;

        result = expr.op->apply(child_result);
      }

      void visit(BinaryExpression& expr) {
        expr.left->accept(*this);
        auto left_result = result;

        expr.right->accept(*this);
        auto right_result = result;

        result = expr.op->apply(left_result, right_result);
      }
  };
}

#endif