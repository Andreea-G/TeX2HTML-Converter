 /*
	* Master.hpp
	* Created on: Oct 7, 2014
	* Author: Andreea G
	*/

#ifndef MASTER__MASTER_H_
#define MASTER__MASTER_H_

#include <string>
using std::string;

class Master {

public:
	Master(const string html_contents, const string css_contents);

	int MainRun();

	static int ParseArgsAndExecute(int argc, char* argv[]);

private:
	//file contents for the html and css files
	string html_contents_, css_contents_;
};


#endif /*MASTER__MASTER_H_ */
