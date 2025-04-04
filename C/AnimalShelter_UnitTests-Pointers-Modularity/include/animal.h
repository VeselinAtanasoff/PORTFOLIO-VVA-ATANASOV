#include <stdbool.h>
#ifndef ANIMAL_H
#define ANIMAL_H

#define MAX_LENGTH_NAME 30
#define MAX_NUMBER_ANIMAL 20

typedef enum
{
    CAT,
    CHINCHILLA,
    DOG,
    TURTLE,
} Species;

typedef struct
{
    char name[MAX_LENGTH_NAME];
    Species species;
    int chip_number;
} Animal;

// To do : declare your functions
bool add_animal(Animal *animal, int *number_of_animals, Animal new_animal);
bool search_animal(Animal *animals, int number_of_animals, char *name, Animal *temp_animals, int *found_animals);
bool update_species_by_chip_number(Animal *animals, int number_of_animals, int chip_number, Species new_species);
bool remove_animal_by_chip_number(Animal *animals, int *number_of_animals, int chip_number);


#endif