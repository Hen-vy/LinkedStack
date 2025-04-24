/********************************************
* File Name : LinkedStack
*
* Function  : None
* Argument  : None
* Retval    : None
*
* Author    : Hrolf
* Data      : 4/9/2025
* Note      : None
*
* CopyRight (c)      Hrolf     All Right Reseverd
* @param c
* @return
*
* *****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//元素表数据类型用户可以根据实际修改
typedef int  DataType_t;

//结构体定义各项参数 链栈 数据 下一个元素
typedef struct LinkedStack
{
    DataType_t          Data; //节点数据域
    struct LinkedStack  *next; //节点指针域

}LStack_t;



//创建链头，也就是栈的底部指针
LStack_t * LStack_Create(void)
{
    //1创建头节点，并且申请一个栈内存
    LStack_t *Head = (LStack_t *)calloc(1, sizeof(LStack_t));
    if (NULL == Head){
        perror("Failure to calloc memory for Head");
        exit(-2);
    }
    //2成功申请，保证指针指向有效元素
    Head->next = NULL;
    //3返回头节点地址
    return Head;
}



//创建新的节点，并且初始化
LStack_t * LList_NewNode(DataType_t data)
{
    //1创建新节点，并且申请一个栈内存
    LStack_t *New = (LStack_t *)calloc(1, sizeof(LStack_t));
    if (NULL == New) {
        perror("Failure to calloc memory for Head");
        return NULL;
    }

    //2对新节点的数据与和指针域进行初始化
    New->Data = data;
    New->next = NULL;

    return New;

}



//入栈  从链尾部
bool LStack_Push(LStack_t *Head, DataType_t data)
{
    //1备份头节点
    LStack_t *PHead = Head;
    //2创建新的节点
    LStack_t *New = LList_NewNode(data);
    if (NULL == New){
        printf("Cannot Insert New Node\n");
        return false;
    }
    //3判断栈是否为空,空则直接插入
    if (NULL == PHead->next){
        PHead->next = New;
        return true;
    }
    //4非空,先遍历到尾节点，再让尾节点指向新节点，再让新结点指向NULL
    while (PHead->next){
        PHead = PHead->next;
    }
    PHead->next = New;
    return true;
}



//出栈 链的尾删
DataType_t LStack_Pop (LStack_t *Head )
{
    DataType_t temp = 0;
    //1判断栈是否为空，空直接退出
    if ( Head->next == NULL ){
        printf("The LinkedStack is NULL\n");
        return false;
    }
    //2备份头节点
    LStack_t *PHead = Head;
    //3创建新节点，来备份尾节点前一个结点
    LStack_t *FTail = NULL;
    while ( PHead->next ){
        FTail = PHead;
        PHead = PHead->next;
    }
    //4首先让尾节点前一个节点指向NULL，再释放尾节点
    FTail->next = NULL;
    temp = PHead->Data;
    PHead->next = NULL;
    free(PHead);
    return temp;
}


//遍历,输出 单链只能从头部输出
void LList_Print(LStack_t * Head)
{

    //1对头节点进行备份
    LStack_t *PHead= Head;
    while (PHead->next != NULL){
        //把当前节点的直接后继作为新节点的直接后继
        PHead=PHead->next;
        //输出当前节点数据域
        printf(" %d",PHead->Data);
    }
    printf("\n");
}



int main(void)
{
    printf("/********/\n");
    printf("Create An Linked Stack\n");
    LStack_t * Head = LStack_Create();

    //1判断Head是否为空，NULL则返回
    if (Head == NULL){
        perror("Memory allocation is failed\n");
        return -2;
    }

    //3插入元素 尾插法
    printf("******Push Stack\n");
    LStack_Push(Head, 1);
    LStack_Push(Head, 411);
    LStack_Push(Head, 211);
    LStack_Push(Head, 0);
    LStack_Push(Head, 511);
    LStack_Push(Head, 6);
    LStack_Push(Head, 85);
    LStack_Push(Head, 0);
    //输出元素 0 85 6 511 0 211 411 1
    printf("******Expecting Order:0 85 6 511 0 211 411 1\n");
    printf("******But It is Hard To For Single Stack To Push Stack Expecting Order:1 411 211 0 511 6 85 0\n");
    LList_Print(Head);
    printf("\n");


    printf("******Pop Stack\n");
    LStack_Pop(Head);
    printf("******Expecting Order:85 6 511 0 211 411 1\n");
    printf("******But It is Hard To For Single Stack To Push Stack Expecting Order:1 411 211 0 511 6 85\n");
    LList_Print(Head);
    LStack_Pop(Head);
    printf("******Expecting Order:6 511 0 211 411 1\n");
    printf("******But It is Hard To For Single Stack To Push Stack Expecting Order:1 411 211 0 511 6\n");
    LList_Print(Head);
    LStack_Pop(Head);
    printf("******Expecting Order:511 0 211 411 1\n");
    printf("******But It is Hard To For Single Stack To Push Stack Expecting Order:1 411 211 0 511\n");
    LList_Print(Head);
    LStack_Pop(Head);
    LStack_Pop(Head);
    LStack_Pop(Head);
    LStack_Pop(Head);
    LStack_Pop(Head);
    printf("******Excepting Output: The Linked Stack Is Empty\\NULL\n");
    LStack_Pop(Head);

    printf("\n");
    printf("Hello, World!\n");


    return 100;
}

