#ifndef GAVBF_VIEW_H
#define GAVBF_VIEW_H
/**************************************************
 * Includes
 **************************************************/
#include <vector>
#include <fstream>
#include <ncurses.h>

#include "view.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/
using namespace std;

struct Borders {
	int rows;
	int cols;
	int y;
	int x;
};

class Gavbf_View: public BF_View {
	BF_Controller* controller;
	string infile_name = {};
	ifstream infile = {};
	string infile_string = {};
	string output_string = {};
	vector<Borders> borders = {};
	// Window variables
	int total_y;
	int total_x;
	WINDOW* input_program_win;
	WINDOW* program_output_win;
	WINDOW* pointers_win;
	WINDOW* buttons_win;
	WINDOW* tape_win;
public:
	Gavbf_View(BF_Controller* controller);
	Gavbf_View(BF_Controller* controller, string filename);
	~Gavbf_View();
	void bf_output(unsigned char out_char) override;
	// Drawing methods
	void draw() override;
	void draw_background() override;
	void draw_input() override;
	void draw_output() override;
	void draw_pointers() override;
	void draw_buttons() override;
	void draw_tape() override;
	// Controlling the view
	void set_tape_start(int start) override;
private:
	// void draw_borders();
	void draw_single_border(int rows, int cols, int y, int x);
};

#endif // GAVBF_VIEW_H
