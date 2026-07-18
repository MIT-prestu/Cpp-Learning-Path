#include <iostream>
#include <assert.h>


namespace CYX {

	template<class T>
	struct __list_node {
		__list_node* _next;
		__list_node* _prev;
		T _data;

		__list_node(const T& val = T())
			:_next(nullptr)
			,_prev(nullptr)
			, _data(val)
		{}
	};


	template<class T, class Ref, class Ptr>
	struct __list_iterator {
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> Self;

		__list_iterator(Node* node) :_node(node){}

		Ref operator*() {
			return _node->_data;
		}

		Ptr operator->() {
			return &(_node->_data);
		}

		Self& operator++() {
			_node = _node->_next;
			return *this;
		}

		Self operator++(int) {
			Self tmp(*this);
			_node = _node->_next;

			return tmp;
		}

		bool operator!=(const Self& it) const{
			return _node != it._node;
		}

		Node* _node;
	};



	template<class T>
	class List {
	public:
		typedef __list_node<T>  Node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		List(){
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;

		}

		~List(){
			clear();
			delete _head;
			_head = nullptr;
		}

		//List l1 = l2
		List(const List& lt) {
			 _head = new Node;
			 _head->_next = _head;
			 _head->_prev = _head;

			for (const auto& e : lt) {
				push_back(e);
			}
		}


		List& operator=(List lt) {
			std::swap(_head, lt._head);

			return *this;
		}

		iterator begin() { return iterator(_head->_next); }
		iterator  end() { return iterator(_head); }
		const_iterator begin()const { return const_iterator(_head->_next); }
		const_iterator end()const { return const_iterator(_head); }

		void clear() {
			iterator it = begin();
			while (it != end()) {
				it = erase(it);
			}
		}

		void push_back(const T& x) {
			//Node* newnode = new Node(x);

			//Node* prev = _head->_prev;
			////prev newnode head
			//
			//newnode->_next = _head;
			//newnode->_prev = prev;
			//prev->_next = newnode;
			//_head->_prev = newnode;

			insert(end(), x);
		}

		void push_front(const T& x) {
			insert(begin(), x);
		}



		void pop_back() {
			assert(_head->_next != _head);

			/*Node* prev = _head->_prev->_prev;
			
			delete _head->_prev;

			prev->_next = _head;
			_head->_prev = prev;*/
			erase(iterator(_head->_prev));

		}


		void pop_front() {
			assert(_head->_next != _head);

			erase(begin());
		}

		iterator insert(iterator pos, const T& x) {
			Node* newnode = new Node(x);
			
			Node* cur = pos._node;
			Node* prev = cur->_prev;

			//prev newnode cur
			newnode->_next = cur;
			newnode->_prev = prev;
			cur->_prev = newnode;
			prev->_next = newnode;

			return iterator(newnode);
		}


		iterator erase(iterator pos) {
			assert(pos != end());

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			// prev  cur next

			prev->_next = next;
			next->_prev = prev;

			delete cur;
			cur = nullptr;

			return iterator(next);

		}

	private:
		Node* _head;
	};


};