 /*
	* CssFile.hpp
	* Created on: Oct 8, 2014
	* Author: Andreea G
	*/

#ifndef CSSFILE__CSSFILE_HPP
#define CSSFILE__CSSFILE_HPP

#include <string>
using std::string;

class CssFile {

public:
	CssFile(const string css_contents) : contents_(css_contents) {}
	int ProcessFile();

private:
	//file contents for the css file
	string contents_;
};


#endif /*CSSFILE__CSSFILE_HPP */
