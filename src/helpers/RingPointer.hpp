#ifndef RINGPOINTER_HPP
#define RINGPOINTER_HPP

#include <functional>
#include <algorithm>
#include <numeric>

#include <boost/operators.hpp>

#include "helpers/Assert.hpp"

namespace PDP {
	template<typename T>
	auto product(T && _begin, T && _end) {
		return std::accumulate(_begin, _end, static_cast<typename T::value_type>( 1 ), std::multiplies<typename T::value_type>() );
	}

	template<typename T>
	auto product(T && dims) {
		return product( begin(dims), end(dims) );
	}



	template<typename T>
	struct RingPointer : public boost::addable2<RingPointer<T>, size_t>{
	public:
		typedef T																value_type;
		typedef typename std::add_const<value_type>::type 						const_value_type;
		typedef typename std::add_lvalue_reference<value_type>::type 			reference;
		typedef typename std::add_lvalue_reference<const_value_type>::type 		const_reference;
		typedef typename std::add_pointer<value_type>::type             		pointer;
		typedef typename std::add_pointer<const_value_type>::type             	const_pointer;
		typedef size_t															size_type;

		class iterator : 
			public boost::addable2<iterator,int>, 
			public boost::partially_ordered<iterator> {
		public:
			typedef RingPointer::value_type 										value_type;
			typedef int 															difference_type;
			typedef typename std::add_const<value_type>::type 						const_value_type;
			typedef typename std::add_lvalue_reference<value_type>::type 			reference;
			typedef typename std::add_lvalue_reference<const_value_type>::type 		const_reference;
			typedef typename std::add_pointer<value_type>::type             		pointer;
			typedef typename std::add_pointer<const_value_type>::type             	const_pointer;
			typedef std::forward_iterator_tag										iterator_category;

			iterator(const RingPointer & ptr) 
			: m_ptr( ptr ), m_idx( 0 )
			{}

			iterator(const iterator & rhs) = default;
			iterator(iterator && rhs) = default;

			iterator operator++() {
				++m_idx;
				return *this;
			}

			iterator operator++(int) {
				auto tmp = *this;
				++(*this);
				return tmp;
			}

			iterator operator+=(difference_type i) {
				m_idx += i;
				return *this;
			}


			const_reference operator*() const {
				return *(m_ptr + m_idx);
			}

			bool operator==(const iterator & rhs) const {
				return m_idx == rhs.m_idx;
			}

			bool operator<(const iterator & rhs) const {
				return m_idx < rhs.m_idx;
			}


		private:
			const RingPointer 	m_ptr;
			size_type			m_idx;   
		};

		RingPointer(T * const ptr, size_type entries) :
			m_ptr(ptr), m_entries(entries), m_idx(0)
		{}

		RingPointer(const RingPointer & rhs) = default;
		RingPointer(RingPointer && rhs) = default;

		size_type entries() 	const { return m_entries; }
		size_type idx() 		const { return m_idx; }


		const_pointer get() const { return m_ptr + idx(); }

		iterator begin() const { return iterator(*this); };

		template<typename U = value_type>
		typename std::enable_if<!std::is_const<U>::value,pointer>::type
		get() { return m_ptr + idx(); }

		RingPointer & operator++() {
			m_idx = (m_idx+1) % entries();
			return *this;
		}

		RingPointer operator++(int) {
			auto tmp = *this;
			++(*this);
			return tmp;
		}

		RingPointer operator+=(size_type i) {
			m_idx = (m_idx + i) % entries();
			return *this;
		}


		const_reference operator*() const { return *get(); }

		template<typename U = value_type>
		typename std::enable_if<!std::is_const<U>::value,reference>::type
		operator*() { return *get(); }

	private:
		const pointer 		m_ptr;
		const size_type		m_entries;
		size_type			m_idx;
	};

	template<typename T>
	RingPointer<T> MakeRingPtr(T * ptr, typename RingPointer<T>::size_type entries) {
		return RingPointer<T>(ptr, entries);
	}
}

#endif // RINGPOINTER_HPP