#include "BaseType.hpp"

namespace mcmas {

  std::string to_string(const BaseType& type) {
    std::string type_string = std::visit(Overload {
      [](const BOOL) { 
        return std::string("boolean");
      },
      [](const ENUM e) { 
        std::string enum_ids;
        for (auto it = e.ids.cbegin(); it != e.ids.cend(); ++it) {
          if (it != --e.ids.cend()) {
            enum_ids += *it + ", ";
          } else {
            enum_ids += *it + " ";
          }
        }
        return enum_ids;
      },
      [](const RANGED_INT i) {
        return std::to_string(i.min) + ".." + std::to_string(i.max);
      }
    }, type);

    return type_string;
  }

  IntBoolVector generate_possible_values(const BaseType& type) {
    return std::visit(Overload {
      [](const BOOL) -> IntBoolVector {
        return {std::vector<bool>{false, true}};
      },
      [](const ENUM) -> IntBoolVector {
        // TODO
        return {std::vector<int>()};
      },
      [](const RANGED_INT i) -> IntBoolVector {
        std::vector<int> range;
        for (int x = i.min; x <= i.max; ++x) { range.push_back(x); }
        return {range};
      }
    }, type);
  }

}