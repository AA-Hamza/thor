# Thor

Thor is a multi-threaded web server inspired by NGNIX. 

## Dependencies
G++ with C++11 support

meson build system 

## Installation
download this repo and enter in the directory.
```bash
meson setup builddir && cd builddir
meson compile
```

## Usage

```
Usage: ./thor <addr> <port> <root-dir> <num-of-workers>
```

## examples
```bash
./thor localhost 8080 home/ 4
```
