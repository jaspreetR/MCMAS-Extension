#include <string>
#include <iostream>
#include <fstream>

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
#include "parser/parser.hpp"

using mcmas::Expression;
using mcmas::Formula;

int main(int argc, char** argv) {

  mcmas::SwarmAgent env;
  env.name = "Environment";
  env.add_actions({"go"});
  env.add_variable("dummy", mcmas::BOOL());
  env.add_init_condition(Expression::Eq(Expression::Id("dummy"), Expression::Bool("true")));
  env.add_protocol_line(Expression::Eq(Expression::Id("dummy"), Expression::Id("dummy")), {"go"});

  mcmas::SwarmAgent agent;
  agent.name = "Robot";
  agent.add_actions({"go", "exit", "stop"});
  agent.add_variable("pos", mcmas::RANGED_INT(1, 3));
  agent.add_init_condition(Expression::Eq(Expression::Id("pos"), Expression::Int(1)));
  agent.add_protocol_line(Expression::Eq(Expression::Id("pos"), Expression::Int(1)), {"exit", "go"});
  agent.add_protocol_line(Expression::Eq(Expression::Id("pos"), Expression::Int(2)), {"go"});
  agent.add_protocol_line(Expression::Eq(Expression::Id("pos"), Expression::Int(3)), {"stop"});

  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(2)), 
                           Expression::And(Expression::Eq(Expression::Id("GlobalAction"), Expression::Id("exit")),
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("go")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(1)))));

  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(1)), 
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("go")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(2))));

  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(3)), 
                           Expression::Or(
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("stop")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(3))),
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("exit")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(1)))));

  mcmas::Evaluation evaluation;
  //evaluation.lines.emplace_back(mcmas::EvaluationLine("at3", Expression::Eq(Expression::Id("Robot", "pos"), Expression::Int(3))));
  std::vector<mcmas::IndexedFormula> formulas;
  std::vector<std::string> placeholders{"X", "Y"};
  //formulas.emplace_back(placeholders, Formula::EF(Formula::And(Formula::Atom("X", "at3"), Formula::Atom("Y", "at3"))));

  ////////////////////////////////////////////////////////////////////////////

 /* 
  mcmas::SwarmAgent env;
  env.name = "Environment";
  env.add_actions({"go"});
  env.add_variable("dummy", mcmas::BOOL());
  env.add_init_condition(Expression::Eq(Expression::Id("dummy"), Expression::Bool("true")));
  env.add_protocol_line(Expression::Eq(Expression::Id("dummy"), Expression::Id("dummy")), {"go"});

  mcmas::SwarmAgent agent;
  agent.name = "Robot";
  agent.add_actions({"go_left", "go_right", "stop"});
  agent.add_variable("pos", mcmas::RANGED_INT(1, 7));
  agent.add_init_condition(Expression::Eq(Expression::Id("pos"), Expression::Int(1)));
  agent.add_protocol_line(Expression::Leq(Expression::Id("pos"), Expression::Int(3)), {"go_left", "go_right"});
  agent.add_protocol_line(Expression::Gt(Expression::Id("pos"), Expression::Int(3)), {"stop"});
  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(2)), 
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("go_left")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(1))));
  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(3)), 
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("go_right")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(1))));
  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(4)), 
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("go_left")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(2))));
  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(5)), 
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("go_right")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(2))));
  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(6)), 
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("go_left")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(3))));
  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Int(7)), 
                           Expression::And(Expression::Eq(Expression::Id("Action"), Expression::Id("go_right")),
                                           Expression::Eq(Expression::Id("pos"), Expression::Int(3))));
  agent.add_evolution_line(Expression::Eq(Expression::Id("pos"), Expression::Id("pos")), 
                           Expression::Eq(Expression::Id("Action"), Expression::Id("stop")));
  
  mcmas::Evaluation evaluation;
  evaluation.lines.emplace_back(mcmas::EvaluationLine("at7", Expression::Eq(Expression::Id("Robot", "pos"), Expression::Int(7))));
  std::vector<mcmas::IndexedFormula> formulas;
  std::vector<std::string> placeholders{"X", "Y"};
  formulas.emplace_back(placeholders, Formula::EF(Formula::And(Formula::Atom("X", "at7"), Formula::Atom("Y", "at7"))));
  */
  
 //////////////////////////////////////////////////////////////////////////////

/*
  mcmas::SwarmAgent env;
  env.name = "Environment";
  env.add_actions({"go"});
  env.add_variable("dummy", mcmas::BOOL());
  env.add_init_condition(Expression::Eq(Expression::Id("dummy"), Expression::Bool("true")));
  env.add_protocol_line(Expression::Eq(Expression::Id("dummy"), Expression::Id("dummy")), {"go"});

  mcmas::SwarmAgent agent;
  agent.name = "Robot";
  agent.add_actions({"go_plus", "go", "go_minus", "halt", "nothing"});
  agent.add_variable("pos", mcmas::RANGED_INT(1, 4));
  agent.add_variable("sensor_pos", mcmas::RANGED_INT(1, 4));
  agent.add_variable("stopped", mcmas::BOOL());
  agent.add_init_condition(Expression::And(
                             Expression::Eq(Expression::Id("pos"), Expression::Int(1)),
                             Expression::And(
                               Expression::Eq(Expression::Id("sensor_pos"), Expression::Int(1)),
                               Expression::Eq(Expression::Id("stopped"), Expression::Bool(false))
                             )
                          ));
  agent.add_protocol_line(Expression::And(
                            Expression::Lt(Expression::Id("sensor_pos"), Expression::Int(3)), 
                            Expression::Eq(Expression::Id("stopped"), Expression::Bool(false))
                          ), 
                          {"go", "go_plus", "go_minus"});

  agent.add_protocol_line(Expression::And(
                            Expression::Geq(Expression::Id("sensor_pos"), Expression::Int(3)), 
                            Expression::Eq(Expression::Id("stopped"), Expression::Bool(false))
                          ), 
                          {"halt"});
  agent.add_protocol_line(Expression::Eq(Expression::Id("stopped"), Expression::Bool(true)), {"nothing"});
  agent.add_evolution_line(Expression::And(
                             Expression::Eq(Expression::Id("stopped"), Expression::Bool(false)),
                           Expression::And(
                             Expression::Eq(Expression::Id("pos"), Expression::Add(Expression::Id("pos"), Expression::Int(1))), 
                             Expression::Eq(Expression::Id("sensor_pos"), Expression::Add(Expression::Id("pos"), Expression::Int(0))) 
                           )),
                           Expression::And(
                             Expression::Eq(Expression::Id("Action"), Expression::Id("go_minus")),
                             Expression::Not(Expression::Eq(Expression::Id("GlobalAction"), Expression::Id("halt")))
                             //Expression::Not(Expression::Eq(Expression::Id("Action"), Expression::Id("halt")))
                           ));

  agent.add_evolution_line(Expression::And(
                             Expression::Eq(Expression::Id("stopped"), Expression::Bool(false)),
                           Expression::And(
                             Expression::Eq(Expression::Id("pos"), Expression::Add(Expression::Id("pos"), Expression::Int(1))), 
                             Expression::Eq(Expression::Id("sensor_pos"), Expression::Add(Expression::Id("pos"), Expression::Int(1))) 
                           )),
                           Expression::And(
                             Expression::Eq(Expression::Id("Action"), Expression::Id("go")),
                             Expression::Not(Expression::Eq(Expression::Id("GlobalAction"), Expression::Id("halt")))
                             //Expression::Not(Expression::Eq(Expression::Id("Action"), Expression::Id("halt")))
                           ));

  agent.add_evolution_line(Expression::And(
                             Expression::Eq(Expression::Id("stopped"), Expression::Bool(false)),
                           Expression::And(
                             Expression::Eq(Expression::Id("pos"), Expression::Add(Expression::Id("pos"), Expression::Int(1))), 
                             Expression::Eq(Expression::Id("sensor_pos"), Expression::Add(Expression::Id("pos"), Expression::Int(2))) 
                           )),
                           Expression::And(
                             Expression::Eq(Expression::Id("Action"), Expression::Id("go_plus")),
                             Expression::Not(Expression::Eq(Expression::Id("GlobalAction"), Expression::Id("halt")))
                             //Expression::Not(Expression::Eq(Expression::Id("Action"), Expression::Id("halt")))
                           ));

  agent.add_evolution_line(Expression::Eq(Expression::Id("stopped"), Expression::Bool(true)),
                           Expression::Or(
                             Expression::Eq(Expression::Id("GlobalAction"), Expression::Id("halt")),
                             //Expression::Eq(Expression::Id("Action"), Expression::Id("halt")),
                             Expression::Eq(Expression::Id("Action"), Expression::Id("nothing"))
                           ));

  mcmas::Evaluation evaluation;
  evaluation.lines.emplace_back(mcmas::EvaluationLine("halted", Expression::Eq(Expression::Id("Robot", "stopped"), Expression::Bool(true))));
  evaluation.lines.emplace_back(mcmas::EvaluationLine("pos1", Expression::Eq(Expression::Id("Robot", "sensor_pos"), Expression::Int(1))));
  evaluation.lines.emplace_back(mcmas::EvaluationLine("pos2", Expression::Eq(Expression::Id("Robot", "sensor_pos"), Expression::Int(2))));
  evaluation.lines.emplace_back(mcmas::EvaluationLine("pos3", Expression::Eq(Expression::Id("Robot", "sensor_pos"), Expression::Int(3))));
  evaluation.lines.emplace_back(mcmas::EvaluationLine("pos4", Expression::Eq(Expression::Id("Robot", "sensor_pos"), Expression::Int(4))));

  std::vector<mcmas::IndexedFormula> formulas;
  std::vector<std::string> placeholders{"X", "Y"};

  formulas.emplace_back(placeholders, Formula::EF(Formula::And(Formula::AG(Formula::Atom("X", "pos1")), Formula::AG(Formula::Atom("Y", "pos1")))));
  formulas.emplace_back(placeholders, Formula::EF(Formula::And(Formula::AG(Formula::Atom("X", "pos2")), Formula::AG(Formula::Atom("Y", "pos2")))));
  formulas.emplace_back(placeholders, Formula::EF(Formula::And(Formula::AG(Formula::Atom("X", "pos3")), Formula::AG(Formula::Atom("Y", "pos3")))));
  formulas.emplace_back(placeholders, Formula::EF(Formula::And(Formula::AG(Formula::Atom("X", "pos4")), Formula::AG(Formula::Atom("Y", "pos4")))));

  formulas.emplace_back(placeholders, Formula::AG(
                                        Formula::Arrow(
                                          Formula::Atom("X", "halted"), 
                                          Formula::K("X", Formula::AX(Formula::AX(Formula::Atom("Y", "halted"))))
                                        )
                                      ));

  formulas.emplace_back(placeholders, Formula::AG(
                                        Formula::Arrow(
                                          Formula::Atom("X", "halted"), 
                                          Formula::K("X", Formula::Atom("Y", "halted"))
                                        )
                                      ));

  formulas.emplace_back(placeholders, Formula::AG(
                                        Formula::Arrow(
                                          Formula::Atom("X", "halted"), 
                                          Formula::K("X", Formula::AX(Formula::Atom("Y", "halted")))
                                        )
                                      ));

  formulas.emplace_back(placeholders, Formula::AG(
                                        Formula::Arrow(
                                          Formula::Atom("X", "halted"), 
                                          Formula::K("X", Formula::AX(Formula::AX(Formula::AX(Formula::Atom("Y", "halted")))))
                                        )
                                      ));
*/
  mcmas::SwarmSystem ss{env, agent, 0, evaluation, std::move(formulas)};
  

  /*
  std::string file_name = "test60.ispl";
  std::ofstream fs; 
  fs.open(file_name);
  ss.print(fs);
  fs.close();
  */

  //mcmas::parser::do_parse();
  //std::cout << ss.to_string() << std::endl;

}