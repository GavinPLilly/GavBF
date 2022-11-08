/**************************************************
 * Includes
 **************************************************/
#include <iostream>
#include <cassert>
#include <glog/logging.h>


#include "gavbf_model.h"

/**************************************************
 * Constants
 **************************************************/
const int D_MEM_INIT_SIZE = 256;

/**************************************************
 * Gavbf_Model
 **************************************************/
using namespace std;

Gavbf_Model::Gavbf_Model(Gavbf_Controller& controller, string infile_name):
	controller{controller},
	infile_name{infile_name},
	i_idx{0},
	d_idx{0},
	i_mem{},
	d_mem(D_MEM_INIT_SIZE, 0),
	last_executed_instruction{0},
	infile{infile_name}
{
	LOG(INFO) << "Creating Gavbf_Model";
	init_i_mem();
	init_d_mem();
	LOG(INFO) << "Created Gavbf_Model";
}

/**************************************************
 * Public Methods
 **************************************************/
void Gavbf_Model::set_i_idx(int new_i_idx)
{
	assert(new_i_idx >= 0);
	assert(i_mem.size());
	i_idx = new_i_idx;
}

void Gavbf_Model::set_d_idx(int new_d_idx)
{
	assert(new_d_idx >= 0);
	assert(new_d_idx < d_mem.size());
	d_idx = new_d_idx;
}

void Gavbf_Model::write_i_mem(char new_instruction)
{
	i_mem[i_idx] = new_instruction;
}

void Gavbf_Model::write_d_mem(unsigned char new_data)
{
	d_mem[d_idx] = new_data;
}

void Gavbf_Model::execute_next_char()
{
	LOG(INFO) << "Entering execute_next_char()";
	if(is_terminated()) {
		return;
	}
	switch(i_mem[i_idx]) {
		case '>':
			if(d_idx + 1 > d_mem.size()) {
				d_mem.resize((d_mem.size() * 3) / 2);
			}
			++d_idx;
			break;
		case '<':
			--d_idx;
			break;
		case '+':
			++(d_mem[d_idx]);
			break;
		case '-':
			--(d_mem[d_idx]);
			break;
		case '.':
			bf_output(d_mem[d_idx]);
			break;
		case ',':
			d_mem[d_idx] = bf_input();
			break;
		case '[':
			execute_left_bracket();
			break;
		case ']':
			execute_right_bracket();
			break;
	}
	if(is_terminated()) {
		return;
	}
	++i_idx;
	LOG(INFO) << "Exiting execute_next_char()";
}

void Gavbf_Model::execute_next_instruction()
{
	LOG(INFO) << "Entering execute_next_char()";
	// assert(is_terminated() == false);
	if(is_terminated() == true) {
		return;
	}
	while(i_idx < i_mem.size()) {
		if(is_executable_instruction(i_mem[i_idx])) {
			execute_next_char();
			return;
		}
		++i_idx;
	}
	LOG(INFO) << "Exiting execute_next_char()";
}

bool Gavbf_Model::is_terminated()
{
	return i_idx >= i_mem.size();
}

/**************************************************
 * Private Methods
 **************************************************/
void Gavbf_Model::init_i_mem()
{
	char c;
	infile.get(c);
	while(infile.good() && infile.eof() == false) {
		i_mem.push_back(c);
		infile.get(c);
	}
}

void Gavbf_Model::init_d_mem()
{}

void Gavbf_Model::execute_left_bracket()
{
	if(d_mem[d_idx] == 0) {
		int depth = 0;
		++i_idx;
		while(i_idx < i_mem.size()) {
			if(depth == 0 && i_mem[i_idx] == ']') {
				return;
			}
			if(i_mem[i_idx] == '[') {
				++depth;
			}
			else if(i_mem[i_idx] == ']') {
				--depth;
			}
			++i_idx;
		}
	}
}

void Gavbf_Model::execute_right_bracket()
{
	if(d_mem[d_idx] != 0) {
		int depth = 0;
		--i_idx;
		while(i_idx >= 0) {
			if(depth == 0 && i_mem[i_idx] == '[') {
				return;
			}
			if(i_mem[i_idx] == ']') {
				++depth;
			}
			else if(i_mem[i_idx] == '[') {
				--depth;
			}
			--i_idx;
		}
	}
}

void Gavbf_Model::bf_output(unsigned char out_char)
{
	controller.bf_output(out_char);
}

unsigned char Gavbf_Model::bf_input()
{
	return controller.bf_input();
}

/**************************************************
 * Code
 **************************************************/
bool is_executable_instruction(char instruction)
{
	return instruction == '>'
		|| instruction == '<'
		|| instruction == '+'
		|| instruction == '-'
		|| instruction == '.'
		|| instruction == ','
		|| instruction == '['
		|| instruction == ']';
}
