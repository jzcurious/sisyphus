#ifndef _SISYPHUS_PROVIDER_HPP_
#define _SISYPHUS_PROVIDER_HPP_

#include <concepts>
#include <cstddef>

namespace sis::detail {

template <class T>
concept not_void = not std::same_as<T, void>;

}

namespace sis {

template <class T>
concept DataProviderKind = requires(T x, std::size_t n) {
  { x(n) } -> detail::not_void;
};

}  // namespace sis

#endif  //   _SISYPHUS_PROVIDER_HPP_
