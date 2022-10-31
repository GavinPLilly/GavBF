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
	virtual void draw_background() = 0;
	virtual void draw_input() = 0;
	virtual void draw_output() = 0;
	virtual void draw_pointers() = 0;
	virtual void draw_buttons() = 0;
	virtual void draw_tape() = 0;
	// Controlling the view
	virtual void set_tape_start(int start) = 0;
};

#endif // VIEW_H
