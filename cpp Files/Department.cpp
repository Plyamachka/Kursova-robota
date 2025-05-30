#include "../Headers/Department.h"

Department::Department(int id, const std::string& name, int facultyId)
    : id(id), name(name), facultyId(facultyId) {}

int Department::getId() const { return id; }
std::string Department::getName() const { return name; }
int Department::getFacultyId() const { return facultyId; }