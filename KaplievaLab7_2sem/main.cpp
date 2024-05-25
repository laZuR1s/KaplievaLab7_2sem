#include "Flist.h"
#include <fstream>
#include<functional>
#include<Windows.h>

void task(FLIST& flist,std::ifstream& input, std::ostream& output);
bool findOddFragment(FLIST& flist, ptrNODE& beg, ptrNODE& end,std::function<bool(int)> condition);


int main()
{
	SetConsoleOutputCP(1251);
	FLIST list;
	std::ifstream file("input.txt");
	std::ofstream output_file("output.txt");
	task(list,file, output_file);
	std::cout << "File output.txt was created";
	std::cin.ignore(std::cin.rdbuf()->in_avail()).get();
}

bool findOddFragment(FLIST& list, ptrNODE& beg, ptrNODE& end, std::function<bool(int)> condition)
{

	beg = end = nullptr;;
	ptrNODE head = list.get_head();
	ptrNODE ptr = head;
	bool isBeg = false;
	bool isEnd = false;

	while (ptr->next&&!isEnd)
	{
		if (ptr->next&& condition(ptr->next->info))
		{
			if (!isBeg)
			{
				beg = ptr;
				isBeg = true;
			}
		}
		else
			if (condition(ptr->info)&&!condition(ptr->next->info))
			{
				end = ptr;
				isEnd = true;
			}
		ptr = ptr->next;
	}
	if (beg && end)
		std::cout << beg->info << ' ' << end->info << '\n';
	return end != nullptr&&isBeg!=false;

}


void task(FLIST& list, std::ifstream& input, std::ostream& output) // перестановка фрагмента в конец
{
	list.create_by_queue(input);
	list.print("древнмй список ");
	ptrNODE beg{}, end{};
	bool result = findOddFragment(list, beg, end, [](int x) {return x % 2 != 0; });
	if (result && end->next)
	{
		ptrNODE tail = list.get_tail();
		ptrNODE tmp = beg->next;
		beg->next = end->next;
		end->next = tail->next;
		tail->next = tmp;
		list.set_tail(end);
		ptrNODE ptr = tmp;
		while (ptr)
		{
			output << ptr->info << ' ';
			ptr = ptr->next;
		}
		list.print("нови ");

	}
	else
	{
		std::cout << "нет нови\n";
		output << "NO!";

	}
}
