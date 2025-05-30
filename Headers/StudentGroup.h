#pragma once
class StudentGroup {
    int id;
    int facultyId;
    int course;
public:
    StudentGroup(int id, int facultyId, int course)
        : id(id), facultyId(facultyId), course(course) {}
    int getId() const { return id; }
    int getFacultyId() const { return facultyId; }
    int getCourse() const { return course; }
};