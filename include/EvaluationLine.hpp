#ifndef MCMAS_EVALUATIONLINE_HPP
#define MCMAS_EVALUATIONLINE_HPP
#include <string>
#include "expressions/Expression.hpp"

namespace mcmas {

  class EvaluationLine {
    public:
      std::string name;
      Expression::Ptr condition; 

      EvaluationLine(const std::string& name, Expression::Ptr&& condition);

      EvaluationLine(const EvaluationLine& other);
      EvaluationLine& operator=(const EvaluationLine& other);

      std::string to_string() const;

      EvaluationLine clone() const;
  };

}

#endif