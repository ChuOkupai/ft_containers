#include <CppUTest/TestHarness.h>
#include <string>
#include "algorithm.hpp"

TEST_GROUP(algorithm)
{};

static bool is_palindrome(const std::string &s)
{
	return ft::equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
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
	return ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
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
	CHECK(ft::max(0, 5) == 5);
	CHECK(ft::max(5, 0) == 5);
	CHECK(ft::max(-3, -6) == -3);
	CHECK(ft::max(-8, 17) == 17);
	CHECK(ft::max(7U, 6U) == 7U);
	CHECK(ft::max(0U, 12U) == 12U);
	CHECK(ft::max(12U, 0U) == 12U);
	CHECK(ft::max(21L, 42L) == 42L);
	CHECK(ft::max(my_int8(8), my_int8(12)) == my_int8(12));
}

TEST(algorithm, min)
{
	CHECK(ft::min(0, 5) == 0);
	CHECK(ft::min(5, 0) == 0);
	CHECK(ft::min(-3, -6) == -6);
	CHECK(ft::min(-8, 17) == -8);
	CHECK(ft::min(7U, 6U) == 6U);
	CHECK(ft::min(0U, 12U) == 0U);
	CHECK(ft::min(12U, 0U) == 0U);
	CHECK(ft::min(21L, 42L) == 21L);
	CHECK(ft::min(my_int8(8), my_int8(12)) == my_int8(8));
}

TEST(algorithm, swap)
{
	int a = 0, b = 1;
	ft::swap(a, b);
	CHECK(a == 1 && b == 0);
	long c = -1, d = 9;
	ft::swap(c, d);
	CHECK(c == 9 && d == -1);

	my_int8 e(7), f(-2);
	ft::swap(e, f);
	CHECK(e == my_int8(-2) && f == my_int8(7));
}
