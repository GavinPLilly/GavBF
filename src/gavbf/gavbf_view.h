#ifndef GAVBF_VIEW_H
#define GAVBF_VIEW_H
/**************************************************
 * Includes
 **************************************************/
#include "view.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/

class Gavbf_View: public BF_View {
BF_Controller* controller;
public:
	Gavbf_View(BF_Controller* controller);
	void output(char out_char);
private:
};

#endif // GAVBF_VIEW_H
