# Project Description

This project is a command-line application for managing a store's inventory and handling customer transactions. It provides functionality for adding, removing, updating, and displaying products in the inventory. It also allows customers to make purchases and generates bills for the transactions.

## Project Structure

The project consists of the following files and directories:

- `main.c`: The main file containing the program's entry point and menu options.
- `library/accounts/AdminAccess.c`: A library file for handling administrative access.
- `library/cosmetics/ANSI.h`: A library file for ANSI color codes used in the command-line interface.
- `library/Snippets.c`: A library file containing miscellaneous utility functions.
- `item_management.h`: A header file for item management functions (not included in the provided code).
- `items/`: A directory containing data files related to the store's inventory.
- `admins/`: A directory containing data files for admin accounts.

## Functionality

The project provides the following functionality:

### Admin Access

- Administrative users can log in to the system by entering their username and password.
- The system checks the provided credentials against the data stored in the `admins/` directory.

### Item Management

- Admin users can add new products to the inventory by providing details such as ID, name, price, discount, and quantity.
- Existing products can be removed from the inventory by specifying their ID.
- Products in the inventory can be updated based on various criteria, including ID, name, price, quantity, discount, or all fields.

### Display Product

- The current inventory can be displayed, showing the ID, name, price, discount, and quantity of each product.

### Sell Product

- Customers can make purchases by selecting items from the inventory and specifying the quantity.
- The system calculates the total price, including any applicable discounts, for the selected items.
- A bill is generated for the customer, showing the purchased items, quantity, price, and discount applied.
- The system also keeps track of the total selling amount for each admin user.

### Total Amount Sold

- Admin users can check the total selling amount associated with their account.

## Usage

To use this project, follow these steps:

1. Compile the provided source code files using a C compiler.
2. Run the compiled executable.
3. Follow the on-screen instructions to navigate through the menu options.
4. Enter the required information for each operation, such as adding, removing, or updating products, and making purchases.
5. Interact with the command-line interface to manage the store's inventory and handle customer transactions.

Please note that the provided code may have additional dependencies or requirements not explicitly mentioned. Ensure that your system meets those requirements for successful compilation and execution.

