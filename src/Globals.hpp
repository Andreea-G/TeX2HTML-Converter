#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

namespace globals {

extern int MAX_WIDTH; //width of the page measured in inch. Set to 11 in for US letter size.
extern float COLUMN_GAP; //space between columns measured in inch (if multi-column environment). Good values: 0.2 to 0.5 in.

// Useful functions throughout the program

// Convert number to string
template <class T>
std::string NumberToString (T Number);

// Reads all contents from filename (see reference in Readme)
std::string get_file_contents(const char *filename);

}

#endif // GLOBALS_H
