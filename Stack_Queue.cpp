#include <iostream>
#include <deque>
#include <vector>
#include <assert.h>



namespace CYX {
	template <class T, class Container = std::deque<T>>
	class Stack {
	public:

		void push(const T& x) { _con.push_back(x); }
		void pop() { _con.pop_back(); }
		
		T& top() { return _con.back(); }
		const T& top()const { return _con.back(); }

		bool empty()const { return _con.empty(); }
		size_t size()const { return _con.size(); }

	private:
		Container _con;
	};




	template <class T, class Container = std::deque<T>>
	class Queue {
	public:
		void push(const T& x) { _con.push_back(x); }
		void pop() { _con.pop_front(); }

		T& front() { return _con.front(); }
		const T& front() const { return _con.front(); }

		T& back() { return _con.back(); }
		const T& back() const { return _con.back(); }

		bool empty() const { return _con.empty(); }
		size_t size() const { return _con.size(); }
	private:
		Container _con;
	};


	template<class T>
	struct Less {
		bool operator()(const T& x, const T& y) const {
			return x < y; 
		}
	};

	template<class T>
	struct Greater {
		bool operator()(const T& x, const T& y) const {
			return x > y; 
		}
	};


	template <class T, class Container = std::vector<T>, class Compare = Less<T>>
	class Priority_Queue {
	public:
		void push(const T& x) {
			_con.push_back(x);
			AdjustUp(_con.size()-1);
		}

		void pop() {
			assert(!_con.empty());
			std::swap(_con[0], _con[size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}

		const T& top() const{
			assert(!_con.empty());
			return _con[0];
		}

		bool empty() const{
			return _con.empty();
		}

		size_t size()const {
			return _con.size();
		}
	private:
		void AdjustUp(size_t child) {
			Compare comp;
			size_t parent = (child - 1) / 2;

			while (child > 0) {
				//Big heap
				if (comp(_con[parent], _con[child])) {
					std::swap(_con[parent], _con[child]);

					child = parent;
					parent = (child - 1) / 2;

				}
				else {
					break;
				}
			}
		}

		void AdjustDown(size_t parent) {
			Compare comp;
			size_t child = parent * 2 + 1;

			while (child < _con.size()) {
				if (child + 1 < _con.size() && comp(_con[child], _con[child + 1])) {
					child++;
				}
				if (comp(_con[parent], _con[child])) {
					std::swap(_con[parent], _con[child]);

					parent = child;
					child = parent * 2 + 1;
				}
				else {
					break;
				}
			}
		}
		Container _con;
	};
}