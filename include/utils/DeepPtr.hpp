#ifndef MCMAS_DEEPPTR_HPP
#define MCMAS_DEEPPTR_HPP
#include <memory>

namespace mcmas {

  // See https://codereview.stackexchange.com/questions/103744/deepptr-a-deep-copying-unique-ptr-wrapper-in-c
  //
  // Extends std::unique_ptr to allow for deep_copying of pointers
  // Used for representing children in AST
  template <typename T>
  struct DeepPtr : public std::unique_ptr<T>
  {
    public:
      using std::unique_ptr<T>::unique_ptr;
      DeepPtr() {};
      DeepPtr(DeepPtr<T> const& other)
      { 
          auto value = *other.get();
          this->reset(new T(value));
      }
      DeepPtr<T>& operator=(DeepPtr<T> const& other)
      {
          auto value = *other.get();
          this->reset(new T(value));
          return *this;
      }
  };

}

#endif