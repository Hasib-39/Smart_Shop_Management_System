#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library/accounts/AdminAccess.c"
#include "library/cosmetics/ANSI.h"
#include "library/Snippets.c"
#include <math.h>
#include <time.h>

char filename_customer[150];
struct check
{
    int id;
    char name[50];
    int quantity;
    double discount;
    double price;
};
struct customer
{
    char name[30];
    double discount;
    double buying_amount;
};

// #include "item_management.h"
struct Item
{
    int id;
    char name[50];
    double price;
    double discount;
    int quantity;
};

// Prototypes:
void total_amount_sold();
void CustomerAccess(FILE *Admin, FILE *Customer);
void item_management(FILE *Admin);
void add_product();
void remove_product();
void update_product();
void display_product();
void Sell_product(FILE *Admin, FILE *Customer);
void Bill_body(struct Item *item1, int index, int quantity);
void check_customer_header();
void check_customer_footer(double netprice);
void del(int id, FILE *fp);
void cash_reserve();
void Checkout_Menu(int index, FILE *Admin, FILE *Customer);

void total_amount_sold()
{
    FILE *fp;
    double value;
    system("cls");
    char username[50], filename[200];
    printf("%s%s", GREEN, BOLD);
    printf("Enter your username: ");
    fflush(stdin);
    gets(username);
    printf("\n");
    snprintf(filename, sizeof(filename), "admins/%s.dat", username);
    fp = fopen(filename, "rb");
    while (fread(&value, sizeof(value), 1, fp) == 1)
    {
        printf("%s%s", YELLOW, BOLD);
        printf("Your total selling amount: %0.2f\n", value);
    }
    fclose(fp);
    system("pause");
}
void add_product()
{
    system("cls");
    fflush(stdin);
    display_product();
    FILE *fp, *id_checker;
    int item_id[200] = {0}, no_of_products;
    struct Item item1, item2;
    char ch;

    fp = fopen("items/items.dat", "ab");
    // dbgsym: Compatibility;
    printf("%s", MAGENTA, BOLD);
    printf("\t# Add Product #\n");
    printf("\nEnter the following details:\n\n");

    fflush(stdin);
    printf("%s", GREEN, BOLD);
    printf("Item ID: ");
    printf("%s", YELLOW, BOLD);
    scanf("%d", &item1.id);
    // checking validity of new product id
    id_checker = fopen("items/items.dat", "rb");
    while (fread(&item2, sizeof(item2), 1, id_checker) == 1)
    {
        if (item1.id == item2.id)
        {
            printf("%s%s", RED, BOLD);
            printf("Sorry!! Item ID already exists...\n");
            fclose(id_checker);
            fclose(fp);
            system("pause");
            exit(0);
        }
    }
    if ((item1.id) < 0)
    {
        printf("Sorry!! Please enter positive value.\n");
        fclose(fp);
        exit(0);
    }

    fflush(stdin);
    printf("%s", GREEN, BOLD);
    printf("Name: ");
    printf("%s", YELLOW, BOLD);
    gets(item1.name);

    fflush(stdin);
    printf("%s", GREEN, BOLD);
    printf("Price: ");
    printf("%s", YELLOW, BOLD);
    scanf("%lf", &item1.price);
    if ((item1.price) < 0)
    {
        printf("Sorry!! Please enter positive value.\n");
        fclose(fp);
        exit(0);
    }

    fflush(stdin);
    printf("%s", GREEN, BOLD);
    printf("Discount: ");
    printf("%s", YELLOW, BOLD);
    scanf("%lf", &item1.discount);
    if ((item1.discount) < 0)
    {
        printf("Sorry!! Please enter positive value.\n");
        fclose(fp);
        exit(0);
    }

    fflush(stdin);
    printf("%s", GREEN, BOLD);
    printf("Quantity: ");
    printf("%s", YELLOW, BOLD);
    scanf("%d", &item1.quantity);
    if ((item1.quantity) < 0)
    {
        printf("Sorry!! Please enter positive value.\n");
        fclose(fp);
        exit(0);
    }

    fwrite(&item1, sizeof(item1), 1, fp);
    fclose(fp);

    printf("%s", CYAN, BOLD);
    printf("Product Added Successfully....\n");
}
void del(int id, FILE *fp)
{
    int f = 0;
    struct Item item1;
    FILE *ft, *fp1;

    fp1 = fopen("items//items.dat", "rb");
    ft = fopen("items//temp.dat", "wb");

    while (fread(&item1, sizeof(item1), 1, fp1) == 1)
    {
        if (item1.id == id)
        {
            f = 1;
        }
        else
        {
            fwrite(&item1, sizeof(item1), 1, ft);
        }
    }
    fclose(fp1);
    fclose(ft);
    ft = fopen("items/temp.dat", "rb");
    fp = fopen("items/items.dat", "wb");
    while (fread(&item1, sizeof(item1), 1, ft) == 1)
    {
        fwrite(&item1, sizeof(item1), 1, fp);
    }
    fclose(fp);
    fclose(ft);
    // int a,b;
    // printf("before\n");
    // a = remove("items/items.dat");
    // b = rename("items/temp.dat", "items/items.dat");
    // printf("after\n");
}
void remove_product()
{
    system("cls");
    fflush(stdin);
    display_product();
    int id, f;
    printf("\t# Remove Product #\n");
    printf("%s", GREEN, BOLD);
    printf("\nEnter the ID of the product to be removed: ");
    printf("%s", YELLOW, BOLD);
    scanf("%d", &id);
    FILE *fp;

    struct Item item1;

    fp = fopen("items/items.dat", "rb+");

    while (fread(&item1, sizeof(item1), 1, fp) == 1)
    {
        fflush(stdin);
        if (item1.id == id)
        {
            f = 1;
            fclose(fp);
            break;
        }
    }
    if (f == 1)
    {
        printf("%s", BLUE, BOLD);
        printf("\nProduct Deleted Successfully....\n");
        del(id, fp);
    }
    else
    {
        printf("%s", CYAN, BOLD);
        printf("\nProduct Not Found....\n");
    }

    // printf("before\n");
    // int re_name, re_move;
    // re_move = remove("items/items.dat");
    // re_name = rename("items/temp.dat", "items/items.dat");
    // printf("after\n");
}
void update_product()
{
    system("cls");
    display_product();
    struct Item item1;
    int f = 0, negative = 0;
    int id, criteria;
    FILE *fp;
    printf("%s", MAGENTA, BOLD);
    printf("\t # Update Product #\n");
    printf("Update Criterias:\n");
    printf("%s", CYAN, BOLD);
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Price\n");
    printf("4. Quantity\n");
    printf("5. Discount\n");
    printf("6. All\n");
    // add quantity, price edit, discount edit, whole edit
    // eita korte hobe
    printf("%s", GREEN, BOLD);
    printf("\nEnter your desired updating criteria: ");
    printf("%s", YELLOW, BOLD);
    scanf("%d", &criteria);
    printf("%s", GREEN, BOLD);
    printf("\nEnter the ID of the product to be updated: ");
    printf("%s", YELLOW, BOLD);
    scanf("%d", &id);

    switch (criteria)
    {
    case 1:
        fp = fopen("items/items.dat", "rb+");
        // dbgsym: Compatibility;
        while (fread(&item1, sizeof(item1), 1, fp) == 1)
        {
            if (id == item1.id)
            {
                f = 1;
                printf("%s", GREEN, BOLD);
                printf("Enter New ID: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                scanf("%d", &item1.id);
                if ((item1.id) < 0)
                {
                    printf("Sorry!! Please enter positive value.\n");
                    negative = 1;
                    fclose(fp);
                    break;
                }

                fseek(fp, -sizeof(item1), 1);
                fwrite(&item1, sizeof(item1), 1, fp);
                fclose(fp);
                break;
            }
        }

        break;
    case 2:
        fp = fopen("items/items.dat", "rb+");
        // dbgsym: Compatibility;
        while (fread(&item1, sizeof(item1), 1, fp) == 1)
        {
            if (id == item1.id)
            {
                f = 1;
                printf("%s", GREEN, BOLD);
                printf("Enter the new name: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                gets(item1.name);

                fseek(fp, -sizeof(item1), 1);
                fwrite(&item1, sizeof(item1), 1, fp);
                fclose(fp);
                break;
            }
        }
        break;
    case 3:
        fp = fopen("items/items.dat", "rb+");
        // dbgsym: Compatibility;
        while (fread(&item1, sizeof(item1), 1, fp) == 1)
        {
            if (id == item1.id)
            {
                f = 1;
                printf("%s", GREEN, BOLD);
                printf("Enter new price: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                scanf("%lf", &item1.price);
                if ((item1.price) < 0)
                {
                    printf("Sorry!! Please enter positive value.\n");
                    negative = 1;
                    fclose(fp);
                    break;
                }

                fseek(fp, -sizeof(item1), 1);
                fwrite(&item1, sizeof(item1), 1, fp);
                fclose(fp);
                break;
            }
        }
        break;
    case 4:
        fp = fopen("items/items.dat", "rb+");
        // dbgsym: Compatibility;
        while (fread(&item1, sizeof(item1), 1, fp) == 1)
        {
            if (id == item1.id)
            {
                f = 1;
                printf("%s", GREEN, BOLD);
                printf("Enter new quantity: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                scanf("%d", &item1.quantity);
                if ((item1.quantity) < 0)
                {
                    printf("Sorry!! Please enter positive value.\n");
                    negative = 1;
                    fclose(fp);
                    break;
                }

                fseek(fp, -sizeof(item1), 1);
                fwrite(&item1, sizeof(item1), 1, fp);
                fclose(fp);
                break;
            }
        }
        break;
    case 5:
        fp = fopen("items/items.dat", "rb+");
        // dbgsym: Compatibility;
        while (fread(&item1, sizeof(item1), 1, fp) == 1)
        {
            if (id == item1.id)
            {
                f = 1;
                printf("%s", GREEN, BOLD);
                printf("Enter new discount: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                scanf("%lf", &item1.discount);
                if ((item1.discount) < 0)
                {
                    printf("Sorry!! Please enter positive value.\n");
                    negative = 1;
                    fclose(fp);
                    break;
                }

                fseek(fp, -sizeof(item1), 1);
                fwrite(&item1, sizeof(item1), 1, fp);
                fclose(fp);
                break;
            }
        }
        break;
    case 6:
        fp = fopen("items/items.dat", "rb+");
        // dbgsym: Compatibility;
        while (fread(&item1, sizeof(item1), 1, fp) == 1)
        {
            if (id == item1.id)
            {
                f = 1;
                printf("%s", GREEN, BOLD);
                printf("Enter ID: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                scanf("%d", &item1.id);
                if ((item1.id) < 0)
                {
                    printf("Sorry!! Please enter positive value.\n");
                    negative = 1;
                    fclose(fp);
                    break;
                }

                printf("%s", GREEN, BOLD);
                printf("Enter the new name: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                gets(item1.name);

                printf("%s", GREEN, BOLD);
                printf("Enter new quantity: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                scanf("%d", &item1.quantity);
                if ((item1.quantity) < 0)
                {
                    printf("Sorry!! Please enter positive value.\n");
                    negative = 1;
                    fclose(fp);
                    break;
                }

                printf("%s", GREEN, BOLD);
                printf("Enter new price: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                scanf("%lf", &item1.price);
                if ((item1.price) < 0)
                {
                    printf("Sorry!! Please enter positive value.\n");
                    negative = 1;
                    fclose(fp);
                    break;
                }

                printf("%s", GREEN, BOLD);
                printf("Enter new discount: ");
                fflush(stdin);
                printf("%s", YELLOW, BOLD);
                scanf("%lf", &item1.discount);
                if ((item1.discount) < 0)
                {
                    printf("Sorry!! Please enter positive value.\n");
                    negative = 1;
                    fclose(fp);
                    break;
                }

                fseek(fp, -sizeof(item1), 1);
                fwrite(&item1, sizeof(item1), 1, fp);
                fclose(fp);
                break;
            }
        }
        break;
    }

    if (f == 1 && negative == 0)
    {
        printf("%s", BLUE, BOLD);
        printf("Product Updated Successfully....\n");
    }
    else if (f == 0 && negative == 0)
    {
        printf("%s", CYAN, BOLD);
        printf("Product not found....\n");
    }
}
void display_product()
{
    system("cls");

    struct Item item1;
    FILE *fp;
    printf("%s", MAGENTA, BOLD);

    printf("                                             # Product List #                \n");
    printf("*******************************************************************************************************\n");
    printf("%-10s %-30s %-20s %-20s %-20s\n", "ID", "Name", "Price(TK.)", "Discount(%)", "Quantity");
    printf("*******************************************************************************************************\n");

    fp = fopen("items/items.dat", "rb");
    // dbgsym: Compatibility;
    while (fread(&item1, sizeof(item1), 1, fp) == 1)
    {
        printf("%s", CYAN, BOLD);
        printf("%-10d %-30s %-20.2lf %-20.2lf %-20d\n", item1.id, item1.name, item1.price, item1.discount, item1.quantity);
    }
    printf("\n");
    fclose(fp);
}
void Sell_product(FILE *Admin, FILE *Customer)
{
    system("cls");
    fflush(stdin);
    struct Item item1;
    FILE *fp;
    int f = 0, negative = 0, large = 0;
    int exist;
    char checkout;
    int id, quantity, i = 1;
    display_product();
    printf("%s", MAGENTA, BOLD);
    printf("\t# Sell Product #\n");
    // double total = 0;
    while (1)
    {
        exist = 0;
        system("cls");
        display_product();
        printf("%s", MAGENTA, BOLD);
        printf("\n\t# Adding Product no %d #", i);
        i++;
        printf("%s", GREEN, BOLD);
        printf("\nEnter ID of product to buy: ");
        printf("%s", YELLOW, BOLD);
        scanf("%d", &id);
        if (id < 0)
        {
            printf("Sorry!! Please enter positive value.\n");
            negative = 1;
            break;
        }

        printf("%s", GREEN, BOLD);
        printf("\nEnter the quantity: ");
        printf("%s", YELLOW, BOLD);
        fflush(stdin);
        scanf("%d", &quantity);
        if (quantity < 0)
        {
            printf("Sorry!! Please enter positive value.\n");
            negative = 1;
            break;
        }
        fp = fopen("items/items.dat", "rb+");

        // dbgsym: Compatibility;
        while (fread(&item1, sizeof(item1), 1, fp) == 1)
        {

            if (id == (item1.id))
            {
                if ((item1.quantity) < quantity)
                {
                    large = 1;
                    printf("Sorry!! You entered invalid quantity\n");
                    break;
                }
                exist = 1;
                item1.quantity = (item1.quantity) - quantity;
                fseek(fp, -sizeof(item1), 1);
                fwrite(&item1, sizeof(item1), 1, fp);
                Bill_body(&item1, i, quantity);
                // total += (item1.price) * (item1.quantity);
                fclose(fp);
                if (item1.quantity == 0)
                {
                    del(item1.id, fp);
                }
                break;
            }
            else if (id == (item1.id))
            {
                exist = 1;
                printf("\nSorry!! Product Quantity is less than your required quantity...");
                printf("\nPlease Enter again...");
                break;
            }
        }
        if (large == 1)
        {
            break;
        }
        if (exist && ((item1.quantity) >= quantity))
        {
            printf("%s", BLUE, BOLD);
            printf("\nProduct added to cart...\n");
        }

        else if (exist == 0)
        {
            printf("%s", CYAN, BOLD);
            printf("\nSorry! Your desired product no %d does not exist !!\n", i - 1);
            i = 1;
        }
        fflush(stdin);
        printf("%s", GREEN, BOLD);
        printf("\nPress * to checkout, # to continue: ");
        printf("%s", YELLOW, BOLD);
        scanf("%c", &checkout);
        printf("\n");
        if (checkout == '*')
        {
            f = 1;
            // check out codes should be here
            Checkout_Menu(i, Admin, Customer);
        }
        else if (checkout == '#')
            continue;
        if (f == 1)
        {
            printf("%s", BLUE, BOLD);
            printf("\nProduct bought successfully....\n");
            break;
        }
    }
}

void Bill_header()
{
    fflush(stdin);
    printf("\n");
    printf("%s", MAGENTA, BOLD);
    printf("                                        # Checkout #\n");
    printf("****************************************************************************************************************\n");
    // fprintf(fp, "\n                                        # Checkout #");
    // fprintf(fp, "\n****************************************************************************************************************\n");
    // printf("\nDate: %s",date);

    printf("%-10s %-30s %-20s %-20s %-20s\n", "ID", "Name", "Quantity", "Discount(%)", "Price(TK.)");
    // fprintf(fp, "%s\t%s\t\t\t%s\t%s\t%s\n", "ID", "Name", "Quantity", "Discount", "Price");

    printf("****************************************************************************************************************\n");
    // fprintf(fp, "****************************************************************************************************************\n");
}
void Bill_body(struct Item *item1, int index, int quantity)
{
    double customer_discount;
    FILE *customer;
    struct customer customer1;
    customer = fopen(filename_customer, "rb");
    while (fread(&customer1, sizeof(customer1), 1, customer) == 1)
    {
        int total_bought = floor(customer1.buying_amount);
        if (total_bought >= 20000)
        {
            customer1.discount = 5;
            customer_discount = 5;
        }
        else if (total_bought >= 50000)
        {
            customer1.discount = 8;
            customer_discount = 8;
        }
        else
        {
            customer1.discount = 0;
            customer_discount = 0;
        }
    }
    fclose(customer);
    customer = fopen(filename_customer, "wb");
    fwrite(&customer1, sizeof(customer1), 1, customer);
    fclose(customer);

    double netprice = ((item1->price) * quantity) - ((item1->discount) / 100) * ((item1->price) * quantity);
    FILE *fp;
    struct check check1;
    check1.id = item1->id;
    strcpy(check1.name, item1->name);
    check1.quantity = quantity;
    check1.discount = item1->discount;
    check1.price = netprice;

    fp = fopen("items/check.dat", "a");
    // fprintf(fp, "%-10d %-30s %-20d %-20.2lf %-20.2lf\n", index, check1.name, check1.quantity, check1.discount, check1.price);
    fwrite(&check1, sizeof(check1), 1, fp);
    fclose(fp);
    // printf("%-10d %-30s %-20d %-20lf %-20lf\n", index, item1->name ,quantity, item1->discount, netprice);
}
void Bill_footer(double netprice)
{
    printf("%s", MAGENTA, BOLD);
    printf("\n----------------------------------------------------------------------------------------");
    printf("%s", CYAN, BOLD);
    FILE *fp;
    struct customer customer1;
    double discount_price;
    fp = fopen(filename_customer, "rb");
    while (fread(&customer1, sizeof(customer1), 1, fp) == 1)
    {
        int discount = floor(customer1.discount);
        if (discount > 0)
        {
            discount_price = (netprice * (customer1.discount)) / 100;
            printf("\n%-20s %-60.2lf", "Total :", netprice);
            printf("\n%s%0.0lf%s %-120.2lf", "Discount(", customer1.discount, "%):   ", discount_price);
            printf("\n%-20s %-120.2lf", "Total(including discount):", (netprice - discount_price));
        }
        else
        {
            printf("\n%-20s %-120.2lf", "Grand Total:", netprice);
        }
    }
    printf("%s", MAGENTA, BOLD);
    printf("\n----------------------------------------------------------------------------------------\n");
}
void check_customer_header()
{
    FILE *fp2;
    fp2 = fopen("items/check_customer.dat", "a");

    if (fp2 == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp2, "\t# Customer Checkout #\n");
    fprintf(fp2, "*******************************************\n");
    fprintf(fp2, "%-10s %-30s %-20s %-20s %-20s\n", "ID", "Name", "Quantity", "Discount", "Price");
    fprintf(fp2, "******************************************************************************************************************\n");

    fclose(fp2);
}

void check_customer_footer(double netprice)
{
    FILE *fp2;
    fflush(stdin);
    fp2 = fopen("items/check_customer.dat", "a");
    fprintf(fp2, "\n----------------------------------------------------------------------------------------");
    FILE *fp;
    struct customer customer1;
    double discount_price;
    fp = fopen(filename_customer, "rb");
    while (fread(&customer1, sizeof(customer1), 1, fp) == 1)
    {
        int discount = floor(customer1.discount);
        if (discount > 0)
        {
            discount_price = (netprice * (customer1.discount)) / 100;
            fprintf(fp2, "\n%-20s %-60.2lf", "Total :", netprice);
            fprintf(fp2, "\n%s%0.0lf%s %-120.2lf", "Discount(", customer1.discount, "%) :", discount_price);
            fprintf(fp2, "\n%-20s %-120.2lf", "Total(including discount):", (netprice - discount_price));
        }
        else
        {
            fprintf(fp2, "\n%-20s %-120.2lf", "Grand Total:", netprice);
        }
    }
    fprintf(fp2, "\n----------------------------------------------------------------------------------------\n");
    fprintf(fp2, "\n* * * Thank you for visiting our shop * * *\n");
    fclose(fp2);
}
void cash_reserve()
{
    FILE *fp;
    double x;
    fp = fopen("items/cash.dat", "rb");
    if (fread(&x, sizeof(x), 1, fp) == 1)
    {
        system("cls");
        printf("%s", GREEN, BOLD);
        printf("\n\tCurrent Account balance is: %.2lf\n\n", x);
    }
    fclose(fp);
}
void Checkout_Menu(int index, FILE *Admin, FILE *Customer)
{
    // FILE *fp, *fp2;

    system("cls");
    fflush(stdin);
    time_t t;
    time(&t);
    printf("%s%s", GREEN, BOLD);
    printf("Time: %s\n", ctime(&t));
    FILE *fp, *fp2;
    fp = fopen("items/check_customer.dat", "w");
    fprintf(fp, "Time: %s\n", ctime(&t));

    printf("Customer name: ");
    FILE *name;
    name = fopen(filename_customer, "rb");
    struct customer customer1;
    while (fread(&customer1, sizeof(customer1), 1, name) == 1)
    {
        puts(customer1.name);
        printf("\n");
        fprintf(fp, "Customer name: %s\n", customer1.name);
    }
    fclose(name);
    fclose(fp);
    Bill_header();
    check_customer_header();
    double total = 0;
    struct check check1;
    fp2 = fopen("items/check_customer.dat", "a");
    fp = fopen("items/check.dat", "r");
    if (fp == NULL)
    {
        printf("%s", CYAN, BOLD);
        printf("File not found");
        exit(0);
    }
    for (int i = 1; i < index; i++)
    {
        fread(&check1, sizeof(check1), 1, fp);
        total = total + check1.price;
        printf("%s", CYAN, BOLD);
        printf("%-10d %-30s %-20d %-20.2lf %-20.2lf\n", i, check1.name, check1.quantity, check1.discount, check1.price);
        // fwrite(&i, 1, sizeof(i), fp2);
        // fwrite(&check1, 1, sizeof(check1), fp2);
        fprintf(fp2, "%-10d %-30s %-20d %-20.2lf %-20.2lf\n", i, check1.name, check1.quantity, check1.discount, check1.price);
    }
    fclose(fp);
    fclose(fp2);
    remove("items/check.dat");
    Bill_footer(total);
    check_customer_footer(total);
    double cash_reserve;
    double Admin_sell;
    double Customer_buy;
    fp = fopen("items/cash.dat", "rb");
    while (fread(&cash_reserve, sizeof(cash_reserve), 1, fp) == 1)
    {
        cash_reserve = cash_reserve + total;
    }
    fclose(fp);
    fp = fopen("items/cash.dat", "wb");
    fwrite(&cash_reserve, sizeof(cash_reserve), 1, fp);
    fclose(fp);

    // admin editing
    while (fread(&Admin_sell, sizeof(Admin_sell), 1, Admin) == 1)
    {
        Admin_sell = Admin_sell + total;
    }
    fclose(Admin);
    Admin = fopen(filepath_Admin, "wb");
    fwrite(&Admin_sell, sizeof(Admin_sell), 1, Admin);
    fclose(Admin);

    // Customer editing
    while (fread(&customer1, sizeof(customer1), 1, Customer) == 1)
    {
        (customer1.buying_amount) = ((customer1.buying_amount) + total);
    }
    fclose(Customer);
    Customer = fopen(filename_customer, "wb");
    fwrite(&customer1, sizeof(customer1), 1, Customer);
    fclose(Customer);
}
void item_management(FILE *Admin)
{
    system("cls");
    int choice;
    FILE *Customer;
    while (1)
    {
        // system("cls");
        printf("%s%s", YELLOW, BOLD);
        printf("*********************************************************\n");
        printf("                  Admin Management Menu                \n");
        fflush(stdin);
        printf("*********************************************************\n");
        printf("%s%s", CYAN, BOLD);
        printf("\t1.Add Product\n");
        printf("\t2.Remove Product\n");
        printf("\t3.Update Product\n");
        printf("\t4.Display Product\n");
        printf("\t5.Sell Product\n");
        printf("\t6.Check cash reserve\n");
        printf("\t7.Check total amount sold\n");
        printf("\t0.Exit\n");
        printf("\n");
        printf("%s", GREEN, BOLD);
        printf("Please Enter your choice: ");
        printf("%s", YELLOW, BOLD);
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            exit(0);
        case 1:
            add_product();
            break;
        case 2:
            remove_product();
            break;
        case 3:
            update_product();
            break;
        case 4:
            display_product();
            break;
        case 5:
            CustomerAccess(Admin, Customer);
            break;
        case 6:
            cash_reserve();
            break;
        case 7:
            total_amount_sold();
            break;
        default:
            printf("Wrong choice!! Please enter valid input\n");
            system("pause");
            break;
        }
    }
}
void CustomerAccess(FILE *Admin, FILE *Customer)
{
    char phone_no[15], path[50];
    int digits, i, len;
    FILE *existance;

    while (1)
    {
        system("cls");
        fflush(stdin);
        printf("%s", GREEN, BOLD);
        printf("Enter the phone number of the Customer: ");
        printf("%s", YELLOW, BOLD);
        scanf("%14s", phone_no);

        // Phone No Validation Code
        len = strlen(phone_no);
        digits = 0;
        for (i = 0; i < 11; i++)
        {
            if (phone_no[i] >= '0' && phone_no[i] <= '9')
            {
                digits++;
            }
        }
        // printf("Lenght: %d\t Digits: %d", len, digits);

        if (digits != 11 || (len != 11))
        {
            printf("%s", CYAN, BOLD);
            printf("[Invalid Input]: A phone number should be all numbers, of 11 digit. please try again....\n");
        }
        else
            break;
    }

    // char filepath[150];
    snprintf(filename_customer, sizeof(filename_customer), "customers/%s.dat", phone_no);

    existance = fopen(filename_customer, "rb");

    // If cant open, means he's new customer
    if (!existance)
    {

        existance = fopen(filename_customer, "wb");

        if (existance == NULL)
        {
            printf("%s", CYAN, BOLD);
            printf("[ERROR!] : Error occured handling customer file.....\n");
            exit(1);
        }
        else
        {
            fflush(stdin);
            struct customer customer1;
            printf("%s", MAGENTA, BOLD);
            printf("Enter the following details: \n");
            printf("%s", GREEN, BOLD);
            printf("Customer name: ");
            printf("%s", YELLOW, BOLD);
            gets(customer1.name);
            customer1.buying_amount = 0;
            customer1.discount = 0;
            fflush(stdin);
            fwrite(&customer1, sizeof(customer1), 1, existance);
        }
    }
    else
    {
        intelligent_close(existance);
    }
    // printf("%p\n", existance);
    intelligent_close(existance);
    existance = fopen(filename_customer, "rb+");
    Customer = existance;
    Sell_product(Admin, Customer);
}

int main()
{

    FILE *Admin;
    FILE *Customer;

    system("cls");
    AdminAccess(Admin);

    intelligent_close(Admin);
    intelligent_close(Customer);
    return 0;
}
