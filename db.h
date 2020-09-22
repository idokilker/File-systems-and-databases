#pragma once
#include <mysqlx/xapi.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class db
{
public:
	mysqlx_session_t* sess;
	void create_tables();
	void init();
	void op1(string y1, string y2);
	void op2(string y1, string y2, string x);
	void op3(string y1, string y2, string x);
	void op4();
	void op5(string a);
	void op6(string y1, string y2);
	void op7();
	void op8();
	void op9();
	void op10();
	void op11(string y1, string y2);
	void op12();
	void op13();
	void op14();
	void op15();
	db();
	~db();
private:

};

string get_date();
