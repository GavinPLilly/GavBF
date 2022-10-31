/**************************************************
 * Includes
 **************************************************/
#include <iostream>
#include <fmt/core.h>

#include "gavbf_view.h"
#include "model.h"

/**************************************************
 * Constants
 **************************************************/
const int POINTERS_WIN_ROWS = 3;
const int TAPE_WIN_ROWS = 5;

/**************************************************
 * Gavbf_View
 **************************************************/

Gavbf_View::Gavbf_View(BF_Controller* controller):
	controller(controller),
	infile_name{},
	infile{},
	infile_string{},
	output_string{},
	borders{}
{
	// Init ncurses stuff
	initscr();
	noecho();
	curs_set(0);

	// Init windows and their borders
	getmaxyx(stdscr, total_y, total_x);
	// The plus and minus 2's account for the window outlines
	int i_p_win_rows = total_y - (POINTERS_WIN_ROWS + 2) - (TAPE_WIN_ROWS + 2) - 2;
	int i_p_win_cols = (total_x / 2) - 2;
	int i_p_win_y = 1;
	int i_p_win_x = 1;
	input_program_win = newwin(i_p_win_rows, i_p_win_cols, i_p_win_y, i_p_win_x);
	borders.push_back({i_p_win_rows, i_p_win_cols, i_p_win_y, i_p_win_x});
	int o_p_win_rows = total_y - (POINTERS_WIN_ROWS + 2) - (TAPE_WIN_ROWS + 2) - 2;
	int o_p_win_cols = (total_x) / 2 - 2;
	int o_p_win_y = 1;
	int o_p_win_x = (total_x / 2) + 1;
	program_output_win = newwin(o_p_win_rows, o_p_win_cols, o_p_win_y, o_p_win_x);
	borders.push_back({o_p_win_rows, o_p_win_cols, o_p_win_y, o_p_win_x});
	int p_win_rows = POINTERS_WIN_ROWS;
	int p_win_cols = (total_x / 2) - 2;
	int p_win_y = i_p_win_y + i_p_win_rows + 2;
	int p_win_x = 1;
	pointers_win = newwin(p_win_rows, p_win_cols, p_win_y, p_win_x);
	borders.push_back({p_win_rows, p_win_cols, p_win_y, p_win_x});
	int b_win_rows = POINTERS_WIN_ROWS;
	int b_win_cols = (total_x / 2) - 2;
	int b_win_y = o_p_win_y + o_p_win_rows + 2;
	int b_win_x = (total_x / 2) + 1;
	buttons_win = newwin(b_win_rows, b_win_cols, b_win_y, b_win_x);
	borders.push_back({b_win_rows, b_win_cols, b_win_y, b_win_x});
	int t_win_rows = TAPE_WIN_ROWS;
	int t_win_cols = total_x - 2;
	int t_win_y = p_win_y + p_win_rows + 2;
	int t_win_x = 1;
	tape_win = newwin(t_win_rows, t_win_cols, t_win_y, t_win_x);
	borders.push_back({t_win_rows, t_win_cols, t_win_y, t_win_x});
}

Gavbf_View::Gavbf_View(BF_Controller* controller, string infile_name):
	Gavbf_View(controller)
{
	this->infile_name = infile_name;
	this->infile = ifstream(infile_name);
	this->infile_string = string{istreambuf_iterator<char>(infile),
			std::istreambuf_iterator<char>()};
}

Gavbf_View::~Gavbf_View()
{
	delwin(input_program_win);
	delwin(program_output_win);
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
	// draw_background();
	draw_input();
	draw_output();
	draw_pointers();
	draw_buttons();
	draw_tape();

	// refresh();
	wrefresh(input_program_win);
	wrefresh(program_output_win);
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

void Gavbf_View::draw_input()
{
	mvwprintw(input_program_win, 0, 0, "Input:");
	if(infile.is_open() == false) {
		mvwprintw(input_program_win, 1, 0, "<No file selected>");
		return;
	}
	mvwprintw(input_program_win, 1, 0, infile_string.c_str());
}

void Gavbf_View::draw_output()
{
	mvwprintw(program_output_win, 0, 0, "Output:");
	mvwprintw(program_output_win, 1, 0, output_string.c_str());
}

void Gavbf_View::draw_pointers()
{
	mvwprintw(pointers_win, 0, 0, "Pointers:");
	string tmp = fmt::format("Instruction Pointer: {}",
			controller->get_model().get_i_idx());
	mvwprintw(pointers_win, 1, 0, tmp.c_str());
	tmp = fmt::format("Data Pointer: {}", controller->get_model().get_d_idx());
	mvwprintw(pointers_win, 2, 0, tmp.c_str());
}

void Gavbf_View::draw_buttons()
{
	mvwprintw(buttons_win, 0, 0, "Buttons");
}

void Gavbf_View::draw_tape()
{
	mvwprintw(tape_win, 0, 0, "Tape:");
}

void Gavbf_View::set_tape_start(int start)
{
	// TODO
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
