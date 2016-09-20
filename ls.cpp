#include <iostream>
#include <stdio.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fnmatch.h>

using namespace std;

int getdir (string dir, vector<string> &files){
	struct dirent *dir_struct;
	DIR *direct_getdir;
	if((direct_getdir = opendir(dir.c_str())) == NULL){
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}
	while ((dir_struct = readdir(direct_getdir)) != NULL){
		files.push_back(string(dir_struct->d_name));
	}
	closedir(direct_getdir);
	return 0;
}


int main(int argc, char const *argv[])
{
	char CDIR[1024];
	getcwd(CDIR, sizeof(CDIR));
	string dir = argv[0];
	vector<string> files = vector<string>();
	getdir(dir,files);
	cout << endl;
	if(files.size() < 0){
		cout<<" "<<endl;
	}else{
		for (int i = 0;i < files.size();i++){
			cout << "Archivo[" << i+1 << "]:\t"<<files[i] << endl;
		}
	}

	return 0;
}