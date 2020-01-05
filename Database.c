#include "../Main.h"
#include "Database.h"
#include <malloc.h>
#include <string.h>
#include <ctype.h>


static void ConvertToUpper(char* const string)
{
    for (int i = 0; i < MAX_STUDENT_SINGLE_DATA_BUFFER_LENGTH; ++i)
    {
        if (string != NULL && string[i] != '\0')
            string[i] = toupper(string[i]);
        else
            break;
    }
}


static float CalculateAverage(int* grades)
{
    float average = 0;
    if (grades != NULL)
    {
        average = (float)((grades[Math] + grades[Physics] + grades[English]) / MaxClass);
    }
    return average;
}


StudentsDatabase* CreateDatabase(void)
{
    StudentsDatabase* database = (StudentsDatabase*)malloc(sizeof(StudentsDatabase));

    database->numberOfStudents = 0;
    database->students = (Student*)calloc(1, sizeof(Student));

    return database;
}


void AddStudent(StudentsDatabase* database, Student studentToAdd)
{
    database->students = (Student*)realloc(database->students, (database->numberOfStudents + 1) * sizeof(Student));

    database->students[database->numberOfStudents] = studentToAdd;
    database->numberOfStudents++;
}


void InsertNStudentsIntoIndex(StudentsDatabase* database, Student* studentsToInsert, const int numberOfStudents, const unsigned int index)
{
    if (studentsToInsert != NULL)
    {
        database->students = (Student*)realloc(database->students, (database->numberOfStudents + numberOfStudents) * sizeof(Student));
        database->numberOfStudents += numberOfStudents;

        for (unsigned int i = database->numberOfStudents; i > index; --i)
        {
            strcpy(database->students[i-1].surname, database->students[i-1-numberOfStudents].surname);
            strcpy(database->students[i-1].birthdate, database->students[i-1-numberOfStudents].birthdate);
            memcpy(database->students[i-1].grades, database->students[i-1-numberOfStudents].grades, MaxClass*sizeof(int));
            database->students[i-1].indexNumber = database->students[i-1-numberOfStudents].indexNumber;
        }

        for (int i = 0; i < numberOfStudents; ++i)
        {
            strcpy(database->students[i+index].surname, studentsToInsert[i].surname);
            strcpy(database->students[i+index].birthdate, studentsToInsert[i].birthdate);
            memcpy(database->students[i+index].grades, studentsToInsert[i].grades, MaxClass * sizeof(int));
            database->students[i+index].indexNumber = studentsToInsert[i].indexNumber;
        }
    }
}


void RemoveStudentWithIndex(StudentsDatabase* database, const unsigned int indexToRemove)
{
    for (unsigned int i = indexToRemove; i < database->numberOfStudents; ++i)
    {
        strcpy(database->students[i].surname, database->students[i+1].surname);
        strcpy(database->students[i].birthdate, database->students[i+1].birthdate);
        memcpy(database->students[i].grades, database->students[i+1].grades, MaxClass * sizeof(int));
        database->students[i].indexNumber = database->students[i+1].indexNumber;
    }

    database->numberOfStudents--;
    database->students = (Student*)realloc(database->students, database->numberOfStudents * sizeof(Student));
}


int FindStudentBySurname(StudentsDatabase* database, char* const surname)
{
    ConvertToUpper(surname);

    int foundStudentIndex = -1;

    for (unsigned int checkedIndex = 0; checkedIndex < database->numberOfStudents; ++checkedIndex)
    {
        char nextStudentSurname[MAX_STUDENT_SINGLE_DATA_BUFFER_LENGTH] = { '\0' };
        strcpy(nextStudentSurname, database->students[checkedIndex].surname);
        ConvertToUpper(nextStudentSurname);

        if (0 == strcmp(surname, nextStudentSurname))
        {
            foundStudentIndex = checkedIndex;
            break;
        }
    }

    return foundStudentIndex;
}


Student FindStudentWithHighestDegreeInSubject(StudentsDatabase* database, const Class subject)
{
    int indexOfStudentWithHighestDegree = 0;
    for (unsigned int i = 1; i < database->numberOfStudents; ++i)
    {
        if (database->students[i].grades[subject] > database->students[i - 1].grades[subject])
        {
            indexOfStudentWithHighestDegree = i;
        }
    }

    return database->students[indexOfStudentWithHighestDegree];
}


Student FindStudentInDatabaseWithHighestAverage(StudentsDatabase* database)
{
    int indexOfStudentWithHighestDegree = 0;
    for (unsigned int i = 1; i < database->numberOfStudents; ++i)
    {
        if (CalculateAverage(database->students[i].grades) > CalculateAverage(database->students[i - 1].grades))
        {
            indexOfStudentWithHighestDegree = i;
        }
    }

    return database->students[indexOfStudentWithHighestDegree];
}

