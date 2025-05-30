#pragma once
#include "Person.h"
#include <string>

enum class TeacherCategory {
    Assistant,
    Docent,
    Professor
};

class Teacher : public Person {
    int departmentId;
    TeacherCategory category;
    int childrenCount;
    double salary;
    bool isPhdStudent;
    bool hasPhd;
    bool hasDoctor;
    bool isDocent;
    bool isProfessor;
public:
    Teacher(int id, const std::string& name, int departmentId, TeacherCategory category, const std::string& gender,
            int birthYear, int childrenCount, double salary, bool isPhdStudent, bool hasPhd, bool hasDoctor, bool isDocent, bool isProfessor)
        : Person(id, name, birthYear, gender), departmentId(departmentId), category(category), childrenCount(childrenCount),
          salary(salary), isPhdStudent(isPhdStudent), hasPhd(hasPhd), hasDoctor(hasDoctor), isDocent(isDocent), isProfessor(isProfessor) {}

    int getDepartmentId() const { return departmentId; }
    TeacherCategory getCategory() const { return category; }
    int getChildrenCount() const { return childrenCount; }
    double getSalary() const { return salary; }
    bool getIsPhdStudent() const { return isPhdStudent; }
    bool getHasPhd() const { return hasPhd; }
    bool getHasDoctor() const { return hasDoctor; }
    bool getIsDocent() const { return isDocent; }
    bool getIsProfessor() const { return isProfessor; }

    std::string getInfo() const override {
        return "Викладач: " + name + ", кафедра: " + std::to_string(departmentId);
    }
};