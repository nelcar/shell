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
	if( remove( argv[0] ) != 0 )
	    cout << "Error: No habia nada que borrar"<< endl;
	else
	    cout << "Archivo: " << argv[0] << " Borrado." << endl;
	return 0;
}