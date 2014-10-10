/*
 * CssFile.cpp
 * Created on: Oct 8, 2014
 * Author: Andreea G
 */


#include <src/cssfile/CssFile.hpp>
#include <cerrno>
#include <iostream>
#include <fstream>

using namespace std;

int CssFile::ProcessFile() {
	void FontSizes();
	void MathFonts();


	return 0;
}

void CssFile::FontSizes() {
	(void) RE2::Replace(&contents_, ".cmbx", "h2 { font-size:x-large; text-align:center;}\nh3 { font-size:x-large;}\nh4 { font-size:large;}\nh5 { font-size:medium;}\n.cmbx");
	return;
}

void CssFile::MathFonts() {
	(void) RE2::Replace(&contents_, "math mstyle(.*?)normal; } ", "math mtext.label{ vertical-align:top; }\n math mstyle { vertical-align:top; }\n math mstyle[mathvariant=\"bold\"] mi { font-weight: bold; }\n math mstyle[mathvariant=\"italic\"] mi { font-style: italic; }");
	return;
}
