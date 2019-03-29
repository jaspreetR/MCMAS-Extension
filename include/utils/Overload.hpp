#ifndef MCMAS_OVERLOAD_HPP
#define MCMAS_OVERLOAD_HPP

namespace mcmas {

  template<class... Ts> struct Overload : Ts... { using Ts::operator()...; };
  template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

}

#endif
