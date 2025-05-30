#include "../Headers/Discipline.h"

Discipline::Discipline(int id, const std::string& name) : id(id), name(name) {}
int Discipline::getId() const { return id; }
std::string Discipline::getName() const { return name; }