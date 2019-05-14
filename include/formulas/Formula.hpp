#ifndef MCMAS_FORMULA_HPP
#define MCMAS_FORMULA_HPP
#include <memory>
#include <string>

namespace mcmas {

  class FormulaVisitor;
  class ConstFormulaVisitor;

  class Formula {
    public:
      using Ptr = std::unique_ptr<Formula>;

      virtual void accept(FormulaVisitor& visitor) = 0;
      virtual void accept(ConstFormulaVisitor& visitor) const = 0;

      virtual Ptr clone() const = 0;

      std::string to_string() const;

      static Ptr And(Ptr&& left, Ptr&& right);
      static Ptr Or(Ptr&& left, Ptr&& right);
      static Ptr Not(Ptr&& child);
      static Ptr Arrow(Ptr&& left, Ptr&& right);

      static Ptr AG(Ptr&& child);   
      static Ptr EG(Ptr&& child);   
      static Ptr AF(Ptr&& child);   
      static Ptr EF(Ptr&& child);   
      static Ptr AX(Ptr&& child);   
      static Ptr EX(Ptr&& child);   
      static Ptr AU(Ptr&& left, Ptr&& right);   
      static Ptr EU(Ptr&& left, Ptr&& right);   

      static Ptr K(const std::string& agent_name, Ptr&& child);

      static Ptr Atom(const std::string& atom_name);
      static Ptr Atom(const std::string& owner, const std::string& atom_name);
  };


  namespace formulas {

    enum class Quantifier {
      A,
      E
    };

    class TemporalFormula : public Formula { 
      public:
        Quantifier quantifier;

        TemporalFormula(Quantifier quantifier)
        : quantifier(quantifier)
        {
        }
    };

    class G : public TemporalFormula {
      public:
        Formula::Ptr child;

        G(Formula::Ptr&& child, Quantifier quantifier) 
        : TemporalFormula(quantifier),
          child(std::move(child))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class F : public TemporalFormula {
      public:
        Formula::Ptr child;

        F(Formula::Ptr&& child, Quantifier quantifier) 
        : TemporalFormula(quantifier),
          child(std::move(child))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class X : public TemporalFormula {
      public:
        Formula::Ptr child;

        X(Formula::Ptr&& child, Quantifier quantifier) 
        : TemporalFormula(quantifier),
          child(std::move(child))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class U : public TemporalFormula {
      public:
        Formula::Ptr left;
        Formula::Ptr right;

        U(Formula::Ptr&& left, Formula::Ptr&& right, Quantifier quantifier) 
        : TemporalFormula(quantifier),
          left(std::move(left)),
          right(std::move(right))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class K : public Formula {
      public:
        std::string agent_name;
        Formula::Ptr child;

        K(const std::string& agent_name, Formula::Ptr&& child) 
        : agent_name(agent_name),
          child(std::move(child))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class And : public Formula {
      public:
        Formula::Ptr left;
        Formula::Ptr right;

        And(Formula::Ptr&& left, Formula::Ptr&& right) 
        : left(std::move(left)),
          right(std::move(right))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class Or : public Formula {
      public:
        Formula::Ptr left;
        Formula::Ptr right;

        Or(Formula::Ptr&& left, Formula::Ptr&& right) 
        : left(std::move(left)),
          right(std::move(right))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class Arrow : public Formula {
      public:
        Formula::Ptr left;
        Formula::Ptr right;

        Arrow(Formula::Ptr&& left, Formula::Ptr&& right) 
        : left(std::move(left)),
          right(std::move(right))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class Not : public Formula {
      public:
        Formula::Ptr child;

        Not(Formula::Ptr&& child) 
        : child(std::move(child))
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

    class Atom : public Formula {
      public:
        std::string owner;
        std::string atom_name;

        Atom(const std::string& atom_name)
        : atom_name(atom_name)
        {
        }

        Atom(const std::string& owner, const std::string& atom_name)
        : owner(owner),
          atom_name(atom_name)
        {
        }

        void accept(FormulaVisitor& visitor);
        void accept(ConstFormulaVisitor& visitor) const;

        Formula::Ptr clone() const;
    };

  } // namespace formulas

} // namespace mcmas

#endif