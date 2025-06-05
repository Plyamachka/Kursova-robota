#pragma once
#include <string>

class Discipline {
private:
    int id;
    std::string name;
    int departmentId; 
public:
    Discipline(int id, const std::string& name, int departmentId); 
    int getId() const;
    std::string getName() const;
    int getDepartmentId() const { return departmentId; } 
};