#pragma once
#include <memory>
#include <stdexcept>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
	template<class T>
	class _vector_iterator : public iterator<std::random_access_iterator_tag, T>
	{
		typedef iterator<std::random_access_iterator_tag, T> traits;

	public:
		typedef typename traits::iterator_category	iterator_category;
		typedef typename traits::value_type			value_type;
		typedef typename traits::difference_type	difference_type;
		typedef typename traits::pointer			pointer;
		typedef typename traits::reference			reference;

		_vector_iterator(pointer pos = NULL) :
		p(pos)
		{}

		template<class U>
		_vector_iterator(const _vector_iterator<U> &other)
		{
			*this = other;
		}

		~_vector_iterator()
		{}

		template<class U>
		_vector_iterator &operator=(const _vector_iterator<U> &other)
		{
			p = other.base();
			return *this;
		}

		pointer base() const
		{
			return p;
		}

		reference operator*() const
		{
			return *p;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		_vector_iterator &operator++()
		{
			++p;
			return *this;
		}

		_vector_iterator operator++(int)
		{
			_vector_iterator tmp = *this;
			++p;
			return tmp;
		}

		_vector_iterator &operator--()
		{
			--p;
			return *this;
		}

		_vector_iterator operator--(int)
		{
			_vector_iterator tmp = *this;
			--p;
			return tmp;
		}

		_vector_iterator operator+(difference_type n) const
		{
			return _vector_iterator(p + n);
		}

		_vector_iterator operator-(difference_type n) const
		{
			return _vector_iterator(p - n);
		}

		_vector_iterator &operator+=(difference_type n)
		{
			p += n;
			return *this;
		}

		_vector_iterator &operator-=(difference_type n)
		{
			p -= n;
			return *this;
		}

		// Non-member functions:
		template<class U>
		friend inline bool operator==(const _vector_iterator &x, const _vector_iterator<U> &y)
		{
			return x.base() == y.base();
		}

		template<class U>
		friend inline bool operator!=(const _vector_iterator &x, const _vector_iterator<U> &y)
		{
			return !(x == y);
		}

		template<class U>
		friend inline bool operator<(const _vector_iterator &x, const _vector_iterator<U> &y)
		{
			return x.base() < y.base();
		}

		template<class U>
		friend inline bool operator<=(const _vector_iterator &x, const _vector_iterator<U> &y)
		{
			return !(x > y);
		}

		template<class U>
		friend inline bool operator>(const _vector_iterator &x, const _vector_iterator<U> &y)
		{
			return y < x;
		}

		template<class U>
		friend inline bool operator>=(const _vector_iterator &x, const _vector_iterator<U> &y)
		{
			return !(x < y);
		}

		template<class U>
		friend inline difference_type operator-(const _vector_iterator &x, const _vector_iterator<U> &y)
		{
			return x.base() - y.base();
		}

		friend inline _vector_iterator operator+(difference_type n, const _vector_iterator &it)
		{
			return it + n;
		}

	private:
		pointer p;
	};

	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer 		const_pointer;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef _vector_iterator<T>						iterator;
		typedef _vector_iterator<const T>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		explicit vector(const Allocator &alloc = Allocator()) :
		_allocator(alloc), _array(NULL), _capacity(0), _size(0)
		{}

		explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator()) :
		_allocator(alloc), _array(NULL), _capacity(0), _size(0)
		{
			insert(begin(), count, value);
		}

		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator &alloc = Allocator()) :
		_allocator(alloc), _array(NULL), _capacity(0), _size(0)
		{
			insert(begin(), first, last);
		}

		vector(const vector &other) :
		_allocator(other._allocator), _array(NULL), _capacity(0), _size(0)
		{
			*this = other;
		}

		~vector()
		{
			clear();
			if (_array)
				_allocator.deallocate(_array, capacity());
		}

		vector &operator=(const vector &other)
		{
			assign(other.begin(), other.end());
			return *this;
		}

		void assign(size_type count, const T &value)
		{
			clear();
			insert(begin(), count, value);
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last)
		{
			clear();
			insert(begin(), first, last);
		}

		allocator_type get_allocator() const
		{
			return _allocator;
		}

		// Element access:
		reference at(size_type pos)
		{
			check_range(pos);
			return _array[pos];
		}

		const_reference at(size_type pos) const
		{
			check_range(pos);
			return _array[pos];
		}

		reference operator[](size_type pos)
		{
			return _array[pos];
		}

		const_reference operator[](size_type pos) const
		{
			return _array[pos];
		}

		reference front()
		{
			return *_array;
		}

		const_reference front() const
		{
			return *_array;
		}

		reference back()
		{
			return _array[size() - 1];
		}

		const_reference back() const
		{
			return _array[size() - 1];
		}

		// Iterators:
		iterator begin()
		{
			return iterator(_array);
		}

		const_iterator begin() const
		{
			return const_iterator(_array);
		}

		iterator end()
		{
			return begin() + size();
		}

		const_iterator end() const
		{
			return begin() + size();
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		// Capacity:
		bool empty() const
		{
			return !size();
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return _allocator.max_size();
		}

		void reserve(size_type n)
		{
			if (n > max_size())
				throw (std::length_error("ft::vector::reserve invalid length"));
			if (n > capacity())
				realloc(n);
		}

		size_type capacity() const
		{
			return _capacity;
		}

		// Modifiers:
		void clear()
		{
			erase(begin(), end());
		}

		iterator insert(iterator pos, const T &value)
		{
			difference_type i = pos - begin();
			insert(pos, 1, value);
			return begin() + i;
		}

		void insert(iterator pos, size_type count, const T &value)
		{
			pos = prepare_insert(pos, count);
			for (iterator last = pos + count; pos != last; ++pos)
				_allocator.construct(pos.base(), value);
		}

		template<class InputIt>
		typename enable_if<_is_exactly_input_iterator<InputIt>::value>::type
		insert(iterator pos, InputIt first, InputIt last)
		{
			for (; first != last; ++first)
				pos = insert(pos, *first) + 1;
		}

		template<class InputIt>
		typename enable_if<_is_forward_iterator<InputIt>::value>::type
		insert(iterator pos, InputIt first, InputIt last)
		{
			for (pos = prepare_insert(pos, ft::distance(first, last)); first != last; ++pos, ++first)
				_allocator.construct(pos.base(), *first);
		}

		iterator erase(iterator pos)
		{
			return erase(pos, pos + 1);
		}

		iterator erase(iterator first, iterator last)
		{
			iterator		i, j;
			difference_type	n = ft::distance(first, last);
			for (i = first; i != last; ++i)
				_allocator.destroy(i.base());
			for (i = first, j = last; j != end(); ++i, ++j)
			{
				_allocator.construct(i.base(), *j);
				_allocator.destroy(j.base());
			}
			_size -= n;
			return first;
		}

		void push_back(const T &value)
		{
			insert(end(), value);
		}

		void pop_back()
		{
			erase(--end());
		}

		void resize(size_type count, T value = T())
		{
			if (count > size())
				insert(end(), count - size(), value);
			else if (count < size())
				erase(begin() + count, end());
		}

		void swap(vector &other)
		{
			ft::swap(_allocator, other._allocator);
			ft::swap(_array, other._array);
			ft::swap(_capacity, other._capacity);
			ft::swap(_size, other._size);
		}

		// Non-member functions:
		friend inline bool operator==(const vector &x, const vector &y)
		{
			return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
		}

		friend inline bool operator!=(const vector &x, const vector &y)
		{
			return !(x == y);
		}

		friend inline bool operator<(const vector &x, const vector &y)
		{
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}

		friend inline bool operator<=(const vector &x, const vector &y)
		{
			return !(x > y);
		}

		friend inline bool operator>(const vector &x, const vector &y)
		{
			return y < x;
		}

		friend inline bool operator>=(const vector &x, const vector &y)
		{
			return !(x < y);
		}

		friend inline void swap(vector &x, vector &y)
		{
			x.swap(y);
		}

	private:
		allocator_type	_allocator;
		pointer			_array;
		size_type		_capacity;
		size_type		_size;

		void check_range(size_type i) const
		{
			if (i >= size())
				throw (std::out_of_range("ft::vector::at out of range exception"));
		}

		iterator prepare_insert(iterator pos, size_type count)
		{
			if (size() + count > capacity())
			{
				difference_type i = pos - begin();
				realloc(ft::max(size() + count, 2 * size()), i, count);
				pos = begin() + i;
			}
			else
				for (pointer i = end().base(); i-- != pos.base();)
				{
					_allocator.construct(i + count, *i);
					_allocator.destroy(i);
				}
			_size += count;
			return pos;
		}

		void realloc(size_type new_capacity, size_type begin_index = 0, size_type count = 0)
		{
			value_type *tmp = _allocator.allocate(new_capacity);
			for (size_type i = 0; i < begin_index; ++i)
			{
				_allocator.construct(tmp + i, _array[i]);
				_allocator.destroy(_array + i);
			}
			for (size_type i = begin_index; i < size(); ++i)
			{
				_allocator.construct(tmp + i + count, _array[i]);
				_allocator.destroy(_array + i);
			}
			if (_array)
				_allocator.deallocate(_array, capacity());
			_array = tmp;
			_capacity = new_capacity;
		}
	};
}
