#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
struct tile{
  char name[10];
  int location;
  int direction;
  int hourglass;
  int check;
  int way;

};
struct node
{
    struct tile member;
    struct node *next;
};

struct tile member1;
struct node *list1=NULL;
struct node *head=NULL;
struct node* fill_list(struct tile member1);
char names[9][10]={"I_L","J_B","J_P","J_S","J_L","Mad","M_S","S_G","W_G"};



struct token{
 char name[10];
 int location_cop;//it has twelve modes and when it is in mode 1 ,it can see tile 1,2,3

};
struct token cop[3];



struct action{
 char name[2][10];

};
struct action state[4];
int random_action_card[4];

void list_set_next();
void identity_tile();
void identity_cop();
void identity_action();
int hourglass(char *);
int location();
int direction();
void random_action();
void play_action_chase(struct action,int,int);
void print();
void function(int);
void play_action_chase(struct action state1,int number,int actor);//the first phase,the chase section
int number_tile=9;
int way1=0;
int round=1;


int number_state[4];//for function ,for better print
int first=1;//for clear number_state[4] in function


int main()
{
    int actor_Mr_jack=0;
    int actor_cop=1;

identity_tile();
identity_cop();
identity_action();
random_action();

print();
printf("\n\n");

//game
while(round<=2)
{if(round%2==0)
    {for(int i=0;i<4;i++)
     printf("%d\t%s\n",i+1,state[i].name[1-random_action_card[i]]);
        function(actor_Mr_jack);
     function(actor_cop);function(actor_cop);
     function(actor_Mr_jack);
     round++;
     continue;
     }
 if(round%2==1)
 {for(int i=0;i<4;i++)
   printf("%d\t%s\n",i+1,state[i].name[random_action_card[i]]);
     function(actor_cop);
 function(actor_Mr_jack);function(actor_Mr_jack);
 function(actor_cop);
 round++;
continue;

 }}




}

void identity_tile()
{
  for (int i=0;i<9;i++)
{
strcpy(member1.name,names[i]);
member1.location=location();
member1.direction=direction();
if(member1.location==1)
    member1.direction=1;
if(member1.location==3)
    member1.direction=3;
if(member1.location==8)
    member1.direction=4;

member1.hourglass=hourglass(names[i]);

list1 =fill_list(member1);
       if(i==0)
            head=list1;
     list_set_next();

}



 struct node *counter;
  for(counter=head;counter!= NULL ;counter=counter->next)
   {counter->member.check=0;
    counter->member.way=0;
   }


}


void identity_cop()
{
 strcpy(cop[0].name,"Hol");
 cop[0].location_cop =1;

strcpy(cop[1].name,"Wat");
 cop[1].location_cop =5;
   strcpy(cop[2].name,"Tob");
 cop[2].location_cop =9;

}




void identity_action()
{
   strcpy(state[0].name[0],"lens");
   strcpy(state[0].name[1],"HOL");
   strcpy(state[1].name[0],"TOB");
   strcpy(state[1].name[1],"WAT");
   strcpy(state[2].name[0],"turn1");
   strcpy(state[2].name[1],"swap");
   strcpy(state[3].name[0],"turn2");
   strcpy(state[3].name[1],"cops");
}


void random_action() //give 4 value for game actions
{srand(time(0));
for(int i=0;i<4;i++)
      random_action_card[i]=rand()%2;


}

void function(int actor)
{ int number;
    do{
    scanf("%d",&number);
    if(number>4 || number<1)
        printf("Error!!!\nEnter again plz.");
     }while(number>4 || number<1 );
        play_action_chase(state[number-1],number-1,actor);
    if(round==1)
       {number_state[number-1]=number;
       for(int i=0;i<4;i++)
         if(i+1!=number_state[i])
             printf("%d\t%s\n",i+1,state[i].name[random_action_card[i]]);
        }
if(round==2)
    {if(first==1)
       for(int i=0;i<4;i++)
            number_state[i]=0;
   first++;
   number_state[number-1]=number;
    for(int i=0;i<4;i++)
        if(i+1!=number_state[i])
            printf("%d\t%s\n",i+1,state[i].name[1-random_action_card[i]]);
     }

}

void play_action_chase(struct action state1,int number,int actor)//the first phase,the chase section
{  int i;
    if(round==1)
      i = random_action_card[number];
    if(round==2)
      i = 1- random_action_card[number];


 if(strcmp(state1.name[i],"lens")==0)
     {if(actor==0)
       {int m;
        srand(time(0));
        m=rand()%(/*number_tile-way1*/9)+1;
        int i=1;
    struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
     { if(i==m)
        {if(counter->member.check!=1)
          {counter->member.check=1;
           number_tile--;
            break;
          }
          if(counter->member.check==1)
           {m=rand()%(/*number_tile-way1*/9)+1;
             i=0;
            counter=head;
           }}

        i++;
     }
      print();
      return ;

       }
     if(actor==1)
      {int m;
        srand(time(0));
        m=rand()%(/*number_tile*/9-way1)+1;
        int i=1;
    struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
     {if(i==m)
         {if(counter->member.check!=1)
             {counter->member.way=1;
               way1++;
               break;
             }
         if(counter->member.check==1)
         {m=rand()%(/*number_tile*/9-way1)+1;
             counter=head;
             i=0;
         }}
        i++;
     }print();
     return;


       }


     }

   if((strcmp(state1.name[i],"HOL")==0) || (strcmp(state1.name[i],"TOB")==0) || (strcmp(state1.name[i],"WAT")==0) )
    {int j;
        if(strcmp(state1.name[i],"HOL")==0)
            j=0;
        if(strcmp(state1.name[i],"WAT")==0)
            j=1;
        if(strcmp(state1.name[i],"TOB")==0)
            j=2;


    printf("how many moves do you want?\(1 or 2\)\n");
    int m;
    do{scanf("%d",&m);
        if(m>2 || m <1)
            printf("Error!!!\nEnter again plz.\n");
      }while(m>2 || m<1);

    cop[j].location_cop+=m;
    if(cop[j].location_cop>12)
        cop[j].location_cop-=12;

        print();
        return ;
    }
   if((strcmp(state1.name[i],"turn1")==0) || (strcmp(state1.name[i],"turn2")==0))
    {printf("Which card do you choose to rotate?\(Enter name\)\n");
     char rotate[10];
      int check2=0;
     do{
         scanf("%s",rotate);
         for(int i=0;i<9;i++)
            if(strcmp(rotate,names[i])==0)
               check2=1;
         if(check2==0)
           printf("Error!!!\nEnter again plz.\n");

       }while(check2==0);

    printf("How much do you want rotate?\n1\)90  2\)180 3\)270\n\(enter 1 or 2 or 3\)\n");
     int m;
     do{
        scanf("%d",&m);
        if(m>3 || m<1)
            printf("Error!!!\nEnter again plz.\n");
       }while(m>3 || m<1);

    struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
        {if(strcmp(counter->member.name,rotate)==0)
            {counter->member.direction+=m;
               if(counter->member.direction==5)
                 counter->member.direction=1;
               if(counter->member.direction==6)
                counter->member.direction=2;
               if(counter->member.direction==7)
                counter->member.direction=3;
            break;
            }

            }
     print();
     return;
    }

   if(strcmp(state1.name[i],"swap")==0)
     {printf("which cards do you want to swap?\(enter names\)\n");
      char swap1[10];
      char swap2[10];
       int check3=0;
 do{scanf("%s",swap1);
    for(int i=0;i<9;i++)
    if(strcmp(swap1,names[i])==0)
        check3=1;
    if(check3==0)
     printf("Error!!!\nEnter again plz.\n");
    }while(check3==0);
check3=0;
 do{scanf("%s",swap2);
    for(int i=0;i<9;i++)
        if(strcmp(swap2,names[i])==0)
            check3=1;
         if(check3==0)
           printf("Error!!!\nEnter again plz.\n");
    }while(check3==0);

 int location1,location2;
       struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
       {if(strcmp(counter->member.name,swap1)==0)
          location1=counter->member.location;

        if(strcmp(counter->member.name,swap2)==0)
          location2=counter->member.location;
        }


      for(counter=head;counter!= NULL ;counter=counter->next)
       {if(strcmp(counter->member.name,swap1)==0)
          counter->member.location=location2;

        if(strcmp(counter->member.name,swap2)==0)
          counter->member.location=location1;
        }
       print();
       return;

     }
if(strcmp(state1.name[i],"cops")==0)
    {int m;
    if(actor==0)
     {printf("enter 1\)Holmes  2\)Watson 3\)Toby 4\)don't change \(Enter number\)\n");
        do{scanf("%d",&m);
            if(m>4 || m<1)
            printf("Wrong!!!\nEnter again:\n");
          }while(m>4 || m<1);
     }

      if(actor==1)
             {printf("enter 1\)Holmes  2\)Watson 3\)Toby \(Enter number\) \n");
               do{scanf("%d",&m);
                   if(m>3 || m<1)
                     printf("Wrong!!!\nEnter again:\n");
                 }while(m>3 ||m<1);
             }

        if(m==1)
            cop[0].location_cop+=1;
        if(m==2)
            cop[1].location_cop+=1;
         if(m==3)
            cop[2].location_cop+=1;


        print();
        return;
        }










}

struct node* fill_list(struct tile member1)
{
    struct node *nn=malloc(sizeof(struct node));
    nn->member= member1;
    nn ->next =NULL;

    return nn;

};

void list_set_next()
{
    struct node *counter;
    for(counter=head;counter->next!= NULL;counter=counter->next);
    counter->next =list1;
    list1->next =NULL;


}

int hourglass(char *name)
{ if(strcmp(name,"I_L"))
    return 0;
  if(strcmp(name,"J_B"))
     return 1;
  if(strcmp(name,"J_P"))
   return 1;
  if(strcmp(name,"J_S"))
   return 1;
  if(strcmp(name,"J_L"))
   return 1;
  if(strcmp(name,"Mad"))
   return 2;
  if(strcmp(name,"M_S"))
   return 1;
  if(strcmp(name,"S_G"))
   return 0;
  if(strcmp(name,"W_G"))
   return 1;
}

int location()  //this function for arrange tile.
{int random_location;
srand(time(0));
int check=0;
while(check!=1)
{ check=1;
 random_location=rand()%9+1;
 struct node *counter;
 for(counter=head;counter!= NULL ;counter=counter->next)
    if(counter->member.location==random_location)
     {check=0;
     continue;}}

return random_location;
}

/*every tile have direction, So we have to set the direction of the package randomly,
Except for three numbers that are in places 1, 3 and 8 (Rules of the game)*/

int direction()
{int random_direction;
    srand(time(0));
  random_direction= rand()%4+1;
  return random_direction;

}


void print()
{ int p = 0;
   for(int i=0;i<32;i++)
        printf("_");
        printf("\n");
/*printf("      ");
  if(cop[0].location.cop==2)
     printf("HOL");
   else if(cop[1].location.cop==2)
     printf("WAT");
  else if(cop[2].location.cop==2)
     printf("TOB");
     else
        printf("   ");
printf("      ");
 if(cop[0].location.cop==3)
     printf("HOL");
   else if(cop[1].location.cop==3)
     printf("WAT");
  else if(cop[2].location.cop==3)
     printf("TOB");
     else
        printf("   ");*/
for(int i=2;i<=4;i++)
    {printf("      ");
  if(cop[0].location_cop==i)
     printf("HOL");
   else if(cop[1].location_cop==i)
     printf("WAT");
  else if(cop[2].location_cop==i)
     printf("TOB");
     else
        printf("   ");}

printf("\n");
  char m[9][10];
  int n[9];
  int way2[9];
  int i=0;

  struct node *counter;
  while(i!=9)
 {  for(counter=head;counter!= NULL;counter=counter->next)
       if(counter->member.location==i+1)
          {n[i] =counter->member.direction;
          way2[i]=counter->member.way;
        strcpy(m[i],counter->member.name);
         i++;
         continue;
          }}
/*int check22;
  if(cop[0].location_cop==1)
     check22=0;
  if(cop[0].location_cop==11)
    check22=6;
  if(cop[0].location_cop==12)
    check22=3;*/

while(p!=9)
   {for(int k=0;k<3;k++)
    {printf("   ");
     for(int j=p;j<p+3;j++)
         {printf("   ");
          printf(" ");
        if(n[j]==1 || n[j]==3 || n[j]==4)
        {
            printf("|");
        }
        if(n[j]==2)
         {
           printf("*");
         }
         printf(" ");

     printf("   ");

    }
    printf("\n");}

    if(cop[0].location_cop==1 && p==0)
     printf("HOL");
    if(cop[1].location_cop==1&& p==0)
     printf("WAT");
    if(cop[2].location_cop==1 && p==0)
     printf("TOB");
     if(cop[0].location_cop!=1 && cop[1].location_cop!=1 && cop[2].location_cop!=1 && p==0)
         printf("   ");


  if(cop[0].location_cop==11 && p==6)
     printf("HOL");
  if(cop[1].location_cop==11&&p==6)
     printf("WAT");
  if(cop[2].location_cop==11&& p==6)
     printf("TOB");
  if(cop[0].location_cop!=11 && cop[1].location_cop!=11 && cop[2].location_cop!=11 && p==6)
        printf("   ");


    if(cop[0].location_cop ==12 && p==3)
     printf("HOL");
    if(cop[1].location_cop ==12 && p==3)
     printf("WAT");
    if(cop[2].location_cop==12  && p==3)
     printf("TOB");
     if(cop[0].location_cop!=12 && cop[1].location_cop!=12 && cop[2].location_cop!=12 && p==3)
        printf("   ");


//printf("   ");
for(int j=p;j<p+3;j++)
        {if(n[j]==1)
         printf("***");
       if(n[j]==2 || n[j]==4||n[j]==3)
        printf("---");
    if(way2[j]==1)
        printf("   ");
     else
        printf("%s",m[j]);
if(n[j]==1||n[j]==2||n[j]==4)
         printf("---");
         if(n[j]==3)
         printf("***");
    }





    if(cop[0].location_cop==5 && p==0)
     printf("HOL");
    if(cop[1].location_cop==5&& p==0)
     printf("WAT");
    if(cop[2].location_cop==5 && p==0)
     printf("TOB");
     if(cop[0].location_cop!=5 && cop[1].location_cop!=5 && cop[2].location_cop!=5 && p==0)
         printf("   ");


  if(cop[0].location_cop==7 && p==6)
     printf("HOL");
  if(cop[1].location_cop==7&&p==6)
     printf("WAT");
  if(cop[2].location_cop==7&& p==6)
     printf("TOB");
  if(cop[0].location_cop!=7 && cop[1].location_cop!=7 && cop[2].location_cop!=7 && p==6)
        printf("   ");


    if(cop[0].location_cop ==6 && p==3)
     printf("HOL");
    if(cop[1].location_cop ==6 && p==3)
     printf("WAT");
    if(cop[2].location_cop==6  && p==3)
     printf("TOB");
     if(cop[0].location_cop!=6 && cop[1].location_cop!=6 && cop[2].location_cop!=6 && p==3)
        printf("   ");
   /* if(cop[0].location_cop==5)
     printf("HOL");
   else if(cop[1].location_cop==5)
     printf("WAT");
  else if(cop[2].location_cop==5)
     printf("TOB");
     else
        printf("   ");*/


    printf("\n");

    for(int k=0;k<3;k++)
    {printf("   ");
     for(int j=p;j<p+3;j++)
         {printf("   ");
          printf(" ");
        if(n[j]==1 || n[j]==2 || n[j]==3)
        {
            printf("|");
        }
        if(n[j]==4)
         {
           printf("*");
         }
         printf(" ");

     printf("   ");

    }
    printf("\n");}

    printf("\n");
    p=p+3;
    }


    for(int i=10;i>=8;i--)
    {printf("      ");
  if(cop[0].location_cop==i)
     printf("HOL");
   else if(cop[1].location_cop==i)
     printf("WAT");
  else if(cop[2].location_cop==i)
     printf("TOB");
     else
        printf("   ");}

        printf("\n");

}













