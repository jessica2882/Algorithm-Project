#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cctype>
#include "header.h"
int main() {
  StudentList studentList;
    StudentList LoadFromFile();
    int numStudent ;
    int currentStudent = 0;
    int choice;
    do {
        cout << "--------------------------------------------------------\n";
        cout << "                    Student System                      \n";
        cout << "--------------------------------------------------------\n";
        cout << "1. Add a new student\n";
        cout << "2. Search for a student by name or ID\n";
        cout << "3. Display all students\n";
        cout << "4. Delete a student by ID\n";
        cout << "5. Edit Info Students\n";
        cout << "0. Exit the program\n";
        cout << "---------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                Student st;
                cout<<"------------------------------------------"<<endl;
                cout<<"              1.Add new student           "<<endl;
                cout<<"------------------------------------------"<<endl;
                cout<<"How many student do you want to add?      "<<endl;
                cout << "Please Enter:";
                cin >> numStudent;
                for (int i = 1;i<= numStudent ;i++){
                cout<<"           Info of Student:"<< i <<endl;
                cout<<"-------------------------------------\n"<<endl;
                cout << "Enter Student ID: ";
                cin >> st.id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, st.name);
                cout << "Enter Gender: ";
                getline(cin, st.gender);
                cout << "Enter Date of Birth: ";
                getline(cin, st.dob);
                cout << "Enter Place of Birth: ";
                getline(cin, st.pob);
                cout << "Enter Major: ";
                getline(cin, st.major);

                cout << "Enter Computer Architecture Score: ";
                cin >> st.scores.CA;
                cout << "Enter Soft Skill Score: ";
                cin >> st.scores.SS;
                cout << "Enter Web Design Score: ";
                cin >> st.scores.WEB;
                cout << "Enter Basic Robot Score: ";
                cin >> st.scores.BR;
                cout << "Enter Advanced Algorithm Score: ";
                cin >> st.scores.CPP;
                st.isDeleted = false;
                studentList.addStudent(st);
                }
                currentStudent += numStudent;
                StudentList saveToFile();
                break;
            }
            case 2: {
                string keyword;
                cout<<"-----------------------------------"<< endl;
                cout<<"      2. Search Info Student       "<<endl;
                cout<<"-----------------------------------"<<endl;
                cout << "Enter name or ID to search: ";
                cin.ignore();
                getline(cin, keyword);
                studentList.searchStudent(keyword);
                break;
            }
            case 3: {
                cout<<"-----------------------------------"<< endl;
                cout<<"      3.Display all Info Student"<<endl;
                cout<<"------------------------------------ "<<endl;
                studentList.sortStudentsByID();
                studentList.displayAllStudents();
                break;
            }
            case 4: {
                int id;
                cout<<"-----------------------------------"<< endl;
                cout<<"        4. Delete Student          "<<endl;
                cout<<"-----------------------------------"<<endl;
                cout << "Enter the ID of the student to delete: ";
                cin >> id;
                studentList.removeStudent(id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter the ID of the student to edit: ";
                cin >> id;
                studentList.editStudent();
                break;
            }
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
        currentStudent += numStudent;
        studentList.saveToFile();
    } while (choice != 0);

    return 0;
}