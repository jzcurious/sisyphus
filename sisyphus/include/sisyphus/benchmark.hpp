#ifndef _SISYPHUS_BENCHMARK_
#define _SISYPHUS_BENCHMARK_

#include "job.hpp"

#include "deltat/timeit.hpp"
#include "deltat/timers/ktimer.hpp"

namespace sis::detail {

template <typename T>
concept TupleLike = requires(T a) {
  std::tuple_size<T>::value;
  std::get<0>(a);
};

template <TupleLike T>
auto make_indices_for_tuple(T) {
  return std::make_index_sequence<std::tuple_size_v<T>>{};
}

// void default_iter_callback() {}
}  // namespace sis::detail

namespace sis {

// TODO: iteration callback

// template <class T, class... Us>
// concept IterCallbackKind = requires(T x, Us... ys) {
//   { x(ys...) };
// };

template <class TargetT, JobKind JobT, TimerKind TimerT>
class Benchmark {
 public:
  const char* name;

 private:
  JobT _job;
  TimeIt<TargetT, TimerT> _timeit;

  template <class TupleT, std::size_t... I>  // TODO: move to TimeIt
  void _run_timeit_with_tuple(TupleT args_tuple, std::index_sequence<I...>) {
    _timeit.run(std::get<I>(args_tuple)...);
  }

 public:
  Benchmark(const char* name,
      const JobT& job,
      TimerT,
      const TargetT& target,
      std::size_t nrepeats = 1,
      std::size_t nwarmups = 0)
      : name(name)
      , _job(job)
      , _timeit(target, nrepeats, nwarmups) {}

  std::vector<double>& results() const {
    return _timeit.measurements();
  }

  void reset() {
    _timeit.reset();
  }

  Benchmark& run(size_t nprobes) {
    for (size_t i = 0; i < nprobes; ++i) {
      // TODO: add iteration callback
      auto args = _job(i);
      if constexpr (detail::TupleLike<decltype(args)>)
        _run_timeit_with_tuple(args, detail::make_indices_for_tuple(args));
      else
        _timeit.run(args);
    }
    return *this;
  }
};

}  // namespace sis

#endif  // _SISYPHUS_BENCHMARK_
