#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CustomerAccess(FILE** Customer) {
    char phone_no[15], path[50];
    int digits, i, len;
    FILE* existance;

    while(1){
        printf("Enter the phone number : ");
        scanf("%14s",phone_no);
    
        // Phone No Validation Code
        len=strlen(phone_no);
        digits=0;
        for (i=0; i < 11; i++) {
            if (phone_no[i] >= '0' && phone_no[i] <= '9') {
                digits++;
            }
        }
        // printf("Lenght: %d\t Digits: %d", len, digits);

        if (digits!=11 || (len!= 11)){
            printf("[Invalid Input]: A phone number should be all numbers, of 11 digit. please try again....\n");
        }
        else break;

    }
    
    char filepath[150];
    snprintf(filepath, sizeof(filepath), "../../customers/%s.dat", phone_no);

    existance = fopen(filepath, "r");
    
    //If cant open, means he's new customer
    if(!existance){

        existance = fopen(filepath, "a+");

        if (existance == NULL) {
            printf("[ERROR!] : Error occured handling customer file.....\n");
            exit(1);
        }else {
            printf("Whatcha Name?\n");
        }
    }
    printf("%p\n", existance);
    *Customer=existance;
    return 0;
}