#include <iostream>
#include "Input.h"
#include <string>

using namespace std;
// образец вызова из терминала
//./mmu [-a<algo>] [-o<options>] [–f<num_frames>] inputfile [ randomfile ]
//-aC -f32 -oOPFS in1K4
string get_argv(char argv[])//функция получения аргумента
{
    string arg = "", args = "";
    args = string(argv);
    int i = 2;
    while  (i < args.size())
    {
        arg  += args[i];
        i++;
    }

    return arg;
}

string get_option(char argv[])//фонкция получения имени опции
{
    string opt = "", args = "";
    args = string(argv);
    for (int i=0; i < 2 && i < args.size(); i++)
        opt  += args[i];
    return opt;
}

int main(int argc, char* argv[]) {
	if (argc < 2) //проверка на наличие хотя бы 1-го аргумента
	{
		cout << "ERROR! Not enouth arguments!" << endl;
		return -1;
	}
       

    string opt, alg = "default", options = "default", infile, num_frames = "default";
    //какие-бы аргументы не были введены, последним агрументом обязательно должно быть имя входного файла
    for (int i = 1; i< argc; i++)
    {
        opt = get_option(argv[i]);
        if (opt == "-a" || opt == "-A")
            alg = get_argv(argv[i]);
        else if (opt == "-o" || opt == "-O")
            options = get_argv(argv[i]);
        else if (opt == "-f" || opt == "-F")
            num_frames = get_argv(argv[i]);
        else if (i == argc-1)
            infile = string (argv[i]);
    }
    Input input(alg, options, num_frames, infile);
	if (input.go() == -1)
		return -1;
    return 0;
}