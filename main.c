#include <stdio.h>
//#include<stdlib.h>
//#include<string.h>
#include"Model/DS_DoubleLinkedList.h"
#include"View/UserInterface.h"
#include"Model/InputData.h"
//#define N 6
#define NUM_OF_STRING_ITEMS 2
#define SIZE_OF_TEMP_BUFFER 100

int main()
{
    int nMenu;
    //FILE* const fp = stdin;
    char aryTemp[SIZE_OF_TEMP_BUFFER] = {};
    char* aryBuffer[NUM_OF_STRING_ITEMS] = {};
    InitList();

    while(1)
    {
        printf("원하는 기능을 선택하시오 : ");
        scanf("%d", &nMenu);
        CleanStdinBuffer();

        if(nMenu == -1) { break; }

        switch(nMenu)
        {
            case 1:
                //Data 입력받기 - InsertAtHead
                InputInterface_strData(aryTemp, aryBuffer, sizeof(aryTemp));
                InsertAtHead(MakeUserData(*aryBuffer, *(aryBuffer+1)));
                break;


            case 2:
                //특정 Data 삭제하기 - DeleteNode
                InputInterface_strData(aryTemp, aryBuffer, sizeof(aryTemp));
                DeleteNode(SearchNode(MakeUserData(*aryBuffer, *(aryBuffer+1))));
                break;

            case 3:
                //전채 List 삭제하기 - ReleaseAllList
                ReleaseList();
                break;

            case 4:
                //전체 List 출력하기
                PrintAllList();
                break;

            case 5:
                //Data 입력받기 - InsertAtTail
                InputInterface_strData(aryTemp, aryBuffer, sizeof(aryTemp));
                InsertAtTail(MakeUserData(*aryBuffer, *(aryBuffer+1)));
                break;

            case 6:
                //전체 Node 개수 출력
                printf("전체 Node 개수(Head/Tail)제외 : %d\n", GetSize());
                break;

            case 7:
                //특정 Index에 Node Insert
                {
                    int idx;
                    InputInterface_index(&idx);
                    InputInterface_strData(aryTemp, aryBuffer, sizeof(aryTemp));

                    InsertAtIdx(idx, MakeUserData(*aryBuffer, *(aryBuffer+1)));
                }
                break;

        ///////////////////Data와의 의존성 없앤 DS class의 함수 사용

            case 8:
                //특정 Node에 대해 name으로 검색해서 삭제
                InputInterface_strData(aryTemp, aryBuffer, sizeof(aryTemp));
                DeleteNode_UsingKey(*aryBuffer);
                break;

            case 9:
                //입력받은 Data Head뒤에 Node 생성 후Insert
                InputInterface_strData(aryTemp, aryBuffer, sizeof(aryTemp));
                InsertAtHead_UsingPf(MakeUserData(*aryBuffer, *(aryBuffer+1)));
                break;

            case 10:
            //특정 Index에 Node Insert
            {
                int idx;
                InputInterface_index(&idx);
                InputInterface_strData(aryTemp, aryBuffer, sizeof(aryTemp));

                InsertAtIdx_UsingPf(idx,
                                    MakeUserData(*aryBuffer, *(aryBuffer+1)));
            }
            break;

            case 11:
                //입력받은 Data Tail 앞에 Node 생성 후Insert
                InputInterface_strData(aryTemp, aryBuffer, sizeof(aryTemp));
                InsertAtTail_UsingPf(MakeUserData(*aryBuffer, *(aryBuffer+1)));
                break;

            default:
                break;

        }
    }

    DeInitList();
}
