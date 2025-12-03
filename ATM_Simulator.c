#include <string.h>
#include <stdio.h>
#define Af "account.txt"
#define tf "transactions.txt"

void load();
void save();
void addTrans(char t[], float a);
void statment();
void trimOld();
void chnagepin();


int pin,lock;
float bal;

//  i am saving the the details in a file 
void save()
{
    FILE *fp = fopen(Af,"w");
    fprintf(fp,"%d %d %f",pin, lock,bal);
    fclose(fp);
}

// function to change the pin
void chnagepin()
{
  int npin;
  printf("enter the new pin");
  scanf("%d",&npin);
  pin=npin;
  save();
}

// this will create a statment of last 5 transaction 
void statment()
{
    FILE *fp = fopen(tf,"r");
    char ln[200];

    if(fp==NULL){
        printf("No transactions yet.\n");
        return;
    }

    printf("last 5 transaction\n");

    while(fgets(ln,sizeof(ln),fp)){
        printf("%s",ln);
    }

    fclose(fp);
}

// adds transaction
void addTrans(char x[], float a)
{
    trimOld();
    FILE *fp = fopen(tf,"a");
    fprintf(fp,"%s | Amt: %f | Bal: %f\n",x,a,bal);
    fclose(fp);
}
// this will load datd from the account file 
void load()
{
    FILE *fp =fopen(Af,"r");

    if(fp==NULL)
    {
        pin = 1234;
        lock = 0;
        bal = 5000;
        save();
        return;
    }

    fscanf(fp,"%d %d %f", &pin, &lock, &bal);
    fclose(fp);
}

// to maintain last 4 transactions 
void trimOld()
{
    char arr[1000][200];
    int c=0;
    FILE *fp=fopen(tf, "r");
    if (fp != NULL)
    {
        while (c<1000&&fgets(arr[c],sizeof(arr[c]),fp))
        {
            c++;
        }
        fclose(fp);
    }
    fp=fopen(tf,"w");
    int start=0;
    if (c>5)
    {
        start=c-5;  
    }
    for (int i=start+1;i<c;i++)
    {
        fputs(arr[i],fp);
    }
    fclose(fp);
}

int main() 
{
    load();
    int epin,c,ch;
    float amt;
    c=0;
    if(lock==1)
    {
        printf("acc is locked to due to entering wrong pin three times \n");
        return 0;
    }
    while(c < 3)
    {
        printf("enter yout account pin   ");
        scanf("%d",&epin);
        if(epin==pin)
        {
          printf("you are logged in \n");
          break;
        }
        else
        {
          printf("incorrect pin\n");
          c++;
        }
    }

    if(c ==3)
    {
        printf("account is locked \n");
        lock=1;
        save();
        return 0;
    }

    while(1)
    {
        printf("check balance (1)\n");
        printf("withdraw money (2)\n");
        printf("deposit money (3)\n");
        printf("get mini statement (4)\n");
        printf("change pin (5)\n");
        printf("exit atm (6)\n");
        printf("Enter choice: ");
        scanf("%d",&ch);

        if(ch==1)
        {
            printf("Balance: %f\n",bal);
            addTrans("BAL",0);
        }
        else if(ch==2)
        {
            printf("enter amount ");
            scanf("%f",&amt);

            if(amt >bal)
            {
                printf("balance is not enough \n");
            }
            else
            {
                bal -=amt;
                printf("Withdrawn.\n");
                save();
                addTrans("WITHDRAW",amt);
            }
        }
        else if(ch==3)
        {
            printf("Deposit amount: ");
            scanf("%f",&amt);
            bal+=amt;
            printf("amount is deposited\n");
            save();
            addTrans("DEPOSIT",amt);
        }
        else if(ch==4)
        {
            statment();
        }
        else if(ch==6){
            printf("thankyou for using he ATM \n");
            break;
        }
        else if(ch==5)
        {
          chnagepin();
        }
        else  {
            printf("not a valid input \n");
        }
    }

    return 0;
}


