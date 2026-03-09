# Business Management System

A **C++ console application** for managing business transactions and procurement processes. This system allows users to record revenue and expenses, generate analytics reports, and manage purchase orders including creation, approval, and viewing.

---

## Features

### 1. Analytics Module

* Add revenue or expense transactions.
* Automatically saves transactions to a file (`transactions.txt`) for persistence.
* Generate detailed analytics report including:

  * Total Revenue and Expenses
  * Net Profit
  * Number of Revenue and Expense Transactions
  * Highest Revenue/Expense Transaction
  * Average Revenue and Expense

### 2. Procurement Module

* Create purchase requests with details such as vendor, item, quantity, and price.
* Approve pending purchase orders with automatic timestamping.
* View all purchase orders with status, creation, and approval dates.
* Data is stored in `orders.txt` for persistence.

### 3. User Interface

* Simple console-based menu for navigation.
* Input validation for negative values, zero quantities, and correct transaction types.
* Confirmation prompts before approving purchase orders.

---

## Screenshots

**Main Menu Example:**

```
===== BUSINESS MANAGEMENT SYSTEM =====
1. Add Transaction
2. Generate Analytics Report
3. Create Purchase Request
4. Approve Purchase Order
5. View Purchase Orders
6. Exit
Enter Choice:
```

**Analytics Report Example:**

```
====== ANALYTICS REPORT ======
Total Revenue: 5000
Total Expense: 1200
Net Profit: 3800
Number of Revenue Transactions: 5
Number of Expense Transactions: 3
Highest Revenue Transaction: 2000
Highest Expense Transaction: 700
Average Revenue: 1000
Average Expense: 400
==============================
```

**Purchase Orders Example:**

```
====== PURCHASE ORDERS ======
ID: 1 | Vendor: ABC Corp | Item: Laptop | Qty: 2 | Total: 1500 | Status: Approved | Created: 09-Mar-2026 | Approved: 09-Mar-2026
ID: 2 | Vendor: XYZ Ltd | Item: Printer | Qty: 1 | Total: 300 | Status: Requested | Created: 09-Mar-2026 | Approved: Not Approved
=============================
```

---

## Installation

1. Clone the repository:

```bash
git clone https://github.com/yourusername/business-management-system.git
```

2. Navigate to the project folder:

```bash
cd business-management-system
```

3. Compile the code using a C++ compiler (e.g., g++):

```bash
g++ main.cpp -o BusinessSystem
```

4. Run the application:

```bash
./BusinessSystem    # Linux/Mac
BusinessSystem.exe  # Windows
```

---

## Usage

1. **Add Transaction**

   * Enter transaction type (`Revenue` or `Expense`).
   * Enter amount (must be positive).

2. **Generate Analytics Report**

   * Displays summary of all transactions including net profit, highest transaction, and averages.

3. **Create Purchase Request**

   * Enter vendor name, item name, quantity, and price.
   * Purchase request is saved to `orders.txt` as `Requested`.

4. **Approve Purchase Order**

   * Enter Order ID.
   * Confirm approval to mark order as `Approved`.

5. **View Purchase Orders**

   * Shows all purchase orders with full details including status, creation, and approval dates.

---

## Data Persistence

* **transactions.txt:** Stores all revenue and expense transactions.
* **orders.txt:** Stores all purchase orders with IDs, details, and status.

---

## Technology Stack

* **Language:** C++ (Standard C++11/14)
* **Libraries:**

  * `<iostream>` for input/output
  * `<vector>` for dynamic storage
  * `<fstream>` for file handling
  * `<ctime>` for timestamps
  * `<limits>` for input validation

---

## Project Structure

```
/BusinessManagementSystem
│
├── main.cpp            # Main program containing Analytics & Procurement modules
├── transactions.txt    # Data file for transactions
├── orders.txt          # Data file for purchase orders
└── README.md           # Project documentation
```

---

## Future Enhancements

* Integrate a **GUI interface** using Qt or SFML for better usability.
* Add **report export** functionality (CSV, PDF).
* Include **user authentication** for multi-user management.
* Add **sorting and filtering** options for purchase orders and transactions.
* Integrate with a **database** for large-scale data storage.

---

## License

This project is licensed under the MIT License. See the LICENSE file for details.

---
