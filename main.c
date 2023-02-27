#include <stdio.h>
//#include<stdlib.h>
#include<string.h>
#include"Model/UserData.h"
#include"View/UserInterface.h"
#define NUM_OF_STRING_ITEMS 2
#define SIZE_OF_TEMP_BUFFER 100

int main()
{
    FILE* const fp = stdin;
    char aryTemp[SIZE_OF_TEMP_BUFFER] = {};
    char* aryBuffer[NUM_OF_STRING_ITEMS] = {};

    // command + D --> 종료
    while(getchar() != -1)
    {
        CleanStdinBuffer();

        printf("이름을 입력하시오 : ");
        fgets(aryTemp, SIZE_OF_TEMP_BUFFER, fp);
        aryBuffer[0] = aryTemp;

        //fgets()로 입력받은 문자배열에서 '\n'제거
//        (*aryBuffer)[strlen(*aryBuffer)-1] = '\0';
        *(*aryBuffer + (strlen(*aryBuffer) - 1)) = '\0';

        printf("전화번호를 입력하시오 : ");
        fgets(aryTemp + (strlen(*aryBuffer) + 1),
              SIZE_OF_TEMP_BUFFER, fp);
        aryBuffer[1] = aryTemp + (strlen(aryTemp) + 1); //배열의 길이로 배열의 특정 위치 구하기

        //fgets()로 입력받은 문자배열에서 '\n'제거
//        (*(aryBuffer+1))[strlen(*(aryBuffer+1))-1] = '\0';
        *(*(aryBuffer+1) + (strlen(*(aryBuffer+1))-1)) = '\0';

        //연결 리스트 테스트 Code
        InsertNewNode_first(aryBuffer);
    }


    PrintAllList();
    ReleaseAllList();


}
