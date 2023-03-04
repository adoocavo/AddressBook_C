//
// Created by KHANG JU CHOI on 2023/02/25.
//

#include"UserData.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//enum
//{
//    NO = 0,
//    YES = 1,
//    ERROR = 2,
//    SUCCESS = 3
//};


//1. 모든 Node 초기화 함수
//=> 필요한가??
//=> Head/Tail 포인터 변수에 동적할당 하여 Head/Tail (Dummy) Node 생성
//=> Head/Tail Node가 서로를 포인팅 하게 초기화
//=> 전체 리스트 삭제 함수(ReleaseList())에서 동적할당 해제 후 NULL 포인팅 만들기
void InitList()
{
    g_pHead = (UserDataNode*)malloc(sizeof(UserDataNode));
    g_pTail = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(g_pHead, 0, sizeof(UserDataNode));
    memset(g_pTail, 0, sizeof(UserDataNode));

    //Head/Tail Node가 서로 포인팅 하도록 만들기 Empty 상황
    g_pHead->pnNext = g_pTail;
    g_pTail->pnPrev = g_pHead;

    //Node 개수 counting 전역 변수도 초기화
    g_nNodeCount = 0;

    printf("InitList\n");
}

//2. Head 방향으로 새로운 Node Insert
const int InsertAtHead(const char *name, const char *phoneNumber)
{
    //param 유효성 검사
    if(CheckParam(name, phoneNumber) == ERROR)
    {
        return ERROR;
    }

    //추가할 Node 생성
    UserDataNode *pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pNode, 0, sizeof(UserDataNode));

    //생성할 Node에 입력 Data 저장 - Deep copy
    AddData(pNode, name, phoneNumber);

    //Insert 전 전/후 Node 연결 처리
    //1. 새로 삽입하는 Node의 prev,next 채우기
    pNode->pnNext = g_pHead->pnNext;
    pNode->pnPrev = g_pHead;

    //2. 새로 삽입하는 Node에 연결된 prev,next Node의 next prev 채우기
    pNode->pnNext->pnPrev = pNode;
    g_pHead->pnNext = pNode;
/*
    //1. 비어있는 List
    if(IsEmpty() == YES)
    {

        //새로 삽입하는 Node - Head Dummy Node 간 연결
        g_pHead->pnNext = pNode;
        pNode->pnPrev = g_pHead;

        //새로 삽입하는 Node - Tail Dummy Node 간 연결
        g_pTail->pnPrev = pNode;
        pNode->pnNext = g_pTail;
    }

    //2. Head Dummy Node 바로 뒤에 Insert
    else {
        //새로 삽입하는 Node - 다음 Node 연결
        pNode->pnNext = g_pHead->pnNext;
        g_pHead->pnNext->pnPrev = pNode;

        //Head Node - 새로 삽입하는 Node 연결
        g_pHead->pnNext = pNode;
        pNode->pnPrev = g_pHead;
    }
*/

    ++g_nNodeCount;
    return SUCCESS;

}


//3. Tail 방향으로 새로운 Node Insert
const int InsertAtTail(const char *name, const char *phoneNumber)
{
    //param 유효성 검사
    if(CheckParam(name, phoneNumber) == ERROR)
    {
        return ERROR;
    }

    //추가할 Node 생성
    UserDataNode *pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pNode, 0, sizeof(UserDataNode));

    //생성할 Node에 입력 Data 저장 - Deep copy
    AddData(pNode, name, phoneNumber);

    //Insert 전 전/후 Node 연결 처리

    //1. 새롭게 추가하는 Node의 prev, next 채우기
    pNode->pnPrev = g_pTail->pnPrev;
    pNode->pnNext = g_pTail;

    //2. 새로 삽입하는 Node에 연결된 prev,next Node의 next prev 채우기
    pNode->pnPrev->pnNext = pNode;
    pNode->pnNext->pnPrev = pNode;

/*
    //1. 비어있는 List
    if(IsEmpty() == YES)
    {
        //새로 삽입하는 Node - Head Dummy Node 간 연결
        g_pHead->pnNext = pNode;
        pNode->pnPrev = g_pHead;

        //새로 삽입하는 Node - Tail Dummy Node 간 연결
        g_pTail->pnPrev = pNode;
        pNode->pnNext = g_pTail;
    }

    //2. Tail Dummy Node 바로 앞에 Insert
    else
    {
        //새로 삽입 Node - Tail Dummy Node 바로 앞 Node 간 연결
        pNode->pnPrev = g_pTail->pnPrev;
        g_pTail->pnPrev->pnNext = pNode;

        //새로 삽입 Node - Tail Dummy Node 간 연결
        pNode->pnNext = g_pTail;
        g_pTail->pnPrev = pNode;
    }
*/
    ++g_nNodeCount;
    return SUCCESS;
}

//4. 모든 Node 할당해제(삭제) 함수
const int ReleaseList()
{
    //1. 비어있는 리스트인지 확인
    if (IsEmpty() == YES)
    {
        return ERROR;
    }

    //Head -> Tail 방향으로 삭제
    //2. 대상 Node 차례로 할당 해제
    UserDataNode *pDelete = g_pHead->pnNext;            //현재 삭제 대상 저장
    UserDataNode *pTemp = NULL;                         //다음 삭제 대상 임시저장

    while (pDelete != g_pTail)
    {
        //다음 삭제 대상 임시 저장
        pTemp = pDelete->pnNext;

        DeleteNode(pDelete);
        pDelete = pTemp;
    }

    return SUCCESS;
}

//5. 특정 Node 삭제 함수
const int DeleteNode(UserDataNode* pDelete)
{
/*
    if(CheckParam(pDelete->strData.name, pDelete->strData.phoneNumber)
    == ERROR)
    {
        return ERROR;
    }
*/
    //Param 유효성 검사
    if(pDelete == NULL || CheckParam(pDelete->strData.name, pDelete->strData.phoneNumber) == ERROR)
    {
        return ERROR;
    }

    //삭제 대상 Node 앞/뒤 연결
    pDelete->pnPrev->pnNext = pDelete->pnNext;
    pDelete->pnNext->pnPrev = pDelete->pnPrev;

    //삭제 대상 출력
    printf("Delete : [%p] %s, next[%p]\n", pDelete, pDelete->strData.name, pDelete->pnNext);
    printf("Delete : [%p] %s, next[%p]\n", pDelete, pDelete->strData.phoneNumber, pDelete->pnNext);

    //삭제 대상 삭제
    free(pDelete->strData.name);
    free(pDelete->strData.phoneNumber);
    pDelete->strData.name = NULL;
    pDelete->strData.phoneNumber = NULL;

    free(pDelete);
    pDelete = NULL;

    --g_nNodeCount;
    return SUCCESS;

}

//6. 특정 Node 검색 함수
//=> Head -> Tail 방향으로 검색
UserDataNode* SearchNode(const char *name, const char *phoneNumber)
{
    if(CheckParam(name, phoneNumber) == ERROR)
    {
        return NULL;
    }

    //검색 대상 : from g_pHead->pnNext to g_pTail->pnPrev
    UserDataNode *pSearch = g_pHead->pnNext;

    while(pSearch != g_pTail)
    {
        if (strncmp(pSearch->strData.name, name, strlen(pSearch->strData.name)) == 0 &&
            strncmp(pSearch->strData.phoneNumber, phoneNumber, strlen(pSearch->strData.phoneNumber)) == 0)
        {
            return pSearch;
        }

        pSearch = pSearch->pnNext;
    }

    return NULL;
}

//8. 전체 List 출력 함수
//Head -> Tail 방향으로
void PrintAllList()
{
    printf("PrintAllList(): g_nNodeCount : %d, g_pHead [%p], g_pTail[%p]\n", g_nNodeCount, g_pHead, g_pTail);


    UserDataNode* pPrint = g_pHead->pnNext;

    while(pPrint != g_pTail) {
        printf("prev[%p] %s[%p], next[%p]\n", pPrint->pnPrev, pPrint->strData.name, pPrint, pPrint->pnNext);
        printf("prev[%p] %s[%p], next[%p]\n", pPrint->pnPrev, pPrint->strData.phoneNumber, pPrint, pPrint->pnNext);

        pPrint = pPrint->pnNext;
    }
}

//10. 특정 index에 Node 삽입
const int InsertAtIdx(const int idx, const char *name, const char *phoneNumber)
{
    if(CheckParam(name, phoneNumber) == ERROR || idx >= g_nNodeCount)
    {
        return ERROR;
    }

    //삽입하려는 Index의 현재 Node
    UserDataNode *pSearch = GetNodeAtIdx(idx);
    //특정 Index에 삽입하려는 새로운 Node
    UserDataNode *pNode = (UserDataNode*)malloc(sizeof(UserDataNode));

    //1. 새로 생성한 Node에 입력받은 Data 저장
    AddData(pNode, name, phoneNumber);

    //2. 검색 결과 pNode의 Head 방향에 Insert
    pNode->pnNext = pSearch;
    pNode->pnPrev = pSearch->pnPrev;

    pSearch->pnPrev->pnNext = pNode;
    pSearch->pnPrev = pNode;

    //g_nNodeCount 수정
    ++g_nNodeCount;
    return SUCCESS;
}

//11. 특정 index의 Node 검색 + 주소 리턴
UserDataNode * GetNodeAtIdx(const int idx)
{
    UserDataNode *pSearch = g_pHead->pnNext;
    int countIdx = 0;

    while(countIdx != idx)
    {
        pSearch = pSearch->pnNext;
        ++countIdx;
    }
    return pSearch;
}

//+) 리스트 비어있는지 확인
const int IsEmpty()
{
    if(g_pHead->pnNext == g_pTail
    && g_pTail->pnPrev == g_pHead)
    {
        printf("Empty List\n");
        return YES;
    }

    return NO;
}

//+) Node에 동적할당 하여 name, phoneNumber 저장하는 함수
//=> Add Data to Node by Deep copy
void AddData(UserDataNode* pNode, const char *name, const char *phoneNumber )
{
    const unsigned long nLength_name = strlen(name);
    const unsigned long nLength_phoneNumber = strlen(phoneNumber);

    //이름, 번호 저장할 메모리 동적할당
    pNode->strData.name = (char*)malloc(nLength_name+1);
    strncpy(pNode->strData.name, name, nLength_name+1);

    pNode->strData.phoneNumber = (char*)malloc(nLength_phoneNumber+1);
    strncpy(pNode->strData.phoneNumber, phoneNumber, nLength_phoneNumber+1);
}