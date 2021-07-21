#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>

struct tile{
  char name[10];
  int location;
  int direction;
  int hourglass;
  int hide_identity;//When Mr. Jack selects a tile in the action lens
  int way; //Used in the intuition phase and lens
  int mr_jack;//The tile chosen for Mr. Jack

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
 int location_cop;//it has twelve modes
};
struct token cop[3];



struct action{
 char name[2][10];

};
struct action state[4];

int random_action_card[4];
int kk=0; //when the user wants to rotate a card twice in one round.
int check2[4];//when the user wants to rotate a card twice in one round.

int input_repeat_bug[4];//It is for the input bug, that when selecting the action, the user does not enter the used action
int xx=0;//Control for input_repeat_bug

void list_set_next();
void identity_tile();
void identity_cop();
void identity_action();
int hourglass(char *);
int hourglass1=0;
int location();//use in identity_tile
int direction();//use in identity_tile
void random_action();
void print();
void function(int);
void play_action_chase(struct action state1,int number,int actor);//the first phase,the chase section
int number_tile=9;
int way1=0;
int round=1;
int actor_Mr_jack=0;
int actor_cop=1;

int number_state[4];//for function ,for better print
int first=1;//for clear number_state[4] in function

int location_mr_jack;


// next phase -> Intuition
void ways_pos();
void ways_neg();
void seen();
void reverse_seen();
void end();

//option game
void new_game();
void play_game();
void save_game(int);
void load_game();

int main()
{printf("Welcome to Mr. Jack\n");
while(1)
{printf("1- New Game\n2- Load Game \n3- Exit\n");
int ans;
fflush(stdin);
scanf("%d",&ans);
  if(ans==1)
    new_game();
  if(ans==2)
    load_game();
  if(ans==3)
    return 0;
}

}





void new_game()
{
identity_tile();
identity_cop();
identity_action();
random_action();

print();
printf("\n\n");
 //Mr.jack?
srand(time(0)*time(0));
//I want it to be non-linear because if it is linear i have the possibility of repeating the name of the Mr jack in every game
location_mr_jack=rand()%9+1;
struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
        if(counter->member.location==location_mr_jack)
          {counter->member.mr_jack=1;
          printf("Mr.jack is :%s\n",counter->member.name);}


        int q=0;
        play_game(q);

}

void load_game()
{  char name_game[100][100];
   FILE *p=fopen("name_game","r");
   if(p==NULL)
     {
       printf("No saved recent games\n");
       return;
     }
     int i=0;

     while(fgets(name_game[i],100,p) != NULL)
         i++;

       fclose(p);
       printf("Choose game :\n");
       for(int j=0;j<i;j++)
        printf("%d\t%s",j+1,name_game[j]);

       printf("Please enter the name correctly.\n");
       char address[100];
       scanf("%s",address);
       FILE *qq=fopen(address,"r");
       if(qq==NULL)
        {
           printf("The name entered is incorrect\n");
           return ;
        }
        int round1;
         fscanf(qq,"%d",&round1);
        fscanf(qq,"%d",&round);

for (int i=0;i<9;i++)
{fscanf(qq,"%s",member1.name);
fscanf(qq,"%d",&member1.location);
fscanf(qq,"%d",&member1.direction);
fscanf(qq,"%d",&member1.hourglass);
fscanf(qq,"%d",&member1.hide_identity);
fscanf(qq,"%d",&member1.way);
fscanf(qq,"%d",&member1.mr_jack);

list1 =fill_list(member1);
       if(i==0)
            head=list1;
     list_set_next();
    }
   for(int i=0;i<3;i++)
   {fscanf(qq,"%s",cop[i].name);
    fscanf(qq,"%d",&cop[i].location_cop);
   }

   fscanf(qq,"%d",&hourglass1);
   int r=0;
     if(round==1)
      {fscanf(qq,"%d",&random_action_card[0]);
       fscanf(qq,"%d",& random_action_card[1]);
       fscanf(qq,"%d",&random_action_card[2]);
       fscanf(qq,"%d",&random_action_card[3]);

       fscanf(qq,"%d",&check2[0]);
       fscanf(qq,"%d",&check2[1]);
       fscanf(qq,"%d",&check2[2]);
       fscanf(qq,"%d",&check2[3]);

        r++;
      }

fclose(qq);


int actor_Mr_jack=0;
int actor_cop=1;

identity_action();
if(r==0)
  random_action();


print();
printf("\n\n");



if(round==1)
 round++;
 else
    {round--;
    round1++;
    }


  play_game(round1);


}

void play_game(int q)
{
int p=q;
//game
for(q;q<4;q++)
{
if(p!=q)
 round=1;
first=1;
if(p==0 || p!=q || round==1)
 {for(int i=0;i<4;i++)
    check2[i]=0;
 }
 for(int i=0;i<4;i++)
    number_state[i]=0;
 for(int i=0;i<4;i++)
    input_repeat_bug[i]=0;
if(q!=p)
 random_action();
 xx=0;//control for input_repeat_bug



while(round<=2)
{

    for(int i=0;i<4;i++)
    input_repeat_bug[i]=0;


if(round==1)
 {printf("round :%d\n",2*q+round);
    for(int i=0;i<4;i++)
   printf("%d\t%s\n",i+1,state[i].name[random_action_card[i]]);
        xx=0;
        printf("play detectives\(Enter number plz\):\n");
    function(actor_cop);
        xx++;
        printf("play Mr.jack\(Enter number plz\):\n");
    function(actor_Mr_jack);
        xx++;
        printf("play Mr.jack\(Enter number plz\):\n");
    function(actor_Mr_jack);
        xx++;
        printf("play detectives\(Enter number plz\):\n");
   function(actor_cop);

 ways_pos();
  seen();
  struct node *counter1;
    for(counter1=head;counter1!= NULL ;counter1=counter1->next)
        if(counter1->member.way==1)
           counter1->member.way=2;
    print();


    int b=0;
    struct node *counter22;
    for(counter22=head;counter22!= NULL ;counter22=counter22->next)
        if(counter22->member.way==2)
          b++;
    if(b==8)
     {printf("detectives are win. \nfind Mr.jack.\nEnd.\n");
      sleep(8000);
      system("cls");
     return ;}

    if(hourglass1>=6)
   {printf("Mr.jack wins because he has 6 hourglasses.\nEnd.\n");
    sleep(8000);
    system("cls");
    return ;
    }

   printf("Do you want to save the game?(if yes enter 1 else enter 0)\n");
   int ans1;
   scanf("%d",&ans1);
   if(ans1==1)
     {save_game(q);
      system("cls");
      printf("The game was successfully saved.\n");
      return ;}
 round++;
continue;

 }

if(round%2==0)
  {printf("round :%d\n",2*q+round);
    for(int i=0;i<4;i++)
     printf("%d\t%s\n",i+1,state[i].name[1-random_action_card[i]]);
          xx=0;
          printf("play Mr.jack\(Enter number plz\):\n");
        function(actor_Mr_jack);
          xx++;
          printf("play detectives\(Enter number plz\):\n");
     function(actor_cop);
          xx++;
          printf("play detectives\(Enter number plz\):\n");
     function(actor_cop);
          xx++;
         printf("play Mr.jack\(Enter number plz\):\n");
     function(actor_Mr_jack);

     ways_pos();
  seen();
  struct node *counter1;
    for(counter1=head;counter1!= NULL ;counter1=counter1->next)
        if(counter1->member.way==1)
           counter1->member.way=2;
    print();
    int b=0;
    struct node *counter22;
    for(counter22=head;counter22!= NULL ;counter22=counter22->next)
        if(counter22->member.way==2)
          b++;
    if(b==8)
     {printf("detectives are win. \nfind Mr.jack.\nEnd.\n");
      sleep(10);
      system("cls");
     return ;}

    if(hourglass1>=6)
   {printf("Mr.jack wins because he has 6 hourglasses.\nEnd.\n");
    sleep(10);
    system("cls");
    return ;
    }
 printf("Do you want to save the game?(if yes enter 1 else enter 0)\n");
   int ans1;
   scanf("%d",&ans1);
   if(ans1==1)
     {save_game(q);
      system("cls");
      printf("The game was successfully saved.\n");
      return ;}
     round++;
     continue;
     }
}}
 ways_pos();
 seen();
 struct node *counter2;
    for(counter2=head;counter2!= NULL ;counter2=counter2->next)
        if(counter2->member.way==1)
           counter2->member.way=2;
   end();




}


void save_game(int q)
{ char address[100];
int control=0;//for control game names
 char check_address[100][100];

 FILE *fq=fopen("name_game","a+");
   if(fq==NULL)
   { printf("Cannot open file\n");
    return;
   }

   while(fgets(check_address[control],100,fq) != NULL)
    control++;

 int j;
 printf("Enter the name of the game to save :\n");
 do{j=1;
  fflush(stdin);
  scanf("%s",address);

  for(int i=0;i<control;i++)
    if(strcmp(address,check_address[i])==0)
     {printf("This name exists.\nPlease enter another name.\n");
       j=0;
     }

  }while(j==0);
strcpy(check_address[control],address);
fprintf(fq,"%s\n",check_address[control]);
fclose(fq);





  FILE *fp=fopen(address,"w");
if(fp == NULL){
    printf("Cannot open file\n");
     return ;
       }

       fprintf(fp,"%d\n",q);
       fprintf(fp,"%d\n",round);

    struct node *counter;
    for(counter=head;counter!= NULL; counter= counter ->next)
         fprintf(fp,"%s %d %d %d %d %d %d\n",counter->member.name,counter->member.location,counter->member.direction,counter->member.hourglass,counter->member.hide_identity,counter->member.way,counter->member.mr_jack);

    for(int k=0;k<3;k++)
    fprintf(fp,"%s %d\n",cop[k],cop[k].location_cop);
    fprintf(fp,"%d\n",hourglass1);

    if(round==1)
      {fprintf(fp,"%d\n",random_action_card[0]);
        fprintf(fp,"%d\n",random_action_card[1]);
        fprintf(fp,"%d\n",random_action_card[2]);
        fprintf(fp,"%d\n",random_action_card[3]);

        fprintf(fp,"%d\n",check2[0]);
        fprintf(fp,"%d\n",check2[1]);
        fprintf(fp,"%d\n",check2[2]);
        fprintf(fp,"%d\n",check2[3]);

      }

    fclose(fp);

 return ;

}


void identity_tile()
{
  for (int i=0;i<9;i++)
{
strcpy(member1.name,names[i]);
member1.location=location();
member1.direction=direction();
if(member1.location==1) //Because the closed path must be towards the detectives
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
   {counter->member.hide_identity=0;
    counter->member.way=0;
    counter->member.mr_jack=0;
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
  int input_repeat_bug1;
    do{
    input_repeat_bug1=0;

    scanf("%d",&number);

    input_repeat_bug[xx]=number;
    for(int i=xx-1;i>=0;i--)
        if(number==input_repeat_bug[i])
           input_repeat_bug1=1;

     if(input_repeat_bug1==1)
        printf("This action has been used before.\nEnter again plz.\n");

    if(number>4 || number<1)
        printf("Error!!!\nEnter again plz.\n");
     }while(number>4 || number<1 || input_repeat_bug1==1);
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
    {int k=0;
     char name_lens[9][10];
    struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
        //if(counter->member.way!=2)
          if(counter->member.hide_identity!=1)
            if(counter->member.mr_jack!=1)
             {strcpy(name_lens[k],counter->member.name);
             k++;
             }
    int m;
   srand(time(0));
    m=rand()%k;
    for(counter=head;counter!= NULL ;counter=counter->next)
     { if(strcmp(name_lens[m],counter->member.name)==0)
           {counter->member.hide_identity=1;
            printf("The person that Mr. Jack is hiding using this action : %s\n",name_lens[m]);
            hourglass1+=counter->member.hourglass;
            printf("hourglass for Mr.jack is : %d\n",hourglass1);

           }
     }
      print();
      return ;

    }
     if(actor==1)
      {int k=0;
     char name_lens1[9][10];
    struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
          if(counter->member.hide_identity!=1)
            if(counter->member.mr_jack!=1)
             {strcpy(name_lens1[k],counter->member.name);
             k++;
             }
    int m;
    srand(time(0));
    m=rand()%k;
    for(counter=head;counter!= NULL ;counter=counter->next)
     { if(strcmp(name_lens1[m],counter->member.name)==0)
           {counter->member.hide_identity=1;
            counter->member.way=2;
            printf("The person selected in this action %s\n",name_lens1[m]);
            }


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
    {printf("Which card do you choose to rotate?\(Enter number 1 or 2 ... 9\)\n");
     int rotate;
      int check22;
     do{ check22=1;
         fflush(stdin);
         scanf("%d",&rotate);
         check2[kk]=rotate;
         check2[kk+2]=round;
         if(kk==1)
         {if(check2[3]==check2[2])
             {if(check2[1]==check2[0])
               {printf("Error!!!\nEnter again plz.\nYou can't rotate a card twice in one round.\n");
                 check22=0;}}
            kk=0;
         }
        if(rotate<1 || rotate>9)
              printf("Error!!!\nEnter again plz.\nInvalid number.\n");

       }while(check22==0 || rotate<1 ||rotate>9);
    kk++;
    printf("How much do you want rotate?\n1\)90  2\)180 3\)270\n\(enter 1 or 2 or 3\)\n");
     int m;
     do{
        scanf("%d",&m);
        if(m>3 || m<1)
            printf("Error!!!\nEnter again plz.\n");
       }while(m>3 || m<1);

    struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
        {if(counter->member.location == rotate)
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
     {printf("which cards do you want to swap?\(enter number 1 or 2 ... 9\)\n");
      int swap1;
      int swap2;
   while(1)
    {do{ fflush(stdin);
     scanf("%d",&swap1);
    if(swap1<1 ||swap1>9)
     printf("Error!!!\nEnter again plz.\nInvalid number.\n");
    }while(swap1<1 ||swap1>9);

 do{    fflush(stdin);
        scanf("%d",&swap2);
         if(swap2<1 ||swap2>9)
           printf("Error!!!\nEnter again plz.\n");
    }while(swap2<1 || swap2>9);
    if(swap1!=swap2)
        break;
     else
        printf("The two numbers entered are the same.\nEnter again plz.\n");

    }


 char location1[10],location2[10];
       struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
       {if(counter->member.location==swap1)
         strcpy(location1 , counter->member.name);

        if(counter->member.location==swap2)
          strcpy(location2,counter->member.name);
        }


     for(counter=head;counter!= NULL ;counter=counter->next)
       {if(strcmp(counter->member.name,location1)==0)
          counter->member.location=swap2;

        if(strcmp(counter->member.name,location2)==0)
          counter->member.location=swap1;
        }
       print();
       return;

     }
if(strcmp(state1.name[i],"cops")==0)
    {int m;
    if(actor==0)
     {printf("enter 1\)Holmes  2\)Watson 3\)Toby 4\)don't change \(Enter number 1 or 2 or 3 or 4\)\n");
        do{scanf("%d",&m);
            if(m>4 || m<1)
            printf("Wrong!!!\nEnter again:\n");
          }while(m>4 || m<1);
     }

      if(actor==1)
             {printf("enter 1\)Holmes  2\)Watson 3\)Toby \(Enter number 1 or 2 or 3 \) \n");
               do{scanf("%d",&m);
                   if(m>3 || m<1)
                     printf("Wrong!!!\nEnter again:\n");
                 }while(m>3 ||m<1);
             }

        if(m==1)
            {cop[0].location_cop+=1;
             if(cop[0].location_cop>12)
             cop[0].location_cop-=12;}

            if(m==2)
            {cop[1].location_cop+=1;
            if(cop[1].location_cop>12)
             cop[1].location_cop-=12;}
         if(m==3)
            {cop[2].location_cop+=1;
            if(cop[2].location_cop>12)
             cop[2].location_cop-=12;}


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
{ if(strcmp(name,"I_L")==0)
    return 0;
  if(strcmp(name,"J_B")==0)
     return 1;
  if(strcmp(name,"J_P")==0)
   return 1;
  if(strcmp(name,"J_S")==0)
   return 1;
  if(strcmp(name,"J_L")==0)
   return 1;
  if(strcmp(name,"Mad")==0)
   return 2;
  if(strcmp(name,"M_S")==0)
   return 1;
  if(strcmp(name,"S_G")==0)
   return 0;
  if(strcmp(name,"W_G")==0)
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
   for(int i=0;i<41;i++)
        printf("_");
        printf("\n");

for(int i=2;i<=4;i++)
    {printf("      ");
     int z=0;
  if(cop[0].location_cop==i)
     {printf("HOL");
    z++;
     }


    if(cop[1].location_cop==i)
     {if(z!=0)
      {printf("\n");
      if(i==2)
        printf("      ");
       if(i==3)
        printf("               ");
        if(i==4)
        printf("                        ");
      }

     printf("WAT");
     z++;
     }

   if(cop[2].location_cop==i)
     {if(z!=0)
      {printf("\n");
      if(i==2)
        printf("      ");
       if(i==3)
        printf("               ");
        if(i==4)
            printf("                        ");
      }printf("TOB");
     z++;
     }
     if(cop[0].location_cop!=i && cop[1].location_cop!=i && cop[2].location_cop!=i)
        printf("   ");
    }

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

   int e=0;


    if(cop[0].location_cop==1 && p==0)
     {printf("HOL");
     e++;}
     if(cop[1].location_cop==1&& p==0)
      if(e==0)
        {printf("WAT");
        e++;
        e++;
        }
    if(cop[2].location_cop==1 && p==0)
        if(e==0)
       {printf("TOB");
         }
     if(cop[0].location_cop!=1 && cop[1].location_cop!=1 && cop[2].location_cop!=1 && p==0)
         printf("   ");

  int e1=0;

  if(cop[0].location_cop==11 && p==6)
     {printf("HOL");
     e1++;}
  if(cop[1].location_cop==11&&p==6)
     if(e1==0)
         {printf("WAT");
         e1++;
         e1++;
         }
  if(cop[2].location_cop==11&& p==6)
    if(e1==0)
     printf("TOB");
  if(cop[0].location_cop!=11 && cop[1].location_cop!=11 && cop[2].location_cop!=11 && p==6)
        printf("   ");

int e2=0;
    if(cop[0].location_cop ==12 && p==3)
     {printf("HOL");
     e2++;}
    if(cop[1].location_cop ==12 && p==3)
        if(e2==0)
         {printf("WAT");
         e2++;
         e2++;
         }
    if(cop[2].location_cop==12  && p==3)
        if(e2==0)
          printf("TOB");
     if(cop[0].location_cop!=12 && cop[1].location_cop!=12 && cop[2].location_cop!=12 && p==3)
        printf("   ");

for(int j=p;j<p+3;j++)
        {if(n[j]==1)
         printf("***");
       if(n[j]==2 || n[j]==4||n[j]==3)
        printf("---");
    if(way2[j]==2)
        printf("   ");
     else
        printf("%s",m[j]);
if(n[j]==1||n[j]==2||n[j]==4)
         printf("---");
         if(n[j]==3)
         printf("***");
    }





    if(cop[0].location_cop==5 && p==0)
     printf("HOL ");
    if(cop[1].location_cop==5&& p==0)
     printf("WAT ");
    if(cop[2].location_cop==5 && p==0)
     printf("TOB ");
     if(cop[0].location_cop!=5 && cop[1].location_cop!=5 && cop[2].location_cop!=5 && p==0)
         printf("   ");


  if(cop[0].location_cop==7 && p==6)
     printf("HOL ");
  if(cop[1].location_cop==7&&p==6)
     printf("WAT ");
  if(cop[2].location_cop==7&& p==6)
     printf("TOB ");
  if(cop[0].location_cop!=7 && cop[1].location_cop!=7 && cop[2].location_cop!=7 && p==6)
        printf("   ");


    if(cop[0].location_cop ==6 && p==3)
     printf("HOL ");
    if(cop[1].location_cop ==6 && p==3)
     printf("WAT ");
    if(cop[2].location_cop==6  && p==3)
     printf("TOB ");
     if(cop[0].location_cop!=6 && cop[1].location_cop!=6 && cop[2].location_cop!=6 && p==3)
        printf("   ");


    printf("\n");
  if(e==1)
    {if(cop[1].location_cop==1&& p==0)
        {printf("WAT");
        e++;
        e++;
        }
    if(cop[2].location_cop==1 && p==0)
        if(e==1)
       {printf("TOB");
        }
     if(cop[1].location_cop!=1 && cop[2].location_cop!=1 && p==0)
         printf("   ");
    }

   if(e==2)
   {if(cop[2].location_cop==1 && p==0)
       {printf("TOB");
        }
     if(cop[2].location_cop!=1 && p==0)
         printf("   ");
     }



 if(e1==1)
    {if(cop[1].location_cop==11&& p==6)
        {printf("WAT");
        e1++;
        e1++;
        }
    if(cop[2].location_cop==11 && p==6)
        if(e1==1)
       {printf("TOB");

        }
     if(cop[1].location_cop!=11 && cop[2].location_cop!=11 && p==6)
         printf("   ");
    }
    if(e1==2)
   {if(cop[2].location_cop==11 && p==6)
       {printf("TOB");

        }
     if(cop[2].location_cop!=11 && p==6)
         printf("   ");
     }



if(e2==1)
    {if(cop[1].location_cop==12&& p==3)
        {printf("WAT");
        e2++;
        e2++;
        }
    if(cop[2].location_cop==12 && p==3)
        if(e2==1)
       {printf("TOB");
         //e++;
        }
     if(cop[1].location_cop!=12 && cop[2].location_cop!=12 && p==3)
         printf("   ");
    }

     if(e2==2)
   {if(cop[2].location_cop==12 && p==3)
       {printf("TOB");
         //e++;
        }
     if(cop[2].location_cop!=12 && p==3)
         printf("   ");
     }

if(e!=1 && e!=2 && e!=3 && p==0)
    printf("   ");
if(e1!=1 &&e1!=2 &&e1!=3 && p==6)
    printf("   ");
 if(e2!=1&& e2!=2 &&e2 !=3 && p==3)
    printf("   ");




  for(int k=0;k<3;k++)
    {if(k!=0 && k!=1)
        printf("   ");
    if(k==1 && e==3)
       {if(cop[2].location_cop==1 && p==0)
            printf("TOB");

       else
            printf("   ");}



    if(k==1 && e1==3)
       {if(cop[2].location_cop==11 && p==6)
            printf("TOB");

       else
            printf("   ");}



    if(k==1 && e2==3)
       {if(cop[2].location_cop==12 && p==3)
            printf("TOB");

       else
            printf("   ");}



    if(k==1 && e!=3 && p==0)
         printf("   ");

    if(k==1 && e1!=3 && p==6)
         printf("   ");

    if(k==1 && e2!=3 && p==3)
         printf("   ");


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




//next phase -> Intuition


void ways_pos()
{ int i;
struct node *counter;
struct node *counter01;
struct node *counter02;
   for(int j=0;j<3;j++)
 {
 if(cop[j].location_cop==1 || cop[j].location_cop==11 ||cop[j].location_cop==12)
    {
    if(cop[j].location_cop==1)
        i=1;
    if(cop[j].location_cop==11)
        i=7;
    if(cop[j].location_cop==12)
        i=4;

        for(counter=head;counter!= NULL ;counter=counter->next)
          {if(counter->member.location==i)
           {if(counter->member.direction!=1)
               {if(counter->member.way!=2)
                  counter->member.way=1;
                for(counter01=head;counter01!= NULL ;counter01=counter01->next)
                   {if(counter01->member.location==i+1)
                      {if(counter->member.direction!=3 && counter01->member.direction!=1)
                        {if(counter01->member.way!=2)
                          counter01->member.way=1;
                          for(counter02=head;counter02!= NULL ;counter02=counter02->next)
                           {if(counter02->member.location==i+2)
                             if(counter02->member.direction!=1 && counter01->member.direction!=3)
                                if(counter02->member.way!=2)
                                   counter02->member.way=1;


                           }
                           }}}}}}
      }







  if(cop[j].location_cop==2 || cop[j].location_cop==3 ||cop[j].location_cop==4)
    {if(cop[j].location_cop==2)
        i=1;
    if(cop[j].location_cop==3)
        i=2;
    if(cop[j].location_cop==4)
        i=3;

        for(counter=head;counter!= NULL ;counter=counter->next)
          {if(counter->member.location==i)
           {if(counter->member.direction!=2)
              {if(counter->member.way!=2)
                counter->member.way=1;
                for(counter01=head;counter01!= NULL ;counter01=counter01->next)
                   {if(counter01->member.location==i+3)
                      {if(counter01->member.direction!=2 && counter->member.direction!=4)
                        {if(counter01->member.way!=2)
                          counter01->member.way=1;
                          for(counter02=head;counter02!= NULL ;counter02=counter02->next)
                           {if(counter02->member.location==i+6)
                             if(counter02->member.direction!=2 && counter01->member.direction!=4)
                                if(counter02->member.way!=2)
                                    counter02->member.way=1;
                           }
                           }}}}}}
      }





if(cop[j].location_cop==5 || cop[j].location_cop==6 ||cop[j].location_cop==7)
    {if(cop[j].location_cop==5)
        i=3;
    if(cop[j].location_cop==6)
        i=6;
    if(cop[j].location_cop==7)
        i=9;

        for(counter=head;counter!= NULL ;counter=counter->next)
          {if(counter->member.location==i)
           {if(counter->member.direction!=3)
             {if(counter->member.way!=2)
                 counter->member.way=1;
                for(counter01=head;counter01!= NULL ;counter01=counter01->next)
                   {if(counter01->member.location==i-1)
                      {if(counter01->member.direction!=3 && counter->member.direction!=1)
                         {if(counter01->member.way!=2)
                             counter01->member.way=1;
                          for(counter02=head;counter02!= NULL ;counter02=counter02->next)
                           {if(counter02->member.location==i-2)
                             if(counter02->member.direction!=3 && counter01->member.direction!=1)
                                if(counter02->member.way!=2)
                                    counter02->member.way=1;
                           }
                           }}}}}}
      }






 if(cop[j].location_cop==8 || cop[j].location_cop==9 ||cop[j].location_cop==10)
    {if(cop[j].location_cop==8)
        i=9;
    if(cop[j].location_cop==9)
        i=8;
    if(cop[j].location_cop==10)
        i=7;

        for(counter=head;counter!= NULL ;counter=counter->next)
          {if(counter->member.location==i)
           {if(counter->member.direction!=4)
               {if(counter->member.way!=2)
                   counter->member.way=1;
                for(counter01=head;counter01!= NULL ;counter01=counter01->next)
                   {if(counter01->member.location==i-3)
                      {if(counter01->member.direction!=4 && counter->member.direction!=2)
                         {if(counter01->member.way!=2)
                             counter01->member.way=1;
                          for(counter02=head;counter02!= NULL ;counter02=counter02->next)
                           {if(counter02->member.location==i-6)
                             if(counter02->member.direction!=4 && counter01->member.direction!=2)
                                if(counter02->member.way!=2)
                                    counter02->member.way=1;
                           }
                           }}}}}}
      }


 }



}



void seen()
{ int i=1;
   struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
        {if(counter->member.way==1)
          {if(counter->member.mr_jack==1)
             {printf("jack can be seen by detectives.\n");
              reverse_seen();
              ways_neg();
             i=0;
             break;
             }
          }
          i++;

         }

        if(i!=0)
            {hourglass1++;
            printf("jack can not be seen by detectives.\n");
            printf("hourglass for jack is : %d\n",hourglass1);
            }












}
void reverse_seen()
{
 struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
        if(counter->member.way==0)
           counter->member.way=1;
}

void ways_neg()
{int i;
struct node *counter;
struct node *counter01;
struct node *counter02;
  for(int j=0;j<3;j++)
  {
    if(cop[j].location_cop==1 || cop[j].location_cop==11 ||cop[j].location_cop==12)
    {if(cop[j].location_cop==1)
        i=1;
    if(cop[j].location_cop==11)
        i=7;
    if(cop[j].location_cop==12)
        i=4;

        for(counter=head;counter!= NULL ;counter=counter->next)
          {if(counter->member.location==i)
           {if(counter->member.direction!=1)
               {if(counter->member.way!=2)
                   counter->member.way=0;
                for(counter01=head;counter01!= NULL ;counter01=counter01->next)
                   {if(counter01->member.location==i+1)
                      {if(counter01->member.direction!=1 && counter->member.direction!=3)
                         {if(counter01->member.way!=2)
                             counter01->member.way=0;
                          for(counter02=head;counter02!= NULL ;counter02=counter02->next)
                           {if(counter02->member.location==i+2)
                             if(counter02->member.direction!=1 && counter01->member.direction!=3)
                                if(counter02->member.way!=2)
                                   counter02->member.way=0;
                           }
                           }}}}}}
      }







  if(cop[j].location_cop==2 || cop[j].location_cop==3 ||cop[j].location_cop==4)
    {if(cop[j].location_cop==2)
        i=1;
    if(cop[j].location_cop==3)
        i=2;
    if(cop[j].location_cop==4)
        i=3;

        for(counter=head;counter!= NULL ;counter=counter->next)
          {if(counter->member.location==i)
           {if(counter->member.direction!=2)
               {if(counter->member.way!=2)
                   counter->member.way=0;
                for(counter01=head;counter01!= NULL ;counter01=counter01->next)
                   {if(counter01->member.location==i+3)
                      {if(counter01->member.direction!=2 && counter->member.direction!=4)
                         {if(counter01->member.way!=2)
                             counter01->member.way=0;
                          for(counter02=head;counter02!= NULL ;counter02=counter02->next)
                           {if(counter02->member.location==i+6)
                             if(counter02->member.direction!=2 && counter01->member.direction!=4)
                                if(counter02->member.way!=2)
                                   counter02->member.way=0;
                           }
                           }}}}}}
      }





if(cop[j].location_cop==5 || cop[j].location_cop==6 ||cop[j].location_cop==7)
    {if(cop[j].location_cop==5)
        i=3;
    if(cop[j].location_cop==6)
        i=6;
    if(cop[j].location_cop==7)
        i=9;

        for(counter=head;counter!= NULL ;counter=counter->next)
          {if(counter->member.location==i)
           {if(counter->member.direction!=3)
               {if(counter->member.way!=2)
                   counter->member.way=0;
                for(counter01=head;counter01!= NULL ;counter01=counter01->next)
                   {if(counter01->member.location==i-1)
                      {if(counter01->member.direction!=3 && counter->member.direction!=1)
                         {if(counter01->member.way!=2)
                            counter01->member.way=0;
                          for(counter02=head;counter02!= NULL ;counter02=counter02->next)
                           {if(counter02->member.location==i-2)
                             if(counter02->member.direction!=3 &&counter01->member.direction!=1)
                                 if(counter02->member.way!=2)
                                   counter02->member.way=0;
                           }
                           }}}}}}
      }






 if(cop[j].location_cop==8 || cop[j].location_cop==9 ||cop[j].location_cop==10)
    {if(cop[j].location_cop==8)
        i=9;
    if(cop[j].location_cop==9)
        i=8;
    if(cop[j].location_cop==10)
        i=7;

        for(counter=head;counter!= NULL ;counter=counter->next)
          {if(counter->member.location==i)
           {if(counter->member.direction!=4)
               {if(counter->member.way!=2)
                   counter->member.way=0;
                for(counter01=head;counter01!= NULL ;counter01=counter01->next)
                   {if(counter01->member.location==i-3)
                      {if(counter01->member.direction!=4 && counter->member.direction!=2)
                         {if(counter01->member.way!=2)
                             counter01->member.way=0;
                          for(counter02=head;counter02!= NULL ;counter02=counter02->next)
                           {if(counter02->member.location==i-6)
                             if(counter02->member.direction!=4 && counter01->member.direction!=2)
                                if(counter02->member.way!=2)
                                    counter02->member.way=0;
                           }
                           }}}}}}
      }








}}


void end()
{int n=0;
struct node *counter;
    for(counter=head;counter!= NULL ;counter=counter->next)
        if(counter->member.way==2)
         n++;
   if(n==8)
        printf("Detectives is win.\nEnd\n");
   else
    printf("Mr jack is win.\nEnd\n");




}








