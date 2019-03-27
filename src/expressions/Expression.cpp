#include "expressions/Expression.hpp"
#include "expressions/Operator.hpp"
#include "expressions/Visitor.hpp"

namespace mcmas {

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

  Expression::Ptr Expression::Lt(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new LtOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Leq(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new LeqOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Gt(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new GtOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Geq(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new GeqOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Eq(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new EqOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Neq(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new NeqOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Add(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new AddOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Sub(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new SubOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Mul(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new MulOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Div(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new DivOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::BitAnd(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new BitAndOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::BitOr(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new BitOrOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::BitXor(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new BitXorOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::BitNot(Expression::Ptr&& child) {
    UnaryOperator::Ptr op(new BitNotOperator());
    return Expression::Ptr(new UnaryExpression(std::move(child), std::move(op)));
  }

  Expression::Ptr Expression::Bool(bool value) {
    return Expression::Ptr(new BoolLiteral(value));
  }

  Expression::Ptr Expression::Int(int value) {
    return Expression::Ptr(new IntLiteral(value));
  }

  Expression::Ptr Expression::Id(const std::string& value) {
    return Expression::Ptr(new Identifier(value));
  }

  void BinaryExpression::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void BinaryExpression::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  void UnaryExpression::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void UnaryExpression::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  void BoolLiteral::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void BoolLiteral::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  void IntLiteral::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void IntLiteral::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  void Identifier::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void Identifier::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }
}