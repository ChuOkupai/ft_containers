#pragma once

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		T1	first;
		T2	second;

		pair() :
		first(), second()
		{}

		pair(const T1 &x, const T2 &y) :
		first(x), second(y)
		{}

		template<class U1, class U2>
		pair(const pair<U1, U2> &p) :
		first(p.first), second(p.second)
		{}

		friend inline bool operator==(const pair &x, const pair &y)
		{
			return x.first == y.first && x.second == y.second;
		}

		friend inline bool operator!=(const pair &x, const pair &y)
		{
			return !(x == y);
		}

		friend inline bool operator<(const pair &x, const pair &y)
		{
			return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
		}

		friend inline bool operator<=(const pair &x, const pair &y)
		{
			return !(x > y);
		}

		friend inline bool operator>(const pair &x, const pair &y)
		{
			return y < x;
		}

		friend inline bool operator>=(const pair &x, const pair &y)
		{
			return !(x < y);
		}
	};

	template<class T1, class T2>
	inline pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return (pair<T1, T2>(t, u));
	}
}
