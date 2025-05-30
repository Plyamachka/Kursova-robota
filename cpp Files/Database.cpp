#include "../Headers/Database.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>

void Database::loadFromFiles(const std::string& path) {
    loadStudents(path + "output/students.txt");
    loadFaculties(path + "output/faculties.txt");
    loadGroups(path + "output/groups.txt");
    loadTeachers(path + "output/teachers.txt");
    loadDepartments(path + "output/departments.txt");
    loadDisciplines(path + "output/disciplines.txt");
    loadPlanItems(path + "output/plan_items.txt");
    loadExamResults(path + "output/exam_results.txt");
    loadTheses(path + "output/theses.txt");
}

void Database::loadStudents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, groupIdStr, birthYearStr, gender, hasChildrenStr, scholarshipStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, groupIdStr, ',');
        std::getline(ss, birthYearStr, ',');
        std::getline(ss, gender, ',');
        std::getline(ss, hasChildrenStr, ',');
        std::getline(ss, scholarshipStr, ',');

        try {
            int id = std::stoi(idStr);
            int groupId = std::stoi(groupIdStr);
            int birthYear = std::stoi(birthYearStr);
            bool hasChildren = (std::stoi(hasChildrenStr) == 1);
            double scholarship = std::stod(scholarshipStr);
            students.emplace_back(id, name, groupId, birthYear, gender, hasChildren, scholarship);
        } catch (const std::exception& e) {
            std::cerr << "Помилка при зчитуванні студента: " << e.what() << std::endl;
        }
    }
    file.close();
}

void Database::loadFaculties(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');

        try {
            int id = std::stoi(idStr);
            faculties.emplace_back(id, name);
        } catch (const std::exception& e) {
            std::cerr << "Помилка при зчитуванні факультету: " << e.what() << std::endl;
        }
    }
    file.close();
}

void Database::loadGroups(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, facultyIdStr, courseStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, facultyIdStr, ',');
        std::getline(ss, courseStr, ',');

        try {
            int id = std::stoi(idStr);
            int facultyId = std::stoi(facultyIdStr);
            int course = std::stoi(courseStr);
            groups.emplace_back(id, facultyId, course);
        } catch (const std::exception& e) {
            std::cerr << "Помилка при зчитуванні групи: " << e.what() << std::endl;
        }
    }
    file.close();
}

void Database::loadTeachers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, departmentIdStr, categoryStr, gender, birthYearStr, childrenCountStr, salaryStr, isPhdStudentStr, hasPhdStr, hasDoctorStr, isDocentStr, isProfessorStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, departmentIdStr, ',');
        std::getline(ss, categoryStr, ',');
        std::getline(ss, gender, ',');
        std::getline(ss, birthYearStr, ',');
        std::getline(ss, childrenCountStr, ',');
        std::getline(ss, salaryStr, ',');
        std::getline(ss, isPhdStudentStr, ',');
        std::getline(ss, hasPhdStr, ',');
        std::getline(ss, hasDoctorStr, ',');
        std::getline(ss, isDocentStr, ',');
        std::getline(ss, isProfessorStr, ',');

        try {
            int id = std::stoi(idStr);
            int departmentId = std::stoi(departmentIdStr);
            TeacherCategory category;
            if (categoryStr == "Assistant") category = TeacherCategory::Assistant;
            else if (categoryStr == "Docent") category = TeacherCategory::Docent;
            else if (categoryStr == "Professor") category = TeacherCategory::Professor;
            else throw std::runtime_error("Невідома категорія викладача: " + categoryStr);
            int birthYear = std::stoi(birthYearStr);
            int childrenCount = std::stoi(childrenCountStr);
            double salary = std::stod(salaryStr);
            bool isPhdStudent = (isPhdStudentStr == "1");
            bool hasPhd = (hasPhdStr == "1");
            bool hasDoctor = (hasDoctorStr == "1");
            bool isDocent = (isDocentStr == "1");
            bool isProfessor = (isProfessorStr == "1");

            teachers.emplace_back(id, name, departmentId, category, gender, birthYear, childrenCount, salary, isPhdStudent, hasPhd, hasDoctor, isDocent, isProfessor);
        } catch (const std::exception& e) {
            std::cerr << "Помилка при зчитуванні викладача: " << e.what() << std::endl;
        }
    }
    file.close();
}

void Database::loadDepartments(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, facultyIdStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, facultyIdStr, ',');

        try {
            int id = std::stoi(idStr);
            int facultyId = std::stoi(facultyIdStr);
            departments.emplace_back(id, name, facultyId);
        } catch (const std::exception& e) {
            std::cerr << "Помилка при зчитуванні кафедри: " << e.what() << std::endl;
        }
    }
    file.close();
}

void Database::loadDisciplines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');

        try {
            int id = std::stoi(idStr);
            disciplines.emplace_back(id, name);
        } catch (const std::exception& e) {
            std::cerr << "Помилка при зчитуванні дисципліни: " << e.what() << std::endl;
        }
    }
    file.close();
}

void Database::loadPlanItems(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, disciplineIdStr, groupIdStr, courseStr, semesterStr, hoursStr, lessonTypeStr, controlTypeStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, disciplineIdStr, ',');
        std::getline(ss, groupIdStr, ',');
        std::getline(ss, courseStr, ',');
        std::getline(ss, semesterStr, ',');
        std::getline(ss, hoursStr, ',');
        std::getline(ss, lessonTypeStr, ',');
        std::getline(ss, controlTypeStr, ',');

        try {
            int id = std::stoi(idStr);
            int disciplineId = std::stoi(disciplineIdStr);
            int groupId = std::stoi(groupIdStr);
            int course = std::stoi(courseStr);
            int semester = std::stoi(semesterStr);
            int hours = std::stoi(hoursStr);
            LessonType lessonType;
            if (lessonTypeStr == "Lecture") lessonType = LessonType::Lecture;
            else if (lessonTypeStr == "Seminar") lessonType = LessonType::Seminar;
            else if (lessonTypeStr == "Lab") lessonType = LessonType::Lab;
            else if (lessonTypeStr == "Consultation") lessonType = LessonType::Consultation;
            else if (lessonTypeStr == "Coursework") lessonType = LessonType::Coursework;
            else lessonType = LessonType::Other;
            ControlType controlType;
            if (controlTypeStr == "Credit") controlType = ControlType::Credit;
            else if (controlTypeStr == "Exam") controlType = ControlType::Exam;
            else throw std::runtime_error("Невідомий тип контролю: " + controlTypeStr);

            planItems.emplace_back(id, disciplineId, groupId, course, semester, hours, lessonType, controlType);
        } catch (const std::exception& e) {
            std::cerr << "Помилка при зчитуванні плану занять: " << e.what() << std::endl;
        }
    }
    file.close();
}

void Database::loadExamResults(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, studentIdStr, disciplineIdStr, teacherIdStr, semesterStr, markStr, isExamStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, studentIdStr, ',');
        std::getline(ss, disciplineIdStr, ',');
        std::getline(ss, teacherIdStr, ',');
        std::getline(ss, semesterStr, ',');
        std::getline(ss, markStr, ',');
        std::getline(ss, isExamStr, ',');

        try {
            int id = std::stoi(idStr);
            int studentId = std::stoi(studentIdStr);
            int disciplineId = std::stoi(disciplineIdStr);
            int teacherId = std::stoi(teacherIdStr);
            int semester = std::stoi(semesterStr);
            int mark = std::stoi(markStr);
            bool isExam = (isExamStr == "1");

            examResults.emplace_back(id, studentId, disciplineId, teacherId, semester, mark, isExam);
        } catch (const std::exception& e) {
            std::cerr << "Помилка при зчитуванні результатів іспиту: " << e.what() << std::endl;
        }
    }
    file.close();
}

void Database::loadTheses(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, studentIdStr, teacherIdStr, departmentIdStr, facultyIdStr, typeStr, topic;
        std::getline(ss, idStr, ',');
        std::getline(ss, studentIdStr, ',');
        std::getline(ss, teacherIdStr, ',');
        std::getline(ss, departmentIdStr, ',');
        std::getline(ss, facultyIdStr, ',');
        std::getline(ss, typeStr, ',');
        std::getline(ss, topic, ',');

        try {
            int id = std::stoi(idStr);
            int studentId = std::stoi(studentIdStr);
            int teacherId = std::stoi(teacherIdStr);
            int departmentId = std::stoi(departmentIdStr);
            int facultyId = std::stoi(facultyIdStr);
            DissertationType type = static_cast<DissertationType>(std::stoi(typeStr));
            theses.emplace_back(id, studentId, teacherId, departmentId, facultyId, type, topic);
        } catch (...) {}
    }
    file.close();
}

std::vector<Student> Database::queryStudents(
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
) const {
    std::vector<Student> result;
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int currentYear = now->tm_year + 1900;

    for (const auto& s : students) {
        if (!groupIds.empty() && std::find(groupIds.begin(), groupIds.end(), s.getGroupId()) == groupIds.end()) continue;
        if (!gender.empty() && s.getGender() != gender) continue;
        if (birthYear > 0 && s.getBirthYear() != birthYear) continue;
        int age = currentYear - s.getBirthYear();
        if (minAge > 0 && age < minAge) continue;
        if (maxAge > 0 && age > maxAge) continue;
        if (hasChildren && !s.getHasChildren()) continue;
        if (hasScholarship && s.getScholarship() <= 0) continue;
        if (minScholarship > 0 && s.getScholarship() < minScholarship) continue;
        if (maxScholarship > 0 && s.getScholarship() > maxScholarship) continue;
        result.push_back(s);
    }
    return result;
}

std::vector<Teacher> Database::queryTeachers(
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
) const {
    std::vector<Teacher> result;
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int currentYear = now->tm_year + 1900;

    for (const auto& tchr : teachers) {
        if (!departmentIds.empty() && std::find(departmentIds.begin(), departmentIds.end(), tchr.getDepartmentId()) == departmentIds.end()) continue;
        if (facultyId > 0) { /* ... */ }
        if (!categories.empty() && std::find(categories.begin(), categories.end(), tchr.getCategory()) == categories.end()) continue;
        if (!gender.empty() && tchr.getGender() != gender) continue;
        if (birthYear > 0 && tchr.getBirthYear() != birthYear) continue;
        int age = currentYear - tchr.getBirthYear();
        if (minAge > 0 && age < minAge) continue;
        if (maxAge > 0 && age > maxAge) continue;
        if (hasChildren && tchr.getChildrenCount() == 0) continue;
        if (minChildren > 0 && tchr.getChildrenCount() < minChildren) continue;
        if (maxChildren > 0 && tchr.getChildrenCount() > maxChildren) continue;
        if (minSalary > 0 && tchr.getSalary() < minSalary) continue;
        if (maxSalary > 0 && tchr.getSalary() > maxSalary) continue;
        if (isPhdStudent && !tchr.getIsPhdStudent()) continue;
        if (hasPhd && !tchr.getHasPhd()) continue;
        if (hasDoctor && !tchr.getHasDoctor()) continue;
        result.push_back(tchr);
    }
    return result;
}


std::vector<Thesis> Database::queryDissertations(
    int departmentId,
    int facultyId,
    DissertationType type
) const {
    std::vector<Thesis> result;
    for (const auto& t : theses) {
        if (departmentId > 0 && t.getDepartmentId() != departmentId) continue;
        if (facultyId > 0 && t.getFacultyId() != facultyId) continue;
        if (type != DissertationType::Any && t.getType() != type) continue;
        result.push_back(t);
    }
    return result;
}


std::vector<Department> Database::queryDepartmentsForGroupCourseFacultySemester(
    int groupId,
    int course,
    int facultyId,
    int semester
) const {
    std::vector<Department> result;
    for (const auto& plan : planItems) {
        if ((groupId == 0 || plan.getGroupId() == groupId) &&
            (course == 0 || plan.getCourse() == course) &&
            (semester == 0 || plan.getSemester() == semester)) {
            for (const auto& d : departments) {
                if (facultyId == 0 || d.getFacultyId() == facultyId) {
                    result.push_back(d);
                }
            }
        }
    }
    return result;
}

std::vector<Teacher> Database::queryTeachersByDisciplineGroupCourseFaculty(
    int disciplineId,
    int groupId,
    int course,
    int facultyId
) const {
    std::vector<Teacher> result;
    for (const auto& plan : planItems) {
        if ((disciplineId == 0 || plan.getDisciplineId() == disciplineId) &&
            (groupId == 0 || plan.getGroupId() == groupId) &&
            (course == 0 || plan.getCourse() == course)) {
            for (const auto& t : teachers) {
                for (const auto& d : departments) {
                    if (facultyId == 0 || d.getFacultyId() == facultyId) {
                        if (t.getDepartmentId() == d.getId()) {
                            result.push_back(t);
                        }
                    }
                }
            }
        }
    }
    return result;
}

std::vector<Teacher> Database::queryTeachersByLessonType(
    LessonType lessonType,
    int groupId,
    int course,
    int facultyId,
    int semester
) const {
    std::vector<Teacher> result;
    for (const auto& plan : planItems) {
        if ((lessonType == plan.getLessonType()) &&
            (groupId == 0 || plan.getGroupId() == groupId) &&
            (course == 0 || plan.getCourse() == course) &&
            (semester == 0 || plan.getSemester() == semester)) {
            for (const auto& t : teachers) {
                for (const auto& d : departments) {
                    if (facultyId == 0 || d.getFacultyId() == facultyId) {
                        if (t.getDepartmentId() == d.getId()) {
                            result.push_back(t);
                        }
                    }
                }
            }
        }
    }
    return result;
}

std::vector<Student> Database::queryStudentsByExam(
    const std::vector<int>& groupIds,
    int disciplineId,
    ControlType controlType,
    int mark
) const {
    std::vector<Student> result;
    for (const auto& exam : examResults) {
        if ((disciplineId == 0 || exam.getDisciplineId() == disciplineId) &&
            ((controlType == ControlType::Exam && exam.getIsExam()) ||
             (controlType == ControlType::Credit && !exam.getIsExam())) &&
            (mark == 0 || exam.getMark() == mark)) {
            for (const auto& s : students) {
                if (s.getId() == exam.getStudentId() &&
                    (groupIds.empty() || std::find(groupIds.begin(), groupIds.end(), s.getGroupId()) != groupIds.end())) {
                    result.push_back(s);
                }
            }
        }
    }
    return result;
}

std::vector<Student> Database::queryStudentsBySession(
    const std::vector<int>& groupIds,
    const std::vector<int>& courses,
    int facultyId,
    bool excellentOnly,
    bool noThrees,
    bool noTwos
) const {
    std::vector<Student> result;
    for (const auto& s : students) {
        if (!groupIds.empty() && std::find(groupIds.begin(), groupIds.end(), s.getGroupId()) == groupIds.end()) continue;

        std::vector<const ExamResult*> studentExams;
        for (const auto& exam : examResults) {
            if (exam.getStudentId() == s.getId()) {
                studentExams.push_back(&exam);
            }
        }
        if (studentExams.empty()) continue;

        bool ok = true;
        for (const auto* exam : studentExams) {
            if (excellentOnly && exam->getMark() < 5) { ok = false; break; }
            if (noThrees && exam->getMark() == 3) { ok = false; break; }
            if (noTwos && exam->getMark() == 2) { ok = false; break; }
        }
        if (ok) result.push_back(s);
    }
    return result;
}
std::vector<Teacher> Database::queryTeachersTakingExams(
    const std::vector<int>& groupIds,
    const std::vector<int>& disciplineIds,
    int semester
) const {
    std::vector<Teacher> result;
    for (const auto& exam : examResults) {
        if ((groupIds.empty() || std::find(groupIds.begin(), groupIds.end(), exam.getStudentId()) != groupIds.end()) &&
            (disciplineIds.empty() || std::find(disciplineIds.begin(), disciplineIds.end(), exam.getDisciplineId()) != disciplineIds.end()) &&
            (semester == 0 || exam.getSemester() == semester)) {
            for (const auto& t : teachers) {
                if (t.getId() == exam.getTeacherId()) {
                    result.push_back(t);
                }
            }
        }
    }
    return result;
}

std::vector<Student> Database::queryStudentsByTeacherDisciplineMarkSemesterPeriod(
    const std::vector<int>& groupIds,
    int teacherId,
    const std::vector<int>& disciplineIds,
    int mark,
    const std::vector<int>& semesters,
    int periodStart,
    int periodEnd
) const {
    std::vector<Student> result;
    for (const auto& exam : examResults) {
        if ((teacherId == 0 || exam.getTeacherId() == teacherId) &&
            (disciplineIds.empty() || std::find(disciplineIds.begin(), disciplineIds.end(), exam.getDisciplineId()) != disciplineIds.end()) &&
            (mark == 0 || exam.getMark() == mark) &&
            (semesters.empty() || std::find(semesters.begin(), semesters.end(), exam.getSemester()) != semesters.end()) &&
            (periodStart == 0 || exam.getSemester() >= periodStart) &&
            (periodEnd == 0 || exam.getSemester() <= periodEnd)) {
            for (const auto& s : students) {
                if (s.getId() == exam.getStudentId() &&
                    (groupIds.empty() || std::find(groupIds.begin(), groupIds.end(), s.getGroupId()) != groupIds.end())) {
                    result.push_back(s);
                }
            }
        }
    }
    return result;
}

std::vector<std::pair<Student, std::string>> Database::queryStudentsAndTheses(
    int departmentId,
    int teacherId
) const {
    std::vector<std::pair<Student, std::string>> result;
    for (const auto& thesis : theses) {
        if ((departmentId == 0 || thesis.getDepartmentId() == departmentId) &&
            (teacherId == 0 || thesis.getTeacherId() == teacherId)) {
            for (const auto& s : students) {
                if (s.getId() == thesis.getStudentId()) {
                    result.emplace_back(s, thesis.getTopic());
                }
            }
        }
    }
    return result;
}

std::vector<Teacher> Database::queryThesisSupervisors(
    int departmentId,
    int facultyId,
    const std::vector<TeacherCategory>& categories
) const {
    std::vector<Teacher> result;
    for (const auto& thesis : theses) {
        for (const auto& t : teachers) {
            if (t.getId() == thesis.getTeacherId() &&
                (departmentId == 0 || t.getDepartmentId() == departmentId)) {
                if (categories.empty() || std::find(categories.begin(), categories.end(), t.getCategory()) != categories.end()) {
                    result.push_back(t);
                }
            }
        }
    }
    return result;
}

std::vector<std::tuple<std::string, int, LessonType>> Database::queryTeacherLoad(
    int teacherId,
    int departmentId,
    int semester
) const {
    std::vector<std::tuple<std::string, int, LessonType>> result;
    for (const auto& plan : planItems) {
        if ((semester == 0 || plan.getSemester() == semester)) {
            for (const auto& t : teachers) {
                if ((teacherId == 0 || t.getId() == teacherId) &&
                    (departmentId == 0 || t.getDepartmentId() == departmentId)) {
                    for (const auto& d : disciplines) {
                        if (d.getId() == plan.getDisciplineId()) {
                            result.emplace_back(d.getName(), plan.getHours(), plan.getLessonType());
                        }
                    }
                }
            }
        }
    }
    return result;
}