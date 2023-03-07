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
    //=> void*로 인한 사용의 어려움 --> C++에서 템플릿으로 해결 가능
    //struct UserData strData;
    UserData *pUserData;
/*
    //위의 관리 대상 Data에 대한 pointer 변수(위의 pUserData)를 param으로 하고,
    // 관리 대상 Data의 member 중 name을 retuern 하는
    // 관리 대상 Data의 맴버함수를 pointing 하는 함수 pointer 생성
    //=> InputData.c의 GetKey() 함수를 가리켜야 함
    //=>List에 Insert 할 Node 생성시에 UserData class의
    //key return 함수(GetKey)로 초기화 해야함!
    const char* (*pGetKey)(void*);
*/
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

//2_1. Head 방향으로 새로운 Node Insert
//=> GetKey에 대한 함수 포인터 member를 사용하여
// UserData (class)와의 의존성 없앤 함수
const int InsertAtHead_UsingPf(void *);

//3. Tail 방향으로 새로운 Node Insert
const int InsertAtTail(UserData *);

//3_1 Tail 방향으로 새로운 Node Insert
//=> GetKey에 대한 함수 포인터 member를 사용하여
// UserData (class)와의 의존성 없앤 함수
const int InsertAtTail_UsingPf(void *);

//4. 모든 Node 할당해제(삭제) 함수
const int ReleaseList();

//5. 특정 Node 삭제 함수
const int DeleteNode(UserDataNode*);

//5_1. 특정 Key를 갖는 Node를 삭제하는 함수
const int DeleteNode_UsingKey(const char*);

//6. 특정 Node 검색 함수
UserDataNode* SearchNode(UserData *);

//6_1. 특정 Node를 key(이름)으로 검색하는 함수
UserDataNode* SearchNode_UsingKey(const char*);

//6_2 특정 Node 검색 함수 by Using Getter


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


//10_1. 특정 index에 Node 삽입
//=> UserData * --> void *
//=> 함수 포인터 param으로 받기 --> for Insert
const int InsertAtIdx_UsingPf(const int, void *);


//11. 특정 index의 Node 검색 + 주소 리턴
UserDataNode * GetNodeAtIdx(const int);

//12. 특정 Node의 Head 방향(before)에 새로운 Node 생성 + Insert
const int InsertBefore(UserDataNode *curNode, UserData *);

//12_1. 특정 Node의 Head 방향(before)에 새로운 Node 생성 + Insert
//=> GetKey에 대한 함수 포인터 member를 사용하여
// UserData (class)와의 의존성 없앤 함수
const int InsertBefore_UsingPf(UserDataNode *, void *);

//13. 동적할당을 통한 특정 Node 생성
// => 이미 생성된 관리대상 Data 구조체에 대한 포인터를 param으로 받음
UserDataNode * CreateNewNode(void *);



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