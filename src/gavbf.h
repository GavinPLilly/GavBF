#ifndef GAVBF_H
#define GAVBF_H
/**************************************************
 * Includes
 **************************************************/
#include <vector>
#include <string>
#include <fstream>

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/
using namespace std;

class BF_Program_View {
public:
	virtual void output(char out_char) = 0;
	virtual char input() = 0;
};

class BF_Program {
	ifstream infile;
	vector<char> i_mem; // Instruction memory
	vector<char> d_mem; // Data memory
	int i_idx; // Instruction pointer
	int d_idx; // Data pointer
	int last_executed_instruction;
	BF_Program_View* view_ptr;
public:
	BF_Program(string infile_name, BF_Program_View* view);
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
#endif //GAVBF_H
