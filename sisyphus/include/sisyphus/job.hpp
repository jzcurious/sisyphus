#ifndef _JOB_HPP_
#define _JOB_HPP_

#include "sisyphus/provider.hpp"

namespace sis {

template <class DataT, DataProviderKind<DataT> ProviderT>
class Job {};

}  // namespace sis

#endif  // _JOB_HPP_
