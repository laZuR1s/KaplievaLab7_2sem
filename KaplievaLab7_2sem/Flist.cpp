#include "Flist.h"
#include "fstream"


FLIST::~FLIST()
{
    while (!empty())
    {
        del_from_head();
    }
    delete head;
    head = tail = nullptr;
}

void FLIST::add_to_head(TInfo elem)
{
    adding_by_pointer(head->next, elem);
    if (head == tail)
        tail = tail->next;
}

void FLIST::add_to_tail(TInfo elem)
{
    adding_by_pointer(tail->next, elem);
    tail = tail->next;
}

void FLIST::add_after(ptrNODE ptr, TInfo elem)
{
    if (ptr) 
    {
        adding_by_pointer(ptr->next, elem);
        if (ptr == tail)
            tail = tail->next;
    }
}

void FLIST::del_from_head()
{
    if (head->next)
    {
        deleting_by_pointer(head->next);
        if (!head->next) 
            tail = head;
    }
}

void FLIST::create_by_queue(std::ifstream& file)
{
    TInfo elem;
    while (file >> elem)
        add_to_tail(elem);
}

void FLIST::print(const char* message, std::ostream& stream)
{
    stream << message << '\n';
    ptrNODE ptr = head->next; 
    while (ptr)
    {
        stream << ptr->info << ' ';
        ptr = ptr->next;
    }
    stream << '\n';
}