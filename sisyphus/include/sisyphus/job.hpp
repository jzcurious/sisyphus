#ifndef _JOB_HPP_
#define _JOB_HPP_

#include "sisyphus/growth.hpp"
#include "sisyphus/provider.hpp"

namespace sis {

template <DataProviderKind ProviderT, GrowhtFuncKind GrowthT>
class Job {};

}  // namespace sis

#endif  // _JOB_HPP_
