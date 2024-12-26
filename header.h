#define INFOSTUDENT_H
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cctype>
using namespace std;

struct Score {
    float CA, SS, WEB, BR, CPP;

    float getAverage(){
        float sum = 0;
         sum = CA + SS + WEB + BR + CPP;
         return (sum)/5.0;
    }
    char calculateGrade(){
        float avg = getAverage();
        if (avg >= 90) return 'A';
        if (avg >= 80) return 'B';
        if (avg >= 70) return 'C';
        if (avg >= 60) return 'D';
        if (avg >= 50) return 'E';
        return 'F';
    }
};

class Student {
public:
    int id;
    float avg;
    string name, gender, dob, pob, major;
    Score scores;
    char grade;
    bool isDeleted;
    Student* next;

    Student() : id(0), avg(0), grade('F'), isDeleted(false), next(nullptr) {}

    void calculateStats() {
        avg = scores.getAverage();
        grade = scores.calculateGrade();
    }

    void displayInfo() {
        if (isDeleted) return;
        cout << "| " << setw(10) << left << id
             << " | " << setw(15) << left << name
             << " | " << setw(10) << avg
             << " | " << setw(5) << grade
             << " | " << setw(12) << dob
             << " | " << setw(15) << pob
             << " | " << setw(10) << major << "|\n";
    }
};

class StudentList {
private:
    Student* head;
    const string fileName = "datastudent.txt";
public:
    StudentList() : head(nullptr) {}

    ~StudentList() { clearList(); }

    void clearList() {
        Student* current = head;
        while (current) {
            Student* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
    void addStudent(Student& st) {
        Student* newStudent = new Student(st);
        newStudent->calculateStats();
        newStudent->next = head;
        head = newStudent;
    }

    void searchStudent( string& keyword) const {
        cout << "Search Results:\n";
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "| Student ID | Name           | Average   | Grade | Date of Birth | POB           |Major         |\n";
        cout << "-------------------------------------------------------------------------------------------------\n";
        Student* current = head;
        bool found = false;
        while (current) {
            if (!current->isDeleted &&
                (current->name == keyword || to_string(current->id) == keyword)) {
                current->displayInfo();
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            cout << "| No matching student found.\n";
        }
        cout << "----------------------------------------------------------------------------------------------\n";
    }

    void displayAllStudents() {
        cout << "All Students Information:\n";
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "| Student ID | Name           | Average   | Grade | Date of Birth | POB           |Major         |\n";
        cout << "-------------------------------------------------------------------------------------------------\n";
        Student* current = head;
        while (current) {
            if (!current->isDeleted) {
                current->displayInfo();
            }
            current = current->next;
        }
        cout <<"-----------------------------------------------------------------------------------------------\n";
    }
    void removeStudent(int id) {
        if (!head) {
            cout << "List is empty, nothing to remove.\n";
            return;
        }
        if (head->id == id) {
            Student* temp = head;
            head = head->next;
            delete temp;
            cout << "Student with ID " << id << " removed successfully.\n";
            return;
        }

        Student* current = head;
        Student* previous = nullptr;

        while (current && current->id != id) {
            previous = current;
            current = current->next;
        }

        if (!current) {
            cout << "Student with ID " << id << " not found.\n";
            return;
        }

        previous->next = current->next;
        delete current;
        cout << "Student with ID " << id << " removed successfully.\n";
    }
    void sortStudentsByID(){
    if (!head || !head->next){
        return;
    }
    bool swapped;
    do {
        swapped = false;
        Student*current = head;
        while (current ->next ){
            if (current->id > current->next->id){
                swap(current  ->id , current->next->id);
                swap(current->name, current->next->name);
                swap(current->gender, current->next->gender);
                swap(current->dob, current->next->dob);
                swap(current->pob, current->next->pob);
                swap(current->major, current->next->major);
                swap(current->scores, current->next->scores);
                swap(current->avg, current->next->avg);
                swap(current->grade, current->next->grade);
                swap(current->isDeleted,current->next->isDeleted);
                swapped= true;
            }
            current= current->next;
        }
    } while (swapped);
}
void editStudent() {
    int Id;
    cout << "Enter the ID of the student to edit: ";
    cin >> Id;
    Student *current = head;
    while (current) {
        if (current->id == Id) {
            cout << "Student found. What do you want to edit?\n";
            cout << "1. Name\n";
            cout << "2. Scores\n";
            cout << "3. Date of birth\n";
            cout << "4. Place of birth\n";
            cout << "5. Exit\n";

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    string newName;
                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, newName);
                    current->name = newName;
                    cout << "Name updated successfully.\n";
                    break;
                }
                case 2: {

                cout << "Enter new scores:\n";
                cout << "Computer Architecture: ";
                float score;
                cin >> score;
                if (score >= 0) current->scores.CA = score;

                cout << "Soft Skill: ";
                cin >> score;
                if (score >= 0) current->scores.SS = score;

                cout << "Web Design: ";
                cin >> score;
                if (score >= 0) current->scores.WEB = score;

                cout << "Basic Robot: ";
                cin >> score;
                if (score >= 0) current->scores.BR = score;

                cout << "Advanced Algorithm: ";
                cin >> score;
                if (score >= 0) current->scores.CPP = score;
                current->grade = current->scores.calculateGrade();
                break;
                }
                case 3: {
                    string newdob;
                    cout << "Enter New Dob: ";
                    cin >> newdob;
                    current->dob = newdob;
                    cout << "Dob updated successfully.\n";
                    break;
                }
                case 4: {
                    string newpob;
                    cout << "Enter new grade: ";
                    cin >> newpob;
                    current->pob = newpob;
                    cout << "Pob updated successfully.\n";
                    break;
                }
                case 5:
                    cout << "Exiting edit menu.\n";
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
            saveToFile();
            
            return;
        }
        current = current->next;
    }

    cout << "Student with ID " << Id << " not found.\n";
}
  void saveToFile() {
        ofstream file(fileName);
        if (file.is_open()) {
            file << left << setw(10) << "ID"
                 << left << setw(15) << "Name"
                 << left << setw(10) << "Average"
                 << left << setw(5) << "Grade"
                 << left << setw(12) << "DOB"
                 << left << setw(15) << "POB"
                 << left << setw(15) << "Major" << "\n";
            file << "-------------------------------------------------------------------------------------------------\n";
            Student* current = head;
            while (current) {
                if (!current->isDeleted) {
                    file << left << setw(10) << current->id
                         << left << setw(15) << current->name
                         << left << setw(10) << fixed << setprecision(2) << current->avg
                         << left << setw(5) << current->grade
                         << left << setw(12) << current->dob
                         << left << setw(15) << current->pob
                         << left << setw(15) << current->major << "\n";
                }
                current = current->next;
            }
            file.close();
        } 
            
    }
void loadFromFile() {
    clearList(); 
    ifstream file(fileName); 
    if (file.is_open()) {
        Student student; 
        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            addStudent(student);
        }
        file.close();
    } else {
        cout << "Failed to open file for reading.\n";
    }
}

};
