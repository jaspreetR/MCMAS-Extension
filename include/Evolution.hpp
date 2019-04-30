#ifndef MCMAS_EVOLUTION_HPP
#define MCMAS_EVOLUTION_HPP
#include <vector>
#include "EvolutionLine.hpp"

namespace mcmas {
  class GlobalActionVisitor;

  class Evolution {
    public:
      std::vector<EvolutionLine> lines;

      void apply_local_action_transform(int max_x, int max_y, int comm_distance);
      void apply_global_action_transform(GlobalActionVisitor& visitor);
      
      std::string to_string() const;

      Evolution clone() const;
  };
}

#endif