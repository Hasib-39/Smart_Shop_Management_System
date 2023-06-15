#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customerLogin.c"
#include "../cosmetics/ANSI.h"
#include "../Snippets.c"


FILE* login();

void CustomerAccess(FILE** Customer) {
    int choice;

    do {
        printf("%s%s%s",BLUE, BOLD, UNDERLINE);
        printf("Choose an option:\n");
        printf("%s%s%s",RESET, RED, BOLD);
        printf("\t1. Customer Account\n");
        printf("\t0. Back to main menu\n");
        printf("%s", GREEN);
        scanf("%d", &choice);

        if (choice == 1) {
            if ((*Customer=customerLogin())){
                printf("%p", *Customer);
                filePrinter(*Customer);
                return;
            }
        } else if (choice != 0) {
            printf("Invalid choice!\n");
        }
    } while (choice != 0);
    return;
}

//FILE* login() {
// }