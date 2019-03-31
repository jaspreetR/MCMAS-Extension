#include "Protocol.hpp"
#include "utils/Misc.hpp"

namespace mcmas {

  void Protocol::apply_local_action_transform(int max_x, int max_y, int comm_distance) {
    std::vector<ProtocolLine> new_lines;

    for (const auto& line : lines) {
      for (int i = 1; i <= max_x; ++i) {
        for (int j = 1; j <= max_x; ++j) {
          auto cond_copy = line.condition->clone();
          auto local_condition = Expression::And(
                                   Expression::Eq(Expression::Id("pos_x"), Expression::Int(i)),
                                   Expression::Eq(Expression::Id("pos_y"), Expression::Int(j))
                                 );
          local_condition = Expression::And(std::move(local_condition), std::move(cond_copy));

          std::vector<std::string> new_enabled_actions;
          for (const auto& action : line.enabled_actions) {
            new_enabled_actions.emplace_back(generate_local_action(action, i, j));
          }

          new_lines.emplace_back(std::move(local_condition), new_enabled_actions);
        }
      }
    }

    lines = std::move(new_lines);
  }

  std::string Protocol::to_string() const {
    std::string protocol_string = "Protocol : \n";
    for (auto& line : lines) {
      protocol_string += line.to_string();
    }
    protocol_string += "end Protocol\n";
    return protocol_string;
  }

}