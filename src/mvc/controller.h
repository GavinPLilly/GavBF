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
	virtual void output(char out_char) = 0;
	virtual char input() = 0;
};

#endif // CONTROLLER_H
