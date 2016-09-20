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

int main(int argc, char const *argv[])
{
	string line;
	ifstream archivo(argv[0], ios::in);
	if (archivo.is_open()){
		while(getline(archivo,line)){
			cout<<line<<endl;
		}
		archivo.close();
	}
	return 0;
}