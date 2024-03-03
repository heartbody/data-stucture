#include <stdio.h>
#include <stdlib.h>
//包括两个大部分：单链表操作和双向链表操作 【注：省略循环链表部分，循环链表就是再单链表基础上将最后一个结点指向第一个结点】
//inclusion：头结点的作用主要是：1.可以不用总是改变头指针的值，便于操作；2.可以储存链表信息。


//第一部分为单链表操作：包括创建、头插（删）、尾插（删），指定位置元素插入（删除）等操作（注：均表示成函数），以及在主函数中进行测试：
typedef  int ListDataType;


/*结构体定义，此后可以用ListNode定义结构体或者结构指针*/
typedef struct ListNode{
     ListDataType val;
     struct ListNode *next;
}ListNode;      
 


 //初始化链表
void ListInit(ListNode **phead) //phead为头指针的地址，此处使用因为需要改变头指针的值 【此外注：*phead=head（头指针指向的第一个结点的地址）,**phead=*head=结构体变量）】
{   //assert(phead);
    *phead=NULL;
}



//链表打印
void ListPrint(ListNode *head)//此处使用head（第一个结点的地址），是因为打印只需要遍历各个结构体元素，并不需要改变头指针
{   
ListNode *tra=head;
while(tra!=NULL){
    printf("%d ->",tra->val);
    tra=tra->next;
}
printf("NULL \n");
}


//创立结点
ListNode *Nodecreate(ListDataType val)
{   ListNode *newnode=(ListNode*)malloc(sizeof(ListNode));
    if(newnode==NULL) 
    {   printf("malloc fail\n");
    return NULL;
    }
    else
    {   newnode->val=val;
        newnode->next=NULL;
    }
    return newnode;
}


//尾插法插入结点  【注：因为链表可能为空，此时尾插会改变头指针的值，所以要引用头指针的地址phead】
void NodeCreateback(ListNode **phead,ListDataType val)
{   //assert(phead);
    ListNode *newnode=Nodecreate(val);
    if(*phead==NULL) //原链表为空
    {   *phead=newnode;
    }
    else 
    { ListNode *cur;
        cur=*phead;  

        #if(0)  //
        while(cur)
        //while(cur!=NULL)
        {   cur=cur->next;
        }
        cur=newnode;
       // cur->next=NULL;
        #endif

       #if(1)
       while(cur->next)
       { cur=cur->next;
       }
       cur->next=newnode;
       #endif
    }
}


//尾删法删除结点   【注：因为链表可能为空（不用删），可能只有一个结点（此时需要改变头指针的值），所以尾插可能会改变头指针的值，所以要引用头指针的地址phead】
void NodeDeleteback(ListNode **phead)
{   //assert(phead);
if(*phead==NULL) return; //链表本身就空

else if((*phead)->next==NULL)   //链表只有一个结点（此时需要改变头指针）
    {   free(*phead);
        *phead=NULL;
    } 
else 
{   ListNode *cur=*phead;
    
    #if(0)
    while(cur->next)
    {cur=cur->next;
    }
    free(cur);
    cur=NULL;
    #endif    /*错误原因：cur指向最后一个结点的时候才free，虽然最后一个结点的内存被释放，但是结点的地址并没有消失（变成NULL），只是将自己设置的cur指针变成了NULL，没有改变链表。
              （可以理解成原链表倒数第二个结点的next值并没有变成NULL）*/

    #if(1)
    while(cur->next->next)
    {   cur=cur->next;
    }
    free(cur->next);
    cur->next=NULL;
    #endif
}
}
 

 //头插法插入结点 【注：因为链表可能为空，此时头插需要改变头指针的值，故需要引用头指针地址phead】
 void NodeCreatehead(ListNode **phead,ListDataType val)
 {  //assert(phead);
    ListNode *newnode=Nodecreate(val);
    if(*phead==NULL) *phead=newnode; //原本空链表
    else 
    {ListNode *cur;
     cur=*phead;
     *phead=newnode;
     newnode->next=cur;
    }
    
 }


 //头删结点  【注：需要用到头指针地址phead】
 void NodeDeletehead(ListNode **phead)
 {  //assert(phead);
    if(*phead==NULL) printf("nothing to delete");
    else if((*phead)->next==NULL)
        {free(*phead);*phead=NULL;}
    else
    {   ListNode *next=(*phead)->next;
        free(*phead);
        *phead=next;
    }



    #if(0)
    { ListNode *cur=*phead;
     // ListNode *cur=(*phead)->next; //cur指向第二个结点
     free(*phead);
      *phead=(*phead)->next;
     // *phead=cur;    //头指针指向原链表的第二个结点
    }
    #endif
 }

 //删除链表
 void ListDelete(ListNode **phead)
{//assert(phead);
 ListNode *cur=*phead;
#if(0)
while(cur) //要先把其他指针都free后再free头指针
 {free(cur);
  cur=cur->next;
 }
 #endif
 #if(1)
 while(cur)
 {
 ListNode *next=cur->next;
 free(cur);
 cur=next;
 }
 #endif
 *phead=NULL;
 }



//求链表的结点数
  int NodeTra(ListNode *head)
  { ListNode *tra=head;
  int i=0;
    if(head==NULL)  return 0;
    else
    { while(tra) 
      { tra=tra->next;
        i=i+1;
      }
      return i;
    }
  }



 //删除任一结点
 void DeleteNode(ListNode **phead,int i)
{
    ListNode *pre,*r;
    int a=NodeTra(*phead);
    int k=0;
    if(*phead==NULL) 
    { printf("empty list\n");
    }
    else 
    { if(i<1||i>a) printf("delete unreasonable\n");
      else if(i==1) {pre=(*phead)->next; free(*phead);*phead=pre;ListPrint(*phead);}
      else
       { pre=*phead;
        //while(pre->next!=NULL&&k<i-2)
         while(k<i-2)
          { pre=pre->next;
            k=k+1;
          }
         r=pre->next->next;free(pre->next);pre->next=r;ListPrint(*phead);
        }
         
    }
    
}
        //if(pre->next==NULL) {free(pre);pre=NULL;}
       // else {r=pre->next->next;free(pre->next);pre->next=r;}
        #if(0)
        while(k<i-2)
        {   pre=pre->next;
             k=k+1;
        }
        #endif
    /* if(pre->next==NULL)
        r=pre->next;
        free(pre);
        pre=r;
     if(pre->next==NULL)
    {   
        return 0;
    }*/
    /*r=pre->next;
    pre->next=r->next;
    free(r);
    return 1;*/
    



//任意位置插入结点
void NodeInsert(ListNode **phead,ListDataType e,int i)
{ ListNode *cur,*exp,*a;
int k=0;
  cur=Nodecreate(e);
  if(*phead==NULL) *phead=cur;
  else if(i==1)
  { exp=*phead;*phead=cur;cur->next=exp;
  } 
  else 
  { exp=*phead;
    while(k<i-2)
    { exp=exp->next;
      k=k+1;
    }
    a=exp->next;
    exp->next=cur;
    cur->next=a;
 }
}



//合并两个有序递增链表（包括相等）成一个新的有序链表
ListNode* MergeOrderList(ListNode *L1,ListNode*L2)
//void MergeOrderList(ListNode *L1,ListNode*L2)
{ ListNode *guard=NULL;
  ListNode *tail=NULL;
  ListNode *cur1=L1;
  ListNode *cur2=L2;
  guard=tail=(ListNode*)malloc(sizeof(ListNode));
  if(guard==NULL) { perror("malloc");}
  else
  { while(cur1&&cur2)
     { if(cur1->val>cur2->val)
         { tail->next=cur2;
           tail=tail->next;
           cur2=cur2->next;
         }
       else
         { tail->next=cur1;
           tail=tail->next;
           cur1=cur1->next;
         }
     }
     if(cur1) tail->next=cur1;
     else tail->next=cur2; 
  }
  ListNode *uns=guard->next;
  free(guard);
  return uns;
}




#if(0)//测试链表操作功能：
 int main(){
    ListNode* head;
    ListInit(&head);
    /**
    NodeCreateback(&head,2);
    NodeCreateback(&head,4);
    NodeCreateback(&head,6);
    */
    NodeCreatehead(&head,2);
    NodeCreatehead(&head,4);
    NodeCreatehead(&head,6);
    NodeCreatehead(&head,8);
    NodeInsert(&head,9,5);
    //NodeDeleteback(&head);    
    //NodeDeletehead(&head);s
    //DeleteNode(&head,6);
    ListPrint(head);
    //ListDelete(&head);
    return 0;
 }
#endif

#if(0)//测试合并有序链表
int main(){
    ListNode *List1,*List2;
    ListInit(&List1);ListInit(&List2);
    NodeCreateback(&List1,1);
    NodeCreateback(&List1,8);
    NodeCreateback(&List1,9);
    NodeCreateback(&List2,2);
    NodeCreateback(&List2,4);
    NodeCreateback(&List2,11);
    //ListPrint(List1);
    ListNode *cur;
    cur=MergeOrderList(List1,List2);
    ListPrint(cur);
    return 0;
}
#endif


#if(0)
typedef int ElemType;
typedef struct Node //类型定义Node*（定义指向结点的指针） 与LinkList（定义头指针变量）
{   ElemType data;
    struct Node * next;
}Node,*LinkList;

void InitList(LinkList *L)  //初始化空单链表L
{   *L=(LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;
}
void Createfromhand(LinkList L)
{   Node *s;
    char c;
    int flag=1;
    while (flag)
    {c=getchar();
    if(c!='$')
    {s=(Node*)malloc(sizeof(Node));
    s->data=c;
    s->next=L->next;
    L->next=s;
    }
    else flag=0;
    }
}
#endif
   
#if(0)
    /* 定义一个表示链表的结构体指针 */
    struct list {
        int id;         /* 标识这个元素方便查找 */
        char data[20];      /* 链表中包含的元素 */
        struct list *next;  /* 指向下一个链表的指针 */
    };

    /* 定义一个链表头部 */
    static struct list *list_head = NULL;

    /* 为了保证每一个链表元素的id不同，特意把id定义成一个全局静态变量 */
    static int list_id = 0;

    /** 将指定元素插入到链表尾部
      *     head    : 表示要插入元素的链表的头部的地址
      * list    : 表示要插入到链表中的元素
      */
    static void list_add(struct list *head, struct list *list)
    {
        struct list *temp;

        /* 判断链表是否为空 */
        if(head == NULL)
        {
            /* 为空 */
            head = list;
            list->next = NULL;
        }
        else
        {
            /* 不为空 */
            temp = head;
            while(temp)
            {
                if(NULL == temp->next)
                {
                    temp->next = list;
                    list->next = NULL;
                }
                temp = temp->next;
            }
        }
    }

    /** 遍历一个链表，打印链表中每个元素所包含的数据
      * head : 表示要遍历的链表的头部的指针
      */
    static void list_print(struct list *head)
    {   
        struct list *temp;

        temp = head;

        printf("list information :\n");
        while(temp)
        {
            printf("\tlist %d : %s    %p\n    ", temp->id, temp->data,temp->next);
            //printf("list %d   loca:%p   loca_next:%p\n",temp->id,temp,temp->next);
            temp = temp->next;
        }
    }

    /* 主函数，程序的入口 */
    int main()
    {
        int i = 0;
        struct list *lists = NULL;

        /* 分配10个元素 */
        
        lists = malloc(sizeof(struct list) * 10);
        if(NULL == lists)
        {
            printf("malloc error!\n");
            return -1;
        }
        

        /* 将分配的10个元素依次填充数据并加入到链表当中 */
        for(i = 0; i < 10; i++)
        {   
            lists[i].id = list_id++;
            sprintf(lists[i].data, "TECH-PRO - %d", i);
            list_add(&list_head, &lists[i]);
        }

        /* 遍历链表，把链表中每个元素的信息都打印出来 */
        list_print(&list_head);

        return 0;
    }
   
#endif












//第二部分为双向链表操作。包括双向链表的实现、初始化、头尾插（删），打印等等
//双向链表一定有头结点！！！
//主要结构由prev、data、next三部分组成：prev指向上一个结点，data内存内容，next指向下一个结点。
//结构体定义：
typedef struct ListDubNode
{ struct ListDubNode *next;
  struct ListDubNode *prev;
  ListDataType data;
}LDNode;
 


//创建结点：
LDNode*  BuyLDNode(ListDataType x)
{ LDNode *newnode=(LDNode*)malloc(sizeof(LDNode));
  if(newnode==NULL)
    { perror("malloc fail");
      return NULL;
    }
  newnode->data=x;
  newnode->next=NULL;
  newnode->prev=NULL;   
  return newnode;
}



//初始化：
 LDNode *LDInit()
 { LDNode *head=BuyLDNode(-1);
   head->next=head;
   head->prev=head;
   return head;
 }


 
//尾插法建表：
#if(1)
void LDNodeCreateback(LDNode* head,ListDataType x)
{ LDNode* tail=head->prev;
  LDNode* newnode=BuyLDNode(x);
  tail->next=newnode;
  newnode->prev=tail;
  newnode->next=head;
  head->prev=newnode;
  
}
#endif
  


//头插法建表
void LDNodeCreatehead(LDNode* head,ListDataType x)
{ LDNode* cur=head->next;
  LDNode* newnode=BuyLDNode(x);
  head->next=newnode;
  newnode->prev=head;
  newnode->next=cur;
  (*cur).prev=newnode;  
}



//尾删
void LDNodeDeleteBack(LDNode* head)
{ LDNode* cur;
  if(head->next==head) return;
  else
  { if(head->next->next==head) 
     { free(head->next);
       head->next=head; 
       head->prev=head; 
     }
    else 
     { cur=head->next;
       while(cur->next->next!=head)
       {cur=cur->next; 
       }
       free(cur->next);
       cur->next=head;
       head->prev=cur->next;
     }
  }
}


//头删
void LDNodeDeleteHead(LDNode* head)
{ LDNode* cur;
  if(head->next==head) return;
  else
  { if(head->next->next==head) 
     { free(head->next);
       head->next=head; 
       head->prev=head; 
     }
    else 
    { cur=head->next->next;
      free(head->next);
      head->next=cur;
      cur->prev=head;
    }
  }
}




//打印双向链表
void LDPrint(LDNode* head)
{ printf("guard<==>");
  LDNode*cur=head->next;
  while(cur!=head)
  { printf("%d<==>",cur->data);
    cur=cur->next;
  }
  printf("guard\n");
}
 //双向链表测试：
int main(){
    LDNode* head=LDInit();
    /**
    LDNodeCreateback(head,1);
    LDNodeCreateback(head,4);
    LDNodeCreateback(head,6);
    */
    LDNodeCreatehead(head,1);
    LDNodeCreatehead(head,4);
    LDNodeCreatehead(head,6);
    //LDNodeDeleteBack(head);
    LDNodeDeleteHead(head);
    LDPrint(head);
    
}