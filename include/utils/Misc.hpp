#ifndef MCMAS_MISC_HPP
#define MCMAS_MISC_HPP
#include <string>
#include <vector>
#include <iostream>
#include "expressions/Expression.hpp"
#include "formulas/Formula.hpp"
#include "utils/DynamicBitset.hpp"

namespace mcmas {

  inline int natural_mod(int n, int mod) {
    int temp = (n - 1) % mod;
    return temp < 0 ? temp + mod + 1 : temp + 1;
  }

  inline std::string generate_local_action(const std::string& action, int i, int j) {
    // could cache results in static var
    return action + "_" + std::to_string(i) + "_" + std::to_string(j);
  }

  inline Expression::Ptr generate_local_action_expression(const std::string& action_name,
                                                          int x, int y, int max_x, int max_y, int comm_distance) {
    std::vector<Expression::Ptr> local_action_exprs;
    for (int i = x - comm_distance; i <= x + comm_distance; ++i) {
      for (int j = y - comm_distance; j <= y + comm_distance; ++j) {
        auto local_action = generate_local_action(action_name, natural_mod(i, max_x), natural_mod(j, max_y));

        /*
        for (const auto& agent_name : agent_names) {
          auto local_action_expr = Expression::Eq(Expression::Id(agent_name, "Action"), Expression::Id(local_action));
          local_action_exprs.emplace_back(std::move(local_action_expr));
        }
        */

        auto local_action_expr = Expression::Eq(Expression::Id("GlobalAction"), Expression::Id(local_action));
        local_action_exprs.emplace_back(std::move(local_action_expr));
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

  template <typename T>
  std::vector<std::vector<T>> power_set(const std::vector<T>& vals) {
    std::vector<std::vector<T>> result;
    DynamicBitset bits(vals.size());

    do {
      std::vector<T> subset;
      int i = 0;

      for (auto bit : bits) {
        if (bit) {
          subset.push_back(vals[i]);
        }
        ++i;
      }

      if (subset.size() > 0) {
        result.emplace_back(std::move(subset));
      }

      ++bits;
    } while (bits.some());

    return result;
  }

  inline std::string concat_strings(const std::vector<std::string>& words, const std::string& delim = "__") {
    std::string result;

    for (const auto& action : words) {
      if (result.size() == 0) {
        result += action;
      } else {
        result += "__" + action;
      }
    }

    return result;
  }

  inline std::string quantifier_to_string(formulas::Quantifier quantifier) {
    return quantifier == formulas::Quantifier::A ? "A" : "E"; 
  }
  
} // namespace mcmas

#endif