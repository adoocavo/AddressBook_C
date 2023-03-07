//
// Created by KHANG JU CHOI on 2023/02/25.
//
#include "DS_DoubleLinkedList.h"
//#include<stdlib.h>
#include<string.h>
//#include<stdio.h>

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
const int InsertAtHead(UserData *pParam)
{
    return InsertBefore(g_pHead->pnNext, pParam);
}

//2_1. Head 방향으로 새로운 Node Insert
//=> UserData (class)와의 의존성 없앤 함수
const int InsertAtHead_UsingPf(void *pUserData, const char*(*pfParam)(void *))
{
    const int nResult = InsertBefore_UsingPf(g_pHead->pnNext, pUserData, pfParam);

    if(nResult == ERROR)
    {
        return FAIL;
    }

    else
    {
        return nResult;
    }
}


//3. Tail 방향으로 새로운 Node Insert
const int InsertAtTail(UserData *pParam)
{
    return InsertBefore(g_pTail, pParam);
}

//3_1 Tail 방향으로 새로운 Node Insert
//=> GetKey에 대한 함수 포인터 member를 사용하여
// UserData (class)와의 의존성 없앤 함수
const int InsertAtTail_UsingPf(void *pUserData, const char*(*pfParam)(void *))
{
    const int nResult = InsertBefore_UsingPf(g_pTail, pUserData, pfParam);

    if(nResult == ERROR)
    {
        return FAIL;
    }

    else
    {
        return nResult;
    }
}


//4. 모든 Node 할당해제(삭제) 함수
const int ReleaseList()
{
    //1. 비어있는 리스트인지 확인
    if (GetSize() == 0)
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
    //Param 유효성 검사
    if(pDelete == NULL)
    {
        return ERROR;
    }

    //삭제 대상 Node 앞/뒤 연결
    pDelete->pnPrev->pnNext = pDelete->pnNext;
    pDelete->pnNext->pnPrev = pDelete->pnPrev;

    //삭제 대상 출력 --> 대상자료 소스파일로 이동
    printf("Delete : prev[%p] [%p], next[%p]\n", pDelete->pnPrev, pDelete, pDelete->pnNext);
    PrintUserData(pDelete->pUserData);

    /*
    printf("Delete : [%p] %s, next[%p]\n", pDelete,
           ((UserData*)(pDelete->pUserData))->name,
           pDelete->pnNext);
    printf("Delete : [%p] %s, next[%p]\n", pDelete,
           ((UserData*)(pDelete->pUserData))->phoneNumber,
           pDelete->pnNext);
*/
    /*
    //삭제 대상 삭제 --> 대상자료 소스파일로 이동
    free(((UserData*)(pDelete->pUserData))->name);
    free(((UserData*)(pDelete->pUserData))->phoneNumber);
    ((UserData*)(pDelete->pUserData))->name = NULL;
    ((UserData*)(pDelete->pUserData))->phoneNumber = NULL;

    free(pDelete->pUserData);
    pDelete->pUserData = NULL;
    */

    //UserDataNode 내의 pUserData 동적할당 부분 삭제
    //DeleteUserData((UserData*)(pDelete->pUserData));
    DeleteUserData(pDelete->pUserData);    //=> 자동 형변환?

    free(pDelete);
    pDelete = NULL;

    --g_nNodeCount;
    return SUCCESS;
}

//5_1. 특정 Key를 갖는 Node를 삭제하는 함수
const int DeleteNode_UsingKey(const char *name)
{
    UserDataNode *pDelete = SearchNode_UsingKey(name);

    //검색 결과에 대한 유효성 검사
    if(pDelete == NULL)
    {
        return FAIL;            // 해당 함수 사용자가 FAIL 리턴에 대한 처리 고려
    }

    //삭제 대상 Node의 앞/뒤 연결
    pDelete->pnPrev->pnNext = pDelete->pnNext;
    pDelete->pnNext->pnPrev = pDelete->pnPrev;

    //삭제 대상 Node 삭제
    //=> C++사용하면 그냥 friend 선언으로 접근하는 방법도 있을탠데..
    // 그냥 UserData class의 Delete 함수 사용
    //  UserData class의 해당 DeleteUserData 내용만 바뀌는거면 의존성 상관 없지 않나?
    DeleteUserData(pDelete->pUserData);

    free(pDelete);
    pDelete = NULL;

 //   free((pDelete->pGetKey)(pDelete->pUserData));         //=> const *는 경고??
    --g_nNodeCount;
    return SUCCESS;
}

//6. 특정 Node 검색 함수
//=> Head -> Tail 방향으로 검색
UserDataNode* SearchNode(UserData *pParam)
{
    //검색 대상 : from g_pHead->pnNext to g_pTail->pnPrev
    UserDataNode *pSearch = g_pHead->pnNext;

    while(pSearch != g_pTail)
    {
        if(SearchUserdata(pSearch->pUserData, pParam) == SUCCESS)
        {
            return pSearch;
        }

        pSearch = pSearch->pnNext;
    }

    return NULL;
}

//6_1. 특정 Node를 key(이름)으로 검색하는 함수
UserDataNode* SearchNode_UsingKey(const char *name)
{
    if(name == NULL)
    {
        return NULL;
    }

    //검색 대상 Node
    /*
    UserDataNode *pSearch = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pSearch, 0, sizeof(*pSearch));
    */
    //UserDataNode *pSearch = g_pTail->pnNext;
    UserDataNode *pSearch = g_pHead->pnNext;

    while(pSearch != g_pTail)
    {
        if(strncmp((pSearch->pGetKey)(pSearch->pUserData),
                   name,
                   strlen(pSearch->pGetKey(pSearch->pUserData))) == 0)
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
//    char const *pName = ((UserData*)(pPrint->pUserData))->name;
//    char const *pPhoneNumber = ((UserData*)(pPrint->pUserData))->phoneNumber;


    while(pPrint != g_pTail)
    {
        printf("prev[%p] [%p], next[%p]\n", pPrint->pnPrev, pPrint, pPrint->pnNext);
        PrintUserData(pPrint->pUserData);
        //=> pPrint->pGetKey(pUserData); 로 출력도 가능


        pPrint = pPrint->pnNext;
    }
}

//10. 특정 index에 Node 삽입
//=> 입력받은 index >= nNodeCount  --> 마지막 Node에 append
//=> 입력받은 index < nNodeCount && 입력받은 index >= 0 --> 해당 index에 위치한 Node의 Head 방향에 Insert
//=> 입력받은 index < 0 --> ERROR
const int InsertAtIdx(const int idx, UserData *pParam)
{
    //입력받은 index < 0 --> ERROR
    if(idx < 0)
    {
        return ERROR;
    }

    //=> 입력받은 index < nNodeCount && 입력받은 index >= 0 --> 해당 index에 위치한 Node의 Head 방향에 Insert
    //=> index가 존재하는 범위 내에서만 loop돌게 만듦
    else if(idx>=0 && idx < g_nNodeCount)
    {
        //삽입하려는 Index의 현재 Node
        UserDataNode *pCurNode = GetNodeAtIdx(idx);
        //pCurNode의 Head 방향에 입력받은 Data 저장한 새로운 Node Insert
        return InsertBefore(pCurNode, pParam);
    }

    //=> 입력받은 index >= nNodeCount  --> 마지막 Node에 append
    else
    {
        return InsertAtTail(pParam);
    }
}


//10_1. 특정 index에 Node 삽입
//=> UserData * --> void *
const int InsertAtIdx_UsingPf(const int idx, void *pParam,
                              const char * (*pfParam)(void *))
{
    //입력받은 index < 0 --> ERROR
    if(idx < 0)
    {
        return ERROR;
    }

        //=> 입력받은 index < nNodeCount && 입력받은 index >= 0 --> 해당 index에 위치한 Node의 Head 방향에 Insert
        //=> index가 존재하는 범위 내에서만 loop돌게 만듦
    else if(idx>=0 && idx < g_nNodeCount)
    {
        //삽입하려는 Index의 현재 Node
        UserDataNode *pCurNode = GetNodeAtIdx(idx);
        //pCurNode의 Head 방향에 입력받은 Data 저장한 새로운 Node Insert
        return InsertBefore_UsingPf(pCurNode, pParam, pfParam);
    }

        //=> 입력받은 index >= nNodeCount  --> 마지막 Node에 append
    else
    {
        return InsertAtTail_UsingPf(pParam, pfParam);
    }
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

//12. 특정 Node의 Head 방향(before)에 새로운 Node 생성 + Insert
const int InsertBefore(UserDataNode *pCurNode, UserData *pParam)
{

    //pCurNode 위치에 삽입하려는 새로운 Node
    UserDataNode *pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pNode, 0, sizeof(UserDataNode));
    pNode->pUserData = pParam;
    /*
    //1. 새로 생성한 Node에 입력받은 Data 저장
    AddData(pNode, name, phoneNumber);
    */
    //2. pCurNode의 Head 방향에 pNode Insert
    pNode->pnNext = pCurNode;
    pNode->pnPrev = pCurNode->pnPrev;

    //순서주의 : pCurNode->pnPrev 수정 전에 pCurNode->pnPrev->pnNext에 접근
    pCurNode->pnPrev->pnNext = pNode;
    pCurNode->pnPrev = pNode;

    //Insert/Delete 후 반드시 전역 Node counting 변수 수정
    ++g_nNodeCount;
    return SUCCESS;
}

//12_1. 특정 Node의 Head 방향(before)에 새로운 Node 생성 + Insert
//=> GetKey에 대한 함수 포인터 member를 사용하여
// UserData (class)와의 의존성 없앤 함수
const int InsertBefore_UsingPf(UserDataNode *pCurNode, void *pParam,
                               const char * (*pfParam)(void *))
{
    if(pCurNode == NULL || pParam == NULL || pfParam == NULL)
    {
        return ERROR;
    }

    //pCurNode 위치에 삽입하려는 새로운 Node
    //+ pUserData, pGetKey member 초기화
    UserDataNode *pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pNode, 0, sizeof(UserDataNode));

    //1. 관리 대상 자료애 대한 초기화
    pNode->pUserData = pParam;
    pNode->pGetKey = pfParam;

    //2. pCurNode의 Head 방향에 pNode Insert
    pNode->pnNext = pCurNode;
    pNode->pnPrev = pCurNode->pnPrev;

    //순서주의 : pCurNode->pnPrev 수정 전에 pCurNode->pnPrev->pnNext에 접근
    pCurNode->pnPrev->pnNext = pNode;
    pCurNode->pnPrev = pNode;

    //Insert/Delete 후 반드시 전역 Node counting 변수 수정
    ++g_nNodeCount;
    return SUCCESS;

}

/*
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
*/

