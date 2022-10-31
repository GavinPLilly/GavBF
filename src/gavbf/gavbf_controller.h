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
	void add_model(BF_Model* model) override;
	void add_view(BF_View* view) override;
	BF_Model& get_model() override;

	void bf_output(unsigned char out_char) override;
	char bf_input() override;

	void run() override;
private:
};

#endif // GAVBF_CONTROLLER_H
