#include<string>
#include<vector>
#include<unordered_set>
#include<iostream>
#include<functional>

#include "Student.h"
#include "Program.h"
#include "Subject.h"

//STUDENT METHODS ------------------

// Constructor
Student::Student(
    Program* program,
    int ID,
    const std::string& firstName,
    const std::string& lastName,
    int semester,
    bool startedUniversity
)
    : program(program),
      ID(ID),
      firstName(firstName),
      lastName(lastName),
      semester(semester),
      finishedUniversity(false)
{
    if (startedUniversity == false)
        this->subjects = program->getSubjectsForASemester(semester);
    startedUniversity = true;
}

// Copy constructor
Student::Student(const Student& other)
{
    // Copy the values of private members from the other object
    this->ID = other.ID;
    this->firstName = other.firstName;
    this->lastName = other.lastName;
    this->program = other.program;
    this->subjects = other.subjects;
    this->semester = other.semester;
    this->finishedUniversity = other.finishedUniversity;
}

// Destructor
Student::~Student() {}

// Accessor methods
int Student::getID() const {
    return ID;
}

std::string Student::getFirstName() const {
    return firstName;
}

std::string Student::getLastName() const {
    return lastName;
}

int Student::getSemester() const {
    return semester;
}

std::unordered_set<Subject> Student::getSubjects() const {
    return subjects;
}

// Update methods
void Student::addSubjects(const std::unordered_set<Subject>& newSubjects) {
    subjects = newSubjects;
}


// Other methods
struct Student::StudentComparison {

    StudentComparison(int ID, const std::string& firstName, const std::string& lastName, int semester)
        : ID(ID), firstName(firstName), lastName(lastName), semester(semester) {}

    bool operator()(const Student* s1, const Student* s2) const {
        int score1 = calculateSimilarityScore(s1);
        int score2 = calculateSimilarityScore(s2);
        return score1 > score2;
    }

    int calculateSimilarityScore(const Student* s) const {
        int score = 0;
        if (s->getID() == ID)
            score += 3;
        if (s->getFirstName() == firstName)
            score += 2;
        if (s->getLastName() == lastName)
            score += 2;
        if (s->getSemester() == semester)
            score += 1;
        return score;
    }

    int ID;
    std::string firstName;
    std::string lastName;
    int semester;
};

void Student::updateSemester() {
    std::unordered_set<Subject> nextSemesterSubjects;
    std::unordered_set<Subject> notPassedSubjects;

    int totalCredits=0;
    bool passedAll=1;

    for (auto subject : subjects) {
        if (!subject.passStatus()) {
            notPassedSubjects.insert(subject.resetSubject());
        }
        else {
            totalCredits+=subject.getCredits();
        }
    }
    if (totalCredits >= 120){
        semester++;
        switch (semester) {
        case 2:
            nextSemesterSubjects = program->getSubjectsForASemester(2);
            break;
        case 3:
            nextSemesterSubjects = program->getSubjectsForASemester(3);
            break;
        case 4:
            nextSemesterSubjects = program->getSubjectsForASemester(4);
            break;
        case 5:
            nextSemesterSubjects = program->getSubjectsForASemester(5);
            break;
        case 6:
            nextSemesterSubjects = program->getSubjectsForASemester(6);
            break;
        case 7:
            finishedUniversity=1;//yay
            break;
        default:
            std::cout << "Invalid semester for student: " << ID << std::endl;
            return;
        }

        if (!nextSemesterSubjects.empty()) {
            ++semester;
            subjects = nextSemesterSubjects;
            subjects.insert(notPassedSubjects.begin(), notPassedSubjects.end());
        } else {
            // Reset subjects if no subjects are available for the next semester
            subjects.clear();
        }
    }
    else {
        for (auto it = subjects.begin(); it != subjects.end(); ++it) {
            Subject& subject = const_cast<Subject&>(*it);
            subject = subject.resetSubject();
        }
    }
}

//PROGRAM METHODS -----------------

// Accessor methods
std::string Program::getName() const {
    return name;
}

std::vector<Student> Program::getStudents() const {
    return students;
}

std::vector<Student*> Program::searchStudent(int ID, const std::string& firstname, const std::string& lastname, int semester) const {
    std::vector<Student*> found;

    for (auto& s : students) {
        if ((s.getID() == ID) || (s.getFirstName() == firstname) || (s.getLastName() == lastname) || (s.getSemester() == semester)) {
            found.push_back(const_cast<Student*>(&s));
        }
    }

    std::sort(found.begin(), found.end(), Student::StudentComparison(ID, firstname, lastname, semester));


    return found;
}


std::unordered_set<Subject> Program::getSubjectsForASemester(int s) const {
    switch (s) {
        case 1:
            return subjectsForSem1;
        case 2:
            return subjectsForSem2;
        case 3:
            return subjectsForSem3;
        case 4:
            return subjectsForSem4;
        case 5:
            return subjectsForSem5;
        case 6:
            return subjectsForSem6;
    }
    return {};
}

// Update methods
void Program::addSubject(int s, Subject subject) {
    switch (s) {
        case 1:
            subjectsForSem1.insert(subject);
            break;
        case 2:
            subjectsForSem2.insert(subject);
            break;
        case 3:
            subjectsForSem3.insert(subject);
            break;
        case 4:
            subjectsForSem4.insert(subject);
            break;
        case 5:
            subjectsForSem5.insert(subject);
            break;
        case 6:
            subjectsForSem6.insert(subject);
            break;
    }
}

void Program::changeProgramName(const std::string& newname) {
    name = newname;
}

void Program::addStudent(Student h) {
    students.push_back(h);
}

// Other methods
int Program::getNumberOfStudentsInProgram() const {
    return students.size();
}