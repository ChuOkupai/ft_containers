#pragma once

namespace ft
{
	template<class InputIt1, class InputIt2>
	inline bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)
				return 0;
		return 1;
	}

	template<class InputIt1, class InputIt2>
	inline bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
			if (*first1 < *first2)
				return 1;
			else if (*first2 < *first1)
				return 0;
		return first1 == last1 && first2 != last2;
	}

	template<class T>
	inline const T &max(const T &a, const T &b)
	{
		return a > b ? a : b;
	}

	template<class T>
	inline const T &min(const T &a, const T &b)
	{
		return a < b ? a : b;
	}

	template<class T>
	inline void swap(T &a, T &b)
	{
		T c = a;
		a = b;
		b = c;
	}
}
