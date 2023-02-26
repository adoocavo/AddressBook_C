//
// Created by KHANG JU CHOI on 2023/02/21.
//
#pragma once

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
UserDataNode* g_pHead;

//Node에 동적할당 하여 name, phoneNumber 저장하는 함수
void AddData(UserDataNode*, const char**);


// 연결 리스트 테스트 Code - 관리 Code
//1. 전체 List 출력 함수
void PrintAllList();

//2. 새로운 Node 추가 함수
const int InsertNewNode_first(const char**);

//3. 전체 List 삭제 함수
void ReleaseAllList();

