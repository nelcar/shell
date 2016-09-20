#include <unistd.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	string arg = argv[0];
	//vector<string> route;
    vector<string> files;

    char* duplicated = strdup(arg.c_str());
    char* token = strtok(duplicated, " ");
    while(token != NULL){
        files.push_back(string(token));
        token = strtok(NULL, " ");
    }

    string file1 = files[0];
    string file2 = files[1];

    if (symlink(file1.c_str(), file2.c_str()) == -1 ){
    	cout << "Ocurrio un error" << endl;
    }
	return 0;
}