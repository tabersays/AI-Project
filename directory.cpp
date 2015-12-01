


#include"directory.h"

Directory::Directory( string name = "./" )
{
    DIR* directory = opendir(name.c_str());
    struct dirent* dir_data;

    while( (dir_data = readdir( directory )) )
    {
        string fname = dir_data->d_name;
        if( fname[0] != '.' )
            files_.push_back(name + fname );
    }

    for( unsigned i = 0; i < files_.size(); i++ )
        cout << files_[i] << endl;
}
