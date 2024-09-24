/* the main program for project 2
p2_1.c:	command line safety check
	add structure MODEL and function Get_Models() in pov.h to read in 
		the manufacturer file and store in array MODEL[]

								Gang Qu
								April 7, 2024
p2_2.c:	MODELs are stored in a singly linked list, start from All_Models and 
	use ->info to access the next MODEL
								April 8, 2024

p2_3.c: sample p2.c for stage 1 of the project. Read in the POV database and
		do some simple operations: print out information of one 
		vehicle, all vehicles in a list of vehicles, vehicles that 
		are cheaper than 2999.00, vehicles made in 2011, etc.  
	pov.h: add two structures and many function prototypes 
	MODEL * All_Models; 
	VEHICLE * All_Vehicles;
								April 9, 2024
p2.c: for stage 2 of the project.
								April 19, 2024
*/

#include <stdlib.h>
#include <stdio.h>
#include "pov.h"		// include the header file


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

