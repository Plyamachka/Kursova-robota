#pragma once
#include <string>
#include <ostream>

enum class DissertationType {
    Any = 0,
    Candidate = 1,
    Doctor = 2
};

class Thesis {
    int id;
    int studentId;
    int teacherId;
    int departmentId;
    int facultyId;
    DissertationType type;
    std::string topic;
public:
    Thesis(int id, int studentId, int teacherId, int departmentId, int facultyId, DissertationType type, const std::string& topic);

    int getId() const;
    int getStudentId() const;
    int getTeacherId() const;
    int getDepartmentId() const;
    int getFacultyId() const;
    DissertationType getType() const;
    std::string getTopic() const;
};

inline std::ostream& operator<<(std::ostream& os, const Thesis& t) {
    os << "Тема: " << t.getTopic()
       << ", студент ID: " << t.getStudentId()
       << ", керівник ID: " << t.getTeacherId()
       << ", кафедра: " << t.getDepartmentId()
       << ", факультет: " << t.getFacultyId()
       << ", тип: " << static_cast<int>(t.getType());
    return os;
}