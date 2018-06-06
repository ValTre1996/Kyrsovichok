#include <list>
#include <string>
#include <iostream>
#include "marki.h"
using namespace std;

string word_in;
string mas[8];
class factory
{
public:
~factory();
list <Mark*> list;
Mark * Add(string name, istream &is);
Mark * Add_file(string name, string id, fstream &ofs);
void Print(string type, ostream &os);
void Save(ostream &fr, ostream &fv,string type);
};
factory::~factory()
{
for (Mark *ptr : list)
delete ptr;
}
void factory::Save(ostream &fr, ostream &fv, string type)
for (Mark *ptr : list)
{
if (ptr->Type().name == "real_state") {
fr << ptr->Type().name << endl;
fr << (*ptr) << endl;
}
if (ptr->Type().name == "virtuall_state") {
fv << ptr->Type().name << endl;
fv << (*ptr) << endl;
}
}
}
Mark * factory::Add_file(string typ, string id, fstream &ofs)
{
int i = 0;
for (MarkType *type : get_types())
if (type->name == typ)
{
Mark *ptr = type->make();
while (ofs >> word_in)
{
if (word_in == typ)
{
ofs >> word_in;
if (word_in == id) {
while (word_in != ";")
{
mas[i] = word_in;
ofs >> word_in;
i++;
}
list.push_back(ptr);
ptr->set(mas, ptr);
ptr->Print2(ofs);
return ptr;
}
else {
while (word_in != ";")
ofs >> word_in;
}
}
else {
while (word_in != ";")
ofs >> word_in;
}
}
}
}

Mark * factory::Add(string name, istream &is)
{
for (MarkType *type : get_types())
if (type->name == name)
{
Mark *ptr = type->make();
list.push_back(ptr);
is >> (*ptr);
return ptr;
}
}
void factory::Print(string type, ostream &os)
{
bool flag = (type == "");
for (Mark *ptr : list)
if (flag || ptr->Type().name == type)
{
os << endl << (*ptr);
}
}
