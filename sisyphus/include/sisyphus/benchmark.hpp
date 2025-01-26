#ifndef _SISYPHUS_BENCHMARK_
#define _SISYPHUS_BENCHMARK_

#include "job.hpp"

#include "deltat/timeit.hpp"
#include "deltat/timers/ktimer.hpp"

namespace sis::detail {

struct NoIterCallback {};

}  // namespace sis::detail

namespace sis {

template <class T>
concept IterCallbackKind
    = std::is_same_v<T, detail::NoIterCallback> or requires(T x, std::size_t i) {
        { x(i) };
      };

// clang-format off
template <
  class TargetT,
  JobKind JobT,
  dt::TimerKind TimerT,
  IterCallbackKind IterCallbackT
>
// clang-format on
class Benchmark {
 public:
  const char* name;

 private:
  JobT _job;
  dt::TimeIt<TargetT, TimerT> _timeit;
  IterCallbackT _iter_callback;

 public:
  template <class TargetT_, JobKind JobT_, IterCallbackKind IterCallbackT_>
  Benchmark(const char* name,
      TargetT_&& target,
      JobT_&& job,
      const TimerT& timer,
      std::size_t nrepeats,
      std::size_t nwarmups,
      IterCallbackT_&& iter_callback)
      : name(name)
      , _job(std::forward<JobT_>(job))
      , _timeit(std::forward<TargetT_>(target), timer, nrepeats, nwarmups)
      , _iter_callback(std::forward<IterCallbackT_>(iter_callback)) {}

  const dt::TimeIt<TargetT, TimerT>& timeit() const {
    return _timeit;
  }

  void reset() {
    _timeit.reset();
  }

  Benchmark& run(size_t nprobes) {
    for (std::size_t i = 0; i < nprobes; ++i) {
      auto args = _job(i);
      _timeit.run(args);  // TODO: think about it
      if constexpr (not std::is_same_v<detail::NoIterCallback, IterCallbackT>)
        _iter_callback(i);
    }
    return *this;
  }
};

// clang-format off
template <
  class TargetT_,
  JobKind JobT_,
  IterCallbackKind IterCallbackT_,
  dt::TimerKind TimerT
>
// clang-format on
Benchmark(const char* name,
    TargetT_&& target,
    JobT_&& job,
    const TimerT& timer,
    std::size_t nrepeats,
    std::size_t nwarmups,
    IterCallbackT_&& iter_callback) -> Benchmark<TargetT_, JobT_, TimerT, IterCallbackT_>;

}  // namespace sis

#endif  // _SISYPHUS_BENCHMARK_
