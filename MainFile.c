#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define FLR 2
#define COL 2
#define wait getchar(),getchar()

typedef struct node
{
    int floor;
    int column;
    char num[10];
    int pin;
    time_t tim;
    struct node *link;
}*listpointer;

listpointer first = NULL;

bool position[FLR][COL] = {0};
int holdpos[2];
int car = 0;
int rate = 10;

void getempty()
{
    int i,j;
    for(i=0;i<FLR;i++)
    for(j=0;j<COL;j++)
    {
       if(!position[i][j])
       {
        holdpos[0] = i;
        holdpos[1] = j;
        position[i][j] = 1;
        return;
       }
    }
}


listpointer getnode(char num[])
{
    listpointer temp;
    temp = first;
    while(temp)
    {
    if(!strcmp(num,temp->num))
    return temp;
    else
    temp = temp->link;
    }

    return NULL;
}


listpointer gettrail(listpointer node)
{
    listpointer temp = first;
    if(node == first)
    return NULL;
    else
    while(temp)
    {
        if(temp->link == node)
        return temp;
        else
        temp = temp->link;
    }
}


void pop(listpointer trail,listpointer node)
{
    position[node->floor][node->column] = false;
    if(trail)
    trail->link = node->link;
    else
    first = first->link;
    printf("\nFloor = %d\tColumn = %d\n",node->floor,node->column);
    free(node);
    wait;
}


int getpin()
{
    int pin;
    printf("Enter pin: ");
    scanf("%d",&pin);
    return pin;
}


void push(char number[])
{
    getempty();
    listpointer temp,x;
    x = first;

    for( ; x->link ; x = x->link );

    temp    = (listpointer)malloc(sizeof(*temp));
    x->link = temp;

    strcpy(temp->num,number);
    temp->floor  = holdpos[0];
    temp->column = holdpos[1];
    temp->pin    = getpin();
    temp->tim    = time(NULL);
    temp->link   = NULL;
}


void calc(listpointer temp)
{
    time_t now = time(NULL);
    printf("\nAmount outstanding = %.0f\n",difftime(now,temp->tim)*rate);   // /3600
}

bool checkuser(listpointer temp)
{
    int x;
    printf("Enter our pin: ");
    scanf("%d",&x);
    if( x == temp->pin )
    return true;
    else
    return false;
}


void editnode(listpointer node)
{
    int flor,coll;
    printf("Enter floor and column of car with sequence %s : ",node->num);
    scanf("%d%d",&flor,&coll);
    position[node->floor][node->column] = false;
    node->floor  = flor;
    node->column = coll;
    position[flor][coll] = true;
}


void admin()
{
    system("cls"); //doesn't work on online compilers
    int a;
    char seq[10];
    listpointer node;
    printf("ADMIN screen\n\nEnter password:\t");
    scanf("%d",&a);

    if( a == 123456 )
    {
    system("cls"); //doesn't work on online compiler
    printf("Enter choice\n");
    printf("\t1)End Day\t\t2)Edit Data\n");
    scanf("%d",&a);
    switch(a)
        {
        case 1: exit(0);
        case 2: if(car>0)
            {
                printf("Enter number of the car wrongly parked:\t");
                scanf("%s",seq);
                node = getnode(seq);

                if(node)
                editnode(node);
                else
                printf("No such car\n"),wait;
            }

            else
            {
                printf("Sorry, no Cars\n");
                wait;
            }
            break;
        }
    }
}


void main()
{
    int choice,f;
    char number[10];
    listpointer node;
    first = (listpointer)malloc(sizeof(*first));
    first->link = NULL;

    while(1)
        {
        system("cls"); //doesn't work on online compiler
            printf("Enter choice:\n");
            printf("1)Park Car\t\t2)End Park\t\t3)Admin Login\n\n");
            scanf("%d",&choice);

            switch(choice)
                    {
                        case 1:
                if(car<FLR*COL)
                                {
                    printf("Enter your car's number sequence:\t");
                                    scanf("%s",number);
                                    push(number);
                                    car++;
                                }
                                else
                                {
                    printf("No spaces left\n");
                    wait;
                                }
                                break;

                        case 2:
                if(car>0)
                                {
                    printf("Enter your car's number sequence:\t");
                                    scanf("%s",number);
                                    node = getnode(number);

                    if( node && checkuser(node) )
                    {
                    calc(node);
                    pop(gettrail(node),node);
                    car--;
                    }

                    else
                    printf("No such user\n");

                }

                                else
                printf("No cars parked\n");
                                wait;
                                break;

                        case 3: admin();
                                break;
                    }
        }
}
