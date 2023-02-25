#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Model/UserData.h"
#include"View/UserInterface.h"
#define N 5
#define NUM_OF_ITEMS 2
#define SIZE_OF_TEMP_BUFFER 100
void PrintAllData();


int main()
{

/*
    //FILE* fp = stdin;
    //printf("%ld\n", sizeof(UserDataNode));
    //printf("%ld\n", sizeof(wchar_t));
*/
     UserDataNode* pHead = NULL;

/*
    //UserDataNode type을 요소로 갖는 length 5 배열
    //=> UserDataNode를 배열로 관리
    UserDataNode list[N] = {};
*/
    //연결 리스트 구조화
    // 배열의 요소들을 Linked List로 만듦
    //=> Linked List로 Data 나열
    int i;
    for(i = 0; i < N-1; ++i)
    {
        list[i].pnNext = &list[i+1];
    }
    list[N-1].pnNext = NULL;


    //UserDataNode에 User Data 저장
    char* aryBuffer[NUM_OF_ITEMS] = {};
    unsigned long aryLength[NUM_OF_ITEMS] = {};
    char aryTemp[SIZE_OF_TEMP_BUFFER] = {};

    // 이름/번호 입력받기
    for(i=0; i<N; ++i)
    {
        //입력받은 한글/영어 문자열 길이? 크기 구분해서 44line오류 고치기

        //이름 입력받기
        printf("이름을 입력하시오 : ");
        fgets(aryTemp, SIZE_OF_TEMP_BUFFER, stdin);
        aryBuffer[0] = aryTemp;
        aryLength[0] = strlen(*aryBuffer);
        //aryLength[0] = GetByteOfAry(*aryBuffer);

        //전화번호 입력받기
        printf("전화번호를 입력하시오 : ");
        fgets(aryTemp+(aryLength[0]+1), SIZE_OF_TEMP_BUFFER, stdin);
        //fgets(aryTemp, SIZE_OF_TEMP_BUFFER, stdin);
        aryBuffer[1] = aryTemp+(aryLength[0]+1);
        aryLength[1] = strlen(*(aryBuffer+1));
        //aryLength[1] = GetByteOfAry(*(aryBuffer+1));

        //버퍼에 남은 찌꺼기 비우기
        //CleanStdinBuffer();

        //입력받은 크기만큼 동적할당 + copy
        AddData(list+i, aryBuffer, aryLength);
        /* => 함수로 작성
        list[i].strData.name = (char *) malloc(nLength + 1);
        strncmp(list[i].strData.name, chTemp, nLength + 1);
        */
    }

    // 저장된 이름/번호 출력하기
    //=> 포인터의 관계를 이용한 Node 접근
    //=> 연결 리스트의 연결 구조가 바뀌면 리스트 순서가 바뀐다
    UserDataNode* pTemp = list;
    while(pTemp != NULL)
    {
        /*
        // 값으로 접근
        printf("%s", (*pTemp).strData.name);
        printf("%s", (*pTemp).strData.phoneNumber);

        pTemp = (*pTemp).pnNext;
        */
        //주소로 접근 --> pTemp가 아닌 pTemp의 값이 연산에 참여
        printf("%p : %s", pTemp, pTemp->strData.name);
        printf("%p : %s", pTemp, pTemp->strData.phoneNumber);

        pTemp = pTemp->pnNext;          //단일 연결리스트스러운 code
    }


}
