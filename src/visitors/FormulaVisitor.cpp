#include "visitors/FormulaVisitor.hpp"

namespace mcmas {

  void FormulaVisitor::visit(formulas::And& formula) {
    formula.left->accept(*this);
    formula.right->accept(*this);
  }

  void FormulaVisitor::visit(formulas::Or& formula) {
    formula.left->accept(*this);
    formula.right->accept(*this);
  }

  void FormulaVisitor::visit(formulas::Arrow& formula) {
    formula.left->accept(*this);
    formula.right->accept(*this);
  }

  void FormulaVisitor::visit(formulas::Not& formula) {
    formula.child->accept(*this);
  }

  void FormulaVisitor::visit(formulas::F& formula) {
    formula.child->accept(*this);
  }

  void FormulaVisitor::visit(formulas::G& formula) {
    formula.child->accept(*this);
  }

  void FormulaVisitor::visit(formulas::X& formula) {
    formula.child->accept(*this);
  }

  void FormulaVisitor::visit(formulas::U& formula) {
    formula.left->accept(*this);
    formula.right->accept(*this);
  }

  void FormulaVisitor::visit(formulas::K& formula) {
    formula.child->accept(*this);
  }

  void FormulaVisitor::visit(formulas::Atom& formula) {
  }

  void ConstFormulaVisitor::visit(const formulas::And& formula) {
    formula.left->accept(*this);
    formula.right->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::Or& formula) {
    formula.left->accept(*this);
    formula.right->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::Arrow& formula) {
    formula.left->accept(*this);
    formula.right->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::Not& formula) {
    formula.child->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::F& formula) {
    formula.child->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::G& formula) {
    formula.child->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::X& formula) {
    formula.child->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::U& formula) {
    formula.left->accept(*this);
    formula.right->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::K& formula) {
    formula.child->accept(*this);
  }

  void ConstFormulaVisitor::visit(const formulas::Atom& formula) {
  }
}