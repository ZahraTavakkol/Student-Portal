#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <bits/stdc++.h> 

#define LENGTH 50
#define START 30
#define SPACE 1
#define delimiter "-"
#define delimiterlen 1

using namespace std;

void clearScreen () {
    system("cls");
}

void sleep (int mili) {
    Sleep(mili);
}

void gotoxy (int x, int y) {
    static HANDLE h = NULL;
    if (!h) {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

class Portal{
    private:
        string Menu[6] = {" MENU ", "1) Students", "2) Courses", "3) Courses Registration", "4) Reports", "5) Exit"};
        
    
    public:
    int choice[2] = {0, 0};
    vector<string> INFO;
    void generator(string*, int);
    void action(int* choice);
    void showList(string);
    void storeINFO(string*, int);
};

class Student{

    private:
    string name;
    string family_name;
    string field;
    string StudentID;

    public:
    vector<string> Info;

    void add();
    void remove(const char*);
    void search();

};

class Course {
    protected:
    string name;
    string courseID;
    string credits;
    string description;

    public:
    vector<string> Info;

    void add();
    void remove(const char *);
    void search();
    void addStudent();
    void removeStudent(const char *);
    void addScore();

};

class TheoreticalCourse:public Course{
    public:
    void addDescription() {
        courseID = Info.at(0);
        fstream file;
        file.open("Description.txt", ios::out | ios::app);
        if (file.is_open()){
            file << Info.at(0) << delimiter << Info.at(1) << delimiter << Info.at(2) << delimiter << endl;
        }
        }
};

class PracticalCourse:public Course{
    public:
    void addDescription() {
        courseID = Info.at(0);
        fstream file;
        file.open("Description.txt", ios::out | ios::app);
        if (file.is_open()){
            file << Info.at(0) << delimiter << Info.at(1) << delimiter << Info.at(2) << delimiter << endl;
        }
        }
};

void Student::remove(const char *file_name = "Students.txt"){
    StudentID = Info.at(0);
    fstream file;
    file.open(file_name, ios::in);
    
    fstream temp;
    temp.open("temp.txt", ios::out);

    if (file.is_open()){
        string str;
        while(getline(file, str)){
            vector<string> result;
            string line = str;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }

            if (result.at(2) != StudentID){
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
    }
    rename(file_name, "temp2.txt");
    rename("temp.txt", file_name);
    rename("temp2.txt", "temp.txt");

}

void Portal::generator(string* group, int len){
    
    clearScreen();
    for (int i = START; i < START + LENGTH; i++){
        gotoxy (i, SPACE);
        cout << "*";
        gotoxy (i, SPACE * (len+1));
        cout << "*";
    }

    gotoxy (LENGTH/2+START-(group[0].length())/2, SPACE);
    cout << group[0];

    for (int i = 1; i < len; i++){
        gotoxy (START, SPACE*(i+1));
        cout << "*" << group[i];
        gotoxy (START + LENGTH - 1, SPACE*(i+1));
        cout << "*";
    }

    gotoxy (LENGTH/3+START, SPACE * (len+2));
    cout << "Enter your choice: "; 

    
}

void Portal::action(int* choice){
    if (choice[1] == 0){
        if(choice[0] == 0){
            generator(Menu, 6);
        }else if (choice[0] == 1){
        string group[5] = {" Students ", "1) Add a student", "2) Remove a student", "3) Search a sudent", "4) Back"};
        generator(group, 5);
          } else if(choice[0] == 2){
        string group[6] = {" Courses ", "1) Add a Course", "2) Remove a Course", "3) Search a Course", "4) Add More Description ", "5) Back "};
        generator(group, 6);
         } else if(choice[0] == 3){
        string group[5] = {" Courses Registration ", "1) Add a Course for students", "2) Remove a Course for a student", "3) Add score of a course", "4) Back"};
        generator(group, 5);
          }else if(choice[0] == 4){
        string group[6] = {" Reports ", "1) List of Students", "2) List of Courses", "3) All scores in a Course", "4) All students in a course", "5) Back"};
        generator(group, 6);
    }
    }else if(choice[1] == 1){
        if (choice[0] == 1){
            string group[5] = {" Add a student ", "1) Enter student ID ","2) Enter name ", "3) Enter Family name ",  "4) Enter field "};
            storeINFO(group, 5);
         } else if(choice[0] == 2){
        string group[5] = {" Add a Course ", "1) Enter Course name ", "2) Enter Credit ", "3) Enter Course ID ", "4) Description "};
        storeINFO(group, 5);
         } else if(choice[0] == 3){
        string group[3] = {" Add a Course for students ", "1) Enter student ID ", "2) Enter Course ID "};
        storeINFO(group, 3);
         }else if(choice[0] == 4){
        showList(" Students ");
         
    }
    }else if(choice[1] == 2){
        if (choice[0] == 1){
            string group[2] = {" Remove a student ", "1) Enter student ID "};
            storeINFO(group, 2);
         } else if(choice[0] == 2){
        string group[2] = {" Remove a Course ", "1) Enter Course ID "};
        storeINFO(group, 2);
        } else if(choice[0] == 3){
        string group[3] = {" Remove a Course for a student ", "1) Enter student ID ", "2) Enter Course ID "};
        storeINFO(group, 3);
        }else if(choice[0] == 4){
        showList( " Courses ");
        }
    }else if(choice[1] == 3){
        if (choice[0] == 1){
            string group[2] = {" Search a sudent ", "1) Enter student ID "};
            storeINFO(group, 2);
        } else if(choice[0] == 2){
        string group[2] = {" Search a Course ", "1) Enter Course ID "};
        storeINFO(group, 2);
        } else if(choice[0] == 3){
        string group[4] = {" Add score of a course ", "1) Enter student ID ", "2) Enter Course ID ", "3) Enter score "};
        storeINFO(group, 4);
        }else if(choice[0] == 4){
            string group[2] = {" All scores in a Course ", "1) Enter Course ID "};
            storeINFO(group, 2);
            showList(" All scores in a Course ");
    }
    }else if(choice[1] == 4){
        if (choice[0] == 1 || choice[0] == 3){
            choice[0] = 0;
            choice[1] = 0;
        }else if(choice[0] == 4){
            string group[2] = {" All students in a course ", "1) Enter Course ID "};
            storeINFO(group, 2);
            showList(" All students in a course ");
        }else if(choice[0] == 2){
            string group[4] = {" Add More Description ", "1) Enter Course ID ", "2) Theoretical(enter 1) or Practical(enter 2) ", "3) Write Description: "};
            storeINFO(group, 4);
        }
    }else if(choice[1] == 5){
        if (choice[0] == 1 || choice[0] == 3){
            choice[1] = 0;
        }else if(choice[0] == 4){
            choice[0] = 0;
            choice[1] = 0;
        }else if(choice[0] == 2){
            choice[0] = 0;
            choice[1] = 0;
        }
} 

}

void Portal::showList(string name){
    clearScreen();
    for (int i = START; i < START + LENGTH; i++){
        gotoxy (i, SPACE);
        cout << "*";
    }
    gotoxy (LENGTH/2+START-(name.length())/2, SPACE);
    cout << name;
    string str = " To Return Press * ";
    gotoxy (LENGTH/2+START-(str.length())/2, SPACE * 2);
    cout << str << endl;


    fstream file;
    if (name == " Students "){
        file.open("Students.txt", ios::in);
    } else if (name == " Courses "){
        file.open("Courses.txt", ios::in);
    } else {
        file.open("Integrated.txt", ios::in);
    }
    
    if (file.is_open()){
        string str;
        
        while(getline(file, str)){
            vector<string> result;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }
        

        if (name == " Students "){
            cout << "* " << result.at(0) << " " << result.at(1) << endl;
        }else if (name == " Courses "){
            cout << "* " << result.at(0) << endl;
        }else if (name == " All students in a course "){
            if(result.at(1) == INFO.at(0)){
                cout << "* " << result.at(0) << endl;
            }
        }else if (name == " All scores in a Course "){
            if(result.at(1) == INFO.at(0)){
                cout << "* " << result.at(2) << endl;
            }
        }
        }
        file.close();
    }

    char n;
    while (cin >> n){
        if (n == '*'){
            break;
        }  
    }
}

void Portal::storeINFO(string* group, int len){
    string enter;
    getline(cin, enter);
    for(int i=1;i<len;i++){
        clearScreen();
        for (int i = START; i < START + LENGTH; i++){
        gotoxy (i, SPACE);
        cout << "*";
    }
        gotoxy (LENGTH/2+START-(group[0].length())/2, SPACE);
        cout << group[0];
        gotoxy (LENGTH/2+START-(group[i].length())/2, SPACE*2);
        cout << group[i];
        
        getline(cin, enter);
        INFO.push_back(enter);
    }
    
}

void Student::add(){
    StudentID = Info.at(0);
    name = Info.at(1);
    family_name = Info.at(2);
    field = Info.at(3);

    fstream file;
    file.open("Students.txt", ios::in);

    fstream temp;
    temp.open("temp.txt", ios::out);
    string str;
    
    if (file.is_open()){
        while(getline(file, str)){

            vector<string> result;
            string line = str;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }

            if (result.at(2) != StudentID){
                temp << line << endl;
            }
            
            
        }
        temp << name << delimiter << family_name << delimiter << StudentID << delimiter << field << delimiter << endl;
        file.close();
        temp.close();
    }
    rename("Students.txt", "temp2.txt");
    rename("temp.txt", "Students.txt");
    rename("temp2.txt", "temp.txt");
}

void Student::search(){
    StudentID = Info.at(0);

    clearScreen();
    for (int i = START; i < START + LENGTH; i++){
        gotoxy (i, SPACE);
        cout << "*";
    }

    string st = " To Return Press * ";
    gotoxy (LENGTH/2+START-(st.length())/2, SPACE * 2);
    cout << st << endl;

    fstream file;
    file.open("Students.txt", ios::in);
    
    string str;
    if (file.is_open()){
        while(getline(file, str)){
            vector<string> result;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }

            if (result.at(2) == StudentID){
                cout << "* Name: " <<result.at(0) << " " << result.at(1) << endl;
                cout << "* ID: " <<result.at(2) << endl;
                cout << "* Field: " <<result.at(3) << endl;
            }
        }
        file.close();
    }
    char n;
    while (cin >> n){
        if (n == '*'){
            break;
        }  
    }
}

void Course::add(){
    name = Info.at(0);
    credits = Info.at(1);
    courseID = Info.at(2);
    description = Info.at(3);

    fstream file;
    file.open("Courses.txt", ios::in);
    
    fstream temp;
    temp.open("temp.txt", ios::out);
    string str;

    if (file.is_open()){
        while(getline(file, str)){

        vector<string> result;
        string line = str;

        int pos;
        string token;
        while ((pos = str.find(delimiter)) != str.npos) {
            token = str.substr(0, pos);
            result.push_back(token);
            str.erase(0, pos + delimiterlen);
        }

        if (result.at(1) != Info.at(2)){
            temp << line << endl;
        }
            
            
        }
        temp <<name << delimiter << courseID << delimiter << credits << delimiter << description << delimiter <<endl;
        file.close();
        temp.close();
    }
    rename("Courses.txt", "temp2.txt");
    rename("temp.txt", "Courses.txt");
    rename("temp2.txt", "temp.txt");
}

void Course::search(){
    courseID = Info.at(0);
    clearScreen();
    for (int i = START; i < START + LENGTH; i++){
        gotoxy (i, SPACE);
        cout << "*";
    }

    string st = " To Return Press * ";
    gotoxy (LENGTH/2+START-(st.length())/2, SPACE * 2);
    cout << st << endl;

    fstream file;
    file.open("Courses.txt", ios::in);
    
    string str;
    if (file.is_open()){
        while(getline(file, str)){
            vector<string> result;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }

            if (result.at(1) == courseID){
                cout << "* Name: " << result.at(0) << endl;
                cout << "* ID: " << result.at(1) << endl;
                cout << "* Credit: " << result.at(2) << endl;
                cout << "* Description: " << result.at(3) << endl;
            }
        }
        file.close();
    }

    file.open("Description.txt", ios::in);
    
    if (file.is_open()){
        while(getline(file, str)){
            vector<string> result;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }
            if (result.at(0) == courseID){
                cout << "* More Description: " << result.at(2) << endl;
            }
        }
        file.close();
    }
    char n;
    while (cin >> n){
        if (n == '*'){
            break;
        }  
    }
}

void Course::remove(const char *file_name = "Courses.txt"){
    courseID = Info.at(0);

    fstream file;
    file.open(file_name, ios::in | ios::out);
    
    fstream temp;
    temp.open("temp.txt", ios::out);

    string str;
    if (file.is_open() && temp.is_open()){
        while(getline(file, str)){
            string line = str;
            vector<string> result;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }

            if (result.at(1) != courseID){
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
    }
    rename(file_name, "temp2.txt");
    rename("temp.txt", file_name);
    rename("temp2.txt", "temp.txt");

    file.open("Description.txt", ios::in);

    temp.open("temp.txt", ios::out);
    
    if (file.is_open()){
        while(getline(file, str)){
            vector<string> result;
            string line = str;
            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }

            if (result.at(0) != courseID){
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
    }
    rename("Description.txt", "temp2.txt");
    rename("temp.txt", "Description.txt");
    rename("temp2.txt", "temp.txt");
    
}

void Course::addStudent(){
    courseID = Info.at(1);

    fstream file;
    file.open("Integrated.txt", ios::out | ios::app);
    
    if (file.is_open()){
        
        file << Info.at(0) << delimiter << courseID << delimiter << endl;
        file.close();
    }
}

void Course::removeStudent(const char *file_name = "Integrated.txt"){
    
    fstream file;
    file.open(file_name, ios::in | ios::out);
    
    fstream temp;
    temp.open("temp.txt", ios::out);
    string str;
    if (file.is_open()){
        while(getline(file, str)){
            string line = str;
            vector<string> result;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }

            if (result.at(1) == Info.at(1)){
                if(result.at(0) == Info.at(0)){
                    continue;
            }}
            
            temp << line << endl;
        }
        file.close();
        temp.close();
    }

    rename(file_name, "temp2.txt");
    rename("temp.txt", file_name);
    rename("temp2.txt", "temp.txt");
}

void Course::addScore(){
    
    courseID = Info.at(1);

    fstream file;
    file.open("Integrated.txt", ios::in);

    fstream temp;
    temp.open("temp.txt", ios::out);
    string str;

    if (file.is_open()){
        while(getline(file, str)){

            vector<string> result;
            string line = str;

            int pos;
            string token;
            while ((pos = str.find(delimiter)) != str.npos) {
                token = str.substr(0, pos);
                result.push_back(token);
                str.erase(0, pos + delimiterlen);
            }

            if (result.at(1) == Info.at(1)){
                if(result.at(0) == Info.at(0)){
                    continue;
            }}
            
            temp << line << endl;
        }
        
        temp << Info.at(0) << delimiter << courseID << delimiter << Info.at(2) << delimiter << endl;

        
        file.close();
        temp.close();
    }
    rename("Integrated.txt", "temp2.txt");
    rename("temp.txt", "Integrated.txt");
    rename("temp2.txt", "temp.txt");

}

int main(int argc, char** argv){
    Portal portal;
    
    while(portal.choice[0] != 5){
        portal.action(portal.choice);

        string number;
        cin >> number;
        number = "0" + number;
        int myint = stoi(number);

        for (int i = 1; i<= 5; i++){
            if (i == myint){
                if(portal.choice[0] == 0){
                    portal.choice[0] = myint;
                } else {
                    portal.choice[1] = myint;
                }
            }
        }
        
        portal.action(portal.choice);

        if(portal.choice[0] == 1 && portal.choice[1] != 0){
            Student student;
            for(int i = 0; i < portal.INFO.size(); i++){
                student.Info.push_back(portal.INFO.at(i));
            }
            
            if(portal.choice[1] == 1){
                student.add();
            } else if (portal.choice[1] == 2){
                student.remove();
            } else if (portal.choice[1] == 3){
                student.search();
            }
        
        }else if (portal.choice[0] == 2 || portal.choice[0] == 3){
                Course course;
                for(int i = 0; i < portal.INFO.size(); i++){
                    course.Info.push_back(portal.INFO.at(i));
                }
                if(portal.choice[1] == 1){
                    if(portal.choice[0] == 2){course.add();}
                    else if(portal.choice[0] == 3){course.addStudent();}
                } else if (portal.choice[1] == 2){
                    if(portal.choice[0] == 2){course.remove();}
                    else if(portal.choice[0] == 3){course.removeStudent();}
                } else if (portal.choice[1] == 3){
                    if(portal.choice[0] == 2){course.search();}
                    else if(portal.choice[0] == 3){course.addScore();}
                }else if (portal.choice[1] == 4){
                    if(portal.choice[0] == 2){
                        if(portal.INFO.at(1) == "1"){
                            TheoreticalCourse theoretical;
                            for(int i = 0; i < portal.INFO.size(); i++){
                            theoretical.Info.push_back(portal.INFO.at(i));
                            }
                            theoretical.addDescription();
                        }else if(portal.INFO.at(1) == "2"){
                            PracticalCourse practical;
                            for(int i = 0; i < portal.INFO.size(); i++){
                            practical.Info.push_back(portal.INFO.at(i));
                            }
                            practical.addDescription();}}
                
                }
        }
        portal.choice[1] = 0;
        portal.INFO.clear();
    }
    
}