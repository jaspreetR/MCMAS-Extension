#ifndef MCMAS_DYNAMICBITSET_HPP
#define MCMAS_DYNAMICBITSET_HPP
#include <vector>
#include <string>

namespace mcmas {

  class DynamicBitset {
    public:
      DynamicBitset(size_t size) 
      : _size(size),
        _bits(size)
      {
      }

      auto begin() {
        return _bits.begin();
      }

      auto end() {
        return _bits.end();
      }

      auto rbegin() {
        return _bits.rbegin();
      }

      auto rend() {
        return _bits.rend();
      }

      void operator++() {
        for (auto&& bit : _bits) {
          if (bit) {
            bit = false;
          } else {
            bit = true;
            break;
          }
        }
      }

      bool all() {
        for (auto&& bit : _bits) {
          if (!bit) {
            return false;
          }
        }
        return true;
      }

      bool some() {
        for (auto&& bit : _bits) {
          if (bit) {
            return true;
          }
        }
        return false;
      }

      bool none() {
        return !some();
      }

      size_t size() const {
        return _size;
      }

      std::string to_string() const {
        std::string result;
        result.reserve(_size);
        for (auto it = _bits.rbegin(); it != _bits.rend(); ++it) {
          result.push_back(static_cast<char>(*it) + '0');
        }
        return result;
      }

    private:
      const std::size_t _size;
      std::vector<bool> _bits;

  };

}

#endif