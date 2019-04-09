#include "Evolution.hpp"
#include <string>
#include "utils/Misc.hpp"
#include "visitors/LocalActionVisitor.hpp"

namespace mcmas {


  void Evolution::apply_local_action_transform(const std::vector<std::string>& agent_names, 
                                               int max_x, int max_y, int comm_distance) {
    std::vector<EvolutionLine> new_lines;
    for (const auto& line : lines) {
      for (int i = 1; i <= max_x; ++i) {
        for (int j = 1; j <= max_y; ++j) {
          LocalActionVisitor visitor(i, j, max_x, max_y, comm_distance, agent_names);
          line.condition->accept(visitor);
          auto new_condition = Expression::And(
                                 Expression::Eq(Expression::Id("i"), Expression::Int(i)),
                                 Expression::Eq(Expression::Id("j"), Expression::Int(j))
                               );
          new_condition = Expression::And(std::move(new_condition), std::move(visitor.result));
          new_lines.emplace_back(line.result->clone(), std::move(new_condition));
        }
      } 
    }
    
    lines = std::move(new_lines);
  }


  std::string Evolution::to_string() const {
    std::string evolution_string = "Evolution : \n";
    for (auto& line : lines) {
      evolution_string += line.to_string();
    }
    evolution_string += "end Evolution \n";

    return evolution_string;
  }

}