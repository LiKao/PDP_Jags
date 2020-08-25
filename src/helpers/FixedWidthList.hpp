#ifndef FIXEDWIDTHLIST_HPP
#define FIXEDWIDTHLIST_HPP

#include <iterator>

#include "MemorySection.hpp"

namespace PDP {

	template<typename T, typename S, typename SizeField = const size_t>
	class FWList {
	public:
		typedef T															value_type;
		typedef S 															storage_type;
		typedef typename std::add_const<storage_type>::type 				const_storage_type;
		typedef typename std::add_pointer<storage_type>::type				buffer_type;
		typedef typename std::add_const<value_type>::type					const_value_type;
		typedef typename std::add_pointer<value_type>::type 				pointer;
		typedef typename std::add_pointer<const_value_type>::type 			const_pointer;
		typedef typename std::add_lvalue_reference<value_type>::type 		reference;
		typedef typename std::add_lvalue_reference<const_value_type>::type 	const_reference;
		typedef size_t														size_type;

		typedef MemorySection<storage_type>									raw_type;
		typedef MemorySection<const_storage_type>							const_raw_type;


		class iterator {
		public:
			typedef FWList::value_type									value_type;
			typedef void												pointer_type;
			typedef void 												reference_type;
			typedef std::forward_iterator_tag							iterator_category;
			typedef void 												difference_type;

			iterator(buffer_type buff) 
			: m_buff(  buff )
			{}
			iterator(const iterator & rhs) = default;
			iterator(iterator && rhs) = default;
			

			value_type operator*() {
				return value_type( m_buff );
			}


			iterator & operator++()
			{
				m_buff += value_type::static_extend();
				return *this;
			}

			iterator operator++(int) {
				auto tmp = *this;
				++(*this);
				return tmp;
			}

			bool operator==(const iterator & rhs) {
				return m_buff == rhs.m_buff;
			}

			bool operator!=(const iterator & rhs) {
				return m_buff != rhs.m_buff;
			}
		private:
			buffer_type m_buff;
		};

		typedef std::reverse_iterator<iterator>								reverse_iterator;


		FWList(const buffer_type buff, SizeField size)
		: m_buff(buff), m_size(size)
		{}

		const_raw_type 	raw() const { return const_raw_type(m_buff, m_size * value_type::static_extend()); }
		raw_type 		raw() 		{ return raw_type(m_buff, m_size * value_type::static_extend()); }

		iterator  			begin() 	const 	{ return iterator( m_buff ); }
		iterator 			end()   	const 	{ return iterator( m_buff + m_size * value_type::static_extend() ); }
		iterator  			cbegin() 	const 	{ return iterator( m_buff ); }
		iterator 			cend()   	const 	{ return iterator( m_buff + m_size * value_type::static_extend() ); }
		reverse_iterator  	rbegin() 	const 	{ return reverse_iterator( const_iterator( m_buff ) ); }
		reverse_iterator	rend()   	const 	{ return reverse_iterator( const_iterator( m_buff + m_size * value_type::static_extend() ) ); }
		reverse_iterator	crbegin() 	const 	{ return reverse_iterator( const_iterator( m_buff ) ); }
		reverse_iterator	crend()   	const 	{ return reverse_iterator( const_iterator( m_buff + m_size * value_type::static_extend() ) ); }

		template<typename ... Args>
		void emplace_back(Args&&... args) {
			T( raw().end(), std::forward<Args>(args)... );
			m_size += 1;
		}

	private:
		const buffer_type	 				m_buff;
		SizeField							m_size;
	};
}

#endif // FIXEDWIDTHLIST_HPP