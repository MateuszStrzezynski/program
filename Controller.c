#include "Controller.h"

#include "../Database/Database.h"

#include <stdlib.h>




static void InsertStudentsIntoIndex(StudentsDatabase* database)
{
    int indexToInsert = 0;
    printf("\nWprowadz numer rekordu, pod ktory chcesz wprowadzic nowych studentow:");
    scanf("%d", &indexToInsert);

    int numberOfStudentsToInsert = 0;
    printf("\nWprowadz liczbe studentow jaka zostanie dodana: ");
    scanf("%d", &numberOfStudentsToInsert);

    Student* studentsToInsert = (Student*)calloc(numberOfStudentsToInsert, sizeof(Student));
    for (int insertedStudents = 0; insertedStudents < numberOfStudentsToInsert; ++insertedStudents)
    {
        studentsToInsert[insertedStudents] = CreateStudent();
    }

    InsertNStudentsIntoIndex(database, studentsToInsert, numberOfStudentsToInsert, indexToInsert);

    printf("\nWprowadzanie studentow zakonczone. OK!\n\n");
}


static void RemoveStudentsUnderIndex(StudentsDatabase* database)
{
    int indexToRemove = 0;
    printf("\nWprowadz numer rekordu w bazie, ktory chcesz usunac: ");
    scanf("%d", &indexToRemove);

    RemoveStudentWithIndex(database, indexToRemove);

    printf("\nUsunieto... OK!\n\n");
}


static void SearchStudentBySurname(StudentsDatabase* database)
{
    char searchedSurname[MAX_STUDENT_SINGLE_DATA_BUFFER_LENGTH] = { '\0' };
    printf("\nWprowadz nazwisko szukanego studenta: ");
    scanf("%s", searchedSurname);

    int foundStudentIndex = FindStudentBySurname(database, searchedSurname);

    if (foundStudentIndex != -1)
    {
        Student foundStudent = database->students[foundStudentIndex];
        printf("\nDane studenta:\nNazwisko:\t%s\nData urodzenia:\t%s\nIndeks\t\t%d\nOcena - matematyka:\t\t%d\nOcena - fizyka:\t%d\nOcena - angielski:\t%d\n\n",
            foundStudent.surname,
            foundStudent.birthdate,
            foundStudent.indexNumber,
            foundStudent.grades[Math], foundStudent.grades[Physics], foundStudent.grades[English]);
    }
    else
    {
        printf("\nPrzykro mi... brak takiego studenta w bazie...\n\n");
    }
}


static void SortStudentsAlphabetic(StudentsDatabase* database)
{
    printf("\nSortowanie bazy w toku...\n");
    qsort(database->students, database->numberOfStudents, sizeof(Student), Comparator);
    printf("\nBaza posortowana. OK!\n\n");
}


static void FindStudentWithHighestGrade(StudentsDatabase* database)
{
    int subjectNumber = MaxClass;
    printf("\nAby odszukac studenta o najwyzszej ocenie w przedmiocie, podaj ktory przedmiot cie interesuje:\n0. Matematyka\n1. Fizyka\n2. Angielski\n: ");
    scanf("%d", &subjectNumber);

    if (subjectNumber < MaxClass)
    {
        Student studentWithHighestDegree = FindStudentWithHighestDegreeInSubject(database, subjectNumber);
        printf("\nDane studenta:\nNazwisko:\t\t\t%s\nData urodzenia:\t\t\t%s\nIndeks:\t\t\t\t%d\nOcena - matematyka:\t\t%d\nOcena - fizyka:\t\t\t%d\nOcena - angielski:\t\t%d\n\n",
            studentWithHighestDegree.surname,
            studentWithHighestDegree.birthdate,
            studentWithHighestDegree.indexNumber,
            studentWithHighestDegree.grades[Math], studentWithHighestDegree.grades[Physics], studentWithHighestDegree.grades[English]);
    }
    else
    {
        printf("\nBrak takiego przedmiotu!\n\n");
    }
}


static void FindStudentWithHighestAverage(StudentsDatabase* database)
{
    Student studentWithHighestDegree = FindStudentInDatabaseWithHighestAverage(database);
    printf("\nDane studenta:\nNazwisko:\t\t\t%s\nData urodzenia:\t\t\t%s\nIndeks:\t\t\t\t%d\nOcena - matematyka:\t\t%d\nOcena - fizyka:\t\t\t%d\nOcena - angielski:\t\t%d\n\n",
        studentWithHighestDegree.surname,
        studentWithHighestDegree.birthdate,
        studentWithHighestDegree.indexNumber,
        studentWithHighestDegree.grades[Math], studentWithHighestDegree.grades[Physics], studentWithHighestDegree.grades[English]);
}



void PrintDatabase(StudentsDatabase* database)
{
    for (unsigned int index = 0; index < database->numberOfStudents; ++index)
    {
        printf("\nStudent z numerem w bazie %d:\nNazwisko:\t\t%s\nData urodzenia:\t\t%s\nIndeks:\t\t\t%d\n",
            index, database->students[index].surname, database->students[index].birthdate, database->students[index].indexNumber);
    }
}



void PerformUserOptionOnDatabase(StudentsDatabase* database, const Option option)
{
    switch (option)
    {
    case Insert:
        InsertStudentsIntoIndex(database);
        break;
    case Remove:
        RemoveStudentsUnderIndex(database);
        break;
    case Search:
        SearchStudentBySurname(database);
        break;
    case Sort:
        SortStudentsAlphabetic(database);
        break;
    case FindGreatestDegree:
        FindStudentWithHighestGrade(database);
        break;
    case FindGreatestAverage:
        FindStudentWithHighestAverage(database);
        break;

    case Print:
        PrintDatabase(database);
        break;

    case Quit:
        printf("Wylaczam program...\n\t\t\tDowidzenia!\n");
        break;

    default:
        printf("\nNie rozpoznaje takiej opcji...\n");
        break;
    }
}



