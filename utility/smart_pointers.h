#ifndef UTILITY_SMART_POINTERS_H
#define UTILITY_SMART_POINTERS_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

namespace utility {
namespace smart_pointers {

void shared_ptr_demo();
void weak_ptr_demo();
void shared_ptr_missuse_demo();
void unique_ptr_demo();

// for weak_ptr_demo()
class Person {
public:
    string name;
    shared_ptr<Person> mother;
    shared_ptr<Person> father;
    vector<shared_ptr<Person>> kids;

    Person (const string& n,
            shared_ptr<Person> m = nullptr,
            shared_ptr<Person> f = nullptr)
            : name(n), mother(m), father(f) {
    }
    ~Person() {
        cout << "delete " << name << endl;
    }
};

class PersonEx {
public:
    string name;
    shared_ptr<PersonEx> mother;
    shared_ptr<PersonEx> father;
    vector<weak_ptr<PersonEx>> kids;

    PersonEx (const string& n,
              shared_ptr<PersonEx> m = nullptr,
              shared_ptr<PersonEx> f = nullptr)
              : name(n), mother(m), father(f) {
    }
    ~PersonEx() {
        cout << "delete " << name << endl;
    }
};

template <typename T>
shared_ptr<T> InitFamily(const string& name);

// for shared_ptr_missuse_demo()
struct Good: public enable_shared_from_this<Good>
{
    shared_ptr<Good> GetPtr()
    {
        return shared_from_this();
    }
};

struct Bad
{
    shared_ptr<Bad> GetPtr()
    {
        return shared_ptr<Bad>(this);
    }
};

}
}

#endif //UTILITY_SMART_POINTERS_H