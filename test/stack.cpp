#include "tester.hpp"
#include "stack.hpp"
#include <stack>

TEST_GROUP(stack)
{};

TEST(stack, constructor)
{
	NAMESPACE::stack<int> s;

	CHECK(s.empty() == true);
	CHECK(s.size() == 0);
}

TEST(stack, top)
{
	NAMESPACE::stack<int> s;

	s.push(2);
	CHECK(s.top() == 2);
	s.push(6);
	CHECK(s.top() == 6);
	s.push(51);
	CHECK(s.top() == 51);
}

TEST(stack, empty)
{
	NAMESPACE::stack<int> s;

	CHECK(s.empty() == true);
	s.push(42);
	CHECK(s.empty() == false);
	s.push(84);
	CHECK(s.empty() == false);
}

TEST(stack, size)
{
	NAMESPACE::stack<int> s;

	CHECK(s.size() == 0);
	s.push(1);
	CHECK(s.size() == 1);
	s.push(2);
	CHECK(s.size() == 2);
	s.pop();
	CHECK(s.size() == 1);
	s.pop();
	CHECK(s.size() == 0);
}

TEST(stack, push)
{
	NAMESPACE::stack<int> s;

	s.push(-1);
	s.push(-2);
	s.push(-3);
	CHECK(s.size() == 3);
}

TEST(stack, pop)
{
	NAMESPACE::stack<int> s;

	s.push(2);
	s.push(4);
	s.push(8);
	s.pop();
	CHECK(s.top() == 4);
	s.pop();
	CHECK(s.top() == 2);
}

TEST(stack, logical_operators)
{
	NAMESPACE::stack<int> a, b, c;

	a.push(10);
	a.push(20);
	a.push(30);
	b = a;
	c.push(30);
	c.push(20);
	c.push(10);

	CHECK((a == b) == true);
	CHECK((b != c) == true);
	CHECK((b < c) == true);
	CHECK((c > b) == true);
	CHECK((a <= b) == true);
	CHECK((a >= b) == true);
}

TEST(stack, benchmark)
{
	NAMESPACE::stack<int> s;

	for (size_t i = 0; i < 1e6; ++i)
		s.push(i);
}
