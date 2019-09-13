//
// Created by igor on 03.09.2019.
//

#ifndef UNTITLED1_MANAGER_H
#define UNTITLED1_MANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include "Page.h"
#include "VirtualMem.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

class Manager {

    ofstream out;

    string Algorithm;// Опция для алгоритма
	bool optO = false, optP = false, optF = false, optS = false, opt_p = false, opt_f = false;// опции для вывода
    int Size_of_Phys_Mem,/*количество страничных блоков физической памяти*/
            Size_of_Vir_Nem = 64, hand = 0/*стрелка для алгоритма часы*/,
            discharge = 0; //счетчик для сброса битов R при каждой 10й ошибке замещения страниц
    int tact; //счетчик команд
	int unmap, map, pageins, pageouts, zero;//счетчики операций
    VirtualMem virtual_mem;//виртуальная память
    vector <int> phys_mem; //физическая память, в ней хранится итератор страницы в виртуальной памяти


    void add_new_page(int RW, int Num);//добавленияе новой страницы в виртуальную память
    int add_page_in_phys_mem(int Num,bool itwasinvm);//добавление страницы в физическую, работа с алгоритмами тут
	//itwasinmv - бит подтверждающий была ли страница до этов в виртуальной памяти 
	// на самом деле с ним вывод тоже не соответствует файлу out_in1K4_c_32_OPFS, разлчается количестов операция IN и ZERO


	//помните, здесь было много методов?
	//так вот теперь тут их нет
	//они в VirtualMem
	// не благодарите
	//для протокола: была проведена оптимизация кода


    //Алгоритмы
    int clock_alg();// часы
    int random_alg();// случайный
    int FIFO_alg();// первый пришел, первый вышел
    int second_chance_alg();// Второй шанс
	int NRU_alg();// Исключение недавно используемой страницы
	int work_kit_alg();// Рабочий набор
	int WSClock_alg();// WSClock (Микс часов и рабочего набора)
	int LRU_alg();//замещения наименее вострабованной страницы

	//выводы на основе опций
	void P_out();
	void F_out();
	void S_out();
public:
    int set_options(string alg, string options, string num_frames);//установка опций
    int set_command(int RW, int num);//обработка команды
    int exit();// завершение работы
};


#endif //UNTITLED1_MANAGER_H
