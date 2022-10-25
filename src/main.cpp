/**************************************************
 * Includes
 **************************************************/
#include <iostream>

#include "gavbf.h"
#include "gavbf_text_view.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Code
 **************************************************/
using namespace std;

int main(int argc, char** argv) {
	if(argc < 2) {
		cout << "Missing filename" << endl;
		cout << "Syntax: gavbf <filename>" << endl;
		exit(1);
	}
	if(argc > 2) {
		cout << "Too many arguments" << endl;
		cout << "Syntax: gavbf <filename>" << endl;
		exit(1);
	}
	Text_BF_Program_View view;
	BF_Program my_program(string(argv[1]), &view);
	while(my_program.is_terminated() == false) {
		my_program.execute_next_char();
	}
	return 0;
}
