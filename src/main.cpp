/**************************************************
 * Includes
 **************************************************/
#include <iostream>

#include "gavbf_controller.h"
#include "gavbf_model.h"
#include "gavbf_view.h"

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
	Gavbf_Controller controller;
	Gavbf_Model model(&controller, string(argv[1]));
	Gavbf_View view(&controller);
	controller.add_model(&model);
	controller.add_view(&view);

	while(model.is_terminated() == false) {
		model.execute_next_char();
	}

	return 0;
}
