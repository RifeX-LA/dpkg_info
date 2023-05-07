# DPKG

## Overview

This is the application to get info about installed _dpkg_ packages. 

Application prints info with the following pattern:

```
<publisher name> <publisher email> [<packages count>]
Total packages size: <total packages size>

Package: <package name>
Size: <package size>

Package: <package name>
Size: <package size>

...
```

**Application always prints info in descending order by \<packages count\>**.

**If the publisher name is missing, it will be replaced with "unknown". Publisher email will be missed as well**.

**If the package name is missed, it will be replaced with "unknown"**.

**If the package size is missed, it will be replaced with "0"**.

## Usage

1. Print all installed _dpkg_ packages:

    ```shell
    ./dpkg_info
    ```
   
2. Don't show specified publishers:
    ```shell
    ./dpkg_info -b publisher1 --ban publisher2
    ```
   
3. Print info to the specified file:
    ```shell
    ./dpkg_info -o output.txt
    ```

## Requirements

* `Linux` system
* `CMake 3.16` or higher
* `boost 1.65.1` or higher **with compiled binaries**
* `fmt` library

## Build

In project's root directory run following commands:

```shell
mkdir build
cd build
cmake ..
make
```

Run application:
```shell
./dpkg_info
```