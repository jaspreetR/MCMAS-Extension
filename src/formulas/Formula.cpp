#include "formulas/Formula.hpp"
#include "visitors/FormulaVisitor.hpp"
#include "visitors/FormulaStringVisitor.hpp"

namespace mcmas {

  std::string Formula::to_string() const {
    auto visitor = FormulaStringVisitor();
    this->accept(visitor);
    return std::move(visitor.result);
  }

  Formula::Ptr Formula::And(Formula::Ptr&& left, Formula::Ptr&& right) {
    return Formula::Ptr(new formulas::And(std::move(left), std::move(right)));
  }

  Formula::Ptr Formula::Or(Formula::Ptr&& left, Formula::Ptr&& right) {
    return Formula::Ptr(new formulas::Or(std::move(left), std::move(right)));
  }

  Formula::Ptr Formula::Arrow(Formula::Ptr&& left, Formula::Ptr&& right) {
    return Formula::Ptr(new formulas::Arrow(std::move(left), std::move(right)));
  }

  Formula::Ptr Formula::Not(Formula::Ptr&& child) {
    return Formula::Ptr(new formulas::Not(std::move(child)));
  }

  Formula::Ptr Formula::AG(Formula::Ptr&& child) {
    return Formula::Ptr(new formulas::G(std::move(child), formulas::Quantifier::A));
  }

  Formula::Ptr Formula::EG(Formula::Ptr&& child) {
    return Formula::Ptr(new formulas::G(std::move(child), formulas::Quantifier::E));
  }

  Formula::Ptr Formula::AF(Formula::Ptr&& child) {
    return Formula::Ptr(new formulas::F(std::move(child), formulas::Quantifier::A));
  }

  Formula::Ptr Formula::EF(Formula::Ptr&& child) {
    return Formula::Ptr(new formulas::F(std::move(child), formulas::Quantifier::E));
  }

  Formula::Ptr Formula::AX(Formula::Ptr&& child) {
    return Formula::Ptr(new formulas::X(std::move(child), formulas::Quantifier::A));
  }

  Formula::Ptr Formula::EX(Formula::Ptr&& child) {
    return Formula::Ptr(new formulas::X(std::move(child), formulas::Quantifier::E));
  }

  Formula::Ptr Formula::AU(Formula::Ptr&& left, Formula::Ptr&& right) {
    return Formula::Ptr(new formulas::U(std::move(left), std::move(right), formulas::Quantifier::A));
  }

  Formula::Ptr Formula::EU(Formula::Ptr&& left, Formula::Ptr&& right) {
    return Formula::Ptr(new formulas::U(std::move(left), std::move(right), formulas::Quantifier::E));
  }

  Formula::Ptr Formula::K(const std::string& agent_name, Formula::Ptr&& child) {
    return Formula::Ptr(new formulas::K(agent_name, std::move(child)));
  }

  Formula::Ptr Formula::Atom(const std::string& atom_name) {
    return Formula::Ptr(new formulas::Atom(atom_name));
  }

  Formula::Ptr Formula::Atom(const std::string& owner, const std::string& atom_name) {
    return Formula::Ptr(new formulas::Atom(owner, atom_name));
  }

  void formulas::G::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::G::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::G::clone() const {
    return Formula::Ptr(new formulas::G(child->clone(), quantifier));
  }

  void formulas::F::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::F::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::F::clone() const {
    return Formula::Ptr(new formulas::F(child->clone(), quantifier));
  }

  void formulas::X::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::X::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::X::clone() const {
    return Formula::Ptr(new formulas::X(child->clone(), quantifier));
  }

  void formulas::U::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::U::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::U::clone() const {
    return Formula::Ptr(new formulas::U(left->clone(), right->clone(), quantifier));
  }

  void formulas::K::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::K::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::K::clone() const {
    return Formula::Ptr(new formulas::K(agent_name, child->clone()));
  }

  void formulas::And::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::And::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::And::clone() const {
    return Formula::Ptr(new formulas::And(left->clone(), right->clone()));
  }

  void formulas::Or::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::Or::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::Or::clone() const {
    return Formula::Ptr(new formulas::Or(left->clone(), right->clone()));
  }

  void formulas::Arrow::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::Arrow::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::Arrow::clone() const {
    return Formula::Ptr(new formulas::Arrow(left->clone(), right->clone()));
  }

  void formulas::Not::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::Not::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::Not::clone() const {
    return Formula::Ptr(new formulas::Not(child->clone()));
  }

  void formulas::Atom::accept(FormulaVisitor& visitor) {
    visitor.visit(*this);
  }

  void formulas::Atom::accept(ConstFormulaVisitor& visitor) const {
    visitor.visit(*this);
  }

  Formula::Ptr formulas::Atom::clone() const {
    return Formula::Ptr(new formulas::Atom(atom_name));
  }
}