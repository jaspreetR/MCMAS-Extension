#include "Evolution.hpp"

namespace mcmas {

  std::string Evolution::to_string() const {
    std::string evolution_string = "Evolution : \n";
    for (auto& line : lines) {
      evolution_string += line.to_string();
    }
    evolution_string += "end Evolution \n";

    return evolution_string;
  }

}