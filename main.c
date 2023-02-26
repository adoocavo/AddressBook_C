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

    // ctrl+D --> 종료
    while(getchar() != EOF)
    {
        CleanStdinBuffer();

        printf("이름을 입력하시오 : ");
        fgets(aryTemp, SIZE_OF_TEMP_BUFFER, fp);
        aryBuffer[0] = aryTemp;

        printf("전화번호를 입력하시오 : ");
        fgets(aryTemp + (strlen(*aryBuffer) + 1),
              SIZE_OF_TEMP_BUFFER, fp);
        aryBuffer[1] = aryTemp + (strlen(*aryBuffer) + 1);

        //연결 리스트 테스트 Code
        InsertNewNode_first(aryBuffer);
    }


    PrintAllList();


}
