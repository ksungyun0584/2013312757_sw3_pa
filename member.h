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
		int capacity = 0;

	public:
		void set(string n, int p);
		void b_set(string t, string n, int sd, int ed, int day);
		string pname();
		int pbnum(string t);
		int ppenalty();
		book searchbook(string s);
		magazine searchmagazine(string s, int day);
		e_book searchebook(string s);
		void returnbook(string t, string n, int day);
		void sca(int c);

		void st_set(int sn, int t);
		void sy_set(int st, int t);

		void eset(int et);
		int psn();
		int pst();
		int pt(string st);
		int pet();
		int pca();
		int met(string n, int d);
		int check(int date);
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

magazine member :: searchmagazine(string s, int day){
	class magazine m;
	m.set("n","n",0,0);
	for (int i=0;i<m_num;i++){
		if(s == magazines.at(i).pname() && day==magazines.at(i).psi()) return magazines.at(i);
	}
	return m;
}

e_book member :: searchebook(string s){
	class e_book e;
	e.set("n","n",0,0);
	for (int i=0;i<e_num;i++){
		if(s == e_books.at(i).pname()) return e_books.at(i);
	}
	return e;
}

int member :: check(int date){
	int i=0;
	for(i=0;i<b_num;i++){
		if(date > books.at(i).ped())
			return -1;
	}
	for(i=0;i<m_num;i++){
		if(date > magazines.at(i).ped())
			return -1;
	}
	for(i=0;i<e_num;i++){
		if(date > e_books.at(i).ped())
			return -1;
	}
	return 0;
}

void member :: eset(int et){
	etime = et;
}

int member :: pet(){
	return etime;
}

int member :: met(string n, int d){
	for(int i=0;i<m_num;i++){
		if(magazines.at(i).pname() == n && magazines.at(i).psi() == d){
			return magazines.at(i).ped();
		}
	}
	return -1;
}
int member :: pca(){
	return capacity;
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

int member :: pbnum(string t){
	if(t=="Book")
		return b_num;
	if(t=="Magazine")
		return m_num;
	if(t=="E-book")
		return e_num;
}

void member :: sca(int c){
	capacity = c;
}

int member :: ppenalty(){
	return penalty;
}

void member :: set(string n, int p){
	penalty = p;
	mname = n;
}

void member :: b_set(string t, string n, int sd, int ed, int day){
	if(t == "Book"){
		class book b;
		b.set(n,"B",sd,ed);
		books.push_back(b);
		b_num++;
		return;
	}
	if(t == "Magazine"){
		class magazine m;
		m.set(n,"B",sd,ed);
		m.ssize(day);
		magazines.push_back(m);
		m_num++;
		return;
	}
	if(t == "E-book"){
		class e_book e;
		e.set(n,"B",sd,ed);
		e_books.push_back(e);
		e_num++;
		return;
	}
}

void member :: returnbook(string t, string n, int day){
	int i;
	if(t == "Book"){
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
	if(t == "Magazine"){
		class magazine m;
		if(m_num == 1){
			magazines.pop_back();
			m_num--;
			return;
		}
		for(i=0;i<m_num-1;i++){
			if(magazines.at(i).pname() == n && magazines.at(i).psi() == day) {
				m = magazines.at(i);
				magazines.at(i) = magazines.at(i+1);
				magazines.at(i+1) = m;
			}
		}
		magazines.pop_back();
		m_num--;
		return;
	}
	if(t == "E-book"){
		class e_book e;
		if(e_num == 1){
			e_books.pop_back();
			e_num--;
			return;
		}
		for(i=0;i<e_num-1;i++){
			if(e_books.at(i).pname() == n) {
				e = e_books.at(i);
				e_books.at(i) = e_books.at(i+1);
				e_books.at(i+1) = e;
			}
		}
		e_books.pop_back();
		e_num--;
		return;
	}
}
