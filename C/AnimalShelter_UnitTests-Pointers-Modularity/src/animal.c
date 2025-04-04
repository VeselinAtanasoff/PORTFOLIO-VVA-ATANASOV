#include "animal.h"
#include <stdbool.h>
#include <string.h>

bool is_null(void* ptr) {
    

    return ptr == NULL;
}

bool add_animal(Animal *animals, int *number_of_animals, Animal new_animal)
{
    if (is_null(animals) || is_null(number_of_animals)) {
        return false;
    }
    if (*number_of_animals >= MAX_NUMBER_ANIMAL)
    {
        return false;
    }
    
    for(int i = 0; i < *number_of_animals; i++){
        if(animals->chip_number == new_animal.chip_number){
            return false;
        }
        animals++;
    }

    *animals = new_animal;
    *number_of_animals += 1;
    return true;
}

bool search_animal(Animal *animals, int number_of_animals, char *name, Animal *animals_by_name, int *n_of_animals_by_name)
{
    if (is_null(animals) || is_null(name) || is_null(animals_by_name) || is_null(n_of_animals_by_name)) {
        return false;
    }
    *n_of_animals_by_name = 0;

    for (int i = 0; i < number_of_animals; i++)
    {
        if (strcmp(animals->name, name) == 0)
        {
            *animals_by_name = *animals;
            animals_by_name++;
            *n_of_animals_by_name += 1;
        }
        animals++;
    }

    if (*n_of_animals_by_name == 0)
    {
        return false;
    }

    return true;
}


bool update_species_by_chip_number(Animal *animals, int number_of_animals, int chip_number, Species new_species)
{
    
    if (is_null(animals)) {
        return false;
    }
    if (new_species < CAT || new_species > TURTLE)
    {
        return false;
    }

    for (int i = 0; i < number_of_animals; i++)
    {
        if (animals->chip_number == chip_number)
        {
            animals->species = new_species;
            return true;
        }
        animals++;
    }
}

bool remove_animal_by_chip_number(Animal *animals, int *number_of_animals, int chip_number)
{
    if (is_null(animals) || is_null(number_of_animals)) {
        return false;
    }

    if (*number_of_animals == 0){
        return false;
    }
    Animal *current_animal = animals;
    Animal *last_animal = animals + *number_of_animals - 1;

    while (current_animal <= last_animal)
    {
        if (current_animal->chip_number == chip_number)
        {
            if(current_animal == last_animal){
                *number_of_animals -= 1;
                return true;
            }
            *current_animal = *last_animal;
            *number_of_animals -= 1;
            return true;
        }
        current_animal++;
    }

    return false;
}






