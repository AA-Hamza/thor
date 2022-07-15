# Thor

Thor is a multi-threaded web server inspired by NGNIX. 

## Performance
![Thor, Apache and Ngnix](https://user-images.githubusercontent.com/33000142/179321532-6c35f32f-d3bd-41de-b68b-629fd5c9c1d6.svg)

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
