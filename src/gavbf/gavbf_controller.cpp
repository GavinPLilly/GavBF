/**************************************************
 * Includes
 **************************************************/
#include <cassert>
#include <iostream>
#include <ncurses.h>
#include <glog/logging.h>

#include "gavbf_controller.h"
#include "gavbf_view.h"
#include "gavbf_model.h"

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
void Gavbf_Controller::add_gavbf_model(Gavbf_Model* model)
{
	this->model = model;
}

void Gavbf_Controller::add_gavbf_view(Gavbf_View* view)
{
	this->view = view;
}

Gavbf_Model& Gavbf_Controller::get_gavbf_model()
{
	assert(model != nullptr);
	return *model;
}

Gavbf_View& Gavbf_Controller::get_gavbf_view()
{
	assert(model != nullptr);
	return *view;
}

void Gavbf_Controller::bf_output(unsigned char out_char)
{
	view->bf_output(out_char);
}

char Gavbf_Controller::bf_input()
{
	return view->getchar();
}

void Gavbf_Controller::run()
{
	view->draw();
	// while not user does call exit:
	// 	get input
	// 	respond to input by:
	// 		calling model
	// 		calling vstderrthresholdiew
	// 		calling both
	int c;
	while(true) {
		c = view->getchar();
		// LOG(INFO) << "Recieved input: " << c;
		// google::FlushLogFiles(google::INFO);
		switch(c) {
			case 's':
				model->execute_next_char();
				view->draw();
				break;
			case 'n':
				model->execute_next_instruction();
				view->draw();
				break;
			case 'c':
				model->execute_to_breakpoint();
				view->draw();
				break;
			case 'q':
				goto exit_loop;
				break;
		}
	}
exit_loop:
	;
}

/**************************************************
 * Private Methods
 **************************************************/
