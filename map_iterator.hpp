#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>
#include "utility.hpp"
#include "binary_tree.hpp"

namespace ft {

	template < typename T, class Allocator = std::allocator<T> >
	class BidirectionalIterator {

		public:
			typedef Allocator											allocator_type;
			typedef typename ft::iterator_traits<T*>::value_type		value_type;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef std::bidirectional_iterator_tag 					iterator_category;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef pointer												iterator_type;
			typedef node <value_type, allocator_type> *					node_pointer;
			
		private:
			node_pointer	_node;

			node_pointer tree_min(node_pointer n) const {
				while(n->left != NULL)
					n = n->left;
				return n;
			}

			node_pointer tree_max(node_pointer n) const {
				while (n->right != NULL)
					n = n->right;
				return n;
			}

		public:

		//	constructors and staff
			BidirectionalIterator(node_pointer node = 0) : _node(node) {}
			BidirectionalIterator(const BidirectionalIterator<value_type, allocator_type> &other) { *this = other; }
			virtual ~BidirectionalIterator() {}
			BidirectionalIterator &operator=( const BidirectionalIterator<value_type, allocator_type> &other) {
				if(this != &other)
					this->_node = other._node;
				return *this;
			}
		
		//	member functions
			node_pointer				node() const { return _node; }
			
		//	operators overload
			reference					operator*() const { return *(_node->value); }
			pointer						operator->() const { return _node->value; }
			// BidirectionalIterator&		operator++()  { _node->successor(); return *this; }

			// BidirectionalIterator& operator++() {
			// 	if (_node->right) {
			// 		_node = tree_min(_node->right);
			// 	}
			// 	else {
			// 		node_pointer y = _node->parent;
			// 		while (y != NULL && _node == y->right) {
			// 			_node = y;
			// 			y = y->parent;
			// 		}
			// 		_node = y;
			// 	}
			// 	return *this;
			// }

			void print_end() { std::cout << _node->is_end << "\n"; }

			BidirectionalIterator& operator++() {
				if(_node->right) 
					_node = tree_min(_node->right);
				else {
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->right) {
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return *this;
			}

			BidirectionalIterator&		operator++(int) {
				BidirectionalIterator tmp(_node);
				operator++();
				return tmp;
            }
			// BidirectionalIterator&		operator--() { --_node; return *this; }
			// BidirectionalIterator&		operator--(int) { return BidirectionalIterator(_node--); }
			
			bool operator==(const BidirectionalIterator &other) { return this->_node == other._node; }
			bool operator!=(const BidirectionalIterator &other) { return this->_node != other._node; }

	};	//	class BidirectionalIterator

}	//	namespace ft


#endif