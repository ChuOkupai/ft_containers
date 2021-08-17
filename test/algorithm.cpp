#include "tester.hpp"
#include "algorithm.hpp"
#include <algorithm>
#include <string>

TEST_GROUP(algorithm)
{};

static bool is_palindrome(const std::string &s)
{
	return NAMESPACE::equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
}

TEST(algorithm, equal)
{
	CHECK(is_palindrome("test") == false);
	CHECK(is_palindrome("radar") == true);
	CHECK(is_palindrome("abcde dcba") == false);
	CHECK(is_palindrome("abcdeedcba") == true);
}

static bool compare(const std::string &s1, const std::string &s2)
{
	return NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
}

TEST(algorithm, lexicographical_compare)
{
	CHECK(compare("Apple", "apartment") == true);
	CHECK(compare("apple", "apartment") == false);
	CHECK(compare("xyZzz", "xyzzz") == true);
	CHECK(compare("xyzzz", "xyzzz") == false);
	CHECK(compare("test", "test") == false);
}

struct my_int8
{
	char value;

	my_int8(const char v) :
	value(v)
	{}

	friend inline bool operator==(const my_int8 &x, const my_int8 &y)
	{
		return x.value == y.value;
	}

	friend inline bool operator!=(const my_int8 &x, const my_int8 &y)
	{
		return !(x == y);
	}

	friend inline bool operator<(const my_int8 &x, const my_int8 &y)
	{
		return x.value < y.value;
	}

	friend inline bool operator<=(const my_int8 &x, const my_int8 &y)
	{
		return !(x > y);
	}

	friend inline bool operator>(const my_int8 &x, const my_int8 &y)
	{
		return y < x;
	}

	friend inline bool operator>=(const my_int8 &x, const my_int8 &y)
	{
		return !(x < y);
	}
};

TEST(algorithm, max)
{
	CHECK(NAMESPACE::max(0, 5) == 5);
	CHECK(NAMESPACE::max(5, 0) == 5);
	CHECK(NAMESPACE::max(-3, -6) == -3);
	CHECK(NAMESPACE::max(-8, 17) == 17);
	CHECK(NAMESPACE::max(7U, 6U) == 7U);
	CHECK(NAMESPACE::max(0U, 12U) == 12U);
	CHECK(NAMESPACE::max(12U, 0U) == 12U);
	CHECK(NAMESPACE::max(21L, 42L) == 42L);
	CHECK(NAMESPACE::max(my_int8(8), my_int8(12)) == my_int8(12));
}

TEST(algorithm, min)
{
	CHECK(NAMESPACE::min(0, 5) == 0);
	CHECK(NAMESPACE::min(5, 0) == 0);
	CHECK(NAMESPACE::min(-3, -6) == -6);
	CHECK(NAMESPACE::min(-8, 17) == -8);
	CHECK(NAMESPACE::min(7U, 6U) == 6U);
	CHECK(NAMESPACE::min(0U, 12U) == 0U);
	CHECK(NAMESPACE::min(12U, 0U) == 0U);
	CHECK(NAMESPACE::min(21L, 42L) == 21L);
	CHECK(NAMESPACE::min(my_int8(8), my_int8(12)) == my_int8(8));
}

TEST(algorithm, swap)
{
	int a = 0, b = 1;
	NAMESPACE::swap(a, b);
	CHECK(a == 1 && b == 0);
	long c = -1, d = 9;
	NAMESPACE::swap(c, d);
	CHECK(c == 9 && d == -1);

	my_int8 e(7), f(-2);
	NAMESPACE::swap(e, f);
	CHECK(e == my_int8(-2) && f == my_int8(7));
}
