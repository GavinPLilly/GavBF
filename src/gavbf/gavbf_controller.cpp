/**************************************************
 * Includes
 **************************************************/
#include <iostream>

#include "gavbf_controller.h"
#include "view.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * BF_Controller
 **************************************************/
using namespace std;

Gavbf_Controller::Gavbf_Controller() {}

/**************************************************
 * Public Methods
 **************************************************/
void Gavbf_Controller::add_model(BF_Model* model) {
	this->model = model;
}

void Gavbf_Controller::add_view(BF_View* view) {
	this->view = view;
}

void Gavbf_Controller::output(char out_char) {
	view->output(out_char);
}

char Gavbf_Controller::input() {
	char c;
	cin >> c;
	return c;
}

/**************************************************
 * Private Methods
 **************************************************/
