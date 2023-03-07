//
// Created by KHANG JU CHOI on 2023/03/05.
//

#ifndef ADDRESSBOOK_C_INPUTDATA_H
#define ADDRESSBOOK_C_INPUTDATA_H
#include<stdio.h>
//#include "DS_DoubleLinkedList.h"
//#include<string.h>
//관리 대상 Data
//Node 제작 - Node에 저장할 Data
typedef struct UserData
{
    //관리될 Data
    char *name;
    char *phoneNumber;

    //UserData 구조체의 member name 혹은 phoneNumber를 key로 사용할 때
    //해당 key값을 리턴하는 함수에 대한 함수 포인터 member 변수
    const char* (*pfGetKey_name)(struct UserData*);
    const char* (*pfGetKey_phoneNumber)(struct UserData*);

} UserData;

//1. 입력받은 Data에 대해 UserData 구조체 동적할당 후 Insert/Delete
//함수에 Param으로 넘기기 --> 자료구조 - 자료 간 분리
//=> 리턴되는 주소를 pUserData가 포인팅 하게 만들기
UserData * MakeUserData(const char *, const char *);

//2. 특정 Node의 UserData 부분 삭제 함수
const int DeleteUserData(UserData *);

//3. 'Input Data - pUserData' 의 대조를 통해 특정 pUserData 찾아내기
const int SearchUserdata(UserData *, UserData *);

//4. 특정 Node의 pUserData에 저장된 Data 출력
static inline void PrintUserData(UserData *pUserData)
{
    printf("name : ");
    puts(pUserData->name);

    printf("phoneNumber : ");
    puts(pUserData->phoneNumber);
}

//5. UserData 구조체의 member 중 name을 key로 사용하는 GetKey()
// => 해당 함수를 포인팅하는 변수를 선언하고,
// 그 함수 포인터 변수를 통해 pUserData의 member data name에 접근할 수 있다
const char* GetKey_Name(UserData *);

//6. UserData 구조체의 member 중 phoneNumber를 key로 사용하는 GetKey()
// => 해당 함수를 포인팅하는 변수를 선언하고,
// 그 함수 포인터 변수를 통해 pUserData의 member data phoneNumber를 접근할 수 있다
const char* GetKey_phoneNumber(UserData *);

/*
//7.
static inline UserData * TypeOfUserData(void *pUserData)
{
    if(pUserData == NULL)
    {
        return NULL;
    }

    UserData *pCastUserData = (UserData *)pUserData;

    return pCastUserData;
}
*/

//+) param 유효성 검사
static inline const int CheckParam(const char *name, const char *phoneNumber)
{
    if(name == NULL || phoneNumber == NULL )
    {
        return 0;
    }

    return 1;
}

#endif //ADDRESSBOOK_C_INPUTDATA_H
