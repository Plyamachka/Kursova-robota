#include "../Headers/Discipline.h"

Discipline::Discipline(int id, const std::string& name, int departmentId)
    : id(id), name(name), departmentId(departmentId) {}

int Discipline::getId() const { return id; }
std::string Discipline::getName() const { return name; }