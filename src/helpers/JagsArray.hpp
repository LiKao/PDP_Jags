#include <vector>
#include <numeric>
#include <functional>
#include <type_traits>
#include <memory>
#include <algorithm>
#include <cstring>

#include <iostream>

#include <boost/operators.hpp>

#include <util/dim.h>

#include "helpers/Assert.hpp"

namespace PDP {
	// A simple helper that allows us to use a Multidim JagsArray
	// as if it were a C++ Structure
	// NOTE: Indexing is reversed compared to JAGS indexing!!
	template<typename T>
	struct _JagsArray {
		typedef const std::vector<unsigned int> 								dim_type;
		typedef T																value_type;
		typedef typename std::add_const<value_type>::type 						const_value_type;
		typedef typename std::add_lvalue_reference<value_type>::type 			reference;
		typedef typename std::add_lvalue_reference<const_value_type>::type 		const_reference;
		typedef typename std::add_pointer<value_type>::type             		pointer;
		typedef typename std::add_pointer<const_value_type>::type             	const_pointer;
		typedef dim_type::size_type												level_type;
		typedef dim_type::value_type											size_type;

		friend class _JagsArray<typename std::add_const<value_type>::type>;

		struct iterator : private boost::equivalent<iterator>, boost::totally_ordered<iterator> {
			typedef typename std::make_signed<size_type>::type 		difference_type;
			typedef _JagsArray::value_type 							value_type;
			typedef _JagsArray 										reference;
			typedef _JagsArray::pointer 							pointer;
			typedef std::random_access_iterator_tag					iterator_category;


			iterator(_JagsArray & array, difference_type pos = 1) : m_array(array), m_pos(pos) {}
			iterator(_JagsArray && array, difference_type pos = 1) : m_array(std::move(array)), m_pos(pos) {};

			iterator(const iterator & rhs) : m_array(rhs.m_array), m_pos(rhs.m_pos) {}
			iterator(iterator && rhs) : m_array(std::move(rhs.m_array)), m_pos(rhs.m_pos) {}

			reference operator*() { return m_array[m_pos]; }

			iterator operator+(difference_type d) { return iterator(m_array, m_pos + d); }
			iterator operator-(difference_type d) { return *this + (-d); }

			difference_type operator-(const iterator & rhs) const { return m_pos - rhs.mpos; }

			iterator & operator+=(difference_type d) {
				m_pos += d;
				return *this;
			}
			iterator & operator-=(difference_type d) { return (*this) += (-d); }

			iterator & operator++()
			{
				++m_pos;
				return *this;
			}
			iterator & operator--(){
				--m_pos;
				return *this;
			}
			iterator operator++(int) {
				iterator tmp = this;
				++(*this);
				return tmp;
			}
			iterator operator--(int) {
				iterator tmp = this;
				--(*this);
				return tmp;
			}

			bool operator<(const iterator & rhs) const {
				return m_pos < rhs.m_pos;
			}

		private:
			_JagsArray m_array;
			difference_type m_pos;
		};

		typedef typename _JagsArray<typename std::add_const<value_type>::type>::iterator 	const_iterator;

		static dim_type drop(dim_type & d) 
		{
			if((d.size() == 1) && (d[0] == 1)) {
				return dim_type();
			}
			return d;
		}

		_JagsArray(pointer ptr, const dim_type & dims) : 
			m_level(0), m_dims(std::make_shared<dim_type>(drop(dims))), m_ptr(ptr), m_index(1)
		{}

		_JagsArray(const _JagsArray & rhs) :
			m_level(rhs.m_level), m_dims(rhs.m_dims), m_ptr(rhs.m_ptr), m_index(rhs.m_index)
		{}
		_JagsArray(_JagsArray && rhs) : 
			m_level(rhs.m_level), m_dims(std::move(rhs.m_dims)), m_ptr(std::move(rhs.m_ptr)), m_index(rhs.m_index)
		{}
		template<typename U = value_type>
		_JagsArray(const _JagsArray<typename std::remove_const<typename std::enable_if<std::is_const<value_type>::value,U>::type>::type> & rhs) :
			m_level(rhs.m_level), m_dims(rhs.m_dims), m_ptr(rhs.m_ptr), m_index(rhs.m_index)
		{}


		const_reference operator*() const { return *m_ptr; }
		const_pointer get() const { return m_ptr; }
		
		dim_type & dims() const { return *m_dims; }
		size_type  size() const { return (level() < dims().size()) ? *(m_dims->rbegin() + level()) : 1; }

		level_type level() const { return m_level; }
		level_type depth() const { return dims().size() - level(); }

		size_type stride() const {
			Assert((level() <= dims().size()), "Nesting too deep in JagsArray", std::out_of_range);
			return std::accumulate(m_dims->begin(), m_dims->end() - level(), 1, std::multiplies<size_type>());
		}

		_JagsArray<typename std::add_const<value_type>::type>
		operator[](size_type i) const 
		{ 
			// if we dereference a zero dim array with index 1, we still make it work
			// this removes some additional checks in other code
			if((depth() == 0) && (i == 1)) {
				return _JagsArray<typename std::add_const<value_type>::type>(*this);
			}
			return _JagsArray<typename std::add_const<value_type>::type>(this, i);
		}

		template<typename U = value_type>
		typename std::enable_if<!std::is_const<U>::value,_JagsArray>::type
		operator[](size_type i) 
		{ 
			if((depth() == 0) && (i == 1)) {
				return *this;
			}
			return _JagsArray(this, i); 
		}

		template<typename U = value_type>
		typename std::enable_if<!std::is_const<U>::value,reference>::type
		operator*() { return *m_ptr; }

		template<typename U = value_type>
		typename std::enable_if<!std::is_const<U>::value,pointer>::type
		get() { return m_ptr; }

		template<typename U = value_type>
		typename std::enable_if<!std::is_const<U>::value,value_type>::type
		operator=(value_type val) 
		{
			*m_ptr = val;
			return val;
		}

		template<typename U = value_type, typename V = typename std::enable_if<!std::is_const<U>::value,_JagsArray &>::type>
		V & copy(const _JagsArray & rhs) 
		{
			copy(_JagsArray<typename std::add_const<value_type>::type>(rhs));
			return *this;
		}

		template<typename U = value_type, typename V = typename std::enable_if<!std::is_const<U>::value,_JagsArray &>::type>
		V copy(const _JagsArray<typename std::add_const<value_type>::type> & rhs) 
		{
			Assert(depth() >= rhs.depth(), "Insufficient depth in JagsArray::copy", std::invalid_argument);
			if(depth() == rhs.depth()) {
				if(get() != rhs.get()) {
					Assert(stride() == rhs.stride(), "Incompatible arrays in JagsArray::copy", std::invalid_argument);
					std::memcpy(get(), rhs.get(), stride()*sizeof(value_type));
				}
			} 
			else {
				std::for_each(begin(), end(), [&rhs](auto arr){ arr.copy( rhs ); });
			}
			return *this;
		}

		iterator       begin()        { return iterator(*this); }
		const_iterator begin()  const { return cbegin(); }
		const_iterator cbegin() const { return _JagsArray<typename std::add_const<value_type>::type>(*this).begin(); }
		
		iterator       end()        { return iterator(*this) + size(); }
		const_iterator end()  const { return cend(); }
		const_iterator cend() const { return _JagsArray<typename std::add_const<value_type>::type>(*this).end(); }

		size_type index() const { return m_index; }

		operator value_type() const { return *m_ptr; }

		/*void apply_at(size_t tdepth) {
			std::cout << "Target depth: " << tdepth << std::endl;
			std::cout << "Current depth: " << 
			Assert(depth() >= tdepth, "Target depth to large in JagsArray::apply_at", std::out_of_range);
			if(depth == tdepth) {

			}
			else {
				std::for_each(begin(),end(),
			}
		}*/

		template<typename U, typename Func>
		void for_each_block(const _JagsArray<U> & rhs, level_type blocksize, const Func & f)
		{
			if(rhs.depth() == blocksize) {
				f(*this, rhs);
				return;
			}
			for(auto arr: rhs) {
				(*this)[arr.index()].for_each_block(arr, blocksize, f);
			}
		}

		template<typename U, typename Func>
		void for_each(const _JagsArray<U> & rhs, const Func & f, level_type at = 0)
		{
			if(at > 0) {
				for(auto arr: *this) {
					arr.for_each(rhs, f, at - 1);
				}
				return;
			}
			if(rhs.depth() == 0) {
				f(*this, *rhs);
				return;
			}
			for(auto arr: rhs) {
				(*this)[arr.index()].for_each(arr, f);
			}
		}

	private:
		_JagsArray(_JagsArray * arr, size_type _index) :
			m_level(arr->level() + 1), m_dims(arr->m_dims),
			m_ptr(arr->get() + stride()*(_index-1)), m_index(_index)
		{
			Assert((level() <= dims().size()), "Nesting too deep in JagsArray", std::out_of_range);
			Assert((index() <= arr->size()), "Index out of bound in JagsArray", std::out_of_range);
		}

		_JagsArray(const _JagsArray * arr, size_type _index) :
			m_level(arr->level() + 1), m_dims(arr->m_dims),
			m_ptr(arr->get() + stride()*(_index-1)), m_index(_index)
		{
			Assert((level() <= dims().size()), "Nesting too deep in JagsArray", std::out_of_range);
			Assert((index() <= arr->size()), "Index out of bound in JagsArray", std::out_of_range);
		}

		const level_type 				m_level;
		const std::shared_ptr<dim_type>	m_dims;
		const pointer 					m_ptr;
		const size_type					m_index;
	};

	template<typename T> 
	_JagsArray<T> JagsArray(T * ptr, const typename _JagsArray<T>::dim_type & dims) {
		return _JagsArray<T>(ptr, dims);
	}
}