#include "space.h"
#define MAX_borrow 1

class library {
	private:
		int u_num = 0;
		int b_num = 0;
		int date = 0;
		int date2 = 0;
		int hour = 0;
		int se=0;
		vector<seat> seats;
		vector<studyroom> studyrooms;
		vector<undergraduate> undergraduates;
		vector<graduate> graduates;
		vector<faculty> facultys;
		vector<book> lbooks;
		vector<magazine> lmagazines;
		vector<e_book> le_books;

	public:
		void set_space();
		void set(int n);
		void u_set(string u);
		void b_set(string n);
		int operation(string d, string rt, string rn, string st, string mt, string mn);
		void description(int code);
		int soperation(string d, string st, string sn, string op, string mt, string mn, string mnum, string t);
};

void library :: set_space(){
	int i;
	class studyroom sr;
	class seat st;

	for(i=0;i<10;i++){
		sr.set(i,0,"R");
		studyrooms.push_back(sr);
	}
	for(i=0;i<3;i++){
		st.set(i,0,"R");
		seats.push_back(st);
	}
}

int library :: soperation(string d, string st, string sn, string op, string mt, string mn, string mnum, string t){
	hour = transhour(d);
	int spacenum = stoi(sn) - 1;
	int memnum=0;
	int i;
	int m_num=0;
	int tt = 0;

	if(t != ""){
		tt = stoi(t);
	}
	if(mnum != ""){
		memnum = stoi(mnum);
	}
	if (mt == "Undergraduate"){
		for(i=0;i<u_num;i++){
			m_num = u_num;
			if(mn == undergraduates.at(i).pname()) {
				m_num = i;
				break;
			}
		}
		if(m_num == u_num){
			u_set(mn);
		}
	}

	if(transdate(d) > date2){
		while(studyrooms.size()!=0){
			studyrooms.pop_back();
		}
		while(seats.size()!=0){
			seats.pop_back();
		}
		for(i=0;i<u_num;i++){
			undergraduates.at(i).sy_set(50,24);
			undergraduates.at(i).st_set(50,24);
		}
		set_space();
		date2 = transdate(d);
	}

	for(i=0;i<u_num;i++){
		if(hour%24>undergraduates.at(i).pet()){
			int l = undergraduates.at(i).psn();
			if(l!=50){
				seats.at(l).seat_rset(undergraduates.at(i));
				undergraduates.at(i).st_set(50,24);
			}
		}
		if(hour%24>undergraduates.at(i).pt("Seat")){
			int l = undergraduates.at(i).psn();
			if(l!=50){
				seats.at(l).seat_rset(undergraduates.at(i));
				undergraduates.at(i).st_set(50,24);
			}
		}
		if(hour%24>undergraduates.at(i).pt("StudyRoom")){
			undergraduates.at(i).sy_set(50,24);
		}
	}

	for(i=0;i<10;i++){
		if(hour%24>studyrooms.at(i).pt()){
			studyrooms.at(i).set(spacenum,0,"R");
			studyrooms.at(i).set_space("","");
		}
	}
	if(op == "B"){
		if(st == "StudyRoom"){
			if(spacenum > 9)
				return 8;
			else if(hour%24 < 9 || hour%24 > 18){
				se = 1;
				return 9;
			}
			else if(undergraduates.at(m_num).pst() != 50)
				return 11;
			else if(memnum > 6)
				return 12;
			else if(stoi(t) > 3)
				return 13;
			else if(studyrooms.at(spacenum).ps() == "B"){
				hour = studyrooms.at(spacenum).pt();
				return 14;
			}
			else {
				if(hour%24+tt > 18){
					tt = hour%24+tt-18;
				}
				undergraduates.at(m_num).sy_set(spacenum,hour+tt);
				studyrooms.at(spacenum).set(spacenum,hour+tt,"B");
				studyrooms.at(spacenum).set_space(mn,mt);
				return 0;
			}
		}
		if(st == "Seat"){
			if(spacenum > 2){
				return 8;
			}
			else if((hour%24 < 9 || hour%24 > 21) && spacenum == 1){
				se = 2;
				return 9;
			}
			else if((hour%24 < 9 || hour%24 > 18) && spacenum == 2){
				se = 1;
				return 9;
			}
			else if(undergraduates.at(m_num).psn() != 50)
				return 11;
			else if(memnum > 1)
				return 12;
			else if(stoi(t) > 3)
				return 13;
			else if(seats.at(spacenum).pmm() > 50){
				hour = seats.at(spacenum).searchhour("Seat");
				return 14;
			}
			else {
				if(hour%24+tt > 18 && spacenum == 2){
					tt = hour%24+tt-18;
				}
				if(hour%24+tt > 21 && spacenum == 1){
					tt = hour%24+tt-21;
				}
				undergraduates.at(m_num).st_set(spacenum,hour+tt);
				seats.at(spacenum).seat_set(undergraduates.at(m_num));
				return 0;
			}
		}
	}
	if(op == "R"){
		if(st == "StudyRoom"){
			if(undergraduates.at(m_num).pst() == 0)
				return 10;
			else if(studyrooms.at(spacenum).pmn() != mn)
				return 10;
			else {
				undergraduates.at(m_num).sy_set(50,24);
				studyrooms.at(spacenum).set(spacenum,0,"R");
				studyrooms.at(spacenum).set_space("","");
				return 0;
			}
		}
		if(st == "Seat"){
			if(undergraduates.at(m_num).psn() == 0)
				return 10;
			else {
				undergraduates.at(m_num).st_set(50,24);
				seats.at(spacenum).seat_rset(undergraduates.at(m_num));
				return 0;
			}
		}
	}
	if(op == "E"){
		if(spacenum > 2)
			return 8;
		else if(undergraduates.at(m_num).psn() == 0)
			return 10;
		else {
			undergraduates.at(m_num).eset(hour+1);
			return 0;
		}
	}
	if(op == "C"){
		if(spacenum > 2)
			return 8;
		else if(undergraduates.at(m_num).psn() == 0)
			return 10;
		else {
			undergraduates.at(m_num).eset(24);
			return 0;

		}
	}
}

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
		case 8: cout << "Invalid space id" << endl; break;
		case 9: {
			cout << "This space is not available now. Available from "; 
			if(se==1){
				cout << "09 to 18." << endl;
			}
			if(se==2){
				cout << "09 to 21." << endl;
			}
			se = 0;
			break;
		}
		case 10: cout << "You did not borrow this place." << endl; break;
		case 11: cout << "You already borrowed this kind of space." << endl; break;
		case 12: cout << "Exceed available number." << endl; break;
		case 13: cout << "Exceed available time." << endl; break;
		case 14: cout << "There is no remain space. This space is available after "; phour(hour%24); break;
	}
}
