# Exercise `any_copy`

Write a generic function any_copy() that copies the content of an
array into another one (like the C memcpy() function does)
`void any_copy(void *dest, const void *src, size_t n);`

Where:

- `dest`: pointer to the first element of the destination array
- `src`: pointer to the first element of the source array
- `n`: number of bytes of the source array to copy into the
destination array

## Implementation

Implemented as a cast from generic type to `unsigned char` to work on it as bytes.

Each element is considered as an `unsigned char` (regular byte), then it's copied in destination array.

```c
void any_copy(void *dest, const void *src, size_t n)
{
    assert(dest != NULL);
    assert(src != NULL);

    unsigned char *temp_dest = dest;
    const unsigned char *temp_src = src;

    for (int i = 0; i < n; i++)
        temp_dest[i] = temp_src[i];
}
```
