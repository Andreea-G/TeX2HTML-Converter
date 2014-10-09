#include <sstream>
#include <fstream>
#include <string>
#include <cerrno>

using std::string;
using std::ios;

namespace globals {

extern constexpr int MAX_WIDTH = 13;
extern constexpr float COLUMN_GAP = 0.3;

template <class T>
string NumberToString (T Number) {
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

// Reads all contents from filename (see reference above)
string get_file_contents(const char *filename)
{
	std::ifstream in(filename, ios::in | ios::binary);
	if (in)
	{
		string fileContents;
		in.seekg(0, ios::end);
		fileContents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&fileContents[0], fileContents.size());
		in.close();
		return(fileContents);
	}
	throw(errno);
}

}
