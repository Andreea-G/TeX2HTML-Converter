 /*
	* CssFile.hpp
	* Created on: Oct 8, 2014
	* Author: Andreea G
	*/

#ifndef CSSFILE__CSSFILE_HPP
#define CSSFILE__CSSFILE_HPP

#include <string>
#include <re2/re2.h>

using std::string;

class CssFile {

public:
	CssFile(const string css_contents) : contents_(css_contents) {}
	string get_contents() const { return contents_; }

	int ProcessFile();

private:
	//file contents for the css file
	string contents_;

	//Set font sizes for headers
	void FontSizes();
	//Make paragraph spacing 0.5em (half an empty line) rather than 1em (one full line between paragraphs)
	void ParagraphSpacing();
	//Correct math fonts (so e.g. \boldsymbol command in Latex will give proper bold math)
	void MathFonts();
	//Correct alignments for equation, align, and eqnarray environments (equations centered, labels flushed right)
	void AlignEquations();

};


#endif /*CSSFILE__CSSFILE_HPP */
