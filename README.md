# CSERIO

CSERIO is a single header C library to perform IO operations on .ser format image sequence files.

## Usage
Compile the `cserio.c` file like any other source file and include the `cserio.h` header like normal.

In very simple cases, you could just include the `cserio.h` header and define `CSERIO_IMPLEMENTATION` before
the include which will define the implementation.
```C
#define CSERIO_IMPLMENTATION
#include "cserio.h"
```


### Example Usage
```C
#define CSERIO_IMPLMENTATION

#include "cserio.h"


int main(void) {
    int status = 0;
    serfile* my_ser = NULL;

    ser_open_file(
            &my_ser,
            "/path/saturn_capture.ser",
            READONLY,
            &status
    );
    if (status) {
        fprintf(stderr, "Error opening ser: %d\n", status);
        exit(EXIT_FAILURE);
    }

    int32_t frame_count = 0;
    ser_get_frame_count(my_ser, &frame_count, &status);
    if (status) {
        fprintf(stderr, "Error getting frame count: %d\n", status);
        exit(EXIT_FAILURE);
    }
    printf("Frame count: %d\n", frame_count);

    ser_close_file(my_ser, &status);
    if (status) {
        fprintf(stderr, "Error closing ser: %d\n", status);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
```
