# CSERIO

CSERIO is a single header C library to perform IO operations on .ser format image sequence files.

## Usage
In the simplest case, you include the `cserio.h` header and define `CSERIO_IMPLEMENTATION` before
the include.
```C
#define CSERIO_IMPLMENTATION
#include "cserio.h"
```

You could also compile the header with the appropriate define into an object file and link after.
This omits the need for `#define CSERIO_IMPLMENTATION` in the source.
```sh
cc -DCSERIO_IMPLEMENTATION -x c -c cserio.h
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
