#include "library.h"

int main(int argc, char* argv[]){	
	int i,code1,code2;
	int opcnt = 0;
	int cnt1 = 0;
	int cnt2 = 0;
	ifstream fin1;
	ifstream fin2;
	fin1.open("resource.dat");

	string line1;
	string line2;
	string tmp1;
	string tmp2;

	string resource_type;
	string resource_name;
	string date1;
	string date2;
	string OP;
	string member_type;
	string member_name;

	string space_type;
	string space_num;
	string member_num;
	string time;

	class library lib;
	lib.set_space();

	getline(fin1,line1);
	while(getline(fin1,line1)){
		resource_type = line1.substr(0,line1.find('	'));
		resource_name = line1.substr(line1.find('	')+1,line1.length());
		if(resource_type == "Book"){
			lib.b_set(resource_name);
		}
	}
	fin1.close();

	fin1.open("input.dat");
	fin2.open("space.dat");

	getline(fin1,line1);
	getline(fin2,line2);
	getline(fin1,line1);
	getline(fin2,line2);
	cout << "Op_#	Return_code	Description" << endl;
	while(1){
		opcnt++;
		cout << opcnt << '	';
		date1 = line1.substr(0,line1.find('	'));
		date2 = line2.substr(0,line2.find('	'));

		if((transdate(date1) < transdate(date2) || cnt2 == 1) && cnt1 == 0){
			tmp1 = line1;
			line1 = line1.substr(line1.find('	')+1,line1.length());
			resource_type = line1.substr(0,line1.find('	'));
			line1 = line1.substr(line1.find('	')+1,line1.length());
			resource_name = line1.substr(0,line1.find('	'));
			line1 = line1.substr(line1.find('	')+1,line1.length());
			OP = line1.substr(0,line1.find('	'));
			line1 = line1.substr(line1.find('	')+1,line1.length());
			member_type = line1.substr(0,line1.find('	'));
			line1 = line1.substr(line1.find('	')+1,line1.length());
			member_name = line1.substr(0,line1.find('	'));
			line1 = line1.substr(line1.find('	')+1,line1.length());

			code1 = lib.operation(date1,resource_type,resource_name,OP,member_type,member_name);
			lib.description(code1);
			getline(fin1,line1);
			if(line1=="") {
				cnt1++;
				line1 = tmp1;
			}
		}
		else if((transdate(date1) > transdate(date2) || cnt1 == 1) && cnt1 == 0){
			tmp2 = line2;
			line2 = line2.substr(line2.find('	')+1,line2.length());
			space_type = line2.substr(0,line2.find('	'));
			line2 = line2.substr(line2.find('	')+1,line2.length());
			space_num = line2.substr(0,line2.find('	'));
			line2 = line2.substr(line2.find('	')+1,line2.length());
			OP = line2.substr(0,line2.find('	'));
			line2 = line2.substr(line2.find('	')+1,line2.length());
			member_type = line2.substr(0,line2.find('	'));
			line2 = line2.substr(line2.find('	')+1,line2.length());
			member_name = line2.substr(0,line2.find('	'));
			line2 = line2.substr(line2.find('	')+1,line2.length());
			if(OP == "B"){
				member_num = line2.substr(0,line2.find('	'));
				line2 = line2.substr(line2.find('	')+1,line2.length());
				time = line2.substr(0,line2.find('	'));
				line2 = line2.substr(line2.find('	')+1,line2.length());

				code2 = lib.soperation(date2,space_type,space_num,OP,member_type,member_name,member_num,time);
			}
			else {
				code2 = lib.soperation(date2,space_type,space_num,OP,member_type,member_name,"","");
			}
			lib.description(code2);
			getline(fin2,line2);
			if(line2=="") {
				cnt2++;
				line2 = tmp2;
			}
		}
		if(cnt1 + cnt2 == 2) break;


	}
	fin1.close();
	fin2.close();
	return 0;
}
