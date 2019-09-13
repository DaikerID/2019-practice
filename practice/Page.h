//
// Created by igor on 05.09.2019.
//

#ifndef UNTITLED1_PAGE_H
#define UNTITLED1_PAGE_H

#include <vector>
#include <deque>
using namespace std;

class Page {
    int num;//номер
    int read;//бит R
    int write;//бит M(да, мне лень его было переиминовывать в modifite)
	int frame_num = -1;//номер фрейма в физ памяти, если в физпамяти страницы нет, равен -1
    int age = 0;//возраст, прибавляется каждый такт,независимо от того есть ли он в ФП или нет, обнуляется при получении новой команды
	int swap_out = 0;//бит S
	int outed;//бит который показывает что страница на данный момент выгружена (вывод  # вместо *, но я не уверен что правильно его использую, так как вывод не всегда совпадает)
	deque <int> read_vec;// дек в котором хранятся значения бита R для алгоритма LRU при поступлении нового значения в начало, последнее удаляется
	int size = 10;// размер дека
public:

    Page(int n, int comm);
    Page();
    int get_num();
    int get_write_bit();
    void set_write_bit(int i);
    int get_read_bit();
    void set_read_bit(int i);
    void age_plus();
    int get_age();
    void set_age(int n);
	void set_pagedout(int n);
	int get_swapout();
    void set_command(int comm);
    Page & operator=(const Page &NewPage);
	void set_in_vec();
	int get_count_in_vec();
	void set_outed(int n);
	int get_outed();
	int get_frame_num();
	void set_frame_num(int n);
};


#endif //UNTITLED1_PAGE_H
