#ifndef GAVBF_CONTROLLER_H
#define GAVBF_CONTROLLER_H
/**************************************************
 * Includes
 **************************************************/

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/
using namespace std;

class Gavbf_Model;
class Gavbf_View;

class Gavbf_Controller {
	Gavbf_Model* model;
	Gavbf_View* view;
public:
	Gavbf_Controller();
	void add_gavbf_model(Gavbf_Model* model);
	void add_gavbf_view(Gavbf_View* view);
	Gavbf_Model& get_gavbf_model();
	Gavbf_View& get_gavbf_view();

	void bf_output(unsigned char out_char);
	char bf_input();
	void run();
private:
};

#endif // GAVBF_CONTROLLER_H
