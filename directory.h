
#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__ 

#include<iostream>
using std::string;

#include<dirent.h>

#include<vector>
using std::vector;

class Directory
{
    public:
        Directory(void);
        Directory(string);

        const vector<char*>& file()
        { return files_; }
    private:
        int current_;
        vector<char*> files_;
};
#endif
