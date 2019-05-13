#include "EvaluationLine.hpp"

namespace mcmas {

  EvaluationLine::EvaluationLine(const std::string& name, Expression::Ptr&& condition) {
    this->name = name;
    this->condition = std::move(condition);
  }

  std::string EvaluationLine::to_string() const {
    return name + " if " + condition->to_string();
  }

  EvaluationLine EvaluationLine::clone() const {
    return EvaluationLine(name, condition->clone());
  }

}