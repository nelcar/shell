#include <iostream>
#include <sys/stat.h>

using namespace std;


int main(int argc, char const *argv[])
{
	cout << argc << endl;
	cout << argv[0] << endl;
	if (mkdir(argv[0], S_IRUSR | S_IWUSR | S_IXUSR) == 0){
		cout << "Se creo Exitosamente" << endl;
		return 0;
	}
	else{
		cout << "Error al utilizar mkdir ... Revise sus argumentos";
		return -1;
	}
	return 0;
}