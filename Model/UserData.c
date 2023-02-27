//
// Created by KHANG JU CHOI on 2023/02/25.
//
#ifndef ADDRESSBOOK_C_USERDATA_C
#define ADDRESSBOOK_C_USERDATA_C
#include"UserData.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

extern UserDataNode* g_pHead;

//1. 전체 리스트 출력 함수
//=> 1st Node 가리키는 전역 포인터 변수 사용
void PrintAllList()
{
    UserDataNode* pNode = g_pHead;

    //Node 유효성 검사
    if(pNode == NULL)
    {
        return;
    }

    //while(pNode->pnNext != NULL)
    while(pNode != NULL)
    {
            printf("[%p] %s, next[%p]\n", pNode, pNode->strData.name, pNode->pnNext);
            printf("[%p] %s, next[%p]\n", pNode, pNode->strData.phoneNumber, pNode->pnNext);

            pNode = pNode->pnNext;

    }
}

//2. 새로운 Node 추가 함수
//=> 첫 번째 Node로 삽입
//=> Data 추가 실패/성공 확인 위해 return const int
//=> User 측 에서는 입력할 Data만 입력하게 만들기(내부기능 고려X)
const int InsertNewNode_first(const char* *pszParam)
{
    /* => InsertNewNode_end
    if(*pszParam == NULL || *(pszParam+1) == NULL)
    {
        return 1;
    }

    const int nLength_name = strlen(*pszParam);
    const int nLength_phoneNumber = strlen(*(pszParam+1));

    UserDataNode* pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    UserDataNode* pCheck = g_pHead;

    //Node 추가할 위치 탐색

    if(g_pHead == NULL)
    {
        g_pHead = pNode;
        AddData(pNode, pszParam);
    }

    else
    {
        while(1)
        {
            //위치 찾아서 Node 생성
            if(pCheck->pnNext = NULL)
            {
                pCheck->pnNext = pNode;
                AddData(pNode, pszParam);
                break;
            }

            pCheck = pCheck->pnNext;
        }
*/
    //0. pszParam == NULL인 경우 (param의 유효성 검사)
    if(*pszParam == NULL || *(pszParam+1) == NULL)
    {
        return 1;
    }

    //1. Node 생성
    UserDataNode* pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pNode, 0, sizeof(UserDataNode));

    //2. Node 저장할 위치 검색
    if(g_pHead == NULL)
    {
        g_pHead = pNode;
        AddData(pNode, pszParam);
    }

    else
    {
        pNode->pnNext = g_pHead;
        g_pHead = pNode;
        AddData(pNode, pszParam);
    }

    return 0;
}



//3. 전체 리스트 삭제 함수(동적할당 해제)
void ReleaseAllList()
{
    UserDataNode *pDelete = g_pHead;
    UserDataNode *pTemp = NULL;

    while(pDelete != NULL)
    {
        printf("Delete : [%p] %s, next[%p]\n", pDelete, pDelete->strData.name, pDelete->pnNext);
        printf("Delete : [%p] %s, next[%p]\n", pDelete, pDelete->strData.phoneNumber, pDelete->pnNext);
        pTemp = pDelete->pnNext;

        free(pDelete->strData.name);
        free(pDelete->strData.phoneNumber);
        free(pDelete);

        pDelete = pTemp;
    }
}




void AddData(UserDataNode* pNode, const char* *pszParam)
{
    const unsigned long nLength_name = strlen(*pszParam);
    const unsigned long nLength_phoneNumber = strlen(*(pszParam+1));

    //이름, 번호 저장할 메모리 동적할당
    pNode->strData.name = (char*)malloc(nLength_name+1);
    strncpy(pNode->strData.name, *pszParam, nLength_name+1);

    pNode->strData.phoneNumber = (char*)malloc(nLength_phoneNumber+1);
    strncpy(pNode->strData.phoneNumber, *(pszParam+1), nLength_phoneNumber+1);
}
#endif