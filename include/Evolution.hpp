#ifndef MCMAS_EVOLUTION_HPP
#define MCMAS_EVOLUTION_HPP
#include <vector>
#include "EvolutionLine.hpp"

namespace mcmas {
  class Evolution {
    public:
      std::vector<EvolutionLine> lines;

      std::string to_string() const;
  };
}

#endif