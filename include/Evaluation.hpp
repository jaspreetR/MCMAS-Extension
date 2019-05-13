#ifndef MCMAS_EVALUATION_HPP
#define MCMAS_EVALUATION_HPP
#include <vector>
#include <string>
#include "EvaluationLine.hpp"

namespace mcmas {

  class Evaluation {
    public:
      std::vector<EvaluationLine> lines;

      std::string to_string() const;

      Evaluation clone() const;

  };

}

#endif