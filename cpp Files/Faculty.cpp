#include "../Headers/Faculty.h"

Faculty::Faculty(int id, const std::string& name) : id(id), name(name) {}

int Faculty::getId() const { return id; }
std::string Faculty::getName() const { return name; }