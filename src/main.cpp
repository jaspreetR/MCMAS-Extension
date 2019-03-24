#include <string>
#include <iostream>
#include "expressions/Expressions.hpp"
#include "expressions/Operators.hpp"

struct ToStringVisitor {
  std::string result;
  
  template <typename Child, typename Op>
  void visit(mcmas::BinaryExpr<Child, Op>& expr) {
    result += "(";
    expr.left->accept(*this);
    result += " " + Op::token + " ";
    expr.right->accept(*this);
    result += ")";
  }

  template <typename Child, typename Op>
  void visit(mcmas::UnaryExpr<Child, Op>& expr) {
    result += "(";
    result += Op::token;
    expr.child->accept(*this);
    result += ")";
  }

  void visit(mcmas::BoolExpr& expr) {
    expr.accept(*this);
  }

  void visit(mcmas::Bool& expr) {
    result += expr.value ? "true" : "false";
  }

  void visit(mcmas::Int& expr) {
    result += std::to_string(expr.value);
  }
};

struct EvaluateVisitor {
  template <typename Child, typename Op>
  mcmas::ResultType<Op> visit(mcmas::BinaryExpr<Child, Op>& expr) {
    auto left_result = expr.left->accept(*this);
    auto right_result = expr.right->accept(*this);

    return Op::apply(left_result, right_result);
  }


  template <typename Child, typename Op>
  mcmas::ResultType<Op> visit(mcmas::UnaryExpr<Child, Op>& expr) {
    auto child_result = expr.child->accept(*this);
    return Op::apply(child_result);
  }

  bool visit(mcmas::BoolExpr& expr) {
    return expr.accept(*this);
  }

  bool visit(mcmas::Bool& expr) {
    return expr.value;
  }

  auto visit(mcmas::Int& expr) {
    return false;
  }
};

int main(int argc, char** argv) {
  std::cout << "Hello World!" << std::endl;

  auto and_expr = mcmas::BoolExpr::And(mcmas::Bool(true), mcmas::Bool(false));
  auto not_expr = mcmas::BoolExpr::Not(mcmas::Bool(false));
  auto or_expr = mcmas::BoolExpr::Or(std::move(and_expr), std::move(not_expr));
  mcmas::Bool b;
  b.value = false;

  ToStringVisitor visitor;
  EvaluateVisitor evisitor;
  visitor.visit(or_expr);

  auto value = evisitor.visit(or_expr);

  std::cout << value << std::endl;
  //std::cout << evisitor.visit(b) << std::endl;

  return 0;
}