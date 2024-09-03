# CSERIO
An interface to SER format image captures for C programmers. 

## Building and Installing

### Unix Systems:
```sh
> git clone https://github.com/RyanVNgo/CSERIO
> cd CSERIO
> ./configure [--prefix=/target/install/path]
> make
> make install
```
The `--prefix` argument specifies the path to the directory that CSERIO will install the include and library files. When installed, two new directories (if not already present) will be created in the target directory: `/include` and `/lib`.

If the configuration were run as:
```sh
> ./configure --prefix=/target/dir
```
Then `make install` will copy the `libcserio` library file into `/target/dir/lib` and the necessary include files to `target/dir/include`. If the `--prefix` argument is not specified, the library will install into the project directory.
