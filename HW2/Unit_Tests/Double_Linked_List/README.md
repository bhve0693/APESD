#Referenced from cmocka example for ECEN 5013 Embedded Software Essentials (Old)
#Developed for Unit Testing of Double Linked List HW for ECEN 5013 Advanced Practical Embedded Software

* [cmocka](https://cmocka.org/)

* cmocka [API](https://api.cmocka.org/index.html)

cmocka is included in this repository as a git subtree. See
3rd-party/README.md for details.

## Requirements

* cmake - available through most package managers.

## Build

* building cmocka:

    ```SHELL
    make cmocka
    ```

    This will go into the 3rd-party libraries directory and call cmake
    correctly to build cmocka.

* building and running tests:

    ```SHELL
    make test
    ```
    
* building main executable

    ```SHELL
    make all
    ```
    
* cleaing up local build artifacts:

    ```SHELL
    make clean
    ```
    
* removing all generated files, including 3rd-party builds

    ```SHELL
    make clobber
    ```
    
## Source

Included source files are:

* doublelinkedlist.{h|c} - library for double linked list.

* test_doublelinkedlist.c - unit tests for double linked list.

* main.c - simple demo of double linked list using library.

