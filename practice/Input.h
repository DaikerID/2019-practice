//
// Created by igor on 01.09.2019.
//

#ifndef UNTITLED1_INPUT_H
#define UNTITLED1_INPUT_H


#include "Manager.h"

using namespace std;
class Input {
    Manager manager;//класс менеджера памяти
    string filename;// имя входного файла
public:
    Input (string alg, string options, string num_frames, string inFile);
    int go();//метод внутри которого забираются данные из файла и передаются в менеджер памяти
};


#endif //UNTITLED1_INPUT_H
