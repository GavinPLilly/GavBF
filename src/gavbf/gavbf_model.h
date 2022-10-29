#ifndef GAVBF_MODEL_H
#define GAVBF_MODEL_H
/**************************************************
 * Includes
 **************************************************/
#include <vector>
#include <string>
#include <fstream>

#include "model.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/
using namespace std;

class Gavbf_Model: public BF_Model {
	ifstream infile;
	vector<char> i_mem; // Instruction memory
	vector<char> d_mem; // Data memory
	int i_idx; // Instruction pointer
	int d_idx; // Data pointer
	int last_executed_instruction;
	BF_Controller* controller_ptr;
public:
	Gavbf_Model(BF_Controller* controller_ptr, string infile_name);
	// Mutator methods
	void set_i_idx(int new_i_idx);
	void set_d_idx(int new_d_idx);
	void write_i_mem(char new_instruction);
	void write_d_mem(char new_data_byte);
	void execute_next_char();
	void execute_next_instruction();
	// Accessor methods
	bool is_terminated();
	vector<char>& get_i_mem();
	vector<char>& get_d_mem();
	int get_i_idx();
	int get_d_idx();
	int get_last_executed_instruction();
private:
	void open_infile(string infile_name);
	void init_i_mem();
	void init_d_mem();
	void execute_left_bracket();
	void execute_right_bracket();
	void output(char out_char);
	char input();
};

bool is_executable_instruction(char instruction);
#endif //GAVBF_MODEL_H
