#include "tester.hpp"
#include "utility.hpp"
#include <utility>

TEST_GROUP(utility)
{};

TEST(utility, pair)
{
	NAMESPACE::pair<int, int> p;
	CHECK(p.first == 0 && p.second == 0);

	NAMESPACE::pair<int, int> p2(5, 9);
	CHECK(p2.first == 5 && p2.second == 9);

	NAMESPACE::pair<int, char> p3(65535, 'a');
	CHECK(p3.first == 65535 && p3.second == 'a');

	NAMESPACE::pair<int, int> p4 = NAMESPACE::make_pair(1, 2);
	CHECK(p4.first == 1 && p4.second == 2);

	NAMESPACE::pair<int, int> p5 = p2, p6(9, 5);

	CHECK((p2 == p5) == true);
	CHECK((p5 != p6) == true);
	CHECK((p5 < p6) == true);
	CHECK((p6 > p5) == true);
	CHECK((p2 <= p5) == true);
	CHECK((p2 >= p5) == true);
}
