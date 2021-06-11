/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/sort_compare.c
 *
 * \brief An application to compare different sorting algorithms.
 *
 * \author Simone Gattini, Federico Barbero, Anton Iliev
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <upo/error.h>
#include <upo/sort.h>
#include <upo/hires_timer.h>


#define DEFAULT_OPT_ARRAY_SIZE (size_t) 1000
#define DEFAULT_OPT_NUM_RUNS (size_t) 1
#define DEFAULT_OPT_RNG_SEED (unsigned int) time(NULL)
#define DEFAULT_OPT_SORT_SPECIAL 0
#define DEFAULT_OPT_VERBOSE 0
#define NUM_SORTING_ALGORITHMS (size_t) 4


/** \brief Defines the sorting algorithm category type as an enumerated type. */
typedef enum {
            unknown_sort_algorithm = -1,
            insertion_sort_algorithm,
            merge_sort_algorithm,
            quick_sort_algorithm,
            stdc_sort_algorithm
        } sorting_algorithm_t;

/** \brief Defines the item type as a key-value pair type. */
typedef struct {
            int key;
            double value;
        } item_t;


/** \brief Generates a random number uniformly distributed in [0,1) */
static double runif01();

/** \brief Generates a random array of size \a n */
static item_t* make_random_array(size_t n);

/** \brief Comparison function for elements of type \a item_t to sort in ascending order. */
static int item_comparator(const void *a, const void *b);

/** \brief Comparison function for elements of type \a item_t to sort in descending order. */
static int rev_item_comparator(const void *a, const void *b);

/** \brief Sorts the given array \a items of size \a by means of the sorting algorithm \a alg */
static double sort(sorting_algorithm_t alg, item_t *items, size_t n);

/** \brief Compares sorting algorithms. */
static void compare_algorithms(sorting_algorithm_t algs[], size_t num_algs, size_t n, unsigned int seed, size_t num_runs, int sort_special, int verbose);

/** \brief Extracts the sorting algorithm name from the given string. */
static sorting_algorithm_t parse_sorting_algorithm(const char *str);

/** \brief Prints the sorting algorithm name to the given output stream. */
static void print_sorting_algorithm(FILE *fp, sorting_algorithm_t alg);

/** \brief Prints the given array to standard output. */
static void print_array(const item_t *items, size_t n);

/** \brief Displays a help message. */
static void usage(const char *progname);


double runif01()
{
    return rand()/(RAND_MAX+1.0);
}

item_t* make_random_array(size_t n)
{
    size_t i;
    item_t *a;

    a = malloc(n*sizeof(item_t));
    if (a == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for random array");
    }

    for (i = 0; i < n; ++i)
    {
        item_t item;
        item.key = rand();
        item.value = runif01();
        a[i] = item;
    }

    return a;
}

int item_comparator(const void *a, const void *b)
{
    const item_t *aa = a;
    const item_t *bb = b;

    assert( a != NULL );
    assert( b != NULL );

    return (aa->key > bb->key) - (aa->key < bb->key);
}

int rev_item_comparator(const void *a, const void *b)
{
    const item_t *aa = a;
    const item_t *bb = b;

    assert( a != NULL );
    assert( b != NULL );

    return (aa->key < bb->key) - (aa->key > bb->key);
}

double sort(sorting_algorithm_t alg, item_t *items, size_t n)
{
    upo_hires_timer_t timer;
    double runtime = 0;

    assert( items != NULL );

    timer = upo_hires_timer_create();
    upo_hires_timer_start(timer);
    switch (alg)
    {
        case insertion_sort_algorithm:
            upo_insertion_sort(items, n, sizeof(item_t), item_comparator);
            break;
        case merge_sort_algorithm:
            upo_merge_sort(items, n, sizeof(item_t), item_comparator);
            break;
        case quick_sort_algorithm:
            upo_quick_sort(items, n, sizeof(item_t), item_comparator);
            break;
        case stdc_sort_algorithm:
            qsort(items, n, sizeof(item_t), item_comparator);
            break;
        case unknown_sort_algorithm:
            return -1;
            break;
    }
    upo_hires_timer_stop(timer);

    runtime = upo_hires_timer_elapsed(timer);

    upo_hires_timer_destroy(timer);

    return runtime;
}

void compare_algorithms(sorting_algorithm_t algs[], size_t num_algs, size_t n, unsigned int seed, size_t num_runs, int sort_special, int verbose)
{
    double *tot_runtimes = NULL;
    size_t r;
    size_t k;

    srand(seed);

    /* Allocates memory for the array that will accumulate the runtimes */
    tot_runtimes = malloc(num_algs*sizeof(double));
    if (tot_runtimes == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for the total runtimes");
    }
    memset(tot_runtimes, 0, num_algs*sizeof(long));

    for (r = 0; r < num_runs; ++r)
    {
        item_t *array = NULL;
        item_t *asc_sorted_array = NULL;
        item_t *des_sorted_array = NULL;
        item_t *work_array = NULL;
        size_t i;

        if (verbose)
        {
            printf("RUN #%lu\n", r+1);
        }
        else
        {
            printf("RUN #%lu", r+1);
            fflush(stdout);
        }

        /* Creates a random array */
        array = make_random_array(n);
        if (verbose)
        {
            printf("Input array: ");
            print_array(array, n);
            putchar('\n');
        }

        if (sort_special)
        {
            /* Clones the random array to create an ascending sorted version of the original array */
            asc_sorted_array = malloc(n*sizeof(item_t));
            if (asc_sorted_array == NULL)
            {
                upo_throw_sys_error("Unable to allocate memory for the ascending sorted array");
            }
            memcpy(asc_sorted_array, array, n*sizeof(item_t));
            qsort(asc_sorted_array, n, sizeof(item_t), item_comparator);

            /* Clones the random array to create a descending sorted version of the original array */
            des_sorted_array = malloc(n*sizeof(item_t));
            if (des_sorted_array == NULL)
            {
                upo_throw_sys_error("Unable to allocate memory for the descending sorted array");
            }
            memcpy(des_sorted_array, array, n*sizeof(item_t));
            qsort(des_sorted_array, n, sizeof(item_t), rev_item_comparator);
        }

        /* Clones the random array to use as an argument to the sorting function */
        work_array = malloc(n*sizeof(item_t));
        if (work_array == NULL)
        {
            upo_throw_sys_error("Unable to allocate memory for the work array");
        }

        for (i = 0; i < num_algs; ++i)
        {
            double runtime = 0;

            sorting_algorithm_t alg = algs[i];

            if (!verbose)
            {
                printf(".");
                fflush(stdout);
            }

            /* Sort the randon array */
            memcpy(work_array, array, n*sizeof(item_t));
            runtime = sort(alg, work_array, n);
            if (verbose)
            {
                print_sorting_algorithm(stdout, alg);
                printf(" -> runtime to sort original array: %f sec\n", runtime);
            }
            if (sort_special)
            {
                /* Sort the already sorted array */
                memcpy(work_array, asc_sorted_array, n*sizeof(item_t));
                runtime += sort(alg, work_array, n);
                if (verbose)
                {
                    print_sorting_algorithm(stdout, alg);
                    printf(" -> runtime to sort sorted array: %f sec\n", runtime);
                }
                /* Sort the already reversely sorted array */
                memcpy(work_array, des_sorted_array, n*sizeof(item_t));
                runtime += sort(alg, work_array, n);
                if (verbose)
                {
                    print_sorting_algorithm(stdout, alg);
                    printf(" -> runtime to sort reverse array: %f sec\n", runtime);
                }
            }

            if (verbose)
            {
                print_sorting_algorithm(stdout, alg);
                printf(" -> sorted array: ");
                print_array(work_array, n);
                putchar('\n');
            }

            tot_runtimes[i] += runtime;
        }

        printf("\n");

        free(work_array);
        if (sort_special)
        {
            free(des_sorted_array);
            free(asc_sorted_array);
        }
        free(array);
    }

    printf("SUMMARY\n");
    for (k = 0; k < num_algs; ++k)
    {
        size_t i;

        print_sorting_algorithm(stdout, algs[k]);
        printf("-> Average runtime: %f\n", tot_runtimes[k]/((double) num_runs));
        if (num_algs > 1)
        {
            for (i = 0; i < num_algs; ++i)
            {
                double ratio = tot_runtimes[i]/((double) tot_runtimes[k]);

                if (i == k)
                {
                    continue;
                }

                printf("... vs. ");
                print_sorting_algorithm(stdout, algs[i]);
                if (ratio >= 1)
                {
                    printf(" -> %f %s\n", ratio, "faster"); /* i.e., tot_runtimes[k] = tot_runtimes[i]/ratio */
                }
                else
                {
                    printf(" -> %f %s\n", 1.0/ratio, "slower"); /* i.e., tot_runtimes[k] = tot_runtimes[i]*ratio */
                }
            }
        }
    }

    free(tot_runtimes);
}

sorting_algorithm_t parse_sorting_algorithm(const char *str)
{
    assert( str != NULL );

    if (!strcmp("insertion", str))
    {
        return insertion_sort_algorithm;
    }
    if (!strcmp("merge", str))
    {
        return merge_sort_algorithm;
    }
    if (!strcmp("quick", str))
    {
        return quick_sort_algorithm;
    }
    if (!strcmp("stdc", str))
    {
        return stdc_sort_algorithm;
    }

    return unknown_sort_algorithm;
}

void print_sorting_algorithm(FILE *fp, sorting_algorithm_t alg)
{
    assert( fp != NULL );

    switch (alg)
    {
        case insertion_sort_algorithm:
            fprintf(fp, "Insertion sort");
            break;
        case merge_sort_algorithm:
            fprintf(fp, "Merge sort");
            break;
        case quick_sort_algorithm:
            fprintf(fp, "Quick sort");
            break;
        case stdc_sort_algorithm:
            fprintf(fp, "Standard C sort");
            break;
        case unknown_sort_algorithm:
            fprintf(fp, "Unknown sort");
            break;
    }
}

void print_array(const item_t *items, size_t n)
{
    size_t i;

    assert( items != NULL );

    putchar('[');
    for (i = 0; i < n; ++i)
    {
        if (i > 0)
        {
            putchar(',');
        }
        printf("(%d,%f)", items[i].key, items[i].value);
    }
    putchar(']');
}

void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s <options>\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "-a <value>: Specifies the sorting algorithm to use.\n"
                    "            Possible values are:\n"
                    "            - insertion: insertion sort\n"
                    "            - merge: merge sort\n"
                    "            - quick: quick sort\n"
                    "            - stdc: standard C's sort\n"
                    "            Repeats this option as many times as is the number of algorithms to use.\n");
    fprintf(stderr, "-h: Displays this message.\n");
    fprintf(stderr, "-n <value>: Specifies the size of the array to sort.\n"
                    "            [default: %lu]\n", DEFAULT_OPT_ARRAY_SIZE);
    fprintf(stderr, "-r <value>: Specifies the number of times the comparison must be repeated.\n"
                    "            [default: %lu]\n", DEFAULT_OPT_NUM_RUNS);
    fprintf(stderr, "-s <value>: Specifies the seed for the random number generator.\n"
                    "            [default: <current time>]\n");
    fprintf(stderr, "-v: Enables output verbosity.\n"
                    "    [default: <%s>]\n", (DEFAULT_OPT_VERBOSE ? "enabled" : "disabled"));
    fprintf(stderr, "-x: For each random array, also sorts its corresponding sorted versions (including the\n"
                    "    ones sorted both in increasing and decreasing order).\n"
                    "    [default: <%s>]\n", (DEFAULT_OPT_SORT_SPECIAL ? "enabled" : "disabled"));
}


int main(int argc, char *argv[])
{
    sorting_algorithm_t *opt_algs = NULL;
    size_t opt_n = DEFAULT_OPT_ARRAY_SIZE;
    size_t opt_num_runs = DEFAULT_OPT_NUM_RUNS;
    unsigned int opt_seed = DEFAULT_OPT_RNG_SEED;
    int opt_verbose = DEFAULT_OPT_VERBOSE;
    int opt_help = 0;
    int opt_sort_special = DEFAULT_OPT_SORT_SPECIAL;
    size_t num_algs = 0;
    int chosen_algs[NUM_SORTING_ALGORITHMS];
    int arg;
    size_t i;
    size_t j;

    memset(chosen_algs, 0, NUM_SORTING_ALGORITHMS*sizeof(int));

    for (arg = 1; arg < argc; ++arg)
    {
        if (!strcmp("-a", argv[arg]))
        {
            sorting_algorithm_t alg;

            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected algorithm name.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }

            alg = parse_sorting_algorithm(argv[arg]);
            if (alg == unknown_sort_algorithm)
            {
                fprintf(stderr, "ERROR: unknown algorithm name '%s'.\n", argv[arg]);
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            if (chosen_algs[(int) alg] == 0)
            {
                chosen_algs[(int) alg] = 1;
                ++num_algs;
            }
        }
        else if (!strcmp("-h", argv[arg]))
        {
            opt_help = 1;
        }
        else if (!strcmp("-n", argv[arg]))
        {
            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected array size.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            opt_n = atol(argv[arg]);
        }
        else if (!strcmp("-r", argv[arg]))
        {
            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected number of runs.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            opt_num_runs = atol(argv[arg]);
        }
        else if (!strcmp("-s", argv[arg]))
        {
            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected seed for random number generator.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            opt_seed = atoi(argv[arg]);
        }
        else if (!strcmp("-v", argv[arg]))
        {
            opt_verbose = 1;
        }
        else if (!strcmp("-x", argv[arg]))
        {
            opt_sort_special = 1;
        }
    }

    if (opt_help)
    {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }

    if (opt_verbose)
    {
        printf("Options:\n");
        printf("* Array size: %lu\n", opt_n);
        printf("* Number of runs: %lu\n", opt_num_runs);
        printf("* Seed for random number generation: %u\n", opt_seed);
        printf("* Sorts special instances: %d\n", opt_sort_special);
        printf("* Algorithms:\n");
        j = 0;
        for (i = 0; i < NUM_SORTING_ALGORITHMS; ++i)
        {
            if (j > 0)
            {
                printf(", ");
            }
            if (chosen_algs[i] == 1)
            {
                print_sorting_algorithm(stdout, i);
                ++j;
            }
        }
    }

    if (num_algs == 0)
    {
        fprintf(stderr, "ERROR: at least one sorting algorithm must be specified.\n");
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    opt_algs = malloc(num_algs*sizeof(sorting_algorithm_t));
    if (opt_algs == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for sorting algorithms");
    }

    j = 0;
    for (i = 0; i < NUM_SORTING_ALGORITHMS; ++i)
    {
        if (chosen_algs[i] == 1)
        {
            opt_algs[j++] = (sorting_algorithm_t) i;
        }
    }

    compare_algorithms(opt_algs, num_algs, opt_n, opt_seed, opt_num_runs, opt_sort_special, opt_verbose);

    free(opt_algs);

    return EXIT_SUCCESS;
}
