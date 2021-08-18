#pragma once
#include <functional>
#include <memory>
#include <stdexcept>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{
	struct _rbtree_node_base
	{
		typedef _rbtree_node_base	node_type;
		typedef node_type*			pointer;
		typedef const node_type*	const_pointer;

		enum color_type
		{
			BLACK,
			RED
		};

		color_type	color;
		pointer		parent, left, right;

		_rbtree_node_base(const color_type color = RED) :
		color(color), parent(NULL), left(NULL), right(NULL)
		{}

		~_rbtree_node_base()
		{}

		inline pointer gparent()
		{
			return parent->parent;
		}

		inline pointer maximum()
		{
			pointer x;
			for (x = this; x->right; x = x->right);
			return x;
		}

		inline const_pointer maximum() const
		{
			const_pointer x;
			for (x = this; x->right; x = x->right);
			return x;
		}

		inline pointer minimum()
		{
			pointer x;
			for (x = this; x->left; x = x->left);
			return x;
		}

		inline const_pointer minimum() const
		{
			const_pointer x;
			for (x = this; x->left; x = x->left);
			return x;
		}

		inline void insert_fixup(pointer &root)
		{
			pointer z = this;
			while (z != root && z->parent->color == RED)
			{
				pointer x = z->gparent();
				if (z->parent == x->left)
				{
					pointer y = x->right;
					if (y && y->color == RED)
					{
						z->parent->color = BLACK;
						y->color = BLACK;
						x->color = RED;
						z = x;
					}
					else
					{
						if (z == z->parent->right)
						{
							z = z->parent;
							z->rotate_left(root);
							x = z->gparent();
						}
						z->parent->color = BLACK;
						x->color = RED;
						x->rotate_right(root);
					}
				}
				else
				{
					pointer y = x->left;
					if (y && y->color == RED)
					{
						z->parent->color = BLACK;
						y->color = BLACK;
						x->color = RED;
						z = x;
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							z->rotate_right(root);
							x = z->gparent();
						}
						z->parent->color = BLACK;
						x->color = RED;
						x->rotate_left(root);
					}
				}
			}
			root->color = BLACK;
		}

		inline void remove(pointer &root)
		{
			node_type	sentinel_storage(BLACK);
			pointer		sentinel = &sentinel_storage, z = this, y = z, x;
			color_type	y_original_color = y->color;

			if (!z->left)
			{
				x = y->right;
				if (!x)
					x = z->set_sentinel(sentinel);
				z->transplant(root, x);
			}
			else if (!z->right)
			{
				x = z->left;
				z->transplant(root, x);
			}
			else
			{
				y = z->right->minimum();
				y_original_color = y->color;
				x = y->right;
				if (!x)
					x = y->set_sentinel(sentinel);
				if (y->parent == z)
					x->parent = y;
				else
				{
					y->transplant(root, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				z->transplant(root, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (y_original_color == BLACK && root != sentinel)
				x->remove_fixup(root);
			if (x == sentinel)
			{
				x = x->parent;
				if (x == root->parent)
					x->parent = NULL;
				else if (x->left == sentinel)
					x->left = NULL;
				else
					x->right = NULL;
			}
		}

	private:
		inline void rotate_left(pointer &root)
		{
			pointer x = this, y = right;
			x->right = y->left;
			if (y->left)
				y->left->parent = x;
			y->parent = x->parent;
			if (x == root)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		inline void rotate_right(pointer &root)
		{
			pointer x = this, y = left;
			x->left = y->right;
			if (y->right)
				y->right->parent = x;
			y->parent = x->parent;
			if (x == root)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		inline pointer set_sentinel(pointer sentinel)
		{
			sentinel->parent = this;
			right = sentinel;
			return right;
		}

		inline void transplant(pointer &root, pointer v)
		{
			pointer u = this;
			if (u == root)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		inline void remove_fixup(pointer &root)
		{
			pointer x = this, w;
			while (x != root && x->color == BLACK)
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						x->parent->rotate_left(root);
						w = x->parent->right;
					}
					if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK))
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (!w->right || w->right->color == BLACK)
						{
							w->left->color = BLACK;
							w->color = RED;
							w->rotate_right(root);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						x->parent->rotate_left(root);
						x = root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						x->parent->rotate_right(root);
						w = x->parent->left;
					}
					if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK))
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (!w->left || w->left->color == BLACK)
						{
							w->right->color = BLACK;
							w->color = RED;
							w->rotate_left(root);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						x->parent->rotate_right(root);
						x = root;
					}
				}
			x->color = BLACK;
		}
	};

	template<class Value>
	struct _rbtree_node : public _rbtree_node_base
	{
		typedef _rbtree_node		node_type;
		typedef node_type*			pointer;
		typedef const node_type*	const_pointer;
		typedef Value 				value_type;

		value_type value;

		_rbtree_node(const value_type &value = value_type(), const color_type color = RED) :
		_rbtree_node_base(color), value(value)
		{}

		~_rbtree_node()
		{}

		inline pointer parent_link() const
		{
			return static_cast<pointer>(parent);
		}

		inline pointer left_link() const
		{
			return static_cast<pointer>(left);
		}

		inline pointer right_link() const
		{
			return static_cast<pointer>(right);
		}

		inline const_pointer maximum() const
		{
			return static_cast<const_pointer>(_rbtree_node_base::maximum());
		}

		inline pointer maximum()
		{
			return static_cast<pointer>(_rbtree_node_base::maximum());
		}

		inline const_pointer minimum() const
		{
			return static_cast<const_pointer>(_rbtree_node_base::minimum());
		}

		inline pointer minimum()
		{
			return static_cast<pointer>(_rbtree_node_base::minimum());
		}
	};

	template<class T, class Pointer, class Reference>
	class _rbtree_iterator : public iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, Pointer, Reference>
	{
		typedef iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, Pointer, Reference> traits;

		typedef _rbtree_node_base::pointer			base_node_pointer;
		typedef _rbtree_node<T>						node_type;
		typedef typename _rbtree_node<T>::pointer	node_pointer;
		typedef _rbtree_iterator<T, T*, T&>			iterator;

	public:
		typedef typename traits::iterator_category	iterator_category;
		typedef typename traits::value_type			value_type;
		typedef typename traits::difference_type	difference_type;
		typedef typename traits::pointer			pointer;
		typedef typename traits::reference			reference;

		_rbtree_iterator(node_pointer x = NULL) :
		x(x)
		{}

		_rbtree_iterator(const iterator &other)
		{
			*this = other;
		}

		~_rbtree_iterator()
		{}

		_rbtree_iterator &operator=(const iterator &other)
		{
			x = other.base();
			return *this;
		}

		node_pointer base() const
		{
			return static_cast<node_pointer>(x);
		}

		reference operator*() const
		{
			return base()->value;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		_rbtree_iterator &operator++()
		{
			if (x->right)
				x = x->right->minimum();
			else
			{
				base_node_pointer y = x->parent;
				while (y && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				if (x->right != y)
					x = y;
			}
			return *this;
		}

		_rbtree_iterator operator++(int)
		{
			_rbtree_iterator tmp = *this;
			++*this;
			return tmp;
		}

		_rbtree_iterator &operator--()
		{
			if (x->color == node_type::RED && x->gparent() == x)
				x = x->right;
			else if (x->left)
				x = x->left->maximum();
			else
			{
				base_node_pointer y = x->parent;
				while (x == y->left)
				{
					x = y;
					y = y->parent;
				}
				x = y;
			}
			return *this;
		}

		_rbtree_iterator operator--(int)
		{
			_rbtree_iterator tmp = *this;
			--*this;
			return tmp;
		}

		// Non-member functions:
		friend inline bool operator==(const _rbtree_iterator &x, const _rbtree_iterator &y)
		{
			return x.base() == y.base();
		}

		friend inline bool operator!=(const _rbtree_iterator &x, const _rbtree_iterator &y)
		{
			return !(x == y);
		}

	protected:
		base_node_pointer x;
	};

	template<class Key, class Value, class KeyGetter, class Compare, class Allocator>
	class _rbtree
	{
	public:
		typedef Key					key_type;
		typedef Value				value_type;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef Compare				key_compare;

	private:
		typedef KeyGetter										key_getter;
		typedef _rbtree_node_base::node_type					base_node_type;
		typedef base_node_type::pointer							base_node_pointer;
		typedef typename _rbtree_node<value_type>::node_type	node_type;
		typedef typename node_type::pointer						node_pointer;
		typedef typename node_type::color_type					color_type;

	public:
		typedef typename Allocator::template rebind<node_type>::other			allocator_type;
		typedef _rbtree_iterator<value_type, pointer, reference>				iterator;
		typedef _rbtree_iterator<value_type, const_pointer, const_reference>	const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		explicit _rbtree(const Compare &comp = Compare(), const Allocator &alloc = Allocator()) :
		_allocator(alloc), _comparator(comp), _size(0)
		{
			init();
		}
		
		_rbtree(const _rbtree &other) :
		_allocator(other._allocator), _comparator(other._comparator), _size(0)
		{
			init();
			*this = other;
		}
		
		~_rbtree()
		{
			clear();
		}
		
		_rbtree &operator=(const _rbtree &other)
		{
			clear();
			if (other.size())
			{
				root() = copy(other.root(), _header);
				leftmost() = root()->minimum();
				rightmost() = root()->maximum();
				_size = other.size();
			}
			return *this;
		}

		allocator_type get_allocator() const
		{
			return _allocator;
		}

		// Iterators:
		iterator begin()
		{
			return iterator(leftmost());
		}

		const_iterator begin() const
		{
			return const_iterator(leftmost());
		}

		iterator end()
		{
			return iterator(_header);
		}

		const_iterator end() const
		{
			return const_iterator(_header);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		// Capacity:
		bool empty() const
		{
			return !size();
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return get_allocator().max_size();
		}

		// Modifiers:
		void clear()
		{
			if (empty())
				return ;
			clear(root());
			init();
			_size = 0;
		}

		pair<iterator, bool> insert(const value_type &value)
		{
			node_pointer x = root();
			node_pointer y = _header;
			bool comp_value = true;
			while (x)
			{
				y = x;
				comp_value = compare(value, x->value);
				x = comp_value ? x->left_link() : x->right_link();
			}
			iterator i(y);
			if (comp_value)
			{
				if (i == begin())
					return ft::make_pair(insert_node(x, y, value), true);
				--i;
			}
			if (compare(i.base()->value, value))
				return ft::make_pair(insert_node(x, y, value), true);
			return ft::make_pair(i, false);
		}

		iterator insert(iterator hint, const value_type &value)
		{
			if (hint == begin())
			{
				if (_size && compare(value, hint.base()->value))
					return insert_node(hint.base(), hint.base(), value);
				return insert(value).first;
			}
			if (hint == end())
			{
				if (compare(rightmost()->value, value))
					return insert_node(NULL, rightmost(), value);
				return insert(value).first;
			}
			iterator prev = hint;
			--prev;
			if (compare(prev.base()->value, value) && compare(value, hint.base()->value))
			{
				if (prev.base()->right)
					return insert_node(hint.base(), hint.base(), value);
				return insert_node(NULL, prev.base(), value);
			}
			return insert(value).first;
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while (first != last)
				insert(*first++);
		}

		void erase(iterator pos)
		{
			node_pointer z = pos.base();
			if (z == leftmost())
				_header->left = z->right ? z->right->minimum() : z->parent;
			if (z == rightmost())
				_header->right = z->left ? z->left->maximum() : z->parent;
			z->remove(_header->parent);
			destroy_node(z);
			--_size;
		}

		size_type erase(const Key &key)
		{
			pair<iterator, iterator> range = equal_range(key);
			size_type n = ft::distance(range.first, range.second);
			erase(range.first, range.second);
			return n;
		}

		void erase(iterator first, iterator last)
		{
			if (first == begin() && last == end())
				clear();
			else
				while (first != last)
					erase(first++);
		}

		void swap(_rbtree &other)
		{
			ft::swap(_comparator, other._comparator);
			ft::swap(_header_storage, other._header_storage);
			ft::swap(_size, other._size);
			if (size())
				root()->parent = _header;
			else
				init();
			if (other.size())
				other.root()->parent = other._header;
			else
				other.init();
		}

		// Lookup:
		size_type count(const Key &key) const
		{
			pair<const_iterator, const_iterator> range = equal_range(key);
			return ft::distance(range.first, range.second);
		}

		iterator find(const Key &key)
		{
			iterator i = lower_bound(key);
			return i == end() || _comparator(key, _getter(i.base()->value)) ? end() : i;
		}

		const_iterator find(const Key &key) const
		{
			const_iterator i = lower_bound(key);
			return i == end() || _comparator(key, _getter(i.base()->value)) ? end() : i;
		}

		pair<iterator, iterator> equal_range(const Key &key)
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		pair<const_iterator, const_iterator> equal_range(const Key &key) const
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		iterator lower_bound(const Key &key)
		{
			node_pointer x = root();
			node_pointer y = _header;
			while (x)
				if (_comparator(_getter(x->value), key))
					x = x->right_link();
				else
					y = x, x = x->left_link();
			return iterator(y);
		}

		const_iterator lower_bound(const Key &key) const
		{
			node_pointer x = root();
			node_pointer y = _header;
			while (x)
				if (_comparator(_getter(x->value), key))
					x = x->right_link();
				else
					y = x, x = x->left_link();
			return const_iterator(y);
		}

		iterator upper_bound(const Key &key)
		{
			node_pointer x = root();
			node_pointer y = _header;
			while (x)
				if (_comparator(key, _getter(x->value)))
					y = x, x = x->left_link();
				else
					x = x->right_link();
			return iterator(y);
		}

		const_iterator upper_bound(const Key &key) const
		{
			node_pointer x = root();
			node_pointer y = _header;
			while (x)
				if (_comparator(key, _getter(x->value)))
					y = x, x = x->left_link();
				else
					x = x->right_link();
			return const_iterator(y);
		}

		// Observers:
		key_compare key_comp() const
		{
			return _comparator;
		}

		// Non-member functions:
		friend inline bool operator==(const _rbtree &x, const _rbtree &y)
		{
			return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
		}

		friend inline bool operator!=(const _rbtree &x, const _rbtree &y)
		{
			return !(x == y);
		}

		friend inline bool operator<(const _rbtree &x, const _rbtree &y)
		{
			return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}

		friend inline bool operator<=(const _rbtree &x, const _rbtree &y)
		{
			return !(x > y);
		}

		friend inline bool operator>(const _rbtree &x, const _rbtree &y)
		{
			return y < x;
		}

		friend inline bool operator>=(const _rbtree &x, const _rbtree &y)
		{
			return !(x < y);
		}

		friend inline void swap(_rbtree &x, _rbtree &y)
		{
			x.swap(y);
		}

	private:
		allocator_type	_allocator;
		key_compare		_comparator;
		key_getter		_getter;
		node_pointer	_header;
		base_node_type	_header_storage; // end() (should not be dereferenced)
		size_type		_size;

		inline node_pointer allocate_node(const node_type &node_value)
		{
			node_pointer n = _allocator.allocate(1);
			_allocator.construct(n, node_value);
			return n;
		}

		inline node_pointer clone_node(node_pointer x)
		{
			return allocate_node(node_type(x->value, x->color));
		}

		inline void destroy_node(node_pointer n)
		{
			_allocator.destroy(n);
			_allocator.deallocate(n, 1);
		}

		inline bool compare(const value_type &a, const value_type &b) const
		{
			return _comparator(_getter(a), _getter(b));
		}

		inline void init()
		{
			_header = static_cast<node_pointer>(&_header_storage);
			root() = NULL;
			leftmost() = _header;
			rightmost() = _header;
		}

		inline node_pointer &root() const
		{
			return reinterpret_cast<node_pointer&>(_header->parent);
		}

		inline node_pointer &leftmost() const
		{
			return reinterpret_cast<node_pointer&>(_header->left);
		}

		inline node_pointer &rightmost() const
		{
			return reinterpret_cast<node_pointer&>(_header->right);
		}

		iterator insert_node(node_pointer x, node_pointer y, const value_type &v)
		{
			node_pointer z = allocate_node(node_type(v));
			z->parent = y;
			if (y == _header || x || compare(v, y->value))
			{
				y->left = z;
				if (y == _header)
				{
					root() = z;
					_header->right = z;
				}
				else if (y == leftmost())
					leftmost() = z;
			}
			else
			{
				y->right = z;
				if (y == rightmost())
					rightmost() = z;
			}
			z->insert_fixup(_header->parent);
			++_size;
			return iterator(z);
		}

		inline node_pointer copy(node_pointer x, node_pointer parent)
		{
			node_pointer top = clone_node(x);
			top->parent = parent;
			if (x->right)
				top->right = copy(x->right_link(), top);
			parent = top;
			while ((x = x->left_link()))
			{
				node_pointer y = clone_node(x);
				parent->left = y;
				y->parent = parent;
				if (x->right)
					y->right = copy(x->right_link(), y);
				parent = y;
			}
			return top;
		}

		void clear(node_pointer x)
		{
			if (!x)
				return ;
			clear(x->left_link());
			clear(x->right_link());
			destroy_node(x);
		}
	};
}
