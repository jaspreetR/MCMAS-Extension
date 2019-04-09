#include "ProtocolLine.hpp"
#include "visitors/StringVisitor.hpp"

namespace mcmas {

  std::string ProtocolLine::to_string() const {
    StringVisitor string_visitor;
    condition->accept(string_visitor);
    std::string condition_string = string_visitor.result;
    
    std::string actions_string = "{ ";
    for (auto it = enabled_actions.begin(); it != enabled_actions.end(); ++it) {
      if (it != --enabled_actions.end()) {
        actions_string += *it + ", "; 
      } else {
        actions_string += *it + " ";
      }
    }
    actions_string += "}"; 

    return condition_string + " : " + actions_string + ";\n";
  }

}