#ifndef _SISYPHUS_BENCHMARK_
#define _SISYPHUS_BENCHMARK_

#include "config.hpp"

#include "deltat/timeit.hpp"

namespace sis {

template <class TargetT, BenchmarkConfigKind BenchmarkConfigT>
class Benchmark {
 public:
  const char* name;

 private:
  TargetT _target;
  BenchmarkConfigT _config;
  using TimeItT = dt::TimeIt<TargetT, decltype(_config.timer)>;
  TimeItT _timeit;

  static constexpr const bool _use_callback
      = not std::is_same_v<detail::NoIterCallback, decltype(_config.iter_callback)>;

 public:
  template <class TargetT_, BenchmarkConfigKind BenchmarkConfigT_>
  Benchmark(const char* name, TargetT_&& target, BenchmarkConfigT_ config)
      : name(name)
      , _target(std::forward<TargetT_>(target))
      , _config(config)
      , _timeit(std::forward<TargetT_>(target), config.timer) {}

  const TimeItT& timeit() const {
    return _timeit;
  }

  void reset() {
    _timeit.reset();
  }

  Benchmark& run(size_t nprobes) {
    for (std::size_t i = 0; i < nprobes; ++i) {
      auto args = _config.job(i);
      _timeit.run(args);  // TODO: think about it
      if constexpr (_use_callback) _config.iter_callback(i);
    }
    return *this;
  }
};

template <class TargetT_, BenchmarkConfigKind BenchmarkConfigT_>
Benchmark(
    const char*, TargetT_&&, BenchmarkConfigT_) -> Benchmark<TargetT_, BenchmarkConfigT_>;

}  // namespace sis

#endif  // _SISYPHUS_BENCHMARK_
