//
// Created by igor on 05.09.2019.
//

#ifndef UNTITLED1_PAGE_H
#define UNTITLED1_PAGE_H

#include <vector>
#include <deque>
using namespace std;

class Page {
    int num;//�����
    int read;//��� R
    int write;//��� M(��, ��� ���� ��� ���� ��������������� � modifite)
	int frame_num = -1;//����� ������ � ��� ������, ���� � ��������� �������� ���, ����� -1
    int age = 0;//�������, ������������ ������ ����,���������� �� ���� ���� �� �� � �� ��� ���, ���������� ��� ��������� ����� �������
	int swap_out = 0;//��� S
	int outed;//��� ������� ���������� ��� �������� �� ������ ������ ��������� (�����  # ������ *, �� � �� ������ ��� ��������� ��� ���������, ��� ��� ����� �� ������ ���������)
	deque <int> read_vec;// ��� � ������� �������� �������� ���� R ��� ��������� LRU ��� ����������� ������ �������� � ������, ��������� ���������
	int size = 10;// ������ ����
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
