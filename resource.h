#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class resource {
	private:
		string rname;
		string state = "R";
		int num = 1;
		int s_date = 0;
		int e_date = 0;

	public:
		void set(string n, string st, int s_d, int e_d);
		string pname();
		string pstate();
		int psd();
		int ped();
};

class book:public resource{};
class magazine:public resource{};
class e_book:public resource{};

void resource :: set(string n, string st, int s_d, int e_d){
	rname = n;
	state = st;
	s_date = s_d;
	e_date = e_d;
}

int transdate(string d){
	return ((d.at(0)-48)*10 + (d.at(1)-48))*360 + ((d.at(3)-48)*10 + (d.at(4)-48))*30 + (d.at(6)-48)*10 + (d.at(7)-48);
}

string resource :: pname(){
	return rname;
}

string resource :: pstate(){
	return state;
}

int resource :: psd(){
	return s_date;
}

int resource :: ped(){
	return e_date;
}

void pday(int day){
	int y,m,d;
	y = day/360;
	m = (day-360*y)/30;
	d = day-360*y-30*m;
	int y1 = y/10;
	int y2 = y%10;
	int m1 = m/10;
	int m2 = m%10;
	int d1 = d/10;
	int d2 = d%10;
	cout << y1 << y2 << '/' << m1 << m2 << '/' << d1 << d2 << endl;
}
