#include "member.h"
#define MAX_borrow 1

class library {
	private:
		int u_num = 0;
		int b_num = 0;
		int date = 0;
		vector<undergraduate> undergraduates;
		vector<graduate> graduates;
		vector<faculty> facultys;
		vector<book> lbooks;
		vector<magazine> lmagazines;
		vector<e_book> le_books;

	public:
		void set(int n);
		void u_set(string u);
		void b_set(string n);
		int operation(string d, string rt, string rn, string st, string mt, string mn);
		void description(int code);
};

void library :: b_set(string n){
	class book b;
	b.set(n,"R",0,0);
	lbooks.push_back(b);
	b_num++;
}

void library :: u_set(string u){
	class undergraduate un;
	un.set(u,0);
	undergraduates.push_back(un);
	u_num++;
}

int library :: operation(string d, string rt, string rn, string st, string mt, string mn){
	date = transdate(d);
	class book b;
	int i;
	int rnum=0;
	int mnum=0;
	int mrnum=0;
	if (rt == "Book"){
		for(i=0;i<b_num;i++){
			rnum = b_num;
			if(rn == lbooks.at(i).pname()) {
				rnum = i;
				break;
			}
		}
	}	
	if (mt == "Undergraduate"){
		for(i=0;i<u_num;i++){
			mnum = u_num;
			if(mn == undergraduates.at(i).pname()) {
				mnum = i;
				break;
			}
		}
		if(mnum == u_num){
			u_set(mn);
		}
		b = undergraduates.at(mnum).searchbook(rn);
	}
	
	if(st == "B"){
		if(rnum == b_num){
			date = 0;
			return 1;
		}
		if(undergraduates.at(mnum).pbnum() > MAX_borrow - 1){
			date = 0;
			return 2;	
		}
		if(b.pstate() == "B" && b.pname() == rn){
			date = b.psd();
			return 4;
		}
		if(lbooks.at(rnum).pstate() == "B"){
			date = lbooks.at(rnum).ped();
			return 5;
		}
		if(date-1 < undergraduates.at(mnum).ppenalty()){
			date = undergraduates.at(mnum).ppenalty();
			return 6;
		}
		else {
			lbooks.at(rnum).set(rn,"B",date,date+13);
			undergraduates.at(mnum).set(mn,0);
			undergraduates.at(mnum).b_set(rn,date,date+13);
			date = 0;
			return 0;
		}
	}
	if(st == "R"){
		if(b.pstate() == "n"){
			date = 0;
			return 3;
		}
		if(date > lbooks.at(rnum).ped()){
			undergraduates.at(mnum).set(mn,date - lbooks.at(rnum).ped() + date);
			date = undergraduates.at(mnum).ppenalty();
			lbooks.at(rnum).set(rn,"R",0,0);
			undergraduates.at(mnum).returnbook(rn);
			return 7;
		}
		else {
			lbooks.at(rnum).set(rn,"R",0,0);
			undergraduates.at(mnum).returnbook(rn);
			date = 0;
			return 0;
		}
	}
}

void library :: description(int code){
	cout << code << '	';
	switch (code){
		case 0: cout << "Success." << endl; break;
		case 1: cout << "Non exist resource." << endl; break;
		case 2: cout << "Exceeds your possible number of borrow. Possible # of borrows: " << MAX_borrow << endl; break;
		case 3: cout <<  "You did not borrow this book." << endl; break;
		case 4: cout << "You already borrowed this book at "; pday(date); break;
		case 5: cout << "Other member already borrowed this book. This book will be returned at "; pday(date); break;
		case 6: cout << "Restricted member until "; pday(date); break;
		case 7: cout << "Delayed return. You'll be restricted until "; pday(date); break;
	}
}
