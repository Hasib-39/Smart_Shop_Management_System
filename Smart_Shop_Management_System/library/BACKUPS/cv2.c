//#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../cosmetics/ANSI.h"
#include "../Snippets.c"



FILE* login();

void CustomerAccess(FILE** Customer) {
    int choice;

    do {
        printf("%s%s%s",BLUE, BOLD, UNDERLINE);
        printf("Choose an option:\n");
        printf("%s%s%s",RESET, RED, BOLD);
        printf("\t1. Existing Customer\n");
        printf("\t2. New Customer\n");
        printf("\t0. Back to main menu\n");
        printf("%s", GREEN);
        scanf("%d", &choice);

        if (choice == 1) {
            if ((*Customer=login())){
                // printf("%p", Admin);
                // filePrinter(Admin);
                return;
            }
        // } else if (choice == 2) {
        //     if (signup(&user)) {
        //         printf("Account added, please try logging in\n");
        //         //login(&user);
        //     }
        // }else if (choice != 0) {
        //     printf("Invalid choice!\n");
         }
    } while (choice != 0);

}

FILE* login() {

    char phone_no[15];
    int v=0;

    printf("%s", MAGENTA);
    printf("Enter the phone number : ");
    
    scanf("%s",phone_no);

    // Phone No Validation Code
    for (int i = 0; i < 10; i++) {
        if (phone_no[i] < '0' || phone_no[i] > '9') {
            v++;
        }
    }

    if (!v && (strlen(phone_no) != 11)){

        printf("[Invalid Input]: A phone number should be all numbers, of 11 digit. please try again....");
    }

    return NULL;
}

int main(){

    FILE* Customer;

    CustomerAccess(&Customer);
    printf("%p\n",Customer);
}