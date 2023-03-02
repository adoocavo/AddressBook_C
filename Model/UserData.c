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
    memset(0, pNode, sizeof(UserDataNode));

    //생성할 Node에 입력 Data 저장 - Deep copy
    AddData(pNode, name, phoneNumber);

    //Insert 전 전/후 Node 연결 처리

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
    else
    {
        //새로 삽입하는 Node - 다음 Node 연결
        pNode->pnNext = g_pHead->pnNext;
        g_pHead->pnNext->pnPrev = pNode;

        //Head Node - 새로 삽입하는 Node 연결
        g_pHead->pnNext = pNode;
        pNode->pnPrev = g_pHead;
    }

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
    memset(0, pNode, sizeof(UserDataNode));

    //생성할 Node에 입력 Data 저장 - Deep copy
    AddData(pNode, name, phoneNumber);

    //Insert 전 전/후 Node 연결 처리

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
    //2. 삭제 대상 Node 임시 저장 포인터
    UserDataNode *pDelete = g_pHead->pnNext;
    while (pDelete == g_pTail)
    {

    }


}

//+) 리스트 비어있는지 확인
const int IsEmpty()
{
    if(g_pHead->pnNext == g_pTail
    && g_pTail->pnPrev == g_pHead)
    {
        printf("Empty List");
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