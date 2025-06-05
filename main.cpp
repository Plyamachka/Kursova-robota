#include <iostream>
#include "Headers/Database.h"
#include "Headers/Person.h"
#include "Headers/Student.h"
#include "Headers/Teacher.h"
#include <vector>
#include <limits>
#include <memory>
#include <windows.h>

void printMenu() {
    std::cout << "\n=== Меню запитів ===\n";
    std::cout << "Запит 1(студенти)\n";
    std::cout << "Запит 2(викладачі)\n";
    std::cout << "Запит 3(Перелік тем дисертацій)\n";
    std::cout << "Запит 4(Перелік кафедр)\n";
    std::cout << "Запит 5 (Перелік викладачів за дисципліною)\n";
    std::cout << "Запит 6 (Перелік викладачів за типом занять\n";
    std::cout << "Запит 7 (Перелік студентів, які здали іспит/залік)\n";
    std::cout << "Запит 8 (Перелік студентів, які здали сесію на відмінно/без трійок/без двійок)\n";
    std::cout << "Запит 9 (Перелік викладачів, які брали іспити)\n";
    std::cout << "Запит 10 (Перелік студентів за викладачем, дисципліною, оцінкою)\n";
    std::cout << "Запит 11 (Перелік студентів та тем дипломних робіт)\n";
    std::cout << "Запит 12 (Перелік керівників дипломних робіт)\n";
    std::cout << "Запит 13 (Навантаження викладачів)\n";
    std::cout << "0. Вийти\n";
    std::cout << "Ваш вибір: ";
}

std::string lessonTypeToString(LessonType type) {
    switch (type) {
        case LessonType::Lecture: return "лекція";
        case LessonType::Seminar: return "практика";
        case LessonType::Lab: return "лабораторна";
        case LessonType::Consultation: return "консультація";
        case LessonType::Coursework: return "курсова";
        case LessonType::Other: return "інше";
        default: return "невідомо";
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Database db;
    db.loadFromFiles("./");

    int choice;
    do {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1; 
            continue;
        }

         switch (choice) {
case 1: {
            int subChoice;
            do {
                 std::cout << "\n=== Перелік і число студентів:===\n";
                std::cout << "1. За групою/курсами/факультетом\n";
                std::cout << "2. За статевою ознакою\n";
                std::cout << "3. За роком народження\n";
                std::cout << "4. За віком\n";
                std::cout << "5. За наявністю дітей\n";
                std::cout << "6. За наявністю і розміром стипендії\n";
                std::cout << "0. Назад\n";
                std::cout << "Ваш вибір: ";
                if (!(std::cin >> subChoice)) {
                    std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    subChoice = -1;
                    continue;
                }
                switch (subChoice) {
case 1: {
    std::vector<int> groupIds;
    int groupId;
    std::cout << "Введіть ID групи (0 - пропустити): ";
    std::cin >> groupId;

    int course;
    std::cout << "Введіть курс (0 - пропустити): ";
    std::cin >> course;

    int facultyId;
    std::cout << "Введіть ID факультету (0 - пропустити): ";
    std::cin >> facultyId;

    if (groupId != 0) {
        groupIds.push_back(groupId);
    } else if (course != 0 || facultyId != 0) {
        for (const auto& g : db.getGroups()) {
            if ((course == 0 || g.getCourse() == course) &&
                (facultyId == 0 || g.getFacultyId() == facultyId)) {
                groupIds.push_back(g.getId());
            }
        }
    }

    auto students = db.queryStudents(groupIds, {}, 0, "", 0, 0, 0, false, false, 0, 0);
    std::cout << "Знайдено студентів: " << students.size() << std::endl;
    for (const auto& s : students)
        std::cout << s.getInfo() << std::endl;
    break;
}
                case 2: { 
                    std::string gender;
                    std::cout << "Введіть стать (ч/ж): ";
                    std::cin >> gender;
                    auto students = db.queryStudents({}, {}, 0, gender, 0, 0, 0, false, false, 0, 0);
                    std::cout << "Знайдено студентів: " << students.size() << std::endl;
                    for (const auto& s : students) std::cout << s.getName() << "\n";
                    break;
                }
                case 3: {
                    int year;
                    std::cout << "Введіть рік народження: ";
                    if (!(std::cin >> year)) {
                        std::cout << "Невірний ввід.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                    auto students = db.queryStudents({}, {}, 0, "", year, 0, 0, false, false, 0, 0);
                    std::cout << "Знайдено студентів: " << students.size() << std::endl;
                    for (const auto& s : students) std::cout << s.getName() << "\n";
                    break;
                }
                case 4: {
                    int minAge, maxAge;
                    std::cout << "Введіть мінімальний вік (0 - пропустити): ";
                    if (!(std::cin >> minAge)) minAge = 0;
                    std::cout << "Введіть максимальний вік (0 - пропустити): ";
                    if (!(std::cin >> maxAge)) maxAge = 0;
                    auto students = db.queryStudents({}, {}, 0, "", 0, minAge, maxAge, false, false, 0, 0);
                    std::cout << "Знайдено студентів: " << students.size() << std::endl;
                    for (const auto& s : students) std::cout << s.getName() << "\n";
                    break;
                }
                case 5: {
                    int hasChildren;
                    std::cout << "Чи є діти? (1 - так, 0 - ні): ";
                    if (!(std::cin >> hasChildren)) hasChildren = 0;
                    auto students = db.queryStudents({}, {}, 0, "", 0, 0, 0, true, false, 0, 0);
                    std::cout << "Знайдено студентів: " << students.size() << std::endl;
                    for (const auto& s : students) std::cout << s.getName() << "\n";
                    break;
                }
                case 6: {
                    int hasScholarship;
                    double minS, maxS;
                    std::cout << "Чи є стипендія? (1 - так, 0 - ні): ";
                    if (!(std::cin >> hasScholarship)) hasScholarship = 0;
                    std::cout << "Мінімальна стипендія (0 - пропустити): ";
                    if (!(std::cin >> minS)) minS = 0;
                    std::cout << "Максимальна стипендія (0 - пропустити): ";
                    if (!(std::cin >> maxS)) maxS = 0;
                    auto students = db.queryStudents({}, {}, 0, "", 0, 0, 0, false, hasScholarship == 1, minS, maxS);
                    std::cout << "Знайдено студентів: " << students.size() << std::endl;
                    for (const auto& s : students) std::cout << s.getName() << "\n";
                    break;
                }
                case 0:
                    break;
                default:
                    std::cout << "Невірний вибір!\n";
                }
                    } while (subChoice != 0);
                        break;
        }
case 2: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік і число викладачів ===\n";
        std::cout << "1. За кафедрою\n";
        std::cout << "2. За факультетом\n";
        std::cout << "3. За категорією (асистент, доцент, професор)\n";
        std::cout << "4. За статевою ознакою\n";
        std::cout << "5. За роком народження\n";
        std::cout << "6. За віком\n";
        std::cout << "7. За наявністю та кількістю дітей\n";
        std::cout << "8. За розміром заробітної плати\n";
        std::cout << "9. Аспіранти\n";
        std::cout << "10. Захистили кандидатські у період\n";
        std::cout << "11. Захистили докторські у період\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        std::vector<int> departmentIds;
        int facultyId = 0;
        std::vector<TeacherCategory> categories;
        std::string gender;
        int birthYear = 0, minAge = 0, maxAge = 0;
        bool hasChildren = false;
        int minChildren = 0, maxChildren = 0;
        double minSalary = 0, maxSalary = 0;
        bool isPhdStudent = false, hasPhd = false, hasDoctor = false;

        switch (subChoice) {
        case 1: { 
            int depId;
            std::cout << "Введіть ID кафедри: ";
            if (!(std::cin >> depId)) depId = 0;
            if (depId > 0) departmentIds.push_back(depId);
            break;
        }
        case 2: { 
            std::cout << "Введіть ID факультету: ";
            std::cin >> facultyId;
            break;
        }
        case 3: { 
            int cat;
            std::cout << "Введіть категорію (0 - асистент, 1 - доцент, 2 - професор): ";
            if (!(std::cin >> cat)) cat = 0;
            categories.push_back(static_cast<TeacherCategory>(cat));
            break;
        }
        case 4: { 
            std::cout << "Введіть стать (ч/ж): ";
            std::cin >> gender;
            break;
        }
        case 5: {
            std::cout << "Введіть рік народження: ";
            std::cin >> birthYear;
            break;
        }
        case 6: {
            std::cout << "Мінімальний вік (0 - пропустити): ";
            std::cin >> minAge;
            std::cout << "Максимальний вік (0 - пропустити): ";
            std::cin >> maxAge;
            break;
        }
        case 7: {
            std::cout << "Чи є діти? (1 - так, 0 - ні): ";
            int has;
            std::cin >> has;
            hasChildren = (has == 1);
            std::cout << "Мінімум дітей (0 - пропустити): ";
            std::cin >> minChildren;
            std::cout << "Максимум дітей (0 - пропустити): ";
            std::cin >> maxChildren;

            auto teachers = db.queryTeachers(
                departmentIds, facultyId, categories, gender, birthYear,
                minAge, maxAge, hasChildren, minChildren, maxChildren,
                minSalary, maxSalary, isPhdStudent, hasPhd, hasDoctor
            );
            std::cout << "Знайдено викладачів: " << teachers.size() << std::endl;
            for (const auto& t : teachers)
                std::cout << t.getName() << " (кількість дітей - " << t.getChildrenCount() << ")" << std::endl;
            break;
        } 
        case 8: {
            std::cout << "Мінімальна зарплата (0 - пропустити): ";
            std::cin >> minSalary;
            std::cout << "Максимальна зарплата (0 - пропустити): ";
            std::cin >> maxSalary;

            auto teachers = db.queryTeachers(
                departmentIds, facultyId, categories, gender, birthYear,
                minAge, maxAge, hasChildren, minChildren, maxChildren,
                minSalary, maxSalary, isPhdStudent, hasPhd, hasDoctor
            );
            std::cout << "Знайдено викладачів: " << teachers.size() << std::endl;
            for (const auto& t : teachers)
                std::cout << t.getName() << " (зп - " << t.getSalary() << ")" << std::endl;
            break;
        }
        case 9: {
            isPhdStudent = true;
            break;
        }
        case 10: {
            hasPhd = true;
            break;
        }
        case 11: {
            hasDoctor = true;
            break;
        }
        case 0:
            continue;
        default:
            std::cout << "Невірний вибір!\n";
            continue;
        }
        auto teachers = db.queryTeachers(
            departmentIds, facultyId, categories, gender, birthYear,
            minAge, maxAge, hasChildren, minChildren, maxChildren,
            minSalary, maxSalary, isPhdStudent, hasPhd, hasDoctor
        );
        std::cout << "Знайдено викладачів: " << teachers.size() << std::endl;
        for (const auto& t : teachers) std::cout << t.getName() << "\n";

    } while (subChoice != 0);
    break;
}
case 3: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік тем дисертацій: підменю ===\n";
        std::cout << "1. За кафедрою, факультетом і типом дисертації\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            int departmentId, facultyId, thesisTypeInt;
            std::cout << "Введіть ID кафедри: ";
            if (!(std::cin >> departmentId)) break;
            std::cout << "Введіть ID факультету: ";
            if (!(std::cin >> facultyId)) break;
            std::cout << "Оберіть тип дисертації (0 - усі, 1 - кандидатські, 2 - докторські): ";
            if (!(std::cin >> thesisTypeInt)) thesisTypeInt = 0;
            DissertationType thesisType = static_cast<DissertationType>(thesisTypeInt);

            auto diss = db.queryDissertations(departmentId, facultyId, thesisType);
            std::cout << "Дисертацій: " << diss.size() << std::endl;
            for (const auto& d : diss)
                std::cout << d << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 4: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік кафедр: ===\n";
        std::cout << "1. За групою, курсом, факультетом, семестром\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (subChoice) {
        case 1: {
            int groupId, course, facultyId, semester;
            std::cout << "Введіть ID групи (0 - пропустити): ";
            if (!(std::cin >> groupId)) groupId = 0;
            std::cout << "Введіть курс (0 - пропустити): ";
            if (!(std::cin >> course)) course = 0;
            std::cout << "Введіть ID факультету (0 - пропустити): ";
            if (!(std::cin >> facultyId)) facultyId = 0;
            std::cout << "Введіть семестр (0 - пропустити): ";
            if (!(std::cin >> semester)) semester = 0;

            auto deps = db.queryDepartmentsForGroupCourseFacultySemester(groupId, course, facultyId, semester);
            std::cout << "Кафедр: " << deps.size() << std::endl;
            for (const auto& d : deps)
                std::cout << d.getName() << std::endl;
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 5: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік викладачів за дисципліною: ===\n";
        std::cout << "1. За дисципліною, групою, курсом, факультетом\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            int disciplineId, groupId, course, facultyId;
            std::cout << "Введіть ID дисципліни: ";
            if (!(std::cin >> disciplineId)) break;
            std::cout << "Введіть ID групи (0 - пропустити): ";
            if (!(std::cin >> groupId)) groupId = 0;
            std::cout << "Введіть курс (0 - пропустити): ";
            if (!(std::cin >> course)) course = 0;
            std::cout << "Введіть ID факультету (0 - пропустити): ";
            if (!(std::cin >> facultyId)) facultyId = 0;

            auto teachers = db.queryTeachersByDisciplineGroupCourseFaculty(disciplineId, groupId, course, facultyId);
            std::cout << "Викладачів: " << teachers.size() << std::endl;
            for (const auto& t : teachers) std::cout << t.getName() << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 6: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік викладачів за типом занять: ===\n";
        std::cout << "1. За типом заняття, групою, курсом, факультетом, семестром\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            int lessonTypeInt, groupId, course, facultyId, semester;
            std::cout << "Введіть тип заняття (0 - лекція, 1 - практика, 2 - лабораторна, 3 - консультація, 4 - курсова): ";
            if (!(std::cin >> lessonTypeInt)) break;
            LessonType lessonType;
            switch (lessonTypeInt) {
            case 0: lessonType = LessonType::Lecture; break;
            case 1: lessonType = LessonType::Seminar; break;
            case 2: lessonType = LessonType::Lab; break;
            case 3: lessonType = LessonType::Consultation; break;
            case 4: lessonType = LessonType::Coursework; break;
            default: lessonType = LessonType::Other; break;
            }
            std::cout << "Введіть ID групи (0 - пропустити): ";
            if (!(std::cin >> groupId)) groupId = 0;
            std::cout << "Введіть курс (0 - пропустити): ";
            if (!(std::cin >> course)) course = 0;
            std::cout << "Введіть ID факультету (0 - пропустити): ";
            if (!(std::cin >> facultyId)) facultyId = 0;
            std::cout << "Введіть семестр (0 - пропустити): ";
            if (!(std::cin >> semester)) semester = 0;

            auto teachers = db.queryTeachersByLessonType(lessonType, groupId, course, facultyId, semester);
            std::cout << "Викладачів: " << teachers.size() << std::endl;
            for (const auto& t : teachers) std::cout << t.getName() << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 7: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік студентів, які здали іспит/залік: ===\n";
        std::cout << "1. За групами, дисципліною, типом контролю, оцінкою\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            std::vector<int> groupIds;
            int groupId, disciplineId, controlTypeInt, mark;
            std::cout << "Введіть ID групи (0 - завершити введення груп): ";
            while (true) {
                if (!(std::cin >> groupId) || groupId == 0) break;
                groupIds.push_back(groupId);
                std::cout << "Ще групу? (ID або 0 для завершення): ";
            }
            std::cout << "Введіть ID дисципліни: ";
            if (!(std::cin >> disciplineId)) break;
            std::cout << "Введіть тип контролю (0 - іспит, 1 - залік): ";
            if (!(std::cin >> controlTypeInt)) controlTypeInt = 0;
            ControlType controlType = (controlTypeInt == 1) ? ControlType::Credit : ControlType::Exam;
            std::cout << "Введіть оцінку: ";
            if (!(std::cin >> mark)) break;

            auto students = db.queryStudentsByExam(groupIds, disciplineId, controlType, mark);
            std::cout << "Студентів: " << students.size() << std::endl;
            for (const auto& s : students) std::cout << s.getName() << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 8: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік студентів за результатами сесії: ===\n";
        std::cout << "1. За групами/курсами/факультетом та типом успішності\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            std::vector<int> groupIds, courses;
            int groupId, course, facultyId, filterType;
            std::cout << "Введіть ID групи (0 - завершити введення груп): ";
            while (true) {
                if (!(std::cin >> groupId) || groupId == 0) break;
                groupIds.push_back(groupId);
                std::cout << "Ще групу? (ID або 0 для завершення): ";
            }
            std::cout << "Введіть курс (0 - завершити введення курсів): ";
            while (true) {
                if (!(std::cin >> course) || course == 0) break;
                courses.push_back(course);
                std::cout << "Ще курс? (номер або 0 для завершення): ";
            }
            std::cout << "Введіть ID факультету (0 - пропустити): ";
            if (!(std::cin >> facultyId)) facultyId = 0;
            std::cout << "Оберіть тип фільтрації:\n";
            std::cout << "1. На відмінно\n";
            std::cout << "2. Без трійок\n";
            std::cout << "3. Без двійок\n";
            std::cout << "Ваш вибір: ";
            if (!(std::cin >> filterType)) filterType = 1;

            bool excellentOnly = (filterType == 1);
            bool noThrees = (filterType == 2);
            bool noTwos = (filterType == 3);

            auto students = db.queryStudentsBySession(groupIds, courses, facultyId, excellentOnly, noThrees, noTwos);
            std::cout << "Студентів: " << students.size() << std::endl;
            for (const auto& s : students) std::cout << s.getName() << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 9: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік викладачів, які брали іспити: ===\n";
        std::cout << "1. За групами, дисциплінами, семестром\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            std::vector<int> groupIds, disciplineIds;
            int groupId, disciplineId, semester;
            std::cout << "Введіть ID групи (0 - завершити введення груп): ";
            while (true) {
                if (!(std::cin >> groupId) || groupId == 0) break;
                groupIds.push_back(groupId);
                std::cout << "Ще групу? (ID або 0 для завершення): ";
            }
            std::cout << "Введіть ID дисципліни (0 - завершити введення дисциплін): ";
            while (true) {
                if (!(std::cin >> disciplineId) || disciplineId == 0) break;
                disciplineIds.push_back(disciplineId);
                std::cout << "Ще дисципліну? (ID або 0 для завершення): ";
            }
            std::cout << "Введіть семестр (0 - пропустити): ";
            if (!(std::cin >> semester)) semester = 0;

            auto teachers = db.queryTeachersTakingExams(groupIds, disciplineIds, semester);
            std::cout << "Викладачів: " << teachers.size() << std::endl;
            for (const auto& t : teachers) std::cout << t.getName() << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 10: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік студентів за викладачем, дисципліною, оцінкою: ===\n";
        std::cout << "1. За групами, викладачем, дисциплінами, оцінкою, семестрами, періодом\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            std::vector<int> groupIds, disciplineIds, semesters;
            int groupId, teacherId, disciplineId, mark, semester, periodStart, periodEnd;
            std::cout << "Введіть ID групи (0 - завершити введення груп): ";
            while (true) {
                if (!(std::cin >> groupId) || groupId == 0) break;
                groupIds.push_back(groupId);
                std::cout << "Ще групу? (ID або 0 для завершення): ";
            }
            std::cout << "Введіть ID викладача (0 - пропустити): ";
            if (!(std::cin >> teacherId)) teacherId = 0;
            std::cout << "Введіть ID дисципліни (0 - завершити введення дисциплін): ";
            while (true) {
                if (!(std::cin >> disciplineId) || disciplineId == 0) break;
                disciplineIds.push_back(disciplineId);
                std::cout << "Ще дисципліну? (ID або 0 для завершення): ";
            }
            std::cout << "Введіть оцінку (0 - пропустити): ";
            if (!(std::cin >> mark)) mark = 0;
            std::cout << "Введіть семестр (0 - завершити введення семестрів): ";
            while (true) {
                if (!(std::cin >> semester) || semester == 0) break;
                semesters.push_back(semester);
                std::cout << "Ще семестр? (номер або 0 для завершення): ";
            }
            std::cout << "Введіть початок періоду (рік, 0 - пропустити): ";
            if (!(std::cin >> periodStart)) periodStart = 0;
            std::cout << "Введіть кінець періоду (рік, 0 - пропустити): ";
            if (!(std::cin >> periodEnd)) periodEnd = 0;

            auto students = db.queryStudentsByTeacherDisciplineMarkSemesterPeriod(
                groupIds, teacherId, disciplineIds, mark, semesters, periodStart, periodEnd
            );
            std::cout << "Студентів: " << students.size() << std::endl;
            for (const auto& s : students) std::cout << s.getName() << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 11: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік студентів і тем дипломних робіт: ===\n";
        std::cout << "1. За кафедрою\n";
        std::cout << "2. За викладачем\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            int departmentId;
            std::cout << "Введіть ID кафедри: ";
            if (!(std::cin >> departmentId)) break;
            auto pairs = db.queryStudentsAndTheses(departmentId, 0);
            std::cout << "Записів: " << pairs.size() << std::endl;
            for (const auto& p : pairs)
                std::cout << p.first.getName() << " - " << p.second << "\n";
            break;
        }
        case 2: {
            int teacherId;
            std::cout << "Введіть ID викладача: ";
            if (!(std::cin >> teacherId)) break;
            auto pairs = db.queryStudentsAndTheses(0, teacherId);
            std::cout << "Записів: " << pairs.size() << std::endl;
            for (const auto& p : pairs)
                std::cout << p.first.getName() << " - " << p.second << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 12: {
    int subChoice;
    do {
        std::cout << "\n=== Перелік керівників дипломних робіт: ===\n";
        std::cout << "1. За кафедрою\n";
        std::cout << "2. За факультетом\n";
        std::cout << "3. За категорією викладача\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            int departmentId;
            std::cout << "Введіть ID кафедри: ";
            if (!(std::cin >> departmentId)) break;
            auto teachers = db.queryThesisSupervisors(departmentId, 0, {});
            std::cout << "Керівників: " << teachers.size() << std::endl;
            for (const auto& t : teachers) std::cout << t.getName() << "\n";
            break;
        }
        case 2: {
            int facultyId;
            std::cout << "Введіть ID факультету: ";
            if (!(std::cin >> facultyId)) break;
            auto teachers = db.queryThesisSupervisors(0, facultyId, {});
            std::cout << "Керівників: " << teachers.size() << std::endl;
            for (const auto& t : teachers) std::cout << t.getName() << "\n";
            break;
        }
        case 3: {
            std::vector<TeacherCategory> categories;
            int cat;
            std::cout << "Введіть категорію (0 - асистент, 1 - доцент, 2 - професор, 3 - завершити): ";
            while (std::cin >> cat && cat != 3) {
                categories.push_back(static_cast<TeacherCategory>(cat));
                std::cout << "Ще категорію? (номер або 3 для завершення): ";
            }
            auto teachers = db.queryThesisSupervisors(0, 0, categories);
            std::cout << "Керівників: " << teachers.size() << std::endl;
            for (const auto& t : teachers) std::cout << t.getName() << "\n";
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
case 13: {
    int subChoice;
    do {
        std::cout << "\n=== Навантаження викладачів: ===\n";
        std::cout << "1. За викладачем\n";
        std::cout << "2. За кафедрою\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш вибір: ";
        if (!(std::cin >> subChoice)) {
            std::cout << "Невірний ввід. Будь ласка, введіть число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            subChoice = -1;
            continue;
        }
        switch (subChoice) {
        case 1: {
            int teacherId, semester;
            std::cout << "Введіть ID викладача: ";
            if (!(std::cin >> teacherId)) break;
            std::cout << "Введіть семестр (0 - всі): ";
            if (!(std::cin >> semester)) semester = 0;
            auto loads = db.queryTeacherLoad(teacherId, 0, semester);
            std::cout << "Навантажень: " << loads.size() << std::endl;
            for (const auto& l : loads) {
            std::cout << std::get<0>(l) << " - " << std::get<1>(l) << " годин (" << lessonTypeToString(std::get<2>(l)) << ")\n";
            }
            break;
        }
        case 2: {
            int departmentId, semester;
            std::cout << "Введіть ID кафедри: ";
            if (!(std::cin >> departmentId)) break;
            std::cout << "Введіть семестр (0 - всі): ";
            if (!(std::cin >> semester)) semester = 0;
            auto loads = db.queryTeacherLoad(0, departmentId, semester);
            std::cout << "Навантажень: " << loads.size() << std::endl;
            for (const auto& l : loads) {
                std::cout << std::get<0>(l) << " - " << std::get<1>(l) << " годин (" << lessonTypeToString(std::get<2>(l)) << ")\n";
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
    break;
}
        case 0:
            std::cout << "Вихід з програми.\n";
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (choice != 0);

    return 0;
}