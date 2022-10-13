/**************************************************
 * Includes
 **************************************************/
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <exception> // TODO

/**************************************************
 * Constants
 **************************************************/

const int D_MEM_SIZE = 30000;

/**************************************************
 * Functions
 **************************************************/

using namespace std;

/*
 * Reads the command line args and returns a ifstream object to the brainfuck program to be run
 */
ifstream get_input_file(int argc, char** argv) {
	if(argc < 2) {
		cout << "Missing filename" << endl;
		cout << "Syntax: gavbf <filename>" << endl;
		exit(1);
	}
	if(argc > 2) {
		cout << "Too many arguments" << endl;
		cout << "Syntax: gavbf <filename>" << endl;
		exit(1);
	}
	if(filesystem::exists(argv[1]) == false) {
		cout << "Cannot find file: \"" << argv[1] << "\"" << endl;
		exit(2);
	}
	return ifstream(argv[1]);
}

/*
 * Removes all unnecessary characters from program input
 */
/*
 * @param
 * 	ifstream& in_file: ifstream for input program fie
 * 	vector<char>& i_mem: the vector object that will be initialized to the instructions of the input program
 */
void init_i_mem(ifstream& in_file, vector<char>& i_mem) {
	char cur;
	in_file.get(cur);
	while(in_file.good() && !in_file.eof()) {
		if(cur == '>' || cur == '<' || cur == '+' || cur == '-' || cur == '.' || cur == ',' || cur == '[' || cur == ']') {
			i_mem.push_back(cur);
		}
		in_file.get(cur);
	}
}

/*
 * Processes the next character of the input program
 */
void run_next_char(vector<char>& i_mem, int& i_idx, vector<char>& d_mem, int& d_idx) {
	switch(i_mem[i_idx]) {
		case '>':
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
			cout << d_mem[d_idx];
			break;
		case ',':
			cin >> d_mem[d_idx];
			break;
		case '[':
			if(d_mem[d_idx] == 0) {
				int depth = 0;
				++i_idx;
				while(!(depth == 0 && i_mem[i_idx] == ']')) {
					if(i_mem[i_idx] == '[') {
						++depth;
					}
					else if(i_mem[i_idx] == ']') {
						--depth;
					}
					++i_idx;
				}
			}
			break;
		case ']':
			if(d_mem[d_idx] != 0) {
				int depth = 0;
				--i_idx;
				while(!(depth == 0 && i_mem[i_idx] == '[')) {
					if(i_mem[i_idx] == ']') {
						++depth;
					}
					else if(i_mem[i_idx] == '[') {
						--depth;
					}
					--i_idx;
				}
			}
			break;
	}
	++i_idx;
}

int main(int argc, char** argv) {
	// Read input char
	// Do op
	// loop
	ifstream in_file = get_input_file(argc, argv);

	vector<char> i_mem;
	init_i_mem(in_file, i_mem);
	int i_idx = 0;
	vector<char> d_mem(D_MEM_SIZE, 0);
	int d_idx = 0;

	while(i_idx >= 0 && i_idx < i_mem.size()) {
		run_next_char(i_mem, i_idx, d_mem, d_idx);
	}
}
