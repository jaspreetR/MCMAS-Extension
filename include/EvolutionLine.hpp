#ifndef MCMAS_EVOLUTIONLINE_HPP
#define MCMAS_EVOLUTIONLINE_HPP
#include "expressions/Expression.hpp"

namespace mcmas {

  class EvolutionLine {
    public:
      Expression::Ptr result;
      Expression::Ptr condition;

      EvolutionLine(Expression::Ptr&& result, Expression::Ptr&& condition) 
      : result(std::move(result)),
        condition(std::move(condition))
      {}
  };

}

#endif