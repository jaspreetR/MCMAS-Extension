#include <string>
#include <iostream>

#include "expressions/Operators2.hpp"

/*
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
  
  void visit(mcmas::LogicExpr& expr) {
    expr.accept(*this);
  };

  void visit(mcmas::ArithmeticExpr& expr) {
    expr.accept(*this);
  }

  void visit(mcmas::Bool& expr) {
    result += expr.value ? "true" : "false";
  }

  void visit(mcmas::Int& expr) {
    result += std::to_string(expr.value);
  }
};

struct FlipVisitor {
  template <typename Child, typename Op>
  void visit(mcmas::BinaryExpr<Child, Op>& expr) {
    expr.left->accept(*this);
    expr.right->accept(*this);
  }

  template <typename Child, typename Op>
  void visit(mcmas::UnaryExpr<Child, Op>& expr) {
    expr.child->accept(*this);
  }

  void visit(mcmas::BoolExpr& expr) {
    expr.accept(*this);
  }
  
  void visit(mcmas::LogicExpr& expr) {
    expr.accept(*this);
  };

  void visit(mcmas::ArithmeticExpr& expr) {
    expr.accept(*this);
  }

  void visit(mcmas::Bool& expr) {
    expr.value = !expr.value;
  }

  void visit(mcmas::Int& expr) {
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

  auto visit(mcmas::BoolExpr& expr) {
    return expr.accept(*this);
  }

  auto visit(mcmas::LogicExpr& expr) {
    return expr.accept(*this);
  };

  auto visit(mcmas::ArithmeticExpr& expr) {
    return expr.accept(*this);
  }

  bool visit(mcmas::Bool& expr) {
    return expr.value;
  }

  int visit(mcmas::Int& expr) {
    return expr.value;
  }
};

int main(int argc, char** argv) {
  std::cout << std::boolalpha;
  std::cout << "Hello World!" << std::endl;

  auto and_expr = mcmas::BoolExpr::And(mcmas::Bool(true), mcmas::Bool(false));
  auto not_expr = mcmas::BoolExpr::Not(mcmas::Bool(false));
  auto or_expr = mcmas::BoolExpr::Or(std::move(and_expr), std::move(not_expr));
  auto add_expr = mcmas::ArithmeticExpr::Add(mcmas::Int(10), mcmas::Int(22));
  mcmas::Bool b;
  b.value = false;

  ToStringVisitor tsvisitor;
  EvaluateVisitor evisitor;
  FlipVisitor fvisitor;

  fvisitor.visit(or_expr);
  tsvisitor.visit(or_expr);

  auto value1 = evisitor.visit(or_expr);
  auto value2 = evisitor.visit(add_expr);

  std::cout << value1 << std::endl;
  std::cout << value2 << std::endl;
  std::cout << tsvisitor.result << std::endl;
  //std::cout << evisitor.visit(b) << std::endl;

  return 0;
}
*/

int main(int argc, char** argv) {
  std::cout << std::boolalpha;
  std::cout << "Hello World!" << std::endl;

  auto expr = mcmas::Expression::And(mcmas::Expression::Bool(false), mcmas::Expression::Bool(true));
  auto expr2 = mcmas::Expression::Not(mcmas::Expression::Bool(false));
  mcmas::CountingVisitor counting_visitor;
  mcmas::EvalVisitor eval_visitor;

  expr->accept(counting_visitor);
  expr2->accept(counting_visitor);
  expr2->accept(eval_visitor);

  std::cout << counting_visitor.value << std::endl;

  expr->accept(eval_visitor);
  std::cout << std::get<bool>(eval_visitor.result) << std::endl;

  expr2->accept(eval_visitor);
  std::cout << std::get<bool>(eval_visitor.result) << std::endl;
}