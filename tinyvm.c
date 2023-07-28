/*
        Anna Del Negro
        Christie Beaubrun
*/

#include <stdio.h>
#include <stdlib.h>

/*max size of memory*/
#define MAX_MEMORY 11

/*defining instructions for the machine*/
enum State
{
    LOAD = 1,
    ADD = 2,
    STORE = 3,
    SUB = 4,
    IN = 5,
    OUT = 6,
    HALT = 7,
    JMP = 8,
    SKIPZ = 9,
    SKIPG = 10,
    SKIPL = 11,
};

/*defining struct that holds opcode and memory address*/
typedef struct
{
    int op_code;
    int address;
} instruction;

/*creating variables*/
int code_size = 128;
int p_counter = 0;                       /*program counter*/
int acc = 0;                             /*accumulator*/
int i_register = 0;                      /*instruction register*/
int mar = 0;                             /*memory address*/
int dm[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; /*array - memory address*/
int mdr = 0;                             /*store memory's data*/

int main(int argc, char *argv[])
{
    /*ensuring amount of arguments passed is correct*/
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    /*error handling*/
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Cannot open file: %s\n", argv[1]);
        return 1;
    }
    
    int dm[MAX_MEMORY] = {0};

    /*setting 10th element in array to 1 for it to be used*/
    dm[10] = 1;

    /*creating struct*/
    instruction program_memory;

    /*array to store each variable read from file*/
    int instruction_memory[128] = {0};

    int ic = 0; /*instruction_counter*/

    while (!feof(fp))
    {
        fscanf(fp, "%d %d\n", &instruction_memory[ic], &instruction_memory[ic + 1]);
        /*  to test:
        printf("%d %d\n", instruction_memory[ic], instruction_memory[ic + 1]);
        */
        ic += 2;
    }
    fclose(fp);

    /*declaring variables*/
    int i = 0;
    int eof = 0;

    /*to test:
    for(int i=0; i<26; i++){
        printf("\n%d", instruction_memory[i]);
    }
    */

   /*since EOF in halt is 1, we loop as long as EOF is 0*/
    while (eof == 0)
    {
        /*extract opcode and address*/
        program_memory.op_code = instruction_memory[p_counter];
        program_memory.address = instruction_memory[p_counter + 1];

        int opcode = program_memory.op_code;
        int address = program_memory.address;

        /*switch statement*/
        switch (opcode)
        {
        case LOAD:
            /*A <— DM[x]*/
            printf("\nLoading address [%d]", address);
            i_register = address;
            mar = i_register;
            mdr = dm[mar];
            acc = mdr;
            break;
        case ADD:
            /*A <— A + DM[x]*/
            printf("\nAdding accumulator and value in data memory");
            i_register = address;
            mar = i_register;
            mdr = dm[mar];
            acc += mdr;
            break;
        case STORE:
            /*DM[x] <— A*/
            printf("\nStoring value in Acc into memory location");
            mdr = acc;
            i_register = address;
            mar = i_register;
            dm[mar] = mdr;
            break;
        case SUB:
            /*A <— A - DM[x]*/
            printf("\nSubtracting [%d] from accumulator", address);
            i_register = address;
            mar = i_register;
            mdr = dm[mar];
            acc -= mdr;
            break;
        case IN:
            /*A <— Read from Device (*/
            printf("\nInput a positive value\n");
            scanf("%d", &acc);
            break;
        case OUT:
            /*A —> Write to device (*/
            printf("\nThe result is: %d\n", acc);
            break;
        case HALT:
            /*End of program (stop running)*/
            printf("\nProgram has ended\n");
            eof = 1;
            break;
        case JMP:
            /*PC <— x*/
            printf("\nSetting PC to [%d]", address);
            p_counter = address;
            break;
        case SKIPZ:
            /*If A is equal zero, PC = PC + 2*/
            printf("\nSKIPZ");
            if (acc == 0)
            {
                p_counter = p_counter + 2;
            }
            break;
        case SKIPG:
            /*If A > zero, PC = PC + 2*/
            printf("\nSKIPG");
            if (acc > 0)
            {
                p_counter = p_counter + 2;
            }
            break;
        case SKIPL:
            /*If A < zero, PC = PC + 2*/
            printf("\nSKIPL");
            if (acc < 0)
            {
                p_counter = p_counter + 2;
            }
            break;
        default:
            /*error handling*/
            printf("Error: invalid opcode %d\n", opcode);
            return 1;
        }

        /*print state*/
        int i = 0;
        printf("\nPC: %d | A: %d | MEM: [", p_counter, acc);

        /*printing data in memory*/
        for (i; i < 10; i++)
        {
            printf("%d", dm[i]);
            if(i != 9){
                printf(",", dm[i]);
            }
        }
        printf("]\n");

        p_counter += 2;
    }

    return 0;
}
