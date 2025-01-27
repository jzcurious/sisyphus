#ifndef _SISYPHUS_CONFIG_HPP_
#define _SISYPHUS_CONFIG_HPP_

#include "deltat/timers/chronotimer.hpp"
#include "deltat/timers/ktimer.hpp"
#include "itercallback.hpp"
#include "job.hpp"

#include <utility>

namespace sis {

template <class T>
concept BenchmarkConfigKind = requires { typename T::BenchmarkConfigFeature{}; };

template <JobKind JobT, dt::TimerKind TimerT, IterCallbackKind IterCallbackT>
struct BenchmarkConfig {
  struct BenchmarkConfigFeature {};

  JobT job;
  TimerT timer;
  IterCallbackT iter_callback;
  std::size_t nrepeats;
  std::size_t nwarmups;

  template <JobKind JobT_, dt::TimerKind TimerT_, IterCallbackKind IterCallbackT_>
  BenchmarkConfig(JobT_&& job,
      TimerT_&& timer,
      IterCallbackT_&& callback,
      std::size_t nrepeats = 2,
      std::size_t nwarmups = 1)
      : job(std::forward<JobT_>(job))
      , timer(std::forward<TimerT_>(timer))
      , iter_callback(std::forward<IterCallbackT_>(callback))
      , nrepeats(nrepeats)
      , nwarmups(nwarmups) {}

  template <JobKind JobT_, dt::TimerKind TimerT_>
  BenchmarkConfig(
      JobT_&& job, TimerT_&& timer, std::size_t nrepeats = 2, std::size_t nwarmups = 1)
      : job(std::forward<JobT_>(job))
      , timer(std::forward<TimerT_>(timer))
      , iter_callback()
      , nrepeats(nrepeats)
      , nwarmups(nwarmups) {}

  template <JobKind JobT_, IterCallbackKind IterCallbackT_>
  BenchmarkConfig(JobT_&& job,
      IterCallbackT_&& callback,
      std::size_t nrepeats = 2,
      std::size_t nwarmups = 1)
      : job(std::forward<JobT_>(job))
      , timer()
      , iter_callback(std::forward<IterCallbackT_>(callback))
      , nrepeats(nrepeats)
      , nwarmups(nwarmups) {}
};

template <JobKind JobT_, dt::TimerKind TimerT_, IterCallbackKind IterCallbackT_>
BenchmarkConfig(JobT_&&,
    TimerT_&&,
    IterCallbackT_&&,
    std::size_t nrepeats = 2,
    std::size_t nwarmups = 1) -> BenchmarkConfig<JobT_, TimerT_, IterCallbackT_>;

template <JobKind JobT_, dt::TimerKind TimerT_>
BenchmarkConfig(JobT_&&, TimerT_&&, std::size_t nrepeats = 2, std::size_t nwarmups = 1)
    -> BenchmarkConfig<JobT_, TimerT_, detail::NoIterCallback>;

template <JobKind JobT_, IterCallbackKind IterCallbackT_>
BenchmarkConfig(JobT_&&,
    IterCallbackT_&&,
    std::size_t nrepeats = 2,
    std::size_t nwarmups = 1) -> BenchmarkConfig<JobT_, dt::ChronoTimer, IterCallbackT_>;

}  // namespace sis

#endif  // _SISYPHUS_CONFIG_HPP_
