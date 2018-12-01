#include "library.h"

int main(int argc, char* argv[]){	
	int i,code;
	int opcnt = 0;
	ifstream fin;
	fin.open("resource.dat");

	string line;
	string resource_type;
	string resource_name;
	string date;
	string OP;
	string member_type;
	string member_name;

	class library lib;

	getline(fin,line);
	while(getline(fin,line)){
		resource_type = line.substr(0,line.find('	'));
		resource_name = line.substr(line.find('	')+1,line.length());
		lib.b_set(resource_type, resource_name);
	}
	fin.close();

	fin.open("input.dat");
	getline(fin,line);
	cout << "Op_#	Return_code	Description" << endl;
	while(getline(fin,line)){
		opcnt++;
		cout << opcnt << '	';
		date = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		resource_type = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		resource_name = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		OP = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		member_type = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());
		member_name = line.substr(0,line.find('	'));
		line = line.substr(line.find('	')+1,line.length());

		code = lib.operation(date,resource_type,resource_name,OP,member_type,member_name);
		lib.description(code);
	}
	fin.close();
	return 0;
}
