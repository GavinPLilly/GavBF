#ifndef VIEW_H
#define VIEW_H
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

class BF_View {
public:
	virtual void bf_output(unsigned char out_char) = 0;
	// Drawing methods
	virtual void draw() = 0;
	// Controlling the view
	virtual void set_tape_start(int start) = 0;
};

#endif // VIEW_H
