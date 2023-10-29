#include <stdint.h>
#include <stdio.h>

#define TAPE_SIZE 1000
#define CODE_SIZE 256

typedef struct
{
    uint8_t tape[TAPE_SIZE];
    int8_t *head;
} BrainFuckStruct;

void interpret_code(char code[], BrainFuckStruct *bf_tape)
{
    int i = 0;
    while(i < CODE_SIZE)
    {
        //printf("i: %d\n", i);
        switch (code[i])
        {
        case ',': // Read Input
            break;

        case '.': // Print Output
            printf("%c", (char)*bf_tape->head);
            break;

        case '+': // Increment Cell
            (*bf_tape->head)++;
            break;

        case '-': // Decrement Cell
            (*bf_tape->head)--;
            break;

        case '>': // Mov Head to Right
            bf_tape->head++;
            break;

        case '<': // Mov Head to Left
            bf_tape->head--;
            break;

        case '[': // Jump if Zero
            //printf("hehe\n");
            if (*bf_tape->head == 0)
            {
                int loop_count = 1;
                while (loop_count != 0)
                {
                    //printf("loop: %d - i: %d\n", loop_count, i);

                    switch (code[++i])
                    {
                    case '[':
                        loop_count++;
                        break;

                    case ']':
                        loop_count--;
                        break;

                    default:
                        break;
                    }
                }
            }

            break;

        case ']': // Jump unless Zero
            if (*bf_tape->head != 0)
            {
                int loop_count = 1;
                while (loop_count != 0)
                {
                    //printf("\tloop_count: %d", loop_count);
                    switch (code[--i])
                    {
                    case '[':
                        loop_count--;
                        break;

                    case ']':
                        loop_count++;
                        break;

                    default:
                        break;
                    }
                }
            }

            break;

        default:
            // Invalid Instruction
            break;
        }
        ++i;
    }
}

int main(int argc, char *argv[])
{
    // Args
    if (argc != 2)
    {
        perror("Args are missing\n");
        return 1;
    }

    FILE *input_fp = fopen(argv[1], "r");
    if (input_fp == NULL)
    {
        perror("Cannot open input file (first arg)\n");
        return 1;
    }

    // Tape Init
    BrainFuckStruct brainfuck_tape;
    for (int i = 0; i < TAPE_SIZE; i++)
    {
        brainfuck_tape.tape[i] = 0;
    }
    brainfuck_tape.head = brainfuck_tape.tape; // pointer to 0th of tape

    char code[CODE_SIZE], instruction;
    int i;
    while (fscanf(input_fp, "%c", &instruction) == 1)
    {
        code[i++] = instruction;
    };
    interpret_code(code, &brainfuck_tape);

    /*
        for(int i = 0; i < TAPE_SIZE; i++){
            printf("%d", brainfuck_tape.tape[i]);
        }
    */
    printf("\n");
    return 0;
}