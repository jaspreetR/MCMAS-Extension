#include "EvolutionLine.hpp"

namespace mcmas {

  std::string EvolutionLine::to_string() const {
    std::string result_string = result->to_string();
    std::string condition_string = condition->to_string();

    return result_string + " if " + condition_string + ";\n";
  }

  EvolutionLine EvolutionLine::clone() const {
    auto line = EvolutionLine(result->clone(), condition->clone());
    return line;
  }

}