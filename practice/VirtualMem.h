#pragma once

#include "Page.h"
#include <vector>
using namespace std;

class VirtualMem
{
	vector<Page> vir_mem;
public:
	//iNum - итератор страницы внуттри виртуальной памяти
	void add_new_page(int RW, int num);//добавление новой страницы в вм
	bool is_page_exists_in_vm(int num_of_page);//проверка на наличие страрницы в ВП
	bool is_page_exists_in_phm(int num_of_page);//-\\-\\- тоже самое ток в ФП
	void set_command(int num_of_page, int RW);//установка новой команды
	void set_framenum_by_num(int num_of_page, int n);//установка нового номера фреймав ФП по номеру страницы
	void set_framenum_by_iNum(int iNum, int n);//-\\-\\-\\ по итератору
	int get_frame_num(int num_of_page);//номер фрейма по номеру страницы
	int get_iNum(int num_of_page);//получить итератор страницы
	int get_num(int iNum);//получить номер по итератору
	void discharge_read_bit();//обнуление битов чтения у всех страниц
	void set_read_bit(int iNum, int bit);//установить бит R по итератору
	int get_read_bit(int iNum);//получить бит R по итератору
	void set_write_bit(int iNum, int bit);//установить бит M по итератору
	int get_write_bit(int iNum);//получить бит M по итератору
	void set_age(int iNum, int new_age);//установить новое значение возраста по итератору
	void age_plus(int iNum);// прибавить возраст, по итератору
	void age_plus();//прибавить возраст у всех страниц
	int get_age(int iNum);//получить возраст
	void set_pageout(int iNum, int out);//установить бит S
	int get_pageout(int iNum);//получить бит S
	void set_in_vec();//записать новое значения бита R в дек страницы, для каждой страницы
	int get_count_read(int iNum);//получить количество обращений к странице
	void set_outed(int iNum, int out);//установить бит out
	int get_outed(int iNum);//получить бит out
	int get_swapout(int iNum);//получить бит swap_out 
	int size();//текущий размр ВП
	
};

