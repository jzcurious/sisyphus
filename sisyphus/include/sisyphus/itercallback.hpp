#ifndef _ITER_CALLBACK_HPP_
#define _ITER_CALLBACK_HPP_

#include <type_traits>

namespace sis::detail {

struct NoIterCallback {};

}  // namespace sis::detail

namespace sis {

template <class T>
concept IterCallbackKind
    = std::is_same_v<T, detail::NoIterCallback> or requires(T x, std::size_t i) {
        { x(i) };
      };

}  // namespace sis

#endif  // _ITER_CALLBACK_HPP_
