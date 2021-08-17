#include "tester.hpp"
#include "iterator.hpp"
#include <iterator>
#include <list>

TEST_GROUP(iterator)
{};

TEST(iterator, reverse_iterator)
{
	std::list<int> l;

	for (int i = 1; i < 4; ++i)
		l.push_back(i);
	NAMESPACE::distance(l.begin(), l.end());
	typedef NAMESPACE::reverse_iterator<std::list<int>::iterator> iter;
	int i = 3;
	for (iter j(l.end()); j != iter(l.begin()); --i, ++j)
		CHECK(i == *j);
}

