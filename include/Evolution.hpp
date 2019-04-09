#ifndef MCMAS_EVOLUTION_HPP
#define MCMAS_EVOLUTION_HPP
#include <vector>
#include "EvolutionLine.hpp"

namespace mcmas {
  class Evolution {
    public:
      std::vector<EvolutionLine> lines;

      void apply_local_action_transform(const std::vector<std::string>& agent_names, 
                                        int max_x, int max_y, int comm_distance);
      
      std::string to_string() const;
  };
}

#endif