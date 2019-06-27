#ifndef MCMAS_FORMULATDVISITOR_HPP
#define MCMAS_FORMULATDVISITOR_HPP
#include <algorithm>
#include "FormulaVisitor.hpp"

namespace mcmas {

  class FormulaTDVisitor : public ConstFormulaVisitor {
    public:
      int result = 0;

      void visit(const formulas::And& formula) {
        formula.left->accept(*this);
        auto left_result = result;

        formula.right->accept(*this);
        auto right_result = result;

        result = std::max(left_result, right_result);
      }

      void visit(const formulas::Or& formula) {
        formula.left->accept(*this);
        auto left_result = result;

        formula.right->accept(*this);
        auto right_result = result;

        result = std::max(left_result, right_result);
      }

      void visit(const formulas::Not& formula) {
        formula.child->accept(*this);
      }

      void visit(const formulas::Arrow& formula) {
        formula.left->accept(*this);
        auto left_result = result;

        formula.right->accept(*this);
        auto right_result = result;

        result = std::max(left_result, right_result);
      }

      void visit(const formulas::F& formula) {
        formula.child->accept(*this);
        auto child_result = result;

        result = child_result + 1;
      }

      void visit(const formulas::G& formula) {
        formula.child->accept(*this);
        auto child_result = result;

        result = child_result + 1;
      }

      void visit(const formulas::X& formula) {
        formula.child->accept(*this);
        auto child_result = result;

        result = child_result + 1;
      }

      void visit(const formulas::U& formula) {
        formula.left->accept(*this);
        auto left_result = result;

        formula.right->accept(*this);
        auto right_result = result;

        result = std::max(left_result, right_result) + 1;
      }

      void visit(const formulas::K& formula) {
        formula.child->accept(*this);
      }

      void visit(const formulas::Atom& formula) {
        result = 0;
      }

  };

}

#endif