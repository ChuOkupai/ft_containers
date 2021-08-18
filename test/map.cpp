#include "tester.hpp"
#include "map.hpp"
#include <map>
#include <string>
#include <vector>

TEST_GROUP(map)
{};

TEST(map, empty_constructor)
{
	NAMESPACE::map<int, int> m;

	CHECK(m.empty() == true);
	CHECK(m.size() == 0);
}

TEST(map, input_constructor)
{
	std::vector<NAMESPACE::pair<std::string, int> > v;

	v.push_back(NAMESPACE::pair<std::string, int>("foo", 1));
	v.push_back(NAMESPACE::pair<std::string, int>("bar", 2));
	v.push_back(NAMESPACE::pair<std::string, int>("baz", 3));
	v.push_back(NAMESPACE::pair<std::string, int>("qux", 4));

	NAMESPACE::map<std::string, int> m(v.begin() + 1, v.end() - 1);

	CHECK(m.empty() == false);
	CHECK(m.size() == 2);
	CHECK(m.find("foo") == m.end());
	CHECK(m.find("bar") != m.end());
	CHECK(m.find("baz") != m.end());
	CHECK(m.find("qux") == m.end());
}

TEST(map, copy_constructor)
{
	NAMESPACE::map<int, int> m;

	for (int i = 1; i < 10; ++i)
		m[i] = -i;

	NAMESPACE::map<int, int> n(m);
	CHECK(m == n);
}

TEST(map, iterators)
{
	NAMESPACE::map<int, int> m;

	CHECK(m.begin() == m.end());
	for (int i = 0; i < 5; ++i)
		m[i] = i + 1;
	CHECK(m.begin() != m.end());
	NAMESPACE::map<int, int>::const_iterator i = m.begin();
	for (int j = 0; j < 5; ++i, ++j)
		CHECK(i->first == j && i->second == j + 1);
}

TEST(map, empty)
{
	NAMESPACE::map<int, int> m;

	CHECK(m.empty() == true);
	m[0] = 0;
	CHECK(m.empty() == false);
}

TEST(map, size)
{
	NAMESPACE::map<int, int> m;

	CHECK(m.size() == 0);
	m[0] = 0;
	CHECK(m.size() == 1);
	m[1] = 1;
	CHECK(m.size() == 2);
	m.erase(0);
	CHECK(m.size() == 1);
	m[3] = 3;
	CHECK(m.size() == 2);
}

TEST(map, clear)
{
	NAMESPACE::map<int, int> m;

	for (int i = 0; i < 4; ++i)
		m[i] = i;
	m.clear();
	CHECK(m.empty() == true);
}

TEST(map, insert)
{
	NAMESPACE::pair<const int, int> t[] =
	{
		NAMESPACE::make_pair(11, -11),
		NAMESPACE::make_pair(2, -2),
		NAMESPACE::make_pair(14, -14),
		NAMESPACE::make_pair(1, -1),
		NAMESPACE::make_pair(7, -7),
		NAMESPACE::make_pair(15, -15),
		NAMESPACE::make_pair(5, -5),
		NAMESPACE::make_pair(8, -8),
		NAMESPACE::make_pair(4, -4)
	};
	size_t n = sizeof(t) / sizeof(*t);

	NAMESPACE::map<int, int> m;

	for (size_t i = 0; i < n; ++i)
		m.insert(t[i]);
	for (size_t i = 0; i < n; ++i)
	{
		NAMESPACE::map<int, int>::const_iterator j = m.find(t[i].first);
		CHECK(*j == t[i]);
	}
}

TEST(map, erase)
{
	NAMESPACE::map<char, int> m;

	m['A'] = 1;
	m.erase('A');
	CHECK(m.empty());
	m['B'] = 2;
	m.erase(m.begin());
	CHECK(m.empty());

	const std::string t = "BADCE";
	for (size_t i = 0; i < t.size(); ++i)
		m[t[i]] = i + 1;

	for (size_t i = 0; i < t.size(); ++i)
	{
		m.erase(t[i]);
		CHECK(m.size() == t.size() - i - 1);
		CHECK(m.find(t[i]) == m.end());
		for (size_t j = i + 1; j < t.size(); ++j)
			CHECK(m.find(t[j]) != m.end());
	}
}

TEST(map, swap)
{
	NAMESPACE::map<int, int> m1, m2;

	m1[1] = 1;
	m1.swap(m2);
	CHECK(m1.find(1) == m1.end());
	CHECK(m1.empty() == true);
	CHECK(m2.find(1) != m2.end());
	CHECK(m2.empty() == false);
	m1[2] = 2;
	m2.swap(m1);
	CHECK(m1.find(1) != m1.end());
	CHECK(m1.find(2) == m1.end());
	CHECK(m2.find(1) == m2.end());
	CHECK(m2.find(2) != m1.end());
}

TEST(map, count)
{
	NAMESPACE::map<int, std::string> m;

	m[0] = "Squalala";
	m[1] = "Woosh";
	CHECK(m.count(0) == 1);
	CHECK(m.count(1) == 1);
	CHECK(m.count(2) == 0);
	m[2] = "Pouet";
	CHECK(m.count(0) == 1);
	CHECK(m.count(1) == 1);
	CHECK(m.count(2) == 1);
}

TEST(map, find)
{
	NAMESPACE::map<int, std::string> m;

	m[0] = "Squalala";
	m[1] = "Woosh";
	CHECK(m.find(0) != m.end());
	CHECK(m.find(1) != m.end());
	CHECK(m.find(2) == m.end());
	m[2] = "Pouet";
	CHECK(m.find(0) != m.end());
	CHECK(m.find(1) != m.end());
	CHECK(m.find(2) != m.end());
	CHECK(m.find(2)->second == "Pouet");
}

TEST(map, bounds)
{
	typedef NAMESPACE::map<int, const char*> t_map;

	t_map m;

	m[0] = "zero";
	m[1] = "one";
	m[2] = "two";
	m[3] = "three";

	NAMESPACE::pair<t_map::const_iterator, t_map::const_iterator> p;

	p = m.equal_range(-1);
	CHECK(p.first == m.begin());
	CHECK(p.second == m.begin());
	p = m.equal_range(4);
	CHECK(p.first == m.end());
	CHECK(p.second == m.end());
	p = m.equal_range(1);
	CHECK(p.first != m.end());
	CHECK(p.first->first == 1);
	CHECK(++p.first == p.second);

	t_map::const_iterator i;

	i = m.lower_bound(-1);
	CHECK(i == m.begin());
	i = m.lower_bound(4);
	CHECK(i == m.end());
	i = m.lower_bound(1);
	CHECK(i == ++m.begin());

	i = m.upper_bound(-1);
	CHECK(i == m.begin());
	i = m.upper_bound(4);
	CHECK(i == m.end());
	i = m.upper_bound(1);
	CHECK(i == ++++m.begin());
}

struct KeyModCmp
{
	bool operator()(const int a, const int b) const
	{
		return (a % 97) < (b % 97);
	}
};

TEST(map, key_comp)
{
	NAMESPACE::map<int, char, KeyModCmp> m;
	KeyModCmp cmp = m.key_comp();
	CHECK(cmp(2, 100) && !cmp(100, 2));
	CHECK(!cmp(3, 100) && !cmp(100, 3));
	CHECK(!cmp(4, 100) && cmp(100, 4));
}

struct ValueModCmp
{
	bool operator()(const int a, const int b) const
	{
		return (a % 97) < (b % 97);
	}
};

TEST(map, value_comp)
{
	NAMESPACE::map<int, char, ValueModCmp> m;
	NAMESPACE::map<int, char, ValueModCmp>::value_compare cmp = m.value_comp();
	const NAMESPACE::pair<int, char> p(100, 'x'), b(2, 'b'), c(3, 'c'), d(4, 'd');
	CHECK(cmp(b, p) && !cmp(p, b));
	CHECK(!cmp(c, p) && !cmp(p, c));
	CHECK(!cmp(d, p) && cmp(p, d));
}

TEST(map, logical_operators)
{
	NAMESPACE::map<int, char> alice;
	alice[1] = 'a';
	alice[2] = 'b';
	alice[3] = 'c';
	NAMESPACE::map<int, char> bob;
	bob[7] = 'Z';
	bob[8] = 'Y';
	bob[9] = 'X';
	bob[10] = 'W';
	NAMESPACE::map<int, char> eve = alice;

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

TEST(map, benchmark)
{
	NAMESPACE::map<int, int> m;

	for (int i = 0; i < 1e4; ++i)
		m[i] = -i;
}
