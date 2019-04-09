#ifndef MCMAS_MISC_HPP
#define MCMAS_MISC_HPP
#include <string>
#include <vector>

namespace mcmas {

  inline std::string generate_local_action(const std::string& action, int i, int j) {
    // could cache results in static var
    return action + "_" + std::to_string(i) + "_" + std::to_string(j);
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