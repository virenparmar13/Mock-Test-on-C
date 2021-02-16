#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
struct Node
{
	char q[200],op1[30],op2[30],op3[30],op4[30],ans;
	struct Node *next;
};
typedef struct Node* subnode;
typedef struct Node dsubnode;
struct headernode
{
	int count;
	subnode next;
};
typedef struct headernode* hnode;
typedef struct headernode dhnode;
hnode createh()
{
	hnode ptr=(hnode)malloc(sizeof(dhnode));
	return ptr;
}
subnode newnode(subnode prev)
{
	subnode ptr=(subnode)malloc(sizeof(dsubnode));
	prev->next = ptr;
	return ptr;
}
void freenode(subnode curr, subnode prev)
{
	prev->next = curr->next;
	free(curr);

}
hnode buildlist(FILE *fp)
{
	int i,j;
	hnode start = createh();
	subnode ptr = (subnode)malloc(sizeof(dsubnode));
	start->next = ptr;
	fgets(ptr->q,200,fp);
	fgets(ptr->op1,30,fp);
	fgets(ptr->op2,30,fp);
	fgets(ptr->op3,30,fp);
	fgets(ptr->op4,30,fp);
	ptr->ans = fgetc(fp);
	fgetc(fp);
	for(i=0;!(feof(fp));i++)
	{
		ptr->next = newnode(ptr);
		ptr = ptr->next;
		fgets(ptr->q,200,fp);
		fgets(ptr->op1,30,fp);
		fgets(ptr->op2,30,fp);
		fgets(ptr->op3,30,fp);
		fgets(ptr->op4,30,fp);
		ptr->ans = fgetc(fp);
		fgetc(fp);
	}
	start->count = i;
	return start;
}
int genrand(int upper)
{
	int num = (rand() % (upper))+1;
	return num;
}
void newuser()
{
	FILE *fp;
	int i;
	char c,len[2];
	system("cls");
	printf("\nThis distribution of software includes one user license which you will be now creating.");
	printf("\n\n\nEnter username(max 20 characters) : ");
	fp = fopen("userpass.txt","w");
	for(i=0;;i++)
	{
		c=getch();
		printf("%c",c);
		fputc(c,fp);
		if(c=='\r')
		{
			c='\n';
			fputc(c,fp);
			break;
		}
		if(i==19)
		{
			c='\n';
			fputc(c,fp);
			break;
		}
	}
	printf("Enter password(max 20 characters) : ");
	for(;;)
	{
		c=getch();
		if(c=='\r')
		{
			c='\n';
			fputc(c,fp);
			break;
		}
		printf("*",c);
		fputc(c,fp);
		if(i==19)
		{
			c='\n';
			fputc(c,fp);
			break;
		}
	}
	fclose(fp);
}
void login()
{
	char username[20];
	char userpwd[8];
	int i;
	FILE *fp;
	fp = fopen("userpass.txt","r");
	if(fp== NULL)
	{
		newuser();
	}
	struct node
	{
		char arr[20];
		struct node *next;
	};
	struct node *user,*pass;
	user = (struct node *)malloc(sizeof(struct node));
	pass = (struct node *)malloc(sizeof(struct node));
	user->next=pass;
	fgets(user->arr,21,fp);
	fgets(pass->arr,21,fp);
	for(i=0;i<=20;i++)
		if(user->arr[i]=='\n')
		{
			user->arr[i]='\0';
			break;
		}
	for(i=0;i<=20;i++)
		if(user->next->arr[i]=='\n')
		{
			user->next->arr[i]='\0';
			break;
		}
	system("cls");
	printf("Enter your username : ");
	scanf("%s",username);
	printf("Enter your password : ");
	for(i=0;;i++)
	{
		userpwd[i]=getch();
		if(userpwd[i]=='\r')
			break;
		printf("*");
	}
	userpwd[i]='\0';
	if(!strcmp(username,user->arr) && !strcmp(userpwd,user->next->arr))
	{
		printf("\n\nLogged In Successfully");
	}
	else
	{
		printf("\n\nIncorrect Username or Password!");
		getch();
		fclose(fp);
		exit(0);
	}
	getch();
	fclose(fp);
}
subnode getptr(int num, hnode start)
{
	int i;
	subnode ptr = start->next;
	for(i=2;i<=num;i++)
	{
		ptr = ptr->next;
	}
	return ptr;
}
int calct(clock_t t)
{
	clock_t ta;
	ta = clock();
	int ttaken = ((int)(ta-t));
	return ttaken;
}
void main()
{
	int sub,num,reply,i;
	FILE *fp;
	login();
	clrscr();
	printf("Enter the number of the subject you want to give test on :-\n1. sub1\n2. sub2\n\n");
	scanf("%d",&sub);
	if(sub==1)
		fp=fopen("sub1.txt","r");
	else if(sub==2)
		fp=fopen("sub2.txt","r");
	else
	{
		printf("Invalid Input!");
		getch();
		exit(0);
	}
	if(fp==NULL)
	{
		clrscr();
		printf("Question set not found for selected subject!");
		getch();
		exit(0);
	}
	srand(time(0));
	hnode head = buildlist(fp);
	fclose(fp);
	subnode ptr;
	clrscr();
	printf("INSTRUCTIONS :-\n\n1. A total of 10 questions will be asked, each of 10 marks.\n2. Each question should be attempted within a minute failing which no marks would be credited for that particular question.\n3. Attempting all questions is compulsory.\n4. You cannot jump between questions\n\npress any key to begin the test...");
	char c = getch();
	if(c=='e') exit(0);
	clrscr();
	int marks = 0; clock_t start,end;double ttaken;
	for(i=1;i<=10;i++)
	{
		num = genrand((head->count)-1);
		ptr = getptr(num,head);
		printf("%s %s %s %s %s \n\nAnswer : ",ptr->next->q,ptr->next->op1,ptr->next->op2,ptr->next->op3,ptr->next->op4);
		start = clock();
		printf("");
		char reply=getch();
		int ttaken = calct(start);
		printf("%c",reply);
		if(ttaken>=60)
		{
			printf("\n\nToo Late!\nCorrect answer is : %c",ptr->next->ans);
			getch();
			clrscr();
		}
		else if(reply == ptr->next->ans)
		{
			printf("\n\nCorrect answer!");
			marks = marks+10;
			getch();
			clrscr();
		}
		else
		{
			printf("\n\nThe correct answer is : %c",ptr->next->ans);
			getch();
			clrscr();
		}
		freenode(ptr->next,ptr);
		--(head->count);
	}

	printf("\nYou scored %d out of 100",marks);
	getch();
	exit(0);
}
