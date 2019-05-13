#ifndef MCMAS_SWARMSYSTEM_HPP
#define MCMAS_SWARMSYSTEM_HPP
#include <vector>
#include "AbstractAgent.hpp"
#include "Evaluation.hpp"
#include "expressions/Expression.hpp"
#include "SwarmAgent.hpp"

namespace mcmas {

  class SwarmSystem {
    public:
      SwarmAgent environment;
      std::vector<SwarmAgent> concrete_agents;
      std::vector<AbstractAgent> abstract_agents;

      Expression::Ptr init_states;
      Evaluation evaluation;

      SwarmSystem(const SwarmAgent& enviroment, const SwarmAgent& agent, int num_agents, const Evaluation& evaluation);

      std::string to_string() const;

  };
}

#endif
