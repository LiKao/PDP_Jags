#ifndef VECDISPATCHER_HPP
#define VECDISPATCHER_HPP

namespace PDP {
	template<size_t N>
	struct static_log2
	{ 
		static constexpr size_t value = static_log2<(N >> 1)>::value + 1;
	};

	template<>
	struct static_log2<1>
	{
		static constexpr size_t value = 0;
	};


	template<template<size_t> class op, size_t N, size_t M = 0>
	struct dispatcher {
		static constexpr size_t K = (1 << N);
		static constexpr size_t value = M;

		template<typename ... Args>
		static void ALWAYS_INLINE call(const size_t n, Args && ... args) {
			if( n & K ) {
				dispatcher<op, N-1, value+K>::call(n ^ K, std::forward<Args>(args) ... );
			} else {
				dispatcher<op, N-1, value>::call(n, std::forward<Args>(args) ...);
			}
		}
	};

	template<template<size_t> class op, size_t M>
	struct dispatcher<op, 0, M>
	{
		static constexpr size_t K = 1;

		template<typename ... Args>
		static void ALWAYS_INLINE call(const size_t n, Args && ... args) {
			if( n & K ) {
				op<M+1>::run( std::forward<Args>(args)... );
			} else {
				op<M>::run( std::forward<Args>(args)... );
			}
		}
	};

}

#endif // VECDISPATCHER_HPP