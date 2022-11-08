/**************************************************
 * Includes
 **************************************************/
#include <iostream>
#include <string>
#include <fmt/core.h>
#include <glog/logging.h>

#include "gavbf_view.h"
#include "gavbf_model.h"

/**************************************************
 * Constants
 **************************************************/
const int POINTERS_WIN_ROWS = 3;
const int TAPE_WIN_ROWS = 5;

/**************************************************
 * Gavbf_View
 **************************************************/

Gavbf_View::Gavbf_View(Gavbf_Controller& controller, Gavbf_Model& model):
	controller{controller},
	model{model},
	program_name{},
	program_file{},
	program_string{},
	input_string{},
	output_string{},
	borders{}
{
	// Init ncurses stuff
	initscr(); // Init ncurses
	start_color(); // Add color capability
	cbreak(); // Don't buffer input
	keypad(stdscr, TRUE); // Allow automatic handling of special characters
	noecho(); // Don't echo input
	curs_set(0); // No cursor

	// Init windows and their borders
	getmaxyx(stdscr, total_y, total_x);
	// The plus and minus 2's account for the window outlines
	int p_win_rows = total_y - (POINTERS_WIN_ROWS + 2) - (TAPE_WIN_ROWS + 2) - 2;
	int p_win_cols = (total_x / 2) - 2;
	int p_win_y = 1;
	int p_win_x = 1;
	program_win = newwin(p_win_rows, p_win_cols, p_win_y, p_win_x);
	borders.push_back({p_win_rows, p_win_cols, p_win_y, p_win_x});

	int i_win_rows = ((total_y - (POINTERS_WIN_ROWS + 2) - (TAPE_WIN_ROWS + 2)) / 2)
		- 2;
	int i_win_cols = (total_x / 2) - 2;
	int i_win_y = 1;
	int i_win_x = (total_x / 2) + 1;
	input_win = newwin(i_win_rows, i_win_cols, i_win_y, i_win_x);
	borders.push_back({i_win_rows, i_win_cols, i_win_y, i_win_x});

	int o_win_rows = total_y - (i_win_rows + 2) - (POINTERS_WIN_ROWS + 2)
		- (TAPE_WIN_ROWS + 2) - 2;
	int o_win_cols = (total_x) / 2 - 2;
	int o_win_y = i_win_y + i_win_rows + 2;
	int o_win_x = (total_x / 2) + 1;
	output_win = newwin(o_win_rows, o_win_cols, o_win_y, o_win_x);
	borders.push_back({o_win_rows, o_win_cols, o_win_y, o_win_x});

	int ptr_win_rows = POINTERS_WIN_ROWS;
	int ptr_win_cols = (total_x / 2) - 2;
	int ptr_win_y = p_win_y + p_win_rows + 2;
	int ptr_win_x = 1;
	pointers_win = newwin(ptr_win_rows, ptr_win_cols, ptr_win_y, ptr_win_x);
	borders.push_back({ptr_win_rows, ptr_win_cols, ptr_win_y, ptr_win_x});
	int b_win_rows = POINTERS_WIN_ROWS;
	int b_win_cols = (total_x / 2) - 2;
	int b_win_y = o_win_y + o_win_rows + 2;
	int b_win_x = (total_x / 2) + 1;
	buttons_win = newwin(b_win_rows, b_win_cols, b_win_y, b_win_x);
	borders.push_back({b_win_rows, b_win_cols, b_win_y, b_win_x});
	int t_win_rows = TAPE_WIN_ROWS;
	int t_win_cols = total_x - 2;
	int t_win_y = ptr_win_y + ptr_win_rows + 2;
	int t_win_x = 1;
	tape_win = newwin(t_win_rows, t_win_cols, t_win_y, t_win_x);
	borders.push_back({t_win_rows, t_win_cols, t_win_y, t_win_x});
}

Gavbf_View::Gavbf_View(Gavbf_Controller& controller, Gavbf_Model& model, string program_name):
	Gavbf_View(controller, model)
{
	this->program_name = program_name;
	this->program_file = ifstream(program_name);
	this->program_string = string{istreambuf_iterator<char>(program_file),
			istreambuf_iterator<char>()};
}

Gavbf_View::~Gavbf_View()
{
	delwin(program_win);
	delwin(input_win);
	delwin(output_win);
	delwin(pointers_win);
	delwin(buttons_win);
	delwin(tape_win);
	endwin();
}

/**************************************************
 * Public Methods
 **************************************************/

void Gavbf_View::bf_output(unsigned char out_char)
{
	output_string += out_char;
}

void Gavbf_View::draw()
{
	draw_background();
	draw_program();
	draw_input();
	draw_output();
	draw_pointers();
	draw_buttons();
	draw_tape();

	refresh();
	wrefresh(program_win);
	wrefresh(input_win);
	wrefresh(output_win);
	wrefresh(pointers_win);
	wrefresh(buttons_win);
	wrefresh(tape_win);
}

void Gavbf_View::draw_background()
{
	for(auto& b : borders) {
		draw_single_border(b.rows, b.cols, b.y, b.x);
	}
	refresh();
}

void Gavbf_View::draw_program()
{
	mvwprintw(program_win, 0, 0, "Input:");
	if(program_file.is_open() == false) {
		mvwprintw(program_win, 1, 0, "<No file selected>");
		// wcolor_set(WINDOW *win, short pair, void* opts);
		wattron(program_win, A_STANDOUT);
	}
	else {
		// wcolor_set(WINDOW *win, short pair, void* opts);
		int i_idx = model.i_idx;
		wmove(program_win, 1, 0);
		wprintw(program_win, "%.*s", i_idx, program_string.c_str());

		wattron(program_win, A_STANDOUT);
		wprintw(program_win, "%c", program_string.c_str()[i_idx]);
		wattroff(program_win, A_STANDOUT);

		wprintw(program_win, "%s", &(program_string.c_str())[i_idx + 1]);

		LOG(INFO) << "i_idx: " << i_idx;
		LOG(INFO) << "program_string: \n"
			<< static_cast<int>(program_string.c_str()[i_idx]);
	}
	// Reset attributes
	wattroff(program_win, A_STANDOUT);
}

void Gavbf_View::draw_input()
{
	mvwprintw(input_win, 0, 0, "Input:");
}

void Gavbf_View::draw_output()
{
	mvwprintw(output_win, 0, 0, "Output:");
	mvwprintw(output_win, 1, 0, output_string.c_str());
}

void Gavbf_View::draw_pointers()
{
	mvwprintw(pointers_win, 0, 0, "Pointers:");
	string tmp = fmt::format("Instruction Pointer: {}", model.i_idx);
	mvwprintw(pointers_win, 1, 0, tmp.c_str());
	tmp = fmt::format("Data Pointer: {}", model.i_idx);
	mvwprintw(pointers_win, 2, 0, tmp.c_str());
}

void Gavbf_View::draw_buttons()
{
	mvwprintw(buttons_win, 0, 0, "Commands");
}

void Gavbf_View::draw_tape()
{
	int y;
	int x;
	int cells;
	vector<unsigned char>& data = model.d_mem;

	getmaxyx(tape_win, y, x);
	cells = (x - 1) / 6;

	string tape0 = " ";
	string tape1 = "|";
	string tape2 = "|";
	string tape3 = "|";

	for(int i = 0; i < cells; ++i) {
		if(i < 10) {
			tape0 += "  " + to_string(i) + "   ";
		}
		else {
			tape0 += "  " + to_string(i) + "  ";
		}
		tape1 += "-----|";
		if(data[i] < 10) {
			tape2 += string("  ") + to_string(data[i]) + "  |";
		}
		else if(data[i] < 100) {
			tape2 += string("  ") + to_string(data[i]) + " |";
		}
		else if(data[i] < 1000) {
			tape2 += string(" ") + to_string(data[i]) + " |";
		}
		else if(data[i] < 10'000) {
			tape2 += " " + to_string(data[i]);
		}
		else {
			tape2 += to_string(data[i]);
		}
		tape3 += "_____|";
	}

	mvwprintw(tape_win, 0, 0, "Tape");
	mvwprintw(tape_win, 1, 0, tape0.c_str());
	mvwprintw(tape_win, 2, 0, tape1.c_str());
	mvwprintw(tape_win, 3, 0, tape2.c_str());
	mvwprintw(tape_win, 4, 0, tape3.c_str());
}

void Gavbf_View::set_tape_start(int start)
{
	// TODO
}

int Gavbf_View::getchar() {
	mvwprintw(input_win, 1, 0, "NEED INPUT!");
	draw_input();
	return getch();
}

/**************************************************
 * Private Methods
 **************************************************/

// This draws a border on stdscr AROUND BUT OUTSIDE the given coordinates
void Gavbf_View::draw_single_border(int rows, int cols, int y, int x)
{
	// Corners
	mvprintw(y - 1, x - 1, "+");
	mvprintw(y - 1, x + cols, "+");
	mvprintw(y + rows, x - 1, "+");
	mvprintw(y + rows, x + cols, "+");
	// Sides
	for(int i = 0; i < rows; ++i) {
		mvprintw(y + i, x - 1, "|");
		mvprintw(y + i, x + cols, "|");
	}
	for(int i = 0; i < cols; ++i) {
		mvprintw(y - 1, x + i, "-");
		mvprintw(y + rows, x + i, "-");
	}
	mvprintw(0, 0, "");
}
