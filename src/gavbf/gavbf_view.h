#ifndef GAVBF_VIEW_H
#define GAVBF_VIEW_H
/**************************************************
 * Includes
 **************************************************/
#include <vector>
#include <fstream>
#include <string>
#include <ncurses.h>

#include "gavbf_controller.h"

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

class Gavbf_View {
	Gavbf_Controller& controller;
	Gavbf_Model& model;
	string program_name = {};
	ifstream program_file = {};
	string program_string = {};
	string input_string = {};
	string output_string = {};
	vector<Borders> borders = {};
	int tape_start = 0;
	// Window variables
	int total_y;
	int total_x;
	WINDOW* program_win = {};
	WINDOW* input_win = {};
	WINDOW* output_win = {};
	WINDOW* pointers_win = {};
	WINDOW* buttons_win = {};
	WINDOW* tape_win = {};
public:
	Gavbf_View(Gavbf_Controller& controller, Gavbf_Model& model);
	Gavbf_View(Gavbf_Controller& controller, Gavbf_Model& model, string filename);
	~Gavbf_View();
	void bf_output(unsigned char out_char);
	// Drawing methods
	void draw();
	void draw_background();
	void draw_program();
	void draw_input();
	void draw_output();
	void draw_pointers();
	void draw_buttons();
	void draw_tape();
	// Controlling the view
	void set_tape_start(int start);
	void scroll_tape_start(int offset);
	// Input
	int getchar();
private:
	// void draw_borders();
	void draw_tape(int print_index, int data_index);
	void draw_single_border(int rows, int cols, int y, int x);
};

#endif // GAVBF_VIEW_H
