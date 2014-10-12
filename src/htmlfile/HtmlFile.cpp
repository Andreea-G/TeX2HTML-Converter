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
		cerr << "Error in HtmlFile::IncludeJavaScripts\n";
		return -1;
	}
	MakeColumns();
	AlignEquations();
	exit_status = IncludeVideos();
	if (exit_status < 0) {
		cerr << "Error in HtmlFile::IncludeVideos\n";
		return -1;
	}
	exit_status = Toggles();
	if (exit_status < 0) {
		cerr << "Error in HtmlFile::Toggles\n";
		return -1;
	}
	exit_status = Alerts();
	if (exit_status < 0) {
		cerr << "Error in HtmlFile::Alerts\n";
		return -1;
	}
	return 0;
}


void HtmlFile::CleanUp() {
	//Remove strange text in the begining of file
	(void) RE2::Replace(&contents_, "<!ENTITY % MATHML.prefixed \"INCLUDE\"> \n<!ENTITY % MATHML.prefix \"m\">", "");

	//Clean up file. Delete useless endlines, and insert endlines before comments
		//(useful since many of the comments in html file point to corresponding lines inside the original Latex file!)
	string begining(""), replacement("");
	(void) RE2::PartialMatch(contents_, "((.|\\s)*)</script>", &begining);
	(void) RE2::PartialMatch(contents_, "</script>([\\s\\S]*?)</body>", &replacement);
	(void) RE2::GlobalReplace(&replacement, "(\\s+)", " ");
	(void) RE2::GlobalReplace(&replacement, "<![-][-]", "\n\n<!--");
	contents_ = begining + "</script>\n\n" + replacement + "\n</body>\n</html>";

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


void HtmlFile::AlignEquations() {
	//Align equations with "align" environment
	string dummy;		//will be useful to get rid of "(\\s)"
	string equation, replacement;
	while (RE2::PartialMatch(contents_, "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" display=\"block\" ><mtable columnalign=\"left\" class=\"align\">((.|\\s)*?)</mtr></mtable></math>", &equation)) {
		string labelRaw, labelTable("</mtr></mtable></mtd><mtd class=\"align-label\"><mtable class=\"align\">");
		while (RE2::PartialMatch(equation, "<mtd(( columnalign=\"right\" )| )class=\"align-label\">((.|\\s)*?)</mtd>", &dummy, &dummy, &labelRaw)) {
			labelTable = labelTable + "<mtr><mtd columnalign=\"right\" class=\"align-label\">" + labelRaw + "</mtd></mtr>";
			RE2::Replace(&equation, "<mtd(( columnalign=\"right\" )| )class=\"align-label\">((.|\\s)*?)</mtd>", "");
		}
		equation = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" display=\"block\" ><mtable class=\"align-full\"><mtr><mtd><mtable columnalign=\"left\" class=\"align\">" + equation + labelTable + "</mtable></mtd></mtr></mtable></math>";
		re2::StringPiece re2Equation(equation);
		RE2::Replace(&contents_, "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" display=\"block\" ><mtable columnalign=\"left\" class=\"align\">((.|\\s)*?)</mtr></mtable></math>", re2Equation);
	}

	//Align equations with "eqnarray" environment
	while (RE2::PartialMatch(contents_, "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" display=\"block\" > <mtable class=\"eqnarray\" columnalign=\"right center left\" >((.|\\s)*?)</mtr></mtable>(\\s)</math>", &equation)) {
		string labelRaw, labelTable("</mtr></mtable></mtd><mtd class=\"eqnarray-4\"><mtable class=\"eqnarray\">");
		while (RE2::PartialMatch(equation, "<mtd class=\"eqnarray-4\">((.|\\s)*?)</mtd>", &labelRaw)) {
			labelTable = labelTable + "<mtr><mtd class=\"eqnarray-4\">" + labelRaw + "</mtd></mtr>";
			RE2::Replace(&equation, "<mtd class=\"eqnarray-4\">((.|\\s)*?)</mtd>", "");
		}
		equation = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" display=\"block\" ><mtable class=\"eqnarray-full\"><mtr><mtd><mtable class=\"eqnarray\" columnalign=\"right center left\" >" + equation + labelTable + "</mtable></mtd></mtr></mtable></math>";
		re2::StringPiece re2Equation(equation);
		RE2::Replace(&contents_, "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" display=\"block\" > <mtable class=\"eqnarray\" columnalign=\"right center left\" >((.|\\s)*?)</mtr></mtable>(\\s)</math>", re2Equation);
	}

	//Fix strange indentation for "eqnarray" environment. Specifically, the next paragraph is mistakenly indented after numbered "eqnarrays".
	(void) RE2::GlobalReplace(&contents_, "<p class=\"nopar\" > </p> \n\n<!--l. (\\d+)--><p class=\"indent\" >", "<p class=\"noindent\" >");

	//Similarly, text following a numbered "equation" environment is always indented.
		//However, there is no pattern to correct for this time! :( Will make default non-indented.
		//Only way to make indented text following equation environment will be by writing "\indent" in the lyx or tex file at the begining of the line.
		//Or just use the align or eqnarray environments instead...
	int eqnNumber = 0, lineNumber = 0;
	while (RE2::PartialMatch(contents_, "</math></td><td class=\"eq-no\">\\((\\d+)\\)</td></tr></table> \n\n<!--l. (\\d+)--><p class=\"indent\" >", &eqnNumber, &lineNumber)) {
		replacement = "</math></td><td class=\"eq-no\">(" + globals::NumberToString(eqnNumber) + ")</td></tr></table> \n\n<!--l. (" + globals::NumberToString(lineNumber) + ")--><p class=\"noindent\" >";
		re2::StringPiece re2Replacement(replacement);
		RE2::Replace(&contents_, "</math></td><td class=\"eq-no\">\\((\\d+)\\)</td></tr></table> \n\n<!--l. (\\d+)--><p class=\"indent\" >", re2Replacement);
	}

	//Make indentations. Important! This block must be after the "equation" environment indentations (see above)
	(void) RE2::GlobalReplace(&contents_, "class=\"noindent\" >IndentHere ", "class=\"indent\" >");
	(void) RE2::GlobalReplace(&contents_, "class=\"indent\" >IndentHere ", "class=\"indent\" >");
	(void) RE2::GlobalReplace(&contents_, "class=\"noindent\" > IndentHere ", "class=\"indent\" > ");
	(void) RE2::GlobalReplace(&contents_, "class=\"indent\" > IndentHere ", "class=\"indent\" > ");
	(void) RE2::GlobalReplace(&contents_, "FullJustify", "<div align=\"justify\">");
	(void) RE2::GlobalReplace(&contents_, "EndJustify", "</div>");
	(void) RE2::GlobalReplace(&contents_, "DrawHLine", "\n<hr>\n");

	//Remove strange empty columns for "align-star"
	(void) RE2::GlobalReplace(&contents_, "<mtd columnalign=\"right\" class=\"align-label\"></mtd> <mtd class=\"align-label\"> <mspace width=\"2em\"/></mtd>", "");
	//Remove strange empty <mtext class="endlabel"> for "eqnarray"
	(void) RE2::GlobalReplace(&contents_, "<mtext class=\"endlabel\"></mtext>", "");

	return;
}

//BeginVideo bear&#x02D9;movie.ogg<img src="fig_1.png" alt="PIC" />EndVideo

int HtmlFile::IncludeVideos() {
	string VideoName("");
	string replacement, dummy;
	//must have ogg format, otherwise Firefox will not work!
	while (RE2::PartialMatch(contents_, "BeginVideo(\\s)((\\w|&#x02D9;)+).ogg([\\s\\S]*?)EndVideo", &dummy, &VideoName, &dummy)) {
		//TODO: test if VideoName is empty
		(void) RE2::GlobalReplace(&VideoName, "&#x02D9;", "_");
		replacement = "<video width=\"480\" height=\"360\" controls> <source src=\"" + VideoName + ".ogg\" type=\"video/ogg\"><source src=\"" + VideoName + ".mp4\" type=\"video/mp4\"> </video>";
		re2::StringPiece re2Replacement(replacement);
		(void) RE2::Replace(&contents_, "BeginVideo(\\s)((\\w|&#x02D9;)+).ogg((.|\\s)*?)EndVideo", re2Replacement);
	}
	//TODO test if any "BeginVideo...EndVideo" left.
	return 0;
}

int HtmlFile::Toggles() {
	//Start all Toggles
	string dummy, replacement;
	string IDword, ShowHide, Display(""), BackColor;
	while (RE2::PartialMatch(contents_, "BeginToggle(\\s)(\\w+)(\\s)(\\w+)(\\s)(\\w+)(\\s)((\\w|\\s|&#x2019;)*)(\\s)BeginToggle", &dummy, &ShowHide, &dummy, &IDword, &dummy, &BackColor, &dummy, &Display)) {
		(void) RE2::GlobalReplace(&Display, "\n", " ");
		if (RE2::FullMatch(Display, "null")) {
			(void) RE2::GlobalReplace(&Display, "null", "");
		} else {Display = " " + Display; }
		if (RE2::FullMatch(ShowHide, "Show")) {
			replacement = "<input id=\"displayIDword\" type=\"button\" onclick=\"return toggleButton('toggleIDword','displayIDword','Myval')\" value=\"HideMyval\"><br><div id=\"toggleIDword\" style=\"display:block;background-color:#MyColor\">";
		} else if (RE2::FullMatch(ShowHide, "Hide")) {
			replacement = "<input id=\"displayIDword\" type=\"button\" onclick=\"return toggleButton('toggleIDword','displayIDword','Myval')\" value=\"ShowMyval\"><br><div id=\"toggleIDword\" style=\"display:none;background-color:#MyColor\">";
		} else {
			return -1;
		}
		re2::StringPiece re2IDword(IDword);
		(void) RE2::GlobalReplace(&replacement, "IDword", re2IDword);
		re2::StringPiece re2Display(Display);
		(void) RE2::GlobalReplace(&replacement, "Myval", re2Display);
		re2::StringPiece re2BackColor(BackColor);
		(void) RE2::GlobalReplace(&replacement, "MyColor", re2BackColor);
		re2::StringPiece re2Replacement(replacement);
		(void) RE2::Replace(&contents_, "BeginToggle(\\s)(\\w+)(\\s)(\\w+)(\\s)(\\w+)(\\s)((\\w|\\s|&#x2019;)*)(\\s)BeginToggle", re2Replacement);
	}
	//End all Toggles
	(void) RE2::GlobalReplace(&contents_, "EndToggle", "</div>");

	return 0;
}

int HtmlFile::Alerts() {
	//Start all Alerts
	string dummy;
	string alertText;
	while (RE2::PartialMatch(contents_, "BeginAlert(\\s)([\\s\\S]*?)(\\s)AlertOnClick", &dummy, &alertText)) {
		cout << "Alert:\n";
		cout << alertText << "\n";
		(void) RE2::GlobalReplace(&alertText, "\"", "\\\\\\\\'"); //yup, 8 of them!
			//The string parser removes half, regex removes half of what's left,
			//and we also repeat the operation when inserting alertText into contents...
			//End result will be one \ followed by one '
		(void) RE2::GlobalReplace(&alertText, "\n", " ");
		alertText = "<span onmouseover=\"return changeColor(this,'red')\" onmouseout=\"return changeColor(this,'black')\" onClick=\"return myAlert('" + alertText + "')\">";
		re2::StringPiece re2alertText(alertText);
		(void) RE2::Replace(&contents_, "((<p class=\"noindent\" > )*)BeginAlert(\\s)([\\s\\S]*?)(\\s)AlertOnClick(( </p>)*)", re2alertText);
		//TODO: this could also be "indent" ??
	}
	//End all Alerts
	(void) RE2::GlobalReplace(&contents_, "EndAlert", "</span>");

	return 0;
}
