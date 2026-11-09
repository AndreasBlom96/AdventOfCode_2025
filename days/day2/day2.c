#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "day2.h"

#define LINE_SIZE 1024

const char* example_path = "../inputs/day2_example.txt";
const char* input_path = "../inputs/day2.txt";

uint64_t solve_A(const char* input_file, int debug){
    char line[LINE_SIZE];
    uint64_t answer=0;

    /* Open file*/
    FILE* fd = fopen(input_file, "r");

    if (!fd)
    {
        printf("could not open file at: %s", input_file);
        return -1;
    }
    /*--------------------*/

    while (fgets(line, LINE_SIZE, fd) != NULL)
    {
        if (debug > 0)
        {
            printf("line: %s\n", line);
        }
        
        char* substr = strtok(line, ",");
        int i = 1;
        while (substr && strlen(substr) > 1)
        {
            /* Fixing start and end numbers*/
            char *delim_pos = strchr(substr, '-');
            int length_start_str = delim_pos - substr;
            if (debug > 0)
            {
                printf("substr: %s\n", substr);
            }
            
            char *start = malloc(length_start_str + 1);
            memcpy(start, substr, length_start_str);
            start[length_start_str] = '\0';

            char *end = delim_pos +1;
            /* -------------------------------*/
            
            /*Make logic check here!!*/
            uint64_t start_int = strtoull(start, NULL, 10);
            uint64_t end_int = strtoull(end, NULL, 10);
            
            for(uint64_t i = start_int; i < end_int+1; i++){
                char current_number_as_string[32];

                snprintf(current_number_as_string,
                    sizeof(current_number_as_string),
                    "%llu",
                    (unsigned long long)i);
                int length = 0;
                int *divisors = factor(strlen(current_number_as_string), &length);
                
                if(check_symmetry(current_number_as_string, divisors, length) > 0){
                    answer += i;
                    if (debug > 0)
                    {
                        printf("found valid ID: %llu\n", i);
                    }
                    
                }
                free(divisors);
            }
            /*-----------------------*/

            /*prepare for next */
            substr = strtok(NULL, ",");
            if (debug > 0)
            {
                printf("\n");
            }
            
            free(start);
            i++;
        }
        

        /*if (debug > 0)
        {
            printf("substr: %s -> ", substr);
            printf("start: %s -> end: %s\n", r.start, r.end);
        }
            */
    }

    /*Closing and freeing data*/
    fclose(fd);
    return answer;
}

int* factor(int number_of_letters, int *result_size){
    int k = 0;
    for(size_t i = 1; i < number_of_letters; i++)
    {
        if(number_of_letters%i == 0){
            k++;
        }
    }

    int *count = malloc(k * sizeof(int));
    *result_size = k; 

    k = 0;
    for(size_t i = 1; i < number_of_letters; i++)
    {
        if(number_of_letters%i == 0){
            count[k++] = i;
        }
    }

    return count;
}

int check_symmetry(char *src, int *divisors, int divisor_length){
    int steps;
    if(strlen(src)%2 != 0)
    {
        return 0;
    }

    if(divisor_length > 1)
    {
        steps = divisors[divisor_length-1];
    }else{
        steps = divisors[0];
        char char_to_match=src[0];
        for(int k = 1; k < strlen(src); k++){
            if (src[k] != char_to_match)
            {
                return 0;
            }
        }
        return 1;
    }

    char *first = malloc(steps + 1);
    memcpy(first, src, steps);
    first[steps] = '\0';

    char *second = src + steps;

    if(strcmp(first, second)==0){
        free(first);
        return 1;
    }
    free(first);
    return 0;
}

uint64_t solve_B(const char *input_file, int debug){
    char line[LINE_SIZE];
    uint64_t answer=0;

    /* Open file*/
    FILE* fd = fopen(input_file, "r");

    if (!fd)
    {
        printf("could not open file at: %s", input_file);
        return -1;
    }
    /*--------------------*/

    while (fgets(line, LINE_SIZE, fd) != NULL)
    {
        if (debug > 0)
        {
            printf("line: %s\n", line);
        }
        
        char* substr = strtok(line, ",");
        int i = 1;
        while (substr && strlen(substr) > 1)
        {
            /* Fixing start and end numbers*/
            char *delim_pos = strchr(substr, '-');
            int length_start_str = delim_pos - substr;
            if (debug > 0)
            {
                printf("substr: %s\n", substr);
            }
            
            char *start = malloc(length_start_str + 1);
            memcpy(start, substr, length_start_str);
            start[length_start_str] = '\0';

            char *end = delim_pos +1;
            /* -------------------------------*/
            
            /*Make logic check here!!*/
            uint64_t start_int = strtoull(start, NULL, 10);
            uint64_t end_int = strtoull(end, NULL, 10);
            
            for(uint64_t i = start_int; i <= end_int; i++){
                char current_number_as_string[32];

                snprintf(current_number_as_string,
                    sizeof(current_number_as_string),
                    "%llu",
                    (unsigned long long)i);
                
                if(check_repetition(current_number_as_string) == 1){
                    if (debug > 0)
                    {
                        printf("found ID: %s\n", current_number_as_string);
                    }
                    answer += i;
                }
            }
            /*-----------------------*/

            /*prepare for next */
            substr = strtok(NULL, ",");
            if (debug > 0)
            {
                printf("\n");
            }
            
            free(start);
            i++;
        }
    }

    /*Closing and freeing data*/
    fclose(fd);
    return answer;
}

int check_repetition(char *src){
    int length = strlen(src);

    for(int i = 1; i <= length/2; i++){
        if(length%i != 0){
            continue;
        }
        char tmp1[i+1];
        char tmp2[i+1];
        
        int found_rep = 1;
        for (size_t k = 0; k < (length/i)-1; k++)
        {
            strncpy(tmp1, src+(k*i), i);
            strncpy(tmp2, src+(k*i)+i, i);
            tmp1[i] = '\0';
            tmp2[i] = '\0';
            if(strcmp(tmp1, tmp2) != 0){
                found_rep = 0;
                break;
            }
        }
        if (found_rep == 1)
        {
            return 1;
        }   
    }
    return 0;
}


uint64_t main(int argc, char* argv[]){
    const char* path = input_path;
    int debug = 0;
    char part = 'a';
    uint64_t solution;

    printf("argc: %i\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%i]: %s ->", i, argv[i]);
        switch (i)
        {
            case 1:
                if (strcmp(argv[i], "b")==0)
                {
                    part = 'b';
                }
                printf(" solving part %c\n", part);
                break;
            case 2:
                if (strcmp(argv[i], "e") == 0)
                {
                    path = example_path;
                    printf(" input file: example \n");
                }else{
                    printf(" input file: real\n");
                }
                    
            break;
            case 3:
            char *debug_String=" debug OFF\n";
                if (strcmp(argv[i], "d") == 0)
                {
                    debug = 1;
                    debug_String = " debug ON\n\n";
                }
                printf(debug_String, debug);
            break;

        default:
                printf("\n");
            break;
    }
    }

    if (part == 'a')
    {
        solution = solve_A(path, debug);
    }else{
        solution = solve_B(path, debug);
    }
    

    printf("\nsolution: %llu", solution);
    return solution;
}