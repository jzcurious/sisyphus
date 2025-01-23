#ifndef _SISYPHUS_PROVIDER_
#define _SISYPHUS_PROVIDER_

#include <concepts>
#include <cstddef>

namespace sis {

template <class T, class U>
concept DataProviderKind = requires(T x, std::size_t i) {
  { x.data(i) } -> std::same_as<U>;
};

}  // namespace sis

#endif  //   _SISYPHUS_PROVIDER_
