#pragma once
#include <cstddef>
#include <iterator>
#include "type_traits.hpp"

namespace ft
{
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template<class T>
	struct _has_iterator_typedefs
	{
	private:
		typedef char yes[1];
		typedef char no[2];
		template<class _Up> static no &test(...);
		template<class _Up> static yes &test(
			typename _void_t<typename _Up::iterator_category>::type* = 0,
			typename _void_t<typename _Up::value_type>::type* = 0,
			typename _void_t<typename _Up::difference_type>::type* = 0,
			typename _void_t<typename _Up::pointer>::type* = 0,
			typename _void_t<typename _Up::reference>::type* = 0
		);

	public:
		static const bool value = sizeof(test<T>(0, 0, 0, 0, 0)) == sizeof(yes);
	};

	template<class T>
	struct _has_iterator_category
	{
	private:
		typedef char yes[1];
		typedef char no[2];
		template<class _Up> static no &test(...);
		template<class _Up> static yes &test(typename _Up::iterator_category* = 0);

	public:
		static const bool value = sizeof(test<T>(0)) == sizeof(yes);
	};

	template<class Iter, bool> struct _iterator_traits_impl {};

	template<class Iter>
	struct _iterator_traits_impl<Iter, true>
	{
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template<class Iter, bool>
	struct _iterator_traits {};

	template<class Iter>
	struct _iterator_traits<Iter, true> : _iterator_traits_impl<Iter,
	is_convertible<typename Iter::iterator_category, std::input_iterator_tag>::value || is_convertible<typename Iter::iterator_category, std::output_iterator_tag>::value> {};

	template<class Iter>
	struct iterator_traits : _iterator_traits<Iter, _has_iterator_typedefs<Iter>::value> {};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef typename remove_cv<T>::type		value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T& 								reference;
	};

	template<class From, class To, bool = _has_iterator_category<iterator_traits<From> >::value>
	struct _has_iterator_category_convertible_to : public integral_constant<bool, is_convertible<typename iterator_traits<From>::iterator_category, To>::value> {};

	template<class From, class To>
	struct _has_iterator_category_convertible_to<From, To, false> : public false_type {};

	template<class Iter>
	struct _is_bidirectional_iterator : public _has_iterator_category_convertible_to<Iter, std::bidirectional_iterator_tag> {};

	template<class Iter>
	struct _is_forward_iterator : public _has_iterator_category_convertible_to<Iter, std::forward_iterator_tag> {};

	template<class Iter>
	struct _is_input_iterator : public _has_iterator_category_convertible_to<Iter, std::input_iterator_tag> {};

	template<class Iter>
	struct _is_random_access_iterator : public _has_iterator_category_convertible_to<Iter, std::random_access_iterator_tag> {};

	template<class Iter>
	struct _is_exactly_input_iterator : public integral_constant<bool, _is_input_iterator<Iter>::value && !_is_forward_iterator<Iter>::value> {};

	template<class InputIt>
	inline typename enable_if<_is_input_iterator<InputIt>::value && !_is_random_access_iterator<InputIt>::value, typename iterator_traits<InputIt>::difference_type>::type
	distance(InputIt first, InputIt last)
	{
		typename iterator_traits<InputIt>::difference_type n;
		for (n = 0; first != last; ++first, ++n);
		return n;
	}

	template<class InputIt>
	inline typename enable_if<_is_random_access_iterator<InputIt>::value, typename iterator_traits<InputIt>::difference_type>::type
	distance(InputIt first, InputIt last)
	{
		return last - first;
	}

	template<class Iter>
	class reverse_iterator : public iterator<typename iterator_traits<Iter>::iterator_category, typename iterator_traits<Iter>::value_type,
	typename iterator_traits<Iter>::difference_type, typename iterator_traits<Iter>::pointer, typename iterator_traits<Iter>::reference>
	{
		typedef iterator_traits<Iter> traits;

	public:
		typedef Iter								iterator_type;
		typedef typename traits::iterator_category	iterator_category;
		typedef typename traits::difference_type	value_type;
		typedef typename traits::difference_type	difference_type;
		typedef typename traits::pointer			pointer;
		typedef typename traits::reference			reference;

		reverse_iterator() :
		current(iterator_type())
		{}

		explicit reverse_iterator(iterator_type x) :
		current(x)
		{}

		template<class Iter2>
		reverse_iterator(const reverse_iterator<Iter2> &other)
		{
			*this = other;
		}

		~reverse_iterator()
		{}

		template<class Iter2>
		reverse_iterator &operator=(const reverse_iterator<Iter2> &other)
		{
			current = other.base();
			return *this;
		}

		iterator_type base() const
		{
			return current;
		}

		reference operator*() const
		{
			iterator_type tmp = current;
			return *--tmp;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return base()[- n - 1];
		}

		reverse_iterator &operator++()
		{
			--current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--current;
			return tmp;
		}

		reverse_iterator &operator--()
		{
			++current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++current;
			return tmp;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(current - n);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current + n);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		// Non-member functions:
		template<class Iter2>
		friend inline bool operator==(const reverse_iterator &x, const reverse_iterator<Iter2> &y)
		{
			return x.base() == y.base();
		}

		template<class Iter2>
		friend inline bool operator!=(const reverse_iterator &x, const reverse_iterator<Iter2> &y)
		{
			return !(x == y);
		}

		template<class Iter2>
		friend inline bool operator<(const reverse_iterator &x, const reverse_iterator<Iter2> &y)
		{
			return x.base() > y.base();
		}

		template<class Iter2>
		friend inline bool operator<=(const reverse_iterator &x, const reverse_iterator<Iter2> &y)
		{
			return !(x > y);
		}

		template<class Iter2>
		friend inline bool operator>(const reverse_iterator &x, const reverse_iterator<Iter2> &y)
		{
			return y < x;
		}

		template<class Iter2>
		friend inline bool operator>=(const reverse_iterator &x, const reverse_iterator<Iter2> &y)
		{
			return !(x < y);
		}

		template<class Iter2>
		friend inline difference_type operator-(const reverse_iterator &x, const reverse_iterator<Iter2> &y)
		{
			return y.base() - x.base();
		}

		friend inline reverse_iterator operator+(difference_type n, const reverse_iterator &it)
		{
			return it + n;
		}

	protected:
		iterator_type current;
	};
}
