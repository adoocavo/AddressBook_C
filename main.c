#include <stdio.h>
//#include<stdlib.h>
//#include<string.h>
#include"Model/UserData.h"
#include"View/UserInterface.h"
//#define N 6
#define NUM_OF_STRING_ITEMS 2
#define SIZE_OF_TEMP_BUFFER 100

int main()
{
    int nMenu;
    //FILE* const fp = stdin;
    char aryTemp[SIZE_OF_TEMP_BUFFER] = {};
    char* aryBuffer[NUM_OF_STRING_ITEMS] = {};

//    printf("%d\n", sizeof(aryTemp)/ sizeof(char));
//    printf("%d\n", sizeof(aryTemp)/ sizeof(char*));

    while(1)
    {
        printf("원하는 기능을 선택하시오 : ");
        scanf("%d", &nMenu);
        CleanStdinBuffer();

        if(nMenu == -1) { break; }

        switch(nMenu)
        {
            case 1:
                //Data 입력받기 - InsertNewNode_first
                InputInterface(aryTemp, aryBuffer, sizeof(aryTemp));
                InsertNewNode_first(aryBuffer);
                break;


            case 2:
                //특정 Data 삭제하기 - DeleteNode
                InputInterface(aryTemp, aryBuffer, sizeof(aryTemp));
                DeleteNode(aryBuffer);
                break;

            case 3:
                //전채 List 삭제하기 - ReleaseAllList
                ReleaseAllList();
                break;

            case 4:
                //전체 List 출력하기
                PrintAllList();
                break;

            default:
                break;

        }
    }

}
