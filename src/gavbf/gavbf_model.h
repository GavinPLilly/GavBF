#ifndef GAVBF_MODEL_H
#define GAVBF_MODEL_H
/**************************************************
 * Includes
 **************************************************/
#include <vector>
#include <string>
#include <fstream>

#include "gavbf_controller.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/
using namespace std;

class i_elem {
public:
	char c;
	int row;
	int col;
	i_elem(char c, int row, int col):
		c{c}, row{row}, col{col}
	{}
};

class Gavbf_Model {
	friend class Gavbf_View;
	Gavbf_Controller& controller;
	string infile_name;
	int i_idx; // Instruction pointer
	int d_idx; // Data pointer
	vector<i_elem> i_mem; // Instruction memory
	vector<unsigned char> d_mem; // Data memory
	int last_executed_instruction;
	ifstream infile;
public:
	Gavbf_Model(Gavbf_Controller& controller, string infile_name);
	void set_i_idx(int new_i_idx);
	void set_d_idx(int new_d_idx);
	void write_i_mem(char new_instruction);
	void write_d_mem(unsigned char new_data_byte);
	void execute_to_breakpoint();
	void execute_next_char();
	void execute_next_instruction();
	bool is_terminated();
private:
	void init_i_mem();
	void init_d_mem();
	void execute_left_bracket();
	void execute_right_bracket();
	void bf_output(unsigned char out_char);
	unsigned char bf_input();
};

bool is_executable_instruction(char instruction);
bool is_breakpoint(char c);
#endif //GAVBF_MODEL_H
