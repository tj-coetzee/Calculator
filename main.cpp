#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    

    string n1 = "", n2 = "", sign = "", answer = "";

    while (n1 != "q" || n1 != "quit") {
    	cout << ">> ";
    	cin >> n1;
    	if (n1 == "q" || n1 == "quit") break;
    	cin >> sign >> n2;
    	if (sign == "+") {
    		answer = add(n1, n2);
    	} else if (sign == "*") {
    		answer = multiply(n1, n2);
    	}

    	cout << "\nans =\n\n    " << answer << endl;
    	cout << endl;
    }

    cout << "\nfarvel!" << endl;


}

