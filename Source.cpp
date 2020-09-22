#include <mysqlx/xapi.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include"db.h"



using namespace std;

int main() {
	db data;
	int temp_c;
	int re_menu = 1;
	while (re_menu) {
		system("CLS");
		cout << "WELCOM!" << endl << "*to Ido Kilker and Linoy Noah's music studio*" << endl;
		cout << endl << "MENU:" << endl;
		cout << "1)How many albums were recorded between Y1 and Y2?" << endl;
		cout << "2)How many different songs did musician X record between Y1 and Y2?" << endl;
		cout << "3)How many different albums did Musician X attend between Y1 and Y2?" << endl;
		cout << "4)What is the most widely used musical instrument over the years?" << endl;
		cout << "5)What are the instruments playing in album A?" << endl;
		cout << "6)Who is the busiest producer between Y1 and Y2?" << endl;
		cout << "7)Who is the most popular manufacturer?" << endl;
		cout << "8)How many musicians have recorded over the years?" << endl;
		cout << "9)Who is the musician who collaborated with the greatest number of other musicians ? " << endl;
		cout << "10)What is the most popular song genre (over the years)?" << endl;
		cout << "11)Who is the recording technician who recorded the largest number of songs between Y1 and Y2 ? " << endl;
		cout << "12)What is the first album recorded in the studio?" << endl;
		cout << "13)List of songs included in 2 or more albums." << endl;
		cout << "14)The list of technicians who participated in recording an entire album." << endl;
		cout << "15)Who is the most versatile musician( = The musician who recorded songs " << endl << "   In the widest variety of genres)? " << endl;
		cout << "0)Exit." << endl;

		cin >> temp_c;
		string y1;
		string y2;
		string x;
		string temp;
		switch (temp_c) {
		case 1:
		{
			system("CLS");
			cout << "1)How many albums were recorded between Y1 and Y2?" << endl;
			cout << endl;
			cout << "Y1 date:";
			y1 = get_date();
			cout << endl;
			cout << "Y2 date:";
			y2 = get_date();
			cout << endl;

			data.op1(y1, y2);
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 2:
		{
			system("CLS");
			cout << "2)How many different songs did musician X record between Y1 and Y2?" << endl;
			cout << endl;
			cout << "Y1 date:";
			y1 = get_date();
			cout << endl;
			cout << "Y2 date:";
			y2 = get_date();
			cout << endl;
			cout << "musician name: ";
			cin >> x;
			data.op2(y1, y2, x);
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 3:
		{
			system("CLS");
			cout << "3)How many different albums did Musician X attend between Y1 and Y2?" << endl;
			cout << endl;
			cout << "musician name: ";
			cin >> x;
			cout << endl;
			cout << "Y1 date:";
			y1 = get_date();
			cout << endl;
			cout << "Y2 date:";
			y2 = get_date();
			cout << endl;
			data.op3(y1, y2, x);
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 4:
		{
			system("CLS");
			cout << "4)What is the most widely used musical instrument over the years?" << endl;
			data.op4();

			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 5: {
			system("CLS");
			cout << "5)What are the instruments playing in album A?" << endl;
			cout << endl;
			cout << "album name: ";
			cin >> x;
			cout << endl;
			data.op5(x);

			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break; }
		case 6: {
			system("CLS");
			cout << "6)Who is the busiest producer between Y1 and Y2?" << endl;
			cout << "Y1 date:";
			y1 = get_date();
			cout << endl;
			cout << "Y2 date:";
			y2 = get_date();
			cout << endl;
			data.op6(y1, y2);
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 7: {
			system("CLS");
			cout << "7)Who is the most popular manufacturer?" << endl;
			data.op7();
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 8: {
			system("CLS");
			cout << "8)How many musicians have recorded over the years?" << endl;
			data.op8();

			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 9: {
			system("CLS");
			cout << "9)Who is the musician who collaborated with the greatest number of other musicians ? " << endl;
			data.op9();
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break; }
		case 10: {
			system("CLS");
			cout << "10)What is the most popular song genre (over the years)?" << endl;
			data.op10();
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 11: {
			system("CLS");
			cout << "11)Who is the recording technician who recorded the largest number of songs between Y1 and Y2 ? " << endl;
			cout << "Y1 date:";
			y1 = get_date();
			cout << endl;
			cout << "Y2 date:";
			y2 = get_date();
			cout << endl;
			data.op11(y1, y2);
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break; }
		case 12: {
			system("CLS");
			cout << "12)What is the first album recorded in the studio?" << endl;
			data.op12();
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 13: {
			system("CLS");
			cout << "13)List of songs included in 2 or more albums." << endl;
			data.op13();
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break; }
		case 14: {
			system("CLS");
			cout << "14)The list of technicians who participated in recording an entire album." << endl;
			data.op14();
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		case 15: {
			system("CLS");
			cout << "15)Who is the most versatile musician( = The musician who recorded songs " << endl << "   In the widest variety of genres)? " << endl;
			data.op15();
			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break; }
		default: {
			system("CLS");
			cout << "invalid input";

			cout << endl << endl << "to return to menu press 1." << endl << "or 0 to Exit." << endl;
			cin >> temp; if (temp == "0") { re_menu = 0; }
			break;
		}
		}
	}
	return 0;

}