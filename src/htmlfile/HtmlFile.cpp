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
