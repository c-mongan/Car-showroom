
#define _CRT_SECURE_NO_WARNINGS 0
#define bool int
#define false 0
#define true (!false)

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Preprocessor Variable
#define SIZE 5

//Stucture template for data part of the linked list
struct car
{
    int prevOwners;
    char regNum[20];
    char make[20];
    char model[20];
    int reserved;
    int deposit;
};

//Stucture template for one node
struct LinearNode
{
    struct car *element;
    struct LinearNode *next;
};

// Function prototypes
void addCars();                //adding cars to front of the list
void deleteCar(char aReg[10]); //delete a specific car
void viewAllCars();
bool isEmpty();
void readFromFile(); //read cars from file
void searchCar();
void changeDeposit();

// Global Variables
struct LinearNode *list = NULL; //front of list

struct LinearNode *last = NULL; //pointer to last car in list

/**************MAIN FUNCTION*******************/
int main()
{

    int firstOption;

    printf("Add cars manually 0 or add from file 1 : ");
    scanf("%d", &firstOption);

    if (firstOption == 0)
    {
        addCars();
    }
    else
    {

        if (fopen("cars.dat", "r"))
        {
            readFromFile();
        }
        else
        {
            printf("file not found \n");
        }
    }

    bool run = true;

    while (run)
    {

        int menuOption;
        printf("menu options: \n 1 - View all cars \n 2 - Delete a car \n 3 - Find a car \n 4 - Reserve a car \n 5 - Exit program\n");
        scanf("%d", &menuOption);

        if (menuOption == 1)
        {
            viewAllCars();
        }
        if (menuOption == 2)
        {

            char delReg[10];
            printf("Please enter the registration of the car you wish to sell : ");
            scanf("%s", delReg);
            deleteCar(delReg);
        }

        if (menuOption == 3)
        {

            searchCar();
        }

        if (menuOption == 4)
        {
            changeDeposit();
        }

        if (menuOption == 5)
        {
            run = false;
        }
    }
}

void addCars()
{
    int i;
    int anOwner;
    char aReg[10];
    char aMake[20];
    char aModel[20];
    int aReservation;
    int resAmount;
    struct LinearNode *aNode;
    struct car *anElement;

    // add SIZE nodes to the list
    for (i = 0; i < SIZE; i++)
    {
        printf("Enter a registration for car %d:\n", i + 1);
        scanf("%s", aReg);

        anElement = (struct car *)malloc(sizeof(struct car));
        aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));

        printf("Enter the amount of previous owners  for car (Must be less than 4)%d:\n", i + 1);
        scanf("%d", &anOwner);

        anElement->prevOwners = anOwner;
        printf("Enter a reg for for car in the format yy-D-nnnn %d:\n", i + 1);
        scanf("%s", aReg);
        strcpy(anElement->regNum, aReg);
        printf("Enter a make for for car %d\n: ", i + 1);
        scanf("%s", aMake);
        strcpy(anElement->make, aMake);
        printf("Enter a model for for car %d:\n ", i + 1);
        scanf("%s", aModel);
        strcpy(anElement->model, aModel);
        printf("Enter 1 if the Car is reserved and 0 if it isn't %d:\n", i + 1);
        scanf("%d", &aReservation);
        anElement->reserved = aReservation;

        while (aReservation == 1)
        {

            printf("If car is reserved , please enter the amount deposited %d\n:", i + 1);
            scanf("%d", &resAmount);
            anElement->deposit = resAmount;
            aReservation = 0;
        }

        if (aNode == NULL)
            printf("Error - no space in the showroom for the new car\n");
        else
        { // add data part to the node
            aNode->next = NULL;
            aNode->element = anElement;

            //add node to end of the list
            if (isEmpty())
            {
                list = aNode;
                last = aNode;
            }
            else
            {
                last->next = aNode;
                last = aNode;
            } //end else
        }     //end else
    }         //end for
} //end addCars

void viewAllCars()
{
    struct LinearNode *current;

    if (isEmpty())
        printf("Error - there are no cars in the showroom\n");
    else
    {
        current = list;
        while (current != NULL)
        {

            printf("Car owner count is %d\n", current->element->prevOwners);
            printf("Car reg is %s\n", current->element->regNum);
            printf("Car make is %s\n", current->element->make);
            printf("Car model is %s\n", current->element->model);
            printf("Car Reserved? 1=Yes , 0=No : %d\n", current->element->reserved);
            printf("The deposit amount on the car is :%d\n \n \n", current->element->deposit);

            current = current->next;
        } //end while
    }     //end else
} //end viewAllCars

void deleteCar(char aReg[10])
{
    struct LinearNode *current, *previous;
    bool notFound = true;

    if (isEmpty())
        printf("Error - there are no cars in the showroom\n");
    else
    {
        current = previous = list;

        while (notFound && current != NULL)
        {
            if (strcmp(aReg, current->element->regNum) == 0)
                notFound = false;
            else
            {
                previous = current;
                current = current->next;
            } //end else
        }     //end while

        if (notFound)
            printf("Error - there is not such car with this registration %s\n", aReg);
        else
        {
            if (current == list)
            {
                list = list->next;
                free(current);
            } //end else
            else
            {
                previous->next = current->next;
                free(current);
            } //end else
            printf("Car with reg: %s has been deleted\n", aReg);
            printf("The remaining cars are:\n \n \n");
            viewAllCars();

        } //end else
    }     //end else
} // end deleteCar

bool isEmpty()
{
    if (list == NULL)
        return true;
    else
        return false;
}

void readFromFile()
{

    FILE *filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];
    filePointer = fopen("cars.dat", "r");

    while (fgets(buffer, bufferLength, filePointer))
    {

        struct LinearNode *aNode;
        struct car *anElement;
        anElement = (struct car *)malloc(sizeof(struct car));
        aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));

        int init_size = strlen(buffer);
        char delim[] = " ";
        char *ptr = strtok(buffer, delim);
        char reserved[20];
        char deposit[20];

        int prevOwnersI;
        sscanf(ptr, "%d", &prevOwnersI);
        anElement->prevOwners = prevOwnersI;
        ptr = strtok(NULL, delim);

        strcpy(anElement->regNum, ptr);
        ptr = strtok(NULL, delim);

        strcpy(anElement->make, ptr);
        ptr = strtok(NULL, delim);

        strcpy(anElement->model, ptr);
        ptr = strtok(NULL, delim);

        strcpy(reserved, ptr);
        int reservedI;
        sscanf(reserved, "%d", &reservedI);
        anElement->reserved = reservedI;
        ptr = strtok(NULL, delim);

        strcpy(deposit, ptr);
        int depositI;
        sscanf(deposit, "%d", &depositI);
        anElement->deposit = depositI;

        if (aNode == NULL)
            printf("Error - no space for the new car in the showroom\n");
        else
        { // add data part to the node
            aNode->next = NULL;
            aNode->element = anElement;

            //add node to end of the list
            if (isEmpty())
            {
                list = aNode;
                last = aNode;
            }
            else
            {
                last->next = aNode;
                last = aNode;
            } //end else
        }     //end else
    }

    fclose(filePointer);
}

void searchCar()
{

    char searchReg[7];

    printf("Please enter the registration of the car you wish to search for. Note: Must be in the format yyDnnnn\n");
    scanf("%s", searchReg);

    struct LinearNode *current, *previous;
    bool notFound = true;

    if (isEmpty())
        printf("Error - there are no cars in the showroom\n");
    else
    {
        current = previous = list;

        while (notFound && current != NULL)
        {
            if (strcmp(searchReg, current->element->regNum) == 0)
            {

                notFound = false;
                printf("car found with reg %s\n \n \n", current->element->regNum);
                ;
                printf("Car owner count is %d\n", current->element->prevOwners);
                printf("Car reg is %s\n", current->element->regNum);
                printf("Car make is %s\n", current->element->make);
                printf("Car model is %s\n", current->element->model);
                printf("Car Reserved? 1=Yes , 0=No : %d\n", current->element->reserved);
                printf("The deposit amount on the car is :%d\n", current->element->deposit);
            }
            else
            {
                previous = current;
                current = current->next;
            } //end else
        }     //end while

        if (notFound)
        {
            printf("Error - there is no such car with registration :%s\n", searchReg);
        }
    }
} // end deleteCar

void changeDeposit()
{

    char searchReg[7];

    printf("Please enter the registration of the car you wish to modify\n");
    scanf("%s", searchReg);

    struct LinearNode *current, *previous;
    bool notFound = true;

    if (isEmpty())
        printf("Error - there are no cars in the showroom\n");
    else
    {
        current = previous = list;

        while (notFound && current != NULL)
        {
            if (strcmp(searchReg, current->element->regNum) == 0)
            {
                notFound = false;

                if (current->element->reserved == 1)
                {
                    printf("Car is already Reserved");
                }
                else
                {

                    printf("The deposit amount on the car is :%d\n", current->element->deposit);

                    int newDeposit;

                    printf("Please enter the new Deposit\n");
                    scanf("%d", &newDeposit);

                    printf("The deposit amount on the car is :%d\n", current->element->deposit);

                    current->element->deposit = newDeposit;
                }
            }
            else
            {
                previous = current;
                current = current->next;
            } //end else
        }     //end while

        if (notFound)
        {
            printf("Error - there is no such car with registration : %s\n", searchReg);
        }
    }
} // end deleteCar
