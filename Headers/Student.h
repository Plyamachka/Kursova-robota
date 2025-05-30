#pragma once
#include "Person.h"

class Student : public Person {
    int groupId;
    bool hasChildren;
    double scholarship;
public:
    Student(int id, const std::string& name, int groupId, int birthYear, const std::string& gender, bool hasChildren, double scholarship)
        : Person(id, name, birthYear, gender), groupId(groupId), hasChildren(hasChildren), scholarship(scholarship) {}

    int getGroupId() const { return groupId; }
    bool getHasChildren() const { return hasChildren; }
    double getScholarship() const { return scholarship; }

    std::string getInfo() const override {
        return "Студент: " + name + ", група: " + std::to_string(groupId);
    }
};