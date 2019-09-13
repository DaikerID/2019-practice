#pragma once

#include "Page.h"
#include <vector>
using namespace std;

class VirtualMem
{
	vector<Page> vir_mem;
public:
	//iNum - �������� �������� ������� ����������� ������
	void add_new_page(int RW, int num);//���������� ����� �������� � ��
	bool is_page_exists_in_vm(int num_of_page);//�������� �� ������� ��������� � ��
	bool is_page_exists_in_phm(int num_of_page);//-\\-\\- ���� ����� ��� � ��
	void set_command(int num_of_page, int RW);//��������� ����� �������
	void set_framenum_by_num(int num_of_page, int n);//��������� ������ ������ ������� �� �� ������ ��������
	void set_framenum_by_iNum(int iNum, int n);//-\\-\\-\\ �� ���������
	int get_frame_num(int num_of_page);//����� ������ �� ������ ��������
	int get_iNum(int num_of_page);//�������� �������� ��������
	int get_num(int iNum);//�������� ����� �� ���������
	void discharge_read_bit();//��������� ����� ������ � ���� �������
	void set_read_bit(int iNum, int bit);//���������� ��� R �� ���������
	int get_read_bit(int iNum);//�������� ��� R �� ���������
	void set_write_bit(int iNum, int bit);//���������� ��� M �� ���������
	int get_write_bit(int iNum);//�������� ��� M �� ���������
	void set_age(int iNum, int new_age);//���������� ����� �������� �������� �� ���������
	void age_plus(int iNum);// ��������� �������, �� ���������
	void age_plus();//��������� ������� � ���� �������
	int get_age(int iNum);//�������� �������
	void set_pageout(int iNum, int out);//���������� ��� S
	int get_pageout(int iNum);//�������� ��� S
	void set_in_vec();//�������� ����� �������� ���� R � ��� ��������, ��� ������ ��������
	int get_count_read(int iNum);//�������� ���������� ��������� � ��������
	void set_outed(int iNum, int out);//���������� ��� out
	int get_outed(int iNum);//�������� ��� out
	int get_swapout(int iNum);//�������� ��� swap_out 
	int size();//������� ����� ��
	
};

