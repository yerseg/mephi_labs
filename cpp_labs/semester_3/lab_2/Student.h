#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

using namespace std;

class Student {
private:
	int flag;
public:
	string name;
	struct Birthday {

		unsigned int day, month, year;

		const bool operator== (const Birthday &birth) {
			return (day == birth.day && month == birth.month && year == birth.year);
		}
		const bool operator>(const Birthday &birth) {
			if (year > birth.year)
				return true;
			else if (year == birth.year && month > birth.month)
				return true;
			else if (year == birth.year && month == birth.month && day > birth.day)
				return true;
			else return false;
		}
		const bool operator<(const Birthday &birth) {
			if (year < birth.year)
				return true;
			else if (year == birth.year && month < birth.month)
				return true;
			else if (year == birth.year && month == birth.month && day < birth.day)
				return true;
			else return false;
		}
		const bool operator<=(const Birthday &birth) {
			if (year <= birth.year)
				return true;
			else if (year == birth.year && month <= birth.month)
				return true;
			else if (year == birth.year && month == birth.month && day <= birth.day)
				return true;
			else return false;
		}
		const bool operator>=(const Birthday &birth) {
			if (year >= birth.year)
				return true;
			else if (year == birth.year && month >= birth.month)
				return true;
			else if (year == birth.year && month == birth.month && day >= birth.day)
				return true;
			else return false;
		}
		const bool operator!=(const Birthday &birth) {
			return (day != birth.day || month != birth.month || year != birth.year);
		}
		friend ostream& operator << (ostream &s, Birthday &birth) {
			s << "Дата рождения: " << birth.day << '/' << birth.month << '/' << birth.year;
			return s;
		}
	} birthday;

	const bool operator==(const Student &student) {
		if (this->flag == 1) 
			return (name == student.name);
		else if (this->flag == 0)
			return (name == student.name && birthday == student.birthday);
		else 
			return (birthday == student.birthday);
	}
	const bool operator>(const Student &student) {
		if (flag == 1) 
			return (name > student.name);
		else if (flag == 0) {
			if (birthday > student.birthday && name != student.name)
				return true;
			else if (birthday < student.birthday)
				return false;
			else if (birthday == student.birthday)
				return (name > student.name);
		}
		else 
			return (birthday > student.birthday);
	}
	const bool operator<(const Student &student) {
		if (flag == 1) return (name < student.name);
		else if (flag == 0) {
			if (birthday < student.birthday && name != student.name)
				return true;
			else if (birthday > student.birthday)
				return false;
			else if (birthday == student.birthday)
				return (name < student.name);
		}
		else return (birthday < student.birthday);
	}
	const bool operator<=(const Student &student) {
		if (flag == 1) return (name <= student.name);
		else if (flag == 0) {
			if (birthday < student.birthday)
				return true;
			else if (birthday > student.birthday)
				return false;
			else if (birthday == student.birthday)
				return (name <= student.name);
		}
		else return (birthday <= student.birthday);
	}
	const bool operator>=(const Student &student) {
		if (flag == 1) return (name >= student.name);
		else if (flag == 0) {
			if (birthday > student.birthday)
				return true;
			else if (birthday < student.birthday)
				return false;
			else if (birthday == student.birthday)
				return (name >= student.name);
		}
		else return (birthday >= student.birthday);
	}
	const bool operator!=(const Student &student) {
		if (flag == 1) return (name != student.name);
		else if (flag == 0)
			return (name != student.name && birthday != student.birthday);
		else return (birthday != student.birthday);
	}
	friend ostream& operator << (ostream &s, Student &st) {
		s << "Студент " << st.name << " " << st.birthday;
		return s;
	}

	Student(string name_, int day_, int month_, int year_) {
		name = name_;
		birthday.day = day_;
		birthday.month = month_;
		birthday.year = year_;
	}

	Student() {}

	~Student() {}

	void set_flag(int flag_) {
		flag = flag_;
	}

	string GetName() {
		return name;
	}
};

#endif /* STUDENT_H */
