//
// Created by KHANG JU CHOI on 2023/02/21.
//
#ifndef ADDRESSBOOK_C_DS_DOUBLELINKEDLIST_H
#define ADDRESSBOOK_C_DS_DOUBLELINKEDLIST_H
#include<stdio.h>
#include<stdlib.h>
#include "InputData.h"
enum
{
    FAIL = 0,
    YES = 1,
    ERROR = 2,
    SUCCESS = 3
};

//Node 제작 - 관리 구조 체계1(저장할 Data네 대한 저장 틀)
typedef struct UserDataNode
{
    //관리 대상 Data
    //=> UserData 구조체를 포인팅 해야 한다
    //struct UserData strData;
    void *pUserData;

    // 자료구조
    // Data 관리(구조) 체계이다 == Data 관리를 위한 포인터
    struct UserDataNode *pnNext;
    struct UserDataNode *pnPrev;
} UserDataNode;

//자료구조-2
//전체 연결 리스트 관리하는 포인터 변수
UserDataNode *g_pHead;          //Head Node를 가리키는 포인터
UserDataNode *g_pTail;          //Tail Node를 가리키는 포인터
int g_nNodeCount;                 //Node 개수 counting 변수


//////////////////////Double Linked List////////////////////
//1. 모든 Node 초기화 함수
//=> 필요한가??
void InitList();

//2. Head 방향으로 새로운 Node Insert
const int InsertAtHead(UserData *);

//3. Tail 방향으로 새로운 Node Insert
const int InsertAtTail(UserData *);

//4. 모든 Node 할당해제(삭제) 함수
const int ReleaseList();

//5. 특정 Node 삭제 함수
const int DeleteNode(UserDataNode*);

//6. 특정 Node 검색 함수
UserDataNode* SearchNode(UserData *);

//7. List내 Node 개수 리턴(Head/Tail Dummy 제외)
static inline const int GetSize()
{
    return g_nNodeCount;
}

//8. 전체 List 출력 함수
void PrintAllList();

//9. 초기화 리셋 함수
static inline void DeInitList()
{
    free(g_pHead);
    free(g_pTail);

    g_pHead = NULL;
    g_pTail = NULL;

    g_nNodeCount = 0;

    printf("DeInitList\n");

}

//10. 특정 index에 Node 삽입
//=> 입력받은 index >= nNodeCount  --> 마지막 Node에 append
//=> 입력받은 index < nNodeCount && 입력받은 index >= 0 --> 해당 index에 위치한 Node의 Head 방향에 Insert
//=> 입력받은 index < 0 --> ERROR
const int InsertAtIdx(const int, UserData *);

//11. 특정 index의 Node 검색 + 주소 리턴
UserDataNode * GetNodeAtIdx(const int);

//12. 특정 Node의 Head 방향(before)에 새로운 Node 생성 + Insert
const int InsertBefore(UserDataNode *curNode, UserData *);

/* => 해당 Index에 새로운 Node를 넣으면 기존 Node는 Tail 방향으로 밀어져야 함
//12. 특정 Node의 Head 방향으로 새로운 Node Insert
void InsertAtHead_Of_Node(UserDataNode *, UserDataNode *);

//13. 특정 Node의 Tail 방향으로 새로운 Node Insert
void InsertAtTail_Of_Node(UserDataNode *, UserDataNode *);
*/
/*
//+) 리스트 비어있는지 확인
const int IsEmpty();
*/
/*
//+) Node에 동적할당 하여 name, phoneNumber 저장하는 함수
//=> Add Data to Node by Deep copy
void AddData(UserDataNode*, const char *, const char *);
*/
#endif