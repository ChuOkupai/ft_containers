#include "tester.hpp"
#include "type_traits.hpp"

TEST_GROUP(type_traits)
{};

template<class T>
typename ft::enable_if<sizeof(T) == 1, bool>::type
static is_byte()
{
	return true;
}

template<class T>
typename ft::enable_if<sizeof(T) != 1, bool>::type
static is_byte()
{
	return false;
}

template<class T>
typename ft::enable_if<sizeof(T) == 1>::type
static set_x(T &v)
{
	v = 'x';
}

template<class T>
typename ft::enable_if<sizeof(T) != 1>::type
static set_x(T &)
{}

TEST(type_traits, enable_if)
{
	CHECK(is_byte<char>() == true);
	CHECK(is_byte<int>() == false);

	char c = 0;
	set_x(c);
	CHECK(c == 'x');
	int n = 0;
	set_x(n);
	CHECK(n == 0);
}

struct fake_integral {};

TEST(type_traits, is_integral)
{
	CHECK(ft::is_integral<bool>::value == true);
	CHECK(ft::is_integral<short>::value == true);
	CHECK(ft::is_integral<int>::value == true);
	CHECK(ft::is_integral<long>::value == true);
	CHECK(ft::is_integral<long long>::value == true);

	CHECK(ft::is_integral<unsigned short>::value == true);
	CHECK(ft::is_integral<unsigned int>::value == true);
	CHECK(ft::is_integral<unsigned long>::value == true);
	CHECK(ft::is_integral<unsigned long long>::value == true);

	CHECK(ft::is_integral<const int>::value == true);
	CHECK(ft::is_integral<volatile int>::value == true);
	CHECK(ft::is_integral<const volatile int>::value == true);

	CHECK(ft::is_integral<float>::value == false);
	CHECK(ft::is_integral<double>::value == false);
	CHECK(ft::is_integral<long double>::value == false);
	CHECK(ft::is_integral<fake_integral>::value == false);
}
