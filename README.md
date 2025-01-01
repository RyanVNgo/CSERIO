# CSERIO
An interface to SER format image captures for C programmers. 

## Building and Installing

### Unix Systems:
```sh
> git clone https://github.com/RyanVNgo/CSERIO
> cd CSERIO
> make
> make install prefix={target/directory}
```

Runnning `make` will create a `bin` directory in the project home with two subdirectories,
`/include` and `/lib`. The `cserio.h` header will be placed in the `/include` directory and
the `libcserio.a` library file will be placed in the `/lib` directory.

The `prefix` argument for `make install` specifies the path to the directory that CSERIO will
install the include and library files. When installed, two new directories (if not already present)
will be created in the target directory: `/include` and `/lib`. If `prefix` is not defined, then
`make install` will not do anything.
