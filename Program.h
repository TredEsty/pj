#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

class Student;
class Subject;

class Program {
private:
    std::string name;
    std::vector<Student> students;
    std::unordered_set<Subject> subjectsForSem1;
    std::unordered_set<Subject> subjectsForSem2;
    std::unordered_set<Subject> subjectsForSem3;
    std::unordered_set<Subject> subjectsForSem4;
    std::unordered_set<Subject> subjectsForSem5;
    std::unordered_set<Subject> subjectsForSem6;

public:
    // Constructor
    Program() : name("") {}

    //Deconstructor
    ~Program() {}

    // Accessor methods
    std::string getName() const;
    std::vector<Student> getStudents() const;
    std::vector<Student*> searchStudent(int ID = -1, const std::string& firstname = "", const std::string& lastname = "", int semester = -1) const;
    std::unordered_set<Subject> getSubjectsForASemester(int s) const;

    // Update methods
    void addSubject(int s, Subject subject);
    void changeProgramName(const std::string& newname);
    void addStudent(Student h);

    // Other methods
    int getNumberOfStudentsInProgram() const;
};