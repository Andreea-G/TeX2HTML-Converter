 /*
	* CssFile.hpp
	* Created on: Oct 8, 2014
	* Author: Andreea G
	*/

#ifndef CSSFILE__CSSFILE_HPP_
#define CSSFILE__CSSFILE_HPP_

#include <string>
using std::string;

class CssFile {

public:
	CssFile(const string css_contents) : css_contents_(css_contents) {}
	int ProcessFile();

private:
	//file contents for the css file
	string css_contents_;
};


#endif /*CSSFILE__CSSFILE_HPP_ */
