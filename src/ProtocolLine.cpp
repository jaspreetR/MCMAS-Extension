#include "ProtocolLine.hpp"
#include "visitors/StringVisitor.hpp"

namespace mcmas {

  ProtocolLine::ProtocolLine(const ProtocolLine& other) {
    auto line = other.clone();
    condition = std::move(line.condition);
    enabled_actions = std::move(line.enabled_actions);
  }

  std::string ProtocolLine::to_string() const {
    std::string condition_string = condition->to_string();
    
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

  ProtocolLine ProtocolLine::clone() const {
    auto line = ProtocolLine(this->condition->clone(), enabled_actions);
    return line;
  }

}