# Advanced concepts

This part of the repo contains all of those operations normally in C standard libraries (e.g.: `upo_mem_set` as `memset` C standard function).

## Hex_fprint

Hex_fprint allows to print an element into a bunch of bytes encoded into a hexadecimal string.

### Hex_fprint function prototype

```c
void upo_hex_fprint(FILE *stream, const void *p, size_t n);
```

### How hex_fprint works

- `stream`: pointer to file representing output (`stdout` or a real file)
- `p`: generic pointer to anything you want to print on `stream`
- `n`: size of object pointed by p

```c
char *s = "Hello, World!";
upo_hex_fprintf(stdout, s, strlen(s));
// prints 48 65 6C 6C 6F 2C 20 57 6F 72 6C 64 21

char cary[] = "GNU is Not Unix";
upo_hex_fprintf(stdout, cary + (sizeof cary)/2, sizeof cary - (sizeof cary)/2);
// prints 6F 74 20 55 6E 69 78 0

unsigned char ucary[] = {255,128,64,32,16};
upo_hex_fprintf(stderr, ucary, sizeof ucary);
// prints FF 80 40 20 10
```

Those tests are implemented in `test_hex_fprint` function.

## Mem_set

Mem_set allows to set bytes of a memory area with a given character.

### Mem_set function prototype

```c
void upo_mem_set(void *p, unsigned char c, size_t n);
```

### How mem_set works

- `p`: pointer to memory area
- `c`: char used to replace content
- `n`: size of memory area which `mem_set` works on

```c
char cary[] = "Hello, World!";
upo_mem_set(cary, '?', strlen(cary));
// cary: "?????????????"

int i = 10;
upo_mem_set(&i, 0, sizeof i);
// i: 0

unsigned char ucary[] = {255,128,64,32,16,8};
upo_mem_set(ucary, 127, (sizeof ucary)/2);
//ucary: {127,127,127,32,16,8}
```

## Mem_cmp

Mem_cmp allows to compare two memory areas and see if the first area pointed by `p1` is less than, equal or greater than the second area `p2`.

### Mem_cmp function prototype

```c
int upo_mem_cmp(const void *p1, const void *p2, size_t n);
```

### How mem_cmp works

- `p1`: pointer to first memory area
- `p2`: pointer to second memory area
- `n`: size of memory area

```c
char *p1 = "Ciao";
char *p2 = "Ciao";

memcmp(p1, p2, strlen(p1)) == upo_mem_cmp(p1, p2, strlen(p1)); // returns true

int int1 = 0;
int int2 = 1;

memcmp(&int1, &int2, sizeof(int)) == upo_mem_cmp(&int1, &int2, sizeof(int)); // returns true
```

## All_of

All_of allows to check if all elements in an array respect a predicate (e.g.: all numbers in an integer array are even).

### All_of function prototype

```c
int upo_all_of(const void *base, size_t n, size_t sz, int (*pred)(const void *));
```

### How all_off works

- `base`: pointer to array
- `n`: number of items in the array
- `sz`: element dimension
- `pred`: pointer to predicate function

```c
int iary[] = {0, 2, 4, 6, 8};
upo_all_of(iary2, sizeof(iary2) / sizeof(int), sizeof(int), is_even) == 0; //returns true
```
