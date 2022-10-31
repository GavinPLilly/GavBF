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
	BF_Controller* controller_ptr;
	string infile_name;
	int i_idx; // Instruction pointer
	int d_idx; // Data pointer
	vector<char> i_mem; // Instruction memory
	vector<unsigned char> d_mem; // Data memory
	int last_executed_instruction;
	ifstream infile;
public:
	Gavbf_Model(BF_Controller* controller_ptr, string infile_name);
	// Mutator methods
	void set_i_idx(int new_i_idx) override;
	void set_d_idx(int new_d_idx) override;
	void write_i_mem(char new_instruction) override;
	void write_d_mem(unsigned char new_data_byte) override;
	void execute_next_char() override;
	void execute_next_instruction() override;
	// Accessor methods
	bool is_terminated() override;
	int get_i_idx() override;
	int get_d_idx() override;
	vector<char>& get_i_mem() override;
	vector<unsigned char>& get_d_mem() override;
	int get_last_executed_instruction() override;
	string get_infile_name() override;
private:
	void init_i_mem();
	void init_d_mem();
	void execute_left_bracket();
	void execute_right_bracket();
	void bf_output(unsigned char out_char);
	unsigned char bf_input();
};

bool is_executable_instruction(char instruction);
#endif //GAVBF_MODEL_H
