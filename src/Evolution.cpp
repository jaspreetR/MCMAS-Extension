#include "Evolution.hpp"
#include <string>
#include "utils/Misc.hpp"
#include "visitors/LocalActionVisitor.hpp"
#include "visitors/GlobalActionVisitor.hpp"

namespace mcmas {


  void Evolution::apply_local_action_transform(int max_x, int max_y, int comm_distance) {
    std::vector<EvolutionLine> new_lines;
    for (const auto& line : lines) {
      for (int i = 1; i <= max_x; ++i) {
        for (int j = 1; j <= max_y; ++j) {
          LocalActionVisitor visitor(i, j, max_x, max_y, comm_distance);
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

  void Evolution::apply_global_action_transform(GlobalActionVisitor& visitor) {
    std::vector<EvolutionLine> new_lines;
    for (const auto& line : lines) {
      line.condition->accept(visitor);
      new_lines.emplace_back(line.result->clone(), std::move(visitor.result));
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

  Evolution Evolution::clone() const {
    std::vector<EvolutionLine> new_lines;
    new_lines.reserve(lines.size());

    for (const auto& line : lines) {
      new_lines.emplace_back(line.clone());
    }

    Evolution result;
    result.lines = std::move(new_lines);
    return result;
  }

}