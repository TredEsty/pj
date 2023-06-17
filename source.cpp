#include<string>
#include<vector>
#include<unordered_set>
#include<iostream>
#include<fstream>
#include<sstream>
#include<filesystem>
#include<regex>
//#include <pj.h>
#include<stdlib.h>

#include "projectMethods.h"




std::string extractNumberFromString(const std::string& str) {
    std::regex regex("\\d+"); // Match one or more digits
    std::smatch match;
    
    if (std::regex_search(str, match, regex)) {
        std::string numericPart = match.str(); // Get the matched substring
        return numericPart; // Return the string representation of the number
    }
    
    return ""; // Return an empty string if no match found
}
/*

void readData(Program* obj) {

    
    std::filesystem::path parentPath = std::filesystem::current_path(); // Assuming the parent folder is the current working directory
    std::string programFolderName;

    // Gets the name of the Program folder
    if (std::filesystem::is_directory(parentPath)) {
        std::filesystem::directory_iterator it(parentPath);
        if (it != std::filesystem::directory_iterator()) {
            programFolderName = it->path().filename().string(); // Contains the name of the Program folder
            obj->changeProgramName(programFolderName);
        }
    }

    
        const std::string filename = "/"+ programFolderName +"/curriculum.csv";

        std::ifstream file(filename);
        if (!file) {
            std::cout << "Failed to open the file: " << filename << std::endl;
            return;
        }

        std::string line;
        int semester = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;

            // Read semester number from the line
            if (std::getline(ss, cell, ',')) {
                semester = std::stoi(cell);//makes the first row of a line int and store it in semestre 
            }

            std::string subjectName;
            float credits;
            bool isSubjectName = true; //flag if the row cell is string(SubjectName) or int(credits) 

            while (std::getline(ss, cell, ',')) {
                if (!cell.empty()) { 
                    if (isSubjectName) {
                        subjectName = cell;
                    } else {
                        credits = std::stof(cell);
                        Subject subject(subjectName, credits);
                        obj->addSubject(semester, subject);
                        std::cout<<subjectName<<" "<<credits;
                    }
                    isSubjectName = !isSubjectName; 
                }
            }
        }

        file.close();


    std::filesystem::path studentsPath = parentPath / programFolderName / "students";
    
    for (const auto& entry : std::filesystem::directory_iterator(studentsPath)) {
        if (entry.is_directory()) {
            std::string studentFolderName = entry.path().filename().string();

            //citim din programFolder+"/students/"+studentFolderName+"/studentData.csv" si construim un obiect Student pe care il denumim "student1, student2 ..."
            //trebuie sa bagi obiectul studentX in unordered set-ul lui obj
            //Student student1(obj, id, firstname, lastname)
            //id-ul studentului va veni dupa numarul din folder ex folderul studentului e student132 atunci id-ul obiectului student132 de clasa Student va fi 132

            std::string id=extractNumberFromString(studentFolderName);
            
            std::ifstream file("/"+programFolderName+"/students"+"/studentdata.csv");
            if (!file) {
                std::cout << "Failed to open the file: " << filename << std::endl;
                return;
            }

            std::istringstream iss(line);

            std::string firstName;
            std::string lastName;

            if (iss >> firstName >> lastName >> semester)  { //citeste first line-ul si pune in variabile coloanele
                
            } 
            else {
                std::cout << "Failed to read data from the file." << std::endl;
            }

            
            file.close();

            Student student(obj ,id,firstName,lastName , semester);

            obj->addStudent(student); //aici cred ca ar trebui sa bagam student in obj dupa ce bagam si subjects in student   




            std::filesystem::path subjectsPath = parentPath / programFolderName / "students" / studentFolderName / "subjects";

            //selectam din folderul subjects, fisierul csv corespunzator semestrului in care se afla studentul
            //ex student1.getSemester()==3 atunci student.insertSemester(unordered_set<Subject> subjects)
            //subjects va fi lista creata dupa citirea din fisier a datelor semestrului respectiv

            std::unordered_set<Subject> subjects; // subiectele din semestrul in care studentul se afla
            
            semester=student.getSemester();
            std::ifstream file3(programFolderName+ "/students/"+studentFolderName +"/subjects" "/sem" + std::to_string(semester) + ".csv"); 

            if (!file3) {
                std::cout << "Failed to open the file." << std::endl;

            }

            Subject temp ; //subject temporar

            std::string line;
            while ( std::getline( file, line) ) {
               
                temp.updateSubjectName(line);
                subjects.insert(temp);
 
            } 
            file3.close(); 

            student.addSubjects(subjects);
        }
    }
}

void writeData(Program *obj)
{
    //change the name of the folder Program
    std::filesystem::path parentPath = std::filesystem::current_path();
    std::string programFolderName;
    std::string newFolderName;
    // Gets the name of the Program folder
    if (std::filesystem::is_directory(parentPath)) {  //verificam daca folderul cu numele programului e acelasi cu numele programului din obj si daca nu e schimbam numele folderului dupa numele programului obj
        std::filesystem::directory_iterator it(parentPath);
        if (it != std::filesystem::directory_iterator()) {
            programFolderName = it->path().filename().string(); // Contains the name of the Program folder
            newFolderName = obj->getName(); // Specify the new folder name

            std::filesystem::path oldFolderPath = parentPath / programFolderName;
            std::filesystem::path newFolderPath = parentPath / newFolderName;

            if (!std::filesystem::exists(newFolderPath)) {
                std::error_code ec;
                std::filesystem::rename(oldFolderPath, newFolderPath, ec);
                if (ec) {
                    std::cout << "Failed to rename the folder: " << ec.message() << std::endl;
                } else {
                    std::cout << "Folder renamed successfully." << std::endl;
                }
            } else {
                std::cout << "A folder with the new name already exists." << std::endl;
            }
        }
    }

    //Write in curiculum.csv

    std::ofstream file("curriculum.csv");
    if (!file) {
        std::cout << "Failed to open the file: " << "curiculum.csv" << std::endl;
        return;
    }
    else{
        for(int j=1;j<=6;j++) //go through all the semesters
           {
            file<<j<<","; //put the number of the semester on the first row

            for(Subject temp : obj->getSubjectsForASemester(j)){

               file<<temp.getSubjectName()<<","<<temp.getCredits()<<",";  //put the name of the subject then the credits 
            }
            file<<std::endl; //dupa ce toate subiectele si creditele pt un semestru s-au scris trecem la rand nou pentru urmatorul semestru

           }

           file.close();
    }
    
    //cumva trebuie creat folderul cu student+id si apoi deschis mai jos in loc de "studentPath/studentdata.csv"

   
    for(Student temp : obj->getStudents())
    {
       
        std::string folderName = "student"+temp.getID(); //numele folderelor student+id

        std::filesystem::path folderPath("/"+programFolderName + "/students/" + folderName);

        if (std::filesystem::exists(folderPath)) {
            std::cout << "Folder already exists." << std::endl; 
        } else {
            if (std::filesystem::create_directories("/"+programFolderName + "/students/" + folderName)) { 
                //se creeaza folderul student+id daca nu exista
            } else {
                std::cout << "Failed to create the folder structure." << std::endl;
            }
        }

        std::ofstream studentData(programFolderName+"/students"+folderName+"/studentdata.csv");
        if (!studentData) {
            std::cout << "Failed to open the file: "  << std::endl;
        }
        else{
            studentData<<temp.getFirstName()<<","<<temp.getLastName()<<","<<temp.getSemester()<<std::endl;
        }

        studentData.close();
        
        
        
        std::string semester ="sem"+ std::to_string(temp.getSemester())+ ".csv";

        std::ofstream semfile(programFolderName+"/students"+folderName+"/"+semester);
        if (!semfile) {
            std::cout << "Failed to open the file: "  << std::endl;
        }
        else{
            for(Subject temp : obj->getSubjectsForASemester(temp.getSemester()))
            {
                semfile<<temp.getSubjectName()<<std::endl;
            }
        }

        studentData.close();


    }


}
*/

void viewSubjects(Program *program) {

}

void showStudents(Program *program) {

}

void searchStudent(Program *program) {

}

void addStudent(Program *program) {
    using namespace std;

    int ID = program->getStudents().back().getID() + 1;
    string firstName;
    string lastName;
    


    system("clear");

    std::cout << "Enter information:" << std::endl << "(Student will be created as a first year, first semester student)" << std::endl;    

    cout << "First name:"; cin >> firstName;
    cout << "Last name:"; cin >> lastName;
    Student newStudent(program, ID, firstName, lastName, 1);
    program->addStudent(newStudent);

    cout << "Processed finished!" << endl << "Press enter to go to the main menu";
}

void saveChanges(Program *program) {

}

void interface(Program *program) {
    using namespace std;
    int opt;
    while(1) {
        system("clear");

        cout << "University Program Managing Tool" << endl;
        cout << "Program name: "<<program->getName() << endl<<endl;
        cout << "Options:" << endl << endl;

        cout << "1. View the subjects for this program" << endl;
        cout << "2. Show all students" << endl;
        cout << "3. Search for a student" << endl;
        cout << "4. Add for a student" << endl;
        cout << "5. Save changes" << endl;
        cout << "0. Exit" << endl;

        cin >> opt;

        switch(opt) {
            case 0:
                exit(1);
            case 1:
                viewSubjects(program);
            case 2:
                showStudents(program);
            case 3:
                searchStudent(program);
            case 4:
                addStudent(program);
            case 5:
                saveChanges(program);
            default:
                cout << "\n1..7!";
        }
        return;
    }
}

int main() {
    Program program;

    interface(&program);


}
