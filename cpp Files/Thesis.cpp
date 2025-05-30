#include "../Headers/Thesis.h"

Thesis::Thesis(int id, int studentId, int teacherId, int departmentId, int facultyId, DissertationType type, const std::string& topic)
    : id(id), studentId(studentId), teacherId(teacherId), departmentId(departmentId), facultyId(facultyId), type(type), topic(topic) {}

int Thesis::getId() const { return id; }
int Thesis::getStudentId() const { return studentId; }
int Thesis::getTeacherId() const { return teacherId; }
int Thesis::getDepartmentId() const { return departmentId; }
int Thesis::getFacultyId() const { return facultyId; }
DissertationType Thesis::getType() const { return type; }
std::string Thesis::getTopic() const { return topic; }