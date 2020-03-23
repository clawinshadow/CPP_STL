#ifndef STL_DEMO_CONTAINERS_OTHERS_H
#define STL_DEMO_CONTAINERS_OTHERS_H

#include <string>
#include <iostream>
#include <memory>

namespace containers {
namespace others {

void StringsDemo();
void C_Arrays_Demo();
void Reference_Semantics();
void Reference_Wrapper();

class Item {
private:
    std::string name;
    float price;
public:
    Item(const std::string &_name, float p = 0): name(_name), price(p) { };

    std::string GetName() const {
        return name;
    }

    void SetName(const std::string &_n) {
        name = _n;
    }

    float GetPrice() const {
        return price;
    }

    void SetPrice(float p) {
        price = p;
    }
};

typedef std::shared_ptr<Item> ItemPtr;

class ItemPtrCmp {
public:
    bool operator() (const ItemPtr &_item1, const ItemPtr &_item2)
    {
        return _item1->GetName() < _item2->GetName();
    }
};

template <typename Coll>
void printItems(const std::string& msg, const Coll& coll)
{
    std::cout << msg << std::endl;
    for (const auto& elem : coll) {
        std::cout << ' ' << elem->GetName() << ": "
                         << elem->GetPrice() << std::endl;
    }
}

}
}

#endif //STL_DEMO_CONTAINERS_OTHERS_H
