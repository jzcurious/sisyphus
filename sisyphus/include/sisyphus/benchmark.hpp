#ifndef _SISYPHUS_BENCHMARK_
#define _SISYPHUS_BENCHMARK_

#include "job.hpp"

#include "deltat/timeit.hpp"
#include "deltat/timers/ktimer.hpp"

namespace sis::detail {
// void default_iter_callback() {}
}  // namespace sis::detail

namespace sis {

// TODO: iteration callback

// template <class T, class... Us>
// concept IterCallbackKind = requires(T x, Us... ys) {
//   { x(ys...) };
// };

template <class TargetT, JobKind JobT, dt::TimerKind TimerT>
class Benchmark {
 public:
  const char* name;

 private:
  JobT _job;
  dt::TimeIt<TargetT, TimerT> _timeit;

 public:
  template <class TargetT_>
  Benchmark(const char* name,
      TargetT_&& target,
      const JobT& job,
      TimerT timer,
      std::size_t nrepeats = 3,
      std::size_t nwarmups = 1)
      : name(name)
      , _job(job)
      , _timeit(std::forward<TargetT_>(target), timer, nrepeats, nwarmups) {}

  const dt::TimeIt<TargetT, TimerT>& timeit() const {
    return _timeit;
  }

  void reset() {
    _timeit.reset();
  }

  Benchmark& run(size_t nprobes) {
    for (size_t i = 0; i < nprobes; ++i) {
      auto args = _job(i);
      _timeit.run(args);
    }
    return *this;
  }
};

template <class TargetT_, JobKind JobT, dt::TimerKind TimerT>
Benchmark(const char* name,
    TargetT_&& target,
    const JobT& job,
    TimerT timer,
    std::size_t nrepeats = 3,
    std::size_t nwarmups = 1) -> Benchmark<TargetT_, JobT, TimerT>;

}  // namespace sis

#endif  // _SISYPHUS_BENCHMARK_
