# Intro-exercises

This part of the repo contains basic exercises to learn how to use generic functions with `void *` ponters.

## Any_copy

Any_copy allows to copy an entire memory area (equals to `memcpy` C standard function).

### Any_copy function prototype

```c
void any_copy(void *dest, const void *src, size_t n)
```

Source code is available [here](./cptrs-ex01-any_copy).

## Binary_search

Binary_search allows to sort a generic array (equals to `bsearch` C standard function).

### Binary_search function prototype

```c
void *binary_search(const void *key, const void *base, size_t num_elem, size_t elem_size, int (*compar)(const void *, const void *));
```

Source code is available [here](./cptrs-ex02-binary_search).

## Dump_array

Dump_array allows to dump a generic array into a file.

### Dump_array function prototype

```c
void dump_array(const void *base, size_t num_elem, size_t elem_size, void (*dump_element)(const void *, FILE *), FILE *fp)
```

Source code is available [here](./cptrs-ex03-dump_array).
