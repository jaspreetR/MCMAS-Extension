#include "EvaluationLine.hpp"

namespace mcmas {

  EvaluationLine::EvaluationLine(const std::string& name, Expression::Ptr&& condition) {
    this->name = name;
    this->condition = std::move(condition);
  }

  EvaluationLine::EvaluationLine(const EvaluationLine& other) {
    auto line = other.clone();
    name = std::move(line.name); 
    condition = std::move(line.condition); 
  }

  EvaluationLine& EvaluationLine::operator=(const EvaluationLine& other) {
    auto line = other.clone();
    name = std::move(line.name); 
    condition = std::move(line.condition); 

    return *this;
  }

  std::string EvaluationLine::to_string() const {
    return name + " if " + condition->to_string();
  }

  EvaluationLine EvaluationLine::clone() const {
    return EvaluationLine(name, condition->clone());
  }

}