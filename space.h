#include "member.h"

class space {
	private:
		int space_num;
		int time;
		int memnum=0;
		vector<undergraduate> undergraduates;
		string st;
		string mem_name;
		string mem_type;
	public:
		void set(int s, int t, string stat);
		void set_space(string mn, string mt);
		void seat_set(undergraduate u);
		void seat_rset(undergraduate u);
		void eset(int et);
		int psn();
		int pt();
		int pmm();
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

int space :: pmm(){
	return memnum;
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
	memnum++;
	undergraduates.push_back(u);
}

void space :: seat_rset(undergraduate u){
	undergraduate un;
	int i,k;
	for(i=0;i<memnum;i++){
		if(undergraduates.at(i).pname() == u.pname()){
			k = i;
		}
	}
	un = undergraduates.at(i);
	undergraduates.at(i) = u;
	undergraduates.at(k) = un;
	memnum--;
	undergraduates.pop_back();
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
