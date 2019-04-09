#include <string>
#include <iostream>

#include "expressions/Expression.hpp"
#include "visitors/Visitor.hpp"
#include "utils/Overload.hpp"
#include "utils/Misc.hpp"
#include "SwarmAgent.hpp"
#include "utils/DynamicBitset.hpp"

using mcmas::Expression;

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

  auto states = agent.get_all_states();
  auto eval_expr = Expression::Add(Expression::Id("pos_x"), Expression::Int(3));

  for (const auto& state : states) {
    for (const auto& [name, value] : state.get()) {
      std::visit([&](auto&& value){
        std::cout << name << " " << value << ", ";
      }, value);
    }

    std::cout << std::get<int>(state.evaluate(eval_expr.get()));
    std::cout << std::endl;
  }

  mcmas::DynamicBitset bitset(2);
  for (size_t i = 0; i < 1u << bitset.size(); ++i) {
    std::cout << bitset.to_string() << std::endl;
    ++bitset;
  }
  std::cout << bitset.to_string() << std::endl;

  auto apply_expr = Expression::Eq(Expression::Id("pos_x"), Expression::Add(Expression::Id("pos_x"), Expression::Int(1))); 
  auto apply_expr2 = Expression::Eq(Expression::Id("pos_x"), Expression::Sub(Expression::Id("pos_x"), Expression::Int(1))); 
  auto new_state = states[0].apply(apply_expr.get());

  for (const auto& [name, value] : new_state.get()) {
    std::visit([&](auto&& value){
      std::cout << name << " " << value << ", ";
    }, value);
  }
  std::cout << std::endl;

  std::vector<std::vector<int>> new_states(states.size());
  std::vector<Expression::Ptr> exprs;
  exprs.emplace_back(Expression::Eq(Expression::Id("pos_x"), Expression::Add(Expression::Id("pos_x"), Expression::Int(1))));
  exprs.emplace_back(Expression::Eq(Expression::Id("pos_x"), Expression::Add(Expression::Id("pos_x"), Expression::Int(-1))));
  exprs.emplace_back(Expression::Eq(Expression::Id("pos_y"), Expression::Add(Expression::Id("pos_x"), Expression::Int(1))));
  exprs.emplace_back(Expression::Eq(Expression::Id("pos_y"), Expression::Add(Expression::Id("pos_x"), Expression::Int(-1))));
  exprs.emplace_back(Expression::Eq(Expression::Id("bit"), Expression::Not(Expression::Id("bit"))));

  for (size_t i = 0; i < states.size(); ++i) {
    const auto& state = states[i];
    for (const auto& expr : exprs) {
      auto new_state = state.apply(expr.get());
      for (size_t j = 0; j < states.size(); ++j) {
        if (new_state == states[j]) {
          new_states[i].push_back(j);
          break;
        }
      }
    }
  }

  for (size_t i = 0; i < new_states.size(); ++i) {
    std::cout << i << ": "; 
    for (auto j : new_states[i]) {
      std::cout << j << " ";
    } 
    std::cout << std::endl;
  }

  auto product = mcmas::cartesian_product(std::vector(2, std::vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
  /*
  for (auto& elem : product) {
    for (auto i : elem) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
  */
  std::cout << product[0][0] << std::endl;
}