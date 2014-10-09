#include <string>
#include <fstream>
#include <string>
#include <cerrno>

using std::ios;
using std::string;

namespace globals {

extern constexpr int MAX_WIDTH = 13;
extern constexpr float COLUMN_GAP = 0.3;


string get_file_contents(const char *filename) {
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
