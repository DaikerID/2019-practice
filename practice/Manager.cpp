#include "Manager.h"
int Manager::set_options(string alg, string options, string num_frames) {
    out.open("output.txt");
	tact = 0;
    if (!out)
    {
        cout<<"ERROR! Output file does not opened!";
        return -1;
    }

    if (alg!="default")
        Algorithm = alg;
    else
        Algorithm = "C";// по дфолту используется алгоритм часы
    if (options != "default")
    {
		for (int i = 0; i < options.size(); i++)//устанавливаем опции вывода
		{
			if (options[i] == 'O')
				optO = true;
			if (options[i] == 'P')
				optP = true;
			if (options[i] == 'F')
				optF = true;
			if (options[i] == 'S')
				optS = true;
			if (options[i] == 'p')
				opt_p = true;
			if (options[i] == 'f')
				opt_f = true;
		}
    }
    if (num_frames != "default")
        Size_of_Phys_Mem = stoi(num_frames);
    else Size_of_Phys_Mem = 32;
    return 0;
}

int Manager::set_command(int RW, int num) {
    out << "==> inst: "<< RW <<" "<<num<<"\n";
	cout << "==> inst: " << RW << " " << num << "\n";
	add_new_page(RW, num);
	if (opt_p)//вывод на основе опций
		P_out();
	if (opt_f)
		F_out();
    tact++;
    return 0;
}

int Manager::exit() {
	if (optP && !opt_p)//вывод на основе опций
		P_out();
	if (optF && !opt_f)
		F_out();
	if (optS)
		S_out();
    out.close();
    return 0;
}

void Manager::add_new_page(int RW, int Num)
{
	// если используется алгоритм LRU то на каждом десятом такте записывается значение бита R каждой страницы в дек внутри страницы
	// удаляется самое первое добавленное значение
	// да,я не знаю как это лучше сформулировать
	if (tact % 10 == 0 && (Algorithm =="L" || Algorithm == "l"))
		virtual_mem.set_in_vec();

	virtual_mem.age_plus();// прибавляем значение возраста у каждой страницы
	
						   
	//если стрвницы нет в виртуальной памяти
    if (!virtual_mem.is_page_exists_in_vm(Num) && virtual_mem.size()<Size_of_Vir_Nem)
    {
        //добавляем в виртуальную память
        virtual_mem.add_new_page(RW,Num);
		// добавляем в физическую
		virtual_mem.set_framenum_by_num(Num, add_page_in_phys_mem(Num, false));
    }
    else //если страница есть в виртуальной памяти
    {
        virtual_mem.set_command(Num,RW);// устанавливаем соответствующую команду
		// и добавляем в физическую память
		virtual_mem.set_framenum_by_num(Num, add_page_in_phys_mem(Num,true));
    }

}

int Manager::add_page_in_phys_mem(int Num, bool itwasinvm)
{
	if (tact == 101)
		cout << "ghj" << endl;
	int frame_num = -1;
    //проверка на наличие в физической памяти
    if (virtual_mem.is_page_exists_in_phm(Num))
    {
        frame_num = virtual_mem.get_frame_num(Num);
        return frame_num;
    }
    else //если в страницы нету в физической памяти
    {
        if (phys_mem.size() < Size_of_Phys_Mem)//если физическая память не заполнена
        {
            frame_num = phys_mem.size(); //запоминаем новый фрейм
            phys_mem.push_back(virtual_mem.get_iNum(Num)); // и добавляем туда итератор страницы в виртуальной памяти
			if (optO)
			{
				out << tact << ": ZERO   " << frame_num << "\n";
				out << tact << ": MAP " << Num << " " << frame_num << "\n";
			}
			cout << tact << ": ZERO   " << frame_num << "\n";
			cout << tact << ": MAP " << Num << " " << frame_num << "\n";
			// прибавляю счетчики операций
			zero++;
			map++;
            return frame_num;
        }
        else
        {        
			//обратите внимание что обнуление битов R внутри страниц происходит только у некоторых алгоритмов,
			// поскольку методичка требовала это делать только для алгоритма NRU,
			// обнуление происходит при каждой 10-й ошибке замещения страниц
			if (Algorithm == "C" || Algorithm == "c") //Clock
                frame_num= clock_alg();
            else if (Algorithm == "R" || Algorithm == "r")//random
                frame_num = random_alg();
            else if (Algorithm == "F" || Algorithm == "f")//FIFO
                frame_num = FIFO_alg();        
			
            else if (Algorithm == "S" || Algorithm == "s")//Second chance
				frame_num = second_chance_alg();            
			else if (Algorithm == "N" || Algorithm == "n")//NRU
			{
				if (discharge % 10 == 0)					// при каждой 10м возникновении ошибки заммещения страниц сбрасываем биты чтения у всех страниц
					virtual_mem.discharge_read_bit();	
				else
					discharge++;

				frame_num = NRU_alg();
			}
			else if (Algorithm == "W" || Algorithm == "w")// Рабочий набор
			{
				if (discharge % 10 == 0)// при каждой 10м возникновении ошибки заммещения страниц сбрасываем биты чтения у всех страниц
					virtual_mem.discharge_read_bit();
				else
					discharge++;

				frame_num = work_kit_alg();
			}
			else if (Algorithm == "Ws" || Algorithm == "ws")//WSClock
			{
				if (discharge % 10 == 0)// при каждой 10м возникновении ошибки заммещения страниц сбрасываем биты чтения у всех страниц
					virtual_mem.discharge_read_bit();
				else
					discharge++;

				frame_num = WSClock_alg();
			}
			else if (Algorithm == "L" || Algorithm == "l")//LRU
			{
				if (discharge % 10 == 0)// при каждой 10м возникновении ошибки заммещения страниц сбрасываем биты чтения у всех страниц
					virtual_mem.discharge_read_bit();
				else
					discharge++;
				frame_num = LRU_alg();
			}

            
			if (optO)//вывод в соответствии с опциями
				out << tact << ": UNMAP " << virtual_mem.get_num(phys_mem[frame_num]) << " " << frame_num << "\n";
			cout << tact << ": UNMAP " << virtual_mem.get_num(phys_mem[frame_num]) << " " << frame_num << "\n";
			unmap++;
			
			if (virtual_mem.get_write_bit(phys_mem[frame_num]) == 1)// если страница была модифицирована
			{
				if (optO)
					out << tact << ": OUT " << virtual_mem.get_num(phys_mem[frame_num]) << " " << frame_num << "\n";
				cout << tact << ": OUT " << virtual_mem.get_num(phys_mem[frame_num]) << " " << frame_num << "\n";
				pageouts++;
			}
				
			//именно в этом моменте решается что выводить ZERO или IN, но я так и не разобрался в логике
			if (itwasinvm && virtual_mem.get_write_bit(phys_mem[frame_num]) == 1)
			{
				if (optO)				
					out << tact << ": IN " << Num << " " << frame_num << "\n";			
				cout << tact << ": IN " << Num << " " << frame_num << "\n";
				pageins++;
			}	
			else
			{
				if (optO)
					out <<	tact << ": ZERO    " << frame_num << "\n";
				cout << tact << ": ZERO    " << frame_num << "\n";
				zero++;
			}
			//устанавливаем соответствующие биты, если страница была модифицирована то мы ее выгружаем
			if (virtual_mem.get_write_bit(phys_mem[frame_num]) == 1)
			{
				// ставим бит, указыввающий что в данный момент страница выгружена
				virtual_mem.set_outed(phys_mem[frame_num], 1); // тоже не очень соответствует выводу в образце, с опцией P
				virtual_mem.set_pageout(phys_mem[frame_num], 1); // ставим бит S в единицу
			}
				
				
			if (optO)
				out << tact << ": MAP " << Num << " " << frame_num << "\n";
			cout << tact << ": MAP " << Num << " " << frame_num << "\n";
			map++;
		
			//ставим номер фрейма странцы в физической памяти в виртуальную
			virtual_mem.set_framenum_by_iNum(phys_mem[frame_num],-1);
			//ставим итератор новой только что добавленной страницы
			phys_mem[frame_num] = virtual_mem.get_iNum(Num);
        }
    }
    return frame_num;
}

int Manager::clock_alg() //алгоритм часы
{	
    int i = hand; // получаем текщее значениие стрелки
    hand++;// повышаем значение стрелки
	if (i == phys_mem.size())// если текущее значении равно размеру вектора физ. памяти, обнуляем его(вроде как лишняя проверка)
		i = 0;
	if (hand == phys_mem.size())// если следующее значение стрелки -//-//-//
		hand = 0;
    while (virtual_mem.get_read_bit(phys_mem[i]) == 1)// проверяем бит чтения рассматриваемой страницы равен единицы
    {
        virtual_mem.set_read_bit(phys_mem[i],0); // обнуляем бит чтения, и переводим стрелку на следующую страницу
        i++;
        hand++;
        if (hand == phys_mem.size())
            hand = 0;
        if (i == phys_mem.size())
            i = 0;
    }
	
    return i;
}

int Manager::random_alg()//алгоритм рандома
{
    //srand( time( 0 ) );// это использовать не нужно
    int random_number = rand() % phys_mem.size();// не знаю нужно ли было делать проверку на чтение
	// в алгоритме рабочего набора если все страницы относятся к раб. набору. то мы выбираем случайным образом
	// страницу, предпочтительнее не измененную
	// возможно здесь нужно сделать так же, я не уверен
    return random_number;
}

int Manager::FIFO_alg() //алгоритм FIFO
{
    int max_age = 0, ind = -1;
    for (int i = 0; i < phys_mem.size(); i++)
		if (virtual_mem.get_age(phys_mem[i]) >= max_age)// просто проверяем если возраст рассматриваеой страницы больше чем найденный максимальный возраст до этого, то на замещение планируется именно эта страница
		{
			ind = i;
			max_age = virtual_mem.get_age(phys_mem[i]); // запоминаем максимальный возраст
		}
            
    return ind;
}

int Manager::second_chance_alg() //алгоритм второй шанс
{
    int max_age = 0, ind = 0;
	while (true)
	{
		for (int i = 0; i < phys_mem.size(); i++)
			if (virtual_mem.get_age(phys_mem[i]) > max_age)// так же как и в фифо проверем возраст и запоминаем если он максимальный из раннее рассматриваемых
			{
				ind = i;
				max_age = virtual_mem.get_age(phys_mem[i]);
			}
		if (virtual_mem.get_read_bit(phys_mem[ind]) == 1)// второй шанс, смотрим бит R
		{
			virtual_mem.set_read_bit(phys_mem[ind], 0); //если он равен 1, то мы обнуляем его
			virtual_mem.set_age(phys_mem[ind], 0);//, а так же обнуляем возраст рассматриваемой страницы 
			max_age = 0;
		}
		else
			return ind;//иначе страница подходит для замещения
	}
    return ind;
}

int Manager::NRU_alg()// Алгоритм исключения недавно используемой страницы
{
	int frame_num = -1;
	vector<int> class_zero, class_one, class_two, class_three;//векторы классов
	//в них хранятся итераторы страниц соответствующих этим классам
	for (int i = 0; i < phys_mem.size(); i++)//распределяем страницы по классам
	{
		int read = virtual_mem.get_read_bit(phys_mem[i]);
		int write = virtual_mem.get_write_bit(phys_mem[i]);
		
		if (read == 0 && write == 0)
			class_zero.push_back(i);
		else if (read == 0 && write == 1)
			class_one.push_back(i);
		else if (read == 1 && write == 0)
			class_two.push_back(i);
		else
			class_three.push_back(i);
	}

	int ind = -1;//проверяем на наличие переменных от самого низкого класа, к самому высокому, и рандомно выбираем страницу
	if (class_zero.size() > 0)
	{
		ind = rand() % class_zero.size();
		frame_num = class_zero[ind];
	}		
	else if (class_one.size() > 0)
	{
		ind = rand() % class_one.size();
		frame_num = class_one[ind];
	}		
	else if (class_two.size() > 0)
	{
		ind = rand() % class_two.size();
		frame_num = class_two[ind];
	}		
	else
	{
		ind = rand() % class_three.size();
		frame_num = class_three[ind];
	}

	return frame_num;
}

int Manager::work_kit_alg()
{
	int frame_num = -1, read, age, t= 10;// t - предполагаемо число тактов, за который набирается рабочий наборе
	//TODO я так понимаю это лучше указать в методе
	
	int frame_num_in_work_kit = -1, //номер фрейма самой старой страницы из рабочего набора, если вдруг не найдетс подходящая страница вне его
		max_age_in_work_kit = 0, max_age = 0;//максимальное значение возраста внутри РН, и вне его 
	for (int i = 0; i < phys_mem.size(); i++)
	{
		read = virtual_mem.get_read_bit(phys_mem[i]);
		age = virtual_mem.get_age(phys_mem[i]);

		if (read == 1)
			virtual_mem.set_age(phys_mem[i], 0);//Если его значение
			//равно 1, текущее виртуальное время записывается в поле времени последнего  
			//использования таблицы страниц, показывая, что страница была использована  
			//при возникновении ошибки отсутствия страницы.(просто обнуляю возраст страницы,
			//не было смысла создавать еще одну переменную)
		else if (read == 0 && age <= t && age > max_age_in_work_kit)
		{
			frame_num_in_work_kit = i;
			max_age_in_work_kit = age;
		}	//Но если значение R равно 0, но возраст меньше или равен t, то страница все еще от -
			//носится к рабочему набору.Страница временно избегает удаления, но страница с наи -
			//большим возрастом(наименьшим значением времени последнего использования)
			//берется на заметку.
		else if (read == 0 && age > t && age > max_age)
		{
			frame_num = i;
			max_age = age;
		}
		//если страница вне рабочего набора, с максимальным возрастом, то она рассматривается на замещение
	}
	if (frame_num != -1) //если есть страница не из рабочего набора с больщим числом
		return frame_num;
	else if (frame_num_in_work_kit != -1)// если есть стрница в рабочем наборе с наибольшим возрастом и битом чтения равным 0
		return frame_num_in_work_kit;
	else //  в этот блок мы попадаем только в том случае есле все страницы будут (типа) принадлежать рабочему набору 
	{
		// такой вариант будет при возникновении первой ошибка замещения страниц
		// так как мы обнуляем биты R только при каждой десятой ошибке замещения страниц, как это написано
		// в англоязычной методичке

		// кстати вот этот блок можно вставить в алгоритм рандома
		frame_num = rand() % phys_mem.size();// выбираем рандомную страницу
		for (int i = 0; i < phys_mem.size(); i++)// предпочтительно не измененнную
		{
			//количество попытк найти неизмененную страницу равно размеру физ. памяти, если не найдем,
			//то выберем последнюю выпавшую, бедолагу
			if (virtual_mem.get_write_bit(phys_mem[frame_num]) == 1)
				frame_num = rand() % phys_mem.size();
			else return frame_num;
		}
	}
	return frame_num;
}

int Manager::WSClock_alg()
{
	int frame_num = -1, read, age, write, t = 10;//тоже должно указываться в методе
	int first_hand = hand, // запоминаю положение стрелки при входе в алгоритм
		i = hand;
	hand++;
	if (i == phys_mem.size())
		i = 0;
	if (hand == phys_mem.size())
		hand = 0;
	vector <int> plan_for_out; // вектор в который вносятся индексы страниц из физ памяти, которые планируется выгрузить
	// если я правильно понял то что написал про это Таненбаум
	while (true)
	{		
		read = virtual_mem.get_read_bit(phys_mem[i]);
		age = virtual_mem.get_age(phys_mem[i]);
		write = virtual_mem.get_write_bit(phys_mem[i]);
		
		if (read == 0 && age > t && write == 0)//если страница не принадлежит рабочему набору и не модернизирована
			return i;// то сразу выгружаем
		else if (read == 0 && age > t && write == 1)//-||-||- и модернизирована добавляем в план для выгрузки
			plan_for_out.push_back(i);
		else if (read == 1)// если принадлежит рабочему набору то обнуляем бит R
			virtual_mem.set_read_bit(phys_mem[i], 0);
		//else if (read == 0 && age =< t )// этот момент у Таненбаума не прописан, но я так понимаю, это и не нужно
		

		i++;
		hand++;
		if (hand == phys_mem.size())
			hand = 0;
		if (i == phys_mem.size())
			i = 0;
		if (i == first_hand)// если мы прошли полный оборот
			break;
	}
	if (plan_for_out.size() > 0)//если запланировали на выгрузку, предполагаем что все они выгружены
	{
		// тогда пробегаем полный оборот стрелки, в поиске уже выгруженной страницы
		for (int ind = 0; ind < plan_for_out.size(); ind++)
			if (plan_for_out[ind] == i)// если в плане присутствует фрейм на который указывает стрелка
				return i;
		i++;
		hand++;
		if (hand == phys_mem.size())
			hand = 0;
		if (i == phys_mem.size())
			i = 0;
		while (i != first_hand)
		{
			for (int ind = 0; ind < plan_for_out.size(); ind++)
				if (plan_for_out[ind] == i)// если в плане присутствует фрейм на который указывает стрелка
					return i;
			i++;
			hand++;
			if (hand == phys_mem.size())
				hand = 0;
			if (i == phys_mem.size())
				i = 0;
		}
	}
	else // иначе выгружаем любую первую попавшуюся неизмененную страницу
	{
		if (virtual_mem.get_write_bit(phys_mem[i]) == 0)
			return i;
		else
		{
			i++;
			hand++;
			if (hand == phys_mem.size())
				hand = 0;
			if (i == phys_mem.size())
				i = 0;
			while (i != first_hand)
			{
				if (virtual_mem.get_write_bit(phys_mem[i]) == 0)
					return i;
				i++;
				hand++;
				if (hand == phys_mem.size())
					hand = 0;
				if (i == phys_mem.size())
					i = 0;
			}
		}
	}
	return i;// если таковых нет просто сбрасываем текущую
}

int Manager::LRU_alg()//Алгоритм замещения наименее вострабованной страницы
{
	int frame_num = -1;
	int age, count, max_age = -1, min_count = 11;
	vector<int>for_del;
	for (int i = 0; i < phys_mem.size(); i++)// получаем значение максимального возраста
	{
		age = virtual_mem.get_age(phys_mem[i]) / 10;//для имитации алгоритмаа LRU возраст делится на 10
		// поскольку в реальности может воникнуть ситуация, когда мы не знаем к какой странице обращались раньше в определенном такте
		if (age > max_age)
		{
			max_age = age;
		}			
	}
	for (int i = 0; i < phys_mem.size(); i++)// помечаем страницы возраст которых равен максимальному
	{
		age = virtual_mem.get_age(phys_mem[i]) / 10;
		if (age == max_age)
			for_del.push_back(i);		
	}
	for (int i = 0; i < for_del.size(); i++)// выбираем страницу к которой было меньше всего обращений за последние 100 тактов
	{
		count = virtual_mem.get_count_read(phys_mem[for_del[i]]);
		if (count < min_count)
			frame_num = i;
	}
	return frame_num;
}

void Manager::P_out()// вывод опции Р
{
	int ind;
	for (int i = 0; i < Size_of_Vir_Nem; i++)
	{
		ind = virtual_mem.get_iNum(i);
		if (ind == -1) // Если страница номер i есть в вртуальной памяти
		{
			out << "* ";
			cout << "* ";
		}
			
		else if (virtual_mem.get_outed(ind) == 1) // если она была выгружена(некорректно что-то из того работает)
		{
			out << "# ";
			cout << "# ";
		}
			
		else // иначе выводим биты
		{
			out << i << ":";
			cout << i << ":";
			if (virtual_mem.get_read_bit(ind) == 1)
			{
				out << "R";
				cout << "R";
			}
				
			else
			{
				out << "-";
				cout << "-";
			}
			if (virtual_mem.get_write_bit(ind) == 1)
			{
				out << "M";
				cout << "M";
			}
				
			else 
			{
				out << "-";
				cout << "-";
			}
			if (virtual_mem.get_swapout(ind) == 1)
			{
				out << "S ";
				cout << "S ";
			}
				
			else
			{
				out << "- ";
				cout << "- ";
			}

		}
	}
	cout << "\n";
	out << "\n";
}

void Manager::F_out()
{
	for (int i = 0; i < Size_of_Phys_Mem; i++)
	{
		if (i >= phys_mem.size())
		{
			out << "* ";
			cout << "* ";
		}
			
		else
		{
			out << virtual_mem.get_num(phys_mem[i]) << " ";
			cout << virtual_mem.get_num(phys_mem[i]) << " ";
		}
			
	}
	out << "\n";
	cout << "\n";
}

void Manager::S_out()
{
	int sum = unmap + map + pageins + pageouts + zero;
	out << "SUM " << tact << " U=" << unmap << " M=" << map << " I=" << pageins << " O=" << pageouts << " Z=" << zero << " ===> " << sum << "\n";
	cout << "SUM " << tact << " U=" << unmap << " M=" << map << " I=" << pageins << " O=" << pageouts << " Z=" << zero << " ===> " << sum << "\n";
}

