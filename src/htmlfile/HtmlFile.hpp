 /*
	* HtmlFile.hpp
	* Created on: Oct 8, 2014
	* Author: Andreea G
	*/

#ifndef HTMLFILE__HTMLFLE_HPP_
#define HTMLFILE__HTMLFLE_HPP_

#include <string>
using std::string;

class HtmlFile {

public:
	HtmlFile(const string html_contents) : html_contents_(html_contents) {}
	int ProcessFile();

private:
	//file contents for the html file
	string html_contents_;
};


#endif /*HTMLFILE__HTMLFLE_HPP_ */
