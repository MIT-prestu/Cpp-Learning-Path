#include <iostream>
using namespace std;


class Date {
public:

	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

	int GetDayOfMonth(int year, int month) const{
		static int GetMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
			return 29;
		}

		return GetMonth[month];
	}
	
	Date(int year = 1900, int month = 1, int day = 1) {
		if (year > 0 && month > 0 && month <= 12 && day > 0 && day <= GetDayOfMonth(year, month)) {
			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "Error, wrong date value! Initialize to 1900/1/1" << endl;
			_year = 1900; _month = 1; _day = 1;
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


	bool operator==(const Date& d) const{
		return _year == d._year && _month == d._month && _day == d._day;
	}

	bool operator!=(const Date& d) const{
		return !(*this == d);
	}

	bool operator>(const Date& d) const{
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

	bool operator<(const Date& d) const{
		return !(*this >= d);
	}

	bool operator>=(const Date& d) const{
		return *this == d || *this > d;
	}

	bool operator<=(const Date& d) const{
		return !(*this > d);
	}

	Date operator+(int day) const{
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
		while (_day <= 0) {
			_month--;
			if (_month == 0) {
				_month = 12;
				_year--;
			}
			_day += GetDayOfMonth(_year, _month);
		}

		return *this;
	}

	Date operator-(int day) const{
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

	int operator-(const Date& d) {
		Date min = d;
		Date max = *this;
		int flag = 1;

		if (d > *this) {
			max = d;
			min = *this;
			flag = -1;
		} 

		int count = 0;
		while (min != max) {
			count++;
			min++;
		}

		return flag * count;
	}



	~Date() {

	}



private:
	int _year;
	int _month;
	int _day;
};




ostream& operator<<(ostream& out, const Date& d) {
	out << d._year << "/" << d._month << "/" << d._day << endl;

	return out;
}

istream& operator>>(istream& in, Date& d) {
	in >> d._year >> d._month >> d._day;

	return in;
}

