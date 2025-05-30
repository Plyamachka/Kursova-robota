#pragma once
#include <string>

class Department {
private:
    int id;
    std::string name;
    int facultyId;
public:
    Department(int id, const std::string& name, int facultyId);
    int getId() const;
    std::string getName() const;
    int getFacultyId() const;
};