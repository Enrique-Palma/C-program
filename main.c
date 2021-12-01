//Enrique Palma jaramillo assigment 3 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Instruction struct
struct Instruction
{
    int opCode;          //to store opcode
    int deviceOrAddress; //address of the operation
};

int ac = 0; //ac global variable

int comparingStrings(const char *a, const char *b);
//Function used to count the amount of lines in text asmCodefile
int getNumberOfLineInFile(FILE *asmCodefile);
//Function used to parse instruction into machine code
void simulator(int opCode, int b, int dataMemory[], int ir, int pc);

int main(int argc, char *argv[])
{
    //Tiny Machine Architecture variables
    int pc = 0; // for program counter
    int ir = 0; //for instruction register
    int dataMemory[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    int maxProgramSize = 0;
    //This is where we get the number of lines in the code
    maxProgramSize = getNumberOfLineInFile(fopen(argv[1], "r"));

    //This creates array for storing instructions
    struct Instruction programMemory[maxProgramSize];

    //Reading a asmCodefile line by line
    FILE *inputFile_ptr = fopen(argv[1], "r");
    char asmCodefileBuffer[10];
    int i = 0;

    if (inputFile_ptr == NULL)
    {
        printf("ERROR! Input file is not opening");
        exit(0);
    }

    //read line from inputfile and check wether each line contains two values
    while (fgets(asmCodefileBuffer, sizeof(maxProgramSize), inputFile_ptr) != NULL)    
    {
        //Check if new line and empty space to skip
        if (!(comparingStrings(asmCodefileBuffer, " ") == 0 && comparingStrings(asmCodefileBuffer, " ") != 0))
        {
            //check if it contains two digits or not
            if (isdigit(asmCodefileBuffer[0]) && (int)asmCodefileBuffer[2] != 0)
            {
                //store data in programMemory at posion i
                programMemory[i].opCode = atoi(&asmCodefileBuffer[0]);
                programMemory[i].deviceOrAddress = atoi(&asmCodefileBuffer[2]);
                i++; 
            }
        }
    }

    //close file
    fclose(inputFile_ptr);

    //Display output    
    printf("Assembling program...\n");
    printf("Program Assembled\n\nRun.");

    //Print intial value in tinny machine varibles
    ///////////////////////
    printf("\nPC = %d | A = %d | DM = [", pc, ac);
    //print data in memory
    for (i = 0; i < 9; i += 1)
    {
        printf("%d,", dataMemory[i]);
    }
    printf("] \n");
    /////////////////

    //Get the instruction from programMemory
    for (i = pc / 10; i < sizeof(programMemory); i += 1)
    {
        //call function and passing programMemory value into our parser function
        simulator(programMemory[i].opCode, programMemory[i].deviceOrAddress, dataMemory, ir, pc); 
        pc += 1;
    }
    printf("Program concluded... ");
    return 0;
}
//function to compare strings
int comparingStrings(const char *a, const char *b)
{
    while (*a && *a == *b)
    {
        ++a;
        ++b;
    }
    return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}

//Function used to count the amount of lines in text asmCodefile
int getNumberOfLineInFile(FILE *fileInput_ptr)
{
    char asmCodeBuffer[10];
    int count = 0;    
    //caluclate the number of line
    while (fgets(asmCodeBuffer, 10, fileInput_ptr) != NULL)
    {
        count++; //increament count
    }
    fclose(fileInput_ptr);
    return count; //return count
}

//Function used to parse instruction into machine code
void simulator(int opCode, int b, int dataMemory[], int ir, int pc)
{
    int LOAD = 1;
    int ADD = 2;
    int STORE = 3;
    int SUB = 4;
    int IN = 5;
    int OUT = 6;
    int END = 7;
    int JMP = 8;
    int SKIPZ = 9;

    int mar = 0; //to store address of memory
    int mdr = 0; //to store data of memory
    int i = 0;

    if (opCode == LOAD)
    {
        printf("/* Loading from address [%d]... */ ", b);
        ir = b;
        mar = ir;
        mdr = dataMemory[mar];
        ac = mdr;
        //Print value in tinny macine varibles
        ///////////////////////
        printf("\nPC: %d | A: %d | DM: [", pc, ac);
        //print data in memory
        for (i = 0; i < 9; i += 1)
        {
            printf("%d,", dataMemory[i]);
        }
        printf("] \n");
        /////////////////

        printf("\n/* PC <- PC + 1 */ ");
        printf(" -> /* PC <- PC + 1 */ ");
        printf(" -> /* MAR <- IR.ADDR */ ");
        printf(" -> /* MDR <- DM[MAR] */ ");
        printf(" -> /* A <- MDR */ \n\n");
    }
    else if (opCode == ADD)
    {
        printf("/*Adding accumulator and value obtain from address [%d]*/ ", b);
        ir = b;
        mar = ir;
        mdr = dataMemory[mar];
        ac += mdr;

        //Print value in tinny macine varibles
        ///////////////////////
        printf("\nPC = %d | A = %d | DM = [", pc, ac);
        //print data in memory
        for (i = 0; i < 9; i += 1)
        {
            printf("%d,", dataMemory[i]);
        }
        printf("] \n");
        /////////////////
    }
    else if (opCode == STORE)
    {
        printf("/* storing accumulator to memory location 0 */ ");
        mdr = ac;
        ir = b;
        mar = ir;
        dataMemory[mar] = mdr;
        //Print value in tinny macine varibles
        ///////////////////////
        printf("\nPC = %d | A = %d | DM = [", pc, ac);
        //print data in memory
        for (i = 0; i < 9; i += 1)
        {
            printf("%d,", dataMemory[i]);
        }
        printf("] \n");
        /////////////////
    }
    else if (opCode == SUB)
    {
        printf("/* Subtracting memory address value [%d] from accumulator*/ ", b);
        ir = b;
        mar = ir;
        mdr = dataMemory[mar];
        ac -= mdr;
        //Print value in tinny macine varibles
        ///////////////////////
        printf("\nPC = %d | A = %d | DM = [", pc, ac);
        //print data in memory
        for (i = 0; i < 9; i += 1)
        {
            printf("%d,", dataMemory[i]);
        }
        printf("] \n");
        /////////////////
    }
    else if (opCode == IN)
    {
        printf("/*Please input value:*/ ");
        scanf("%d", &ac);
        //Print value in tinny macine varibles

        ///////////////////////
        printf("PC = %d | A = %d | DM = [", pc, ac);
        //print data in memory
        for (i = 0; i < 9; i += 1)
        {
            printf("%d,", dataMemory[i]);
        }
        printf("] \n");
        /////////////////
    }
    else if (opCode == OUT)
    {
        printf("/*sending value %d from accumulator to printer*/ ", ac);
        //Print value in tinny machine varibles
        ///////////////////////
        printf("\nPC = %d | A = %d | DM = [", pc, ac);
        //print data in memory
        for (i = 0; i < 9; i += 1)
        {
            printf("%d,", dataMemory[i]);
        }
        printf("] \n");
        /////////////////
    }
    else if (opCode == END)
    {
        printf("Program Complete.");
        exit(1);
    }
    else if (opCode == JMP)
    {
        // *Jump to address
        printf("/*Setting counter to %d*/ ", b);
        pc = b;
        //Print value in tinny macine varibles
        ///////////////////////
        printf("\nPC = %d | A = %d | DM = [", pc, ac);
        //print data in memory
        for (i = 0; i < 9; i += 1)
        {
            printf("%d,", dataMemory[i]);
        }
        printf("] \n");
        /////////////////
    }
    else if (opCode == SKIPZ)
    {
        //Check if accumulator is 0,
        printf("/*Skipping the next instruction*/ ");
        if (ac == 0) //if it is skip next instruction
        {
            pc += 2; //increament PC by 2
        }
        else //otherwise
        {
            pc += 1; //increament PC by 1
        }

        //Print value in tinny macine varibles
        ///////////////////////
        printf("\nPC = %d | A = %d | DM = [", pc, ac);
        //print data in memory
        for (i = 0; i < 9; i += 1)
        {
            printf("%d,", dataMemory[i]);
        }
        printf("] \n");
        /////////////////
    }
    else
    {
        printf("/*There was an error parsing that opcode! Exiting program*/ ");
        exit(0);
    }
}