#include "formulas/IndexedFormula.hpp"
#include <map>
#include <cassert>
#include "SwarmAgent.hpp"
#include "visitors/FormulaOwnerReplaceVisitor.hpp"

namespace mcmas {

  void IndexedFormula::insert_agent_names(const std::vector<SwarmAgent>& agents) {
    assert(placeholders.size() <= agents.size());

    std::map<std::string, std::string> replacements;

    for (size_t i = 0; i < placeholders.size(); ++i) {
      auto& placeholder = placeholders[i];
      auto& agent = agents[i];
      replacements[placeholder] = agent.name;
    }

    FormulaOwnerReplaceVisitor visitor(replacements);
    formula->accept(visitor);
  }

}