/*
 * FileUtility.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "FileUtility.hpp"


/**
 * Builds a path from its parts.
 * 
 * @param root Root of the path.
 * @param parts Parts of the path.
 */
string FileUtility::build(const string &root,
                          vector<string> &parts) {
	
	ostringstream path;
	
	// Check for no parts
	if (parts.empty()) {
		return "";
	}
	
	// Build path from parts using separator
	path << root;
	path << parts[0];
	for (size_t i=1; i<parts.size(); ++i) {
		path << '/';
		path << parts[i];
	}
	return path.str();
}


/**
 * @return filename part from a path.
 */
string FileUtility::getBasename(const string& path) {
	
	int index;
	
	index = path.find_last_of("/\\");
	if (index == -1) {
		return path;
	} else {
		return path.substr(index+1, path.length()-index);
	}
}


/**
 * @return directory part from a path.
 */
string FileUtility::getDirname(const string& path) {
	
	size_t index;
	const char *result;
	
	index = path.find_last_of("/\\");
	if (index > path.length()) {
		result = ".";
	} else if (index == 0) {
		result = "/";
	} else {
		result = path.substr(0, index).c_str();
	}
	
	// Finish
	if (isWindowsRoot(result)) {
		result = "";
	}
	
	// Finish
	return result;
}


string FileUtility::getExtension(const string &path) {
	
	size_t pos;
	
	pos = path.rfind('.');
	return path.substr(pos + 1);
}


/**
 * @return directories between root and filename.
 */
string FileUtility::getInternals(const string& path) {
	
	return stripRoot(getDirname(path));
}


/**
 * Makes a filename relative to another path.
 * 
 * @param primary Path used as the base.
 * @param secondary Relative path to modify primary.
 */
string FileUtility::getRelativePath(const string &primary,
                                    const string &secondary) {
	
	string root;
	vector<string> path, change;
	
	// Check for empty strings
	if (primary.empty() || secondary.empty())
		throw "[FileUtility] Cannot use an empty string.";
	
	// Handle absolute paths
	if (isAbsolutePath(secondary))
		return secondary;
	root = getRoot(primary);
	
	// Split paths
	tokenize(getInternals(primary), path);
	tokenize(secondary, change);
	
	// Merge them back together
	return mergePaths(root, path, change);
}


/**
 * @return top-most directory from a path.
 */
string FileUtility::getRoot(const string &path) {
	
	// Unix
	if (path[0] == '/') {
		return "/";
	}
	
	// Windows
	if (isAbsolutePath(path)) {
		return path.substr(0,3);
	}
	
	return "";
}


/**
 * @return true if the path starts with a drive letter and a colon.
 */
bool FileUtility::hasWindowsRoot(const string &token) {
	
	return isalpha(token[0]) && token[1]==':';
}


/**
 * @return true if the filename is an absolute path.
 */
bool FileUtility::isAbsolutePath(const string& filename) {
	
	// Check for Unix absolute path
	if (filename[0] == '/')
		return true;
	
	// Check for Windows absolute path
	if (filename.length() < 2)
		return false;
	if (isalpha(filename[0])
	      && filename[1] == ':'
	      && (filename[2] == '/' || filename[2] == '\\'))
		return true;
	return false;
}


/**
 * @return true if the token is a drive letter followed by a colon.
 */
bool FileUtility::isWindowsRoot(const string& token) {
	
	return (token.length()==2) && hasWindowsRoot(token);
}


/**
 * @return true if the character is a forward slash or backslash.
 */
bool FileUtility::isSeparator(char character) {
	
	return character == '/' || character == '\\';
}


/**
 * Merges a relative path with a base path.
 * 
 * @param root Top-most directory
 * @param path Base path
 * @param change Relative path 
 */
string FileUtility::mergePaths(const string &root,
                               vector<string> &path,
                               vector<string> &change) {
	
	vector<string>::iterator it;
	
	// Move up in path for each ".." in change
	for (it=change.begin(); it!=change.end(); ++it) {
		if (*it != ".." || path.empty()) {
			break;
		}
		path.pop_back();
	}
	
	// Check if the path is trying to go above root
	if (!root.empty()
	      && path.empty()
	      && *it == "..") {
		throw "[FileUtility] Relative path cannot go above root.";
	}
	
	// After that just add each change to path
	for (; it!=change.end(); ++it) {
		path.push_back(*it);
	}
	
	// Build string from path
	return build(root, path);
}


/**
 * Removes the top-most directory from a path.
 */
string FileUtility::stripRoot(const string &path) {
	
	// Absolute path
	if (isAbsolutePath(path)) {
		if (path[0] == '/') {
			return path.substr(1, -1);
		} else {
			return path.substr(3, -1);
		}
	}
	
	// Also remove current directory
	if (path[0] == '.') {
		if (path.length() == 1) {
			return "";
		} else if (isSeparator(path[1])) {
			return path.substr(2, -1);
		}
	}
	
	// Nothing found
	return path;
}


/**
 * Splits a filename up into tokens.
 * 
 * @param filename Path to split up.
 * @param tokens Parts of the path.
 */
void FileUtility::tokenize(const string &filename,
                           vector<string> &tokens) {
	
	char *token, *buffer;
	
	// Copy filename into buffer
	buffer = new char[filename.length()+1];
	strcpy(buffer, filename.c_str());
	
	// Break up buffer into tokens
	token = strtok(buffer, "/\\");
	while (token != NULL) {
		tokens.push_back(token);
		token = strtok(NULL, "/\\");
	}
	
	// Finish
	delete[] buffer;
}

