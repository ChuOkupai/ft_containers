#pragma once
#include "_rbtree.hpp"
#include "functional.hpp"
#include "utility.hpp"

namespace ft
{
	template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
	public:
		typedef Key				key_type;
		typedef Key				value_type;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		typedef Compare			key_compare;
		typedef Compare			value_compare;
		typedef Allocator		allocator_type;

	private:
		typedef _rbtree<const key_type, const value_type, identity<const value_type>, key_compare, allocator_type> tree_type;

		tree_type _tree;

	public:
		typedef typename tree_type::reference				reference;
		typedef typename tree_type::const_reference			const_reference;
		typedef typename tree_type::pointer					pointer;
		typedef typename tree_type::const_pointer 			const_pointer;
		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

	public:
		explicit set(const Compare &comp = Compare(), const Allocator &alloc = Allocator()) :
		_tree(comp, alloc)
		{}
		
		template<class InputIt>
		set(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()) :
		_tree(comp, alloc)
		{
			insert(first, last);
		}
		
		set(const set &other) :
		_tree(other._tree)
		{}
		
		~set()
		{}
		
		set &operator=(const set &other)
		{
			_tree = other._tree;
			return *this;
		}

		allocator_type get_allocator() const
		{
			return _tree.get_allocator();
		}

		// Iterators:
		iterator begin()
		{
			return _tree.begin();
		}

		const_iterator begin() const
		{
			return _tree.begin();
		}

		iterator end()
		{
			return _tree.end();
		}

		const_iterator end() const
		{
			return _tree.end();
		}

		reverse_iterator rbegin()
		{
			return _tree.rbegin();
		}

		const_reverse_iterator rbegin() const
		{
			return _tree.rbegin();
		}

		reverse_iterator rend()
		{
			return _tree.rend();
		}

		const_reverse_iterator rend() const
		{
			return _tree.rend();
		}

		// Capacity:
		bool empty() const
		{
			return _tree.empty();
		}

		size_type size() const
		{
			return _tree.size();
		}

		size_type max_size() const
		{
			return _tree.max_size();
		}

		// Modifiers:
		void clear()
		{
			_tree.clear();
		}

		pair<iterator, bool> insert(const value_type &value)
		{
			return _tree.insert(value);
		}

		iterator insert(iterator hint, const value_type &value)
		{
			return _tree.insert(hint, value);
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			return _tree.insert(first, last);
		}

		void erase(iterator pos)
		{
			_tree.erase(pos);
		}

		size_type erase(const Key &key)
		{
			return _tree.erase(key);
		}

		void erase(iterator first, iterator last)
		{
			_tree.erase(first, last);
		}

		void swap(set &other)
		{
			_tree.swap(other._tree);
		}

		// Lookup:
		size_type count(const Key &key) const
		{
			return _tree.count(key);
		}

		iterator find(const Key &key)
		{
			return _tree.find(key);
		}

		const_iterator find(const Key &key) const
		{
			return _tree.find(key);
		}

		pair<iterator, iterator> equal_range(const Key &key)
		{
			return _tree.equal_range(key);
		}

		pair<const_iterator, const_iterator> equal_range(const Key &key) const
		{
			return _tree.equal_range(key);
		}

		iterator lower_bound(const Key &key)
		{
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound(const Key &key) const
		{
			return _tree.lower_bound(key);
		}

		iterator upper_bound(const Key &key)
		{
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound(const Key &key) const
		{
			return _tree.upper_bound(key);
		}

		// Observers:
		key_compare key_comp() const
		{
			return _tree.key_comp();
		}

		value_compare value_comp() const
		{
			return value_compare(key_comp());
		}

		// Non-member functions:
		friend inline bool operator==(const set &x, const set &y)
		{
			return x._tree == y._tree;
		}

		friend inline bool operator!=(const set &x, const set &y)
		{
			return !(x == y);
		}

		friend inline bool operator<(const set &x, const set &y)
		{
			return x._tree < y._tree;
		}

		friend inline bool operator<=(const set &x, const set &y)
		{
			return !(x > y);
		}

		friend inline bool operator>(const set &x, const set &y)
		{
			return y < x;
		}

		friend inline bool operator>=(const set &x, const set &y)
		{
			return !(x < y);
		}

		friend inline void swap(set &x, set &y)
		{
			x.swap(y);
		}
	};
}
