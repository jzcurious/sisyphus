#ifndef _SISYPHUS_JOB_HPP_
#define _SISYPHUS_JOB_HPP_

#include "sisyphus/growth.hpp"
#include "sisyphus/provider.hpp"

namespace sis {

template <class T>
concept JobKind = requires(T x, std::size_t i) {
  { x(i) } -> detail::not_void;
};

template <DataProviderKind ProviderT, GrowhtFuncKind GrowthT>
class Job {  // TODO: maybe rename the class
 private:
  ProviderT _provider;
  GrowthT _growth;

  using DataT = decltype(_provider(0));

 public:
  Job(ProviderT provider, GrowthT growth)
      : _provider(provider)
      , _growth(growth) {};

  DataT operator()(std::size_t i) {
    return _provider(_growth(i));
  }
};

}  // namespace sis

#endif  // _SISYPHUS_JOB_HPP_
