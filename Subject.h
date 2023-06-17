#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <functional>


class Subject{
private:
    std::string name;
    float LT1;//grade at lab test 1
    float LT2;//grade at lab test 2
    float MTE;//grade at course midterm
    float FE;//grade at final exam
    int labAttendance;
    int courseAttendance;


public:

//constructor

    Subject(
        const std::string& name = "",
        float LT1 = -1,
        float LT2 = -1,
        float MTE = -1,
        float FE = -1,
        int labAttendance = 0,
        int courseAttendance = 0
    )
    : name(name),
    LT1(LT1),
    LT2(LT2),
    MTE(MTE),
    FE(FE),
    labAttendance(labAttendance),
    courseAttendance(courseAttendance) {}

//copy constructor
    Subject(const Subject& other)
        : name(other.name),
        LT1(other.LT1),
        LT2(other.LT2),
        MTE(other.MTE),
        FE(other.FE),
        labAttendance(other.labAttendance),
        courseAttendance(other.courseAttendance)
    {
        // Additional initialization or deep copying if needed
    }


//deconstructor

    ~Subject() {}

//operator overloading

    bool operator==(const Subject& other) const {
        // Compare the relevant attributes of the objects
        return name == other.name;
    }

//accessor methods

    std::string getSubjectName() const{
        return name;
    }

    float getLT1() const{
        return LT1;
    }

    float getLT2() const{
        return LT2;
    }

    float getMTE() const{
        return MTE;
    }

    float getFE(){
        return FE;
    }
    
    int getLabAttendance() const{
        return labAttendance;
    }

    int getCourseAttendance() const{
        return courseAttendance;
    }

    

//update methods

    void updateSubjectName(const std::string& name){
        this->name=name;
    }

    void updateLT1(float LT1){
        this->LT1=LT1;
    }

    void updateLT2(float LT2){
        this->LT2=LT2;
    }

    void updateMTE(float MTE){
        this->MTE=MTE;
    }

    void updateFE(float FE){
        this->FE=FE;
    }
    
    void updateLabAttendance(int labAttendance){
        this->labAttendance=labAttendance;
    }

    void updateCourseAttendance(int courseAttendance){
        this->courseAttendance=courseAttendance;
    }

    Subject resetSubject() {
        Subject obj=Subject(name);

        return obj;
    }

//other methods

    float getLabGrade() const{
        return (LT1+LT2)/2;
    }

    float getFinalGrade() const{
        if(FE==-1){
            return -1;//will print N/A
        }
        else
            return (this->getLabGrade()*0.3 + MTE*0.2 + FE*0.5);
    }

    bool examEntrance(){
        if(labAttendance>=10 && courseAttendance>=5 && getLabGrade() >=5)
            return true;//will be able to enter exam
        return false;//will not be able to enter exam
    }

    bool passStatus(){
        if(getFinalGrade()>=5){
            return true;
        }
        else{
            return false;
        }
    }
    int getCredits() const {
        return 5*getFinalGrade();
    }

    friend struct std::hash<Subject>;
};