#ifndef _JOB_HPP_
#define _JOB_HPP_

#include "sisyphus/growth.hpp"
#include "sisyphus/provider.hpp"

namespace sis {

template <DataProviderKind ProviderT, GrowhtFuncKind GrowthT>
class Job {
 private:
  ProviderT _provider;
  GrowthT _growth;
  using DataT = decltype(_provider(0));

 public:
  Job(ProviderT provider, GrowthT growth)
      : _provider(provider)
      , _growth(growth) {};

  DataT data(std::size_t i) {
    return _provider.data(_growth(i));
  }
};

}  // namespace sis

#endif  // _JOB_HPP_
