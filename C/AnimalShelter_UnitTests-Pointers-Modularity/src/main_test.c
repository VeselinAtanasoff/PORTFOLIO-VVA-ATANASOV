#include "animal.h"
#include "unity.h"



#define CHIP_NUMBER1 1
#define CHIP_NUMBER2 2
#define CHIP_NUMBER3 3
#define CHIP_NUMBER4 4



void setUp(void)
{
    // To do: optionally add the code to be executed before each unit test

    
}

void tearDown(void)
{
    // To do: optionally add the code to be executed after each unit test
   
}

void test_add_animal(void) {
    Animal animals[MAX_NUMBER_ANIMAL];
    int number_of_animals = 0;
    Animal new_animal1 = {"Test1", CAT, CHIP_NUMBER1};
    Animal new_animal2 = {"Test2", DOG, CHIP_NUMBER2};
    Animal new_animal3 = {"Test3", TURTLE, CHIP_NUMBER3};

    Animal new_animal = {"Test4", CHINCHILLA, CHIP_NUMBER4};
    int expected_number_of_animals = 4;

    add_animal(animals, &number_of_animals, new_animal1);
    add_animal(animals, &number_of_animals, new_animal2);
    add_animal(animals, &number_of_animals, new_animal3);
    add_animal(animals, &number_of_animals, new_animal);

    TEST_ASSERT_EQUAL_INT(expected_number_of_animals, number_of_animals);
    TEST_ASSERT_EQUAL_INT(new_animal.chip_number, animals[3].chip_number);
    TEST_ASSERT_EQUAL_STRING(new_animal.name, animals[3].name);
    TEST_ASSERT_EQUAL(new_animal.species, animals[3].species);
    
}

void test_search_animal(void) {
    
    Animal animals_by_name[MAX_NUMBER_ANIMAL];
    int n_of_animals_by_name = 0;
    Animal animals[MAX_NUMBER_ANIMAL];
    int number_of_animals = 0;
    Animal new_animal1 = {"Test1", CAT, CHIP_NUMBER1};
    Animal new_animal2 = {"Test2", DOG, CHIP_NUMBER2};
    Animal new_animal3 = {"Test3", TURTLE, CHIP_NUMBER3};
    Animal new_animal = {"Test2", DOG, CHIP_NUMBER4};
    int expected_n_of_animals_by_name = 2;

    add_animal(animals, &number_of_animals, new_animal1);
    add_animal(animals, &number_of_animals, new_animal2);
    add_animal(animals, &number_of_animals, new_animal3);
    add_animal(animals, &number_of_animals, new_animal);
    search_animal(animals, number_of_animals, "Test2", animals_by_name, &n_of_animals_by_name);

    TEST_ASSERT_EQUAL_INT(expected_n_of_animals_by_name, n_of_animals_by_name);
    TEST_ASSERT_EQUAL_INT(CHIP_NUMBER2, animals_by_name[0].chip_number);
    TEST_ASSERT_EQUAL_INT(CHIP_NUMBER4, animals_by_name[1].chip_number);
    
}

void test_update_species_by_chip_number(void) {
    Animal animals[MAX_NUMBER_ANIMAL];
    int number_of_animals = 0;
    Animal new_animal1 = {"Test1", CAT, CHIP_NUMBER1};
    Animal new_animal2 = {"Test2", DOG, CHIP_NUMBER2};
    Animal new_animal3 = {"Test3", TURTLE, CHIP_NUMBER3};
    
    Species expected_species = DOG;

    add_animal(animals, &number_of_animals, new_animal1);
    add_animal(animals, &number_of_animals, new_animal2);
    add_animal(animals, &number_of_animals, new_animal3);
    update_species_by_chip_number(animals, number_of_animals, CHIP_NUMBER1, DOG);
    
    TEST_ASSERT_EQUAL_INT(expected_species, animals[0].species);
    
}

void test_remove_animal_by_chip_number(void) {
   Animal animals[MAX_NUMBER_ANIMAL];
    int number_of_animals = 0;
    Animal new_animal1 = {"Test1", CAT, CHIP_NUMBER1};
    Animal new_animal2 = {"Test2", DOG, CHIP_NUMBER2};
    Animal new_animal3 = {"Test3", TURTLE, CHIP_NUMBER3};
    int expected_number_of_animals = 2;

    add_animal(animals, &number_of_animals, new_animal1);
    add_animal(animals, &number_of_animals, new_animal2);
    add_animal(animals, &number_of_animals, new_animal3);
    remove_animal_by_chip_number(animals, &number_of_animals, CHIP_NUMBER1);

    TEST_ASSERT_EQUAL_INT(expected_number_of_animals, number_of_animals);
    TEST_ASSERT_EQUAL_INT(CHIP_NUMBER3, animals[0].chip_number);
    
}


int main(void)
{
    UnityBegin(0);

    // To do : add your unit tests
    RUN_TEST(test_add_animal);
    RUN_TEST(test_search_animal);
    RUN_TEST(test_update_species_by_chip_number);
    RUN_TEST(test_remove_animal_by_chip_number);
    
    return UnityEnd();
}

