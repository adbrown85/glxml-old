/*
 * Preprocessor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP
#include "common.h"
#include <fstream>
#include <iomanip>
#include <stack>
#include <vector>
#include "Exception.hpp"
#include "Path.hpp"
#include "Text.hpp"
using namespace std;


/** @brief Utility for preprocessing C-like code.
 * 
 * Basically, %Preprocessor simply looks through C-like code and performs a few 
 * simple operations.  First, if it finds an @e include directive, it replaces 
 * that line with the lines from the appropriate file.  Define directives can 
 * be used to make sure this only happens once.  Lastly, it strips both 
 * multiline and single line comments, as well as trailing spaces.
 * 
 * @ingroup system
 */
class Preprocessor {
public:
	Preprocessor();
	Preprocessor(const string &filename);
	int getRealLineNumber(int line) const;
	string getFileForLine(int line) const;
	vector<string> getLines();
	void printBoundaries();
	void printDefines();
	void printLines();
	void setFilename(const string &filename);
	void start();
protected:
	void addBoundary(const string &line);
	void addLine(string &line, int lineNumber, bool &inComment);
	void addNewLines();
	string getPragmaKey(const string &line);
	string getPragmaValue(const string &line);
	string getToken(const string &line, int i);
	bool isDefine(const string &line);
	bool isEndIf(const string &line);
	bool isIfNotDefined(const string &line);
	bool isInclude(const string &line);
	bool isPragma(const string &line);
	bool isVersion(const string &line);
	void load(const string &filename);
	void onDefine(const string &line);
	void onEndIf(const string &line);
	void onIfNotDefined(const string &line);
	void onInclude(const string &line);
	void onVersion(const string &line);
	string replaceDefines(string &line);
	bool skipLines();
	string stripComments(const string &line, bool &inComment);
	string stripFirstToken(const string &line);
	string stripQuoted(const string &line);
	string stripTrailingSpaces(const string &line);
private:
	map<int,string> boundaries;
	map<string,string> defines;
	stack<bool> conditionals;
	stack<string> paths;
	string filename;
	vector<string> lines;
	vector<int> lineNumbers;
};

/** @return the lines of the file that are actual code. */
inline vector<string> Preprocessor::getLines() {return lines;}


#endif