#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <functional>

class Subject;
class Program;

class Student {
private:
    int ID;
    std::string firstName;
    std::string lastName;

    Program* program;
    std::unordered_set<Subject> subjects; // Store subjects for each semester
    int semester;

    bool startedUniversity;
    bool finishedUniversity;

public:
    // Constructor
    Student(
        Program* program = nullptr,
        int ID = -1,
        const std::string& firstName = "",
        const std::string& lastName = "",
        int semester = 1,
        bool startedUniversity = false
    );

    // Copy constructor
    Student(const Student& other);

    // Destructor
    ~Student();

    // Accessor methods
    int getID() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    int getSemester() const;
    std::unordered_set<Subject> getSubjects() const;

    // Update methods
    void addSubjects(const std::unordered_set<Subject>& subjects);

    // Other methods
    struct StudentComparison;

    void updateSemester();
};