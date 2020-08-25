#ifndef MEMORYSECTION_HPP
#define MEMORYSECTION_HPP

#include <iterator>
#include <type_traits>

namespace PDP {

	template<typename T, typename SizeField = const size_t>
	class MemorySection {
	public:
		typedef T															value_type;
		typedef typename std::add_const<value_type>::type					const_value_type;
		typedef typename std::add_pointer<value_type>::type 				pointer;
		typedef typename std::add_pointer<const_value_type>::type 			const_pointer;
		typedef typename std::add_lvalue_reference<value_type>::type 		reference;
		typedef typename std::add_lvalue_reference<const_value_type>::type 	const_reference;
		typedef size_t														size_type;

		typedef pointer														iterator;
		typedef const_pointer												const_iterator;
		typedef std::reverse_iterator<iterator>								reverse_iterator;
		typedef std::reverse_iterator<const_iterator>						const_reverse_iterator;

		MemorySection(T* buff, SizeField size)
		: m_buff(buff), m_size(size)
		{}
		MemorySection(const MemorySection & rhs) = default;
		MemorySection(MemorySection && rhs) = default;

		iterator 				begin() 		  { return m_buff; }
		const_iterator 			begin() 	const { return m_buff; }
		iterator 				end()			  { return m_buff + size(); }
		const_iterator 			end()		const { return m_buff + size(); }
		const_iterator 			cbegin() 	const { return begin(); }
		const_iterator 			cend()   	const { return end(); }
		reverse_iterator 		rbegin()		  { return reverse_iterator(end()); }
		const_reverse_iterator 	rbegin()	const { return const_reverse_iterator(end()); }
		reverse_iterator		rend()			  { return reverse_iterator(begin()); }
		const_reverse_iterator	rend()		const { return const_reverse_iterator(begin()); }
		const_reverse_iterator	crbegin()	const { return rbegin(); }
		const_reverse_iterator	crend()		const { return rend(); }

		template<typename Iter>
		void insert(typename std::enable_if<!std::is_const<value_type>::value,Iter>::type begin, Iter end) {
			std::move( begin, end, m_buff + size() );
			m_size += end - begin;
		}

		template<typename U>
		void push_back(const typename std::enable_if<!std::is_const<value_type>::value,U>::type & value) {
			m_buff[m_size++] = value;
		}

		size_type size() const { return static_cast<size_type>( m_size ); }

	private:
		const pointer 						m_buff;
		SizeField							m_size;
	};
}

#endif // MEMORYSECTION_HPP