#ifndef GAVBF_CONTROLLER_H
#define GAVBF_CONTROLLER_H
/**************************************************
 * Includes
 **************************************************/
#include "controller.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/
using namespace std;

class BF_Model;
class BF_View;

class Gavbf_Controller: public BF_Controller {
	BF_Model* model;
	BF_View* view;
public:
	Gavbf_Controller();
	void add_model(BF_Model* model);
	void add_view(BF_View* view);
	void output(char out_char);
	char input();
private:
};

#endif // GAVBF_CONTROLLER_H
