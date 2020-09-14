#ifndef PDP_MEMORY_HPP
#define PDP_MEMORY_HPP

#include "config.h"

#include <Eigen/Core>

// We need to use a define, so this will always be inlined correctly
#define aligned_alloca(size,align) \
	(reinterpret_cast<void*>( (reinterpret_cast<size_t>( alloca((size) + (align)) ) &  ~(std::size_t(align))) + (align)))

#endif // PDP_MEMORY_HPP