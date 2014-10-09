/*
 * HtmlFile.cpp
 * Created on: Oct 8, 2014
 * Author: Andreea G
 */


#include <src/htmlfile/HtmlFile.hpp>
#include <src/Globals.hpp>
#include <cerrno>
#include <iostream>
#include <fstream>

using namespace std;

int HtmlFile::ProcessFile() {

	CleanUp();
	int exit_status = IncludeJavaScripts();
	if (exit_status < 0) {
		return -1;
	}
	MakeColumns();

	return 0;
}


void HtmlFile::CleanUp() {
	//Remove strange text in the begining of file
	(void) RE2::Replace(&contents_, "<!ENTITY % MATHML.prefixed \"INCLUDE\"> \n<!ENTITY % MATHML.prefix \"m\">", "");
	return;
}

int HtmlFile::IncludeJavaScripts () {
	try{
		string script = globals::get_file_contents("javascripts.html");
		re2::StringPiece re2Script(script);
		(void) RE2::Replace(&contents_, "</script>", re2Script);
		return 0;
	} catch (int &e) {
		cout << "Error reading javascript file. Do you have a file called javascripts.html??. Errno " << e << "\n";
	}
	return -1; //program shouldn't reach here
}

void HtmlFile::MakeColumns() {
	int columnNumber;
	string dummy;
	(void) RE2::PartialMatch(contents_, "BeginColumns(\\s)(\\d+)", &dummy, &columnNumber);
	cout << "Column number: " << columnNumber << "\n";
	string myColumns = "<head><style>\n.myWindow{\nmax-width:"
			+ globals::NumberToString(globals::MAX_WIDTH)
			+ "in;\nmargin: 0 auto;\nbackground-color:#FDFDFD;\n}\n.myColumns{\nmax-width:"
			+ globals::NumberToString(globals::MAX_WIDTH) + "in;\nmargin: 0 auto;\n-moz-column-count:"
			+ globals::NumberToString(columnNumber) + ";\n-webkit-column-count:"
			+ globals::NumberToString(columnNumber) + ";\ncolumn-count:"
			+ globals::NumberToString(columnNumber) + ";\n-moz-column-gap:"
			+ globals::NumberToString(globals::COLUMN_GAP) + "in;\n-webkit-column-gap:"
			+ globals::NumberToString(globals::COLUMN_GAP) + "in;\n column-gap:"
			+ globals::NumberToString(globals::COLUMN_GAP) + "in;\n}</style>\n";
	re2::StringPiece re2MyColumns(myColumns);
	(void) RE2::Replace(&contents_, "<head>", re2MyColumns);
	//onload window.scrollTo(0,0) command scrolls to top of page whenever page is reloaded
	(void) RE2::Replace(&contents_, "<body(\\s*)>", "<body class=\"myWindow\"  onload=\"window.scrollTo(0,0)\">\n");
	(void) RE2::GlobalReplace(&contents_, "BeginColumns(\\s)(\\d+)", "<div class=\"myColumns\">");
	(void) RE2::GlobalReplace(&contents_, "EndColumns", "</div>");

	return;
}
