#ifndef MCMAS_MISC_HPP
#define MCMAS_MISC_HPP
#include <string>
#include <vector>
#include "expressions/Expression.hpp"

namespace mcmas {

  inline std::string generate_local_action(const std::string& action, int i, int j) {
    // could cache results in static var
    return action + "_" + std::to_string(i) + "_" + std::to_string(j);
  }

  inline Expression::Ptr generate_local_action_expression(const std::vector<std::string>& agent_names,
                                                   const std::string& action_name,
                                                   int x, int y, int max_x, int max_y, int comm_distance) {
    std::vector<Expression::Ptr> local_action_exprs;
    for (int i = std::max(x - comm_distance, 1); i <= std::min(x + comm_distance, max_x); ++i) {
      for (int j = std::max(y - comm_distance, 1); j <= std::min(y + comm_distance, max_x); ++j) {
        auto local_action = generate_local_action(action_name, i, j);
        for (const auto& agent_name : agent_names) {
          auto local_action_expr = Expression::Eq(Expression::Id(agent_name, "Action"), Expression::Id(local_action));
          local_action_exprs.emplace_back(std::move(local_action_expr));
        }
      }
    }

    return Expression::Or(std::move(local_action_exprs));
  }

  template <typename T>     
  std::vector<std::vector<T>> cartesian_product(const std::vector<std::vector<T>>& args) {
    size_t result_size = 1;

    for (const auto& arg : args) {
      result_size *= arg.size();
    }

    std::vector<std::vector<T>> result = {{}};
    result.reserve(result_size);

    for (const auto& arg : args) {
        std::vector<std::vector<T>> temp;
        temp.reserve(result_size);

        for (const auto& result_elem : result) {
            for (const auto& arg_elem : arg) {
                temp.emplace_back(result_elem);
                temp.back().emplace_back(arg_elem);
            }
        }

        result = std::move(temp);
    }

    return result;
  }
  

} // namespace mcmas

#endif