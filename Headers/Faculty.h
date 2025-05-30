#pragma once
#include <string>
#include <vector>

class Faculty {
private:
    int id;
    std::string name;
public:
    Faculty(int id, const std::string& name);
    int getId() const;
    std::string getName() const;
};