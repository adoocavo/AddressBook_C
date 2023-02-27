//
// Created by KHANG JU CHOI on 2023/02/21.
//
#ifndef ADDRESSBOOK_C_USERINTERFACE_H
#define ADDRESSBOOK_C_USERINTERFACE_H
#include <stdio.h>
static inline void CleanStdinBuffer()
{
    while(getchar() != '\n') {}
}
void InputInterface(char*, char**, const int);


#endif //ADDRESSBOOK_C_USERINTERFACE_H

