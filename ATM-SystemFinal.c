/*
Title-ATM-System
Author-AS2020925
Date-2021.10.31
Version-4.0
Description-Simulation of an ATM
*/

#include<stdio.h>
#include<windows.h>
#include<time.h>

/*-----------------------------------------------------
[Begin]Declaration of Functions
-------------------------------------------------------*/

void PageBreak();
int PinCheck(int intPin,int intAccNo);
int GetUser(int intAccNo);
void AccountBalance(int intIndex);
void DepositCash(int intIndex);
void WithdrawCash(int intIndex);
void TransferCash(int intIndex);
void ReadDataFile();
void UpdateFile();
void PrintBill(int intIndex);
void TransactionRecord(int intAcBalRecord,int intIndex);
void PrintTransaction(int intAccNo);
/*-----------------------------------------------------
[End]Declaration of Functions
-------------------------------------------------------*/

/*---------------------------------------------------
[Begin]Declaration of Global Variables
-----------------------------------------------------*/
int const intRow=4;//Edit point1
int const intCol=4;//Edit point2
int intDiposit=0;
int intWithdraw=0;
int intTransAmount=0;
int intTransAccNo=0;

//Definition of integer arrays
int intAccounts[4][4];//Account data
int intTransRecords[15][6];//Transaction Records

//Definition of String array
char StringAccounts[4][50] =
{
    "Mr.Tharidu",
    "Miss.Krishani",
    "Mr.Perera",
    "Mrs.Fernando"
};
/*---------------------------------------------------
[End]Declaration of Global Variables
-----------------------------------------------------*/

/*--------------------------------------------------
[Begin]Main Function
----------------------------------------------------*/
int main()
{
    system("color 8F");

    //Variable Definition
    int intPin=0;
    int intAccNo=0;
    int intAccNoindex=0;
    int intResult,i,j,intMatch;
    int intResponse=0;
    int intAcBalRecord=0;
    char text[20];
    char chrResponce;
    char chrPrintBill;
    char chrPrintRecord;
    float fltBalance=1000.00;

    time_t now;//Getting System time
    time(&now);
    printf("\n\t\t %s",ctime(&now));

    printf("____________________________________________________________\n");
    printf("||| ||||||||||||||||||| | TKT Bank | ||||||||||||||||||| |||\n");
    printf("____________________________________________________________\n\n\a");

    for (i=0; 3>i; i++)
    {
        printf("\n\t\tEnter Your Account No : ");
        scanf("%d",&intAccNo);
        printf("\n\t\tEnter Your Pin No     : ");
        scanf("%d",&intPin);
        intMatch=PinCheck(intPin,intAccNo);//function calling

        if (intMatch==1)
        {
            do
            {
                PageBreak();//function calling
                printf("\n\t1.Account Balance\n");
                printf("\t2.Deposit Cash\n");
                printf("\t3.Withdraw Cash\n");
                printf("\t4.Transfer Cash\n");
                printf("\t5.Exit\n\n");
                printf(" Enter Your Response : ");
                scanf("%d",&intResponse);
                intAccNoindex=GetUser(intAccNo);//function calling

                PageBreak();//function calling
                switch(intResponse)
                {
                case 1:
                    AccountBalance(intAccNoindex);//function calling
                    printf(" Do you Wish to Continue transaction?[Y]/[N]:");
                    scanf(" %c",&chrResponce);
                    intAcBalRecord++;
                    break;
                case 2:
                    DepositCash(intAccNoindex);//function calling
                    printf(" Do you Wish to Continue transaction?[Y]/[N]:");
                    scanf(" %c",&chrResponce);
                    break;
                case 3:
                    WithdrawCash(intAccNoindex);//function calling
                    printf(" Do you Wish to Continue transaction?[Y]/[N]:");
                    scanf(" %c",&chrResponce);
                    break;
                case 4:
                    TransferCash(intAccNoindex);//function calling
                    printf(" Do you Wish to Continue transaction?[Y]/[N]:");
                    scanf(" %c",&chrResponce);
                    break;
                case 5:
                    chrResponce='N';
                    break;
                default:
                    printf("\n\n\tWrong input\n\n");
                    chrResponce='Y';
                    Beep(523,800);
                }

            }
            while(chrResponce=='Y');
            break;
        }
        else
            continue;
    }
    //Runs after 3 failed logings
    if (i==3)
        printf("\n Please Contact The Bank!!\n");
    if (intResponse!=5)
        PageBreak();

    //Runs only if pin correct
    if (intMatch==1)
    {
        printf("\n Do you Want to Print a Bill?[Y]/[N]: ");
        scanf(" %c",&chrPrintBill);
        printf("\n");
        if (chrPrintBill=='Y')
            PrintBill(intAccNoindex);//function calling

        //Transaction Report
        TransactionRecord(intAcBalRecord,intAccNoindex);

        printf("\n Do you want to see your last 5 transactions?[Y]/[N]: ");
        scanf(" %c",&chrPrintRecord);
        printf("\n");
        if (chrPrintRecord=='Y')
            PrintTransaction(intAccNo);//function calling
    }


    return 0;
}
/*--------------------------------------------------
[End]Main Function
----------------------------------------------------*/


/*--------------------------------------------------
[Begin]PageBreak Function
----------------------------------------------------*/
void PageBreak()
{
    printf("\n____________________________________________________________\n");
    printf("__________________________________________Hotline-0712345363\n\a");
    //printf("----------------------------------------------------------\n\n");
}
/*-------------------------------------------------
[End]PageBreak Function
---------------------------------------------------*/

/*-------------------------------------------------
[Begin]PinCheck Function
---------------------------------------------------*/
int PinCheck(int intPin,int intAccNo)
{
    ReadDataFile(); //Reading Data to array

    int i;
    int intValue=0;
    int intMatch=0;
    for (i=0; intRow>i; i++)
    {
        intValue=intAccounts[i][0];
        if (intValue==intAccNo)
        {
            intValue=intAccounts[i][1];
            if (intValue==intPin)
            {
                intMatch=1;
                break;
            }
            else
            {
                Beep(523,800);
                intMatch=0;
                break;
            }

        }
        else if (i==intRow-1)
        {
            Beep(610,1000);
            printf("\n Invalid Account No!!\n\n");
        }

    }
    return intMatch;
}
/*-------------------------------------------------
[End]PinCheck Function
---------------------------------------------------*/

/*-------------------------------------------------
[Begin]GetUser Function
--------------------------------------------------*/
int GetUser(int intAccNo)
{
    ReadDataFile(); //Reading Data to array

    int i;
    int intUserIndex;
    for (i=0; TRUE; i++)
    {
        if (intAccNo==intAccounts[i][0])
        {
            intUserIndex=i;
            break;
        }

    }
    return intUserIndex;
}
/*-------------------------------------------------
[End]GetUser Function
--------------------------------------------------*/

/*-------------------------------------------------
[Begin]AccountBalance Function
--------------------------------------------------*/
void AccountBalance(int intIndex)
{
    ReadDataFile(); //Reading Data to array

    printf("\n\n Account Owner           : %s\n",StringAccounts[intIndex]);
    printf(" ID Number               : %dV\n\n",intAccounts[intIndex][2]);
    printf(" Your Account Balance is : Rs.%d\n\n",intAccounts[intIndex][3]);
}
/*-------------------------------------------------
[End]AccountBalance Function
--------------------------------------------------*/


/*-------------------------------------------------
[Begin]DepositCash Function
--------------------------------------------------*/
void DepositCash(int intIndex)
{

    ReadDataFile(); //Reading Data to array
    int i,j;
    int intBalance=0;
    printf("\n Cash Amount                 : Rs.");
    scanf("%d",&intDiposit);
    printf("\n Put your bills on the tray");
    Beep(410,400);
    Beep(410,400);
    Beep(410,400);
    for (i=0; i<10; i++)
    {
        printf(" .");
    }
    Sleep(2000);
    intBalance=intAccounts[intIndex][3]+intDiposit;
    intAccounts[intIndex][3]=intBalance;
    printf("\n Your New Account Balance is : Rs.%d\n\n",intBalance);

    UpdateFile(); //Write Data to file


}
/*-------------------------------------------------
[End]DepositCash Function
--------------------------------------------------*/

/*-------------------------------------------------
[Begin]WithdrawCash Function
--------------------------------------------------*/
void WithdrawCash(int intIndex)
{
    ReadDataFile(); //Reading Data to array

    int i;
    int intBalance=0;
    int intAcBalance=0;

    intBalance=intAccounts[intIndex][3];
    if (intBalance<101)
    {
        printf("\n Insufficient account balance\n\n");
        Beep(410,400);
    }
    else
    {
        do
        {
            printf("\n Cash Amount                 : Rs.");
            scanf("%d",&intWithdraw);
            intBalance=intAccounts[intIndex][3]-intWithdraw;
            if (intBalance<100)
            {
                printf("\n Insufficient account balance\n Try again!!\n");
                Beep(410,400);
                continue;
            }
            else
            {
                Beep(410,400);
                Beep(410,400);
                Beep(410,400);
                Beep(410,400);
                for (i=0; i<10; i++)
                {
                    printf(" .");
                }
                Sleep(2000);
                printf("\n Please get your bills out");
                Sleep(2000);
                printf("\n Your New Account Balance is : Rs.%d\n\n",intBalance);
                intAccounts[intIndex][3]=intBalance;
                break;
            }
        }
        while(intBalance<100);

        UpdateFile(); //Write Data to file
    }

}
/*-------------------------------------------------
[End]WithdrawCash Function
--------------------------------------------------*/

/*-------------------------------------------------
[Begin]TransferCash Function
--------------------------------------------------*/
void TransferCash(int intIndex)
{
    ReadDataFile(); //Reading Data to array

    int i;
    int intValue;
    int intSenderBalance;
    int intReciverBalance;
    int intBalance=0;
    int intAcBalance=0;

    intBalance=intAccounts[intIndex][3];
    if (intBalance<101)
    {
        printf("\n\tInsufficient account balance\n\n");
        Beep(410,400);
    }
    else
    {
        do
        {
            printf("\n Account no : ");
            scanf("%d",&intTransAccNo);

            for(i=0; i<intRow; i++)
            {
                intValue=intAccounts[i][0];
                if ((intTransAccNo==intValue)&&(intTransAccNo!=intAccounts[intIndex][0]))
                {
                    do
                    {
                        printf(" Amount     : ");
                        scanf("%d",&intTransAmount);
                        intReciverBalance=intAccounts[i][3]+intTransAmount;
                        intSenderBalance=intAccounts[intIndex][3]-intTransAmount;

                        if (intSenderBalance>100)
                        {
                            intAccounts[intIndex][3]=intSenderBalance;
                            printf(" Your New Account Balance is : Rs.%d\n\n",intAccounts[intIndex][3]);
                            intAccounts[intIndex][3]= intSenderBalance;
                            intAccounts[i][3]= intReciverBalance;
                            printf(" You have Transfered Rs.%d to %s - %d  \n\n",intTransAmount,StringAccounts[i],intAccounts[i][0]);
                            break;
                        }
                        else
                        {
                            printf("\tInsufficient Account Balance\n\n");
                            Beep(523,800);
                            continue;
                        }
                    }
                    while(intSenderBalance<100);
                    break;
                }
                else if (i==intRow-1)
                {
                    if (intTransAccNo==intAccounts[intIndex][0])
                    {
                        printf("\tInvalid Input\n");
                        Beep(523,800);
                        break;
                    }
                    else
                    {
                        printf("\tAccount Doesn't exist \n");
                        Beep(523,800);
                        break;
                    }

                }
            }
        }
        while(intTransAccNo!=intValue);
        UpdateFile(); //Write Data to file

    }
}

/*-------------------------------------------------
[Begin]ReadDataFile Function
--------------------------------------------------*/
void ReadDataFile()
{
    //Reading the file (Beginning)
    FILE *myFile=fopen("AccountDetails.txt","r");
    int i,j;
    for(i=0; i<intRow; i++)
    {
        for (j=0; j<intCol; j++)
        {
            fscanf(myFile,"%d,",&intAccounts[i][j]);//Entering to array
        }
    }


    fclose(myFile);

    //Reading the file (End)

}
/*-------------------------------------------------
[End]ReadDataFile Function
--------------------------------------------------*/

/*-------------------------------------------------
[Begin]UpdateFile Function
--------------------------------------------------*/
void UpdateFile()
{
    //Updating the file (Beginning)
    int i,j;
    FILE *myFile=fopen("AccountDetails.txt","r");
    FILE *newFile=fopen("AccountDetails_temp.txt","w");


    for (i=0; i<intRow; i++)
    {
        for(j=0; j<intCol; j++)
        {
            if (j==intCol-1)
            {
                fprintf(newFile,"%d",intAccounts[i][j]);
            }
            else
            {
                fprintf(newFile,"%d,",intAccounts[i][j]);
            }

        }
        fprintf(newFile,"\n");
    }


    fclose(myFile);
    fclose(newFile);

    remove("AccountDetails.txt");
    rename("AccountDetails_temp.txt","AccountDetails.txt");

    //Updating the file (End)

}
/*-------------------------------------------------
[End]UpdateFile Function
--------------------------------------------------*/


/*-------------------------------------------------
[Begin]PrintBill Function
--------------------------------------------------*/
void PrintBill(int intIndex)
{

    printf("\t============================================\n");
    printf("\t\t  ATM TRANSACTION-TKT BANK\n");
    printf("\t============================================\n");

    printf("\t ACCOUNT NUMBER\n");
    printf("\t %d\n",intAccounts[intIndex][0]);
    printf("\t ACCOUNT OWNER    : %s\n\n",StringAccounts[intIndex]);

    if (intDiposit!=0)
    {
        printf("\t DEPOSITION AMOUNT: Rs:%d\n",intDiposit);
    }
    if (intWithdraw!=0)
    {
        printf("\t WITHDRAWN AMOUNT : Rs:%d\n",intWithdraw);
    }
    if (intTransAmount!=0)
    {
        printf("\t TRANSFERED AMOUNT: Rs:%d\n",intTransAmount);
        printf("\t TRANSFERED AC.NO : %d\n",intTransAccNo);
    }
    printf("\t ACCOUNT BALANCE  : Rs.%d\n",intAccounts[intIndex][3]);


    printf("\t============================================\n");
    printf("\t\t\tTHANK YOU!!\n");
}
/*-------------------------------------------------
[End]PrintBill Function
--------------------------------------------------*/

/*-------------------------------------------------
[Begin]TransactionRecord Function
--------------------------------------------------*/
void TransactionRecord(int intAcBalRecord,int intIndex)
{
    int i,j;
    FILE *recordFile=fopen("DailyRecords.txt","a");

    fprintf(recordFile,"%d,%d,%d,%d,%d,%d\n",intAccounts[intIndex][0],intAcBalRecord,intDiposit,intWithdraw,intTransAmount,intTransAccNo);


    fclose(recordFile);
}
/*-------------------------------------------------
[End]TransactionRecord Function
--------------------------------------------------*/

/*-------------------------------------------------
[Begin]PrintTransaction Function
--------------------------------------------------*/
void PrintTransaction(int intAccNo)
{
    FILE *myFile=fopen("DailyRecords.txt","r"); //Reading the file
    int i,j;
    int intTData=0;
    int intValue=0;

    for(i=0; i<20; i++)
    {
        for (j=0; j<6; j++)
        {
            fscanf(myFile,"%d,",&intTransRecords[i][j]);
        }
    }

    for(i=0; TRUE; i++)
    {

        intValue=intTransRecords[i][0];
        if (intValue==intAccNo)
        {

            printf("\n Checked Account Balance %d time/s\n",intTransRecords[i][1]);
            printf(" Deposited Rs.%d \n",intTransRecords[i][2]);
            printf(" Withdrew Rs.%d \n",intTransRecords[i][3]);
            printf(" Transferred Rs.%d to %d Account\n\n",intTransRecords[i][4],intTransRecords[i][5]);
            intTData++;

            if (intTData==5)
                break;

        }

    }

    fclose(myFile);
}
/*-------------------------------------------------
[End]PrintTransaction Function
--------------------------------------------------*/





