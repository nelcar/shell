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
#include <sys/utsname.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

using namespace std;

char CDIR[1024];

string contenido;
int contador;
string subStr = "nul";
string subStrPipe = "nul";
string direccionActual; 
bool pipeExist;
vector<string> comandosPipe;
vector<int> cmdSizes;
vector<string> comandos;
	
void p_mkdir();
void p_cd();
void p_ls();
void p_clear();
void p_cat();
void p_rmdir();
void p_rm();
void p_ln();
void p_ps();
void p_uname();
void p_kill();
void coman();
int main(int argc, char const *argv[]) {
	int fd[2];
	pipe(fd);

	comandos.push_back("mkdir");
	comandos.push_back("cd");
	comandos.push_back("ls");
	comandos.push_back("clear");
	comandos.push_back("exit");
	comandos.push_back("cat");
	//comandos.push_back("chmod");
	comandos.push_back("rmdir");
	comandos.push_back("rm");
	//comandos.push_back("ln");
	comandos.push_back("ps");
	comandos.push_back("uname");
	comandos.push_back("kill");

	coman();

	getcwd(CDIR,sizeof(CDIR));
	direccionActual = CDIR;
	direccionActual += "/";
	

	cout << "" << endl;
	while(true){
		pipeExist = false;
		cout<<"@miShell--@ >> "<<direccionActual<<"> ";
		comandosPipe.clear();
		cmdSizes.clear();
		getline(cin,contenido);
		contador = 0;
		for (int i = 0; i   < contenido.size(); i++){
			if (contenido[i] == ' '){
				break;
			}else{
				contador++;
			}
		}
		subStr = contenido.substr(0,contador);
		for (int i = 0; i < contenido.size(); ++i)
		{
			if (contenido[i]=='|')
			{
				pipeExist=true;
			}
		}
    	if (pipeExist){//Existe algun multicomando

    	}else{//No Existe multicomandos
    		if (subStr ==  "mkdir") {
    			p_mkdir();
    		}
    		else if(contenido == "cd"){
    			cout << "Error: falta de argumentos luego del cd" << endl;
    		}
    		else if(subStr=="cd"){
    			p_cd();    			
    		}
    		else if (contenido =="ls")
    		{
    			p_ls();
    		}
    		else if(contenido=="clear"){
    			p_clear();
    		}
    		else if(contenido=="exit"){
    			break;
    		}else if(contenido == "cat"){
    			cout << "Error: falta de argumentos luego del cat" << endl;			
    		}else if(subStr == "cat"){
    			p_cat();
    		}else if(contenido == "rmdir"){
    			cout << "Error: falta de argumentos luego del rmdir" << endl;
    		}else if(subStr == "rmdir"){
    			p_rmdir();
    		}else if(contenido == "rm"){
    			cout << "Error: falta de argumentos luego del rm" << endl;
    		}else if(subStr == "rm"){
    			p_rm();
    		}else if(contenido == "ln"){

    		}else if(subStr == "ln"){
    			//p_ln();
    		}else if(contenido == "ps"){
    			p_ps();
    		}else if(contenido == "kill"){
    			cout << "Error: falta de argumentos luego del kill" << endl;
    		}else if(subStr == "kill"){
    			p_kill();
    		}else if(contenido == "uname"){
    			p_uname();
    		}else if(contenido == "mn"){
    			coman();
    		}else{
    			cout << "comando no existe" << endl;
    		}
    	}
    } // fin while true
    return 0;
}

void p_mkdir(){
	string dir = direccionActual + "/" +contenido.substr(contador+1,contenido.size());
	char* name[] = {(char*) dir.c_str(), (char*)0};
                //cout << name[0]<<endl;
	if (!fork()) {
		string exe = CDIR;
		exe += "/mkdir";
		execv(exe.c_str(),name);
	}
}

void p_cd(){
	string carpeta = contenido.substr(contador+1,contenido.size());
	if (carpeta == ".."){
		//cout << "entro a carpeta" << endl;
		//cout << direccionActual << endl;
		int counter = 0;
		for (int i = 0; i < direccionActual.size(); ++i){
			if(direccionActual[i]=='/')
				counter++;
		}
		//cout << direccionActual << endl;
		//cout << "despues del for" << endl;
		int counterletter = 0;
		//cout << "counter letter: "<< counterletter << endl;
		
		int counter2 = 0;
		for (int i = 0; i < direccionActual.size(); ++i){
			if ((counter-1)==counter2){
				break;
			}else if(direccionActual[i]=='/'){
				counter2++;
			}
			counterletter++;
		}
		cout << "counter2: "<< counter2 << endl;
		
		//cout << direccionActual << endl;
		//cout << "depues otro for" << endl;
		string substr2 = direccionActual.substr(0,counterletter);
		//cout << "counter letter: "<< counterletter << endl;
		direccionActual = substr2;
		//cout << direccionActual << endl;
	}else{
		//cout << direccionActual << endl;
		string tmp = direccionActual +"/" +carpeta;
		if ( access( tmp.c_str(), 0 ) == 0 ){
			struct stat status;
			stat( tmp.c_str(), &status );

			if ( status.st_mode & S_IFDIR )
			{
				direccionActual += (carpeta+"/");
			}       
		}else{
			cout << "**********"<<endl<<"ERROR: La carpeta que ingreso no existe" << endl << "**********" << endl;
		}
	}
}

void p_ls(){
	if (!fork()) {
		string exe = CDIR;
		char* directory[] = {(char*) direccionActual.c_str(), (char*)0};
		string com = exe + "/ls";
		execv(com.c_str(),directory);
	}

}

void p_ps(){
	if (!fork()) {
		execlp("ps","ps",NULL);
	}
}

void p_clear(){
	for (int i = 0; i < 25; i++){
		cout<<endl<<endl;
	}
	cout << "\e[H\e[2J";
}

void p_cat(){
	string dir = direccionActual + contenido.substr(contador+1,contenido.size());
	char* name[] = {(char*) dir.c_str(), (char*)0};
	//cout << name[0] << endl;
	if (!fork()) {
		string exe = CDIR;
		exe += "/cat";
		execv(exe.c_str(),name);
	}
}

void p_rmdir(){
	string dir = direccionActual + contenido.substr(contador+1,contenido.size());
	char* name[] = {(char*) dir.c_str(), (char*)0};

	if (!fork()) {
		string exe = CDIR;
		exe += "/rmdir";
		execv(exe.c_str(),name);
	}
	cout << "--- Delete: " << name[0] << " ---"<< endl;
}

void p_rm(){
	string dir = direccionActual + contenido.substr(contador+1,contenido.size());
	char* name[] = {(char*) dir.c_str(), (char*)0};

	if (!fork()) {
		string exe = CDIR;
		exe += "/rm";
		execv(exe.c_str(),name);
	}
}

void p_ln(){
	string dir = direccionActual.substr(6,contenido.size());
	char* name[] = {(char*) dir.c_str(), (char*)0};

	if (!fork()) {
		string exe = CDIR;
		exe += "/ln";
		execv(exe.c_str(),name);
	}
}

void p_uname(){
	struct utsname sysinfo;
                uname(&sysinfo);
                cout << sysinfo.sysname<<endl;
}

void p_kill(){
	string procName = contenido.substr(8,contenido.size());
                char* todo[] = {(char*) procName.c_str(), (char*)0};
                
                if (!fork()) {
                    string exe = CDIR;
                    exe += "/kill";
                    execv(exe.c_str(),todo);
                }
}

void coman(){
	cout << "Lista de comandos existentes: " << endl;
	for (int i = 0; i < comandos.size(); ++i)
	{
		cout << "*********\t"<< comandos[i] <<"\t ********"<< endl;
	}
}