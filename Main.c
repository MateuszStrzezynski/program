#include "Main.h"

#include <stdlib.h>
#include <stdio.h>

#include "Database/DatabaseLoader.h"
#include "Database/Database.h"
#include "Controller/Controller.h"



int main(void)
{
    printf("\nOto program stanowiacy symulacje bazy danych studentow.\n\t\tWitaj!\n\n");

    char* fileName = (char*)malloc(sizeof(char)*MAX_STUDENTS_FILEBASE_NAME_LENGTH);
    printf("\nPodaj nazwe pliku, ktora zawiera dane studentow (oddzielone przecinkami): ");
    scanf("%s", fileName);

    printf("\n\nRozpoczynam pobieranie danych z bazy %s...\n", fileName);


    while (ReadAndPrintStudentsDataFromFile(fileName) == false)
    {
        printf("Brak takiego pliku! Podaj nazwe jeszcze raz: ");
        scanf("%s", fileName);
    }

    StudentsDatabase* database = CreateDatabase();
    ReadAndParseStudentsDataIntoDatabase(database, fileName);


    printf("\nBaza danych studentow zostala poprawnie wczytana.\n\n");
    Option option = 0;
    while (option != Quit)
    {
        printf("Wybierz jedna opcje z ponizszych:\n"
            "1. Wprowadz studentow\n"
            "2. Usun rekord\n"
            "3. Szukaj w bazie\n"
            "4. Sortuj baze\n"
            "5. Znajdz najwysza ocene\n"
            "6. Znajdz najwyzsza srednia\n"
            "7. Wyswietl baze\n"
            "10. Wyjdz\n:");
        scanf("%d", &option);

        PerformUserOptionOnDatabase(database, option);
    }



    getchar();
    return EXIT_SUCCESS;
}