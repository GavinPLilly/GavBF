#ifndef MODEL_H
#define MODEL_H
/**************************************************
 * Includes
 **************************************************/
#include <vector>
#include <string>

#include "controller.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Declarations
 **************************************************/
using namespace std;

class BF_Model {
public:
	// Mutator methods
	virtual void set_i_idx(int new_i_idx) = 0;
	virtual void set_d_idx(int new_d_idx) = 0;
	virtual void write_i_mem(char new_instruction) = 0;
	virtual void write_d_mem(unsigned char new_data_byte) = 0;
	virtual void execute_next_char() = 0;
	virtual void execute_next_instruction() = 0;
	// Accessor methods
	virtual bool is_terminated() = 0;
	virtual int get_i_idx() = 0;
	virtual int get_d_idx() = 0;
	virtual vector<char>& get_i_mem() = 0;
	virtual vector<unsigned char>& get_d_mem() = 0;
	virtual int get_last_executed_instruction() = 0;
	virtual string get_infile_name() = 0;
};

#endif // MODEL_H
