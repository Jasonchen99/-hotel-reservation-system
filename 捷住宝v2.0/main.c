#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define maxprice 4

typedef struct hotel
{
    char name[20];//�Ƶ�����
    int roomnumber;
    struct room *headr;//��������
    struct hotel *next;//�Ƶ�ָ��
} hotelnode,*hotellist;


typedef struct room
{
    int RoomID;//�����
    int Price;//����۸�
    char type[20];//��������
    int State;//����״̬
    struct room *nextr;//����ָ��
} roomnode,*roomlist;


hotellist head;//�Ƶ�����
int flag=0;


//��������

//��½����
void login();
//������Ч
void transition();
//�û�����
void usermode();
//����Ա����
void managermode();
//ѡ�񷿼�
void chooseroom(char *name);
//��ʾ����
void showroom();
//��ʾ�Ƶ�
void showhotel();
//��ӾƵ�
void addhotel();
//ɾ���Ƶ�
void delhotel();
//�޸ķ���
void modifyhotel();
//�۸�����
void sort1(roomlist head,int count);
//��ʼ������
void Initiate(roomlist *head);
//ȡ��������Ԫ�ڵ�
roomlist GetFirstNode(roomlist head);
//����ڵ���ĩβ
void AppendNode(roomlist head,roomlist node);
//��˳�򽫽ڵ����¹�������
void Total(roomlist L,roomlist head);
//����������
int Power(int a,int n);
//���۸�λ������
int GetNum(roomlist p,int i);
//�Ƶ�Ԥ��
void checkin(char *name,int roomid);
//��ʾ������Ϣ
void showall();



/***
��������login()
����ֵ���ͣ�void
�������ܣ���¼����
���룺0/1/2
�������
***/

void login()
{

    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|     *��ѡ�����ģʽ*    |\n");
    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|     >1.�û�ģʽ         |\n");
    printf("\t\t\t|     >2.����Աģʽ       |\n");
    printf("\t\t\t|     >0.�˳�����         |\n");
    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t���������ֱ��ѡ����룺     ");

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
        printf("\t\t\t���������������������룺\n");
        Sleep(1000);
        login();
    }

}

/***
��������transition()
����ֵ���ͣ� void
�������ܣ����ɶ���
���룺��
�������
***/

void transition()
{

    printf("\n\t\t\tLoding��");//���붯��

    for(int i=0; i<9; i++)
    {
        Sleep(80);
        printf("��");
    }

    printf("\n\t\t\t������ɣ�������һ���˵�");
    Sleep(500);
    system("cls");

}

/***
��������usermode()
����ֵ���ͣ�void
�������ܣ��û�����
���룺0/1
�������
***/

void usermode()
{

    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|        *�û�ģʽ*       |\n");
    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|     >1.ѡ��Ƶ�         |\n");
    printf("\t\t\t|     >0.�˳���¼         |\n");
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
��������managermode()
����ֵ���ͣ�void
�������ܣ�����Ա����
���룺0/1/2
�������
***/

void managermode()
{

    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|       *����Աģʽ*      |\n");
    printf("\t\t\t|-------------------------|\n");
    printf("\t\t\t|     >1.���ӾƵ�         |\n");
    printf("\t\t\t|     >2.ɾ���Ƶ�         |\n");
    printf("\t\t\t|     >3.�޸ķ���         |\n");
    printf("\t\t\t|     >4.��ʾ���оƵ귿�� |\n");
    printf("\t\t\t|     >0.�˳���¼         |\n");
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
��������showroom()
����ֵ���ͣ�void
�������ܣ���ʾ����
���룺�Ƶ�����
�������
***/

void showroom()
{

    showhotel();
    char name[20];
    printf("\t\t\t��������ס�Ƶ����ƣ�\n");
    scanf("%s",name);
    system("cls");
    hotellist p=head->next;

    while(p)
    {
        if(strcmp(p->name,name)==0)
        {
            printf("\t\t\t---------------------------\n");
            printf("\t\t\t|   ��ǰ�Ƶ��Ԥ���ķ���  |\n");
            printf("\t\t\t---------------------------\n");
            printf("\t\t\t�����\t��������\t����۸�\n");
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
��������chooseroom();
����ֵ���ͣ�void
�������ܣ�ѡ�񷿼�
���룺�����
�������
***/

void chooseroom(char *name)
{

    printf("\t\t\t1.�۸�����\n");
    printf("\t\t\t2.Ԥ������\n");
    printf("\t\t\t3.�����ϲ�\n");
    printf("\t\t\t����������ѡ��\n");
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
        printf("\t\t\t|   ��ǰ�Ƶ��Ԥ���ķ���  |\n");
        printf("\t\t\t---------------------------\n");
        printf("\t\t\t�����\t��������\t����۸�\n");
        printf("\t\t\t---------------------------\n");
        while(rmove2->nextr!=NULL)
        {
            if(rmove2->nextr->State==0)
            {
                printf("\t\t\t%d\t%s\t%d\n",rmove2->nextr->RoomID,rmove2->nextr->type,rmove2->nextr->Price);
            }
            rmove2=rmove2->nextr;
        }

        printf("\t\t\t�����뷿���Ԥ����\n");
        int roomidx;
        scanf("%d",&roomidx);
        checkin(name,roomidx);
        system("pause");
        system("cls");
        usermode();
        break;

    case 2:
        printf("\t\t\t�����뷿���Ԥ����\n");
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
��������showhotel()
����ֵ���ͣ�void
�������ܣ���ʾ�Ƶ�
���룺��
��������оƵ���
***/

void showhotel()
{

    system("cls");
    printf("\t\t\t---------------------------\n");
    printf("\t\t\t|        *�Ƶ��б�*       |\n");
    printf("\t\t\t---------------------------\n");

    if(head==NULL)
    {
        printf("\t\t\t��ǰ�޾Ƶ�");
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
��������addhotel()
����ֵ���ͣ�void
�������ܣ���ӾƵ�
���룺�Ƶ귿����Ϣ
�������
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
    printf("\t\t\t������Ƶ����ƣ�\n");
    scanf("%s",p->name);
    printf("\t\t\t������Ƶ귿������\n");
    scanf("%d",&i);
    p->roomnumber=i;
    printf("\t\t\t����ӸþƵ귿��:\n\n");
    roomlist qr;
    p->headr=(roomlist)malloc(sizeof(roomnode));
    p->headr->nextr=NULL;

    while(i--)
    {
        system("cls");
        qr=(roomlist)malloc(sizeof(roomnode));
        /*printf("�������%d������ţ�\n",j);
        scanf("%d",&qr->RoomID);
        printf("�������%d���������ͣ�\n",j);
        scanf("%s",qr->type);
        printf("�������%d������۸�\n",j);
        scanf("%d",&qr->Price);*/
        printf("\t\t\t�����뷿����Ϣ��\n");
        printf("\t\t\t����� �������� ����۸�\n");
        scanf("\t\t\t%d %s %d",&qr->RoomID,qr->type,&qr->Price);
        qr->State=0;
        j++;
        qr->nextr=p->headr->nextr;
        p->headr->nextr=qr;

    }

    p->next=head->next;
    head->next=p;
    printf("\t\t\t�½��ɹ�������\n");
    system("pause");
    system("cls");
    managermode();

}

/***
��������delhotel()
����ֵ���ͣ�void
�������ܣ�ɾ���Ƶ�
���룺�Ƶ���
�������
***/

void delhotel()
{

    char name[20];

    if(head==NULL)
    {
        printf("\t\t\t��ǰ�޾Ƶ�");
        system("pause");
        system("cls");
        managermode();
    }

    printf("\t\t\t������Ҫɾ���ľƵ����ƣ�\n");
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
            printf("\t\t\t�þƵ�ɾ���ɹ�!\n");
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
��������modifyhotel()
����ֵ���ͣ�void
�������ܣ��޸ķ���
���룺�Ƶ����������
�������
***/

void modifyhotel()
{

    system("cls");
    char name[20];
    int roomid;

    if(head==NULL)
    {
        printf("\t\t\t��ǰ�޾Ƶ�");
        system("pause");
        system("cls");
        managermode();
    }

    printf("\t\t\t������Ҫ�޸ĵľƵ����ƣ�\n");
    scanf("%s",name);
    printf("\t\t\t������Ҫ�޸ĵķ���ţ�\n");
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
                    printf("\t\t\t������Ҫ�޸ĵļ۸�\n");
                    scanf("%d",&newp);
                    rmove->nextr->Price=newp;
                    break;
                }

                rmove=rmove->nextr;
            }
        }

        p=p->next;
    }

    printf("\t\t\t�޸ĳɹ�\n");
    system("pause");
    system("cls");
    managermode();
}

/***
��������Initiate()
����ֵ���ͣ�void
�������ܣ���ʼ������
���룺��
�������
***/


void Initiate(roomlist *head)
{
    (*head)=(roomlist)malloc(sizeof(roomnode));
    (*head)->nextr=NULL;
}

/***
��������GetFirstNode()
����ֵ���ͣ�roomlist
�������ܣ�ȡ��������Ԫ�ڵ�
���룺��
�������
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
��������AppendNode()
����ֵ���ͣ�void
�������ܣ����ڵ����β��
���룺��
�������
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
��������Total()
����ֵ���ͣ�void
�������ܣ����ڵ㰴��˳����������
���룺��
�������
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
��������Power()
����ֵ���ͣ�void
�������ܣ����������㣨��дpow������
���룺��
�������
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
��������GetNum()
����ֵ���ͣ�int
�������ܣ�ȡ�÷���۸��λ����
���룺��
�������
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
��������sort1()
����ֵ���ͣ�void
�������ܣ���С��������
���룺��
�������
***/
//�ڶ����βα�ʾ�μ�������������λ��һ����countλ����

void sort1(roomlist head,int count)
{

    roomlist p[10],q;
    int i,j,k;

    for(j=1; j<=count; j++)
    {
        //ʮ��ͷ����ʼ��
        for(i=0; i<10; i++)
        {
            Initiate(&p[i]);
        }

        //�����ͷ��βɨ�裬����ɨ�赽�Ľڵ���������
        while(head->nextr!=NULL)
        {
            q=GetFirstNode(head);
            k=GetNum(q,j); //ȡ������ڵ��jλ��Ԫ��ֵk
            AppendNode(p[k],q); //���ýڵ����ӵ�10��������Ӧ��λ��
        }
        //��10�������0-9�������ӵ�head�ڵ����

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
��������checkin()
����ֵ���ͣ�void
�������ܣ��Ƶ�Ԥ��
���룺��
�������
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
    printf("\t\t\tԤ���ɹ�������\n");

}

/***
��������showall()
����ֵ���ͣ�void
�������ܣ���ʾ������Ϣ
���룺��
�������
***/

void showall()
{
    system("cls");
    printf("\t\t\t---------------------------\n");
    printf("\t\t\t|        *�Ƶ��б�*       |\n");
    printf("\t\t\t---------------------------\n");

    if(head==NULL)
    {
        printf("\t\t\t��ǰ�޾Ƶ�");
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
��������main()
����ֵ���ͣ�void
�������ܣ�������
���룺��
�������
***/

int main()
{
    login();
    return 0;
}
