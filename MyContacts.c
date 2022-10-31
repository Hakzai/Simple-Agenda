/*  Isaac Pellegrini Alencar
    SOFTWARE DEVELOPER
    Project 02 - AGENDA
    Class - LP1
    */
    
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct contact{
    char name[32];
    char email[64];
    char phone[16];
    int day, month, year;
}contactStruct;

int main() 
{
    FILE *contactList; 
    contactStruct *myContact;

    int menuController=-1;
    int subMenuController=-1;
    int i, count; 
    int qty=0; 
    int found; 
    int age;
    char compare[32]; 

    if((contactList = fopen("Agenda_MyContacts.bin", "ab+")) == NULL) 
    {
        puts("File cannot be opened!");
        exit(1);
    }
    fclose(contactList);

    printf("** Welcome to App MyContacts **\n\n");

    while(menuController!=0)
    {
        if ((contactList = fopen("Agenda_MyContacts.bin", "rb+")) == NULL)
            puts("Reading Error!");
        fread(&qty, sizeof(int), 1, contactList);
        fclose(contactList);

        if(qty!=0)
        {
            myContact = ((contactStruct *) malloc (qty * sizeof(contactStruct))); 
            if (!myContact){
                printf ("Error: Insufficient Memory !");
                exit(0);
            }
        }

        found=0, subMenuController=-1;

        printf("Menu: \n\n1 - Create Contact \n2 - Search Contact \n3 - Contacts List \n4 - Modify Contact \n5 - Month Birthdays \n\n0 - Exit app \n\nInput >> ");
        scanf("%d", &menuController);
        while(menuController<0 || menuController>5)
        {
            printf("\nInvalid Option!\nInsert correct input: ");
            scanf("%d", &menuController);
        }
        if (menuController==1) 
        {
            system("cls");
            if(qty==0)
            {
                myContact = ((contactStruct *) malloc (sizeof(contactStruct)));
                if (!myContact){
                    printf ("Error: Insufficient Memory !");
                    exit(0);
                }
            }
            else
            {
                myContact = ((contactStruct *) realloc (myContact, (qty+1)*sizeof(contactStruct)));
                if (!myContact){
                    printf ("Error: Insufficient Memory !");
                    exit(0);
                }
            }

            printf("Write the name: ");
            fflush(stdin);
            scanf(" %[^\n]s", &myContact[0].name);
            printf("Write the email: ");
            fflush(stdin);
            scanf("%s", &myContact[0].email);
            printf("Write the phone: ");
            fflush(stdin);
            scanf("%s", &myContact[0].phone);
            printf("Write the Birth date day / month / year:\n");
            scanf("%d", &myContact[0].day);
            scanf("%d", &myContact[0].month);
            scanf("%d", &myContact[0].year);
            qty ++; 

            if((contactList = fopen("Agenda_MyContacts.bin","rb+"))==NULL)
                printf("\nError opening the file!");

            fseek(contactList, 0, SEEK_SET);
            fwrite((int *) &qty, sizeof(int), 1, contactList);
            fclose(contactList);

            if((contactList = fopen("Agenda_MyContacts.bin","ab+"))==NULL)
                printf("\nError opening the file!");

            fwrite(myContact, sizeof(contactStruct), 1, contactList);
            fclose(contactList);

            system("cls");
            printf(">> Contact Created!\n\n"); 
        }
        else if (menuController==2)
        {
            system("cls");
            if(qty==0) 
                printf("There are no contacts in the List!\n\n");
            else
            {
                if((contactList = fopen("Agenda_MyContacts.bin","rb+"))==NULL) 
                    printf("\nReading Error!");
                fseek(contactList, 0-sizeof(contactStruct)*(qty), SEEK_END);
                fread(myContact, sizeof(contactStruct), qty, contactList);
                fclose(contactList);

                printf("Write the name for search: ");
                scanf(" %[^\n]s", &compare);
                for(i=0;i<MAX;i++)
                {
                    if(strncmp( (*(myContact+i)).name , compare, count=strlen(compare)) == 0) 
                    {
                        age = (2022 - (*(myContact+i)).year); 
                        if ((*(myContact+i)).month > 05)
                        {
                            age = age - 1;
                        }
                        if((*(myContact+i)).month == 05 && ((*(myContact+i)).day > 28))
                        {
                            age = age - 1;
                        }
                        printf("\nName: %s \nEmail: %s \nPhone: %s \nAge: %d\n", (*(myContact+i)).name, (*(myContact+i)).email, (*(myContact+i)).phone, age);
                        found = 1;
                    }
                    if(i>qty)
                    {
                        break;
                    }
                }
                if (found != 1) 
                {
                    system("cls");
                    printf("Contact has not been found with the given Name!\n\n");
                }
                else
                {
                    printf ("\n");
                    system("pause");
                    system("cls");
                }
            }
        }
        else if (menuController==3)
        {
            system("cls");
            if(qty==0) 
                printf("There are no contacts in the List!\n\n");
            else
            {
                if((contactList = fopen("Agenda_MyContacts.bin","rb+")) == NULL)
                    printf("\nError opening the file!");

                fseek(contactList, 0-sizeof(contactStruct) * (qty), SEEK_END);
                fread(myContact, sizeof(contactStruct), qty, contactList);
                fclose(contactList);

                for(i=0;i<qty;i++)
                {
                    age = (2022 - (*(myContact+i)).year); 
                    if ((*(myContact+i)).month > 05)
                    {
                        age = age - 1;
                    }
                    if((*(myContact+i)).month == 05 && ((*(myContact+i)).day > 28))
                    {
                        age = age - 1;
                    }
                    printf("Name: %s \nEmail: %s \nPhone: %s \nAge: %d\n\n", (*(myContact+i)).name, (*(myContact+i)).email, (*(myContact+i)).phone, age);
                }
                system("pause");
                system("cls");
            }
        }
        else if (menuController==4) 
        {
            system("cls");
            if(qty==0) 
                printf("There are no contacts in the List!\n\n");
            else
            {
                if((contactList = fopen("Agenda_MyContacts.bin","rb+")) == NULL)
                    printf("\nError opening the file!");

                fseek(contactList, 0-sizeof(contactStruct) * qty, SEEK_END);
                fread(myContact, sizeof(contactStruct), qty, contactList);
                fclose(contactList);

                printf("Write the contact name: "); 
                fflush(stdin);
                scanf(" %[^\n]s", &compare);

                for(i=0;i<MAX;i++)
                {
                    if(strcmp( (*(myContact+i)).name , compare) == 0) 
                    {
                        age = (2022 - (*(myContact+i)).year); 
                        if ((*(myContact+i)).month > 05)
                        {
                            age = age - 1;
                        }
                        if((*(myContact+i)).month == 05 && ((*(myContact+i)).day > 28))
                        {
                            age = age - 1;
                        }
                        printf("\nName: %s \nEmail: %s \nPhone: %s \nAge: %d\n", (*(myContact+i)).name, (*(myContact+i)).email, (*(myContact+i)).phone, age); 
                        printf("\nWhich data do you want to modify?\n");
                        while(subMenuController!=0)
                        {
                            printf("\n1 - Name \n2 - Email \n3 - Phone \n4 - Birth date \n\n0 - Return\n\nEnter >> "); 
                            scanf("%d", &subMenuController);
                            while(subMenuController<0 || subMenuController>5)
                            {
                                printf("\nInvalid Option!\nInsert correct input: ");
                                scanf("%d", &subMenuController);
                            }
                            if(subMenuController==1) 
                            {
                                printf("Write the new name: ");
                                scanf(" %[^\n]s", &(*(myContact+i)).name);
                            }
                            else if(subMenuController==2) 
                            {
                                printf("Write the new email: ");
                                scanf("%s", &(*(myContact+i)).email);
                            }
                            else if(subMenuController==3)
                            {
                                printf("Write the new phone: ");
                                scanf("%s", &(*(myContact+i)).phone);
                            }
                            else if(subMenuController==4)
                            {
                                printf("Write the new Birth date day / month / year:\n");
                                scanf("%d", &(*(myContact+i)).day);
                                scanf("%d", &(*(myContact+i)).month);
                                scanf("%d", &(*(myContact+i)).year);
                            }
                            if (subMenuController==0)
                            {
                                system("cls");
                                printf("Contact was not modified!\n\n"); 
                                found=1;
                                break;
                            }
                            if((contactList = fopen("Agenda_MyContacts.bin","rb+"))==NULL)
                            printf("\nIt was not possible to open file!");

                            fseek(contactList, 0-(i*sizeof(contactStruct)), SEEK_END);
                            fwrite(&myContact[i], sizeof(contactStruct), 1, contactList);
                            fclose(contactList);

                            subMenuController=0;
                            system("cls");
                            printf("Contact modified with Success!\n\n"); 
                            found=1;
                        }
                    }
                    if(i>qty || found==1)
                    {
                        break;
                    }
                }
                if(found!=1)
                {
                    system("cls");
                    printf("Contact has not been found with the given Name!\n\n");
                }
            }
        }
        else if (menuController==5) 
        {
            system("cls");
            if(qty==0) 
                printf("There are no contacts in the List!\n\n");
            else
            {
                printf("Write the month number (01 to 12): "); 
                scanf("%d", &count);

                if((contactList = fopen("Agenda_MyContacts.bin","rb"))==NULL)
                    printf("\nReading Error!");

                fseek(contactList, 0-sizeof(contactStruct) * (qty), SEEK_END);
                fread(myContact, sizeof(contactStruct), qty, contactList);
                fclose(contactList);

                for(i=0;i<qty;i++)
                {
                    if((*(myContact+i)).month == count) 
                    {
                        printf("name: %s - day %d\n", (*(myContact+i)).name,(*(myContact+i)).day );
                    }
                }
                system("pause"); 
                system("cls");
            }
        }
        else if(menuController==0) 
            printf("\nThank you for using this App!\n\nDeveloped by:\nIsaac Alencar\n"); 
    }

    free(myContact); 
    return 1;
}
