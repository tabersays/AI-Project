/**
 *   Loads the names of all files in a directory into a vector and provides
 * access to that vector.
 *
 * @file directory.h
 * @author Thomas Russel Carrel
 */
#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__ 

#include<iostream>
using std::string;
using std::cout;
using std::endl;

//Directory processing
#include<dirent.h>

#include<vector>
using std::vector;

class Directory
{
    public:
        Directory(string);

        const vector<string>& file()
        { return files_; }
    private:
        int current_;
        vector<string> files_;
};
#endif
