#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<stdbool.h>
#include<ctype.h>
#pragma warning(disable : 4996)

void main()
{
	int main_menu();
	void new_inventory_parts();
	void request_inventory_parts();
	void inventory_tracking();
	void search_part_record();
	void run_application();
	void file_creating();
	run_application();
	_getch();
}

int main_menu()
{
	char choiceStr[100];
	int choice, i;
	
	printf("\tWelcome to the Inventory Management System.");
	printf("\n\tWhat do you want to do?");
	printf("\n\t\t1. Insert New Inventory Parts.");
	printf("\n\t\t2. Request Inventory Parts.");
	printf("\n\t\t3. Inventory Tracking.");
	printf("\n\t\t4. Search Parts Record and Supplier Details.");
	printf("\n\t\t5. Exit");
	printf("\n\t\t6. Creating New File and Insert New Data.");
	printf("\n\n\t\t *** You will have to choose 6 first if there is no text file created before ***");
	while (true)
	{
		printf("\n\tPlease choose the number from the menu above (integer only).\n\t");
		gets_s(choiceStr);

		choice = atoi(choiceStr);
		if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6)
		{
			break;
		}
		for (i = 0; i < 100; i++)
		{
			if (isdigit(choiceStr[i]) == 0)
			{
				break;
			}
		}
	}
	return choice;
}

void new_inventory_parts()
{

	char modelCode[100], warehouseCode[100], divisionCode[100], partCode[100], partAmountStr[100];
	int partAmountInt, partLeft;

	printf("\n\tWhat are the model that you are going to supply?");
	printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
	printf("\n\tBlaze (BZ), Silk (SL), Armer (AR).\n\t");
	while (true)
	{
		gets_s(modelCode); while (getchar() != '\n');

		if (strcmp("BZ", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WBZ");
			break;
		}

		else if (strcmp("SL", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WSL");
			break;
		}

		else if (strcmp("AR", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WAR");
			break;
		}
		else
			printf("\tPlease input the correct code.\n\t");
	}

	while (true)
	{
		printf("\n\tWhat is the division of the part that you are going to supply?");
		printf("\n\tPlease choose one from the code below (uppercase) (100 charater max).");
		printf("\n\tEngine Section (ES), Body Work Section (BWS), Air-con Section (AS).\n\t");

		gets_s(divisionCode); while (getchar() != '\n');
		if (strcmp("ES", divisionCode) == 0 || strcmp("BWS", divisionCode) == 0 || strcmp("AS", divisionCode) == 0)
			break;
		printf("\tPlease input the correct code.\n\t");
	}

	if ((strcmp(divisionCode, "ES")) == 0)
	{
		while (true)
		{
			printf("\n\tWhat is the engine part that you are supplying?");
			printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
			printf("\n\tEngine Block (EB), Piston (P), Crankshaft (CS), Engine Valves (EV), Cylinder Head (CH).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "EB")) == 0) || ((strcmp(partCode, "P")) == 0) || ((strcmp(partCode, "CS")) == 0) || ((strcmp(partCode, "EV")) == 0) || ((strcmp(partCode, "CH")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	else if ((strcmp(divisionCode, "BWS")) == 0)
	{
		while (true)
		{
			printf("\n\tWhat is the engine part that you are supplying?");
			printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
			printf("\n\tBody Kits (BK), Body Shell (BS), Body Trim (BT), Bonnet (B), Fluid Bottle (FB).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "BK")) == 0) || ((strcmp(partCode, "BS")) == 0) || ((strcmp(partCode, "BT")) == 0) || ((strcmp(partCode, "B")) == 0) || ((strcmp(partCode, "FB")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	else if ((strcmp(divisionCode, "AS")) == 0)
	{
		while (true)
		{
			printf("\n\tWhat is the engine part that you are supplying?");
			printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
			printf("\n\tCompressor (CP), Condenser (CD), Receiver (R), Orifice Tube (OT), Evaporator (EP).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "CP")) == 0) || ((strcmp(partCode, "CD")) == 0) || ((strcmp(partCode, "R")) == 0) || ((strcmp(partCode, "OT")) == 0) || ((strcmp(partCode, "EP")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	//Ensure only integer imput to prevent the program to crash and ruin the text files
	while (true)
	{
		printf("\tHow many parts are you going to supply? (integer only) (no space) (max 100 character)\n\t");
		int i, allInt = 1;
		gets_s(partAmountStr); while (getchar() != '\n');
		for (i = 0; i < strlen(partAmountStr); i++)
		{
			if (!isdigit(partAmountStr[i]))
			{
				printf("\n\t\Please input integer only (max 100 character).\n");
				allInt = 0;
				break;
			}
		}
		if (allInt == 0)
			continue;
		else
			break;
	}
	partAmountInt = atoi(partAmountStr);

	struct partsInfo
	{
		char partDivision[20], partDivisionCode[4], partName[20], partCode[4], partLeftStr[10];
	};
	int partLeftInt, location = 0;

	//Reading from file and get the location of the data according to user input (partCode)
	if (strcmp("WBZ", warehouseCode) == 0)
	{
		FILE* fptr;
		fptr = fopen("Blaze Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		struct partsInfo a[15];
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);

		for (i = 0; i < 15; i++)
		{
			if (strcmp(partCode, a[i].partCode) == 0)
			{
				location = i;
				break;
			}
		}

		partLeftInt = atoi(a[location].partLeftStr);
		partLeftInt = partAmountInt + partLeftInt;
		itoa(partLeftInt, a[location].partLeftStr, 10);

		fptr = fopen("Blaze Warehouse.txt", "w");
		for (i = 0; i < 15; i++)
		{
			fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WSL", warehouseCode) == 0)
	{
		FILE* fptr;
		fptr = fopen("Silk Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		struct partsInfo a[20];
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);

		for (i = 0; i < 15; i++)
		{
			if (strcmp(partCode, a[i].partCode) == 0)
			{
				location = i;
				break;
			}
		}

		partLeftInt = atoi(a[location].partLeftStr);
		partLeftInt = partAmountInt + partLeftInt;
		itoa(partLeftInt, a[location].partLeftStr, 10);

		//Write to the file to update the amount
		fptr = fopen("Silk Warehouse.txt", "w");
		for (i = 0; i < 15; i++)
		{
			fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WAR", warehouseCode) == 0)
	{
		FILE* fptr;
		fptr = fopen("Armer Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		struct partsInfo a[20];
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);

		for (i = 0; i < 15; i++)
		{
			if (strcmp(partCode, a[i].partCode) == 0)
			{
				location = i;
				break;
			}
		}

		partLeftInt = atoi(a[location].partLeftStr);
		partLeftInt = partAmountInt + partLeftInt;
		itoa(partLeftInt, a[location].partLeftStr, 10);

		fptr = fopen("Armer Warehouse.txt", "w");
		for (i = 0; i < 15; i++)
		{
			fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	printf("\n\n\tYour part supplied had been successfully added, %d total now.", partLeftInt);

	return;
}

void request_inventory_parts()
{
	char modelCode[100], warehouseCode[100], divisionCode[100], partCode[100], partRequestedStr[100];
	int partRequestedInt, i, location = NULL;

	printf("\n\tWhat is the model that you want to take its part?");
	printf("\n\tPlease choose one of the code below (uppercase) (10 charater max).");
	printf("\n\tBlaze (BZ), Silk (SL), Armer(AR).\n\t");
	while (true)
	{
		gets_s(modelCode); while (getchar() != '\n');

		if (strcmp("BZ", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WBZ");
			break;
		}

		else if (strcmp("SL", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WSL");
			break;
		}

		else if (strcmp("AR", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WAR");
			break;
		}
		else
			printf("\tPlease input the correct code.\n\t");
	}
	
	while (true)
	{
		printf("\n\tWhat is the section that you want to take its part?");
		printf("\n\tPlease choose one of the code below (uppercase) (10 charater max).");
		printf("\n\tEngine Section (ES), Body Work Section (BWS), Air-con Section (AS).\n\t");
		gets_s(divisionCode); while (getchar() != '\n');
		if (((strcmp(divisionCode, "ES")) == 0) || ((strcmp(divisionCode, "BWS")) == 0) || ((strcmp(divisionCode, "AS")) == 0))
			break;
		printf("\tPlease input the correct code.\n\t");
	}

	if ((strcmp(divisionCode, "ES")) == 0)
	{
		while (true)
		{
			printf("\n\tWhat is the part that you want to take?");
			printf("\n\tPlease choose one of the code below (uppercase) (10 charater max).");
			printf("\n\tEngine Block (EB), Piston (P), Crankshaft (CS), Engine Valves (EV), Cylinder Head (CH).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "EB")) == 0) || ((strcmp(partCode, "P")) == 0) || ((strcmp(partCode, "CS")) == 0) || ((strcmp(partCode, "EV")) == 0) || ((strcmp(partCode, "CH")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	else if ((strcmp(divisionCode, "BWS")) == 0)
	{
		while (true)
		{
			printf("\n\tWhat is the part that you want to take?");
			printf("\n\tPlease choose one of the code below (uppercase) (10 charater max).");
			printf("\n\tBody Kits (BK), Body Shell (BS), Body Trim (BT), Bonnet (B), Fluid Bottle (FB).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "BK")) == 0) || ((strcmp(partCode, "BS")) == 0) || ((strcmp(partCode, "BT")) == 0) || ((strcmp(partCode, "B")) == 0) || ((strcmp(partCode, "FB")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	else if ((strcmp(divisionCode, "AS")) == 0)
	{
		while (true)
		{
			printf("\n\tWhat is the part that you want to take?");
			printf("\n\tPlease choose one of the code below (uppercase) (10 charater max).");
			printf("\n\tCompressor (CP), Condenser (CD), Receiver (R), Orifice Tube (OT), Evaporator (EP).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "CP")) == 0) || ((strcmp(partCode, "CD")) == 0) || ((strcmp(partCode, "R")) == 0) || ((strcmp(partCode, "OT")) == 0) || ((strcmp(partCode, "EP")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	struct partsInfo
	{
		char partDivision[20], partDivisionCode[4], partName[20], partCode[4], partLeftStr[10];
	};
	int partLeftInt;
	struct partsInfo a[15];
	FILE* fptr;

	//Reading from file and get the location of the data according to user input (partCode)
	if (strcmp("WBZ", warehouseCode) == 0)
	{
		fptr = fopen("Blaze Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WSL", warehouseCode) == 0)
	{
		fptr = fopen("Silk Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WAR", warehouseCode) == 0)
	{
		fptr = fopen("Armer Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	for (i = 0; i < 15; i++)
	{
		if (strcmp(partCode, a[i].partCode) == 0)
		{
			location = i;
			break;
		}
	}

	//Ensure only integer imput to prevent the program to crash and ruin the text files
	while (true)
	{
		partLeftInt = atoi(a[location].partLeftStr);
		printf("\tHow many parts are you going to take? (integer only) (max 100 character)\n");
		printf("\t%d max\n\t", partLeftInt);
		int i, allInt = 1;
		gets_s(partRequestedStr); while (getchar() != '\n');
		for (i = 0; i < strlen(partRequestedStr); i++)
		{
			if (!isdigit(partRequestedStr[i]))
			{
				printf("\n\tPlease input integer only (max 100 character).\n");
				allInt = 0;
				break;
			}
		}

		if (allInt == 0)
			continue;
		partRequestedInt = atoi(partRequestedStr);
		if (partRequestedInt > partLeftInt)
		{
			printf("\n\tSorry there is not enough parts. Please input the amount no more than %d.\n", partLeftInt);
			continue;
		}
		break;
	}

	partLeftInt = atoi(a[location].partLeftStr);
	partLeftInt = partLeftInt - partRequestedInt;
	itoa(partLeftInt, a[location].partLeftStr, 10);

	//Writing to file to update the amount
	if (strcmp("WBZ", warehouseCode) == 0)
	{
		fptr = fopen("Blaze Warehouse.txt", "w");
		for (i = 0; i < 15; i++)
		{
			fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WSL", warehouseCode) == 0)
	{
		fptr = fopen("Silk Warehouse.txt", "w");
		for (i = 0; i < 15; i++)
		{
			fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WAR", warehouseCode) == 0)
	{
		fptr = fopen("Armer Warehouse.txt", "w");
		for (i = 0; i < 15; i++)
		{
			fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	printf("\n\n\tYour part requested had been successfully deducted, %d left.", partLeftInt);

	return;
}

void inventory_tracking()
{
	char warehouseCode[100], warehouseName[30];
	int i, less = 0;

	printf("\n\tWhich warehouse's inventory do you want to check?");
	printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
	printf("\n\tBlaze Warehouse (WBZ), Silk Warehouse (WSL), Armer Warehouse (WAR).\n\t");
	while (true)
	{
		gets_s(warehouseCode);
		if (((strcmp(warehouseCode, "WBZ")) == 0) || ((strcmp(warehouseCode, "WSL")) == 0) || ((strcmp(warehouseCode, "WAR")) == 0))
			break;
		printf("\tPlease input the correct code.\n\t");
	}

	struct partsInfo
	{
		char partDivision[20], partDivisionCode[4], partName[20], partCode[4], partLeftStr[10];
	};
	struct partsInfo a[15];

	struct supplierInfo
	{
		char supplierName[20], suppliedDivision[20], suppliedDivisionCode[4], supplierContact[20], partSupplied1[10], partSupplied2[10], partSupplied3[10], partSupplied4[10], partSupplied5[10];
	};
	struct supplierInfo b[3];

	FILE* fptr;

	if (strcmp("WBZ", warehouseCode) == 0)
	{
		fptr = fopen("Blaze Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WSL", warehouseCode) == 0)
	{
		fptr = fopen("Silk Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WAR", warehouseCode) == 0)
	{
		fptr = fopen("Armer Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	if (strcmp(warehouseCode, "WBZ") == 0)
		strcpy(warehouseName, "BLaze Warehouse Inventory");
	else if (strcmp(warehouseCode, "WSL") == 0)
		strcpy(warehouseName, "Silk Warehouse Inventory");
	else if (strcmp(warehouseCode, "WAR") == 0)
		strcpy(warehouseName, "Armer Warehouse Inventory");

	printf("\n\t\t%s\n\n", warehouseName);

	for (i = 0; i < 15; i++)
	{
		printf(" \t%s\t%s\t%s   \t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
	}

	printf("\n\n\t\tParts that have less than 10 units:\n\n");

	for (i = 0; i < 15; i++)
	{
		if (atoi(a[i].partLeftStr) < 10)
		{
			printf(" \t%s\t%s\t%s   \t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
			less = 1;
		}
	}

	if (less == 0)
	{
		printf("\tNone");
	}
	else
	{
		fptr = fopen("supplier.txt", "r");
		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}

		for (i = 0; i < 3; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", b[i].supplierName, b[i].suppliedDivision, b[i].suppliedDivisionCode, b[i].supplierContact, b[i].partSupplied1, b[i].partSupplied2, b[i].partSupplied3, b[i].partSupplied4, b[i].partSupplied5);
		}
		printf("\n\n\tYou can contact the supplier according to the information below to get the parts with less volume.\n\n");
		for (i = 0; i < 3; i++)
		{
			printf("\t\t%s\t%s\t%s\t%s\n", b[i].supplierName, b[i].suppliedDivision, b[i].suppliedDivisionCode, b[i].supplierContact);
			printf("\t\tThe parts that is supplied: %s %s %s %s %s\n\n", b[i].partSupplied1, b[i].partSupplied2, b[i].partSupplied3, b[i].partSupplied4, b[i].partSupplied5);
		}
	}

	return;
}


void search_part_record()
{
	char modelCode[100], warehouseCode[100], divisionCode[100], partCode[100], warehouseName[30];
	int i, location;
	FILE* fptr;

	struct partsInfo
	{
		char partDivision[20], partDivisionCode[4], partName[20], partCode[4], partLeftStr[10];
	};
	struct partsInfo a[15];

	struct supplierInfo
	{
		char supplierName[20], suppliedDivision[20], suppliedDivisionCode[4], supplierContact[20], partSupplied1[10], partSupplied2[10], partSupplied3[10], partSupplied4[10], partSupplied5[10];
	};
	struct supplierInfo b[3];

	printf("\n\tWhat is the part's model do you want to check?");
	printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
	printf("\n\tBlaze (BZ), Silk (SL), Armer(AR).\n\t");
	while (true)
	{
		gets_s(modelCode); while (getchar() != '\n');

		if (strcmp("BZ", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WBZ");
			break;
		}

		else if (strcmp("SL", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WSL");
			break;
		}

		else if (strcmp("AR", modelCode) == 0)
		{
			strcpy_s(warehouseCode, "WAR");
			break;
		}
		else
			printf("\tPlease input the correct code.\n\t");
	}

	while (true)
	{
		printf("\n\tWhat is the section does the part belongs to?");
		printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
		printf("\n\tEngine Section (ES), Body Work Section (BWS), Air-con Section (AS).\n\t");
		gets_s(divisionCode); while (getchar() != '\n');
		if (((strcmp(divisionCode, "ES")) == 0) || ((strcmp(divisionCode, "BWS")) == 0) || ((strcmp(divisionCode, "AS")) == 0))
			break;
		printf("\tPlease input the correct code.\n\t");
	}

	if ((strcmp(divisionCode, "ES")) == 0)
	{
		while (true)
		{
			printf("\n\tWhich part do you want to check?");
			printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
			printf("\n\tEngine Block (EB), Piston (P), Crankshaft (CS), Engine Valves (EV), Cylinder Head (CH).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "EB")) == 0) || ((strcmp(partCode, "P")) == 0) || ((strcmp(partCode, "CS")) == 0) || ((strcmp(partCode, "EV")) == 0) || ((strcmp(partCode, "CH")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	else if ((strcmp(divisionCode, "BWS")) == 0)
	{
		while (true)
		{
			printf("\n\tWhich part do you want to check?");
			printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
			printf("\n\tBody Kits (BK), Body Shell (BS), Body Trim (BT), Bonnet (B), Fluid Bottle (FB).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "BK")) == 0) || ((strcmp(partCode, "BS")) == 0) || ((strcmp(partCode, "BT")) == 0) || ((strcmp(partCode, "B")) == 0) || ((strcmp(partCode, "FB")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	else if ((strcmp(divisionCode, "AS")) == 0)
	{
		while (true)
		{
			printf("\n\tWhich part do you want to check?");
			printf("\n\tPlease choose one of the code below (uppercase) (100 charater max).");
			printf("\n\tCompressor (CP), Condenser (CD), Receiver (R), Orifice Tube (OT), Evaporator (EP).\n\t");
			gets_s(partCode); while (getchar() != '\n');
			if (((strcmp(partCode, "CP")) == 0) || ((strcmp(partCode, "CD")) == 0) || ((strcmp(partCode, "R")) == 0) || ((strcmp(partCode, "OT")) == 0) || ((strcmp(partCode, "EP")) == 0))
				break;
			printf("\tPlease input the correct code.\n\t");
		}
	}

	if (strcmp("WBZ", warehouseCode) == 0)
	{
		fptr = fopen("Blaze Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WSL", warehouseCode) == 0)
	{
		fptr = fopen("Silk Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}

	else if (strcmp("WAR", warehouseCode) == 0)
	{
		fptr = fopen("Armer Warehouse.txt", "r");

		if (fptr == NULL)
		{
			printf("\n\tError, Please Create the files first.\n");
			return;
		}
		int i;
		for (i = 0; i < 15; i++)
		{
			fscanf(fptr, "%s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
		}
		fclose(fptr);
	}


	if (strcmp(warehouseCode, "WBZ") == 0)
		strcpy(warehouseName, "BLaze Warehouse Inventory");
	else if (strcmp(warehouseCode, "WSL") == 0)
		strcpy(warehouseName, "Silk Warehouse Inventory");
	else if (strcmp(warehouseCode, "WAR") == 0)
		strcpy(warehouseName, "Armer Warehouse Inventory");

	printf("\n\t%s:\n", warehouseName);

	for (i = 0; i < 15; i++)
	{
		if (strcmp(a[i].partCode, partCode) == 0)
		{
			location = i;
			break;
		}
	}

	printf("\n\tSearched Part Information:\n\n");
	printf("\t%s\t%s\t%s\t%s\t%s\n\n", a[location].partDivision, a[location].partDivisionCode, a[location].partName, a[location].partCode, a[location].partLeftStr);

	//Read from supplier file
	fptr = fopen("supplier.txt", "r");

	if (fptr == NULL)
	{
		printf("\n\tError\n");
		return;
	}

	for (i = 0; i < 3; i++)
	{
		fscanf(fptr, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", b[i].supplierName, b[i].suppliedDivision, b[i].suppliedDivisionCode, b[i].supplierContact, b[i].partSupplied1, b[i].partSupplied2, b[i].partSupplied3, b[i].partSupplied4, b[i].partSupplied5);
	}


	for (i = 0; i < 3; i++)
	{
		if (strcmp(a[location].partDivisionCode, b[i].suppliedDivisionCode) == 0)
		{
			location = i;
			break;
		}
	}

	printf("\n\tThe supplier information for the part:\n\n");
	printf("\t%s\t%s\t%s\t%s\n", b[location].supplierName, b[location].suppliedDivision, b[location].suppliedDivisionCode, b[location].supplierContact);

	return;
}

void file_creating()
{
	struct partsInfo
	{
		char partDivision[20], partDivisionCode[4], partName[20], partCode[4], partLeftStr[100];
	};
	struct partsInfo a[15];
	
	char amountInput[100];
	int i, k, allInt = 0;
	FILE* fptr;

	for (i = 0; i < 5; i++)
	{
		strcpy(a[i].partDivision, "EngineSection");
		strcpy(a[i].partDivisionCode, "ES");
	}
	for (i = 5; i < 10; i++)
	{
		strcpy(a[i].partDivision, "BodyWorkSection");
		strcpy(a[i].partDivisionCode, "BWS");
	}
	for (i = 10; i < 15; i++)
	{
		strcpy(a[i].partDivision, "Air-conSection");
		strcpy(a[i].partDivisionCode, "AS");
	}

	for (k = 0; k < 3; k++)
	{
		if (k == 0)
			printf("\n\n\t\tNow please input all the inventory in the Blaze Warehouse:\n");
		else if (k == 1)
			printf("\n\n\t\tNow please input all the inventory in the Silk Warehouse:\n");
		else if (k == 2)
			printf("\n\n\t\tNow please input all the inventory in the Armer Warehouse:\n");

		printf("\n\n\t\tNow is the inventory for Engine Section.");
		strcpy(a[0].partName, "EngineBlock"); strcpy(a[0].partCode, "EB");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Engine Block Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');
			//scanf("%s", amountInput);

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[0].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[0].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[1].partName, "Piston"); strcpy(a[1].partCode, "P");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Piston Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				};
			}

			if (allInt == 1)
			{
				strcpy(a[1].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[1].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[2].partName, "Crankshaft"); strcpy(a[2].partCode, "CS");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Crankshaft Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[2].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[2].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[3].partName, "EngineValve"); strcpy(a[3].partCode, "EV");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Engine Valve Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[3].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[3].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[4].partName, "CylinderHead"); strcpy(a[4].partCode, "CH");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Cylinder Head Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[4].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[4].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		printf("\n\n\t\tNow is the inventory for Body Work Section.");
		strcpy(a[5].partName, "BodyKits"); strcpy(a[5].partCode, "BK");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Body Kits Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[5].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[5].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[6].partName, "BodyShell"); strcpy(a[6].partCode, "BS");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Body Shell Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[6].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[6].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[7].partName, "BodyTrim"); strcpy(a[7].partCode, "BT");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Body Trim Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[7].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[7].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[8].partName, "Bonnet"); strcpy(a[8].partCode, "B");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Bonnet Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[8].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[8].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}


		strcpy(a[9].partName, "FluidBottle"); strcpy(a[9].partCode, "FB");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Fluid Bottle Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[9].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[9].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		printf("\n\n\t\tNow is the inventory for Air-con Section.");
		strcpy(a[10].partName, "Compressor"); strcpy(a[10].partCode, "CP");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Compressor Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[10].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[10].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[11].partName, "Condenser"); strcpy(a[11].partCode, "CD");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Condenser Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[11].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[11].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[12].partName, "Receiver"); strcpy(a[12].partCode, "R");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Receiver Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[12].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[12].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[13].partName, "OrificeTube"); strcpy(a[13].partCode, "OT");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Orifice Tube Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[13].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[13].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		strcpy(a[14].partName, "Evaporator"); strcpy(a[14].partCode, "EP");
		while (true)
		{
			allInt = 1;
			printf("\n\tWhat is the amount of Evaporator Part left (no space is allowed) (integers only):\n\t");
			scanf("%s", amountInput); while (getchar() != '\n');

			for (i = 0; i < strlen(amountInput); i++)
			{
				if (!isdigit(amountInput[i]))
				{
					printf("\n\tPlease input integer only (max 100 character).\n");
					allInt = 0;
					break;
				}
			}

			if (allInt == 1)
			{
				strcpy(a[14].partLeftStr, amountInput);
				printf("\n\tThe inventory amount is %s", a[14].partLeftStr);
				break;
			}
			else
			{
				printf("\n\tPlease give valid input.\n");
				continue;
			}
		}

		if (k == 0)
		{
			fptr = fopen("Blaze Warehouse.txt", "w");
			for (i = 0; i < 15; i++)
			{
				fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
			}
			fclose(fptr);
		}
		else if (k == 1)
		{
			fptr = fopen("Silk Warehouse.txt", "w");
			for (i = 0; i < 15; i++)
			{
				fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
			}
			fclose(fptr);
		}
		else if (k == 2)
		{
			fptr = fopen("Armer Warehouse.txt", "w");
			for (i = 0; i < 15; i++)
			{
				fprintf(fptr, " %s\t%s\t%s\t%s\t%s\n", a[i].partDivision, a[i].partDivisionCode, a[i].partName, a[i].partCode, a[i].partLeftStr);
			}
			fclose(fptr);
		}
	}

	// Supplier File Creating
	fptr = fopen("supplier.txt", "w");
	fprintf(fptr, " %s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "Lucas", "EngineSection", "ES", "012-5554488", "EB", "P", "CS", "EV", "CH");
	fprintf(fptr, " %s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "Adam", "BodyWorkSection", "BWS", "012-5554444", "BK", "BS", "BT", "B", "FB");
	fprintf(fptr, " %s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "Nick", "Air-conSection", "AS", "011-1225554", "CP", "CD", "R", "OT", "EP");
	fclose(fptr);

	return;
}

void run_application()
{
	int choice;

	while (true)
	{
		choice = main_menu();
		switch (choice)
		{
		case 1:
			printf("\n\n\tYou had choosed to Insert New Inventory Parts.");
			new_inventory_parts();
			printf("\n\n\tPress enter to go back to main menu.");
			while (getchar() != '\n');
			system("cls");
			break;

		case 2:
			printf("\n\n\tYou had choosed to Request Inventory Parts.");
			request_inventory_parts();
			printf("\n\n\tPress enter to go back to main menu.");
			while (getchar() != '\n');
			system("cls");
			break;

		case 3:
			printf("\n\n\tYou had choosed to do Inventory Tracking.");
			inventory_tracking();
			printf("\n\n\tPress enter to go back to main menu.");
			while (getchar() != '\n');
			system("cls");
			break;

		case 4:
			printf("\n\n\tYou had choosed to Search Parts Record and Supplier Details.");
			search_part_record();
			printf("\n\n\tPress enter to go back to main menu.");
			while (getchar() != '\n');
			system("cls");
			break;

		case 5:
			printf("\n\n\tYou had choosed exit this program.");
			printf("\n\tThank You !!!");
			while (getchar() != '\n');
			system("cls");
			return;

		case 6:
			printf("\n\n\tYou had choosed to create new file inventory");
			file_creating();
			printf("\n\tYou had successfully created the files and the inventory.");
			while (getchar() != '\n');
			system("cls");
			break;

		default:
			printf("\n\tInvalid choice, please try again.");
		}
	}
	return;
}