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
	FontSizes();
	MathFonts();
	AlignEquations();

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

void CssFile::AlignEquations() {
	(void) RE2::Replace(&contents_, "mtd.align-odd{margin-left:2em; text-align:right;}\nmtd.align-even{margin-right:2em; text-align:left;}", "mtable.align-star{ height:100%; }\nmtable.align-full{ width:100%; table-layout:fixed; } \nmtable.align-full mtr{height:1%; vertical-align:middle; }\nmtable.align{ min-width:1%; height:100%; vertical-align:middle; }\nmtd.align-odd{ text-align:right; }\nmtd.align-even{ text-align:left; }\nmtd.align-label{ width:50px; text-align:right; vertical-align:middle; } \nmtable.eqnarray-star{ width:100%; } \nmtable.eqnarray-full{ width:100%; table-layout:fixed; vertical-align:middle; } \nmtable.eqnarray-full mtr{height:1%; vertical-align:middle;}\nmtable.eqnarray{ min-width:1%; height:100%; vertical-align:middle; } \nmtd.eqnarray-1{ text-align:right; }\nmtd.eqnarray-2{ min-width:1%;text-align:center; }\nmtd.eqnarray-3{ text-align:left; }\nmtd.eqnarray-4{ width:50px; text-align:right; vertical-align:middle; }\n.figure { text-align:center; }\n");
	return;
}
