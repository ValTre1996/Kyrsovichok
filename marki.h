#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
void clrFile(ostream &fname) {
fname.clear();
}
class Mark;
struct MarkType;
template <class T>
Mark * MarkMaker() { return new T; }
list <MarkType*> & get_types()
{
static list <MarkType*> types;
return types;
}
struct MarkType
{
int count;
string name;
Mark *(*make)();
MarkType(const char *n, Mark *(*m)())
: name(n), make(m), count(0) {
get_types().push_back(this);
}
};
class Mark {
protected:
string appointment;
string issuer;
string form;
string material;
int number_of;
public:
virtual const MarkType & Type() const = 0;
virtual void Print(ostream &os = cout) const;
virtual void Print2(fstream &os) const;
virtual void Read(istream &is);
virtual void Save(ostream &os);
virtual void set(string *mas, Mark *d);
virtual ~Mark() {}
};
void Mark::Save(ostream &os)
{
os << appointment << endl;
os << issuer << endl;
os << form << endl;
os << material << endl;
os << number_of << endl;
}
void Mark::Read(istream &is)
{
cout << "appointment: "; cin >> appointment;
cout << "issuer: "; cin >> issuer;
cout << "form: "; cin >> form;
cout << "material: "; cin >> material;
cout << "number_of: "; cin >> number_of;
}
void Mark::set(string *mas, Mark *d)
{
d->appointment = mas[1];
d->issuer = mas[2];
d->form = mas[3];
d->material = mas[4];
std::istringstream ist2(mas[5]);
ist2 >> d->number_of;
};
void Mark::Print(ostream &os) const
{
os << "appointment: " << appointment << endl;
os << "by the nature of the issuer : " << issuer << endl;
os << "form: " << form << endl;
os << "material: " << material << endl;
os << "number of: " << number_of << endl;
};
void Mark::Print2(fstream &os) const
{
cout << "appointment: " << appointment << endl;
cout << "issuer: " << issuer << endl;
cout << "form: " << form << endl;
cout << "material: " << material << endl;
cout << "number_of: " << number_of << endl;
}

class real_state :public Mark {
static MarkType type;
public:
real_state() { ++type.count; }
void Print(ostream &os);
void Print2(fstream &os);
const MarkType & Type() const { return type; }
};
class virtuall_state :public Mark {
static MarkType type;
public:
virtuall_state() { ++type.count; }
const MarkType & Type() const { return type; }
void Print(ostream &os);
void Print2(fstream &os);
};

void real_state::Print(ostream &os) { Mark::Print(os); }
void real_state::Print2(fstream &os) { Mark::Print2(os); }
void virtuall_state::Print(ostream &os) { Mark::Print(os); }
void virtuall_state::Print2(fstream &os) { Mark::Print2(os); }
MarkType real_state::type("real_state", &MarkMaker<real_state>);
MarkType virtuall_state::type("virtuall_state", &MarkMaker<virtuall_state>);

istream & operator >> (istream &is, Mark &d)
{
d.Read(is);	return is;
}
ostream & operator<<(ostream &os, const Mark &d)
{
d.Print(os);	return os;
}
