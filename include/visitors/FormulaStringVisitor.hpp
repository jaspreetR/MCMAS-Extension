#ifndef MCMAS_FORMULASTRINGVISITOR_HPP
#define MCMAS_FORMULASTRINGVISITOR_HPP
#include <string>
#include "utils/Misc.hpp"
#include "FormulaVisitor.hpp"

namespace mcmas {

  class FormulaStringVisitor : public ConstFormulaVisitor {
    public:
      std::string result;

      void visit(const formulas::And& formula) {
        formula.left->accept(*this);
        auto left_result = result;

        formula.right->accept(*this);
        auto right_result = result;

        result = "(" + left_result + " and " + right_result + ")";
      }

      void visit(const formulas::Or& formula) {
        formula.left->accept(*this);
        auto left_result = result;

        formula.right->accept(*this);
        auto right_result = result;

        result = "(" + left_result + " or " + right_result + ")";
      }

      void visit(const formulas::Not& formula) {
        formula.child->accept(*this);
        auto child_result = result;

        result = "(!" + child_result + ")";
      }

      void visit(const formulas::Arrow& formula) {
        formula.left->accept(*this);
        auto left_result = result;

        formula.right->accept(*this);
        auto right_result = result;

        result = "(" + left_result + " -> " + right_result + ")";
      }

      void visit(const formulas::F& formula) {
        formula.child->accept(*this);
        auto child_result = result;

        result = "(" + quantifier_to_string(formula.quantifier) + "F " + child_result + ")";
      }

      void visit(const formulas::G& formula) {
        formula.child->accept(*this);
        auto child_result = result;

        result = "(" + quantifier_to_string(formula.quantifier) + "G " + child_result + ")";
      }

      void visit(const formulas::X& formula) {
        formula.child->accept(*this);
        auto child_result = result;

        result = "(" + quantifier_to_string(formula.quantifier) + "X " + child_result + ")";
      }

      void visit(const formulas::U& formula) {
        formula.left->accept(*this);
        auto left_result = result;

        formula.right->accept(*this);
        auto right_result = result;

        result = "(" + quantifier_to_string(formula.quantifier) + "(" + left_result + "U" + right_result + "))";
      }

      void visit(const formulas::K& formula) {
        formula.child->accept(*this);
        auto child_result = result;

        result = "(K(" + formula.agent_name + ", " + child_result + "))";
      }

      void visit(const formulas::Atom& formula) {
        result = formula.owner == "" ? formula.atom_name : formula.atom_name + "__" + formula.owner;
      }
    };

}

#endif