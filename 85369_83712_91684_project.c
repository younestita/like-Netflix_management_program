//IDs: 85369 83712 91684
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define users 100

int printMenu(void);
void login(int* u, char email[][100],char fname[][100],char lname[][100],char password[][100],char bank_account_number[][100],int balance[],char secret_question[][100],char answer[][100]);
void signup(char email[][100],char fname[][100],char lname[][100],char password[][100],char bank_account_number[][100],int balance[],char secret_question[][100],char answer[][100], int *u);
void pay_bill(char email[][100],char fname[][100],char lname[][100],char password[][100],char bank_account_number[][100],int balance[],char secret_question[][100],char answer[][100],int user);



void changeInfo(char email[][100],char fname[][100],char lname[][100],char password[][100],char bank_account_number[][100],int user){
    int choice;
    char temp_fname[50] = {'\0'};
    char temp_lname[50] = {'\0'};
    char temp_password[13] = {'\0'};
    char temp_email[50] = {'\0'};
    char temp_bank_account[50] = {'\0'};
    ask:
    printf("What do you want to change:\n 1.Profile Name\n 2.Password\n 3.E-Mail\n 4.Bank Account\n 5.Save Changes\n>");
    scanf("%d",&choice);
    if (choice == 1){
        printf("Enter your new first name: ");
        scanf("%s",temp_fname);
        printf("Enter your new last name: ");
        scanf("%s",temp_lname);
        goto ask;
    }
    else if(choice == 2){
        //printf("Enter your new password: ");
         printf("Please enter your password (includes 3 lowercase letters, 3 uppercase letters, 3 digits, and three other characters that\n are not digits and not letters. You must make sure the password does not contain the following\n special characters: @ or  \\ or ;)\n");
        askpass:
        scanf("%s",temp_password);
        int lc=0,uc=0,nc=0,oc=0;
        for(int i = 0; i< 12 ; i++){
            if(temp_password[i]>='A' && temp_password[i]<='Z') uc++;
            else if(temp_password[i]>='a' && temp_password[i]<='z') lc++;
            else if(temp_password[i]>='0' && temp_password[i]<='9') nc++;
            else if(temp_password[i]!='@' && temp_password[i]!=';' && temp_password[i]!=92) oc++;
        }

        if (lc!=3 || uc!=3 || nc!=3 || oc!=3){
            printf("Enter a password that respects the conditions: ");
            goto askpass;
        }
    }
    else if(choice == 3){
        printf("Enter your new e-mail: ");
        scanf("%s",temp_email);
        goto ask;
    }
    else if(choice == 4){
        printf("Enter your new bank account number: ");
        scanf("%s",temp_bank_account);
        goto ask;
    }
    else if(choice == 5){
        char password_check[13];
        printf("Enter the old password to confirm the changes: ");
        passcheck:
        scanf("%s",password_check);
        if (strcmp(password_check,password[user])==0){
            if (temp_email[0]!='\0') strcpy(email[user],temp_email);
            if (temp_fname[0]!='\0') strcpy(fname[user],temp_fname);
            if (temp_lname[0]!='\0') strcpy(lname[user],temp_lname);
            if (temp_password[0]!='\0') strcpy(password[user],temp_password);
            if (temp_bank_account[0]!='\0') strcpy(bank_account_number[user],temp_bank_account);
        }
        else{
            printf("The password is incorrect. Enter it again: ");
            goto passcheck;
        }
        
    }
    else{
        printf("Please, enter one of the numbers on the screen!\n");
        goto ask;
    }
}



int printMenu(void)
{
    printf("Enter the number of the operation you wish to perform:\n 1.Log In\n 2.Sign Up\n 3.Exit\n> ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int main(void)
{

    FILE *inp, *out;
    inp = fopen("database.txt", "r");
    out = fopen("output.txt", "w");
    
    char email[users][100], fname[users][100], lname[users][100], password[users][100], bank_account_number[users][100], secret_question[users][100], answer[users][100], balstr[100];
    int balance[users];
    int u=1;
    while (!feof(inp)){
        fscanf(inp,"%s",email[u]);
        fscanf(inp,"%s",fname[u]);
        fscanf(inp,"%s",lname[u]);
        fscanf(inp,"%s",password[u]);
        fscanf(inp,"%s",bank_account_number[u]);
        fscanf(inp,"%s",balstr);
        balance[u]=atoi(balstr);
        fscanf(inp,"%s",secret_question[u]);
        fscanf(inp,"%s",answer[u]);
        u++;
    }
    u--;
    
    int choice;
    mainpage:
    choice = printMenu();
    while ((getchar()) != '\n');
    if (choice==1){
        login(&u,email,fname,lname,password,bank_account_number,balance,secret_question,answer);
        goto mainpage;
    }
    else if (choice == 2){
        signup(email,fname,lname,password,bank_account_number,balance,secret_question,answer,&u);
        goto mainpage;
    }
    else{
        for (int i = 1; i <= u; i++) {
         for (int j = i+1; j <= u; j++)
             if (strcmp(lname[i], lname[j]) > 0) {
                char temp[50];
                strcpy(temp,lname[i]);
                strcpy(lname[i],lname[j]);
                strcpy(lname[j],temp);

                strcpy(temp,fname[i]);
                strcpy(fname[i],fname[j]);
                strcpy(fname[j],temp);

                strcpy(temp,email[i]);
                strcpy(email[i],email[j]);
                strcpy(email[j],temp);

                strcpy(temp,password[i]);
                strcpy(password[i],password[j]);
                strcpy(password[j],temp);

                strcpy(temp,bank_account_number[i]);
                strcpy(bank_account_number[i],bank_account_number[j]);
                strcpy(bank_account_number[j],temp);

                strcpy(temp,secret_question[i]);
                strcpy(secret_question[i],secret_question[j]);
                strcpy(secret_question[j],temp);

                strcpy(temp,answer[i]);
                strcpy(answer[i],answer[j]);
                strcpy(answer[j],temp);

                int t;
                t=balance[i];
                balance[i]=balance[j];
                balance[j]=t;
            }
        }
    
    for (int i = 1; i <= u; i++) {
       if(strcmp(password[i],"deleted")!=0) fprintf(out,"%s ",email[i]);
       if(strcmp(password[i],"deleted")!=0) fprintf(out,"%s ",fname[i]);
       if(strcmp(password[i],"deleted")!=0) fprintf(out,"%s ",lname[i]);
       if(strcmp(password[i],"deleted")!=0) fprintf(out,"%s ",password[i]);
       if(strcmp(password[i],"deleted")!=0) fprintf(out,"%s ",bank_account_number[i]);
       if(strcmp(password[i],"deleted")!=0) fprintf(out,"%d ",balance[i]);
       if(strcmp(password[i],"deleted")!=0) fprintf(out,"%s ",secret_question[i]);
       if(strcmp(password[i],"deleted")!=0) fprintf(out,"%s\n",answer[i]);
    }

    fclose(inp);
    fclose(out);

    return 0;
    }

    
}
void login(int* up, char email[][100],char fname[][100],char lname[][100],char password[][100],char bank_account_number[][100],int balance[],char secret_question[][100],char answer[][100]){
    char user_email[50], user_password[13], ans[15];
    int choice1, i, n, flag=-1, email_found=0,user;
        
        printf("please enter your email:\n");
        gets(user_email);
        enter_password:
        printf("please enter your password: \n");
        gets(user_password);
        for (i=1; i<=*up; i++){
    
    if (strcmp(user_email,email[i])==0 ){
        email_found=1; user=i;

        if (strcmp(password[i],"deleted")==0){
            printf("You have been deleted from the database! Please sing up again.\n");
            signup(email, fname, lname, password, bank_account_number, balance, secret_question, answer, up);
            goto endlogin;
        }

        else if(strcmp(user_password,password[i])==0 ){
            info:
        printf("1.change user information/ 2.pay bill/ 3.end subsription/ 4.Log out\n ");
        printf("Your current balance is: %d\n", balance[user]);
        scanf("%d",&choice1);
        switch(choice1){

        case 1:
        changeInfo(email,fname,lname,password,bank_account_number,user);
        goto info;
        break; 
        case 2:
        pay_bill( email, fname, lname, password, bank_account_number, balance, secret_question, answer, user);
        goto info;
        break;
        case 4:
        goto endlogin;
        break;
        default:
        strcpy(email[user],"deleted");
        strcpy(fname[user],"deleted");
        strcpy(lname[user],"deleted");
        strcpy(password[user],"deleted");
        strcpy(bank_account_number[user],"deleted");
        balance[user]=-1111;
        strcpy(secret_question[user],"deleted");
        strcpy(answer[user],"deleted");
        break;
            }
        } 
        else {
        
                for(int j=0,k=0; j<12; j++,k++){
                        
                        if( user_password[j]==password[user][k+1] && user_password[j+1]==password[user][k]){
                         flag=0;
                         break;
                        }
                
                }
            } 
                 
            if (flag==0){
                printf("please answer the secret question: %s\n>",secret_question[user]);
                gets(ans);
                flag=1;
                if (strcmp(ans,answer[user])==0){
                    goto info;
                }
                else {
                    flag=1;
                    printf("your password is incorrect, please try again!\n");
                    
                  goto enter_password;  
                }
                }
        
        }
        } 

         if (email_found!=1){
             
            printf("the email entered does not exist, you will be redirected to the sign up page");
             signup(email, fname, lname, password, bank_account_number, balance, secret_question, answer, up);
        }

                
endlogin: ;
}
void signup(char email[][100],char fname[][100],char lname[][100],char password[][100],char bank_account_number[][100],int balance[],char secret_question[][100],char answer[][100], int *u)
{
    *u+=1;
    char email_entered[50], bank_account_number_entered[50];
    int i, flag=1, choice;
    printf("Welcome to the sign up page! Fill in your info:\n");
    askemail:
    printf("Please enter your email:\n>");
    
    gets(email_entered);
    
    
    for(i=1;i<=*u;i++)
    {
        if(strcmp(email_entered,email[i])==0 && strcmp(password[i],"deleted")!=0)
        {
            printf("The email entered already exists!\n");
            goto askemail;
        }
    }

    strcpy(email[*u],email_entered);
    
    printf("please enter your first name:\n");
    gets(fname[*u]);
    
    printf("please neter your last name:\n");
    gets(lname[*u]);
    
    askbank:
    printf("please enter your bank acocunt number-->\n");
    gets(bank_account_number_entered);
    
    for(i=1;i<=*u;i++)
    {
        if(strcmp(bank_account_number_entered,bank_account_number[i])==0)
        {
            printf("The bank account number entered already exists!\n");
            goto askbank;
        }
    }

    strcpy(bank_account_number[*u],bank_account_number_entered);
    

    
    printf("Please enter your password (includes 3 lowercase letters, 3 uppercase letters, 3 digits, and three other characters that\n are not digits and not letters. You must make sure the password does not contain the following\n special characters: @ or \\ or ;)\n");
 

    
    askpass2:
    gets(password[*u]);
    int lc=0,uc=0,nc=0,oc=0;
    for(int i = 0; i< 12 ; i++){
        if(password[*u][i]>='A' && password[*u][i]<='Z') uc++;
        else if(password[*u][i]>='a' && password[*u][i]<='z') lc++;
        else if(password[*u][i]>='0' && password[*u][i]<='9') nc++;
        else if(password[*u][i]!='@' && password[*u][i]!=';' && password[*u][i]!=92) oc++;
    }

    if (lc!=3 || uc!=3 || nc!=3 || oc!=3){
        printf("Enter a password that respects the conditions: ");
        goto askpass2;
    }
    
    printf("please enter your balance\n");
    scanf("%d",&balance[*u]);
    while ((getchar()) != '\n');
    
    printf("Please enter your secret question in this format: question?\n");
    gets(secret_question[*u]);
    
    printf("Please enter the answer to the secret question:\n");
    gets(answer[*u]);

}
void pay_bill(char email[][100],char fname[][100],char lname[][100],char password[][100],char bank_account_number[][100],int balance[],char secret_question[][100],char answer[][100],int user){
    if(balance[user]>500){
    balance[user]-=500;
    }
    else
    {
        // we don't delete the email to check if the user was in our database but their data was deleted
        strcpy(fname[user],"deleted");
        strcpy(lname[user],"deleted");
        strcpy(password[user],"deleted");
        strcpy(bank_account_number[user],"deleted");
        balance[user]=-1111;
        strcpy(secret_question[user],"deleted");
        strcpy(answer[user],"deleted");
        printf("Since your balance is not enough, you have been deleted from the database.\nPlease log out.");
    }

}
