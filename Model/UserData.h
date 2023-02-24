//
// Created by KHANG JU CHOI on 2023/02/21.
//
#pragma once

//Node 제작 - Node에 저장할 Data
typedef struct UserData
{
    //관리될 Data
    char *name;
    char *phoneNumber;
} UserData;

//Node 제작 - 관리 구조 체계1(저장할 Data네 대한 저장 틀)
typedef struct UserDataNode
{
    struct UserData strData;

    //Data 관리(구조) 체계이다 == Data 관리를 위한 포인터
    struct UserDataNode* pnNext;
} UserDataNode;

//관리 구조 체계2 - Node Data를 utilize 하는 함수
static inline void AddData(struct UserDataNode* list, const char* *pszParam,
        const unsigned long* pnLength)
{
    //1. 이름 입력받은 크기만큼 동적할당 + copy
    list->strData.name = (char *) malloc(pnLength[0] + 1);
    strncpy(list->strData.name, *pszParam, pnLength[0] + 1);

    //2. 전화번호 입력받은 크기만큼 동적할당 + copy
    list->strData.phoneNumber = (char *) malloc(pnLength[1] + 1);
    strncpy(list->strData.phoneNumber, *(pszParam+1), pnLength[1] + 1);

}

/*
//입력된 문자열의 바이트 수 구하는 함수 구현
static inline int GetByteOfAry(const char* aryBuffer)
{
    int i = 0;
    int nCount = 0;

    while(aryBuffer[i] != '\0')
    {
        ++nCount;
        ++i;
    }

    return nCount;

}
*/

void GarbageCollector(struct UserDataNode* list)
{
    ;
}
void SearchData(UserDataNode*);
void DeleteData(UserDataNode*);