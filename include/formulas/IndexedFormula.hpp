#ifndef MCMAS_INDEXEDFORMULA_HPP
#define MCMAS_INDEXEDFORMULA_HPP
#include <string>
#include <vector>
#include "Formula.hpp"

namespace mcmas {

  class SwarmAgent;

  class IndexedFormula {
    public:
      std::vector<std::string> placeholders;
      Formula::Ptr formula;

      IndexedFormula(const std::vector<std::string>& placeholders, Formula::Ptr&& formula)
      : placeholders(placeholders),
        formula(std::move(formula))
      {
      }

      void insert_agent_names(const std::vector<SwarmAgent>& agents);
  };

}

#endif
