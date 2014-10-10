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
	CssFile(const string css_contents) : contents_(css_contents) {}
	string get_contents() const { return contents_; }

	int ProcessFile();

private:
	//file contents for the css file
	string contents_;
};


#endif /*CSSFILE__CSSFILE_HPP_ */
