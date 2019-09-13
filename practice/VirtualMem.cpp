#include "VirtualMem.h"

void VirtualMem::add_new_page(int RW, int num)
{
	vir_mem.emplace_back(num, RW);
}

bool VirtualMem::is_page_exists_in_vm(int num_of_page)
{
	for (int i = 0; i < vir_mem.size(); i++)
		if (vir_mem[i].get_num() == num_of_page)
			return true;
	return false;
}

bool VirtualMem::is_page_exists_in_phm(int num_of_page)
{
	for (int i = 0; i < vir_mem.size(); i++)
		if (vir_mem[i].get_num() == num_of_page && vir_mem[i].get_frame_num() != -1)
			return true;
	return false;
}

void VirtualMem::set_command(int num_of_page, int RW)
{
	for (int i = 0; i < vir_mem.size(); i++)
		if (vir_mem[i].get_num() == num_of_page)
			vir_mem[i].set_command(RW);
}

void VirtualMem::set_framenum_by_num(int num_of_page, int n)
{
	for (int i = 0; i < vir_mem.size(); i++)
		if (vir_mem[i].get_num() == num_of_page)
			vir_mem[i].set_frame_num(n);
}

void VirtualMem::set_framenum_by_iNum(int iNum, int n)
{
	vir_mem[iNum].set_frame_num(n);
}

void VirtualMem::discharge_read_bit()
{
	for (int i = 0; i < vir_mem.size(); i++)
		vir_mem[i].set_read_bit(0);
}

void VirtualMem::set_read_bit(int iNum, int bit)
{
	vir_mem[iNum].set_read_bit(bit);
}

int VirtualMem::get_read_bit(int iNum)
{
	return vir_mem[iNum].get_read_bit();
}

void VirtualMem::set_write_bit(int iNum, int bit)
{
	vir_mem[iNum].set_write_bit(bit);
}

int VirtualMem::get_write_bit(int iNum)
{
	return vir_mem[iNum].get_write_bit();
}

void VirtualMem::set_age(int iNum, int new_age)
{
	vir_mem[iNum].set_age(new_age);
}

void VirtualMem::age_plus(int iNum)
{
	vir_mem[iNum].age_plus();
}

void VirtualMem::age_plus()
{
	for (int i = 0; i < vir_mem.size(); i++)
		vir_mem[i].age_plus();
}

int VirtualMem::get_age(int iNum)
{
	return vir_mem[iNum].get_age();
}

void VirtualMem::set_pageout(int iNum, int out)
{
	vir_mem[iNum].set_pagedout(out);
}

int VirtualMem::get_pageout(int iNum)
{
	return vir_mem[iNum].get_swapout();
}

void VirtualMem::set_in_vec()
{
	for (int i = 0; i < vir_mem.size(); i++)
		vir_mem[i].set_in_vec();
}

int VirtualMem::get_count_read(int iNum)
{
	return vir_mem[iNum].get_count_in_vec();
}

void VirtualMem::set_outed(int iNum, int out)
{
	vir_mem[iNum].set_outed(out);
}

int VirtualMem::get_outed(int iNum)
{
	return vir_mem[iNum].get_outed();
}

int VirtualMem::get_swapout(int iNum)
{
	return vir_mem[iNum].get_swapout();
}

int VirtualMem::size()
{
	return vir_mem.size();
}

int VirtualMem::get_frame_num(int num_of_page)
{
	for (int i = 0; i < vir_mem.size(); i++)
		if (vir_mem[i].get_num() == num_of_page)
			return vir_mem[i].get_frame_num();
	return -1;
}

int VirtualMem::get_iNum(int num_of_page)
{
	for (int i = 0; i < vir_mem.size(); i++)
		if (vir_mem[i].get_num() == num_of_page)
			return i;
	return -1;
}

int VirtualMem::get_num(int iNum)
{
	return vir_mem[iNum].get_num();
}
