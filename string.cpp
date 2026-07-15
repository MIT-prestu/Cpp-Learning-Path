#pragma once
#include <iostream>
#include <cassert>
#include <cstring> 

namespace CYX {
	class string {
	public:
		typedef char* iterator;
		typedef const char* const_iterator; 

		string(const char* str = "") {
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		string(const string& s)
			: _str(new char[s._capacity + 1])
			, _size(s._size)
			, _capacity(s._capacity)
		{
			strcpy(_str, s._str);
		}

		
		void swap(string& s) {
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		
		string& operator=(string s) {
			this->swap(s);
			return *this;
		}

		
		void clear() {
			_size = 0;
			_str[0] = '\0';
		}

		char& operator[](size_t i) {
			assert(i < _size);
			return _str[i];
		}

		const char& operator[](size_t i) const {
			assert(i < _size);
			return _str[i];
		}

		
		const_iterator begin() const { return _str; }
		const_iterator end() const { return _str + _size; }

		iterator begin() { return _str; }
		iterator end() { return _str + _size; }

		const char* c_str() const { return _str; }
		size_t size() const { return _size; }
		size_t capacity() const { return _capacity; }

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
			if (_size == _capacity) {
				size_t newcapacity = _capacity == 0 ? 4 : 2 * _capacity;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';
		}

		void append(const char* str) {
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				size_t newcapacity = 2 * _capacity;
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
				size_t newcapacity = _capacity == 0 ? 4 : 2 * _capacity;
				reserve(newcapacity);
			}
			size_t end = _size + 1;
			while (end > pos) {
				_str[end] = _str[end - 1];
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
				size_t newcapacity = 2 * _capacity;
				if (_size + len > newcapacity) {
					newcapacity = _size + len;
				}
				reserve(newcapacity);
			}
			size_t end = _size;
			while (end >= pos) {
				_str[end + len] = _str[end];
				if (end == pos) break;
				end--;
			}
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
					size_t newcapacity = _capacity * 2;
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

inline std::ostream& operator<<(std::ostream& out, const CYX::string& s) {
	for (size_t i = 0; i < s.size(); i++) {
		out << s[i];
	}
	return out;
}

inline std::istream& operator>>(std::istream& in, CYX::string& s) {
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
