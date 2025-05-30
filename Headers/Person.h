#pragma once
#include <string>

class Person {
protected:
    int id;
    std::string name;
    int birthYear;
    std::string gender;
public:
    Person(int id, const std::string& name, int birthYear, const std::string& gender)
        : id(id), name(name), birthYear(birthYear), gender(gender) {}

    virtual ~Person() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getBirthYear() const { return birthYear; }
    std::string getGender() const { return gender; }

    virtual std::string getInfo() const {
        return name + " (" + gender + ")";
    }
};