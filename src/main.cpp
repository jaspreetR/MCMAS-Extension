#include <string>
#include <iostream>

#include "expressions/Expression.hpp"
#include "expressions/Visitor.hpp"
#include "SwarmAgent.hpp"

int main(int argc, char** argv) {
  std::cout << std::boolalpha;
  std::cout << "Hello World!" << std::endl;

  /*
  auto expr = mcmas::Expression::And(mcmas::Expression::Bool(false), mcmas::Expression::Bool(true));
  auto expr2 = mcmas::Expression::Not(mcmas::Expression::Bool(false));
  auto expr3 = mcmas::Expression::Add(mcmas::Expression::Int(6), mcmas::Expression::Int(3));

  mcmas::CountingVisitor counting_visitor;
  mcmas::EvalVisitor eval_visitor;
  mcmas::StringVisitor string_visitor;
  mcmas::FlipVisitor flip_visitor;
  mcmas::FlipExprVisitor flip_expr_visitor;

  expr->accept(string_visitor);
  std::cout << string_visitor.result << std::endl;

  expr->accept(flip_expr_visitor);
  //expr = std::move(flip_expr_visitor.result);
  expr->accept(string_visitor);
  std::cout << string_visitor.result << std::endl;

  expr3->accept(eval_visitor);
  std::cout << std::get<int>(eval_visitor.result) << std::endl;
  */

  mcmas::SwarmAgent agent(2, 2, 1);
  agent.name = "TestAgent";
  agent.add_actions({"flip", "none"});
  agent.add_variable("bit", mcmas::BOOL());
  agent.add_protocol_line(mcmas::Expression::Eq(mcmas::Expression::Id("bit"), mcmas::Expression::Bool(false)), {"flip"});
  agent.add_protocol_line(mcmas::Expression::Eq(mcmas::Expression::Id("bit"), mcmas::Expression::Bool(true)), {"none"});
  std::cout << agent.to_string() << std::endl;
  std::cout << std::endl;

  agent.apply_local_action_transform();
  std::cout << agent.to_string() << std::endl;

}