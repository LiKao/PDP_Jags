#ifndef MEMORYBLOCK_HPP
#define MEMORYBLOCK_HPP

#include <array>

namespace PDP {

	template<size_t Level, typename _Enable = void>
	struct Layout;


	template<>
	struct Layout<0> {
		size_t product() const { return 1; }
	};

	template<size_t _Level> 
	struct Layout<_Level, typename std::enable_if<(_Level > 0)>::type> {
		static constexpr size_t Level = _Level;

		typedef const Layout<Level-1>	rest_type;


		template<typename ... Args>
		Layout(size_t dim, Args&&... args)
		: m_dim(dim), m_rest( rest_type( std::forward<Args>(args) ... ) )
		{}

		size_t dim() const { return m_dim; }

		rest_type & rest() const { return m_rest; }

		size_t product() const { return m_dim * m_rest.product(); }
	private:
		const size_t 		m_dim;
			  rest_type 	m_rest;
	};


	template<size_t Dims,typename T>
	class MemoryBlock {
	public:
		typedef typename std::conditional<(Dims > 1),MemoryBlock<Dims-1,T>,T>::type 				value_type;
		typedef typename std::conditional<(Dims > 1),MemoryBlock<Dims-1,const T>, const T>::type	const_value_type;
		typedef typename std::add_pointer<value_type>::type 										pointer;
		typedef typename std::add_pointer<const_value_type>::type 									const_pointer;
		typedef typename std::add_lvalue_reference<value_type>::type 								reference;
		typedef typename std::add_lvalue_reference<const_value_type>::type 							const_reference;
		typedef size_t																				size_type;
		typedef Layout<Dims>																		dims_type;

		template<typename... Args>
		MemoryBlock(T * buff, Args&&... dims)
		: m_dims( std::forward<Args>(dims)... ), m_buff( buff ), m_stride( 1 )
		{}

		size_type stride() const { return m_stride; }

		template<size_t DD = Dims>
		typename std::enable_if<(DD > 1), value_type>::type  
		operator[](size_type idx) {
			return value_type(m_buff + idx * stride(), m_dims.rest(), stride() * m_dims.dim() );
		}

		template<size_t DD = Dims>
		typename std::enable_if<(DD > 1), const_value_type>::type 
		operator[](int idx) const {
			return value_type(m_buff + idx * stride(), m_dims.rest(), stride() * m_dims.dim() );
		}

		template<size_t DD = Dims>
		typename std::enable_if<(DD == 1), reference>::type
		operator[](int idx) {
			return *(m_buff + idx * stride());
		}

		template<size_t DD = Dims>
		typename std::enable_if<(DD == 1), const_reference>::type
		operator[](int idx) const {
			return *(m_buff + idx * stride());
		} 

		MemoryBlock(T * buff, dims_type dims, size_type stride) 
		: m_dims( dims ), m_buff( buff ), m_stride( stride )
		{}

		size_type extend() const { return m_dims.product(); }

		void next() { m_buff += extend(); }

		template<typename U>
		void operator=(const U * rhs) {
			std::move(rhs, rhs + extend(), m_buff );
		}

		pointer       get()       { return m_buff; }
		const_pointer get() const { return m_buff; }

	private:
		const dims_type			m_dims;
		 	  T *				m_buff;
		const size_type         m_stride;
	};
}

#endif // MEMORYBLOCK_HPP