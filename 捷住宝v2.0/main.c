#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define maxprice 4

typedef struct hotel
{
    char name[20];//酒店名称
    int roomnumber;
    struct room *headr;//房间链表
    struct hotel *next;//酒店指针
} hotelnode,*hotellist;


typedef struct room
{
    int RoomID;//房间号
    int Price;//房间价格
    char type[20];//房间类型
    int State;//房间状态
    struct room *nextr;//房间指针
} roomnode,*roomlist;


hotellist head;//酒店链表
int flag=0;


//声明函数

//登陆界面
void login();
//动画特效
void transition();
//用户界面
void usermode();
//管理员界面
void managermode();
//选择房间
void chooseroom(char *name);
//显示房间
void showroom();
//显示酒店
void showhotel();
//添加酒店
void addhotel();
//删除酒店
void delhotel();
//修改房价
void modifyhotel();
//价格排序
void sort1(roomlist head,int count);
//初始化链表
void Initiate(roomlist *head);
//取得链表首元节点
roomlist GetFirstNode(roomlist head);
//插入节点至末尾
void AppendNode(roomlist head,roomlist node);
//按顺序将节点重新构成链表
void Total(roomlist L,roomlist head);
//整型幂运算
int Power(int a,int n);
//将价格位数分离
int GetNum(roomlist p,int i);
//酒店预定
void checkin(char *name,int roomid);
//显示所有信息
void showall();



/***
函数名：login()
返回值类型：void
函数功能：登录界面
输入：0/1/2
输出：无
***/

void login()
{

    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|     *请选择登入模式*    |\n");
    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|     >1.用户模式         |\n");
    printf("\t\t\t|     >2.管理员模式       |\n");
    printf("\t\t\t|     >0.退出程序         |\n");
    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t请输入数字编号选择进入：     ");

    int temp;
    scanf("%d",&temp);
    if(temp==1)
    {
        transition();
        usermode();
    }
    else if(temp==2)
    {
        transition();
        managermode();
    }
    else if(temp==0)
        exit(0);
    else
    {
        system("cls");
        printf("\t\t\t您的输入有误，请重新输入：\n");
        Sleep(1000);
        login();
    }

}

/***
函数名：transition()
返回值类型： void
函数功能：过渡动画
输入：无
输出：无
***/

void transition()
{

    printf("\n\t\t\tLoding：");//进入动画

    for(int i=0; i<9; i++)
    {
        Sleep(80);
        printf("█");
    }

    printf("\n\t\t\t载入完成，进入下一级菜单");
    Sleep(500);
    system("cls");

}

/***
函数名：usermode()
返回值类型：void
函数功能：用户界面
输入：0/1
输出：无
***/

void usermode()
{

    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|        *用户模式*       |\n");
    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|     >1.选择酒店         |\n");
    printf("\t\t\t|     >0.退出登录         |\n");
    printf("\t\t\t|-------------------------|\n");

    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        showroom();
        break;
    case 0:
        system("cls");
        login();
    }

}

/***
函数名：managermode()
返回值类型：void
函数功能：管理员界面
输入：0/1/2
输出：无
***/

void managermode()
{

    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|       *管理员模式*      |\n");
    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|     >1.增加酒店         |\n");
    printf("\t\t\t|     >2.删除酒店         |\n");
    printf("\t\t\t|     >3.修改房价         |\n");
    printf("\t\t\t|     >4.显示所有酒店房间 |\n");
    printf("\t\t\t|     >0.退出登录         |\n");
    printf("\t\t\t|-------------------------|\n");

    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        addhotel();
        break;
    case 2:
        delhotel();
        break;
    case 3:
        modifyhotel();
        break;
    case 4:
        showall();
        break;
    case 0:
        system("cls");
        login();
    }

}


/***
函数名：showroom()
返回值类型：void
函数功能：显示房间
输入：酒店名称
输出：无
***/

void showroom()
{

    showhotel();
    char name[20];
    printf("\t\t\t请输入入住酒店名称：\n");
    scanf("%s",name);
    system("cls");
    hotellist p=head->next;

    while(p)
    {
        if(strcmp(p->name,name)==0)
        {
            printf("\t\t\t---------------------------\n");
            printf("\t\t\t|   当前酒店可预订的房间  |\n");
            printf("\t\t\t---------------------------\n");
            printf("\t\t\t房间号\t房间类型\t房间价格\n");
            printf("\t\t\t---------------------------\n");
            roomlist rmove=p->headr;

            while(rmove->nextr!=NULL)
            {
                if(rmove->nextr->State==0)
                {
                    printf("\t\t\t%d\t%s\t%d\n",rmove->nextr->RoomID,rmove->nextr->type,rmove->nextr->Price);
                }
                rmove=rmove->nextr;
            }

        }

        p=p->next;
    }
    printf("\t\t\t---------------------------\n");
    chooseroom(name);
    system("pause");
    system("cls");
    usermode();

}

/***
函数名：chooseroom();
返回值类型：void
函数功能：选择房间
输入：房间号
输出：无
***/

void chooseroom(char *name)
{

    printf("\t\t\t1.价格正序\n");
    printf("\t\t\t2.预定房间\n");
    printf("\t\t\t3.返回上层\n");
    printf("\t\t\t请输入数字选择：\n");
    hotellist p=head->next;

    while(p)
    {
        if(strcmp(p->name,name)==0)
        {
            break;
        }
        else
            p=p->next;
    }

    int k;
    scanf("%d",&k);
    switch(k)
    {
    case 1:
        sort1(p->headr,maxprice);
        system("cls");
        roomlist rmove2=p->headr;

        printf("\t\t\t---------------------------\n");
        printf("\t\t\t|   当前酒店可预订的房间  |\n");
        printf("\t\t\t---------------------------\n");
        printf("\t\t\t房间号\t房间类型\t房间价格\n");
        printf("\t\t\t---------------------------\n");
        while(rmove2->nextr!=NULL)
        {
            if(rmove2->nextr->State==0)
            {
                printf("\t\t\t%d\t%s\t%d\n",rmove2->nextr->RoomID,rmove2->nextr->type,rmove2->nextr->Price);
            }
            rmove2=rmove2->nextr;
        }

        printf("\t\t\t请输入房间号预定：\n");
        int roomidx;
        scanf("%d",&roomidx);
        checkin(name,roomidx);
        system("pause");
        system("cls");
        usermode();
        break;

    case 2:
        printf("\t\t\t请输入房间号预定：\n");
        int roomid;
        scanf("%d",&roomid);
        checkin(name,roomid);
        system("pause");
        system("cls");
        usermode();
        break;

    case 3:
        system("cls");
        usermode();
        break;
    }

}

/***
函数名：showhotel()
返回值类型：void
函数功能：显示酒店
输入：无
输出：所有酒店名
***/

void showhotel()
{

    system("cls");
    printf("\t\t\t---------------------------\n");
    printf("\t\t\t|        *酒店列表*       |\n");
    printf("\t\t\t---------------------------\n");

    if(head==NULL)
    {
        printf("\t\t\t当前无酒店");
        system("pause");
        system("cls");
        login();
    }
    hotellist pmove=head;

    while (pmove->next != NULL)
    {
        printf("\t\t\t>%s<\n",pmove->next->name);
        pmove=pmove->next;
    }
    printf("\t\t\t---------------------------\n");

}


/***
函数名：addhotel()
返回值类型：void
函数功能：添加酒店
输入：酒店房间信息
输出：无
***/

void addhotel()
{

    int i,j=1;
    system("cls");
    hotellist p;

    if(flag==0)
    {
        head=(hotellist)malloc(sizeof(hotelnode));
        head->next=NULL;
        flag=1;
    }
    p=(hotellist)malloc(sizeof(hotelnode));
    printf("\t\t\t请输入酒店名称：\n");
    scanf("%s",p->name);
    printf("\t\t\t请输入酒店房间数：\n");
    scanf("%d",&i);
    p->roomnumber=i;
    printf("\t\t\t请添加该酒店房间:\n\n");
    roomlist qr;
    p->headr=(roomlist)malloc(sizeof(roomnode));
    p->headr->nextr=NULL;

    while(i--)
    {
        system("cls");
        qr=(roomlist)malloc(sizeof(roomnode));
        /*printf("请输入第%d个房间号：\n",j);
        scanf("%d",&qr->RoomID);
        printf("请输入第%d个房间类型：\n",j);
        scanf("%s",qr->type);
        printf("请输入第%d个房间价格：\n",j);
        scanf("%d",&qr->Price);*/
        printf("\t\t\t请输入房间信息：\n");
        printf("\t\t\t房间号 房间类型 房间价格\n");
        scanf("\t\t\t%d %s %d",&qr->RoomID,qr->type,&qr->Price);
        qr->State=0;
        j++;
        qr->nextr=p->headr->nextr;
        p->headr->nextr=qr;

    }

    p->next=head->next;
    head->next=p;
    printf("\t\t\t新建成功！！！\n");
    system("pause");
    system("cls");
    managermode();

}

/***
函数名：delhotel()
返回值类型：void
函数功能：删除酒店
输入：酒店名
输出：无
***/

void delhotel()
{

    char name[20];

    if(head==NULL)
    {
        printf("\t\t\t当前无酒店");
        system("pause");
        system("cls");
        managermode();
    }

    printf("\t\t\t请输入要删除的酒店名称：\n");
    scanf("%s",name);
    hotellist q=head;
    hotellist p=head->next;

    while(p)
    {
        if(strcmp(p->name,name)==0)
        {
            q->next=p->next;
            free(p);
            p=q->next;
            printf("\t\t\t该酒店删除成功!\n");
            break;
        }
        q=p;
        p=p->next;
    }

    system("pause");
    system("cls");
    managermode();

}

/***
函数名：modifyhotel()
返回值类型：void
函数功能：修改房价
输入：酒店名，房间号
输出：无
***/

void modifyhotel()
{

    system("cls");
    char name[20];
    int roomid;

    if(head==NULL)
    {
        printf("\t\t\t当前无酒店");
        system("pause");
        system("cls");
        managermode();
    }

    printf("\t\t\t请输入要修改的酒店名称：\n");
    scanf("%s",name);
    printf("\t\t\t请输入要修改的房间号：\n");
    scanf("%d,",&roomid);
    hotellist p=head->next;

    while(p)
    {
        if(strcmp(p->name,name)==0)
        {
            roomlist rmove=p->headr;

            while(rmove->nextr!=NULL)
            {

                if(rmove->nextr->RoomID==roomid)
                {
                    int newp;
                    printf("\t\t\t请输入要修改的价格：\n");
                    scanf("%d",&newp);
                    rmove->nextr->Price=newp;
                    break;
                }

                rmove=rmove->nextr;
            }
        }

        p=p->next;
    }

    printf("\t\t\t修改成功\n");
    system("pause");
    system("cls");
    managermode();
}

/***
函数名：Initiate()
返回值类型：void
函数功能：初始化链表
输入：无
输出：无
***/


void Initiate(roomlist *head)
{
    (*head)=(roomlist)malloc(sizeof(roomnode));
    (*head)->nextr=NULL;
}

/***
函数名：GetFirstNode()
返回值类型：roomlist
函数功能：取得链表首元节点
输入：无
输出：无
***/

roomlist GetFirstNode(roomlist head)
{
    if(head->nextr==NULL)
        return NULL;
    else
    {
        roomlist p;
        p=head->nextr;
        head->nextr=p->nextr;
        return p;
    }

}

/***
函数名：AppendNode()
返回值类型：void
函数功能：将节点插入尾部
输入：无
输出：无
***/

void AppendNode(roomlist head,roomlist node)
{

    if(head==NULL)
        return;
    else
    {
        roomlist p;
        p=head;
        while(p->nextr!=NULL)
        {
            p=p->nextr;
        }
        p->nextr=node;
        node->nextr=NULL;
    }

}

/***
函数名：Total()
返回值类型：void
函数功能：将节点按照顺序重新连接
输入：无
输出：无
***/

void Total(roomlist L,roomlist head)
{
    roomlist p;
    p=L;

    while(p->nextr!=NULL)
    {
        p=p->nextr;
    }

    p->nextr=head->nextr;
}

/***
函数名：Power()
返回值类型：void
函数功能：整型幂运算（重写pow函数）
输入：无
输出：无
***/

int Power(int a,int n)
{

    int y;
    if(n==0)
        return 1;
    else
    {
        y=Power(a,n/2);
        y=y*y;
        if(n%2==1)
            y=y*a;
    }
    return y;

}

/***
函数名：GetNum()
返回值类型：int
函数功能：取得房间价格各位数字
输入：无
输出：无
***/

int GetNum(roomlist p,int i)
{
    int data=p->Price;
    int a;
    i--;
    a=data/Power(10,i);
    return a%10;

}

/***
函数名：sort1()
返回值类型：void
函数功能：从小到大排序
输入：无
输出：无
***/
//第二个形参表示参加排序的整数最大位数一共有count位数字

void sort1(roomlist head,int count)
{

    roomlist p[10],q;
    int i,j,k;

    for(j=1; j<=count; j++)
    {
        //十个头结点初始化
        for(i=0; i<10; i++)
        {
            Initiate(&p[i]);
        }

        //链表从头到尾扫描，并将扫描到的节点脱离链表。
        while(head->nextr!=NULL)
        {
            q=GetFirstNode(head);
            k=GetNum(q,j); //取得链表节点第j位的元素值k
            AppendNode(p[k],q); //将该节点连接到10个链表相应的位置
        }
        //将10个链表从0-9依次连接到head节点后面

        for(i=0; i<10; i++)
        {
            Total(head,p[i]);
        }

    }

    for(i=0; i<10; i++)
    {
        free(p[i]);
    }

}


/***
函数名：checkin()
返回值类型：void
函数功能：酒店预订
输入：无
输出：无
***/

void checkin(char *name,int roomid)
{

    hotellist p=head->next;

    while(p)
    {
        if(strcmp(p->name,name)==0)
        {
            roomlist rmove=p->headr;
            while(rmove->nextr!=NULL)
            {
                if(rmove->nextr->RoomID==roomid)
                {
                    rmove->nextr->State=1;
                    break;
                }
                rmove=rmove->nextr;
            }
        }
        p=p->next;
    }
    printf("\t\t\t预定成功！！！\n");

}

/***
函数名：showall()
返回值类型：void
函数功能：显示所有信息
输入：无
输出：无
***/

void showall()
{
    system("cls");
    printf("\t\t\t---------------------------\n");
    printf("\t\t\t|        *酒店列表*       |\n");
    printf("\t\t\t---------------------------\n");

    if(head==NULL)
    {
        printf("\t\t\t当前无酒店");
        system("pause");
        system("cls");
        login();
    }
    hotellist pmove=head;

    while (pmove->next != NULL)
    {
        printf("\t\t\t>%s<\n",pmove->next->name);
        roomlist rmove=pmove->next->headr;
        while(rmove->nextr!=NULL)
            {
                if(rmove->nextr->State==0)
                {
                    printf("\t\t\t%d\t%s\t%d\n",rmove->nextr->RoomID,rmove->nextr->type,rmove->nextr->Price);
                }
                rmove=rmove->nextr;
            }
        pmove=pmove->next;
    }

    printf("\t\t\t---------------------------\n");
    system("pause");
    system("cls");
    managermode();
}

/***
函数名：main()
返回值类型：void
函数功能：主函数
输入：无
输出：无
***/

int main()
{
    login();
    return 0;
}
