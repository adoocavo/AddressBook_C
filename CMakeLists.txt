cmake_minimum_required(VERSION 3.22)
project(AddressBook_C C)

set(CMAKE_C_STANDARD 11)

add_executable(AddressBook_C main.c Model/DS_DoubleLinkedList.h View/UserInterface.h
        Model/DS_DoubleLinkedList.c View/UserInterface.c Model/InputData.c Model/InputData.h)
