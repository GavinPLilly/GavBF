/**************************************************
 * Includes
 **************************************************/
#include <cassert>
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

Gavbf_Controller::Gavbf_Controller():
	model{nullptr},
	view{nullptr}
{}

/**************************************************
 * Public Methods
 **************************************************/
void Gavbf_Controller::add_model(BF_Model* model)
{
	this->model = model;
}

void Gavbf_Controller::add_view(BF_View* view)
{
	this->view = view;
}

BF_Model& Gavbf_Controller::get_model() {
	assert(model != nullptr);
	return *model;
}

void Gavbf_Controller::bf_output(unsigned char out_char)
{
	view->bf_output(out_char);
}

char Gavbf_Controller::bf_input()
{
	char c;
	cin >> c;
	return c;
}

void Gavbf_Controller::run()
{
}

/**************************************************
 * Private Methods
 **************************************************/
