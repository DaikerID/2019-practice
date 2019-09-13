//
// Created by igor on 05.09.2019.
//

#include "Page.h"

Page::Page(int n, int comm) {
    num = n;
    read = 1;
	outed = 0;
	if (comm == 1)
	{
		write = 1;
	}
	
    else write = 0;
	for (int i = 0; i < size; i++)
	{
		read_vec.push_back(0);
	}

}

int Page::get_num() {
    return num;
}

int Page::get_write_bit() {
    return write;
}

void Page::set_read_bit(int i) {
    read = i;
}

void Page::set_write_bit(int i) {
    write = i;
}

int Page::get_read_bit() {
    return read;
}

void Page::age_plus() {
    age++;
}

int Page::get_age() {
    return age;
}

void Page::set_age(int n) {
    age = n;
}

void Page::set_pagedout(int n)
{
	swap_out = n;
	if (swap_out == 1)
		write = 0;
}

int Page::get_swapout()
{
	return swap_out;
}

void Page::set_command(int comm)
{
    read = 1;
	if (comm == 1)
	{
		write = 1;
	}
	outed = 0;
	age = 0;
}

Page &Page::operator=(const Page &NewPage)
{
    this->age = NewPage.age;
    this->write = NewPage.write;
    this->num = NewPage.num;
    this->read = NewPage.read;
    return *this;
}

void Page::set_in_vec()
{
	read_vec.push_front(read);
	read_vec.erase(read_vec.end()-1);
}

int Page::get_count_in_vec()
{
	int count = 0;
	for (int i = 0; i < read_vec.size(); i++)
	{
		if (read_vec[i] == 1)
			count++;
	}
	return count;
}

void Page::set_outed(int n)
{
	outed = n;
	if (outed == 1)
		write = 0;
}

int Page::get_outed()
{
	return outed;
}

int Page::get_frame_num()
{
	return frame_num;
}

void Page::set_frame_num(int n)
{
	frame_num = n;
}

Page::Page() {
    age = 0;
    write = 0;
    num = -1;
    read = 0;
	outed = 0;
	for (int i = 0; i < size; i++)
		read_vec.push_back(0);
}

