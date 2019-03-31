#include "EvolutionLine.hpp"
#include "expressions/Visitor.hpp"

namespace mcmas {

  std::string EvolutionLine::to_string() const {
    StringVisitor string_visitor;
    result->accept(string_visitor);
    std::string result_string = string_visitor.result;

    condition->accept(string_visitor);
    std::string condition_string = string_visitor.result;

    return result_string + " if " + condition_string + ";\n";
  }

}