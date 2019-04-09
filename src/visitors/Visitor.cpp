#include "visitors/Visitor.hpp"
#include "expressions/Expression.hpp"

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

  void Visitor::visit(IntLiteral& expr) {
  }

  void Visitor::visit(Identifier& expr) {
  }

  void ConstVisitor::visit(const UnaryExpression& expr) {
    expr.child->accept(*this);
  }   

  void ConstVisitor::visit(const BinaryExpression& expr) {
    expr.left->accept(*this);
    expr.right->accept(*this);
  }   

  void ConstVisitor::visit(const BoolLiteral& expr) {
  }

  void ConstVisitor::visit(const IntLiteral& expr) {
  }

  void ConstVisitor::visit(const Identifier& expr) {
  }
}