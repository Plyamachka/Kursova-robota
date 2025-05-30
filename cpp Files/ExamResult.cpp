#include "../Headers/ExamResult.h"

ExamResult::ExamResult(int id, int studentId, int disciplineId, int teacherId, int semester, int mark, bool isExam)
    : id(id), studentId(studentId), disciplineId(disciplineId), teacherId(teacherId),
      semester(semester), mark(mark), isExam(isExam) {}

int ExamResult::getId() const { return id; }
int ExamResult::getStudentId() const { return studentId; }
int ExamResult::getDisciplineId() const { return disciplineId; }
int ExamResult::getTeacherId() const { return teacherId; }
int ExamResult::getSemester() const { return semester; }
int ExamResult::getMark() const { return mark; }
bool ExamResult::getIsExam() const { return isExam; }