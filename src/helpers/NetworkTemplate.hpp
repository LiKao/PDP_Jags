#ifndef NETWORKTEMPLATE_HPP
#define NETWORKTEMPLATE_HPP

#include <stdexcept>
#include <type_traits>
#include <iterator>
#include <functional>
#include <numeric>
#include <cstring>

#include "Assert.hpp"
#include "MemorySection.hpp"
#include "FixedWidthList.hpp"

namespace PDP {
	template<typename T>
	class NetworkTemplate {
	public:

		typedef T															value_type;
		typedef typename std::add_const<value_type>::type					const_value_type;
		typedef typename std::add_pointer<value_type>::type 				pointer;
		typedef typename std::add_pointer<const_value_type>::type 			const_pointer;
		typedef typename std::add_lvalue_reference<value_type>::type 		reference;
		typedef typename std::add_lvalue_reference<const_value_type>::type 	const_reference;
		typedef unsigned int												size_type;
		typedef MemorySection<value_type>									raw_type;

		class entry {
		public:
			typedef NetworkTemplate::value_type									value_type;
			typedef typename std::add_const<value_type>::type					const_value_type;
			typedef typename std::add_pointer<value_type>::type 				pointer;
			typedef typename std::add_pointer<const_value_type>::type 			const_pointer;
			typedef typename std::add_lvalue_reference<value_type>::type 		reference;
			typedef typename std::add_lvalue_reference<const_value_type>::type 	const_reference;
			typedef size_t														size_type;

			typedef MemorySection<value_type>									raw_type;

			static constexpr size_type		s_row_idx			= 0;
			static constexpr size_type		s_column_idx		= s_row_idx + 1;
			static constexpr size_type		s_pram_idx			= s_column_idx + 1;
			static constexpr size_type		s_buff_length 		= s_pram_idx + 1;

			entry(const pointer buff, value_type row, value_type column, value_type pram) 
			: m_buff(buff)
			{
				m_buff[s_row_idx] 		= row;
				m_buff[s_column_idx] 	= column;
				m_buff[s_pram_idx] 		= pram;
			}

			entry(const pointer buff)
			: m_buff( buff )
			{}

			const_reference  row() 		const { return m_buff[s_row_idx]; }
			const_reference  column()	const { return m_buff[s_column_idx]; }
			const_reference  pram()		const { return m_buff[s_pram_idx]; }

			size_type	extend() 	const { return static_extend(); }

			static size_type static_extend() { return s_buff_length; }
		private:
			const pointer 	m_buff;
		};

		typedef FWList<entry,value_type,double&>					entry_list_type;
		typedef FWList<entry,const_value_type> 						const_entry_list_type;


	 	static constexpr size_type					s_nnodes_idx    			= 0;
	 	static constexpr size_type					s_nentries_idx 				= s_nnodes_idx + 1;
	 	static constexpr size_type					s_header_length				= s_nentries_idx + 1;
	 	static constexpr size_type					s_prams_idx 				= s_nentries_idx;

		static inline void init(pointer buff, value_type nnodes) 
		{
			buff[s_nentries_idx] = 0;
			buff[s_nnodes_idx] 	 = nnodes;
		}

		NetworkTemplate(const_pointer _buff, size_type _extend) 
		: m_buff(_buff), m_extend(_extend)
		{
			Assert(extend() > 0, "Invalid extend of networkstack", std::invalid_argument);
		}

		template<typename U>
		NetworkTemplate(
			typename std::enable_if<std::is_convertible<U,value_type>::value,pointer>::type _buff, 
			size_type _extend, const NetworkTemplate<U> & _rhs)
			: m_buff(_buff), m_extend(_extend)
		{
			std::move( std::begin(_rhs.raw()), std::end(_rhs.raw()), raw().begin() );
		}

		NetworkTemplate(const NetworkTemplate & rhs) = default;
		NetworkTemplate(NetworkTemplate && rhs) = default;

		size_type 		extend(size_type i = 0) 	const { return m_extend + i*entry::static_extend(); }

	 	raw_type		raw()    	const { return raw_type( m_buff, extend() ); }
	 	raw_type		raw() 			  { return raw_type( m_buff, extend() ); }


	 	const_entry_list_type 	entries()	const { return const_entry_list_type( m_buff + s_header_length, m_buff[s_nentries_idx] ); }	
		entry_list_type 		entries() 		  { return entry_list_type( m_buff + s_header_length, m_buff[s_nentries_idx] ); }

		const_reference nnodes() const { return m_buff[s_nnodes_idx]; }

		value_type nprams() const {
			return std::accumulate(entries().begin(), entries().end(), value_type(0), [](auto lhs, auto entry){ return std::max(lhs, entry.pram() ); } );
		}

	private:
		const pointer 		m_buff;
		const size_type		m_extend;
	};

	template<typename T, typename ... Args>
	NetworkTemplate<T> MakeNetworkTemplate(T * buff, typename NetworkTemplate<T>::size_type extend, Args&&...  args)
	{
		return NetworkTemplate<T>( buff, extend, std::forward<Args>(args)... );
	}
}

#endif