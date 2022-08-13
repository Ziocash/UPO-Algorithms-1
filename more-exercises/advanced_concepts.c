#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void test_hex_fprint();

static void test_mem_set();

static void test_mem_cmp();

static void test_all_of();

static void upo_hex_fprint(FILE *stream, const void *p, size_t n);

static void upo_mem_set(void *p, unsigned char c, size_t n);

static int upo_mem_cmp(const void *p1, const void *p2, size_t n);

static int upo_all_of(const void *base, size_t n, size_t sz, int (*pred)(const void *));

int is_even(const void *v)
{
    assert(v);
    return *((const int *)v) % 2 == 0;
}

int is_odd(const void *v)
{
    assert(v);
    return *((const int *)v) % 2 == 1;
}

int is_palindrome(const void *v)
{
    assert(v);
    const char **ps = (const char **)v;
    size_t len = strlen(*ps);
    for (size_t i = 0; i < len / 2; ++i)
    {
        if ((*ps)[i] != (*ps)[len - i - 1])
            return 0;
    }
    return 1;
}

int main(void)
{
    fprintf(stdout, "Test hex_fprint()...\n");
    test_hex_fprint();
    fflush(stdout);
    printf("hex_fprint() working properly.\n\n");

    fprintf(stdout, "Test mem_set()...\n");
    test_mem_set();
    fflush(stdout);
    printf("mem_set() working properly.\n\n");

    fprintf(stdout, "Test mem_cmp()...\n");
    test_mem_cmp();
    fflush(stdout);
    printf("mem_cmp() working properly.\n\n");

    fprintf(stdout, "Test all_of()...\n");
    test_all_of();
    fflush(stdout);
    printf("all_of() working properly.\n\n");

    return 0;
}

void test_hex_fprint()
{
    fprintf(stdout, "hex_fprint() testing...\n");
    char *s = "Hello, World!";
    char *expected_s = "48 65 6C 6C 6F 2C 20 57 6F 72 6C 64 21";
    char actual_s[strlen(expected_s) + 1];
    fflush(stdout);
    memset(actual_s, '\0', sizeof(actual_s));

    FILE *fp = fopen("./tester.txt", "w");
    upo_hex_fprint(fp, s, strlen(s));
    fclose(fp);

    fp = fopen("./tester.txt", "r");
    fgets(actual_s, strlen(expected_s) + 1, fp);
    fclose(fp);
    upo_hex_fprint(stdout, s, strlen(s));
    fprintf(stdout, "String pointer test...");
    assert(strlen(expected_s) == strlen(actual_s));
    assert(strcmp(expected_s, actual_s) == 0);
    fprintf(stdout, "OK\n");

    char cary[] = "GNU is Not Unix";
    char *expected_cary = "6F 74 20 55 6E 69 78 0";
    char actual_cary[strlen(expected_cary) + 1];
    fflush(stdout);
    fp = fopen("./tester.txt", "w");
    upo_hex_fprint(fp, cary + (sizeof cary) / 2, sizeof cary - (sizeof cary) / 2);
    fclose(fp);

    fp = fopen("./tester.txt", "r");
    fgets(actual_cary, strlen(expected_cary) + 1, fp);
    fclose(fp);

    upo_hex_fprint(stdout, cary + (sizeof cary) / 2, sizeof cary - (sizeof cary) / 2);
    fprintf(stdout, "Char array test...");
    assert(strlen(expected_cary) == strlen(actual_cary));
    assert(strcmp(expected_cary, actual_cary) == 0);
    fprintf(stdout, "OK\n");

    unsigned char ucary[] = {255, 128, 64, 32, 16};
    char *expected_ucary = "FF 80 40 20 10";
    char actual_ucary[strlen(expected_ucary) + 1];
    fflush(stdout);
    fp = fopen("./tester.txt", "w");
    upo_hex_fprint(fp, ucary, sizeof(ucary));
    fclose(fp);

    fp = fopen("./tester.txt", "r");
    fgets(actual_ucary, strlen(expected_ucary) + 1, fp);
    fclose(fp);

    upo_hex_fprint(stderr, ucary, sizeof(ucary));
    fprintf(stdout, "Unsigned char array test...");
    assert(strlen(expected_ucary) == strlen(actual_ucary));
    assert(strcmp(expected_ucary, actual_ucary) == 0);
    fprintf(stdout, "OK\n");
}

void test_mem_set()
{
    fprintf(stdout, "mem_set() testing...\n");
    char cary[] = "Hello, World!";
    char *expected = "?????????????";
    upo_mem_set(cary, '?', strlen(cary));
    fprintf(stdout, "Char array test...");
    assert(strlen(expected) == strlen(cary));
    assert(strcmp(expected, cary) == 0);
    upo_mem_set(cary, '\0', sizeof(cary));
    assert(strlen(cary) == 0);
    fprintf(stdout, "OK\n");

    int i = 10;
    int expected_i = 0;

    upo_mem_set(&i, 0, sizeof(i));
    fprintf(stdout, "Integer value test...");
    assert(i == expected_i);
    fprintf(stdout, "OK\n");

    unsigned char ucary[] = {255, 128, 64, 32, 16, 8};
    unsigned char expected_ucary[] = {127, 127, 127, 32, 16, 8};
    upo_mem_set(ucary, 127, (sizeof ucary) / 2);

    fprintf(stdout, "Unsigned char array test...");
    for (size_t i = 0; i < (sizeof(ucary) / sizeof(unsigned char)); i++)
        assert(ucary[i] == expected_ucary[i]);
    fprintf(stdout, "OK\n");
}

void test_mem_cmp()
{
    char *p1 = "Ciao";
    char *p2 = "Ciao";

    fprintf(stdout, "String test...");
    assert(memcmp(p1, p2, strlen(p1)) == upo_mem_cmp(p1, p2, strlen(p1)));
    fprintf(stdout, "OK\n");

    int int1 = 0;
    int int2 = 1;

    fprintf(stdout, "Integer value test 1...");
    assert(memcmp(&int1, &int2, sizeof(int)) == upo_mem_cmp(&int1, &int2, sizeof(int)));
    fprintf(stdout, "OK\n");

    int int3 = 16777215;
    int int4 = 65535;

    fprintf(stdout, "Integer value test 2...");
    assert(memcmp(&int3, &int4, sizeof(int)) == upo_mem_cmp(&int3, &int4, sizeof(int)));
    fprintf(stdout, "OK\n");
}

void test_all_of()
{
    int iary[] = {0, 2, 4, 6, 8};
    fprintf(stdout, "Integer values array odd correct test...");
    assert(upo_all_of(iary, sizeof(iary) / sizeof(int), sizeof(int), is_even) == 1);
    fprintf(stdout, "OK\n");

    int iary2[] = {0, 2, 5, 6, 8};
    fprintf(stdout, "Integer values array odd failed test...");
    assert(upo_all_of(iary2, sizeof(iary2) / sizeof(int), sizeof(int), is_even) == 0);
    fprintf(stdout, "OK\n");

    int iary3[] = {1, 3, 5, 7, 9};
    fprintf(stdout, "Integer values array even test...");
    assert(upo_all_of(iary3, sizeof(iary3) / sizeof(int), sizeof(int), is_odd) == 1);
    fprintf(stdout, "OK\n");

    char *sary[] = {"C", "H", "H", "C"};
    fprintf(stdout, "String values array palindrome test...");
    assert(upo_all_of(sary, sizeof(sary) / sizeof(sary[0]), sizeof(sary[0]), is_palindrome) == 1);
    fprintf(stdout, "OK\n");
}

void upo_hex_fprint(FILE *stream, const void *p, size_t n)
{
    const unsigned char *num = p;
    for (size_t i = 0; i < n; i++)
    {
        int value = *num;
        fprintf(stream, "%X", value);
        if (i < n - 1)
            fprintf(stream, " ");
        num++;
    }
    fprintf(stream, "\n");
}

void upo_mem_set(void *p, unsigned char c, size_t n)
{
    unsigned char *ptr = p;
    for (size_t i = 0; i < n; i++)
    {
        *ptr = c;
        ptr++;
    }
}

int upo_mem_cmp(const void *p1, const void *p2, size_t n)
{
    const unsigned char *ptr1 = p1;
    const unsigned char *ptr2 = p2;
    int value = 0;

    for (size_t i = 0; i < n; i++)
    {
        value += *ptr1 - *ptr2;
        ptr1++;
        ptr2++;
    }
    return value;
}

int upo_all_of(const void *base, size_t n, size_t sz, int (*pred)(const void *))
{
    const unsigned char *ptr = base;
    int value = 1;
    for (size_t i = 0; i < n; i++)
    {
        value &= pred(ptr + i * sz);
    }
    return value;
}