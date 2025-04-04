#include <stdio.h>
#include <stdbool.h>
#include "animal.h"

Animal animals[MAX_NUMBER_ANIMAL]; // initiase with e.g. 4 animals
Animal animals_by_name[MAX_NUMBER_ANIMAL];
int number_of_animals = 0;
int n_of_animals_by_name = 0;

bool show_animals(Animal *animals, int number_of_animals);
void add_animal_menu();
void search_animal_menu();
void update_species_menu();
void remove_animal_menu();

int main()
{

    int option = -1;

    while (option != 0)
    {
        /*
         * Menu of the animal shelter
         * Mandatory assignment (option 0 to 5)
         * Optional assignment (option 6)
         */
        printf("\nMENU\n====\n");
        printf("0: Quit program\n");
        printf("1: Show all animals\n");
        printf("2: Add an animal\n");
        printf("3: Search animals by name \n");
        printf("4: Update species by id\n");
        printf("5: Remove an animal by id\n");
        printf("6: Sort animals by species and name\n");

        scanf("%d", &option);

        switch (option)
        {
        // To do: add the code to be executed in each case
        case 0:
            printf("Quit program\n");
            break;
        case 1:

            if (!show_animals(animals, number_of_animals))
            {
                printf("No animals in the shelter\n");
            }
            break;
        case 2:
            add_animal_menu();
            printf("Number of animals: %d\n", number_of_animals);   
            break;
        case 3:
            search_animal_menu();
            break;
        case 4:
            update_species_menu();
            break;
        case 5:
            remove_animal_menu();
            break;
        case 6:
            break;
        default:
            printf("ERROR: option %d is not available\n", option);
            break;
        }
    }
    return 0;
}

bool show_animals(Animal *animals, int number_of_animals)
{
    if (number_of_animals == 0)
    {
        return false;
    }
    for (int i = 0; i < number_of_animals; i++)
    {
        printf("Name: %s  ", animals->name);
        printf("Species: %d  ", animals->species);
        printf("Chip number: %d  ", animals->chip_number);
        printf("\n");
        animals++;
    }
    return true;
}

void add_animal_menu()
{
    Animal new_animal;
    printf("Enter the name of the animal: ");
    scanf("%s", &new_animal.name);
    printf("Enter the species of the animal (0=CAT, 1=CHINCHILLA, 2=DOG, 3=TURTLE): ");
    scanf("%d", &new_animal.species);
    printf("Enter the chip number of the animal: ");
    scanf("%d", &new_animal.chip_number);

    if (!add_animal(animals, &number_of_animals, new_animal))
    {
        printf("The animal was not added\n");
    }
}

void search_animal_menu()
{
    char name[MAX_LENGTH_NAME];
    printf("Enter the name of the animal: ");
    scanf("%s", &name);

    if (!search_animal(animals, number_of_animals, name, animals_by_name, &n_of_animals_by_name))
    {
        printf("No animals with this name found\n");
    }
    else
    {
        show_animals(animals_by_name, n_of_animals_by_name);
    }
}

void update_species_menu()
{
    int chip_number;
    Species new_species;
    printf("Enter the chip number of the animal: ");
    scanf("%d", &chip_number);
    printf("Enter the new species of the animal (0=CAT, 1=CHINCHILLA, 2=DOG, 3=TURTLE): ");
    scanf("%d", &new_species);

    if (!update_species_by_chip_number(animals, number_of_animals, chip_number, new_species))
    {
        printf("The species is not supported or the chip number does not exist\n");
    }
    else
    {
        printf("The species is updated\n");
    }
}

void remove_animal_menu()
{
    int chip_number_to_remove;
    printf("Enter the chip number of the animal: ");
    scanf("%d", &chip_number_to_remove);

    if (!remove_animal_by_chip_number(animals, &number_of_animals, chip_number_to_remove))
    {
        printf("The chip number does not exist\n");
    }
    else
    {
        printf("The animal is removed\n");
    }
}