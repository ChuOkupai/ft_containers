#include "tester.hpp"
#include "vector.hpp"
#include <vector>

TEST_GROUP(vector)
{};

TEST(vector, empty_constructor)
{
	NAMESPACE::vector<int > v;

	CHECK(v.empty() == true);
	CHECK(v.size() == 0);
	CHECK(v.capacity() == 0);
}

TEST(vector, init_constructor)
{
	NAMESPACE::vector<long> v(8, 8);

	CHECK(v.empty() == false);
	CHECK(v.size() == 8);
	CHECK(v.capacity() >= 8);
	for (size_t i = 0; i < 5; ++i)
		CHECK(v[i] == 8);
}

TEST(vector, input_constructor)
{
	const char				s[] = "Hello";
	NAMESPACE::vector<char>	v(s, s + sizeof(s) - 1);

	CHECK(v.empty() == false);
	CHECK(v.size() == 5);
	CHECK(v.capacity() >= 5);
	for (size_t i = 0; i < 5; ++i)
		CHECK(v[i] == s[i]);
}

TEST(vector, copy_constructor)
{
	NAMESPACE::vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	NAMESPACE::vector<int> w(v);

	CHECK(v == w);
	CHECK(w.empty() == false);
	CHECK(w.size() == 3);
	CHECK(w.capacity() >= 3);
	for (int i = 0; i < 3; ++i)
		CHECK(v[i] == i + 1);
	v.clear();
	CHECK(v != w);
	CHECK(w.empty() == false);
	CHECK(w.size() == 3);
	CHECK(w.capacity() >= 3);
}

TEST(vector, assign)
{
	NAMESPACE::vector<char> v;

	v.assign(2, 'x');
	CHECK(v.size() == 2);
	for (size_t i = 0; i < v.size(); ++i)
		CHECK(v[i] == 'x');
	v.assign(3, 'y');
	CHECK(v.size() == 3);
	for (size_t i = 0; i < v.size(); ++i)
		CHECK(v[i] == 'y');
	v[0] = 'x';
	v[2] = 'z';

	NAMESPACE::vector<char> w;
	w.assign(v.begin(), v.end());
	CHECK(w.size() == 3);
	CHECK(w[0] == 'x');
	CHECK(w[1] == 'y');
	CHECK(w[2] == 'z');

	const int tab[] = { 7, 77, 777, 7777 };
	NAMESPACE::vector<int> x;

	x.assign(tab, tab + sizeof(tab) / sizeof(*tab));
	CHECK(x[0] == 7);
	CHECK(x[1] == 77);
	CHECK(x[2] == 777);
	CHECK(x[3] == 7777);
}

TEST(vector, at)
{
	NAMESPACE::vector<char> v(3, 'x');

	CHECK(v.at(0) == 'x');
	const char &c = v.at(1);
	CHECK(c == 'x');
	v.at(1) = 'y';
	CHECK(v.at(1) == 'y');
	CHECK(v.at(0) == 'x' && v.at(2) == 'x');
	CHECK_THROWS(std::out_of_range, v.at(v.size()));
	CHECK_THROWS(std::out_of_range, v.at(v.size() + 1));
}

TEST(vector, front)
{
	NAMESPACE::vector<int> v;

	v.push_back(1);
	CHECK(v.front() == 1);
	v.push_back(2);
	CHECK(v.front() == 1);
	v.insert(v.begin(), 3);
	CHECK(v.front() == 3);
}

TEST(vector, back)
{
	NAMESPACE::vector<int> v;

	v.push_back(1);
	CHECK(v.back() == 1);
	v.push_back(2);
	CHECK(v.back() == 2);
	v.insert(v.begin(), 3);
	CHECK(v.back() == 2);
}

TEST(vector, iterators)
{
	NAMESPACE::vector<int> v;

	CHECK(v.begin() == v.end());
	v.push_back(1);
	CHECK(*v.begin() == 1);
	CHECK(v.begin() != v.end());
	CHECK(v.begin() + 1 == v.end());
	CHECK(++v.begin() == v.end());
	CHECK(v.begin()++ != v.end());
	v.push_back(2);
	CHECK(*v.begin() == 1);
	CHECK(v.begin() != v.end());
	CHECK(v.begin() + 1 != v.end());
	CHECK(*++v.begin() == 2);
	CHECK(++v.begin() != v.end());
	CHECK(v.begin()++ != v.end());
	CHECK(v.begin() + 2 == v.end());

	NAMESPACE::vector<int>::iterator i = v.begin();
	NAMESPACE::vector<int>::const_iterator j = v.begin();
	CHECK(i == j);
	i = v.end() - 2;
	j = v.end() - 2;
	CHECK(i == j);
	i = -2 + v.end();
	j = -2 + v.end();
	CHECK(i == j);
	++i;
	j = i;
	CHECK(j == i);
	--i;
	CHECK(j != i);
}

TEST(vector, empty)
{
	NAMESPACE::vector<int> v;

	CHECK(v.empty() == true);
	v.push_back(1);
	CHECK(v.empty() == false);
	v.push_back(2);
	CHECK(v.empty() == false);
}

TEST(vector, size)
{
	NAMESPACE::vector<int> v;

	CHECK(v.size() == 0);
	v.push_back(1);
	CHECK(v.size() == 1);
	v.push_back(2);
	CHECK(v.size() == 2);
}

TEST(vector, reserve)
{
	NAMESPACE::vector<int> v;

	v.reserve(5);
	CHECK(v.capacity() == 5);
	CHECK(v.size() == 0);
	v.reserve(3);
	CHECK(v.capacity() == 5);
	CHECK(v.size() == 0);
	v.reserve(8);
	CHECK(v.capacity() == 8);
	CHECK(v.size() == 0);

	CHECK_THROWS(std::length_error, v.reserve(v.max_size() + 1));
}

TEST(vector, clear)
{
	NAMESPACE::vector<int> v;

	CHECK(v.empty() == true);
	v.assign(4, 0);
	v.clear();
	CHECK(v.empty() == true);
	v.push_back(1);
	v.clear();
	CHECK(v.empty() == true);
}

TEST(vector, insert)
{
	NAMESPACE::vector<int> v;

	v.insert(v.end(), 0, 0);
	CHECK(v.empty() == true);
	CHECK(v.capacity() == 0);
	v.insert(v.begin(), 3);
	CHECK(v[0] == 3);
	v.insert(v.begin(), 1);
	CHECK(v[0] == 1);
	CHECK(v[1] == 3);
	v.insert(v.end(), 4);
	CHECK(v[0] == 1);
	CHECK(v[1] == 3);
	CHECK(v[2] == 4);
	v.insert(v.begin() + 1, 2);
	CHECK(v[0] == 1);
	CHECK(v[1] == 2);
	CHECK(v[2] == 3);
	CHECK(v[3] == 4);

	NAMESPACE::vector<int> w;

	w.push_back(-1);
	w.push_back(0);
	v.insert(v.begin(), w.begin(), w.end());
	CHECK(v[0] == -1);
	CHECK(v[1] == 0);
	CHECK(v[2] == 1);
	CHECK(v[3] == 2);
	CHECK(v[4] == 3);
	CHECK(v[5] == 4);

	w.insert(w.begin() + 1, 2, 99);
	CHECK(w[0] == -1);
	CHECK(w[1] == 99);
	CHECK(w[2] == 99);
	CHECK(w[3] == 0);

	const short tab[] = { -1, 0, 1 };
	NAMESPACE::vector<int> x;

	x.insert(x.begin(), tab, tab + sizeof(tab) / sizeof(*tab));
	CHECK(x[0] == -1);
	CHECK(x[1] == 0);
	CHECK(x[2] == 1);
}

TEST(vector, erase)
{
	NAMESPACE::vector<int> v;

	for (size_t i = 0; i < 10; ++i)
		v.push_back(i);
	v.erase(v.begin());
	CHECK(v[0] == 1);
	v.erase(v.end() - 1);
	CHECK(v.back() == 8);
	v.erase(v.begin() + 1, v.end() - 1);
	CHECK(v.size() == 2);
	CHECK(v[0] == 1);
	CHECK(v[1] == 8);
	v.erase(v.begin(), v.end());
	CHECK(v.empty() == true);
}

TEST(vector, push_back)
{
	NAMESPACE::vector<char> v;

	v.push_back('a');
	CHECK(v.back() == 'a');
	v.push_back('b');
	CHECK(v.back() == 'b');
	v.push_back('c');
	CHECK(v.back() == 'c');
}

TEST(vector, pop_back)
{
	NAMESPACE::vector<char> v;

	v.push_back('a');
	v.push_back('b');
	v.push_back('c');
	v.pop_back();
	CHECK(v.back() == 'b');
	v.pop_back();
	CHECK(v.back() == 'a');
	v.pop_back();
	CHECK(v.empty() == true);
}

TEST(vector, resize)
{
	NAMESPACE::vector<char> v;

	v.resize(5, 'x');
	CHECK(v.size() == 5);
	for (size_t i = 0; i < v.size(); ++i)
		CHECK(v[i] == 'x');
	v.resize(2);
	CHECK(v.size() == 2);
	for (size_t i = 0; i < v.size(); ++i)
		CHECK(v[i] == 'x');
	v.resize(5, 'y');
	CHECK(v.size() == 5);
	for (size_t i = 0; i < 2; ++i)
		CHECK(v[i] == 'x');
	for (size_t i = 2; i < v.size(); ++i)
		CHECK(v[i] == 'y');
}

TEST(vector, swap)
{
	NAMESPACE::vector<int> u, v;

	for (size_t i = 0; i < 3; ++i)
	{
		u.push_back(i);
		v.push_back(9 - i);
	}
	u.swap(v);
	for (int i = 0; i < 3; ++i)
	{
		CHECK(u[i] == 9 - i);
		CHECK(v[i] == i);
	}
}

TEST(vector, logical_operators)
{
	NAMESPACE::vector<int> alice;
	alice.push_back(1);
	alice.push_back(2);
	alice.push_back(3);
	NAMESPACE::vector<int> bob;
	bob.push_back(7);
	bob.push_back(8);
	bob.push_back(9);
	bob.push_back(10);
	NAMESPACE::vector<int> eve;
	eve.push_back(1);
	eve.push_back(2);
	eve.push_back(3);

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

TEST(vector, benchmark)
{
	NAMESPACE::vector<int> v;

	for (size_t count = 1; count <= 1e6; count *= 10)
		v.assign(count, 0);
}
