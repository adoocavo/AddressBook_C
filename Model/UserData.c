//
// Created by KHANG JU CHOI on 2023/02/25.
//

#include"UserData.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//extern UserDataNode* g_pHead;
//extern UserDataNode g_DummyNode;  //=> Node type 자체로 선언 or 포인터로 선언 후 동적할당


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
const int InsertNewNode_Head(const char* name, const char* phoneNumber)
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
    if(name == NULL || phoneNumber == NULL)
    {
        return 0;
    }

    //1. Node 생성 + 입략받은 Data 저장
    UserDataNode* pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pNode, 0, sizeof(UserDataNode));
    AddData(pNode, name, phoneNumber);

    //2. Node 저장할 위치 검색
    //if(g_pHead == NULL)              //Using pHead
    //if(g_DummyNode.pnNext == NULL)   //Using Dummy Node
    if(IsEmpty() == 1)
    {
        //Using Dummy Node
        g_DummyNode.pnNext = pNode;
        //AddData(pNode, pszParam);
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
        //AddData(pNode, pszParam);
        /*
        //Using pHead
        pNode->pnNext = g_pHead;
        g_pHead = pNode;
        AddData(pNode, pszParam);
        */
     }

    return 1;
}

//2_1. 새로운 Node 추가 함수
//=> Tail Node로 삽입
// return 1: 성공, return 0: 실패
const int InsertNewNode_Tail(const char *name, const char *phoneNumber)
{
    //param 유효성 검사
    if(name == NULL || phoneNumber == NULL)
    {
        return 0;
    }

    //Node 생성 + 입력받은 Data 저장
    UserDataNode *pNode = (UserDataNode*)malloc(sizeof(UserDataNode));
    memset(pNode, 0, sizeof(UserDataNode));
    UserDataNode *pSearch = NULL;               //Tail Node 위치 저장
    AddData(pNode, name, phoneNumber);

    //branch1 - Dummy Node가 NULL 포인팅
    //=> 입력받은 Data를 Dummy Node 다음 위치에 추가
    if(IsEmpty() == 1)
    {
        g_DummyNode.pnNext = pNode;
        //AddData(pNode, pszParam);
    }

    //branch2 - List가 비어있지 않은 상태
    //=> 입력받은 Data를 Tail Node 다음 위치에 추가
    else
    {
        //Tail Node 주소 찾기
        pSearch = SearchTail();

        //Tail Node 다음 위치에 Node 추가
        pSearch->pnNext = pNode;

        //새롭게 추가한 Node에 Data 저장
        //AddData(pNode, pszParam);
    }
    return 1;
}



//3. 전체 리스트 삭제 함수(동적할당 해제)
void ReleaseAllList()
{

    //Using DummyNode
    UserDataNode *pDelete = g_DummyNode.pnNext;         //삭제 대상 Node
    /*
    //Using pHead
    UserDataNode *pDelete = g_pHead;
    */
    UserDataNode *pTemp = NULL;                         //다음 삭제 대상 Node 임시저장

    while(pDelete != NULL)
    {
        printf("Delete : [%p] %s, next[%p]\n", pDelete, pDelete->strData.name, pDelete->pnNext);
        printf("Delete : [%p] %s, next[%p]\n", pDelete, pDelete->strData.phoneNumber, pDelete->pnNext);
        pTemp = pDelete->pnNext;

        free(pDelete->strData.name);
        free(pDelete->strData.phoneNumber);
        pDelete->strData.name = NULL;
        pDelete->strData.phoneNumber = NULL;

        free(pDelete);
        pDelete = pTemp;
    }
    //pDelete = NULL;                               //=> 마지막 Node까지 삭제하면 자동으로 NULL 저장됨

    //핵중요! : List의 모든 Node가 할당 해제 된 이루에 Dummy Head Node는 NULL을 가리켜야함!
    g_DummyNode.pnNext = NULL;
    //g_pHead = NULL;
}

//3_1. 특정 Node 검색 함수 for 삭제
//=> Dummy Node사용
//=> call back 되는 함수
//=> 찾고자 하는 대상 Node의 직전 Node 주소 return ()
UserDataNode* SearchNode(const char *name, const char *phoneNumber)
{
    UserDataNode *pSearch = &g_DummyNode;
    if(pSearch == NULL)
    {
        return NULL;
    }

    const unsigned long nLength_name = strlen(name);
    const unsigned long nLength_phoneNumber = strlen(phoneNumber);


    while (pSearch->pnNext != NULL)
    {
        if (strncmp(pSearch->pnNext->strData.name, name, nLength_name + 1) == 0
            && strncmp(pSearch->pnNext->strData.phoneNumber, phoneNumber, nLength_phoneNumber + 1) == 0)
        {
            return pSearch;
        }
        pSearch = pSearch->pnNext;
    }

    return NULL;
}

/*
//3_1. 특정 Node 검색 함수
//=> pHead 사용
//=> call back 되는 함수
UserDataNode* SearchNode(const char* *pszParam)
{
    UserDataNode *pSearch = g_pHead;     //Search 대상 Node
    UserDataNode *pTemp = pSearch;          //Search 대상 Node의 직전 Node

    if(pSearch == NULL)
    {
        return NULL;
    }

    const unsigned long nLength_name = strlen(*pszParam);
    const unsigned long nLength_phoneNumber = strlen(*(pszParam+1));


    while (pSearch != NULL)
    {
        if (strncmp(pSearch->strData.name, *pszParam, nLength_name + 1) == 0
            && strncmp(pSearch->strData.phoneNumber, *(pszParam + 1), nLength_phoneNumber + 1) == 0)
        {
            return pTemp;
        }

        pTemp = pSearch;
        pSearch = pSearch->pnNext;

    }

    return NULL;
}
*/

//3_2. 특정 Node 삭제 함수
//=> Dummy Node 사용
const int DeleteNode(const char *name, const char *phoneNumber)
{
    if(name == NULL || phoneNumber == NULL)
    {
        return 0;
    }

    UserDataNode *pSearch = SearchNode(name, phoneNumber);        //삭제 대상 Node의 앞쪽 Node 주소 return
    UserDataNode *pTarget = NULL;                        //삭제 대상 Node 주소 임시저장

    if(pSearch == NULL)
    {
        return 0;
    }

    //검색 결과로 받은 Node삭제
    //1. 삭제 대상 Node의 주소 임시 저장
    pTarget = pSearch->pnNext;

    //2. 삭제 대상 Node의 앞쪽 Node와 뒤쪽 Node 연결
    //=> 삭제 대상이 마지막 Node여도 g_DummyNode.pnNext에 NULL이 저장됨
    pSearch->pnNext = pSearch->pnNext->pnNext;

    //+) 삭제 Data 출력
    printf("Delete : [%p] %s, next[%p]\n", pTarget, pTarget->strData.name, pTarget->pnNext);
    printf("Delete : [%p] %s, next[%p]\n", pTarget, pTarget->strData.phoneNumber, pTarget->pnNext);

    //3. 삭제 대상 Node 삭제하기
    free(pTarget->strData.name);
    free(pTarget->strData.phoneNumber);
    pTarget->strData.name = NULL;
    pTarget->strData.phoneNumber = NULL;

    free(pTarget);
    pTarget = NULL;

    return 1;
}


/*
//3_2. 특정 Node 삭제 함수
//=> pHead 사용
const int DeleteNode(const char* *pszParam)
{
    if(pszParam == NULL)
    {
        return 0;
    }

    UserDataNode *pSearch = SearchNode(pszParam);    //삭제 대상 Node의 직전 Node
    UserDataNode *pTemp = NULL;                      //삭제 대상 Node 임시 저장

    if(pSearch == NULL)
    {
        return 0;
    }

    //branch1 맨 앞쪽 Node를 삭제하는 경우 - Node 검색 결과가 g_pHead가 가리키는 Node인 경우
    if(pSearch == g_pHead)
    {
        //1. 삭제 대상 Node 주소 임시 저장
        pTemp = pSearch;

        //2. 삭제 대상 Node의 앞쪽 Node(g_pHead)와 뒤쪽 Node 연결
        g_pHead = pTemp->pnNext;
    }

    //branch2 중간, 맨 끝 Node를 삭제하는 경우
    else
    {
        //검색 결과로 받은 Node삭제
        //1. 삭제 대상 Node의 주소 임시 저장
        pTemp = pSearch->pnNext;

        //2. 삭제 대상 Node의 앞쪽 Node와 뒤쪽 Node 연결
        pSearch->pnNext = pSearch->pnNext->pnNext;
    }

    //3. 삭제 대상 Node 삭제하기
    free(pTemp->strData.name);
    free(pTemp->strData.phoneNumber);
    pTemp->strData.name = NULL;
    pTemp->strData.phoneNumber = NULL;

    free(pTemp);
    pTemp = NULL;

    return 1;
}
*/

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

const int IsEmpty()
{
    //Dummy Node가 NULL을 포인팅 하는지 여부로 판단
    if(g_DummyNode.pnNext == NULL)
    {
        return 1;
    }
    return 0;
}

//Tail Node의 주소 return 함수
//Single Linked List의 비효율성이 나타나는 함수
//  => Tail Node를 찾기 위해 전체 Node의 개수만큼 loop 돈다
//      --> List 전체 크기가 증가할수록 탐색 시간 증가
//=> Tail Dummy Node 를 만들어서 역방향으로의 link도 생성 --> Double Linked List
UserDataNode* SearchTail()
{
    //새로운 Node를 연결시킬 직전 Node 검색(마지막 Node 검색)
    UserDataNode *pSearch = &g_DummyNode;

    //while(pSearch->pnNext == NULL)       //=> 실수 주의
    while(pSearch->pnNext != NULL)
    {
        pSearch = pSearch->pnNext;
    }

    return pSearch;
}


/////////////////Stack////////////////////////

//7. Linked List로 stack 구현 - push()
void PushData(const char *name, const char *phoneNumber)
{
    InsertNewNode_Head(name, phoneNumber);
}

//8.  Linked List로 stack 구현 - pop)
//=> param == pop 할 Node 임시 저장 for return
//=> top(Head) 위치의 Node 복사 + 삭제
const int PopData(UserDataNode *pTemp)
{
    if(IsEmpty() == 1)
    {
        printf("Error : Empty Stack\n");
        return 0;
    }

    UserDataNode *pDelete = g_DummyNode.pnNext;     //pop 할 Node 자장 for Delete
/*=> DeleteNode() 내부에서 중복되는 작업
    //1. 앞/뒤 연결작업
    g_DummyNode.pnNext = g_DummyNode.pnNext->pnNext;
*/
    //2. pTemp에 pop 할 Node 임시 저장(deep copy)
    AddData(pTemp, pDelete->strData.name, pDelete->strData.phoneNumber);

    //3. Node 삭제
    DeleteNode(pDelete->strData.name, pDelete->strData.phoneNumber);

    return 1;
}

/////////////////Queue////////////////////////
void Enqueue(const char *name, const char *phoneNumber)
{
    InsertNewNode_Tail(name, phoneNumber);
}

const int Dequeue(UserDataNode *pTemp)
{
   return PopData(pTemp);
}


