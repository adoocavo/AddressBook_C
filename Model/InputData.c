//
// Created by KHANG JU CHOI on 2023/03/05.
//

#include "InputData.h"
#include "DS_DoubleLinkedList.h"
#include<stdlib.h>
#include<string.h>
//1. 입력받은 Data에 대해 UserData 구조체 동적할당 후 Insert/Delete
//함수에 Param으로 넘기기 --> 자료구조 - 자료 간 분리
//=> 해당 함수의 caller 측에서 해당 함수의 리턴 주소를,
// 새롭게 생성하는 UserdataNode type Node의 pUserData 맴버가 가리키도록 제작하기
//=> 입력되는 Data의 type에 의존적
UserData * MakeUserData(const char *name, const char *phoneNumber)
{
    if(CheckParam(name, phoneNumber) == 0)
    {
        return NULL;
    }

    const unsigned long nLength_name = strlen(name);
    const unsigned long nLength_phoneNumber = strlen(phoneNumber);

    //입력받은 Data 저장(동적할당 --> 추후 UserDataNode의 pUserData가 포인텅)
    UserData *pUserData = (UserData*)malloc(sizeof(UserData));
    memset(pUserData, 0, sizeof(UserData));

    pUserData->name = (char*)malloc(nLength_name+1);
    pUserData->phoneNumber = (char*) malloc(nLength_phoneNumber+1);
    pUserData->pfGetKey_name = GetKey_Name;
    pUserData->pfGetKey_phoneNumber = GetKey_phoneNumber;

    strncpy(pUserData->name, name, nLength_name+1);
    strncpy(pUserData->phoneNumber, phoneNumber, nLength_phoneNumber+1);

    return pUserData;
}

//2. 특정 Node의 UserData 부분 삭제 함수
//param == pDelete->pUserData
const int DeleteUserData(UserData *pDelete)
{
    if(pDelete == NULL)
    {
        return ERROR;
    }

    //삭제 대상 출력
    printf("name : ");
    puts(pDelete->name);

    printf("phoneNumber : ");
    puts(pDelete->phoneNumber);

    //UserData의 member 중 동적할당 된 member들에 대해 free()
    free(pDelete->name);
    free(pDelete->phoneNumber);
    free(pDelete);
    pDelete = NULL;         //=> UserData의 member data가 모두 0으로 초기화됨

    return SUCCESS;
}

//3. Input Data - pUserData 와의 대조를 통해 특정 pUserData 찾아내기
const int SearchUserdata(UserData *pSearch, UserData *pUserData)
{
    if(pSearch == NULL || pUserData == NULL)
    {
        return ERROR;
    }

    if (    strncmp( pSearch->name,
                     pUserData->name,
                     strlen(pSearch->name) ) == 0
            &&
            strncmp( pSearch->phoneNumber,
                     pUserData->phoneNumber,
                     strlen(pSearch->phoneNumber) ) == 0
            )
    {
        return SUCCESS;
    }

    return FAIL;
}

//5. UserData 구조체의 member 중 name을 key로 사용하는 GetKey()
//=> 즉, DS관련 소스파일에서 해당 함수를 포인팅하여 DS 구조체에 저장된
// pUserData의 name, phoneNumber 정보에 접근할 수 있다
const char* GetKey_Name(UserData *pUserData)
{
    if(pUserData == NULL)
    {
        return NULL;
    }

    return pUserData->name;
}

//6. UserData 구조체의 member 중 phoneNumber를 key로 사용하는 GetKey()
// => 해당 함수를 포인팅하는 변수를 선언하고,
// 그 함수 포인터 변수를 통해 pUserData의 member data phoneNumber를 접근할 수 있다
const char* GetKey_phoneNumber(UserData *pUserData)
{
    if(pUserData == NULL)
    {
        return NULL;
    }

    return pUserData->phoneNumber;
}
