#include "member.h"

class space {
	private:
		int space_num;
		int time;
		int unum=0;
		int gnum=0;
		int fnum=0;
		vector<undergraduate> undergraduates;
		vector<graduate> graduates;
		vector<faculty> facultys;
		string st;
		string mem_name;
		string mem_type;
	public:
		void set(int s, int t, string stat);
		void set_space(string mn, string mt);
		void seat_set(undergraduate u);
		void seat_rset(undergraduate u);
		void seat_set(graduate u);
		void seat_rset(graduate u);
		void seat_set(faculty u);
		void seat_rset(faculty u);
		void eset(int et);
		int psn();
		int pt();
		int pmm(string mt);
		string ps();
		string pmn();
		string pmt();
		int searchhour(string st);
};

class studyroom:public space{};
class seat:public space{};

int space :: psn(){
	return space_num;
}

int space :: pt(){
	return time;
}

int space :: pmm(string mt){
	if(mt == "Undergraduate"){
		return unum;
	}
	if(mt == "Graduate"){
		return gnum;
	}
	if(mt == "Faculty"){
		return fnum;
	}
}

string space :: ps(){
	return st;
}

string space :: pmn(){
	return mem_name;
}

string space :: pmt(){
	return mem_type;
}

void space :: seat_set(undergraduate u){
	unum++;
	undergraduates.push_back(u);
}

void space :: seat_rset(undergraduate u){
	undergraduate un;
	int i,k;
	for(i=0;i<unum;i++){
		if(undergraduates.at(i).pname() == u.pname()){
			k = i;
		}
	}
	un = undergraduates.at(i);
	undergraduates.at(i) = u;
	undergraduates.at(k) = un;
	unum--;
	undergraduates.pop_back();
}

void space :: seat_set(graduate u){
	gnum++;
	graduates.push_back(u);
}

void space :: seat_rset(graduate u){
	graduate un;
	int i,k;
	for(i=0;i<gnum;i++){
		if(graduates.at(i).pname() == u.pname()){
			k = i;
		}
	}
	un = graduates.at(i);
	graduates.at(i) = u;
	graduates.at(k) = un;
	gnum--;
	graduates.pop_back();
}

void space :: seat_set(faculty u){
	fnum++;
	facultys.push_back(u);
}

void space :: seat_rset(faculty u){
	faculty un;
	int i,k;
	for(i=0;i<fnum;i++){
		if(facultys.at(i).pname() == u.pname()){
			k = i;
		}
	}
	un = facultys.at(i);
	facultys.at(i) = u;
	facultys.at(k) = un;
	fnum--;
	facultys.pop_back();
}

void space :: set(int s, int t, string stat){
	space_num = s;
	time = t;
	st = stat;
}

void space :: set_space(string mn, string mt){
	mem_name = mn;
	mem_type = mt;
}

int space :: searchhour(string st){
	int h=24;
	for(int i=0;i<50;i++){
		if(undergraduates.at(i).pt("Seat") < h)
			h = undergraduates.at(i).pt("Seat");
	}
	return h;
}
