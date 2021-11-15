#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum State
{
	LOAD = 1,
	ADD = 2,
	STORE = 3,
	SUB = 4,
	IN = 5,
	OUT = 6,
	END = 7,
	JMP = 8,
	SKIPZ = 9
};

void printVaribles();
//Creating Instruction structure

struct Instruction
{
	int opCode; //to store opcode
	int deviceOrAddress; //address of the operation

};

//Global variable
int codeSize = 13;
//Tiny Machine Architecture variables
int pc = 10; // for program counter
int ir = 0; //for instruction register
int mar = 0; //to store address of memory
int dataMemory[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int mdr = 0; //to store data of memory
int ac = 0; //accumulator
//function for print the tinny architecuter varibles

void printVaribles()
{
	int i;
	printf("\n PC: %d | A: %d | MEM: [", pc, ac);
	//print data in memory

	for (i = 0; i < 9; i += 1)
	{
		printf("%d,", dataMemory[i]);
	}
	printf("] \n");
}

//Function used to count the amount of lines in text asmCodefile

int getNumberOfLineInFile(FILE* asmCodefile)
{
	char asmCodeBuffer[10];
	int count = 0;
	if (asmCodefile == NULL)
	{
		printf("ASM code file is not opening...");
		exit(0);
	}

	//caluclate the number of line
	while (fgets(asmCodeBuffer, 10, asmCodefile) != NULL)
	{
		count++; //increament count
	}		

	fclose(asmCodefile);

	return count; //return count
}

//Function used to parse instruction into machine code

void tinyMachineSimulator(int opCode, int b)
{
    if(opCode == LOAD)
    {
        printf(" /* Loading from address [%d]... */ ", b);

		ir = b;

		mar = ir;

		mdr = dataMemory[mar];

		ac = mdr;

		//Print value in tinny macine varibles

		printVaribles();

		pc += 1;

		printf("/* PC <- PC + 1 */ ");

		printf("\n/* PC <- PC + 1 */ ");

		printf("\n/* MAR <- IR.ADDR */ ");

		printf("\n/* MDR <- MEM[MAR] */ ");

		printf("\n/* A <- MDR */ ");
    }
    else if(opCode == ADD)
    {
        printf(" /*Adding accumulator and value obtain from address [%d]*/ ", b);

		ir = b;

		mar = ir;

		mdr = dataMemory[mar];

		ac += mdr;

		//Print value in tinny macine varibles

		printVaribles();

		pc += 1;
    }
    else if(opCode == STORE)
    {
        printf(" /* storing accumulator to memory location 0 */ ");

		mdr = ac;

		ir = b;

		mar = ir;

		dataMemory[mar] = mdr;

		//Print value in tinny macine varibles

		printVaribles();

		pc += 1;
    }
    else if(opCode == SUB)
    {
        printf(" /* Subtracting memory address value [%d] from accumulator*/ ", b);

		ir = b;

		mar = ir;

		mdr = dataMemory[mar];

		ac -= mdr;

		//Print value in tinny macine varibles

		printVaribles();

		pc += 1;
    }
    else if(opCode == IN)
    {
        printf(" /*Please input value:*/ ");

		scanf("%d", &ac);

		//Print value in tinny macine varibles

		printVaribles();

		pc += 1;
    }
    else if(opCode == OUT)
    {
        printf(" /*Accumulator current value = %d */ ", ac);

		//Print value in tinny macine varibles

		printVaribles();

		pc += 1;
    }
    else if (opCode == END)
    {
        printf(" Program complete ");

		exit(1);	
    }
    else if(opCode == JMP)
    {
        // *Jump to address

		printf(" /*Setting program counter to %d*/ ", b);

		pc = b;

		//Print value in tinny macine varibles

		printVaribles();
    } 
    else if(opCode == SKIPZ)
    {
        //Check if accumulator is 0,

		printf(" /*Skipping the next instruction*/ ");

		if (ac == 0) //if it is skip next instruction

			pc += 2; //increament PC by 2

		else //otherwise

			pc += 1; //increament PC by 1

		//Print value in tinny macine varibles

		printVaribles();
    } 
    else
    {
        printf(" /*There was an error parsing that opcode! Exiting program*/ ");

		exit(0);
    }

    

	// switch (opCode)
	// {

	// case LOAD:

	// 	printf(" /* Loading from address [%d]... */ ", b);

	// 	ir = b;

	// 	mar = ir;

	// 	mdr = dataMemory[mar];

	// 	ac = mdr;

	// 	//Print value in tinny macine varibles

	// 	printVaribles();

	// 	pc += 1;

	// 	printf("/* PC <- PC + 1 */ ");

	// 	printf("\n/* PC <- PC + 1 */ ");

	// 	printf("\n/* MAR <- IR.ADDR */ ");

	// 	printf("\n/* MDR <- MEM[MAR] */ ");

	// 	printf("\n/* A <- MDR */ ");

	// 	break;

	// case ADD:

	// 	printf(" /*Adding accumulator and value obtain from address [%d]*/ ", b);

	// 	ir = b;

	// 	mar = ir;

	// 	mdr = dataMemory[mar];

	// 	ac += mdr;

	// 	//Print value in tinny macine varibles

	// 	printVaribles();

	// 	pc += 1;

	// 	break;

	// case STORE:

	// 	printf(" /* storing accumulator to memory location 0 */ ");

	// 	mdr = ac;

	// 	ir = b;

	// 	mar = ir;

	// 	dataMemory[mar] = mdr;

	// 	//Print value in tinny macine varibles

	// 	printVaribles();

	// 	pc += 1;

	// 	break;

	// case SUB:

	// 	printf(" /* Subtracting memory address value [%d] from accumulator*/ ", b);

	// 	ir = b;

	// 	mar = ir;

	// 	mdr = dataMemory[mar];

	// 	ac -= mdr;

	// 	//Print value in tinny macine varibles

	// 	printVaribles();

	// 	pc += 1;

	// 	break;

	// case IN:

	// 	printf(" /*Please input value:*/ ");

	// 	scanf("%d", &ac);

	// 	//Print value in tinny macine varibles

	// 	printVaribles();

	// 	pc += 1;

	// 	break;

	// case OUT:

	// 	printf(" /*Accumulator current value = %d */ ", ac);

	// 	//Print value in tinny macine varibles

	// 	printVaribles();

	// 	pc += 1;

	// 	break;

	// case END:

	// 	printf(" Program complete ");

	// 	exit(1);

	// case JMP:

	// 	// *Jump to address

	// 	printf(" /*Setting program counter to %d*/ ", b);

	// 	pc = b;

	// 	//Print value in tinny macine varibles

	// 	printVaribles();

	// 	break;

	// case SKIPZ:

	// 	//Check if accumulator is 0,

	// 	printf(" /*Skipping the next instruction*/ ");

	// 	if (ac == 0) //if it is skip next instruction

	// 		pc += 2; //increament PC by 2

	// 	else //otherwise

	// 		pc += 1; //increament PC by 1

	// 	//Print value in tinny macine varibles

	// 	printVaribles();

	// 	break;

	// default:

	// 	printf(" /*There was an error parsing that opcode! Exiting program*/ ");

	// 	exit(0);
	// }
}

int main(int argc, char* argv[])
{
	//This is where we get the number of lines in the code
	codeSize = getNumberOfLineInFile(fopen(argv[1], "r"));

	//This creates array for storing instructions
	struct Instruction programMemory[codeSize];

	//Reading a asmCodefile line by line
	FILE* asmCodefile = fopen(argv[1], "r");
	char asmCodefileBuffer[10];
	int i = 0;

	if(asmCodefile == NULL)
	{
		printf("ASM code file is not opening...");
		exit(0);
	}
	//read line from inputfile and check wether each line contains two values

	while (fgets(asmCodefileBuffer, sizeof(codeSize), asmCodefile) != NULL)
	{
		//Check if new line and empty space to skip
		if ((strcmp(asmCodefileBuffer, " ") == 0 || strcmp(asmCodefileBuffer, " ") != 0))
		{
			//check if it contains two digits or not
			if (isdigit(asmCodefileBuffer[0]) && (int)asmCodefileBuffer[2] != 0)
			{
				//store data in programMemory at posion i
				programMemory[i].opCode = atoi(&asmCodefileBuffer[0]);
				programMemory[i].deviceOrAddress = atoi(&asmCodefileBuffer[2]);
				i++; //increament
			}
		}
	}

	//Need to close the asmCodefile
	fclose(asmCodefile);

	//Display output

	printf(" Tiny Machine Simulator ");
	printf("Assembling program... ");
	printf("Program assembled Run. ");

	//Print intial value in tinny macine varibles
	printVaribles();

	//Get the instruction from programMemory
	for(i = (pc / 10) - 1; i < sizeof(programMemory); i += 1)
	{
		//call function and passing programMemory value into our parser function
		tinyMachineSimulator(programMemory[i].opCode, programMemory[i].deviceOrAddress);
	}

	printf(" Program concluded... ");
	//system("pause");

	return 0;
}