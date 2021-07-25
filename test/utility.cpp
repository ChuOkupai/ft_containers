#include <CppUTest/TestHarness.h>
#include "utility.hpp"

TEST_GROUP(utility)
{};

TEST(utility, pair)
{
	ft::pair<int, int> p;
	CHECK(p.first == 0 && p.second == 0);

	ft::pair<int, int> p2(5, 9);
	CHECK(p2.first == 5 && p2.second == 9);

	ft::pair<int, char> p3(65535, 'a');
	CHECK(p3.first == 65535 && p3.second == 'a');

	ft::pair<int, int> p4 = ft::make_pair(1, 2);
	CHECK(p4.first == 1 && p4.second == 2);

	ft::pair<int, int> p5 = p2, p6(9, 5);

	CHECK((p2 == p5) == true);
	CHECK((p5 != p6) == true);
	CHECK((p5 < p6) == true);
	CHECK((p6 > p5) == true);
	CHECK((p2 <= p5) == true);
	CHECK((p2 >= p5) == true);
}
