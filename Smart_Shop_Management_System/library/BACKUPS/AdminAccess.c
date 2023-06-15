#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/Library/GeneratePassword.c" 
#include "headers/ANSI.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_HASH_LENGTH 128 //A SHA-512 hash is 128 charecters
#define MAX_LINE_LENGTH (MAX_USERNAME_LENGTH + MAX_HASH_LENGTH + 2)

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char *password_hash;
    FILE *password_file;
} User;

int login(User *user);
int signup(User *user);

int main() {
    User user = {0};
    user.password_file = fopen("psswd/AdminPasswords.dat", "a+");
    int choice;

    do {
        printf("%s%s%s",YELLOW, BOLD, UNDERLINE);
        printf("Choose an option:\n");
        printf("%s%s%s",RESET, BLUE, BOLD);
        printf("\t1. Login\n");
        printf("\t2. Signup\n");
        printf("\t0. Exit\n");
        printf("%s", GREEN);
        scanf("%d", &choice);

        if (choice == 1) {
            login(&user);
        } else if (choice == 2) {
            if (signup(&user)) {
                printf("Account added, please try logging in\n");
                login(&user);
            }
        }else if (choice != 0) {
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    fclose(user.password_file);

    return 0;
}

int login(User *user) {

    printf("%s", MAGENTA);
    printf("Enter username: ");
    scanf("%s", user->username);
    printf("Enter password: ");
    printf("%s%s",HIDDEN, BG_WHITE);
    scanf(" %[^\n]", user->password);
    printf("%s", RESET);
    printf("%s%s", MAGENTA, BOLD);

    char line[MAX_LINE_LENGTH];
    rewind(user->password_file);
    while (fgets(line, sizeof(line), user->password_file)) {
        char *space = strchr(line, ' ');
        if (!space) {
            continue;
        }
        //Checking username
        *space = '\0';
        if (strcmp(line, user->username) == 0) {
            if (user->password_hash) {
                free(user->password_hash);
            }
            user->password_hash = haSha_512(user->password);
            char *stored_password = space + 1;
            stored_password[strcspn(stored_password, "\r\n")] = '\0';
            if (strcmp(stored_password, user->password_hash) == 0) {
                printf("Login successful!\n");
                return 1;
            } else {
                printf("Wrong password!\n");
                // dbgsym => These are the codes meant for debugging
                //printf("Entered password's hash is \t %s\n", user->password_hash);
                //printf("Stored hash is \t %s\n", stored_password);
                return 0;
            }
        }
    }

    printf("Username not found!\n");
    return 0;
}

//TODO
//----
// spaces in password problem, only recognizes first part
// two word name => name password 


int signup(User *user) {
    // user->password_file = fopen("admins/passwords.dat", "a+");
    if (user->password_file == NULL) {
        printf("Error opening passwords file!\n");
        return 0;
    }

    printf("Enter username: ");
    scanf("%s", user->username);

    char line[MAX_LINE_LENGTH];
    rewind(user->password_file);
    while (fgets(line, sizeof(line), user->password_file)) {
        char *space = strchr(line, ' ');
        if (!space) {
            continue;
        }
        *space = '\0';

        if (strcmp(line, user->username) == 0) {
            printf("Username already exists!\n");
            fclose(user->password_file);
            return 0;
        }
    }

    printf("Enter password: ");
    scanf(" %[^\n]", user->password);
    user->password_hash = haSha_512(user->password);

    fprintf(user->password_file, "%s %s\n", user->username, user->password_hash);
    //fclose(user->password_file);
    printf("Signup successful!\n");

    //create file for admin
    char filename[MAX_USERNAME_LENGTH + 30]; 
    sprintf(filename, "admins/%s.dat", user->username);
    FILE* admin_file = fopen(filename, "w");
    if (admin_file == NULL) {
        printf("Error creating admin file!\n");
        return 0;
    }
    fclose(admin_file);

    return 1;
}

/*
Coded by Ahsan, 62
*/