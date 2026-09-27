#include <iostream>
using namespace std;

struct Course {
    string grade;
    int creditHours;
};

int main() {
    Course courses[10];
    int numCourses;
    cout << "welcome to CGPA CALCULATOR " << endl;
    cout << "enter the number of course : ";
    cin >> numCourses;

    double totalGradePoints = 0;
    int totalCredits = 0;

    
    for (int i = 0; i < numCourses; i++) {
        cout << "Enter grade for course " << i + 1 << ": ";
        cin >> courses[i].grade;

        cout << "Enter credit hours for course " << i + 1 << ": ";
        cin >> courses[i].creditHours;

        double points;
        if (courses[i].grade == "A") points = 4.0;
        else if (courses[i].grade == "B") points = 3.0;
        else if (courses[i].grade == "C") points = 2.0;
        else if (courses[i].grade == "D") points = 1.0;
        else points = 0.0;

        totalGradePoints += points * courses[i].creditHours;
        totalCredits += courses[i].creditHours;
    }

   
    double gpa = totalGradePoints / totalCredits;

   
    cout << "\nCourse Grades:\n";
    for (int i = 0; i < numCourses; i++) {
        cout << "Course " << i + 1 << ": " << courses[i].grade
            << " (" << courses[i].creditHours << " credit hours)" << endl;
    }

    cout << "your GPA is : " << gpa << endl;

    return 0;
}