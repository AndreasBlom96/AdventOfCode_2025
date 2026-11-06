#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LINE_SIZE 1024

const char* example_path = "../inputs/day1_example.txt";
const char* input_path = "../inputs/day1.txt";

uint64_t solve_A(const char* input_file, int DEBUG){
    char line[LINE_SIZE];
    char direction;
    int steps;
    int dial = 50;
    uint64_t answer = 0;

    FILE* fd = fopen(input_file, "r");

    while (fgets(line, LINE_SIZE, fd) != NULL)
    {
        direction = line[0];
        steps = atoi(line+1);
        
        if(direction == 'L'){
            dial = (dial - steps) %100;
            if(dial < 0){
                dial = 100 + dial;
            }
        }else
        {
            dial = (dial + steps) %100;
        }

        if (dial == 0)
        {
            answer++;
        }
        
        if (DEBUG)
        {
            printf("line: %s -> ", line);
            printf("direcion: %c -> ", direction);
            printf("steps: %i -> ", steps);
            printf("dial: %i", dial);
            printf("\n\n");
        }
    }
    return answer;
}

uint64_t solve_B(const char* input_file, int DEBUG){
    char line[LINE_SIZE];
    char direction;
    int steps;
    int dial = 50;
    uint64_t answer = 0;

    FILE* fd = fopen(input_file, "r");

    if (fd == NULL) {
    perror("Error opening input file");
    return 0;
    }

    while (fgets(line, LINE_SIZE, fd) != NULL)
    {
        direction = line[0];
        steps = atoi(line+1);
        
        int crossings = 0;

        if (direction == 'R') {
            crossings = (dial + steps) / 100;
            dial = (dial + steps) % 100;
        }
        else if (direction == 'L') {
            if (dial == 0) {
                crossings = steps / 100;
            }
            else {
                crossings = (steps + 100 - dial) / 100;
            }

            dial = (dial - steps) % 100;

            if (dial < 0) {
                dial += 100;
            }
        }

        answer += crossings;    
        
        if (DEBUG > 0)
        {
            printf("line: %s", line);
            printf("direcion: %c -> ", direction);
            printf("steps: %i\n", steps);
            printf("dial: %i  --  ", dial);
            printf("answer: %i", answer);
            printf("\n\n");
        }
    }
    fclose(fd);
    return answer;
}

uint64_t main(int argc, char* argv[]){
    const char* path;
    int debug;
    printf("argc: %i\n", argc);

    for (int i = 0; i < argc; i++) {
    printf("argv[%i]: %s\n", i, argv[i]);
    }

    if(argc > 1 && strcmp(argv[1], "e") == 0){
        path = example_path;
    }else{
        path = input_path;
    }

    if(argc > 2 && strcmp(argv[2],"d")==0){
        debug = 1;
    }else{
        debug = 0;
    }

    uint64_t solution = solve_B(path, debug);

    printf("\nsolution: %llu", solution);
    return solution;
}