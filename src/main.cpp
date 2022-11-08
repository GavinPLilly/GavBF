/**************************************************
 * Includes
 **************************************************/
#include <iostream>
#include <filesystem>
#include <unistd.h> // used for usleep()
#include <cassert>
#include <glog/logging.h>

#include "gavbf_controller.h"
#include "gavbf_model.h"
#include "gavbf_view.h"

/**************************************************
 * Constants
 **************************************************/

/**************************************************
 * Code
 **************************************************/
using namespace std;

int main(int argc, char** argv)
{
	// Setting up logging
	google::InitGoogleLogging(argv[0]);
	FLAGS_stderrthreshold = google::FATAL;
	// google::stderrthreshold(google::FATAL);
	google::SetLogDestination(google::INFO, "logs/info-");
	google::SetLogDestination(google::WARNING, "logs/warning-");
	google::SetLogDestination(google::ERROR, "logs/error-");
	google::SetLogDestination(google::FATAL, "logs/log-");

	LOG(INFO) << "main.cpp started";

	// Checking file arg
	if(argc < 2) {
		cout << "Missing filename" << endl;
		cout << "Syntax: gavbf <filename>" << endl;
		LOG(ERROR) << "Missing filename argument";
		exit(1);
	}
	if(argc > 2) {
		cout << "Too many arguments" << endl;
		cout << "Syntax: gavbf <filename>" << endl;
		LOG(ERROR) << "Too many arguments";
		exit(1);
	}
	if(std::filesystem::exists(argv[1]) == false) {
		cout << "Cannot find file \"" << argv[1] << "\"" << endl;
		LOG(ERROR) << "Cannot find file\"" << argv[1] << "\"";
		exit(1);
	}

	LOG(INFO) << "File arg: \"" << argv[1] << "\" OK";
	google::FlushLogFiles(google::INFO);

	// Setting up MVC components
	Gavbf_Controller controller;
	Gavbf_Model model(controller, string(argv[1]));
	Gavbf_View view(controller, model, string(argv[1]));
	controller.add_gavbf_model(&model);
	controller.add_gavbf_view(&view);

	controller.run();

	return 0;
}
