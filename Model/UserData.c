//
// Created by KHANG JU CHOI on 2023/02/25.
//
#ifndef ADDRESSBOOK_C_USERDATA_C
#define ADDRESSBOOK_C_USERDATA_C
#include"UserData.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//extern UserDataNode* g_pHead;
extern UserDataNode g_DummyNode;

//1. 전체 리스트 출력 함수
//=> 1st Node 가리키는 전역 포인터 변수 사용
void PrintAllList()
{
    /*
    //Using pHead
    UserDataNode* pNode = g_pHead;
    */
    //Using DummyNode
    UserDataNode* pNode = g_DummyNode.pnNext;

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
//  --> 성공 1, 실패 0
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
        return 0;
    }

    //1. Node 생성
    UserDataNode* pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pNode, 0, sizeof(UserDataNode));

    //2. Node 저장할 위치 검색
    if(g_DummyNode.pnNext == NULL)
    {
        //Using Dummy Node
        g_DummyNode.pnNext = pNode;
        AddData(pNode, pszParam);

        /*
        //Using pHead
        g_pHead = pNode;
        AddData(pNode, pszParam);
        */
     }

    else
    {

        //Using DummyNode
        pNode->pnNext = g_DummyNode.pnNext;
        g_DummyNode.pnNext = pNode;
        AddData(pNode, pszParam);
        /*
        //Using pHead
        pNode->pnNext = g_pHead;
        g_pHead = pNode;
        AddData(pNode, pszParam);
         */
    }

    return 1;
}



//3. 전체 리스트 삭제 함수(동적할당 해제)
void ReleaseAllList()
{
    //Using DummyNode
    UserDataNode *pDelete = g_DummyNode.pnNext;
    /*
    //Using pHead
    UserDataNode *pDelete = g_pHead;
    */
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

//3_1. 특정 Node 검색 함수
UserDataNode* SearchNode(const char* *pszParam)
{
    UserDataNode *pSearch = &g_DummyNode;
    if(pSearch == NULL)
    {
        return NULL;
    }

    const unsigned long nLength_name = strlen(*pszParam);
    const unsigned long nLength_phoneNumber = strlen(*(pszParam+1));


    while (pSearch->pnNext != NULL)
    {
        if (strncmp(pSearch->pnNext->strData.name, *pszParam, nLength_name + 1) == 0
            && strncmp(pSearch->pnNext->strData.phoneNumber, *(pszParam + 1), nLength_phoneNumber + 1) == 0)
        {
            return pSearch;
        }
        pSearch = pSearch->pnNext;
    }

    return NULL;
}

//3_2. 특정 Node 삭제 함수
const int DeleteNode(const char* *pszParam)
{
    if(pszParam == NULL)
    {
        return 0;
    }

    UserDataNode *pSearch = SearchNode(pszParam);
    UserDataNode *pTemp = NULL;

    if(pSearch == NULL)
    {
        return 0;
    }

    //검색 결과로 받은 Node삭제
    //1. 삭제 대상 Node의 주소 임시 저장
    pTemp = pSearch->pnNext;

    //2. 삭제 대상 Node의 앞쪽 Node와 뒤쪽 Node 연결
    pSearch->pnNext = pSearch->pnNext->pnNext;

    //3. 삭제 대상 Node 삭제하기
    free(pTemp->strData.name);
    free(pTemp->strData.phoneNumber);
    free(pTemp);
    pTemp = NULL;

    return 1;
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