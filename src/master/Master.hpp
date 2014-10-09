 /*
	* Master.hpp
	* Created on: Oct 7, 2014
	* Author: Andreea G
	*/

#ifndef MASTER__MASTER_HPP_
#define MASTER__MASTER_HPP_

#include <string>

#include <src/htmlfile/HtmlFile.hpp>
#include <src/cssfile/CssFile.hpp>

using std::string;

class Master {

public:
	Master(const string html_contents, const string css_contents);
	string get_html_contents() const { return html_file_.get_contents(); }

	int MainRun();

	static int ParseArgsAndExecute(int argc, char* argv[]);

private:
	HtmlFile html_file_;
	CssFile css_file_;
};


#endif /*MASTER__MASTER_HPP_ */
