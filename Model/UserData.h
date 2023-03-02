//
// Created by KHANG JU CHOI on 2023/02/21.
//
#ifndef ADDRESSBOOK_C_USERDATA_H
#define ADDRESSBOOK_C_USERDATA_H

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


//전체 연결 리스트 관리하는 포인터 변수
//=> 주의: 항상 1st Node를 가리켜야함
//UserDataNode* g_pHead;

//전체 연결 리스트 관리하는 Dummy head Node
UserDataNode g_DummyNode;

/////////////////Single Linked List/////////////////////////
// 연결 리스트 테스트 Code - 관리 Code
//1. 전체 List 출력 함수
void PrintAllList();

//2. 새로운 Node 추가 함수 - At Head
const int InsertNewNode_Head(const char*, const char*);

//2_1. 새로운 Node 추가 함수 - At Tail
const int InsertNewNode_Tail(const char*, const char*);


//3. 전체 List 삭제 함수
void ReleaseAllList();

//3_1.특정 Node 검색 함수 for 삭제
UserDataNode* SearchNode(const char *, const char *);

//3_2. 특정 Node 삭제 함수
const int DeleteNode(const char *, const char *);


//4. 전체 비어있는 Node인지 확인(Dummy Node가 NULL 포인팅 하는지)
const int IsEmpty();

//5. 마지막(Tail) Node의 주소 return
UserDataNode* SearchTail();

//6. Node에 동적할당 하여 name, phoneNumber 저장하는 함수
//=> Add Data to Node by Deep copy
void AddData(UserDataNode*, const char *, const char *);

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