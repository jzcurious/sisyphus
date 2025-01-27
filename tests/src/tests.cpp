#include "deltat/timers/chronotimer.hpp"
#include "sisyphus/benchmark.hpp"
#include "sisyphus/job.hpp"
#include <gtest/gtest.h>
#include <span>
#include <tuple>
#include <vector>

template <class ItemT, std::size_t MaxLen>
class SingleVectorProvider final {
 private:
  std::vector<ItemT> _pool;

 public:
  SingleVectorProvider()
      : _pool(MaxLen) {
    for (std::size_t i = 0; i < MaxLen; ++i) _pool[i] = i;
  }

  std::span<ItemT> operator()(std::size_t i) {
    return std::span(_pool.begin(), _pool.begin() + i);
  }
};

template <class ItemT, std::size_t MaxLen>
class PairVectorProvider final {
 private:
  SingleVectorProvider<ItemT, MaxLen> _svp;

 public:
  std::tuple<std::span<ItemT>, std::span<ItemT>> operator()(std::size_t i) {
    return std::make_tuple(_svp(i), _svp(i));
  }
};

static void func1(std::span<float>& x) {
  for (std::size_t i = 0; i < x.size(); ++i) x[i] += x[i];
}

TEST(Benchmark, single_arg) {
  auto job = sis::Job(SingleVectorProvider<float, 900>{},
      [](std::size_t i) { return (i + 1) * (i + 1); });

  std::size_t counter = 0;

  auto conf
      = sis::BenchmarkConfig(job, dt::ChronoTimer{}, [&](std::size_t i) { counter++; });

  sis::Benchmark("My Benchmark 1", func1, conf).run(30);

  sis::Benchmark("My Benchmark 2",
      func1,
      sis::BenchmarkConfig(job, dt::ChronoTimer{}, [&](std::size_t i) { counter--; }))
      .run(30);

  EXPECT_EQ(counter, 0);
}

TEST(Benchmark, two_args) {
  auto job = sis::Job(
      PairVectorProvider<float, 900>{}, [](std::size_t i) { return (i + 1) * (i + 1); });

  std::size_t counter = 0;

  auto conf
      = sis::BenchmarkConfig(job, dt::ChronoTimer{}, [&](std::size_t i) { counter++; });

  auto func2 = [](std::span<float>& x, std::span<float>& y) {
    for (std::size_t i = 0; i < x.size(); ++i) y[i] += x[i];
  };

  sis::Benchmark("My Benchmark 1", func2, conf).run(30);

  sis::Benchmark("My Benchmark 2",
      func2,
      sis::BenchmarkConfig(job, dt::ChronoTimer{}, [&](std::size_t i) { counter--; }))
      .run(30);

  EXPECT_EQ(counter, 0);
}
