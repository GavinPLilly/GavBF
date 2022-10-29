/**************************************************
 * Includes
 **************************************************/
#include <iostream>

#include "gavbf_view.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/

Gavbf_View::Gavbf_View(BF_Controller* controller) {
	this->controller = controller;
}

void Gavbf_View::output(char out_char) {
	cout << out_char;
}
