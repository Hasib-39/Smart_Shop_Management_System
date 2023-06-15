#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../password/GeneratePassword.c"
#include "../cosmetics/ANSI.h"
#include "../Snippets.c"


#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_HASH_LENGTH 128 // A SHA-512 hash is 128 charecters
#define MAX_LINE_LENGTH (MAX_USERNAME_LENGTH + MAX_HASH_LENGTH + 2)
char filepath_Admin[200];

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char *password_hash;
    FILE *password_file;
} User;

FILE *login(User *user);
int signup(User *user);
void item_management(FILE* Admin);

void AdminAccess(FILE *Admin)
{
    User user = {0};
    user.password_file = fopen("psswd/AdminPasswords.dat", "a+");
    int choice;

    do
    {
        printf("%s%s", YELLOW, BOLD);
        printf("*********************************************************\n");
        printf("                  Login/Signup Menu                \n");
        fflush(stdin);
        printf("*********************************************************\n");
        printf("%s%s%s", RESET, CYAN, BOLD);
        printf("\t1. Login\n");
        printf("\t2. Signup\n");
        printf("\t0. Exit\n");
        printf("\n");
        printf("%s", GREEN);
        printf("Choose an option: ");
        printf("%s",YELLOW);
        scanf("%d", &choice);

        if (choice == 1)
        {
            // login(&user);
            if ((Admin = login(&user)))
            {
                // printf("%p", Admin);
                // filePrinter(Admin);
                // fclose(Admin);

                item_management(Admin);
                return;
            }
        }
        else if (choice == 2)
        {
            if (signup(&user))
            {
                printf("Account added, please try logging in\n");
                // login(&user);
            }
        }
        else if (choice != 0)
        {
            printf("Invalid choice!Please enter a valid input\n");
        }
    } while (choice != 0);

    intelligent_close(user.password_file);
    exit(0);
}

FILE* login(User *user)
{

    printf("%s", MAGENTA);
    printf("Enter username: ");
    scanf("%s", user->username);
    printf("Enter password: ");
    printf("%s%s", HIDDEN, BG_WHITE);
    scanf(" %[^\n]", user->password);
    printf("%s", RESET);
    printf("%s%s", MAGENTA, BOLD);

    char line[MAX_LINE_LENGTH];
    rewind(user->password_file);
    while (fgets(line, sizeof(line), user->password_file))
    {
        char *space = strchr(line, ' ');
        if (!space)
        {
            continue;
        }
        // Checking username
        *space = '\0';
        if (strcmp(line, user->username) == 0)
        {
            if (user->password_hash)
            {
                free(user->password_hash);
            }
            user->password_hash = haSha_512(user->password);
            char *stored_password = space + 1;
            stored_password[strcspn(stored_password, "\r\n")] = '\0';
            if (strcmp(stored_password, user->password_hash) == 0)
            {
                printf("Login successful!\n");

                // Derive filepath from username
                // char filepath[200];
                sprintf(filepath_Admin, "admins/%s.dat", user->username);

                return fopen(filepath_Admin, "rb+");
            }
            else
            {
                printf("Wrong password!\n");
                // dbgsym => These are the codes meant for debugging
                // printf("Entered password's hash is \t %s\n", user->password_hash);
                // printf("Stored hash is \t %s\n", stored_password);
                return NULL;
            }
        }
    }

    printf("Username not found!\n");
    return 0;
}

// dbgsym:  issues
//----
//  spaces in password problem, only recognizes first part
//  two word name => name password

int signup(User *user)
{
    // user->password_file = fopen("../../admins/passwords.dat", "a+");
    if (user->password_file == NULL)
    {
        printf("Error opening passwords file!\n");
        return 0;
    }

    printf("Enter username: ");
    scanf("%s", user->username);

    char line[MAX_LINE_LENGTH];
    rewind(user->password_file);
    while (fgets(line, sizeof(line), user->password_file))
    {
        char *space = strchr(line, ' ');
        if (!space)
        {
            continue;
        }
        *space = '\0';

        if (strcmp(line, user->username) == 0)
        {
            printf("Username already exists!\n");
            intelligent_close(user->password_file);
            return 0;
        }
    }

    printf("Enter password: ");
    scanf(" %[^\n]", user->password);
    user->password_hash = haSha_512(user->password);

    fprintf(user->password_file, "%s %s\n", user->username, user->password_hash);
    // intelligent_close(user->password_file);
    printf("Signup successful!\n");

    // create file for admin
    char filename[MAX_USERNAME_LENGTH + 30];
    sprintf(filename, "admins/%s.dat", user->username);
    FILE *admin_file = fopen(filename, "w");
    if (admin_file == NULL)
    {
        printf("Error creating admin file!\n");
        return 0;
    }
    double zero_input = 0;
    fwrite(&zero_input, sizeof(zero_input), 1, admin_file);
    intelligent_close(admin_file);

    return 1;
}

/*
Coded by Ahsan, 62
*/