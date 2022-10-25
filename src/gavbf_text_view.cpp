/**************************************************
 * Includes
 **************************************************/
#include <iostream>

#include "gavbf_text_view.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Code
 **************************************************/
using namespace std;

void Text_BF_Program_View::output(char out_char) {
	output_record += out_char;
	cout << out_char;
}

char Text_BF_Program_View::input() {
	char c;
	cin >> c;
	return c;
}
