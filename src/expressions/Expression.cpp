#include "expressions/Expression.hpp"
#include "expressions/Operator.hpp"
#include "visitors/Visitor.hpp"
#include "visitors/StringVisitor.hpp"
#include <cassert>

namespace mcmas {

  std::string Expression::to_string() const {
    auto visitor = StringVisitor();
    this->accept(visitor);
    return std::move(visitor.result);
  }

  Expression::Ptr Expression::And(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new AndOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::And(std::vector<Expression::Ptr>&& args) {
    assert(args.size() >= 2);

    auto last = std::move(*args.rbegin());
    auto second_last = std::move(*(args.rbegin()+1));
    auto result = And(std::move(second_last), std::move(last));
    for (auto it = args.rbegin()+2; it != args.rend(); ++it) {
      result = And(std::move(*it), std::move(result));
    }
    return result;
  }

  Expression::Ptr Expression::Or(Expression::Ptr&& left, Expression::Ptr&& right) {
    BinaryOperator::Ptr op(new OrOperator());
    return Expression::Ptr(new BinaryExpression(std::move(left), std::move(right), std::move(op)));
  }

  Expression::Ptr Expression::Or(std::vector<Expression::Ptr>&& args) {
    assert(args.size() >= 2);

    auto last = std::move(*args.rbegin());
    auto second_last = std::move(*(args.rbegin()+1));
    auto result = Or(std::move(second_last), std::move(last));
    for (auto it = args.rbegin()+2; it != args.rend(); ++it) {
      result = Or(std::move(*it), std::move(result));
    }
    return result;
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

  Expression::Ptr Expression::Id(const std::string& id) {
    return Expression::Ptr(new Identifier(id));
  }

  Expression::Ptr Expression::Id(const std::string& owner, const std::string& id) {
    return Expression::Ptr(new Identifier(owner, id));
  }

  void BinaryExpression::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void BinaryExpression::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  Expression::Ptr BinaryExpression::clone() const {
    return Expression::Ptr(new BinaryExpression(left->clone(), right->clone(), op->clone()));
  }

  void UnaryExpression::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void UnaryExpression::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  Expression::Ptr UnaryExpression::clone() const {
    return Expression::Ptr(new UnaryExpression(child->clone(), op->clone()));
  }

  void BoolLiteral::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void BoolLiteral::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  Expression::Ptr BoolLiteral::clone() const {
    return Expression::Ptr(new BoolLiteral(value));
  }

  void IntLiteral::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void IntLiteral::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  Expression::Ptr IntLiteral::clone() const {
    return Expression::Ptr(new IntLiteral(value));
  }

  void Identifier::accept(Visitor& visitor) {
    visitor.visit(*this);
  }

  void Identifier::accept(ConstVisitor& visitor) const {
    visitor.visit(*this);
  }

  Expression::Ptr Identifier::clone() const {
    return Expression::Ptr(new Identifier(owner, id));
  }

  bool Identifier::is_current_agent() const {
    return owner == "";
  }

  bool Identifier::is_environment_action() const {
    return owner == "Environment" && id == "Action";
  }

  bool Identifier::is_local_action() const {
    return owner == "" && id == "LocalAction";
  }

  bool Identifier::is_global_action() const {
    return owner == "" && id == "GlobalAction";
  }

  bool Identifier::is_owner_action() const {
    return owner == "" && id == "Action";
  }
}