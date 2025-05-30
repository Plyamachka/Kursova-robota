#pragma once
#include <vector>
#include <string>
#include <map>
#include "Student.h"
#include "Faculty.h"
#include "StudentGroup.h"
#include "Teacher.h"
#include "Department.h"
#include "Discipline.h"
#include "PlanItem.h"
#include "ExamResult.h"
#include "Thesis.h"

class Database {
private:
    std::vector<Student> students;
    std::vector<Faculty> faculties;
    std::vector<StudentGroup> groups;
    std::vector<Teacher> teachers;
    std::vector<Department> departments;
    std::vector<Discipline> disciplines;
    std::vector<PlanItem> planItems;
    std::vector<ExamResult> examResults;
    std::vector<Thesis> theses;

    std::map<int, std::vector<int>> groupDisciplines;

    void loadStudents(const std::string& filename);
    void loadFaculties(const std::string& filename);
    void loadGroups(const std::string& filename);
    void loadTeachers(const std::string& filename);
    void loadDepartments(const std::string& filename);
    void loadDisciplines(const std::string& filename);
    void loadPlanItems(const std::string& filename);
    void loadExamResults(const std::string& filename);
    void loadTheses(const std::string& filename);
public:
    void loadFromFiles(const std::string& path);
    const std::vector<StudentGroup>& getGroups() const { return groups; }

    std::vector<Student> queryStudents(
        const std::vector<int>& groupIds,
        const std::vector<int>& courses,
        int facultyId,
        const std::string& gender,
        int birthYear,
        int minAge,
        int maxAge,
        bool hasChildren,
        bool hasScholarship,
        double minScholarship,
        double maxScholarship
    ) const;

    std::vector<Teacher> queryTeachers(
        const std::vector<int>& departmentIds,
        int facultyId,
        const std::vector<TeacherCategory>& categories,
        const std::string& gender,
        int birthYear,
        int minAge,
        int maxAge,
        bool hasChildren,
        int minChildren,
        int maxChildren,
        double minSalary,
        double maxSalary,
        bool isPhdStudent,
        bool hasPhd,
        bool hasDoctor
    ) const;

    std::vector<Thesis> queryDissertations(
        int departmentId,
        int facultyId,
        DissertationType type
    ) const;

    std::vector<Department> queryDepartmentsForGroupCourseFacultySemester(
        int groupId,
        int course,
        int facultyId,
        int semester
    ) const;

    std::vector<Teacher> queryTeachersByDisciplineGroupCourseFaculty(
        int disciplineId,
        int groupId,
        int course,
        int facultyId
    ) const;

    std::vector<Teacher> queryTeachersByLessonType(
        LessonType lessonType,
        int groupId,
        int course,
        int facultyId,
        int semester
    ) const;

    std::vector<Student> queryStudentsByExam(
        const std::vector<int>& groupIds,
        int disciplineId,
        ControlType controlType,
        int mark
    ) const;

    std::vector<Student> queryStudentsBySession(
        const std::vector<int>& groupIds,
        const std::vector<int>& courses,
        int facultyId,
        bool excellentOnly,
        bool noThrees,
        bool noTwos
    ) const;

    std::vector<Teacher> queryTeachersTakingExams(
        const std::vector<int>& groupIds,
        const std::vector<int>& disciplineIds,
        int semester
    ) const;

    std::vector<Student> queryStudentsByTeacherDisciplineMarkSemesterPeriod(
        const std::vector<int>& groupIds,
        int teacherId,
        const std::vector<int>& disciplineIds,
        int mark,
        const std::vector<int>& semesters,
        int periodStart,
        int periodEnd
    ) const;

    std::vector<std::pair<Student, std::string>> queryStudentsAndTheses(
        int departmentId,
        int teacherId
    ) const;

    std::vector<Teacher> queryThesisSupervisors(
        int departmentId,
        int facultyId,
        const std::vector<TeacherCategory>& categories
    ) const;

    std::vector<std::tuple<std::string, int, LessonType>> queryTeacherLoad(
        int teacherId,
        int departmentId,
        int semester
    ) const;
};