#include<stdio.h>
#include<string.h>

struct customer
{
    int id;
    char name[30];
    char mobile[15];
    int balance;
};

struct history
{
    int id;
    char name[30];
    char mobile[15];
    int balance;
};

struct customer c, temp;
struct history h;

int findcustomer(char mobile[], struct customer *temp);
void readline(char *str, int size);
void customer_registration();
void recharge_plans();
void recharge();
void recharge_history();
void balance_enquiry();
void bill_generation();
void customers_list();
void end();

int main()
{
    int n;
    printf("\t   MOBILE RECHARGE SYSTEM    \n");
    printf("1.Customer registration\n");
    printf("2.Recharge plans\n");
    printf("3.Recharge\n");
    printf("4.Recharge history\n");
    printf("5.Balance enquiry\n");
    printf("6.Bill generation\n");
    printf("7.Customers list\n");
    printf("8.Exit\n");

    label:
    printf("\nEnter your choice:");
    scanf("%d", &n);
    if(0 < n && n < 9)
        printf("Valid choice\n");
    else
    {
        printf("Invalid choice\n");
        goto label;
    }
    
    switch(n)
    {
        case 1:
            customer_registration();
            goto label;
        case 2:
            recharge_plans();
            goto label;
        case 3:
            recharge();
            goto label;
        case 4:
            recharge_history();
            goto label;
        case 5:
            balance_enquiry();
            goto label;
        case 6:
            bill_generation();
            goto label;
        case 7:
            customers_list();
            goto label;
        case 8:
            end();
            break;
    }
    return 0;  
}

void readline(char *str, int size)
{
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}

int findcustomer(char mobile[], struct customer *temp)
{    
    FILE *fp = fopen("customers.dat", "rb");
    if(fp == NULL)
    {
        return 0;
    }
    while(fread(temp, sizeof(struct customer), 1, fp))
    {
        if(strcmp(temp->mobile, mobile) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void customer_registration()
{
    getchar(); 
    printf("Enter your name:\n");
    readline(c.name, 30);

    mob:
    printf("Enter your mobile number:");
    readline(c.mobile, 15);
    if(strlen(c.mobile) != 10)
    {
        printf("Invalid mobile number\n");
        goto mob;
    }
    else if('6' > c.mobile[0] || c.mobile[0] > '9')
    {
        printf("Invalid mobile number\n");
        goto mob;
    } 
    else
    {
        for(int i = 0; i < 10; i++)
        {
            if(c.mobile[i] < '0' || c.mobile[i] > '9')
            {
                printf("Invalid mobile number\n");
                goto mob;
            }
        }
    }

    if(findcustomer(c.mobile, &temp))
    {
        printf("Already registered\n");
        printf("ID: %d | Name: %s | Mobile: %s | Balance: %d\n", 
               temp.id, temp.name, temp.mobile, temp.balance);
    }
    else
    {
        int max_id = 999;
        FILE *fp = fopen("customers.dat", "rb");
        if(fp != NULL)
        {
            while(fread(&temp, sizeof(struct customer), 1, fp))
            {
                if(temp.id >= 1000 && temp.id > max_id)
                    max_id = temp.id;
            }
            fclose(fp);
        }

        c.id = max_id + 1;
        printf("Enter initial balance:");
        scanf("%d", &c.balance);

        fp = fopen("customers.dat", "ab");
        fwrite(&c, sizeof(struct customer), 1, fp);
        fclose(fp);

        printf("Registered successfully! Your ID is %d\n", c.id);
    }
}

void recharge_plans()
{
    printf("Choice\t Price \t  Data \tValidity\n");
    printf("  1   \tRs.199 \t2GB/day\t28 days\n");
    printf("  2   \tRs.299 \t3GB/day\t28 days\n");
    printf("  3   \tRs.479 \t2GB/day\t56 days\n");
    printf("  4   \tRs.839 \t2GB/day\t84 days\n");
}

void recharge()
{
    int x;
    printf("Enter your plan choice (1-4): ");
    scanf("%d", &x);

    if(x > 0 && x < 5)
    {
        int amount;
        if(x == 1) amount = 199;
        else if(x == 2) amount = 299;
        else if(x == 3) amount = 479;
        else amount = 839;

        getchar();
        printf("Enter registered mobile number: ");
        readline(c.mobile, 15);

        FILE *fp = fopen("customers.dat", "rb+");
        if(fp == NULL)
        {
            printf("Not registered\nEnter choice as 1 and register\n");
            return;
        }

        int found = 0;
        while(fread(&temp, sizeof(struct customer), 1, fp))
        {
            if(strcmp(temp.mobile, c.mobile) == 0)
            {
                found = 1;
                printf("Customer: %s | Previous Balance: Rs.%d\n", temp.name, temp.balance);
                FILE *hfp = fopen("history.dat", "ab");
                if(hfp != NULL)
                {
                    h.id = temp.id;
                    strcpy(h.name, temp.name);
                    strcpy(h.mobile, temp.mobile);
                    h.balance = amount;
                    fwrite(&h, sizeof(struct history), 1, hfp);
                    fclose(hfp);
                }
                temp.balance = amount;
                fseek(fp, -(long)sizeof(struct customer), SEEK_CUR);
                fwrite(&temp, sizeof(struct customer), 1, fp);

                printf("Recharge successful! New Balance: Rs.%d\n", temp.balance);
                break;
            }
        }
        fclose(fp);

        if(!found)
        {
            printf("Not registered\n");
            printf("Enter choice as 1 and register\n");
        }
    }
    else
    {
        printf("Invalid plan choice! View option 2 for valid plans.\n");
    }
}

void recharge_history()
{
    char mobile[15];
    int found = 0;
    getchar(); 
    printf("Enter mobile number to view recharge history: ");
    readline(mobile, 15);

    FILE *hfp = fopen("history.dat", "rb");
    if(hfp == NULL)
    {
        printf("No recharge history found yet\n");
        return;
    }

    printf("\n\t Recharge History for %s \n", mobile);
    while(fread(&h, sizeof(struct history), 1, hfp))
    {
        if(strcmp(h.mobile, mobile) == 0)
        {
            found = 1;
            printf("%d\t%s\t%s\tRs.%d\n", h.id, h.name, h.mobile, h.balance);
        }
    }
    fclose(hfp);

    if(found == 0)
    {
        printf("No recharge records found for this mobile number.\n");
    }
}

void balance_enquiry()
{
    char mobile[15];
    getchar();
    printf("Enter mobile number for balance enquiry: ");
    readline(mobile, 15);

    if(findcustomer(mobile, &temp))
    {
        printf("ID: %d | Name: %s | Current Balance: Rs.%d\n", temp.id, temp.name, temp.balance);
    }
    else
    {
        printf("Mobile number not registered!\n");
    }
}

void bill_generation()
{
    char mobile[15];
    int found = 0;
    getchar(); 
    printf("Enter mobile number to generate bill: ");
    readline(mobile, 15);

    FILE *fp = fopen("customers.dat", "rb");
    if(fp == NULL)
    {
        printf("No customer records found\n");
        return;
    }

    while(fread(&temp, sizeof(struct customer), 1, fp))
    {
        if(strcmp(temp.mobile, mobile) == 0)
        {
            found = 1;
            int total = temp.balance;
            float base_amount = total / 1.18;
            float gst = total - base_amount;
            printf("\n         MOBILE RECHARGE RECEIPT         \n");
            printf("Customer ID   : %d\n", temp.id);
            printf("Customer Name : %s\n", temp.name);
            printf("Mobile Number : %s\n", temp.mobile);
            printf("Base Plan Amt : Rs. %.2f\n", base_amount);
            printf("GST (18%%)     : Rs. %.2f\n", gst);
            printf("Total Paid    : Rs. %d\n", total);
            printf("Status        : PAID\n");
            break;
        }
    }
    fclose(fp);

    if(found == 0)
    {
        printf("Mobile number not registered!\n");
    }
}

void customers_list()
{
    FILE *fp = fopen("customers.dat", "rb");
    if(fp == NULL)
    {
        printf("No customers\n");
        return;
    }
    printf("\nID\tName\t\tMobile\t\tBalance\n");
    while(fread(&temp, sizeof(struct customer), 1, fp) == 1)
    {
        printf("%d\t%-15s\t%s\tRs.%d\n", temp.id, temp.name, temp.mobile, temp.balance);
    }
    fclose(fp);
}

void end()
{
    printf("Thank you\n");
}