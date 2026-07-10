#include <iostream>
using namespace std;


class Date {
public:

	int GetDayOfMonth(int year, int month) {
		static int GetMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
			return 29;
		}

		return GetMonth[month];
	}
	
	Date(int year = 0, int month = 1, int day = 1) {
		if (year > 0 && 
			month > 0 && month <= 12 &&
			day > 0 && day <= GetDayOfMonth(year, month)) {

			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "Error, wrong value" << endl;
		}
	}

	Date(const Date& d) {
		
		_year = d._year;
		_month = d._month;
		_day = d._day;
		
	}
		


	Date& operator=(const Date& d) {

		if (this != &d) {
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		

		return *this;
	}


	bool operator==(const Date& d) {
		return _year == d._year && _month == d._month && _day == d._day;
	}

	bool operator!=(const Date& d) {
		return !(*this == d);
	}

	bool operator>(const Date& d) {
		if (_year > d._year) {
			return true;
		}
		else if (_year == d._year && _month > d._month) {
			return true;
		}
		else if (_year == d._year && _month == d._month && _day > d._day) {
			return true;
		}

		return false;
	}

	bool operator<(const Date& d) {
		return !(*this >= d);
	}

	bool operator>=(const Date& d) {
		return *this == d || *this > d;
	}

	bool operator<=(const Date& d) {
		return !(*this > d);
	}

	Date operator+(int day) {
		Date ret = *this;

		ret += day;

		return ret;
	}

	Date& operator+=(int day) {

		if (day < 0) {
			return *this -= -day;
		}

		_day += day;
		while (_day > GetDayOfMonth(_year, _month)) {
			_day -= GetDayOfMonth(_year, _month);

			_month++;
			if (_month == 13) {
				_month = 1;
				_year++;
			}
		}

		return *this;
	}


	Date& operator-=(int day) {
		if (day < 0) {
			return *this += -day;
		}

		_day -= day;
		while (_day < 0) {
			_day += GetDayOfMonth(_year, _month);

			_month--;
			if (_month == 0) {
				_month = 12;
				_year--;
			}
		}

		return *this;
	}

	Date operator-(int day) {
		Date ret = *this;

		ret -= day;

		return ret;
	}

	Date& operator++() {
		return *this += 1;
	}

	Date operator++(int) {
		Date ret = *this;
		*this += 1;
		return ret;
	}

	Date& operator--() {
		return *this -= 1;
	}

	Date operator--(int) {
		Date ret = *this;
		*this -= 1;
		return ret;
	}


	~Date() {

	}



private:
	int _year;
	int _month;
	int _day;
};















int main() {
	return 0;
}