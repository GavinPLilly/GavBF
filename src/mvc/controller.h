#ifndef CONTROLLER_H
#define CONTROLLER_H
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

class BF_Model;
class BF_View;

class BF_Controller {
public:
	virtual void add_model(BF_Model* model) = 0;
	virtual void add_view(BF_View* view) = 0;
	virtual BF_Model& get_model() = 0;

	virtual void bf_output(unsigned char out_char) = 0;
	virtual char bf_input() = 0;

	virtual void run() = 0;
private:
};

#endif // CONTROLLER_H
