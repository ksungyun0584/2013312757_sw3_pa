#include "member.h"
#define MAX_borrow 1

class library {
	private:
		int u_num = 0;
		int g_num = 0;
		int f_num = 0;
		int b_num = 0;
		int m_num = 0;
		int e_num = 0;
		int date = 0;
		int date2 = 0;
		int hour = 0;
		int se=0;
		vector<undergraduate> undergraduates;
		vector<graduate> graduates;
		vector<faculty> facultys;
		vector<book> lbooks;
		vector<magazine> lmagazines;
		vector<e_book> le_books;

	public:
		void set(int n);
		void u_set(string t, string u);
		void b_set(string t, string n);
		int operation(string d, string rt, string rn, string op, string mt, string mn);
		void description(int code);
};

void library :: b_set(string t, string n){
	if(t == "Book"){
		class book b;
		b.set(n,"R",0,0);
		lbooks.push_back(b);
		b_num++;
	}
	if(t == "Magazine"){
		class magazine m;
		for(int i=0;i<12;i++){
			m.set(n,"R",0,0);
			m.ssize((i+1)*30);
			lmagazines.push_back(m);
			m_num++;
		}
	}
	if(t == "E-book"){
		class e_book e;
		string size;
		string name;
		name = n.substr(0,n.find('['));
		size = n.substr(n.find('[')+1,n.find(']'));
		e.set(name,"R",0,0);
		e.ssize(stoi(size));
		le_books.push_back(e);
		e_num++;
	}
}

void library :: u_set(string t, string u){
	if(t=="Undergraduate"){
		class undergraduate un;
		un.set(u,0);
		undergraduates.push_back(un);
		u_num++;
	}
	if(t=="Graduate"){
		class graduate un;
		un.set(u,0);
		graduates.push_back(un);
		g_num++;
	}
	if(t=="Faculty"){
		class faculty un;
		un.set(u,0);
		facultys.push_back(un);
		f_num++;
	}
}

int library :: operation(string d, string rt, string rn, string op, string mt, string mn){
	date = transdate(d);
	class book b;
	class magazine m;
	class e_book e;
	int i;
	int rnum=0;
	int mnum=0;
	int mrnum=0;
	int day=0;

	try{
		int i;
		if(transdate(d)<3631)
			throw 1;
		if(op != "B" & op != "R")
			throw 3;
		if(mt != "Undergraduate" & mt != "Graduate" & mt != "faculty")
			throw 4;
		for(i=0;i<mn.length();i++){
			if(mn.at(i)=='0' || mn.at(i)=='1' || mn.at(i)=='2' || mn.at(i)=='3' || mn.at(i)=='4' || mn.at(i)=='5' || mn.at(i)=='6' || mn.at(i)=='7' || mn.at(i)=='8' || mn.at(i)=='9')
				throw 5;		
		}
	}
	catch(int excp){
		if(excp == 1)
			return -1;
		if(excp == 3)
			return -3;
		if(excp == 4)
			return -4;
		if(excp == 5)
			return -5;
	}

	if (rt == "Book"){
		for(i=0;i<b_num;i++){
			rnum = b_num;
			if(rn == lbooks.at(i).pname()) {
				rnum = i;
				break;
			}
		}
	}
	else if (rt == "Magazine"){
		string month;
		int j=0;
		month = rn.substr(rn.find('[')+1,rn.find(']'));
		rn = rn.substr(0,rn.find('['));
		day = (month.at(0)*10+month.at(1))*360+(month.at(3)*10+month.at(4))*30;
		for(i=0;i<m_num;i++){
			if(lmagazines.at(i).psi()<day-330){
				lmagazines.at(i).ssize(day-lmagazines.at(i).psi()-300);
				lmagazines.at(i).set(rn,"R",0,0);
			}
		}
		for(i=0;i<m_num;i++){
			rnum = m_num;
			if(rn == lmagazines.at(i).pname() && day == lmagazines.at(i).psi()) {
				rnum = i;
				break;
			}
		}
	}
	else if (rt == "E-book"){
		for(i=0;i<e_num;i++){
			rnum = e_num;
			if(rn == le_books.at(i).pname()) {
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
			u_set(mt, mn);
		}
		if(rt == "Book")
			b = undergraduates.at(mnum).searchbook(rn);
		else if(rt == "Magazine")
			m = undergraduates.at(mnum).searchmagazine(rn);
		else if(rt == "E-book")
			e = undergraduates.at(mnum).searchebook(rn);
	}
	else if (mt == "Graduate"){
		for(i=0;i<g_num;i++){
			mnum = g_num;
			if(mn == graduates.at(i).pname()) {
				mnum = i;
				break;
			}
		}
		if(mnum == g_num){
			u_set(mt, mn);
		}
		if(rt == "Book")
			b = graduates.at(mnum).searchbook(rn);
		else if(rt == "Magazine")
			m = graduates.at(mnum).searchmagazine(rn);
		else if(rt == "E-book")
			e = graduates.at(mnum).searchebook(rn);
	}
	else if (mt == "Faculty"){
		for(i=0;i<f_num;i++){
			mnum = f_num;
			if(mn == facultys.at(i).pname()) {
				mnum = i;
				break;
			}
		}
		if(mnum == f_num){
			u_set(mt, mn);
		}
		if(rt == "Book")
			b = facultys.at(mnum).searchbook(rn);
		else if(rt == "Magazine")
			m = facultys.at(mnum).searchmagazine(rn);
		else if(rt == "E-book")
			e = facultys.at(mnum).searchebook(rn);
	}
	
	if(op == "B"){
		if(mt == "Undergraduate"){
			if(rt == "Book"){
				if(rnum == b_num){
					date = 0;
					return 1;
				}
				else if(undergraduates.at(mnum).pbnum(rt) > MAX_borrow - 1){
					date = 0;
					return 2;	
				}
				else if(b.pstate() == "B" && b.pname() == rn){
					date = b.psd();
					return 4;
				}
				else if(lbooks.at(rnum).pstate() == "B"){
					date = lbooks.at(rnum).ped();
					return 5;
				}
				else if(date-1 < undergraduates.at(mnum).ppenalty()){
					date = undergraduates.at(mnum).ppenalty();
					return 6;
				}
				else {
					lbooks.at(rnum).set(rn,"B",date,date+13);
					undergraduates.at(mnum).set(mn,0);
					undergraduates.at(mnum).b_set(rt,rn,date,date+13);
					date = 0;
					return 0;
				}
			}
			else if(rt == "Magazine"){
				if(rnum == m_num || date > day+330 || day > date){
					date = 0;
					return 1;
				}
				else if(undergraduates.at(mnum).pbnum(rt) > MAX_borrow - 1){
					date = 0;
					return 2;	
				}
				else if(m.pstate() == "B" && m.pname() == rn){
					date = m.psd();
					return 4;
				}
				else if(lmagazines.at(rnum).pstate() == "B"){
					date = lmagazines.at(rnum).ped();
					return 5;
				}
				else if(date-1 < undergraduates.at(mnum).ppenalty()){
					date = undergraduates.at(mnum).ppenalty();
					return 6;
				}
				else {
					lmagazines.at(rnum).set(rn,"B",date,date+13);
					undergraduates.at(mnum).set(mn,0);
					undergraduates.at(mnum).b_set(rt,rn,date,date+13);
					date = 0;
					return 0;
				}
			}
			else if(rt == "E-book"){
				if(rnum == e_num){
					date = 0;
					return 1;
				}
				else if(e.pstate() == "B" && e.pname() == rn){
					date = e.psd();
					return 4;
				}
				else if(date-1 < undergraduates.at(mnum).ppenalty()){
					date = undergraduates.at(mnum).ppenalty();
					return 6;
				}
				else if(undergraduates.at(mnum).pca()+le_books.at(rnum).psi()>100){
					date = 0;
					return 15;
				}
				else {
					undergraduates.at(mnum).sca(undergraduates.at(mnum).pca()+le_books.at(rnum).psi());
					le_books.at(rnum).set(rn,"B",date,date+13);
					undergraduates.at(mnum).set(mn,0);
					undergraduates.at(mnum).b_set(rt,rn,date,date+13);
					date = 0;
					return 0;
				}
			}
		}
		else if(mt == "Graduate"){
			if(rt == "Book"){
				if(rnum == b_num){
					date = 0;
					return 1;
				}
				else if(graduates.at(mnum).pbnum(rt) > MAX_borrow+4 - 1){
					date = 0;
					return 2;	
				}
				else if(b.pstate() == "B" && b.pname() == rn){
					date = b.psd();
					return 4;
				}
				else if(lbooks.at(rnum).pstate() == "B"){
					date = lbooks.at(rnum).ped();
					return 5;
				}
				else if(date-1 < graduates.at(mnum).ppenalty()){
					date = graduates.at(mnum).ppenalty();
					return 6;
				}
				else {
					lbooks.at(rnum).set(rn,"B",date,date+29);
					graduates.at(mnum).set(mn,0);
					graduates.at(mnum).b_set(rt,rn,date,date+29);
					date = 0;
					return 0;
				}
			}
			else if(rt == "Magazine"){
				if(rnum == m_num || date > day+330 || day > date){
					date = 0;
					return 1;
				}
				else if(graduates.at(mnum).pbnum(rt) > MAX_borrow+4 - 1){
					date = 0;
					return 2;	
				}
				else if(m.pstate() == "B" && m.pname() == rn){
					date = m.psd();
					return 4;
				}
				else if(lmagazines.at(rnum).pstate() == "B"){
					date = lmagazines.at(rnum).ped();
					return 5;
				}
				else if(date-1 < graduates.at(mnum).ppenalty()){
					date = graduates.at(mnum).ppenalty();
					return 6;
				}
				else {
					lmagazines.at(rnum).set(rn,"B",date,date+29);
					graduates.at(mnum).set(mn,0);
					graduates.at(mnum).b_set(rt,rn,date,date+29);
					date = 0;
					return 0;
				}
			}
			else if(rt == "E-book"){
				if(rnum == e_num){
					date = 0;
					return 1;
				}
				else if(e.pstate() == "B" && e.pname() == rn){
					date = e.psd();
					return 4;
				}
				else if(date-1 < graduates.at(mnum).ppenalty()){
					date = graduates.at(mnum).ppenalty();
					return 6;
				}
				else if(graduates.at(mnum).pca()+le_books.at(rnum).psi()>500){
					date = 0;
					return 15;
				}
				else {
					graduates.at(mnum).sca(graduates.at(mnum).pca()+le_books.at(rnum).psi());
					le_books.at(rnum).set(rn,"B",date,date+29);
					graduates.at(mnum).set(mn,0);
					graduates.at(mnum).b_set(rt,rn,date,date+29);
					date = 0;
					return 0;
				}
			}
		}
		else if(mt == "Faculty"){
			if(rt == "Book"){
				if(rnum == b_num){
					date = 0;
					return 1;
				}
				else if(facultys.at(mnum).pbnum(rt) > MAX_borrow+9 - 1){
					date = 0;
					return 2;	
				}
				else if(b.pstate() == "B" && b.pname() == rn){
					date = b.psd();
					return 4;
				}
				else if(lbooks.at(rnum).pstate() == "B"){
					date = lbooks.at(rnum).ped();
					return 5;
				}
				else if(date-1 < facultys.at(mnum).ppenalty()){
					date = facultys.at(mnum).ppenalty();
					return 6;
				}
				else {
					lbooks.at(rnum).set(rn,"B",date,date+29);
					facultys.at(mnum).set(mn,0);
					facultys.at(mnum).b_set(rt,rn,date,date+29);
					date = 0;
					return 0;
				}
			}
			else if(rt == "Magazine"){
				if(rnum == m_num || date > day+330 || day > date){
					date = 0;
					return 1;
				}
				else if(facultys.at(mnum).pbnum(rt) > MAX_borrow+9 - 1){
					date = 0;
					return 2;	
				}
				else if(m.pstate() == "B" && m.pname() == rn){
					date = m.psd();
					return 4;
				}
				else if(lmagazines.at(rnum).pstate() == "B"){
					date = lmagazines.at(rnum).ped();
					return 5;
				}
				else if(date-1 < facultys.at(mnum).ppenalty()){
					date = facultys.at(mnum).ppenalty();
					return 6;
				}
				else {
					lmagazines.at(rnum).set(rn,"B",date,date+29);
					facultys.at(mnum).set(mn,0);
					facultys.at(mnum).b_set(rt,rn,date,date+29);
					date = 0;
					return 0;
				}
			}
			else if(rt == "E-book"){
				if(rnum == e_num){
					date = 0;
					return 1;
				}
				else if(e.pstate() == "B" && e.pname() == rn){
					date = e.psd();
					return 4;
				}
				else if(date-1 < facultys.at(mnum).ppenalty()){
					date = facultys.at(mnum).ppenalty();
					return 6;
				}
				else if(facultys.at(mnum).pca()+le_books.at(rnum).psi()>1000){
					date = 0;
					return 15;
				}
				else {
					facultys.at(mnum).sca(facultys.at(mnum).pca()+le_books.at(rnum).psi());
					le_books.at(rnum).set(rn,"B",date,date+29);
					facultys.at(mnum).set(mn,0);
					facultys.at(mnum).b_set(rt,rn,date,date+29);
					date = 0;
					return 0;
				}
			}
		}
	}
	else if(op == "R"){
		if(mt == "Undergraduate"){
			if(rt == "Book"){
				if(b.pstate() == "n"){
					date = 0;
					return 3;
				}
		 		else if(date > lbooks.at(rnum).ped()){
					undergraduates.at(mnum).set(mn,date - lbooks.at(rnum).ped() + date);
					date = undergraduates.at(mnum).ppenalty();
					lbooks.at(rnum).set(rn,"R",0,0);
					undergraduates.at(mnum).returnbook(rt, rn);
					return 7;
				}
				else {
					lbooks.at(rnum).set(rn,"R",0,0);
					undergraduates.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
			else if(rt == "Magazine"){
				if(m.pstate() == "n"){
					date = 0;
					return 3;
				}
		 		else if(date > lmagazines.at(rnum).ped()){
					undergraduates.at(mnum).set(mn,date - lmagazines.at(rnum).ped() + date);
					date = undergraduates.at(mnum).ppenalty();
					lmagazines.at(rnum).set(rn,"R",0,0);
					undergraduates.at(mnum).returnbook(rt, rn);
					return 7;
				}
				else {
					lmagazines.at(rnum).set(rn,"R",0,0);
					undergraduates.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
			else if(rt == "E-book"){
				if(e.pstate() == "n"){
					date = 0;
					return 3;
				}
				else {
					le_books.at(rnum).set(rn,"R",0,0);
					undergraduates.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
		}
		else if(mt == "Graduate"){
			if(rt == "Book"){
				if(b.pstate() == "n"){
					date = 0;
					return 3;
				}
		 		else if(date > lbooks.at(rnum).ped()){
					graduates.at(mnum).set(mn,date - lbooks.at(rnum).ped() + date);
					date = graduates.at(mnum).ppenalty();
					lbooks.at(rnum).set(rn,"R",0,0);
					graduates.at(mnum).returnbook(rt, rn);
					return 7;
				}
				else {
					lbooks.at(rnum).set(rn,"R",0,0);
					graduates.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
			else if(rt == "Magazine"){
				if(m.pstate() == "n"){
					date = 0;
					return 3;
				}
		 		else if(date > lmagazines.at(rnum).ped()){
					graduates.at(mnum).set(mn,date - lmagazines.at(rnum).ped() + date);
					date = graduates.at(mnum).ppenalty();
					lmagazines.at(rnum).set(rn,"R",0,0);
					graduates.at(mnum).returnbook(rt, rn);
					return 7;
				}
				else {
					lmagazines.at(rnum).set(rn,"R",0,0);
					graduates.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
			else if(rt == "E-book"){
				if(e.pstate() == "n"){
					date = 0;
					return 3;
				}
				else {
					le_books.at(rnum).set(rn,"R",0,0);
					graduates.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
		}
		else if(mt == "Faculty"){
			if(rt == "Book"){
				if(b.pstate() == "n"){
					date = 0;
					return 3;
				}
		 		else if(date > lbooks.at(rnum).ped()){
					facultys.at(mnum).set(mn,date - lbooks.at(rnum).ped() + date);
					date = facultys.at(mnum).ppenalty();
					lbooks.at(rnum).set(rn,"R",0,0);
					facultys.at(mnum).returnbook(rt, rn);
					return 7;
				}
				else {
					lbooks.at(rnum).set(rn,"R",0,0);
					facultys.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
			else if(rt == "Magazine"){
				if(m.pstate() == "n"){
					date = 0;
					return 3;
				}
		 		else if(date > lmagazines.at(rnum).ped()){
					facultys.at(mnum).set(mn,date - lmagazines.at(rnum).ped() + date);
					date = facultys.at(mnum).ppenalty();
					lmagazines.at(rnum).set(rn,"R",0,0);
					facultys.at(mnum).returnbook(rt, rn);
					return 7;
				}
				else {
					lmagazines.at(rnum).set(rn,"R",0,0);
					facultys.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
			else if(rt == "E-book"){
				if(e.pstate() == "n"){
					date = 0;
					return 3;
				}
				else {
					le_books.at(rnum).set(rn,"R",0,0);
					facultys.at(mnum).returnbook(rt, rn);
					date = 0;
					return 0;
				}
			}
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

		case -1: cout << "Date out of range" << endl; break;
		case -2: cout << "Non-exist space type" << endl; break;
		case -3: cout << "Non-exist operation" << endl; break;
		case -4: cout << "Non-exist member type" << endl; break;
		case -5: cout << "Member name with numbers" << endl; break;
		case -6: cout << "Negative time" << endl; break;
		case 15: cout << "Exceed your storage capacity." << endl; break;
	}
}
