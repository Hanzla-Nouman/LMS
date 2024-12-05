#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int maxTeachers = 100;
const int maxSubjects = 4;
const int maxClasses = 10;

string teacherInfo[maxTeachers][2];
string teacherSubjects[maxTeachers][maxSubjects];
string teacherClasses[maxTeachers][maxClasses];

const int maxStudents = 100;
const int TotalRegSubjects = 4;

string studentInfo[maxStudents][3];
string studentSubjects[maxStudents][TotalRegSubjects];
string studentGrades[maxStudents][TotalRegSubjects];
string studentMarks[maxStudents][TotalRegSubjects];
double CGPA[maxStudents];

void saveToTeachersFile()
{
    ofstream file("teachers_data.txt");
    if (!file)
    {
        cout << "Error opening file for saving!" << endl;
        return;
    }

    int count = 0;
    while (teacherInfo[count][0] != "" && count < maxTeachers)
    {
        file << teacherInfo[count][0] << "," << teacherInfo[count][1] << endl;

        for (int i = 0; i < maxSubjects; i++)
        {
            file << (teacherSubjects[count][i].empty() ? "NONE" : teacherSubjects[count][i]) << (i == maxSubjects - 1 ? "\n" : ",");
        }

        for (int i = 0; i < maxClasses; i++)
        {
            file << (teacherClasses[count][i].empty() ? "NONE" : teacherClasses[count][i]) << (i == maxClasses - 1 ? "\n" : ",");
        }

        count++;
    }
    file.close();
    cout << "Data saved successfully!" << endl;
}
void saveToStudentsFile()
{
    ofstream file("students.txt");
    if (!file)
    {
        cout << "Error opening file for saving!" << endl;
        return;
    }
    int count = 0;
    while (studentInfo[count][0] != "" && count < maxStudents)
    {
        file << studentInfo[count][0] << "," << studentInfo[count][1] << "," << studentInfo[count][2] << endl;
        for (int i = 0; i < maxSubjects; i++)
        {
            file << studentSubjects[count][i] << (i == maxSubjects - 1 ? "\n" : ",");
        }
        count++;
    }

    file.close();
    cout << "Data saved successfully!" << endl;
}

void loadFromTeachersFile()
{
    ifstream file("teachers_data.txt");
    if (!file)
    {
        cout << "No existing data file found. Starting fresh." << endl;
        return;
    }

    int count = 0;
    string line;

    while (getline(file, line) && count < maxTeachers)
    {
        size_t commaPos = line.find(",");
        teacherInfo[count][0] = line.substr(0, commaPos);
        teacherInfo[count][1] = line.substr(commaPos + 1);

        // Read subjects
        getline(file, line);
        size_t startPos = 0, endPos;
        for (int i = 0; i < maxSubjects; i++)
        {
            endPos = line.find(",", startPos);
            string subject = line.substr(startPos, endPos - startPos);
            teacherSubjects[count][i] = (subject == "NONE" ? "" : subject);
            startPos = endPos + 1;
        }

        // Read classes
        getline(file, line);
        startPos = 0;
        for (int i = 0; i < maxClasses; i++)
        {
            endPos = line.find(",", startPos);
            string className = line.substr(startPos, endPos - startPos);
            teacherClasses[count][i] = (className == "NONE" ? "" : className);
            startPos = endPos + 1;
        }

        count++;
    }
    file.close();
    cout << "Data loaded successfully!" << endl;
}
void loadFromStudentsFile()
{
    ifstream file("students.txt");
    if (!file)
    {
        cout << "No existing data file found. Starting fresh." << endl;
        return;
    }

    int count = 0;
    string line;

    while (getline(file, line) && count < maxStudents)
    {
        size_t commaPos = line.find(",");
        studentInfo[count][0] = line.substr(0, commaPos);
        studentInfo[count][1] = line.substr(commaPos + 1);

        // Read subjects
        // getline(file, line);
        // size_t startPos = 0, endPos;
        // for (int i = 0; i < maxSubjects; i++) {
        //     endPos = line.find(",", startPos);
        //     string subject = line.substr(startPos, endPos - startPos);
        //     teacherSubjects[count][i] = (subject == "NONE" ? "" : subject);
        //     startPos = endPos + 1;
        // }

        // // Read classes
        // getline(file, line);
        // startPos = 0;
        // for (int i = 0; i < maxClasses; i++) {
        //     endPos = line.find(",", startPos);
        //     string className = line.substr(startPos, endPos - startPos);
        //     teacherClasses[count][i] = (className == "NONE" ? "" : className);
        //     startPos = endPos + 1;
        // }

        count++;
    }
    file.close();
    cout << "Data loaded successfully!" << endl;
}

int getTeacherCount()
{
    int count = 0;
    for (int i = 0; i < maxTeachers; i++)
    {
        if (teacherInfo[i][0] == "")
        {
            break;
        }
        count++;
    }
    cout << "count " << count << endl;
    return count;
}
int getStudentCount()
{

    int count = 0;
    for (int i = 0; i < maxStudents; i++)
    {
        if (studentInfo[i][0] == "")
        {
            break;
        }
        count++;
    }

    return count;
}

void printStudents()
{
    cout << "List of Students:\n";
    int count = getStudentCount();
    for (int i = 0; i < count; i++)
    {
        cout << "ID: " << studentInfo[i][0] << ", Name: " << studentInfo[i][1] << endl;
    }
}
void printTeachers()
{
    cout << "List of Teachers:\n";
    int count = getTeacherCount();
    for (int i = 0; i < count; i++)
    {
        cout << "ID: " << teacherInfo[i][0] << ", Name: " << teacherInfo[i][1] << endl;
    }
}

void addTeacher()
{
    int count = getTeacherCount();

    if (count >= maxTeachers)
    {
        cout << "Error: Maximum number of teachers reached!" << endl;
        return;
    }

    string id, name;
    cout << "Enter Teacher ID: ";
    cin >> id;
    cout << "Enter Teacher Name: ";
    cin.ignore(); // To consume the leftover newline character
    getline(cin, name);

    teacherInfo[count][0] = id;
    teacherInfo[count][1] = name;

    // Add subjects
    cout << "Enter up to " << maxSubjects << " subjects (type 'done' to stop):" << endl;
    for (int i = 0; i < maxSubjects; i++)
    {
        string subject;
        cout << "Subject " << (i + 1) << ": ";
        cin >> subject;
        if (subject == "done")
            break;
        teacherSubjects[count][i] = subject;
    }

    // Add classes
    cout << "Enter up to " << maxClasses << " classes (type 'done' to stop):" << endl;
    for (int i = 0; i < maxClasses; i++)
    {
        string className;
        cout << "Class " << (i + 1) << ": ";
        cin >> className;
        if (className == "done")
            break;
        teacherClasses[count][i] = className;
    }

    cout << "Teacher added successfully!" << endl;
    saveToTeachersFile();
}
void addStudent()
{
    int count = getStudentCount();

    if (count >= maxStudents)
    {
        cout << "Error: Maximum number of students reached!" << endl;
        return;
    }

    string id, name;
    cout << "Enter Student ID: ";
    cin >> id;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);

    studentInfo[count][0] = id;
    studentInfo[count][1] = name;

    // Add subjects
    cout << "Enter " << maxSubjects << " subjects:" << endl;
    for (int i = 0; i < maxSubjects; i++)
    {
        string subject;
        cout << "Subject " << (i + 1) << ": ";
        cin >> subject;
        studentSubjects[count][i] = subject;
    }

    // Add classes
    cout << "Enter class" << endl;

    string className;
    cin >> className;

    studentInfo[count][2] = className;

    cout << "Student added successfully!" << endl;
    saveToStudentsFile();
}

void deleteTeacher()
{
    int count = getTeacherCount();
    if (count == 0)
    {
        cout << "No teachers to delete!" << endl;
        return;
    }

    string idToDelete;
    cout << "Enter Teacher ID to delete: ";
    cin >> idToDelete;

    int indexToDelete = -1;
    for (int i = 0; i < count; i++)
    {
        if (teacherInfo[i][0] == idToDelete)
        {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1)
    {
        cout << "Teacher ID not found!" << endl;
        return;
    }

    // Shift elements to "delete" the teacher
    for (int i = indexToDelete; i < count - 1; i++)
    {
        teacherInfo[i][0] = teacherInfo[i + 1][0];
        teacherInfo[i][1] = teacherInfo[i + 1][1];

        for (int j = 0; j < maxSubjects; j++)
        {
            teacherSubjects[i][j] = teacherSubjects[i + 1][j];
        }

        for (int j = 0; j < maxClasses; j++)
        {
            teacherClasses[i][j] = teacherClasses[i + 1][j];
        }
    }

    // Clear the last entry
    teacherInfo[count - 1][0] = "";
    teacherInfo[count - 1][1] = "";
    for (int j = 0; j < maxSubjects; j++)
    {
        teacherSubjects[count - 1][j] = "";
    }
    for (int j = 0; j < maxClasses; j++)
    {
        teacherClasses[count - 1][j] = "";
    }

    cout << "Teacher deleted successfully!" << endl;
    saveToTeachersFile();
}

void deleteStudent()
{
    int count = getStudentCount();
    if (count == 0)
    {
        cout << "No Student to delete!" << endl;
        return;
    }

    string idToDelete;
    cout << "Enter Student ID to delete: ";
    cin >> idToDelete;

    int indexToDelete = -1;
    for (int i = 0; i < count; i++)
    {
        if (studentInfo[i][0] == idToDelete)
        {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1)
    {
        cout << "Student ID not found!" << endl;
        return;
    }

    // Shift elements to "delete" the teacher
    for (int i = indexToDelete; i < count - 1; i++)
    {
        studentInfo[i][0] = studentInfo[i + 1][0];
        studentInfo[i][1] = studentInfo[i + 1][1];
        studentInfo[i][2] = studentInfo[i + 1][2];

        for (int j = 0; j < maxSubjects; j++)
        {
            studentSubjects[i][j] = studentSubjects[i + 1][j];
        }
    }

    // Clear the last entry
    studentInfo[count - 1][0] = "";
    studentInfo[count - 1][1] = "";
    studentInfo[count - 1][2] = "";
    for (int j = 0; j < maxSubjects; j++)
    {
        studentSubjects[count - 1][j] = "";
    }

    cout << "Student deleted successfully!" << endl;
    saveToStudentsFile();
}

void displayTeacherDetails()
{
    string id;
    cout << "Enter Teacher ID to view details: ";
    cin >> id;

    int count = getTeacherCount();
    for (int i = 0; i < count; i++)
    {
        if (teacherInfo[i][0] == id)
        {
            cout << "Name: " << teacherInfo[i][1] << endl;

            cout << "Subjects: ";
            for (int j = 0; j < maxSubjects && !teacherSubjects[i][j].empty(); j++)
            {
                cout << teacherSubjects[i][j];
                if (j < maxSubjects - 1 && !teacherSubjects[i][j + 1].empty())
                {
                    cout << ", ";
                }
            }
            cout << endl;

            cout << "Classes: ";
            for (int j = 0; j < maxClasses && !teacherClasses[i][j].empty(); j++)
            {
                cout << teacherClasses[i][j];
                if (j < maxClasses - 1 && !teacherClasses[i][j + 1].empty())
                {
                    cout << ", ";
                }
            }
            cout << endl;

            return;
        }
    }

    cout << "Teacher ID not found!" << endl;
}
void assignMarks(){
        int count = getStudentCount();
    if (count == 0)
    {
        cout << "No Student to delete!" << endl;
        return;
    }
    string id;
    cout<<"Enter the student's Id: ";
    cin>>id;
    int studentIdMarks = -1;
     for (int i = 0; i < count; i++)
    {
        if (studentInfo[i][0] == id)
        {
            studentIdMarks = i;
            break;
        }
    }

    if (studentIdMarks == -1)
    {
        cout << "Student ID not found!" << endl;
        return;
    }

}
int main()
{
    loadFromTeachersFile(); // Load data on startup
    loadFromStudentsFile(); // Load data on startup

    int option;
    while (true)
    {
        cout << "\nWelcome to Student Management System" << endl;
        cout << "1. Admin \n2. Teacher\n3. Student \n4. Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            int adminOption;
            cout << "1. Add Teacher \n2. Delete Teacher \n3. View Teachers \n4. View Teacher Details" << endl;
            cout << "Enter your option: ";
            cin >> adminOption;

            switch (adminOption)
            {
            case 1:
                addTeacher();
                break;
            case 2:
                deleteTeacher();
                break;
            case 3:
                printTeachers();
                break;
            case 4:
                displayTeacherDetails();
                break;
            default:
                cout << "Invalid option!" << endl;
                break;
            }
            break;
        }
        case 2:
            int teacherOption;
            cout << "1. Add Student \n2. Delete Student \n3. View Students \n4. Assign Marks \n5. Average CGPA \n6. Calculate Grade" << endl;
            cout << "Enter your option: ";
            cin >> teacherOption;
            switch (teacherOption)
            {
            case 1:
                addStudent();
                break;

            case 2:
                deleteStudent();
                break;

            case 3:
                printStudents();
                break;

            case 4:
                assignMarks();
                break;

            case 5:

                break;

            case 6:

                break;

            case 7:

                break;

            default:
                break;
            }
            break;
        case 3:
            cout << "Student logic is not implemented yet." << endl;
            break;
        case 4:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Error! Invalid Input" << endl;
            break;
        }
    }
    return 0;
}
