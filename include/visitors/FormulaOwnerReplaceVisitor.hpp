#ifndef MCMAS_FORMULAOWNERREPLACEVISITOR_HPP
#define MCMAS_FORMULAOWNERREPLACEVISITOR_HPP
#include <map>
#include <string>
#include "formulas/Formula.hpp"
#include "visitors/FormulaVisitor.hpp"

namespace mcmas {

  class FormulaOwnerReplaceVisitor : public FormulaVisitor {
    public:
      const std::map<std::string, std::string>& replacements;

      FormulaOwnerReplaceVisitor(const std::map<std::string, std::string>& replacements) 
      : replacements(replacements)
      {
      }

      void visit(formulas::K& formula) {
        formula.agent_name = replacements.at(formula.agent_name);

        formula.child->accept(*this);
      } 

      void visit(formulas::Atom& formula) {
        formula.owner = replacements.at(formula.owner);
      }
  };

}

#endif