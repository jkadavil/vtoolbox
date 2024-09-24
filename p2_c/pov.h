#ifndef pov
#define pov

#define NEW(x) (x*)malloc(sizeof(x))

typedef struct vehicle
{ char VIN[18];			// a 17-character vehicle identification number 
    char color[10];               // color of the vehicle
    int mileage;			// mileage of the vehicle
    float price;			// price of the vehicle
    void * info;			// you can define additional information about
    // the vehicle (e.g. as a structure) and use
    // this pointer to access that information
} VEHICLE;

typedef struct model
{ char code[4];			// a 3-character manufacturer identifier
    char name[40];		// manufacturer (model) name
    int stock;			// number of vehicles in the POV database with
    // this code[], optional, might be useful
    void * info;			// optional information (e.g. next pointer to
    // the "next" model)
} MODEL;

MODEL * All_Models;		// master list of all manufacturer models
VEHICLE * All_Vehicles;		// master list of all vehicles in the database

extern const char Color[12][10];// 12 different colors for the vehicles
// values of the colors are defined in the sample
// pov.c which you should keep in your pov.c

void search_and_buy (FILE *);	// user will search the POV database (that is,
// All_Vehicles linked list) and decide whether
// she will buy	a vehicle or not. You should
// design your own interface.
// 1. User will not buy more than one vehicle.
// 2. intermediate search results need to be
// printed both on the screen and output file.
// 3. If user decides to buy, the vehicle must
// be removed from the All_Vehicle list and
// the transaction needs to be recorded in the
// output file
// 4. It is recommended to define new (small)
// functions and use them to improve the
// readability of this function
// 5. You can define new structures if needed


void compare_and_sell (FILE *); // similar to the above function, this function
// enables user to compare vehicles in the POV
// database that are similar to the vehicle
// that the user owns and decides whether she
// wants to sell it to the POV database or not.


MODEL * GetModel (FILE *); 	// reads from input file manufacturer.txt
// for all the manufacturer model information
// returns a pointer to a MODEL (or head of a
// linked list of MODELs).
// if file cannot open or no memory left, will
// return NULL, so need to check before use

VEHICLE * GetVehicle (FILE *);	// read from an input file of car database
// and store the vehicle information inside
// the program. The return value is a pointer
// to a VEHICLE (or head of a list of vehicles)
// A NULL pointer could be returned.

void PrintVehicle (VEHICLE *, FILE *);
// print the information of the given vehicle
// on the screen and to the given file using
// the following format
// 1999 Red Dodge car, 180495 miles, 2750.00

void PrintAllVehicles (VEHICLE *, FILE *);
// same as PrintVehicle(), but instead of print-
// ing only one VEHICLE, this function prints
// all the VEHICLES on the list where the head
// VEHICLE is passed to the function as the
// first parameter.

void PrintAllCheaper (VEHICLE *p, FILE *fp, float c);
// p is the head VEHICLE of a list of VEHICLEs,
// fp is the output file
// c is the price
// print the information of vehicles that cost
// c or less, both on the screen and to file fp.


void PrintAllExpensive (VEHICLE *p, FILE *fp, float c);
// same as above, but find vehicles whose price
// is higher or equal to c


VEHICLE * VehicleYear (VEHICLE *p, int k);
// check VEHICLE p or a list of VEHICLEs with p
// as the head for one that was made in the
// given year k (between 1995 and 2024).
// The return value is a pointer to the list of
// VEHICLEs that are made in year k.
// If not found, return NULL


#endif

