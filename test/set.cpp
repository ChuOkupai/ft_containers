#include "tester.hpp"
#include "set.hpp"
#include <set>
#include <string>
#include <vector>

TEST_GROUP(set)
{};

TEST(set, empty_constructor)
{
	NAMESPACE::set<int> s;

	CHECK(s.empty() == true);
	CHECK(s.size() == 0);
}

TEST(set, input_constructor)
{
	std::vector<std::string> v;

	v.push_back("foo");
	v.push_back("bar");
	v.push_back("baz");
	v.push_back("qux");

	NAMESPACE::set<std::string> s(v.begin() + 1, v.end() - 1);

	CHECK(s.empty() == false);
	CHECK(s.size() == 2);
	CHECK(s.find("foo") == s.end());
	CHECK(s.find("bar") != s.end());
	CHECK(s.find("baz") != s.end());
	CHECK(s.find("qux") == s.end());
}

TEST(set, copy_constructor)
{
	NAMESPACE::set<int> s;

	for (int i = 1; i < 10; ++i)
		s.insert(i);

	NAMESPACE::set<int> t(s);
	CHECK(s == t);
}

TEST(set, iterators)
{
	NAMESPACE::set<int> s;

	CHECK(s.begin() == s.end());
	for (int i = 0; i < 5; ++i)
		s.insert(i);
	CHECK(s.begin() != s.end());
	NAMESPACE::set<int, int>::const_iterator i = s.begin();
	for (int j = 0; j < 5; ++i, ++j)
		CHECK(*i == j);
}

TEST(set, empty)
{
	NAMESPACE::set<int> s;

	CHECK(s.empty() == true);
	s.insert(0);
	CHECK(s.empty() == false);
}

TEST(set, size)
{
	NAMESPACE::set<int> s;

	CHECK(s.size() == 0);
	s.insert(0);
	CHECK(s.size() == 1);
	s.insert(1);
	CHECK(s.size() == 2);
	s.erase(0);
	CHECK(s.size() == 1);
	s.insert(3);
	CHECK(s.size() == 2);
}

TEST(set, clear)
{
	NAMESPACE::set<int> s;

	for (int i = 0; i < 4; ++i)
		s.insert(i);
	s.clear();
	CHECK(s.empty() == true);
}

TEST(set, insert)
{
	const int t[] = { 11, 2, 14, 1, 7, 15, 5, 8, 4 };
	size_t n = sizeof(t) / sizeof(*t);

	NAMESPACE::set<int> s;

	for (size_t i = 0; i < n; ++i)
		s.insert(t[i]);
	for (size_t i = 0; i < n; ++i)
	{
		NAMESPACE::set<int, int>::const_iterator j = s.find(t[i]);
		CHECK(*j == t[i]);
	}
}

TEST(set, erase)
{
	NAMESPACE::set<char> s;

	s.insert('A');
	s.erase('A');
	CHECK(s.empty());
	s.insert('B');
	s.erase(s.begin());
	CHECK(s.empty());

	const std::string t = "BADCE";
	for (size_t i = 0; i < t.size(); ++i)
		s.insert(t[i]);

	for (size_t i = 0; i < t.size(); ++i)
	{
		s.erase(t[i]);
		CHECK(s.size() == t.size() - i - 1);
		CHECK(s.find(t[i]) == s.end());
		for (size_t j = i + 1; j < t.size(); ++j)
			CHECK(s.find(t[j]) != s.end());
	}
}

TEST(set, swap)
{
	NAMESPACE::set<int> s1, s2;

	s1.insert(1);
	s1.swap(s2);
	CHECK(s1.find(1) == s1.end());
	CHECK(s1.empty() == true);
	CHECK(s2.find(1) != s2.end());
	CHECK(s2.empty() == false);
	s1.insert(2);
	s2.swap(s1);
	CHECK(s1.find(1) != s1.end());
	CHECK(s1.find(2) == s1.end());
	CHECK(s2.find(1) == s2.end());
	CHECK(s2.find(2) != s1.end());
}

TEST(set, count)
{
	NAMESPACE::set<int> s;

	s.insert(0);
	s.insert(1);
	CHECK(s.count(0) == 1);
	CHECK(s.count(1) == 1);
	CHECK(s.count(2) == 0);
	s.insert(2);
	CHECK(s.count(0) == 1);
	CHECK(s.count(1) == 1);
	CHECK(s.count(2) == 1);
}

TEST(set, find)
{
	NAMESPACE::set<int> s;

	s.insert(0);
	s.insert(1);
	CHECK(s.find(0) != s.end());
	CHECK(s.find(1) != s.end());
	CHECK(s.find(2) == s.end());
	s.insert(2);
	CHECK(s.find(0) != s.end());
	CHECK(s.find(1) != s.end());
	CHECK(s.find(2) != s.end());
	CHECK(*s.find(2) == 2);
}

TEST(set, bounds)
{
	typedef NAMESPACE::set<int> t_set;

	t_set s;

	for (size_t i = 0; i < 4; ++i)
		s.insert(i);

	NAMESPACE::pair<t_set::const_iterator, t_set::const_iterator> p;

	p = s.equal_range(-1);
	CHECK(p.first == s.begin());
	CHECK(p.second == s.begin());
	p = s.equal_range(4);
	CHECK(p.first == s.end());
	CHECK(p.second == s.end());
	p = s.equal_range(1);
	CHECK(p.first != s.end());
	CHECK(*p.first == 1);
	CHECK(++p.first == p.second);

	t_set::const_iterator i;

	i = s.lower_bound(-1);
	CHECK(i == s.begin());
	i = s.lower_bound(4);
	CHECK(i == s.end());
	i = s.lower_bound(1);
	CHECK(i == ++s.begin());

	i = s.upper_bound(-1);
	CHECK(i == s.begin());
	i = s.upper_bound(4);
	CHECK(i == s.end());
	i = s.upper_bound(1);
	CHECK(i == ++++s.begin());
}

struct ModCmp
{
	bool operator()(const int a, const int b) const
	{
		return (a % 97) < (b % 97);
	}
};

TEST(set, key_comp)
{
	NAMESPACE::set<int, ModCmp> s;
	ModCmp cmp = s.key_comp();
	CHECK(cmp(2, 100) && !cmp(100, 2));
	CHECK(!cmp(3, 100) && !cmp(100, 3));
	CHECK(!cmp(4, 100) && cmp(100, 4));
}

TEST(set, value_comp)
{
	NAMESPACE::set<int, ModCmp> s;
	ModCmp cmp = s.key_comp();
	CHECK(cmp(2, 100) && !cmp(100, 2));
	CHECK(!cmp(3, 100) && !cmp(100, 3));
	CHECK(!cmp(4, 100) && cmp(100, 4));
}

TEST(set, logical_operators)
{
	NAMESPACE::set<int> alice;
	alice.insert(1);
	alice.insert(2);
	alice.insert(3);
	NAMESPACE::set<int> bob;
	bob.insert(7);
	bob.insert(8);
	bob.insert(9);
	bob.insert(10);
	NAMESPACE::set<int> eve = alice;

	// Compare non equal containers
	CHECK((alice == bob) == false);
	CHECK((alice != bob) == true);
	CHECK((alice < bob) == true);
	CHECK((alice <= bob) == true);
	CHECK((alice > bob) == false);
	CHECK((alice >= bob) == false);

	// Compare equal containers
	CHECK((alice == eve) == true);
	CHECK((alice != eve) == false);
	CHECK((alice < eve) == false);
	CHECK((alice <= eve) == true);
	CHECK((alice > eve) == false);
	CHECK((alice >= eve) == true);
}

TEST(set, benchmark)
{
	NAMESPACE::set<int> s;

	for (int i = 0; i < 1e4; ++i)
		s.insert(i);
}
