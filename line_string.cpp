#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class line_string {
	string s;
public:
	line_string() {

	}

	line_string(string s1) {
		s = s1;
	}

	bool operator>(line_string ls) {
		if (s > ls.s) {
			return true;

		} else {
			return false;
		}
	}

	bool operator==(line_string ls) {
		if (s == ls.s) {
			return true;
			
		} else {
			return false;
		}
	}

	friend std::ostream& operator<<(std::ostream &out, const line_string &ls) {
		out << ls.s;
		return out;
	}

	friend std::string to_string(line_string const& ls) {
		return ls.s;
	}

	~line_string() {

	}
};