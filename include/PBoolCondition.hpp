#ifndef MCMAS_PBOOLCONDITION_HPP
#define MCMAS_PBOOLCONDITION_HPP
#include <variant>
#include "utils/DeepPtr.hpp"

/*
#include "expressions/Expressions.hpp"

namespace mcmas {

  class PBoolCondition;
  class PBitExpression;
  class PBitTerm;
  class PBitFactor;
  class PBitElement;
  class PExpression;
  class PTerm;
  class PElement;

  class PBoolCondition {
    public:
      using AND = AndExpr<PBoolCondition>;
      using OR = OrExpr<PBoolCondition>;
      using NOT = NotExpr<PBoolCondition>;
      using EXPR = LogicExpr<PBitExpression>;

      DeepPtr<std::variant<AND, OR, NOT, EXPR>> child;
  };

  //TODO: these expressions arent specfic to protocols only but also the evolution definition

  class PBitExpression {
    public:
      using BITOR = BitOrExpr<PBitExpression>;
      using BITXOR = BitXorExpr<PBitExpression>;
      using TERM = PBitTerm;

      DeepPtr<std::variant<BITOR, BITXOR, TERM>> child;
  };

  class PBitTerm {
    public:
      using BITAND = BitAndExpr<PBitTerm>;
      using FACTOR = PBitFactor;

      DeepPtr<std::variant<BITAND, FACTOR>> child;
  };

  class PBitFactor {
    public:
      using BITNOT = BitNotExpr<PBitElement>;
      using ELEMENT = PBitElement;

      DeepPtr<std::variant<BITNOT, ELEMENT>> child;
  };

  class PBitElement {
    public:
      using BITEXPR = PBitExpression;
      using NUMEXPR = PExpression;

      DeepPtr<std::variant<BITEXPR, NUMEXPR>> child;
  };

  class PExpression {
    public:
      using ADD = AddExpr<PExpression>;
      using SUB = SubExpr<PExpression>;
      using TERM = PTerm;

      DeepPtr<std::variant<ADD, SUB, TERM>> child;
  };

  class PTerm {
    public:
      using MUL = MulExpr<PTerm>;
      using DIV = DivExpr<PTerm>;
      using ELEMENT = PElement;

      DeepPtr<std::variant<MUL, DIV, ELEMENT>> child;
  };

  class PElement {
    public:
      using EXPR = PExpression;
      using VALUE = std::variant<std::string, bool, int>;

      DeepPtr<std::variant<EXPR, VALUE>> child;
  };
}

*/

#endif