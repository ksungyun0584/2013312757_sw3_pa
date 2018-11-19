#include "resource.h"

class member {
	private:
		string mname;
		vector<book> books;
		vector<magazine> magazines;
		vector<e_book> e_books;
		int seatnum=50;
		int studynum=50;
		int seattime=24;
		int studytime=24;
		int etime=24;

		int penalty = 0;
		int b_num = 0;
		int m_num = 0;
		int e_num = 0;

	public:
		void set(string n, int p);
		void b_set(string n, int sd, int ed);
		void st_set(int sn, int t);
		void sy_set(int st, int t);
		string pname();
		int pbnum();
		int ppenalty();
		book searchbook(string s);
		void returnbook(string n);

		void eset(int et);
		int psn();
		int pst();
		int pt(string st);
		int pet();
};

class undergraduate:public member{};
class graduate:public member{};
class faculty:public member{};

book member :: searchbook(string s){
	class book b;
	b.set("n","n",0,0);
	for (int i=0;i<b_num;i++){
		if(s == books.at(i).pname()) return books.at(i);
	}
	return b;
}

void member :: eset(int et){
	etime = et;
}

int member :: pet(){
	return etime;
}

int member :: pt(string st){
	if(st == "Seat")
		return seattime;
	if(st == "StudyRoom")
		return studytime;
	else
		return 0;
}

int member :: psn(){
	return seatnum;
}

int member :: pst(){
	return studynum;
}

void member :: st_set(int sn, int t){
	seatnum = sn;
	seattime = t;
}

void member :: sy_set(int st, int t){
	studynum = st;
	studytime = t;
}

string member :: pname(){
	return mname;
}

int member :: pbnum(){
	return b_num;
}

int member :: ppenalty(){
	return penalty;
}

void member :: set(string n, int p){
	penalty = p;
	mname = n;
}

void member :: b_set(string n, int sd, int ed){
	class book b;
	b.set(n,"B",sd,ed);
	books.push_back(b);
	b_num++;
}

void member :: returnbook(string n){
	int i;
	class book b;
	if(b_num == 1){
		books.pop_back();
		b_num--;
		return;
	}
	for(i=0;i<b_num-1;i++){
		if(books.at(i).pname() == n) {
			b = books.at(i);
			books.at(i) = books.at(i+1);
			books.at(i+1) = b;
		}
	}
	books.pop_back();
	b_num--;
	return;
}
