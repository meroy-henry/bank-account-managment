
                                          // BANKING SYSTEM(MANAGING ACCOUNTS)  //
#include<stdio.h>
#include<string.h>

//Structure to store customer data
struct customer {
        char name[50];
        int acc_no;
        float balance;
    };
    
    struct customer e[100];//Array to store multipule accounts
    int size = 0;//Number of accounts stored
    

//FUNCTION:account_creation()
//PURPOSE:Create one or more bank accounts

void account_creation()
{

    int n;
    //ask how many account to create
    printf("Enter number of customers to create accounts for: ");
    scanf("%d", &n); 
    for(int i=0; i<n; i++)
    {
        printf("Enter details for customer %d:\n", i+1);
        //Enter name
        printf("Name: ");
        scanf("%s", e[i].name);
        //Enter unique account number
        printf("Account Number: ");
        scanf("%d", &e[i].acc_no);
        //Enter initial deposit
        printf("Initial Deposit Amount: ");
        scanf("%f", &e[i].balance);
        printf("Account Created Successfully!\n\n");
    }
    size= size +n;//increase total account count
       
    printf("All accounts created successfully!\n");
}
//FUNCTION:deposit_money()
//PURPOSE:Add money to an existing account
void deposit_money()
{
    
    int input_acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &input_acc_no);
    int found = 0;

    //search for account
    for(int i=0; i<size; i++)
    {
    
    if(input_acc_no == e[i].acc_no)
    {
        printf("Enter Amount to Deposit: ");
        scanf("%f", &amount);
        e[i].balance += amount;//Add money to balance
        printf("Amount %.2f deposited successfully to Account Number %d\n", amount, input_acc_no);
        printf("Updated Balance: %.2f\n", e[i].balance);
        
        found = 1;
        break;
    }
   
}
if(found ==0)
{
    printf("Invalid Account Number!\n");
}
}
//FUNCTION:Withdraw_money()
//PURPOSE:Withdraw money from an account
void withdraw_money()
{
    
    int input_acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &input_acc_no);
    int found = 0;
    //Search for matching account
    for(int i=0; i<size; i++)
    {
    
    if(input_acc_no == e[i].acc_no)
    {
        printf("Enter Amount to Withdraw: ");
        scanf("%f", &amount);
        //Check if balance is enough
        if(amount > e[i].balance)
        {
            printf("Insufficient Balance!\n");
            return;
        }
        e[i].balance -= amount;//Deduct money
        printf("Amount %.2f withdrawn successfully from Account Number %d\n", amount, input_acc_no);
        printf("Updated Balance: %.2f\n", e[i].balance);
        found = 1;
        break;
    }
}
if(found ==0)
{
    printf("Invalid Account Number!\n");
}
}
//FUNCTION:Check_balance()
//PURPOSE:show balance of a specific account
void check_balance()
{
    
    int input_acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &input_acc_no);
    int found = 0;
    //Search for account 
    for(int i=0; i<size; i++)
    {
   
    if(input_acc_no == e[i].acc_no)
    {
        printf("Current Balance for Account Number %d is: %.2f\n", e[i].acc_no, e[i].balance);
        found = 1;
        break;
    }
   
}

if(found ==0)
{
    printf("Invalid Account Number!\n");
}
}
//FUNCTION:Transfer_money()
//PURPOSE:Transfer money between two accounts
void transfer_money()
{
    
    int input_acc_no;
    float amount;
    int target_acc_no;
    int found_input = 0, found_target = 0;
    int found1=0,found2=0;
    printf("Enter Account Number: ");
    scanf("%d", &input_acc_no);
    for(int i=0; i<size; i++)
    {
    
    if(input_acc_no == e[i].acc_no)
    {
        found_input = i;
        found1 = 1;
    }
}
//Check if accounts exist 
if(found1 ==0)
{
    printf("Invalid Account Number!\n");
    return;
}
    printf("Enter Target Account Number: ");
    scanf("%d", &target_acc_no);
    for(int i=0; i<size; i++)
    {
    if(target_acc_no == e[i].acc_no)
    {
        found_target = i;
        found2 = 1;
    }
}
    if(found2 ==0)
    {
        printf("Invalid Target Account Number!\n");
        return;
    }
        printf("Enter Amount to Transfer: ");
        scanf("%f", &amount);
        //check sufficient balance
        if(amount > e[found_input].balance)
        {
            printf("Insufficient Balance!\n");
            return;
        }
        //Perform transation
        e[found_input].balance -= amount;
        if(target_acc_no == e[found_target].acc_no)
        {
            e[found_target].balance += amount;
        }
        printf("Amount %.2f transferred successfully from Account Number %d to Account Number %d\n", amount, input_acc_no, target_acc_no);
        printf("Updated Balance: %.2f\n", e[found_input].balance);
    }
//FUNCTION:save_data()
//PURPOSE:save all account data  permanetly to file 
//WITH:After every update (deposit/withdraw/create/delete)
void save_data()
{
    FILE *f = fopen("accounts.txt", "w");
    if (f ==NULL) {
        printf("Failed to open accounts.txt for writing.\n");
        return;
    }
    //Write all account bank into file
    for (int i = 0; i < size; i++) {
        fprintf(f,"Name: %s\n Account no.:%d\n Balance: %.2f\n",e[i].name, e[i].acc_no, e[i].balance);
    }
    fclose(f);//Close file 
    printf("Data saved to accounts.txt\n");
}
//FUNCTION:read_data()
//PURPOSE:Read all previously saved account from file 
//WHEN:called at program start
void read_data()
{
    FILE *f = fopen("accounts.txt","r");//open file in read mode
    //if file dose not exist ,simply return data loading failed
    if(f == NULL)
{
    printf("data loading failed");
    return;
}
char data[2000];
while(fgets(data,2000,f))
{
    printf(" %s\n",data);
}
fclose(f);//close file
}
//FUNCTION:account_deletion()
//PURPOSE:delete an account safely from system & file 
void account_deletion()
{
    int acc;
    printf("Enter the Account no. you want to delete: ");
    scanf("%d", &acc);
    
    int found = 0;
    
    // Search for account in memory array
    for(int i = 0; i < size; i++)
    {
        if(acc == e[i].acc_no)
        {
            // Shift remaining accounts to fill the gap
            for(int j = i; j < size - 1; j++)
            {
                e[j] = e[j + 1];
            }
            size--; // Decrease total account count
            found = 1;
            break;
        }
    }
    
    if(found == 1)
    {
        printf("Account %d deleted successfully!\n", acc);
        // Rewrite entire file with remaining accounts
        FILE *f = fopen("accounts.txt", "w");
        if(f == NULL)
        {
            printf("Failed to update file.\n");
            return;
        }
        
        for(int i = 0; i < size; i++)
        {
            fprintf(f, "Name: %s\nAccount no.%d\nBalance: %.2f\n", 
                    e[i].name, e[i].acc_no, e[i].balance);
        }
        fclose(f);
        printf("File updated successfully!\n");
    }
    else
    {
        printf("Invalid Account Number!\n");
    }
}
//MAIN FUNCTION-MENU SYSTEM
    
int main()
{
    int choice;
    do {
        printf("\nBanking System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. transfer Money\n");
        printf("6. Account deletion\n");
        printf("7. Save data\n");
        printf("8. Read data\n");
        printf("9. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                account_creation();
                break;
            case 2:
                deposit_money();
                break;
            case 3:
                withdraw_money();
                break;
            case 4:
                check_balance();
                break;

            case 5:
                transfer_money();
                break;
            case 6:
                account_deletion();
                break;
            case 7:
                save_data();
                 break;
            case 8:
             read_data(); 
             break;

            case 9:
            printf("Exiting the system. Thank you!\n");
            break;
        
            default:
                printf("Invalid Choice! Please try again.\n");
        }
    } while(choice != 9);
    return 0;
}
