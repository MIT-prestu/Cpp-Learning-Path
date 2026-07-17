#include <iostream>
#include <assert.h>


namespace CYX {
	template <class T>
	class vector {
	public:
		typedef    T*     iterator;
		typedef const T*  const_iterator;


		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{ }

		vector(const vector<T>& v) : _start(nullptr), _finish(nullptr), _endofstorage(nullptr) {
			reserve(v.capacity());
			for (size_t i = 0; i < v.size(); ++i) {
				push_back(v[i]);
			}
		}

		//v1 = v2
		vector<T>& operator=(vector<T> v) {
			
			Swap(v);
			
			return *this;
		}

		void Swap(vector<T>& v) {

			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);

		}


		iterator begin() { return _start; }
		iterator end() { return _finish }
		const_iterator begin()const { return _start }
		const_iterator end()const { return _finish }

		T& operator[](size_t i) {
			assert(i < size());
			return *(_start + i);
		}

		const T& operator[](size_t i)const {
			assert(i < size());
			return *(_start + i);
		}


		void reserve(size_t n) {
			if (n > capacity()) {

				size_t old_size = size();
				T* tmp = new T[n];

				if (_start) {
					
					for (size_t i = 0; i < old_size; i++) {
						tmp[i] = _start[i];
					}
					delete[] _start;
				}

				_start = tmp;
				_finish = _start + old_size;
				_endofstorage = _start + n;
			}

		}

		void resize(size_t n, const T& val = T()) {
			if (n < size()) {
				_finish = n + _start;;
			}
			else {
				if (n > capacity()) {
					reserve(n);
				}
				
				T* des = _start + n;
				while (_finish < des) {
					*(_finish) = val;
					_finish++;
				}
			}
		}


		void push_back(const T& x) {
			if (_finish == _endofstorage) {
				size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newcapacity);
			}

			*_finish = x;
			_finish++;
		}


		void pop_back() {
			assert(size() > 0);

			--_finish;
		}

		iterator insert(iterator pos, const T& x) {
			assert(pos >= _start && pos <= _finish);
			if(_finish == _endofstorage){
				size_t offset = pos - _start;
				size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newcapacity);
				pos = _start + offset;
			}

			iterator end = _finish - 1;
			while (end >= pos) {
				*(end + 1) = *end;
				end--;
			}

			*pos = x;
			_finish++;
			return pos;
		}


		iterator erase(iterator pos) {
			assert(pos >= _start && pos < _finish);

			iterator end = pos + 1;
			while (end < _finish) {
				*(end - 1) = *end;
				end++;
			}

			--_finish;
			return pos;
		}



		size_t size()const {
			return _finish - _start;
		}

		size_t capacity()const{
			return _endofstorage - _start;
		}



		~vector() {
			if (_start)
				delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}


	private:
		T* _start;
		T* _finish;
		T* _endofstorage;
	};
}