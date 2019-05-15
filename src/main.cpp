#include <string>
#include <iostream>

#include "expressions/Expression.hpp"
#include "visitors/Visitor.hpp"
#include "visitors/StringVisitor.hpp"
#include "visitors/GlobalActionVisitor.hpp"
#include "utils/Overload.hpp"
#include "utils/Misc.hpp"
#include "SwarmAgent.hpp"
#include "AbstractAgent.hpp"
#include "Evaluation.hpp"
#include "SwarmSystem.hpp"
#include "utils/DynamicBitset.hpp"

using mcmas::Expression;
using mcmas::Formula;

int main(int argc, char** argv) {
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

  /*
  mcmas::SwarmAgent agent;
  agent.name = "TestAgent";
  agent.add_actions({"flip", "none"});
  agent.add_variable("bit", mcmas::BOOL());
  agent.add_2d_position_variables(3, 3);
  agent.add_protocol_line(mcmas::Expression::Eq(mcmas::Expression::Id("bit"), mcmas::Expression::Bool(false)), {"flip"});
  agent.add_protocol_line(mcmas::Expression::Eq(mcmas::Expression::Id("bit"), mcmas::Expression::Bool(true)), {"none"});
  agent.add_evolution_line(Expression::Eq(Expression::Id("bit"), Expression::Bool(true)), Expression::Eq(Expression::Id("LocalAction"), Expression::Id("flip")));
  std::cout << agent.to_string() << std::endl;
  std::cout << std::endl;

  agent.apply_local_action_transform(1);
  auto agent2 = agent.clone();
  agent2.name = "TestAgent2";

  mcmas::GlobalActionVisitor gav;
  gav.add_actions_from_sa(agent);
  gav.add_actions_from_sa(agent2);
  agent.apply_global_action_transform(gav);
  agent2.apply_global_action_transform(gav);

  std::cout << agent.to_string() << std::endl;
  std::cout << std::endl;
  std::cout << agent2.to_string() << std::endl;
  std::cout << std::endl;

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

  mcmas::SwarmAgent simple_agent;
  simple_agent.name = "TestAgent";
  simple_agent.add_actions({"zzz", "flip", "none"});
  simple_agent.add_variable("bit", mcmas::BOOL());
  simple_agent.add_variable("jib", mcmas::BOOL());
  simple_agent.add_protocol_line(mcmas::Expression::Eq(mcmas::Expression::Id("bit"), mcmas::Expression::Bool(false)), {"flip"});
  simple_agent.add_protocol_line(mcmas::Expression::Eq(mcmas::Expression::Id("jib"), mcmas::Expression::Bool(true)), {"none"});
  simple_agent.add_evolution_line(Expression::Eq(Expression::Id("bit"), Expression::Bool(true)), Expression::Eq(Expression::Id("GlobalAction"), Expression::Id("flip")));
  std::cout << simple_agent.to_string() << std::endl;
  std::cout << std::endl;

  */

  /*
  auto simple_agent_state = simple_agent.get_all_states();
  mcmas::AbstractAgent abstract_agent(simple_agent_state[0], simple_agent, 0);
  std::cout << abstract_agent.to_string() << std::endl;
  std::cout << std::endl;
  */

  /*

  auto simple_agent_abstracts = simple_agent.generate_abstract_agents();

  for (const auto& abstract_agent : simple_agent_abstracts) {
    std::cout << abstract_agent.to_string() << std::endl << std::endl;
  }

  mcmas::DynamicBitset bitset(2);
  for (size_t i = 0; i < 1u << bitset.size(); ++i) {
    std::cout << bitset.to_string() << std::endl;
    ++bitset;
  }
  std::cout << bitset.to_string() << std::endl;

  std::vector<int> super_set = {1, 2, 3};
  auto power_set = mcmas::power_set(super_set);
  for (auto& subset : power_set) {
    for (auto val : subset) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

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
  exprs.emplace_back(Expression::Eq(Expression::Id("pos_y"), Expression::Add(Expression::Id("pos_y"), Expression::Int(1))));
  exprs.emplace_back(Expression::Eq(Expression::Id("pos_y"), Expression::Add(Expression::Id("pos_y"), Expression::Int(-1))));
  exprs.emplace_back(Expression::Eq(Expression::Id("bit"), Expression::Not(Expression::Id("bit"))));

  for (size_t i = 0; i < states.size(); ++i) {
    const auto& state = states[i];
    for (const auto& expr : exprs) {
      auto new_state = state.apply(expr.get());
      for (size_t j = 0; j < states.size(); ++j) {
        if (new_state == states[j]) {
          new_states[j].push_back(i);
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

  mcmas::StringVisitor string_visitor;
  mcmas::AgentState state;
  state.set_value("i", 1);
  state.set_value("j", 2);

  auto subst_expr = Expression::Eq(Expression::Id("i"), Expression::Id("j"));
  subst_expr->accept(string_visitor);
  std::cout << string_visitor.result << std::endl;

  auto subst_expr2 = state.substitute(subst_expr.get());
  subst_expr2->accept(string_visitor);
  std::cout << string_visitor.result << std::endl;

  */


  ///////
  /*


  mcmas::SwarmAgent env;
  env.name = "Environment";
  env.add_actions({"flip", "keep"});
  env.add_variable("dummy", mcmas::BOOL());
  env.add_init_condition(Expression::Eq(Expression::Id("dummy"), Expression::Bool("true")));
  env.add_protocol_line(Expression::Bool(true), {"flip", "keep"});
  env.add_evolution_line(Expression::Eq(Expression::Id("dummy"), Expression::Bool(true)), Expression::Bool(true));

  mcmas::SwarmAgent agent;
  agent.name = "Agent";
  agent.add_actions({"flip", "keep"});
  agent.add_variable("bit", mcmas::BOOL());
  agent.add_init_condition(Expression::Bool(true));
  agent.add_protocol_line(Expression::Bool(true), {"flip", "keep"});
  agent.add_evolution_line(Expression::Eq(Expression::Id("bit"), Expression::Not(Expression::Id("bit"))), 
                         Expression::And(
                           Expression::Eq(
                             Expression::Id("Environment", "Action"), 
                             Expression::Id("flip")
                           ), 
                           Expression::Not(
                             Expression::Eq(
                               Expression::Id("GlobalAction"), 
                               Expression::Id("keep")
                             )
                           )
                         )
                        );

  agent.add_evolution_line(Expression::Eq(Expression::Id("bit"), Expression::Id("bit")), 
                         Expression::And(
                           Expression::Eq(
                             Expression::Id("Environment", "Action"), 
                             Expression::Id("keep")
                           ), 
                           Expression::Not(
                             Expression::Eq(
                               Expression::Id("GlobalAction"), 
                               Expression::Id("flip")
                             )
                           )
                         )
                        );

  mcmas::Evaluation evaluation;
  evaluation.lines.emplace_back(mcmas::EvaluationLine("bittrue", Expression::Eq(Expression::Id("Agent", "bit"), Expression::Bool(true))));
  */

  auto true_expr = Expression::Eq(Expression::Int(1), Expression::Int(1));

  mcmas::SwarmAgent env;
  env.name = "Environment";
  env.add_actions({"go"});
  env.add_variable("dummy", mcmas::BOOL());
  env.add_init_condition(Expression::Eq(Expression::Id("dummy"), Expression::Bool("true")));
  env.add_protocol_line(Expression::Eq(Expression::Id("dummy"), Expression::Id("dummy")), {"go"});

  mcmas::SwarmAgent agent;
  agent.name = "Robot";
  agent.add_actions({"go", "stay"});
  agent.add_variable("pos", mcmas::RANGED_INT(1, 5));
  agent.add_init_condition(Expression::Eq(Expression::Id("pos"), Expression::Int(1)));
  agent.add_protocol_line(Expression::Eq(Expression::Id("pos"), Expression::Id("pos")), {"go, stay"});
  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Add(Expression::Id("pos"), Expression::Int(1))), 
                         Expression::And(
                           Expression::Eq(
                             Expression::Id("Environment", "Action"), 
                             Expression::Id("go")
                           ), 
                           Expression::And(
                             Expression::Eq(
                               Expression::Id("GlobalAction"), 
                               Expression::Id("go")
                             ),
                             Expression::Lt(
                               Expression::Id("pos"),
                               Expression::Int(5)
                             )
                           )
                         )
                        );

  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(5)), 
                           Expression::Eq(Expression::Id("pos"), Expression::Int(5))
                        );

  mcmas::Evaluation evaluation;
  evaluation.lines.emplace_back(mcmas::EvaluationLine("ended", Expression::Eq(Expression::Id("Robot", "pos"), Expression::Int(5))));

  std::vector<mcmas::IndexedFormula> formulas;
  std::vector<std::string> placeholders{"X"};
  formulas.emplace_back(placeholders, Formula::AF(Formula::AG(Formula::Atom("X", "ended"))));
  mcmas::SwarmSystem ss{env, agent, 3, evaluation, std::move(formulas)};

  std::cout << ss.to_string() << std::endl;

}