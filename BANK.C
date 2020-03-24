/*
	Title: BANK MANAGEMENT SYSTEM
	Day 1: 8th May 2017
	By:  Anisha Rauniyar
	Last Update: 11th May 2017
*/

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>

void menu();
void add();
void list();
void modify();
void deposit();
void search();
void del();
void withdraw();
void eror(char *);
void layout(char *);

struct customer
{
	int amt;
	char num[13], fname[20], lname[20], adrs[25], accno[25];
}	bcstmr,cstmr,bstruct;

int i,j,dly=0,gd=DETECT,gm;
FILE *fp, *tp;
char no[13], ero[]="Error! Please try again...", ffail[]="Failed To Open File...!", noexist[]="Number Already Exist..!";

void main()
{
	char task,welcome[]="Welcome To Bank Management System",u[20],p[20],un[]="ADMIN", pw[]="password", noaccess[]="Access Denied!";
	clrscr();
	textcolor(10);
	/*
	gotoxy(25,11); cprintf("User Name: ");
	scanf("%s",&u);
	gotoxy(25,13); cprintf("Password: ");
	scanf("%s",&p);
	if(strcmp(u,un)!=0 || strcmp(pw,p)!=0)
	{
		clrscr();
		gotoxy(25,12);
		cprintf("%s",noaccess);
		getch();
		exit(0);
	}
	*/
	gotoxy(36,13);
	cprintf("Loading...");
	for(i=0;i<=100;i++)
	{
		gotoxy(38,15);
		cprintf("%d %%\b\b\b",i);
		gotoxy(37-i/3,15);
		cprintf("_");
		gotoxy(41+i/3,15);
		cprintf("_");
		delay(20);
	}
	delay(50);
	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
	setcolor(14);
	cleardevice();
	settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
	outtextxy(55,200,welcome);
	delay(1400);
	menu();
}

void menu()
{
	char task,code[20],p[]="CONFIRM",title[]="Main Menu";
	cleardevice();
	layout(title);
	fflush(stdin);
	setcolor(10);
	rectangle(120,130,400,145);
	setfillstyle(1,8);
	floodfill(121,131,10);
	rectangle(120,155,400,170);
	floodfill(121,156,10);
	rectangle(120,180,400,195);
	rectangle(120,205,400,220);
	rectangle(120,230,400,245);
	rectangle(120,255,400,270);
	rectangle(120,280,400,295);
	rectangle(120,305,400,320);
	delay(dly); outtextxy(130,135,"1 -  (A)dding new account.");
	delay(dly); outtextxy(130,160,"2 -  (L)ist of account.");
	delay(dly); outtextxy(130,185,"3 -  (M)odifying account.");
	delay(dly); outtextxy(130,210,"4 -  (C)ash deposit.");
	delay(dly); outtextxy(130,235,"5 -  (S)earching account.");
	delay(dly); outtextxy(130,260,"6 -  (D)eleting account.");
	delay(dly); outtextxy(130,285,"7 -  (W)ithdraw.");
	delay(dly); outtextxy(130,310,"8 -  (E)xit.");
	delay(dly); outtextxy(175,370,"Enter your choice(1-8): ");

	gotoxy(54,24); scanf("%c",&task);
	cleardevice();
	switch(task)
	{
		case 'a':
		case 'A':
		case '1':
		{
			add();
			break;
		}
		case 'l':
		case 'L':
		case '2':
		{
			list();
			break;
		}
		case 'm':
		case 'M':
		case '3':
		{
			modify();
			break;
		}
		case 'c':
		case 'C':
		case '4':
		{
			deposit();
			break;
		}
		case 's':
		case 'S':
		case '5':
		{
			search();
			break;
		}
		case 'd':
		case 'D':
		case '6':
		{
			del();
			break;
		}
		case 'w':
		case 'W':
		case '7':
		{
			withdraw();
			break;
		}

		case 'e':
		case 'E':
		case '8':
		{
			char thank[]="Thank you for using this software!";
			cleardevice();
			settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
			outtextxy(55,200,thank);
			delay(1400);
			closegraph();
			exit();
			break;
		}
		case '#':
		{
			cleardevice();
			setcolor(RED);
			outtextxy(100,190,"Are you sure you want to delete all accounts?");
			outtextxy(100,215,"Enter conformation code: ");
			gotoxy(45,15); scanf("%s",&code);
			cleardevice();
			if(strcmp(code,p)==0)
			{
				remove("Bank.dat");
				remove("b.dat");
				outtextxy(200,200,"All Accounts Deleted!");
			}
			else
				outtextxy(200,200,"Wrong Code!");
			getch();
			menu();
			break;
		}
		default:
			eror(ero);
	}
}

void add()
{
	char more,no[13],title[]="Add Accounts";
	fp=fopen("Bank.dat","a+");
	if(fp==NULL)
		eror(ffail);
	cleardevice();
	layout(title);
	gotoxy(20,10); printf("Enter customer account number:\t");
	scanf("%s",&no);
	while(fread(&cstmr,sizeof(cstmr),1,fp)==1)
	{
		if(strcmp(cstmr.accno,no)==0)
		{
			fclose(fp);
			eror(noexist);
		}
	}
	strcpy(cstmr.accno,no);
	gotoxy(20,12); printf("Enter customer first name:\t");
	scanf("%s",&cstmr.fname);
	gotoxy(20,14); printf("Enter customer last name:\t");
	scanf("%s",&cstmr.lname);
	gotoxy(20,16); printf("Enter customer address:\t");
	scanf("%s",&cstmr.adrs);
	gotoxy(20,18); printf("Enter customer phone number:\t");
	scanf("%s",&cstmr.num);
	gotoxy(20,20); printf("Enter customer amount(Rs.):\t");
	scanf("%d",&cstmr.amt);
	fflush(stdin);
	gotoxy(22,24);printf("Any more records?(Y/N)\t");
	scanf("%c",&more);
	fwrite(&cstmr,sizeof(cstmr),1,fp);
	fclose(fp);
	if(more=='Y'||more=='y')
		add();
	menu();
}

void list()
{
	char title[]="List of Accounts",a[10];
	cleardevice();
	layout(title);
	fp=fopen("Bank.dat","r+");
	if(fp==NULL)
		eror(ffail);
	delay(dly); outtextxy(88,125,"SN");
	delay(dly); outtextxy(115,125,"Name");
	delay(dly); outtextxy(213,125,"Address");
	delay(dly); outtextxy(333,125,"A/C no. ");
	delay(dly); outtextxy(400,125,"Number");
	delay(dly); outtextxy(513,125,"Amount");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	i=10;
	while(fread(&cstmr,sizeof(cstmr),1,fp)>0)
	{
		sprintf(a,"%d",i/10);
		delay(dly); outtextxy(92,140+i,a);
		delay(dly); outtextxy(115,140+i,cstmr.fname);
		delay(dly); outtextxy(213,140+i,cstmr.adrs);
		delay(dly); outtextxy(333,140+i,cstmr.accno);
		delay(dly); outtextxy(400,140+i,cstmr.num);
		sprintf(a,"%d",cstmr.amt);
		delay(dly); outtextxy(513,140+i,a);
		i=i+10;
		if(i>200)
		{
			outtextxy(175,165+i,"Press any key for more..(x for exit)");
			if(getch()=='x')
			menu();
			cleardevice();
			layout(title);
	delay(dly); outtextxy(88,125,"SN");
	delay(dly); outtextxy(115,125,"Name");
	delay(dly); outtextxy(213,125,"Address");
	delay(dly); outtextxy(333,125,"A/C no. ");
	delay(dly); outtextxy(400,125,"Number");
	delay(dly); outtextxy(513,125,"Amount");
			settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
			i=10;
		}
	}
	outtextxy(150,375,"Press any key to go back to the Main Menu.");
	fclose(fp);
	getch();
	menu();
}

void modify()
{
	char sav,title[]="Modify Accounts";
	fp=fopen("Bank.dat","r+");
	remove("b.dat");
	tp=fopen("b.dat","w");
	if(fp==NULL)
		eror(ffail);
	access();
	cleardevice();
	layout(title);
	gotoxy(18,9); printf("Enter account number to modify:\t");
	scanf("%s",&no);
	while(fread(&cstmr,sizeof(cstmr),1,fp)==1)
	{
		if(strcmp(no,cstmr.accno)==0)
		{
			gotoxy(25,10); printf("----------Old  Account----------");
			gotoxy(20,11); printf("Account number: %s",cstmr.accno);
			gotoxy(20,12); printf("Name: %s %s",cstmr.fname,cstmr.lname);
			gotoxy(45,12); printf("Address: %s",cstmr.adrs);
			gotoxy(20,13); printf("Number: %s",cstmr.num);
			gotoxy(45,13); printf("Amount: Rs.%d",cstmr.amt);
			gotoxy(25,15); printf("----------New Account----------");
			gotoxy(20,16); printf("Enter account number:");
			scanf("%s",&cstmr.accno);
			gotoxy(20,17); printf("Enter new customer first name:");
			scanf("%s",&cstmr.fname);
			gotoxy(20,18); printf("Enter last name:");
			scanf("%s",&cstmr.lname);
			gotoxy(20,19); printf("Enter new customer address:");
			scanf("%s",&cstmr.adrs);
			gotoxy(20,20); printf("Enter new customer phone number:");
			scanf("%s",&cstmr.num);
			gotoxy(20,21); printf("Enter new amount(Rs):");
			scanf("%d",&cstmr.amt);
			fflush(stdin);
			gotoxy(20,24); printf("Do you want to save the change?(Y/N)\t");
			scanf("%c",&sav);
			if(sav=='Y'||sav=='y')
				cstmr=cstmr;
		}
		fwrite(&cstmr,sizeof(cstmr),1,tp);
	}
	fclose(fp);
	fclose(tp);
	remove("Bank.dat");
	rename("b.dat","Bank.dat");
	menu();
}

void deposit()
{
	int amt;
	char sav,title[]="Deposit";
	fp=fopen("Bank.dat","r+");
	remove("b.dat");
	tp=fopen("b.dat","w");
	if(fp==NULL)
		eror(ffail);
	access();
	cleardevice();
	layout(title);
	gotoxy(18,9); printf("Enter account number for deposit:\t");
	scanf("%s",&no);
	while(fread(&cstmr,sizeof(cstmr),1,fp)==1)
	{
		if(strcmp(no,cstmr.accno)==0)
		{
			gotoxy(25,11); printf(" \t Present Detail");
			gotoxy(20,12); printf("Account number: %s",cstmr.accno);
			gotoxy(20,13); printf("Name: %s %s",cstmr.fname,cstmr.lname);
				gotoxy(40,13); printf("Address: %s",cstmr.adrs);
			gotoxy(20,14); printf("Number: %s",cstmr.num);
				gotoxy(40,14); printf("amount: Rs.%d", cstmr.amt);
			gotoxy(20,15); printf("_____________________________________");
			gotoxy(20,17); printf("Enter amount to deposit (Rs): ");
			scanf("%d",&amt);
			gotoxy(20,18); printf("New Amount(Rs): %d",cstmr.amt+amt);
			fflush(stdin);
			gotoxy(20,20); printf("Do you want to save the change?(Y/N)\t");
			scanf("%c",&sav);
			if(sav=='Y'||sav=='y')
				cstmr.amt=cstmr.amt+amt;
		}
		fwrite(&cstmr,sizeof(cstmr),1,tp);
	}
	fclose(fp);
	fclose(tp);
	remove("Bank.dat");
	rename("b.dat","Bank.dat");
	menu();
}

void search()
{
	char title[]="Search Account";
	fp=fopen("Bank.dat","r");
	if(fp==NULL)
		eror(ffail);
	cleardevice();
	layout(title);
	gotoxy(18,9); printf("Enter account number to search:\t");
	scanf("%s",&no);
	while(fread(&cstmr,sizeof(cstmr),1,fp)==1)
	{
		if(strcmp(no,cstmr.accno)==0)
		{
			gotoxy(22,11); printf(" \t ACCOUNT INFORMATION");
			gotoxy(20,12); printf("_____________________________________");
			gotoxy(20,14); printf("Account number: %s",cstmr.accno);
			gotoxy(20,15); printf("Name: %s %s",cstmr.fname,cstmr.lname);
			gotoxy(20,16); printf("Address: %s",cstmr.adrs);
			gotoxy(20,17); printf("Phone number: (+977) %s",cstmr.num);
			gotoxy(20,18); printf("Amount: Rs.%d",cstmr.amt);
			gotoxy(20,19); printf("_____________________________________");
		}
	}
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	outtextxy(150,375,"Press any key to go back to the Main Menu.");
	fclose(fp);
	getch();
	menu();
}

void del()
{
	char sav,title[]="Delete Record";
	fp=fopen("Bank.dat","r+");
	remove("b.dat");
	tp=fopen("b.dat","w");
	if(fp==NULL)
		eror(ffail);
	access();
	cleardevice();
	layout(title);
	gotoxy(18,9); printf("Enter account number to delete:\t");
	scanf("%s",&no);
	while(fread(&cstmr,sizeof(cstmr),1,fp)==1)
	{
		if(strcmp(no,cstmr.accno)==0)
		{
			gotoxy(20,11); printf("_____________________________________");
			gotoxy(20,13); printf("Account number: %s",cstmr.accno);
			gotoxy(20,14); printf("Name: %s %s",cstmr.fname,cstmr.lname);
				gotoxy(40,14); printf("Address: %s",cstmr.adrs);
			gotoxy(20,15); printf("Number: %s",cstmr.num);
				gotoxy(40,15); printf("amount: Rs.%d", cstmr.amt);
			gotoxy(20,16); printf("_____________________________________");
			gotoxy(20,20); printf("Do you want to delete this account?(Y/N)\t");
			fflush(stdin);
			scanf("%c",&sav);
			if(sav=='Y'||sav=='y')
				continue;
		}
		fwrite(&cstmr,sizeof(cstmr),1,tp);
	}
	fclose(fp);
	fclose(tp);
	remove("Bank.dat");
	rename("b.dat","Bank.dat");
	menu();
}
void withdraw()
{
	int amt;
	char sav,title[]="Withdraw";
	fp=fopen("Bank.dat","r+");
	remove("b.dat");
	tp=fopen("b.dat","w");
	if(fp==NULL)
		eror(ffail);
	access();
	cleardevice();
	layout(title);
	gotoxy(18,9); printf("Enter account number to withdraw:\t");
	scanf("%s",&no);
	while(fread(&cstmr,sizeof(cstmr),1,fp)==1)
	{
		if(strcmp(no,cstmr.accno)==0)
		{
			gotoxy(25,11); printf(" \t Present Detail");
			gotoxy(20,12); printf("Account number: %s",cstmr.accno);
			gotoxy(20,13); printf("Name: %s %s",cstmr.fname,cstmr.lname);
				gotoxy(40,13); printf("Address: %s",cstmr.adrs);
			gotoxy(20,14); printf("Number: %s",cstmr.num);
				gotoxy(40,14); printf("amount: Rs.%d", cstmr.amt);
			gotoxy(20,15); printf("_____________________________________");
			gotoxy(20,17); printf("Enter amount to withdraw (Rs): ");
			scanf("%d",&amt);
			gotoxy(20,18); printf("Remaining Amount(Rs): %d",cstmr.amt-amt);
			fflush(stdin);
			gotoxy(20,20); printf("Do you want to save the change?(Y/N)\t");
			scanf("%c",&sav);
			if(sav=='Y'||sav=='y')
				cstmr.amt=cstmr.amt-amt;
		}
		fwrite(&cstmr,sizeof(cstmr),1,tp);
	}
	fclose(fp);
	fclose(tp);
	remove("Bank.dat");
	rename("b.dat","Bank.dat");
	menu();
}


void eror(char ero[])
{
	closegraph();
	clrscr(); textcolor(4);
	gotoxy(25,13);
	for(i=0;i<strlen(ero);i++)
	{
		cprintf("%c",ero[i]);
		delay(dly);
	}
	getch(); clrscr();
	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
	menu();
}

void layout(char *t)
{
	fflush(stdin);
	setcolor(11);
	settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
	delay(dly); outtextxy(225,65,t);
	setcolor(11);
	rectangle(78,111,572,352);
	rectangle(80,113,570,350);
	rectangle(78,111,572,50);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
}