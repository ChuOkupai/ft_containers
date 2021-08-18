#pragma once
#include "vector.hpp"

namespace ft
{
	template<class T, class Container = vector<T> >
	class stack
	{
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		explicit stack(const Container &cont = Container()) :
		c(cont)
		{}

		~stack()
		{}

		// Element access:
		reference top()
		{
			return c.back();
		}

		const_reference top() const
		{
			return c.back();
		}

		// Capacity:
		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		// Modifiers:
		void push(const T &value)
		{
			c.push_back(value);
		}

		void pop()
		{
			c.pop_back();
		}

		// Non-member functions:
		friend inline bool operator==(const stack &x, const stack &y)
		{
			return x.c == y.c;
		}

		friend inline bool operator!=(const stack &x, const stack &y)
		{
			return !(x == y);
		}

		friend inline bool operator<(const stack &x, const stack &y)
		{
			return x.c < y.c;
		}

		friend inline bool operator<=(const stack &x, const stack &y)
		{
			return !(x > y);
		}

		friend inline bool operator>(const stack &x, const stack &y)
		{
			return y < x;
		}

		friend inline bool operator>=(const stack &x, const stack &y)
		{
			return !(x < y);
		}

	protected:
		Container c;
	};
}
