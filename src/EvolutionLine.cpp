#include "EvolutionLine.hpp"
#include <iostream>

namespace mcmas {

  // TODO: i dont think this should be needed since this does not need to copied afaik
  EvolutionLine::EvolutionLine(const EvolutionLine& other) {
    auto line = other.clone();
    result = std::move(line.result);
    condition = std::move(line.condition);
  }

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