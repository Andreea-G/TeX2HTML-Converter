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

	//Processing functions. There are called from ProcessFile() only.
	//Initial file clean up
	void CleanUp();
	//Include all scripts from file "javascripts.html"
	int IncludeJavaScripts ();
	//Make n columns, total width equal to MAX_WIDTH in. The number of columns is specified in the tex file.
		//To modify max width change MAX_WIDTH in globals.
		//For US Letter Landscape set MAX_WIDTH to 11.
		//TODO Only works for same number of columns everywhere! Will need to improve later...
	void MakeColumns();

};


#endif /*HTMLFILE__HTMLFLE_HPP_ */
