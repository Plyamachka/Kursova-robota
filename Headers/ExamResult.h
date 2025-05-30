#pragma once
#include <string>

class ExamResult {
private:
    int id;
    int studentId;
    int disciplineId;
    int teacherId;
    int semester;
    int mark;
    bool isExam;
public:
    ExamResult(int id, int studentId, int disciplineId, int teacherId, int semester, int mark, bool isExam);

    int getId() const;
    int getStudentId() const;
    int getDisciplineId() const;
    int getTeacherId() const;
    int getSemester() const;
    int getMark() const;
    bool getIsExam() const;
};