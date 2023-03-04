//
// Created by KHANG JU CHOI on 2023/02/27.
//
//
// Created by KHANG JU CHOI on 2023/02/21.
//

#include"UserInterface.h"
//#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//1. strData 입력받는 인터페이스 함수
void InputInterface_strData(char* aryTemp, char* *aryBuffer, const int nSize)
{
    printf("이름을 입력하시오 : ");
    fgets(aryTemp, nSize, stdin);
    aryBuffer[0] = aryTemp;

    //fgets()로 입력받은 문자배열에서 '\n'제거
    //(*aryBuffer)[strlen(*aryBuffer)-1] = '\0';
    *(*aryBuffer + (strlen(*aryBuffer) - 1)) = '\0';

    printf("전화번호를 입력하시오 : ");
    fgets(aryTemp + (strlen(*aryBuffer) + 1),
          nSize, stdin);
    aryBuffer[1] = aryTemp + (strlen(aryTemp) + 1); //배열의 길이로 배열의 특정 위치 구하기

    //fgets()로 입력받은 문자배열에서 '\n'제거
    //(*(aryBuffer+1))[strlen(*(aryBuffer+1))-1] = '\0';
    *(*(aryBuffer+1) + (strlen(*(aryBuffer+1))-1)) = '\0';
}


//2. index 입력받는 인터페이스 함수
void InputInterface_index(int *idx)
{
    printf("Node를 Insert 하려는 Index를 입력하시오 : ");
    scanf("%d", idx);
    CleanStdinBuffer();
}