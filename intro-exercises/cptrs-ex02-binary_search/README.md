# Exercise `binary_search`

Write a generic function binary_search() that uses the binary search algorithm
to search a sorted array for a given key (like C bsearch() function does)
`void *binary_search(const void *key, const void *base, size_t
num_elem, size_t elem_size, int (*compar)(const void *, const
void *));`

Where:

- `key`: pointer to the object to search
- `base`: pointer to the first element of the input array
- `num_elem`: number of elements of the input array
- `elem_size`: number of bytes taken by each element of the array
- `compar`: pointer to a comparison function which takes a pointer to the key object as 1st argument and to an array element as 2nd argument, and returns an integer < 0, == 0, or > 0 if the key object is, respectively, <, ==, or > the
array element

Returns a pointer to a matching element of the array, or NULL if no match is found

## Implementation

Implemented as a cast from generic type to `unsigned char` to work on it as bytes.

Implementation of generic binary search

```c
void *binary_search(const void *key, const void *base, size_t num_elem, size_t elem_size, int (*compar)(const void *, const void *))
{
    assert(key != NULL);
    assert(base != NULL);
    assert(compar != NULL);

    int lo = 0;
    int hi = num_elem - 1;

    const unsigned char *temp_key = key;
    const unsigned char *array = base;

    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        if (compar(temp_key, &(array[mid * elem_size])) < 0)
            hi = mid - 1;
        else if (compar(temp_key, &(array[mid * elem_size])) > 0)
            lo = mid + 1;
        else
            return (void *)&array[mid * elem_size];
    }
    return NULL;
}
```
