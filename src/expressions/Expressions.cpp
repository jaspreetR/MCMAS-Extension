#include "expressions/Operators2.hpp"

namespace mcmas {

  void Visitor::visit(UnaryExpression& expr) {
    expr.child->accept(*this);
  }   

  void Visitor::visit(BinaryExpression& expr) {
    expr.left->accept(*this);
    expr.right->accept(*this);
  }   

  void Visitor::visit(BoolLiteral& expr) {
  }

  Expression::Ptr Expression::And(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new AndOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Or(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new OrOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Not(Expression::Ptr&& child) {
    UnaryOperator::Ptr op(new NotOperator());
    return Expression::Ptr(new UnaryExpression(std::move(child), std::move(op)));
  }

  Expression::Ptr Expression::Bool(bool value) {
    return Expression::Ptr(new BoolLiteral(value));
  }

}