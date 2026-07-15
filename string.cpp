#pragma once
#include <assert.h>
#include <iostream>
using namespace std;

namespace CYX {
	class string {
	public:
		typedef char* iterator;

		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//String s2(s1)
		string(const string& s)
			:_str(new char[s._size + 1])
			, _size(s._size)
			, _capacity(s._size)
		{
			strcpy(_str, s._str);
		}


		//s2 = s1
		string& operator=(const string& s) {

			if (this != &s) {
				char* newstr = new char[s._size + 1];

				strcpy(newstr, s._str);

				delete[] _str;

				_str = newstr;
				_size = s._size;
				_capacity = s._size;
			}

			return *this;
		}

		char& operator[](size_t i){
			assert(i < _size);

			return _str[i];
		}

		const char& operator[](size_t i) const{
			assert(i < _size);

			return _str[i];
		}

		const iterator begin() const{
			return _str;
		}

		const iterator end() const{
			return _str + _size;
		}

		iterator begin() {
			return _str;
		}

		iterator end() {
			return _str + _size;
		}

		char* c_str() const{
			return _str;
		}

		size_t size() const{
			return _size;
		}

		size_t capacity() const{
			return _capacity;
		}

		void reserve(size_t n) {
			if (n > _capacity) {
				char* newstr = new char[n + 1];

				strcpy(newstr, _str);

				delete[] _str;
				_str = newstr;
				_capacity = n;
			}
			

		}

		void push_back(char ch) {

			if (_size ==_capacity) {
				int newcapacity = _capacity == 0 ? 4 : 2 * _capacity;
				reserve(newcapacity);
			}

			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';

		}

		void append(const char* str) {

			size_t len = strlen(str);

			if (_size + len > _capacity) {
				int newcapacity = 2 * _capacity;
				if (_size + len > newcapacity) {
					newcapacity = _size + len;
				}
				reserve(newcapacity);
			}

			strcpy(_str + _size, str);
			_size += len;
		}

		string& insert(size_t pos, char ch) {
			assert(pos <= _size);

			if (_size == _capacity) {
				int newcapacity = _capacity == 0 ? 4 : 2 * _capacity;
				reserve(newcapacity);
			}

			size_t end = _size+1;
			while (end > pos) {
				_str[end] = _str[end-1];
				end--;
			}

			_str[pos] = ch;
			_size++;

			return *this;
		}

		string& insert(size_t pos, const char* str) {
			assert(pos <= _size);

			size_t len = strlen(str);
			if (_size + len > _capacity) {
				int newcapacity = 2 * _capacity;
				if (_size + len > newcapacity) {
					newcapacity = _size + len;
				}
				reserve(newcapacity);
			}

			size_t end = _size;
			while (end > pos) {
				_str[end+len] = _str[end];
				end--;
			}

			//strncpy(_str + pos, str, len);
			memcpy(_str + pos, str, len);
			_size += len;

			return *this;
		}


		void resize(size_t n, char ch = '\0') {
			if (n < _size) {
				_size = n;
				_str[_size] = '\0';
			}
			else {
				if (n > _capacity) {
					int newcapacity = _capacity * 2;
					if (newcapacity < n) {
						newcapacity = n;
					}
					reserve(newcapacity);
				}

				while (_size < n) {
					_str[_size++] = ch;
				}
		
				_str[_size] = '\0';
			}
		}

		string& erase(size_t pos = 0, size_t len = npos) {
			assert(pos <= _size);

			if (len == npos || len >= _size - pos) {
				_str[pos] = '\0';
				_size = pos; 
			}
			else {
				size_t end = pos + len;
				while (end <= _size) {
					_str[end - len] = _str[end];
					end++;
				}
				_size -= len;
			}

			return *this; 
		}


		size_t find(char ch, size_t pos = 0) const {
			assert(pos <= _size);

			for (size_t i = pos; i < _size; ++i) {
				if (_str[i] == ch) {
					return i; 
				}
			}

			return npos;
		}


		size_t find(const char* str, size_t pos = 0) const {
			assert(pos <= _size);

			const char* ptr = strstr(_str + pos, str);

			if (ptr == nullptr) {
				return npos; 
			}


			return ptr - _str;
		}



		string& operator+=(char ch) {

			this->push_back(ch);
			return *this;

		}


		string& operator+=(const char* str) {

			this->append(str);
			return *this;

		}



		~string() {
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}




	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		static const size_t npos = -1;
	};
}

ostream& operator<<(ostream& out, const string& s) {
	for (int i = 0; i < s.size(); i++) {
		out << s[i];
	}
	return out;
}

std::istream& operator>>(std::istream& in, string& s) {
	s.clear();

	char ch = in.get();

	while (ch == ' ' || ch == '\n' || ch == '\t') {
		ch = in.get(); 
	}

	char buff[128] = { 0 };
	size_t i = 0;

	while (ch != ' ' && ch != '\n' && ch != '\t' && ch != EOF) {
		buff[i++] = ch;

		if (i == 127) {
			buff[i] = '\0'; 
			s += buff;      
			i = 0; 
		}

		ch = in.get(); 
	}

	if (i > 0) {
		buff[i] = '\0';
		s += buff;
	}

	return in; 
}