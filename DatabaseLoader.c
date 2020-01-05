#include "DatabaseLoader.h"
#include "Database.h"

#include <stdio.h>



bool ReadAndPrintStudentsDataFromFile(char* dataFileName)
{
    FILE* studentsDataFile = fopen(dataFileName, "r");
    bool result = false;

    if (studentsDataFile == NULL)
    {
        printf("\nBLAD: Brak pliku!\n");
    }
    else
    {
        char nextDatabaseCharacter = '\0';
        while (nextDatabaseCharacter != EOF)
        {
            char nextRecord[MAX_FULL_DATA_LENGTH] = { '\0' };

            nextDatabaseCharacter = fgetc(studentsDataFile);
            for (int dataLength = 0; nextDatabaseCharacter != '\n' && nextDatabaseCharacter != EOF && dataLength < MAX_SINGLE_DATA_BUFFER_LENGTH; ++dataLength)
            {
                nextRecord[dataLength] = nextDatabaseCharacter;
                nextDatabaseCharacter = fgetc(studentsDataFile);
            }

            ParseAndPrintStudentData(nextRecord);
        }
        result = true;
    }

    fclose(studentsDataFile);
    return result;
}


bool ReadAndParseStudentsDataIntoDatabase(StudentsDatabase* database, char* dataFileName)
{
    FILE* studentsDataFile = fopen(dataFileName, "r");
    bool result = false;

    if (studentsDataFile == NULL)
    {
        printf("\nBLAD: Brak pliku!\n");
    }
    else
    {
        char nextDatabaseCharacter = '\0';
        while (nextDatabaseCharacter != EOF)
        {
            char nextRecord[MAX_FULL_DATA_LENGTH] = { '\0' };

            nextDatabaseCharacter = fgetc(studentsDataFile);
            for (int dataLength = 0; nextDatabaseCharacter != '\n' && nextDatabaseCharacter != EOF && dataLength < MAX_SINGLE_DATA_BUFFER_LENGTH; ++dataLength)
            {
                nextRecord[dataLength] = nextDatabaseCharacter;
                nextDatabaseCharacter = fgetc(studentsDataFile);
            }

            AddStudent(database, ParseAndGetAsStudentRecord(nextRecord));
        }

        result = true;
    }

    fclose(studentsDataFile);
    return result;
}



