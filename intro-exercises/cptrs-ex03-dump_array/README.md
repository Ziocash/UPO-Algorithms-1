# Exercise `dump_array()`

Write a generic function dump_array() that prints the content of an
array to a given output stream
`void dump_array(const void *base, size_t num_elem, size_t elem_size,
void (*dump_element)(const void *, FILE *), FILE *fp);`

Where:

- `base`: pointer to the first element of the input array
- `num_elem`: number of elements of the input array
- `elem_size`: number of bytes taken by each element of the array
- `dump_element`: pointer to a function which takes a pointer to an
array element as 1st argument and to an output stream as 2nd
argument, and prints the input array element to the given
output stream
- `fp`: the output stream where to print the input array

## Implementation

As requested, implementation must implement 3 parts:

1 - `dump_array` as main function: implements a `for` to iterate onto elements and dump the single element

```c
void dump_array(const void *base, size_t num_elem, size_t elem_size, void (*dump_element)(const void *, FILE *), FILE *fp)
{
    assert(base != NULL);
    assert(fp != NULL);

    const unsigned char *array = base;

    fprintf(fp, "[");
    for (int i = 0; i < num_elem; i++)
    {
        dump_element(&(array[i * elem_size]), fp); //array + i * elem_size also works
        if(i < num_elem - 1)
            fprintf(fp, ", ");
    }
    fprintf(fp, "]");
}
```

2 - `dump_int` as dumper function, passed by reference to `dump_array` with declaration: `void (*dump_element)(const void *, FILE *)`

```c
void dump_int(const void *p, FILE *fp)
{
    assert(p != NULL);
    assert(fp != NULL);
    const int *value = p; //this line is a surplus, it can be done directly casting p into *((int *)p)
    fprintf(fp, "%d", *value);
}
```

3 - `dump_string` as dumper function, passed by reference to `dump_array` with declaration: `void (*dump_element)(const void *, FILE *)`

```c
void dump_string(const void *p, FILE *fp)
{
    assert(p != NULL);
    assert(fp != NULL);
    const char * temp = *((char **)p); //surplus line
    fprintf(fp, "%s", temp);
}
```
