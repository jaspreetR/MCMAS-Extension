#ifndef MCMAS_SWARMSYSTEM_HPP
#define MCMAS_SWARMSYSTEM_HPP
#include <vector>
#include <fstream>
#include "AbstractAgent.hpp"
#include "Evaluation.hpp"
#include "expressions/Expression.hpp"
#include "SwarmAgent.hpp"
#include "formulas/IndexedFormula.hpp"

namespace mcmas {

  class SwarmSystem {
    public:
      SwarmAgent environment;
      std::vector<SwarmAgent> concrete_agents;
      std::vector<AbstractAgent> abstract_agents;

      Expression::Ptr init_states;
      Evaluation evaluation;
      std::vector<IndexedFormula> formulas;

      SwarmSystem(const SwarmAgent& enviroment, 
                  const SwarmAgent& agent, 
                  int num_agents, 
                  const Evaluation& evaluation,
                  std::vector<IndexedFormula>&& formulas,
                  bool is_abstract = false, bool has_meta = false);

      std::string to_string() const;
      void print(std::ofstream& fs) const;

  };
}

#endif
