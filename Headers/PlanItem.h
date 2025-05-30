#pragma once
enum class LessonType {
    Lecture,
    Seminar,
    Lab,
    Consultation,
    Coursework,
    Other
};
enum class ControlType {
    Exam,
    Credit
};

class PlanItem {
    int id;
    int disciplineId;
    int groupId;
    int course;
    int semester;
    int hours;
    LessonType lessonType;
    ControlType controlType;
public:
    PlanItem(int id, int disciplineId, int groupId, int course, int semester, int hours, LessonType lessonType, ControlType controlType)
        : id(id), disciplineId(disciplineId), groupId(groupId), course(course), semester(semester), hours(hours), lessonType(lessonType), controlType(controlType) {}

    int getId() const { return id; }
    int getDisciplineId() const { return disciplineId; }
    int getGroupId() const { return groupId; }
    int getCourse() const { return course; }
    int getSemester() const { return semester; }
    int getHours() const { return hours; }
    LessonType getLessonType() const { return lessonType; }
    ControlType getControlType() const { return controlType; }
};