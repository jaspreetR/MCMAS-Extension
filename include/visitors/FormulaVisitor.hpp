#ifndef MCMAS_FORMULAVISITOR_HPP
#define MCMAS_FORMULAVISITOR_HPP
#include "formulas/Formula.hpp"

namespace mcmas {

  class FormulaVisitor {
    public:
      virtual void visit(formulas::And& formula);
      virtual void visit(formulas::Or& formula);
      virtual void visit(formulas::Not& formula);
      virtual void visit(formulas::Arrow& formula);
      virtual void visit(formulas::F& formula);
      virtual void visit(formulas::G& formula);
      virtual void visit(formulas::X& formula);
      virtual void visit(formulas::U& formula);
      virtual void visit(formulas::K& formula);
      virtual void visit(formulas::Atom& formula);
  };

  class ConstFormulaVisitor {
    public:
      virtual void visit(const formulas::And& formula);
      virtual void visit(const formulas::Or& formula);
      virtual void visit(const formulas::Not& formula);
      virtual void visit(const formulas::Arrow& formula);
      virtual void visit(const formulas::F& formula);
      virtual void visit(const formulas::G& formula);
      virtual void visit(const formulas::X& formula);
      virtual void visit(const formulas::U& formula);
      virtual void visit(const formulas::K& formula);
      virtual void visit(const formulas::Atom& formula);
  };
}

#endif