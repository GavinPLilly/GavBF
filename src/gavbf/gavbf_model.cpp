/**************************************************
 * Includes
 **************************************************/
#include <iostream>
#include <cassert>

#include <filesystem>

#include "gavbf_model.h"

/**************************************************
 * Constants
 **************************************************/
const int D_MEM_INIT_SIZE = 256;

/**************************************************
 * Gavbf_Model
 **************************************************/
using namespace std;

Gavbf_Model::Gavbf_Model(BF_Controller* controller_ptr, string infile_name) {
	open_infile(infile_name);
	this->controller_ptr = controller_ptr;
	init_i_mem();
	init_d_mem();
	i_idx = 0;
	d_idx = 0;
	last_executed_instruction = 0;
}

/**************************************************
 * Public Methods
 **************************************************/
void Gavbf_Model::set_i_idx(int new_i_idx) {
	assert(new_i_idx >= 0);
	assert(i_mem.size());
	i_idx = new_i_idx;
}

void Gavbf_Model::set_d_idx(int new_d_idx) {
	assert(new_d_idx >= 0);
	assert(new_d_idx < d_mem.size());
	d_idx = new_d_idx;
}

void Gavbf_Model::write_i_mem(char new_instruction) {
	i_mem[i_idx] = new_instruction;
}

void Gavbf_Model::write_d_mem(char new_data) {
	d_mem[d_idx] = new_data;
}

void Gavbf_Model::execute_next_char() {
	assert(is_terminated() == false);
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
			output(d_mem[d_idx]);
			break;
		case ',':
			d_mem[d_idx] = input();
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
}

void Gavbf_Model::execute_next_instruction() {
	assert(is_terminated() == false);
	while(i_idx < i_mem.size()) {
		if(is_executable_instruction(i_mem[i_idx])) {
			execute_next_instruction();
			return;
		}
		++i_idx;
	}
}

bool Gavbf_Model::is_terminated() {
	return i_idx >= i_mem.size();
}

vector<char>& Gavbf_Model::get_i_mem() {
	return i_mem;
}

vector<char>& Gavbf_Model::get_d_mem() {
	return d_mem;
}

int Gavbf_Model::get_i_idx() {
	return i_idx;
}
int Gavbf_Model::get_d_idx() {
	return d_idx;
}

int Gavbf_Model::get_last_executed_instruction() {
	return last_executed_instruction;
}

/**************************************************
 * Private Methods
 **************************************************/
void Gavbf_Model::open_infile(string infile_name) {
	assert(filesystem::exists(infile_name));
	infile = ifstream(infile_name);
}

void Gavbf_Model::init_i_mem() {
	char c;
	i_mem = vector<char>();
	infile.get(c);
	while(infile.good() && infile.eof() == false) {
		i_mem.push_back(c);
		infile.get(c);
	}
}

void Gavbf_Model::init_d_mem() {
	d_mem = vector<char>(D_MEM_INIT_SIZE, 0);
}

void Gavbf_Model::execute_left_bracket() {
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

void Gavbf_Model::execute_right_bracket() {
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

void Gavbf_Model::output(char out_char) {
	controller_ptr->output(out_char);
}

char Gavbf_Model::input() {
	return controller_ptr->input();
}

/**************************************************
 * Code
 **************************************************/
bool is_executable_instruction(char instruction) {
	return instruction == '>'
		|| instruction == '<'
		|| instruction == '+'
		|| instruction == '-'
		|| instruction == '.'
		|| instruction == ','
		|| instruction == '['
		|| instruction == ']';
}
