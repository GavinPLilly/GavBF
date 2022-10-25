#ifndef GAVBF_VIEW_H
#define GAVBF_VIEW_H
/**************************************************
 * Includes
 **************************************************/
#include <string>

#include "gavbf.h"

class Text_BF_Program_View: public BF_Program_View {
public:
	void output(char out_char);
	char input();
private:
	string output_record;
};

#endif // GAVBF_VIEW_H
