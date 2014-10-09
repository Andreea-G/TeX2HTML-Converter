 /*
	* HtmlFile.hpp
	* Created on: Oct 8, 2014
	* Author: Andreea G
	*/

#ifndef HTMLFILE__HTMLFLE_HPP_
#define HTMLFILE__HTMLFLE_HPP_

#include <string>
#include <re2/re2.h>

using std::string;

class HtmlFile {

public:
	HtmlFile(const string html_contents) : contents_(html_contents) {}
	string get_contents() const { return contents_; }

	int ProcessFile();

private:
	//file contents for the html file
	string contents_;

	void CleanUp();
};


#endif /*HTMLFILE__HTMLFLE_HPP_ */
