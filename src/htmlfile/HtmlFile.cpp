/*
 * HtmlFile.cpp
 * Created on: Oct 8, 2014
 * Author: Andreea G
 */


#include <src/htmlfile/HtmlFile.hpp>
#include <cerrno>
#include <iostream>
#include <fstream>

using namespace std;

int HtmlFile::ProcessFile() {

	CleanUp();


	return 0;
}


void HtmlFile::CleanUp() {
	//Remove strange text in the begining of file
	(void) RE2::Replace(&contents_, "<!ENTITY % MATHML.prefixed \"INCLUDE\"> \n<!ENTITY % MATHML.prefix \"m\">", "");

	return;
}
