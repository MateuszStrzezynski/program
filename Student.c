#include "../Main.h"
#include "Student.h"

#include <string.h>
#include <stdlib.h>



static char* GetStudentDataUnderIndex(int* index, char* data)
{
    char* studentData = (char*)malloc(sizeof(char) * MAX_STUDENT_SINGLE_DATA_BUFFER_LENGTH);
    memset(studentData, '\0', MAX_STUDENT_SINGLE_DATA_BUFFER_LENGTH);

    for (int currentIndex = 0; currentIndex < MAX_STUDENT_SINGLE_DATA_BUFFER_LENGTH && data[*index] != ','; ++currentIndex, ++(*index))
    {
        studentData[currentIndex] = data[*index];
    }
    ++(*index);

    return studentData;
}


void ParseAndPrintStudentData(char* studentFullData)
{
    if (studentFullData != NULL)
    {
        int index = 0;
        char* nextData = GetStudentDataUnderIndex(&index, studentFullData);
        printf("\nNazwisko:\t%s\n", nextData);
        printf("Data urodzenia:\t%s\n", GetStudentDataUnderIndex(&index, studentFullData));
        printf("Indeks:\t\t\t%s\n", GetStudentDataUnderIndex(&index, studentFullData));
        printf("Ocena - matematyka:\t%s\n", GetStudentDataUnderIndex(&index, studentFullData));
        printf("Ocena - fizyka:\t\t%s\n", GetStudentDataUnderIndex(&index, studentFullData));
        printf("Ocena - angielski:\t%s\n", GetStudentDataUnderIndex(&index, studentFullData));
    }
}


Student ParseAndGetAsStudentRecord( char* studentFullData )
{
    Student studentRecord =
    {
        {'\0'},
        {'\0'},
        0,
        0,
        0,
        0
    };

    if (studentFullData != NULL)
    {
        int index = 0;
        strcpy(studentRecord.surname, GetStudentDataUnderIndex(&index, studentFullData));
        strcpy(studentRecord.birthdate, GetStudentDataUnderIndex(&index, studentFullData));
        studentRecord.indexNumber = atoi(GetStudentDataUnderIndex(&index, studentFullData));
        studentRecord.grades[Math] = atoi(GetStudentDataUnderIndex(&index, studentFullData));
        studentRecord.grades[Physics] = atoi(GetStudentDataUnderIndex(&index, studentFullData));
        studentRecord.grades[English] = atoi(GetStudentDataUnderIndex(&index, studentFullData));
    }

    return studentRecord;
}


Student CreateStudent(void)
{
    Student student =
    {
        { '\0' },
        { '\0' },
        0,
        0,
        0,
        0
    };

    printf("\nWprowadz nazwisko dodawanego studenta: ");
    scanf("%s", student.surname);

    printf("\nWprowadz date urodzenia w formacie DD.MM.RRRR: ");
    scanf("%s", &student.birthdate);

    printf("\nWprowadz indeks studenta: ");
    scanf("%d", &student.indexNumber);

    printf("\nPodaj ocene z matematyki: ");
    scanf("%d", &student.grades[Math]);

    printf("\nPodaj ocene z fizyki: ");
    scanf("%d", &student.grades[Physics]);

    printf("\nPodaj ocene z jezyka angielskiego: ");
    scanf("%d", &student.grades[English]);

    printf("\n");
    return student;
}


int Comparator(const void* p1, const void* p2)
{
    for (int character = 0; character < MAX_STUDENT_SINGLE_DATA_BUFFER_LENGTH; ++character)
    {
        if (((Student*)p1)->surname[character] > ((Student*)p2)->surname[character])
        {
            return 1;
        }
        else if (((Student*)p1)->surname[character] < ((Student*)p2)->surname[character])
        {
            return -1;
        }
    }

    return 0;
}

