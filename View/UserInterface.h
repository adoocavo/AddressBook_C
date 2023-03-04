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

//1. strData 입력받는 인터페이스 함수
void InputInterface_strData(char*, char**, const int);

//2. index 입력받는 인터페이스 함수
void InputInterface_index(int *);


#endif //ADDRESSBOOK_C_USERINTERFACE_H

