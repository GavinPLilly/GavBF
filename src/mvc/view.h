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
	virtual void output(char out_char) = 0;
};

#endif // VIEW_H