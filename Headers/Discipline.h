#pragma once
#include <string>

class Discipline {
private:
    int id;
    std::string name;
public:
    Discipline(int id, const std::string& name);
    int getId() const;
    std::string getName() const;
};