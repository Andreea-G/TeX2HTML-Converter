 /*
	* HtmlFile.hpp
	* Created on: Oct 8, 2014
	* Author: Andreea G
	*/

#ifndef HTMLFILE__HTMLFLE_HPP
#define HTMLFILE__HTMLFLE_HPP

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
	//Re-align equations with align, eqnarray and equation environments,
		//such that the equation numbers are at the end of the line and on the same vertical label as the equations.
	//Indententations are also fixed. However, there is no way to correct indententions in the case of "equation" environment! (see body of function for details)
		//Will make default non-indented. The only way to make indented text following equation environment will be by
		//writing "\indent" in the lyx or tex file at the begining of the line. Or just use the align or eqnarray environments instead...
	void AlignEquations();
	//Include Videos in the same way as we can include graphics. ogg format is needed for Firefox!
	int IncludeVideos();
	//Add Toggles
	int Toggles();
	//Change some of the math characters to better resemble the pdf output.
		//So far: Lagrangian density (curly L character) and Hamiltonian density (curly H)
	void MathCharacters();
	//Delete horizontal lines that appear before and after figures
	void FiguresFormat();

};


#endif /*HTMLFILE__HTMLFLE_HPP */
