//
// Created by KHANG JU CHOI on 2023/02/21.
//
#ifndef ADDRESSBOOK_C_USERDATA_H
#define ADDRESSBOOK_C_USERDATA_H
#include<stdio.h>
enum
{
    NO = 0,
    YES = 1,
    ERROR = 2,
    SUCCESS = 3
};

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
    struct UserDataNode *pnNext;
    struct UserDataNode *pnPrev;
} UserDataNode;


//전체 연결 리스트 관리하는 포인터 변수
UserDataNode *g_pHead;          //Head Node를 가리키는 포인터
UserDataNode *g_pTail;          //Tail Node를 가리키는 포인터
int nNodeCount;                 //Node 개수 counting 변수


//////////////////////Double Linked List////////////////////
//1. 모든 Node 초기화 함수
//=> 필요한가??
void InitList();

//2. Head 방향으로 새로운 Node Insert
const int InsertAtHead(const char *, const char *);

//3. Tail 방향으로 새로운 Node Insert
const int InsertAtTail(const char *, const char *);

//4. 모든 Node 할당해제(삭제) 함수
const int ReleaseList();

//+) 리스트 비어있는지 확인
const int IsEmpty();

//+) Node에 동적할당 하여 name, phoneNumber 저장하는 함수
//=> Add Data to Node by Deep copy
void AddData(UserDataNode*, const char *, const char *);

//+) param 유효성 검사
static inline const int CheckParam(const char *name, const char *phoneNumber)
{
    if(name == NULL || phoneNumber == NULL )
    {
        return ERROR;
    }

    return SUCCESS;
}


/////////////////Single Linked List/////////////////////////
// 연결 리스트 테스트 Code - 관리 Code
//1. 전체 List 출력 함수
void PrintAllList();

//2. 새로운 Node 추가 함수 - At Head
const int InsertNewNode_Head(const char*, const char*);

//2_1. 새로운 Node 추가 함수 - At Tail
const int InsertNewNode_Tail(const char*, const char*);


//3. 전체 List 삭제 함수
//void ReleaseAllList();

//3_1.특정 Node 검색 함수 for 삭제
UserDataNode* SearchNode(const char *, const char *);

//3_2. 특정 Node 삭제 함수
const int DeleteNode(const char *, const char *);


//4. 전체 비어있는 Node인지 확인(Dummy Node가 NULL 포인팅 하는지)
const int IsEmpty();

//5. 마지막(Tail) Node의 주소 return
UserDataNode* SearchTail();

//////////Stack///////////////
//=> LIFO
//=> Stack 크기에 따른 pop/push 제한 기능도 필요

//7. Linked List로 stack 구현 - push()
void PushData(const char *, const char *);

//8.  Linked List로 stack 구현 - pop)
const int PopData(UserDataNode *);


/////////////////Queue////////////////////////
//=> FIFO

//9. Linked List로 Queue 구현 - Enqueue
void Enqueue(const char *, const char *);

//10. Linked List로 Queue 구현 - Dequeue
const int Dequeue(UserDataNode *);









#endif