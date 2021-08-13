#pragma once
#include <functional>

namespace ft
{
	template<class Pair>
	struct _select_first : public std::unary_function<Pair, typename Pair::first_type>
	{
		typedef typename Pair::first_type value_type;

		value_type &operator()(Pair &p) const
		{
			return p.first;
		}

		const value_type &operator()(const Pair &p) const
		{
			return p.first;
		}
	};

	template<class T>
	struct identity : public std::unary_function<T, T>
	{
		typedef T value_type;

		const value_type &operator()(const value_type &value) const
		{
			return value;
		}
	};
}
