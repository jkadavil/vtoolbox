/*  Joshua Kadavil
 * The following code is Part 1 of Project 2 which implements all the functions from pov.h provided from Gang Qu.
 * This includes GetModel(), Get Vehicle(), PrintVehicle(), PrintAllVehicles(), PrintAllCheaper(), PrintAllExpensive(), and
 * VehicleYear(). All these functions mentioned use text files with information on the manufacturer
 * and information on each POV(Pre-Owned Vehicle). We also have our own file which has vehicle information
 * for all the vehicles placed in it which will be used in stage 2. For this stage one we are not using options
 * such as search, buy, and exit.
 *
 *
 * Started: 4/12/2024    Ended: 5/6/2024
 *
 *  4/12/2024: Implemented GetVehicle function and used similar structure from GetModel() to get the vehicles
 *             Tested the GetVehicle() function and worked as needed by trying it with p2.c
 *  4/13/2024: Implemented PrintVehicle() function and went through linked list of models to help find model for each vehicle
 *             Did not work initially, but I added <string.h> to properly compare
 *             Tested PrintVehicle() and worked as intended with p2.c provided by Gang Qu
 *             Created PrintAllVehicles() through implementing PrintVehicle into the function
 *             Implemented PrintAllCheaper() and PrintAllExpensive()
 *             Tested all functions and worked as needed according to testing using p2.c and text files provided by Gang Qu
 *  4/14/2024: Began working on VehicleYear and had errors regarding my filtered linked list of vehicles
 *             Realized code was not working due to not linking the new node to the tail of the filtered list
 *             Tested and realized code worked based off testing from text files and p2.c provided by Gang Qu
 *             Saw that VIN codes within text file had errors resulting in an output year of 0
 *  4/16/2024:  Left year as 0 due to VIN code error according to TA and completed commenting and project header
 *
 *  5/1/2024: Created multiple different functions to return the head of the new filtered list base don user input
 *            These new functions followed the same structure as VehicleYear, except for mileage, price, etc.
 *            Expanded search criteria to include multiple brackets for price and mileage
 *            Added a specification for the search and buy function so when the list of vehicles are zero we return to the main menu
 *
 *  5/3/2024: Found errors regarding deleting a vehicle from the database however fixed it by properly freeing the data
 *            Also added additional conditionals based on if the vehicle is at the head, tail, or in between the linked list of vehicles
 *            Began working on compare and sell function by asking the user for appropriate input
 *            Added comments where needed for the function as well
 *
 *  5/5/2024: Created a match counter so as I loop through vehicles I can find out what vehicles fit 2 of the 3 specifications
 *            Asked user for a price and used random number generator between 1 and 2 to accept the offer
 *            From there I created a new vehicle and added the necessary attributes into the new vehicle
 *            Created a VIN number that could be accessed in the vehicle structure, and for digits not filled placed random numbers
 *
 *  5/6/2024: Tested code in grace and placed it into WinSCP for submission
 *            Added some more comments regarding the compare and buy function and reviewed stage 1 functions to ensure everything worked
 *
 *
 *  Special compilation instruction prior to using below commands: gcc (insert file) -std=c99
 *
 *  For stage 1 no commands needed for pov.c. File is implemented through combined use of p2.c and pov.h
 *
 *  For TA: I included a global variable to keep track of transactions when they occur
 *
 *  No new data structures were added based on the template Gang Qu provided. Queries and offers for selling and
 *  buying have not been implemented yet as they are part of stage 2 and not stage 1. However, as part of stage 1
 *  vehicle information has been stored in a file in order to later address these queries for stage 2.
 *
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include "pov.h"

const char Color[12][10] = {"Red", "Blue", "White", "Silver", "Orange", "Yellow",
                            "Black", "Lime", "Green", "Oliver", "Purple", "Gray"};
// 12 different colors of the vehicles
// Keep this in your pov.c

typedef struct vin_detail
{ MODEL *mp;                    // a pointer to the MODEL structure
    int year;                     // year of made
    VEHICLE *next;                // pointer to next VEHICLE
} VIN_DETAIL;

VIN_DETAIL * v_detail;
int trans = 0;


MODEL * GetModel(FILE *fp)
{ static MODEL *manu;
  int No_manu = 0;		// number of models in input file fp

  int i, j, k;
  char ch;
  MODEL *tmp, *cur;

  tmp = NEW(MODEL);
  if (tmp == NULL) return NULL;

  i = 0;
  while(fscanf(fp, "%c", &ch)!= EOF)
  { tmp->code[0] = ch;
    fscanf(fp, "%c%c", &(tmp->code[1]), &(tmp->code[2]));
				// &tmp.code[2] should work as well
    tmp->code[3] = '\0';

    fscanf(fp, "%c", &ch);	// skip the space after code
    j = 0;			// gent model name[]
    do
    { fscanf(fp, "%c", &ch);
      tmp->name[j] = ch;
      j++;
    }while(ch!='\n');
    tmp->name[j-1] = '\0';
    tmp->info = NULL;		// last MODEL in the list
    if (i==0) manu = tmp;	// manu is the head of the list
    else cur->info = tmp;
    cur = tmp;			// stay at the current tail of the list

    i++;
    tmp = NEW(MODEL);
    if (tmp == NULL) return NULL;
  }

  return manu;
}

VEHICLE *GetVehicle(FILE *fp)
{
    static VEHICLE *head; // head of the list of vehicles
    int num_vehicles = 0; // number of vehicles in input file fp

    int i,j;
    char ch;
    VEHICLE *tmp, *cur;

    tmp = NEW(VEHICLE);
    if (tmp == NULL)
        return NULL;

    i = 0;
    while (fscanf(fp, "%c", &ch)!= EOF)
    {
        //retrieve the VIN code from the file
        tmp->VIN[0] = ch;
       for(int k = 1; k < 17; k++){
           fscanf(fp, "%c", &(tmp->VIN[k]));
       }
       //add null terminating character
       tmp->VIN[17] = '\0';

        fscanf(fp, "%c", &ch);

        j = 0;			// get color name[]
        do
        { fscanf(fp, "%c", &ch);
            tmp->color[j] = ch;
            j++;
        }while(ch!=';');
        tmp->color[j-1] = '\0';


// Read the mileage directly as an integer
        fscanf(fp, "%d", &(tmp->mileage));

        fscanf(fp, "%c", &ch); // Skip the semicolon

// Read the price as a float
        fscanf(fp, "$%f", &(tmp->price));

// Skip to the end of the line
        while (ch != '\n' && ch != EOF) {
            fscanf(fp, "%c", &ch);
        }

        tmp->info = NULL; // last VEHICLE in the list
        if (i == 0)
            head = tmp; // head is the head of the list
        else
            cur->info = tmp;
        cur = tmp; // stay at the current tail of the list

        i++;
        tmp = NEW(VEHICLE);
        if (tmp == NULL)
            return NULL;
    }

    return head;
}

void PrintVehicle(VEHICLE *vehicle, FILE *outputFile) {
    int year = 0;
    char year_char = vehicle->VIN[10];

    //checks the 10th character in VIN and use conditionals to check what year model is
    //If ASCII value is within numerical range just add 2000 to provide the year
    if((int)year_char >= 49 && (int)year_char <= 57){
        year = (year_char - '0') + 2000;
    }
    //check for letter and assign year to variable
    if(year_char == 'S'){
        year = 1995;
    }
    else if(year_char == 'T'){
        year = 1996;
    }
    else if(year_char == 'V'){
        year = 1997;
    }
    else if(year_char == 'W'){
        year = 1998;
    }
    else if(year_char == 'X'){
        year = 1999;
    }
    else if(year_char == 'Y'){
        year = 2000;
    }
    else if(year_char == 'A'){
        year = 2010;
    }
    else if(year_char == 'B'){
        year = 2011;
    }
    else if(year_char == 'C'){
        year = 2012;
    }
    else if(year_char == 'D'){
        year = 2013;
    }
    else if(year_char == 'E'){
        year = 2014;
    }
    else if(year_char == 'F'){
        year = 2015;
    }
    else if(year_char == 'G'){
        year = 2016;
    }
    else if(year_char == 'H'){
        year = 2017;
    }
    else if(year_char == 'J'){
        year = 2018;
    }
    else if(year_char == 'K'){
        year = 2019;
    }
    else if(year_char == 'L'){
        year = 2020;
    }
    else if(year_char == 'M'){
        year = 2021;
    }
    else if(year_char == 'N'){
        year = 2022;
    }
    else if(year_char == 'P'){
        year = 2023;
    }
    else if(year_char == 'R'){
        year = 2024;
    }


    //Create a character array with first 3 characters from the VIN for manufacturer
    char identifier[4] = "";
    strncpy(identifier, vehicle->VIN, 3);

    // Variable to store the name of the matching model
    char model_name[23] = "";

    // Loop through the linked list of MODELS
    MODEL *current = All_Models;
    while (current != NULL) {
        // Check if the code from the current MODEL is equal to the identifier
        if (strcmp(current->code, identifier) == 0) {
            // Copy the name to the variable
            strncpy(model_name, current->name, sizeof(model_name));
            // Exit the loop once a match is found
            break;
        }

        // Move to the next MODEL in the linked list
        current = current->info;
    }
    model_name[strlen(model_name)] = '\0';
    //Check if model was found from the model list
    if(model_name == ""){
        printf("No model found!");
    }


    // Print vehicle information to the screen
    printf("%d %s %s, %d miles, %.2f\n", year, vehicle->color, model_name, vehicle->mileage, vehicle->price);

    // Print vehicle information to the output file
    if (outputFile != NULL) {
        fprintf(outputFile, "%d %s %s, %d miles, %.2f\n", year, vehicle->color, model_name, vehicle->mileage, vehicle->price);
    } else {
        printf("Failed to write to output file.\n");
    }
}

void PrintAllVehicles(VEHICLE *head, FILE *outputFile) {
    // Loop through the linked list of vehicles
    VEHICLE *current = head;
    while (current != NULL) {
        // Print the information of the current vehicle
        PrintVehicle(current, outputFile);

        // Move to the next vehicle in the linked list
        current = (VEHICLE *)current->info;
    }
}

void PrintAllCheaper (VEHICLE *p, FILE *fp, float c){
    //Start with p as head of linked list of vehicles
    VEHICLE *current = p;
    while(current != NULL){
        //Check if price of vehicle is less than or equal to value of c
        if((current->price) <= c){
            //Print vehicle on screen and put in output file
            PrintVehicle(current, fp);
        }
        // Move to the next vehicle in the linked list
        current = (VEHICLE *)current->info;
    }
}

void PrintAllExpensive (VEHICLE *p, FILE *fp, float c){
    //Start with p as head of linked list of vehicles
    VEHICLE *current = p;
    while(current != NULL){
        //Check if price of vehicle is greater than or equal to value of c
        if((current->price) >= c){
            //Print vehicle on screen and put in output file
            PrintVehicle(current, fp);
        }
        // Move to the next vehicle in the linked list
        current = (VEHICLE *)current->info;
    }
}

VEHICLE *VehicleYear(VEHICLE *p, int k) {
    //check if year is within valid range
    if(k > 2024 || k < 1995){
        printf("Year is not within valid range!");
        exit(1);
    }
    // Initialize a pointer to the head of the filtered list
    VEHICLE *filteredList = NULL;
    // Initialize a pointer to the tail of the filtered list
    VEHICLE *tail = NULL;

    // Traverse the linked list of vehicles
    VEHICLE *current = p;
    while (current != NULL) {
        // Extract the year portion from the VIN (assuming it's the 10th character)
        char year_char = current->VIN[10];
        int year = 0;
        //checks the 10th character in VIN and use conditionals to check what year model is
        if((int)year_char >= 49 && (int)year_char <= 57){
            year = (year_char - '0') + 2000;
        }
        if(year_char == 'S'){
            year = 1995;
        }
        else if(year_char == 'T'){
            year = 1996;
        }
        else if(year_char == 'V'){
            year = 1997;
        }
        else if(year_char == 'W'){
            year = 1998;
        }
        else if(year_char == 'X'){
            year = 1999;
        }
        else if(year_char == 'Y'){
            year = 2000;
        }
        else if(year_char == 'A'){
            year = 2010;
        }
        else if(year_char == 'B'){
            year = 2011;
        }
        else if(year_char == 'C'){
            year = 2012;
        }
        else if(year_char == 'D'){
            year = 2013;
        }
        else if(year_char == 'E'){
            year = 2014;
        }
        else if(year_char == 'F'){
            year = 2015;
        }
        else if(year_char == 'G'){
            year = 2016;
        }
        else if(year_char == 'H'){
            year = 2017;
        }
        else if(year_char == 'J'){
            year = 2018;
        }
        else if(year_char == 'K'){
            year = 2019;
        }
        else if(year_char == 'L'){
            year = 2020;
        }
        else if(year_char == 'M'){
            year = 2021;
        }
        else if(year_char == 'N'){
            year = 2022;
        }
        else if(year_char == 'P'){
            year = 2023;
        }
        else if(year_char == 'R'){
            year = 2024;
        }

        // Check if the vehicle was made in the given year
        if (year == k) {
            // Allocate memory for a new vehicle node
            VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
            if (newVehicle == NULL) {
                printf( "Memory allocation failed\n");
                // Free memory of the filtered list before returning NULL
                while (filteredList != NULL) {
                    VEHICLE *temp = filteredList;
                    filteredList = (VEHICLE *)filteredList->info;
                    free(temp);
                }
                // Return NULL if memory allocation fails
                return NULL;
            }

            // Copy the current vehicle's data to the new node
            strcpy(newVehicle->VIN, current->VIN);
            strcpy(newVehicle->color, current->color);
            newVehicle->mileage = current->mileage;
            newVehicle->price = current->price;
            newVehicle->info = NULL;

            // If it's the first node in the filtered list
            if (filteredList == NULL) {
                filteredList = newVehicle;
                tail = newVehicle;
            } else {
                // Link the new node to the tail of the filtered list
                tail->info = newVehicle;
                tail = newVehicle;
            }
        }

        // Move to the next vehicle in the linked list
        current = (VEHICLE *)current->info;
    }

    return filteredList;
}

VEHICLE *VehicleManufacturer(VEHICLE *p, char input_code[4]){
    // Initialize a pointer to the head of the filtered list
    VEHICLE *filtered_list = NULL;
    // Initialize a pointer to the tail of the filtered list
    VEHICLE *tail = NULL;
    // Traverse the linked list of vehicles
    VEHICLE *current = p;

    while (current != NULL) {
        char identifier[4] = "";
        strncpy(identifier, current->VIN, 3);

        if (strcmp(identifier, input_code) == 0) {
            // Allocate memory for a new vehicle node
            VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
            if (newVehicle == NULL) {
                printf( "Memory allocation failed\n");
                // Free memory of the filtered list before returning NULL
                while (filtered_list != NULL) {
                    VEHICLE *temp = filtered_list;
                    filtered_list = (VEHICLE *)filtered_list->info;
                    free(temp);
                }
            }

            // Copy the current vehicle's data to the new node
            strcpy(newVehicle->VIN, current->VIN);
            strcpy(newVehicle->color, current->color);
            newVehicle->mileage = current->mileage;
            newVehicle->price = current->price;
            newVehicle->info = NULL;

            // If it's the first node in the filtered list
            if (filtered_list == NULL) {
                filtered_list = newVehicle;
                tail = newVehicle;
            } else {
                // Link the new node to the tail of the filtered list
                tail->info = newVehicle;
                tail = newVehicle;
            }
        }

        // Move to the next vehicle in the linked list
        current = (VEHICLE *)current->info;
    }
    return filtered_list;
}

VEHICLE *VehicleColor(VEHICLE *p, int k){
    // Initialize a pointer to the head of the filtered list
    VEHICLE *filtered_list = NULL;
    // Initialize a pointer to the tail of the filtered list
    VEHICLE *tail = NULL;
    // Traverse the linked list of vehicles
    VEHICLE *current = p;

    while (current != NULL) {
        // Check if the color matches the selected color
        if (strcmp(current->color, Color[k - 1]) == 0) {
            // Allocate memory for a new vehicle node
            VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
            if (newVehicle == NULL) {
                printf( "Memory allocation failed\n");
                // Free memory of the filtered list before returning NULL
                while (filtered_list != NULL) {
                    VEHICLE *temp = filtered_list;
                    filtered_list = (VEHICLE *)filtered_list->info;
                    free(temp);
                }
            }

            // Copy the current vehicle's data to the new node
            strcpy(newVehicle->VIN, current->VIN);
            strcpy(newVehicle->color, current->color);
            newVehicle->mileage = current->mileage;
            newVehicle->price = current->price;
            newVehicle->info = NULL;

            // If it's the first node in the filtered list
            if (filtered_list == NULL) {
                filtered_list = newVehicle;
                tail = newVehicle;
            } else {
                // Link the new node to the tail of the filtered list
                tail->info = newVehicle;
                tail = newVehicle;
            }
        }

        // Move to the next vehicle in the linked list
        current = (VEHICLE *)current->info;
    }
    return filtered_list;
}

VEHICLE *VehicleMileage(VEHICLE *p, int input){
    int lower = 0;
    int upper = 0;
    // Initialize a pointer to the head of the filtered list
    VEHICLE *filtered_list = NULL;
    // Initialize a pointer to the tail of the filtered list
    VEHICLE *tail = NULL;
    // Traverse the linked list of vehicles
    VEHICLE *current = p;
    //Have multiple inputs based on the miles range given by user
    if (input == 14) {
        lower = 120000;
        upper = -1;
        printf("\n----------------Selected Search Criteria: more than 120000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage > lower) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if (input == 1) {
        lower = -1;
        upper = 5000;
        printf("\n----------------Selected Search Criteria: less than 5000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage < upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 2){
        lower= 5000;
        upper = 10000;
        printf("\n----------------Selected Search Criteria: between 5000 and 10000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 3){
        lower= 10000;
        upper = 20000;
        printf("\n----------------Selected Search Criteria: between 10000 and 20000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 4){
        lower= 20000;
        upper = 30000;
        printf("\n----------------Selected Search Criteria: between 20000 and 30000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 5){
        lower= 30000;
        upper = 40000;
        printf("\n----------------Selected Search Criteria: between 30000 and 40000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 6){
        lower= 10000;
        upper = 20000;
        printf("\n----------------Selected Search Criteria: between 40000 and 50000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 7){
        lower= 50000;
        upper = 60000;
        printf("\n----------------Selected Search Criteria: between 50000 and 60000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 8){
        lower= 60000;
        upper = 70000;
        printf("\n----------------Selected Search Criteria: between 60000 and 70000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 9){
        lower= 70000;
        upper = 80000;
        printf("\n----------------Selected Search Criteria: between 70000 and 80000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 10){
        lower= 80000;
        upper = 90000;
        printf("\n----------------Selected Search Criteria: between 80000 and 90000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 11){
        lower= 90000;
        upper = 100000;
        printf("\n----------------Selected Search Criteria: between 90000 and 100000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 12){
        lower= 100000;
        upper = 110000;
        printf("\n----------------Selected Search Criteria: between 100000 and 110000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 13){
        lower= 110000;
        upper = 120000;
        printf("\n----------------Selected Search Criteria: between 110000 and 120000 miles----------------\n");
        while (current != NULL) {
            if (current->mileage >= lower && current->mileage <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    return filtered_list;
}

VEHICLE *VehiclePrice(VEHICLE *p, int input){
    float lower = 0;
    float upper = 0;
    // Initialize a pointer to the head of the filtered list
    VEHICLE *filtered_list = NULL;
    // Initialize a pointer to the tail of the filtered list
    VEHICLE *tail = NULL;
    // Traverse the linked list of vehicles
    VEHICLE *current = p;
    //Multiple conditionals for when the user provides different price ranges
    if (input == 11) {
        lower = 120000;
        upper = -1;
        printf("\n----------------Selected Search Criteria: more than $80000----------------\n");
        while (current != NULL) {
            if (current->price > lower) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if (input == 1) {
        lower = -1;
        upper = 1000;
        printf("\n----------------Selected Search Criteria: less than $1000----------------\n");
        while (current != NULL) {
            if (current->price < upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 2){
        lower = 1000;
        upper = 5000;
        printf("\n----------------Selected Search Criteria: between $1000 and $5000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 3){
        lower = 5000;
        upper = 10000;
        printf("\n----------------Selected Search Criteria: between $5000 and $10000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 4){
        lower = 10000;
        upper = 20000;
        printf("\n----------------Selected Search Criteria: between $10000 and $20000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 5){
        lower = 20000;
        upper = 30000;
        printf("\n----------------Selected Search Criteria: between $20000 and $30000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 6){
        lower = 30000;
        upper = 40000;
        printf("\n----------------Selected Search Criteria: between $30000 and $40000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 7){
        lower = 40000;
        upper = 50000;
        printf("\n----------------Selected Search Criteria: between $40000 and $50000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 8){
        lower = 50000;
        upper = 60000;
        printf("\n----------------Selected Search Criteria: between $50000 and $60000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 9){
        lower = 60000;
        upper = 70000;
        printf("\n----------------Selected Search Criteria: between $60000 and $70000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }
    else if(input == 10){
        lower = 70000;
        upper = 80000;
        printf("\n----------------Selected Search Criteria: between $70000 and $80000----------------\n");
        while (current != NULL) {
            if (current->price >= lower && current->price <= upper) {
                // Allocate memory for a new vehicle node
                VEHICLE *newVehicle = (VEHICLE *)malloc(sizeof(VEHICLE));
                if (newVehicle == NULL) {
                    printf( "Memory allocation failed\n");
                    // Free memory of the filtered list before returning NULL
                    while (filtered_list != NULL) {
                        VEHICLE *temp = filtered_list;
                        filtered_list = (VEHICLE *)filtered_list->info;
                        free(temp);
                    }
                }
                // Copy the current vehicle's data to the new node
                strcpy(newVehicle->VIN, current->VIN);
                strcpy(newVehicle->color, current->color);
                newVehicle->mileage = current->mileage;
                newVehicle->price = current->price;
                newVehicle->info = NULL;

                // If it's the first node in the filtered list
                if (filtered_list == NULL) {
                    filtered_list = newVehicle;
                    tail = newVehicle;
                } else {
                    // Link the new node to the tail of the filtered list
                    tail->info = newVehicle;
                    tail = newVehicle;
                }
            }
            // Move to the next vehicle in the linked list
            current = (VEHICLE *)current->info;
        }
    }

    return filtered_list;
}

void Print_Transaction(VEHICLE *vehicle, FILE *outputFile){
    int year = 0;
    char year_char = vehicle->VIN[10];

    //checks the 10th character in VIN and use conditionals to check what year model is
    //If ASCII value is within numerical range just add 2000 to provide the year
    if((int)year_char >= 49 && (int)year_char <= 57){
        year = (year_char - '0') + 2000;
    }
    //check for letter and assign year to variable
    if(year_char == 'S'){
        year = 1995;
    }
    else if(year_char == 'T'){
        year = 1996;
    }
    else if(year_char == 'V'){
        year = 1997;
    }
    else if(year_char == 'W'){
        year = 1998;
    }
    else if(year_char == 'X'){
        year = 1999;
    }
    else if(year_char == 'Y'){
        year = 2000;
    }
    else if(year_char == 'A'){
        year = 2010;
    }
    else if(year_char == 'B'){
        year = 2011;
    }
    else if(year_char == 'C'){
        year = 2012;
    }
    else if(year_char == 'D'){
        year = 2013;
    }
    else if(year_char == 'E'){
        year = 2014;
    }
    else if(year_char == 'F'){
        year = 2015;
    }
    else if(year_char == 'G'){
        year = 2016;
    }
    else if(year_char == 'H'){
        year = 2017;
    }
    else if(year_char == 'J'){
        year = 2018;
    }
    else if(year_char == 'K'){
        year = 2019;
    }
    else if(year_char == 'L'){
        year = 2020;
    }
    else if(year_char == 'M'){
        year = 2021;
    }
    else if(year_char == 'N'){
        year = 2022;
    }
    else if(year_char == 'P'){
        year = 2023;
    }
    else if(year_char == 'R'){
        year = 2024;
    }


    //Create a character array with first 3 characters from the VIN for manufacturer
    char identifier[4] = "";
    strncpy(identifier, vehicle->VIN, 3);

    // Variable to store the name of the matching model
    char model_name[23] = "";

    // Loop through the linked list of MODELS
    MODEL *current = All_Models;
    while (current != NULL) {
        // Check if the code from the current MODEL is equal to the identifier
        if (strcmp(current->code, identifier) == 0) {
            // Copy the name to the variable
            strncpy(model_name, current->name, sizeof(model_name));
            // Exit the loop once a match is found
            break;
        }

        // Move to the next MODEL in the linked list
        current = current->info;
    }
    model_name[strlen(model_name)] = '\0';
    //Check if model was found from the model list
    if(model_name == ""){
        printf("No model found!");
    }

    trans++;
    // Print vehicle information to the screen
    printf("\nTransaction %d: %d %s %s bought at $%.2f\n\n", trans, year, vehicle->color, model_name, vehicle->price);

    // Print vehicle information to the output file
    if (outputFile != NULL) {
        fprintf(outputFile,"Transaction %d: %d %s %s bought at $%.2f\n", trans, year, vehicle->color, model_name, vehicle->price);
    } else {
        printf("Failed to write to output file.\n");
    }
}

void search_and_buy (FILE *fp)
{
    int i;
    fprintf(fp, "I am here to buy!\n");
    printf("I am here to buy!\n");

    // add your implementation here
    int answer = 0;
    int length = 0;
    VEHICLE *filter = NULL;
    // Initialize a pointer to the head of the filtered list
    VEHICLE *filtered_list = NULL;
    // Declare a pointer to store the head of the original list
    VEHICLE *original_list_head = All_Vehicles;
    // Traverse the linked list of vehicles
    VEHICLE *current = original_list_head;



    do {
        //Offer user an option to select
        printf("\nSelect a number(1-5):\n1.year of made\n2.manufacturer\n3.color\n4.mileage\n5.price\nEnter value: ");
        scanf("%d", &answer);
        getchar();
        //Filter through linked list based on answer provided by user
        if (answer == 1) {
            int year = 0;
            printf("Select a year from 1995 to 2024:");
            scanf("%d", &year);
            getchar();
            filtered_list = VehicleYear(current, year);
            printf("\n----------------Selected Search Criteria: %d----------------\n", year);
            PrintAllVehicles(filtered_list, fp);

        }
        else if (answer == 2) {
            int input;
            char in_manufacturer[40];
            char manufacturers[84][40];
            int numManufacturers = 0;
            MODEL *model = All_Models;
            //Go through all models and place the names in a character array to print for user to pick one
            //Also check for duplicates  as we are adding manufacturers to the list
            while (model != NULL) {
                int found = 0;
                for (int j = 0; j < numManufacturers; j++) {
                    if (strcmp(manufacturers[j], model->name) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(manufacturers[numManufacturers], model->name);
                    numManufacturers++;
                }
                model = model->info;
            }
            // Print the list of manufacturers and receive user input
            printf("\nSelect From List of Manufacturers:\n");
            for (int k = 0; k < numManufacturers; k++) {
                printf("%d. %s\n", k + 1, manufacturers[k]);
            }
            printf("Enter a car manufacturer(type number): ");
            scanf("%d", &input);
            getchar();
            strcpy(in_manufacturer,manufacturers[input-1]);

            char input_code[4] = "";
            model = All_Models;
            //Go through manufacturer list find what equals to user input and assign code to variable
            while (model != NULL) {
                if (strcmp(model->name, in_manufacturer) == 0) {
                    strcpy(input_code, model->code);
                    break;
                }
                model = model->info;
            }
            //Go through list of vehicles and see if code of manufacturer from the input equals the first 3 digits of VIN
            //Then print vehicle onto screen and place it in the output file
            printf("\n----------------Selected Search Criteria: %s----------------\n", in_manufacturer);
            filtered_list = VehicleManufacturer(current, input_code);
            PrintAllVehicles(filtered_list, fp);
        }

        else if (answer == 3) {
            int input;
            printf("\nHere are the colors of vehicles to choose from: \n");
            for (i = 0; i < 12; i++) {
                printf("%2d: %s\n", i + 1, Color[i]);
            }
            printf("Select a color (type number): \n");
            scanf("%d", &input);
            getchar();

            printf("\n----------------Selected Search Criteria: %s----------------\n", Color[input-1]);
            filtered_list = VehicleColor(current, input);
            PrintAllVehicles(filtered_list, fp);
        }

        else if (answer == 4) {
            int input = 0;
            printf("\nSelect a mileage range: "
                   "\n1.less than 5000 miles"
                   "\n2.5000-10000 miles"
                   "\n3.10000-20000 miles"
                   "\n4.20000-30000 miles"
                   "\n5.30000-40000 miles"
                   "\n6.40000-50000 miles"
                   "\n7.50000-60000 miles"
                   "\n8.60000-70000 miles"
                   "\n9.70000-80000 miles"
                   "\n10.80000-90000 miles"
                   "\n11.90000-100000 miles"
                   "\n12.100000-110000 miles"
                   "\n13.110000-120000 miles"
                   "\n14.more than 120000 miles"
                   "\nEnter choice(1-14): ");
            scanf("%d", &input);
            getchar();
            filtered_list = VehicleMileage(current, input);
            PrintAllVehicles(filtered_list, fp);
        }

        else if (answer == 5) {
            int input;

            printf("\nSelect a price range:"
                   "\n1.less than $1000"
                   "\n2.$1000-$5000"
                   "\n3.$5000-$10000"
                   "\n4.$10000-$20000"
                   "\n5.$20000-$30000"
                   "\n6.$30000-$40000"
                   "\n7.$40000-$50000"
                   "\n8.$50000-$60000"
                   "\n9.$60000-$70000"
                   "\n10.$70000-$80000"
                   "\n11.more than $80000"
                   "\nEnter(1-11): ");

            scanf("%d", &input);
            getchar();
            filtered_list = VehiclePrice(current, input);
            PrintAllVehicles(filtered_list, fp);
        }

        //Set the current list to filtered one based on user input for the next iteration
        current = filtered_list;
        //Check length of the filtered list
        VEHICLE *temp = filtered_list;
        length = 0;
        while(temp != NULL){
            length++;
            temp= temp->info;
        }
        //If length is not small enough keep iterating, and if length is 0 return to main menu
        if(length > 5){
            printf("\nSearch results were too  long! Select another specification!\n");
        }
        else if(length == 0){
            return;
        }

    }while(length > 5);

    filter = filtered_list;

    VEHICLE *All = original_list_head;
    VEHICLE *test = original_list_head;
    //Offer user to buy vehicle
    char choice;
    printf("\nDo you want to buy one of these vehicles(type 'y' for yes and 'n' for no): ");
    scanf("%c", &choice);
    getchar();
    //If they do ask them to select a vehicle and go through list of all vehicles, find that specific one, and delete the node
    if('y' == choice){
        int selection = 0;
        printf("Select from the list above by entering a number 1 through %d, where 1 is the top vehicle on the list: ", length);
        scanf("%d", &selection);
        getchar();
        int check = 1;
        while(filter != NULL){
            if(check == selection){
                VEHICLE *previous = NULL;
                while(All != NULL){
                    if(filter->mileage == All->mileage && All->price == All->price && (strcmp(filter->color, All->color) == 0) && (strcmp(filter->VIN, All->VIN) == 0)){

                        Print_Transaction(All, fp);
                        // If it's the first node
                        if (previous == NULL) {
                            All = All->info;
                            free(All);
                            All = All; // Move to the next node
                        }
                        else {
                            previous->info = All->info;
                            free(All);
                            All = previous->info; // Move to the next node
                        }
                    }
                    else {
                        previous = All;
                        All = All->info; // Move to the next node
                    }
                }
                break;
            }
            filter = filter->info;
            check++;
        }
        return;
    }
    //If they do not buy just return to main menu
    else if('n' == choice){
        return;
    }

}


void compare_and_sell (FILE *fp)
{
    fprintf(fp, "I am here to sell!\n");
    printf("I am here to sell!\n");
    // add your implementation here
    VEHICLE *original = All_Vehicles;
    VEHICLE *current = All_Vehicles;

    int in_year = 0;
    int in_mileage = 0;
    char in_manufacturer[40] = "";
    char in_year_char =' ';

    //Enter a year for the car
    printf("Enter the year of your car: ");
    scanf("%d", &in_year);
    getchar();

    int input;
    char manufacturers[84][40];
    int numManufacturers = 0;
    MODEL *model = All_Models;
    //Go through all models and place the names in a character array to print for user to pick one
    //Also check for duplicates  as we are adding manufacturers to the list
    while (model != NULL) {
        int found = 0;
        for (int j = 0; j < numManufacturers; j++) {
            if (strcmp(manufacturers[j], model->name) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(manufacturers[numManufacturers], model->name);
            numManufacturers++;
        }
        model = model->info;
    }
    // Print the list of manufacturers and receive user input
    printf("\nSelect From List of Manufacturers:\n");
    for (int k = 0; k < numManufacturers; k++) {
        printf("%d. %s\n", k + 1, manufacturers[k]);
    }
    printf("Enter a car manufacturer(type number): ");
    scanf("%d", &input);
    getchar();
    printf("\nEnter the mileage of your car: ");
    scanf("%d", &in_mileage);
    getchar();


    strcpy(in_manufacturer,manufacturers[input-1]);

    char input_code[4] = "";
    model = All_Models;
    //Go through manufacturer list find what equals to user input and assign code to variable
    while (model != NULL) {
        if (strcmp(model->name, in_manufacturer) == 0) {
            strcpy(input_code, model->code);
            break;
        }
        model = model->info;
    }
    //Show cars that match at least 2 of 3 specifications within the linked list of all vehicles
    printf("\n------Cars That Fit Specifications------\n");
    fprintf(fp,"\n------Cars That Fit Specifications------\n");
    while(current != NULL){
        int match = 0;
        int year = 0;
        char year_char = current->VIN[10];

        //checks the 10th character in VIN and use conditionals to check what year model is
        //If ASCII value is within numerical range just add 2000 to provide the year
        if((int)year_char >= 49 && (int)year_char <= 57){
            year = (year_char - '0') + 2000;
        }
        //check for letter and assign year to variable
        if(year_char == 'S'){
            year = 1995;
        }
        else if(year_char == 'T'){
            year = 1996;
        }
        else if(year_char == 'V'){
            year = 1997;
        }
        else if(year_char == 'W'){
            year = 1998;
        }
        else if(year_char == 'X'){
            year = 1999;
        }
        else if(year_char == 'Y'){
            year = 2000;
        }
        else if(year_char == 'A'){
            year = 2010;
        }
        else if(year_char == 'B'){
            year = 2011;
        }
        else if(year_char == 'C'){
            year = 2012;
        }
        else if(year_char == 'D'){
            year = 2013;
        }
        else if(year_char == 'E'){
            year = 2014;
        }
        else if(year_char == 'F'){
            year = 2015;
        }
        else if(year_char == 'G'){
            year = 2016;
        }
        else if(year_char == 'H'){
            year = 2017;
        }
        else if(year_char == 'J'){
            year = 2018;
        }
        else if(year_char == 'K'){
            year = 2019;
        }
        else if(year_char == 'L'){
            year = 2020;
        }
        else if(year_char == 'M'){
            year = 2021;
        }
        else if(year_char == 'N'){
            year = 2022;
        }
        else if(year_char == 'P'){
            year = 2023;
        }
        else if(year_char == 'R'){
            year = 2024;
        }

        //Create a character array with first 3 characters from the VIN for manufacturer
        char identifier[4] = "";
        strncpy(identifier, current->VIN, 3);

        // Variable to store the name of the matching model
        char model_name[23] = "";

        // Loop through the linked list of MODELS
        MODEL *mods = All_Models;
        while (mods != NULL) {
            // Check if the code from the current MODEL is equal to the identifier
            if (strcmp(mods->code, identifier) == 0) {
                // Copy the name to the variable
                strncpy(model_name, mods->name, sizeof(model_name));
                // Exit the loop once a match is found
                break;
            }
            // Move to the next MODEL in the linked list
            mods = mods->info;
        }
        model_name[strlen(model_name)] = '\0';
    //Have if statements to see if user input matches the car at this point in the linked list
        if(year == in_year){
            match++;
            in_year_char = year_char;

        }
        if(strcmp(in_manufacturer,model_name) == 0){
            match++;
        }
        if(abs(in_mileage-(current->mileage)) < 5000){
            match++;
        }

        if(match >= 2){
            PrintVehicle(current, fp);
        }
        current = current->info;
    }
    //Ask user to offer a price
    float in_price = 0;
    printf("\nWhat price will you be selling your car at(enter a positive number without $ sign): ");
    scanf("%f", &in_price);
    getchar();

    // Seed the random number generator
    srand(time(NULL));
    // Generate a random number between 1 and 2
    int decision = rand() % 2 + 1;

    //If accepted ask for a color and then create a new vehicle with appropriate attributes and add to list
    if(decision == 1){
        printf("\nPrice is accepted!\n");

        int input;
        printf("\nHere are the colors of vehicles to choose from: \n");
        for ( int i = 0; i < 12; i++) {
            printf("%2d: %s\n", i + 1, Color[i]);
        }
        printf("Select a color (type number): \n");
        scanf("%d", &input);
        getchar();
        VEHICLE *users = (VEHICLE *)malloc(sizeof(VEHICLE));
        strcpy(users->color, Color[input-1]);
        users->price = in_price;
        users->mileage = in_mileage;

        for(int i = 0; i < 3; i++){
            users->VIN[i] = input_code[i];
        }
        for(int i = 3; i < 18; i++){
            int val = rand()%10;
            users->VIN[i] = val + '0';
        }
        users->VIN[10] = in_year_char;

        while (original->info != NULL) {
                original = original->info;
        }
            // Append the new vehicle to the end of the list
            original->info = users;

        trans++;
        printf("\nTransaction %d: %d %s %s bought at $%.2f\n", trans, in_year,Color[input-1], in_manufacturer, in_price);
        if (fp != NULL) {
            fprintf(fp,"Transaction %d: %d %s %s bought at $%.2f\n", trans, in_year,Color[input-1], in_manufacturer, in_price);
        }

    }
    //If price is not good reject offer and return to main menu
    else if(decision == 2){
        printf("\nPrice denied returning to database!\n");
        return;
    }

    return;
}


int main(int argc, char *argv[])
{ FILE *in1, *in2, *out;
    int selection;		// user selection, 1: buy, 2: sell, 0: exit
    VEHICLE * tmp_v;

    if (argc != 4)
    { printf("Usage: a.out pov.txt manufacturer.txt transaction.txt\n");
        exit(0);
    }

    in1 = fopen(argv[1], "r");
    if (in1 == NULL)
    { printf("POV database %s not found ...\n", argv[1]);
        exit(0);
    }

    in2 = fopen(argv[2], "r");
    if (in2 == NULL)
    { printf("manufacturer identifier file %s cannot open ...\n", argv[2]);
        exit(0);
    }

    out = fopen(argv[3], "w");
    if (out == NULL)
    { printf("transaction record file %s cannot open ...\n", argv[3]);
        exit(0);
    }

    All_Models = GetModel(in2);
    fclose(in2);

    All_Vehicles = GetVehicle(in1);
    fclose(in1);

    do
    { printf("Welcome to my Pre-Owned Vehicle Database!\n\n");
        printf("1: search and buy\n2: compare and sell\n0: EXIT\n\n");
        printf("Enter your choice (0-2): ");
        scanf("%d", &selection);

        if (selection == 1) search_and_buy(out);
        if (selection == 2) compare_and_sell(out);
    } while(selection != 0);

    printf("Thank you for visiting my Pre-Owned Vehicle Database!\n");

    fclose(out);
    return 0;
}

