#include "parts.h"
#include <iostream>

void Part::describe()
{
    std::cout << "Part " << name << " subparts are:" << std::endl;
    if (subparts.empty())
        std::cout << "It has no subparts." << std::endl;
    for (std::pair<Part*, int> pair : subparts)
        std::cout << pair.second << " " << pair.first->name << std::endl;
}

int Part::count_howmany(Part const* p)
{
    int result = 0;
    if (p == this)
        return 1;
    for (std::pair<Part*, int> pair : subparts)
        result += pair.first->count_howmany(p) * pair.second;
    return result;
}

int Part::count_howmanyUp(Part* const p)
{
    if (p == this)
        return 1;
    else if (!p->parent)
        return 0;
    else 
        return p->parent->subparts[p] * count_howmanyUp(p->parent);
}

Part* NameContainer::lookup(std::string const &name)
{
    if (name_map[name])
        return name_map[name];
    Part* newPart = new Part(name);
    name_map[name] = newPart;
    return newPart;
}


void NameContainer::add_part(std::string const &x, int q, std::string const &y)
{
    Part* part1 = lookup(x);
    Part* part2 = lookup(y);
    part1->subparts[part2] = q;
    part2->parent = part1;
}

