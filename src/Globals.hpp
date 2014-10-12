#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <string>
#include <sstream>

using std::string;

namespace globals {

extern int MAX_WIDTH; //width of the page measured in inch. Set to 11 in for US letter size.
extern float COLUMN_GAP; //space between columns measured in inch (if multi-column environment). Good values: 0.2 to 0.5 in.

// Useful functions throughout the program
template <class T>
std::string NumberToString (T Number) {
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

// Reads all contents from filename (see reference in Readme)
std::string get_file_contents(const char *filename);

}

#endif // GLOBALS_HPP
