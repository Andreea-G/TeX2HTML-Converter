/*
 * Master.cpp
 * Created on: Oct 7, 2014
 * Author: Andreea G
 */


#include <src/master/Master.hpp>
#include <src/Globals.hpp>
#include <cerrno>
#include <iostream>
#include <fstream>

using namespace std;

Master::Master(const string html_contents, const string css_contents) :
	html_file_(html_contents), css_file_(css_contents) {}


int Master::ParseArgsAndExecute(int argc, char* argv[]) {

	const char *infile = argv[1], *outfile = argv[2], *cssfile = argv[3];

	try {
		string html_contents = globals::get_file_contents(infile);
		string css_contents = globals::get_file_contents(cssfile);

		Master master_process(html_contents, css_contents);

		int exit_status = master_process.MainRun();
		if (exit_status < 0) {
			return -1;
		}

		html_contents = master_process.get_html_contents();

		ofstream out(outfile, ios::out | ios::binary);
		out << html_contents;
		out.close();
		return 0;

	} catch (int &e) {
		cout << "Error reading files. Errno " << e << "\n";
	}

	return -1; //program shouldn't reach here
}


int Master::MainRun() {
	int exit_status = html_file_.ProcessFile();
	if (exit_status < 0) {
		return -1;
	}

	exit_status = css_file_.ProcessFile();
	if (exit_status < 0) {
		return -1;
	}

	return 0;
}
