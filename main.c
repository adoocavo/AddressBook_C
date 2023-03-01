#include <stdio.h>
#include<stdlib.h>
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
                InsertNewNode_Head(*aryBuffer, *(aryBuffer+1));
                break;


            case 2:
                //특정 Data 삭제하기 - DeleteNode
                InputInterface(aryTemp, aryBuffer, sizeof(aryTemp));
                DeleteNode(*aryBuffer, *(aryBuffer+1));
                break;

            case 3:
                //전채 List 삭제하기 - ReleaseAllList
                ReleaseAllList();
                break;

            case 4:
                //전체 List 출력하기
                PrintAllList();
                break;

            case 5:
                //Data 입력받기 - InsertNewNode_Tail
                InputInterface(aryTemp, aryBuffer, sizeof(aryTemp));
                InsertNewNode_Tail(*aryBuffer, *(aryBuffer+1));
                break;

            case 6:
                //Stack을 Linked List로 구현
                //Data 입력받기 - PushData
                InputInterface(aryTemp, aryBuffer, sizeof(aryTemp));
                PushData(*aryBuffer, *(aryBuffer+1));
                break;

            case 7:
                //Stack을 Linked List로 구현
                //Data 빼내기 - PopData
                //popTemp 포안터 동적할당 해제
                //=> 내부 기능 함수(PopData)에서 동적할당 한걸 인터페이스에서 해제하는게 좋은 code인가?

                {
                    UserDataNode *popNode = (UserDataNode*)malloc(sizeof(UserDataNode));;
                    PopData(popNode);

                    printf("%s\n", popNode->strData.name);
                    printf("%s\n", popNode->strData.phoneNumber);

                    free(popNode);
                }
                break;


            default:
                break;

        }
    }

}
