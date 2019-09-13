//
// Created by igor on 01.09.2019.
//

#include "Input.h"


Input::Input(string alg, string options, string num_frames, string inFile)
{
    filename = inFile;
    manager.set_options(alg,options,num_frames);
}
//процесс забора информации из файла и ее обработки
int Input::go()
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout<<"ERROR! File does not exist!"<<endl;
        return -1;
    }
    else
    {
        string str, rw_str = "", num_str = "";
        int rw, num;

        while (!file.eof())
        {
            getline(file,str);

            if (str[0] != '#' && str!="")
            {
                rw_str=str[0];
                for(int i = 2; i<str.size();i++)
                    num_str +=str[i];

                rw = stoi(rw_str);
                num = stoi(num_str);
								
                manager.set_command(rw,num);
                num_str = "";
                str = "";
            }
        }
        manager.exit();
        file.close();
    }
    return 0;
}
