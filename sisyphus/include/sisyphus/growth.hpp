#ifndef _GROWTH_HPP_
#define _GROWTH_HPP_

#include <concepts>
#include <cstddef>

namespace sis {

template <class T>
concept GrowhtFuncKind = requires(T x, std::size_t i) {
  { x(i) } -> std::same_as<std::size_t>;
};

}  // namespace sis

#endif  // _GROWTH_HPP_
