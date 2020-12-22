/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/postfix_eval.c
 *
 * \brief An application to evaluate postfix mathematical expressions.
 *
 * \author Your Name
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "postfix_eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/stack.h>
#include "../src/stack_private.h"


#define MAX_LINE_LEN 256


int eval_postfix(const char *expr, long *res)
{
    upo_stack_t stack = upo_stack_create();
    char string[MAX_LINE_LEN] = "";
    strcpy(string, expr);
    char* token = strtok(string, " ");
    long temp = 0;
    long result = 0;
    while(token != NULL)
    {     
        printf("%s\n", token);
        if(isdigit(*(token)))
        {
            sscanf(token, "%ld\n", &temp);
            printf("%ld\n", temp);
            upo_stack_push(stack, &temp);
            printf("Stack size: %ld\n", upo_stack_size(stack));
            printf("Top -> %ld\n", *((long*) upo_stack_top(stack)));
        }
        else if(!isdigit(*(token)))
        {
            long num2 = *((long*) upo_stack_top(stack));
            printf("Stack size: %ld\n", upo_stack_size(stack));
            upo_stack_pop(stack, 0);
            printf("Stack size: %ld\n", upo_stack_size(stack));
            printf("Num 2: %ld\n", num2);
            long num1 = *((long*) upo_stack_top(stack));
            upo_stack_pop(stack, 0); 
            printf("Stack size: %ld\n", upo_stack_size(stack));           
            printf("Num 1: %ld\n", num1);
            switch (*(token))
            {
            case '+':
                printf("Addition\n");
                printf("Stack size: %ld\n", upo_stack_size(stack));
                result = num1 + num2;
                printf("Result: %ld\n", result);
                break;
            case '-':
                printf("Subtraction\n");
                printf("Stack size: %ld\n", upo_stack_size(stack));
                result = num1 - num2;
                printf("Result: %ld\n", result);
                break;
            case '/':
                printf("Division\n");
                printf("Stack size: %ld\n", upo_stack_size(stack));
                result = num1 / num2;
                printf("Result: %ld\n", result);
                break;
            case '*':
                printf("Multiplication\n");
                printf("Stack size: %ld\n", upo_stack_size(stack));
                result = num1 * num2;
                printf("Result: %ld\n", result);
                break;
            case '%':
                printf("Modulo\n");
                printf("Stack size: %ld\n", upo_stack_size(stack));
                result = num1 % num2;
                printf("Result: %ld\n", result);
                break;
            case '^':
                printf("Exponentation\n");
                printf("Stack size: %ld\n", upo_stack_size(stack));
                result = num1 ^ num2;
                printf("Result: %ld\n", result);
                break;                
            default:
                printf("Simbol is not recognized.\n");
                upo_stack_destroy(stack, 1);
                return 0;
                break;
            }
            printf("Result: %ld\n", result);
            upo_stack_push(stack, &result);
            printf("Updated stack: %ld\n", *((long*) upo_stack_top(stack)));
        }
        token = strtok(NULL, " ");          
    }
    if(stack->size == 1)
    {
        res = (long*)upo_stack_top(stack);
        printf("Result: %ld\n", *(res));
        upo_stack_pop(stack, 1);  
    }
    else
    {
        fprintf(stderr, "Error: malformed expression\n");
        upo_stack_destroy(stack, 1);
        return 0;
    }
    upo_stack_destroy(stack, 1);
    return 1;
}

void eval_lines(FILE *fp)
{
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), fp))
    {
        size_t slen = strlen(line);
        int ok = 0;
        long res = 0;
        char *res_str = NULL;
        long expect_res = 0;

        /* Strips the terminating newline (if any) */
        if (slen > 0 && line[slen-1] == '\n')
        {
            line[slen-1] = '\0';
            --slen;
        }

        /* Checks if we have the expected result. In this case the input line should be: <expr>, <result> */
        res_str = strstr(line, "=>");
        if (res_str != NULL)
        {
            line[res_str-line] = '\0';
            res_str += 2;
            expect_res = atol(res_str);
        }

        ok = eval_postfix(line, &res);
        if (ok)
        {
            if (res_str != NULL)
            {
                printf("Expression '%s' -> %ld (expected: %ld -> %s)\n", line, res, expect_res, (res == expect_res) ? "OK" : "KO");
            }
            else
            {
                printf("Expression '%s' -> %ld\n", line, res);
            }
        }
        else
        {
            printf("Expression '%s' -> Malformed\n", line);
        }
    }
}

void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s -f [<filename>]\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "-f <filename>: The full path name to the file containing strings (one for each line).\n"
                    "               If not given, strings are read from standard input.\n"
                    "               [default: standard input]\n");
    fprintf(stderr, "-h: Displays this message\n");
    fprintf(stderr, "-v: Enables output verbosity\n");
}

int main(int argc, char *argv[])
{
    char *opt_filename = NULL;
    int opt_help = 0;
    int opt_verbose = 0;
    int arg = 0;
    FILE *fp = NULL;

    for (arg = 1; arg < argc; ++arg)
    {
        if (!strcmp("-f", argv[arg]))
        {
            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected file name.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            opt_filename = argv[arg];
        }
        else if (!strcmp("-h", argv[arg]))
        {
            opt_help = 1;
        }
        else if (!strcmp("-v", argv[arg]))
        {
            opt_verbose = 1;
        }
    }

    if (opt_help)
    {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }

    if (opt_verbose)
    {
        printf("-- Options:\n");
        printf("* File name: %s\n", opt_filename ? opt_filename : "<not given>");
    }

 
    if (opt_filename != NULL)
    {
        fp = fopen(opt_filename, "r");
        if (fp == NULL)
        {
            perror("ERROR: cannot open input file");
            return EXIT_FAILURE;
        }
    }
    else
    {
        fp = stdin;
    }

    if (opt_verbose)
    {
        printf("-- Evaluating...\n");
    }

    eval_lines(fp);

    if (opt_filename != NULL)
    {
        fclose(fp);
    }

    return EXIT_SUCCESS;
}
