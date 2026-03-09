#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <limits>
using namespace std;

/* ================= ENUMS ================= */
enum class TransactionType { Revenue, Expense };
enum class OrderStatus { Requested, Approved };

/* ================= TRANSACTION CLASS ================= */
class Transaction {
public:
    TransactionType type;
    double amount;

    Transaction(TransactionType t, double a) {
        type = t;
        amount = a;
    }

    string getTypeStr() {
        return (type == TransactionType::Revenue) ? "Revenue" : "Expense";
    }
};

/* ================= ANALYTICS SYSTEM ================= */
class AnalyticsSystem {
private:
    vector<Transaction> transactions;

public:
    void loadTransactions() {
        ifstream file("transactions.txt");
        if (!file.is_open()) {
            cout << "No previous transactions found.\n";
            return;
        }

        string typeStr;
        double amount;
        while (file >> typeStr >> amount) {
            TransactionType type = (typeStr == "Revenue") ? TransactionType::Revenue : TransactionType::Expense;
            transactions.push_back(Transaction(type, amount));
        }
        file.close();
    }

    void addTransaction() {
        string typeStr;
        double amount;

        do {
            cout << "Enter Type (Revenue/Expense): ";
            cin >> typeStr;
        } while (typeStr != "Revenue" && typeStr != "Expense");

        do {
            cout << "Enter Amount: ";
            cin >> amount;
            if(amount < 0) cout << "Amount cannot be negative!\n";
        } while(amount < 0);

        TransactionType type = (typeStr == "Revenue") ? TransactionType::Revenue : TransactionType::Expense;
        transactions.push_back(Transaction(type, amount));

        ofstream file("transactions.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Error opening transactions.txt!\n";
            return;
        }
        file << typeStr << " " << amount << endl;
        file.close();

        cout << "Transaction Added Successfully!\n";
    }

    void generateReport() {
        double totalRevenue = 0, totalExpense = 0;
        double maxRevenue = 0, maxExpense = 0;
        int revenueCount = 0, expenseCount = 0;

        for (auto &t : transactions) {
            if (t.type == TransactionType::Revenue) {
                totalRevenue += t.amount;
                revenueCount++;
                if (t.amount > maxRevenue) maxRevenue = t.amount;
            } else {
                totalExpense += t.amount;
                expenseCount++;
                if (t.amount > maxExpense) maxExpense = t.amount;
            }
        }

        cout << "\n====== ANALYTICS REPORT ======\n";
        cout << "Total Revenue: " << totalRevenue << endl;
        cout << "Total Expense: " << totalExpense << endl;
        cout << "Net Profit: " << totalRevenue - totalExpense << endl;
        cout << "Number of Revenue Transactions: " << revenueCount << endl;
        cout << "Number of Expense Transactions: " << expenseCount << endl;
        cout << "Highest Revenue Transaction: " << maxRevenue << endl;
        cout << "Highest Expense Transaction: " << maxExpense << endl;
        cout << "Average Revenue: " << (revenueCount ? totalRevenue / revenueCount : 0) << endl;
        cout << "Average Expense: " << (expenseCount ? totalExpense / expenseCount : 0) << endl;
        cout << "==============================\n";
    }
};

/* ================= PURCHASE ORDER CLASS ================= */
class PurchaseOrder {
public:
    int id;
    string vendor;
    string item;
    int quantity;
    double price;
    OrderStatus status;
    string creationDate;
    string approvalDate;

    PurchaseOrder(int i, string v, string it, int q, double p) {
        id = i;
        vendor = v;
        item = it;
        quantity = q;
        price = p;
        status = OrderStatus::Requested;

        time_t now = time(0);
        creationDate = string(ctime(&now));
        approvalDate = "Not Approved";
        if (!creationDate.empty() && creationDate.back() == '\n') creationDate.pop_back();
    }

    double totalAmount() { return quantity * price; }

    string getStatusStr() { return (status == OrderStatus::Requested) ? "Requested" : "Approved"; }
};

/* ================= PROCUREMENT SYSTEM ================= */
class ProcurementSystem {
private:
    vector<PurchaseOrder> orders;
    int orderCounter = 1;

public:
    void loadOrders() {
        ifstream file("orders.txt");
        if (!file.is_open()) {
            cout << "No previous orders found.\n";
            return;
        }

        int id, quantity;
        double price;
        string vendor, item, statusStr, creationDate, approvalDate;

        while (file >> id) {
            file.ignore();
            getline(file, vendor, '|');
            getline(file, item, '|');
            file >> quantity >> price >> statusStr;
            file.ignore();
            getline(file, creationDate, '|');
            getline(file, approvalDate);

            PurchaseOrder po(id, vendor, item, quantity, price);
            po.status = (statusStr == "Approved") ? OrderStatus::Approved : OrderStatus::Requested;
            po.creationDate = creationDate;
            po.approvalDate = approvalDate;

            orders.push_back(po);
            if (id >= orderCounter) orderCounter = id + 1;
        }
        file.close();
    }

    void saveOrders() {
        ofstream file("orders.txt");
        if (!file.is_open()) {
            cerr << "Error opening orders.txt!\n";
            return;
        }

        for (auto &o : orders) {
            file << o.id << " " << o.vendor << "|" << o.item << "|"
                 << o.quantity << " " << o.price << " " << o.getStatusStr()
                 << "|" << o.creationDate << "|" << o.approvalDate << endl;
        }
        file.close();
    }

    void createRequest() {
        string vendor, item;
        int quantity;
        double price;

        cin.ignore();
        cout << "Enter Vendor Name: ";
        getline(cin, vendor);
        cout << "Enter Item Name: ";
        getline(cin, item);

        do {
            cout << "Enter Quantity: ";
            cin >> quantity;
            if (quantity <= 0) cout << "Quantity must be positive!\n";
        } while (quantity <= 0);

        do {
            cout << "Enter Price per Item: ";
            cin >> price;
            if (price < 0) cout << "Price cannot be negative!\n";
        } while (price < 0);

        PurchaseOrder po(orderCounter++, vendor, item, quantity, price);
        orders.push_back(po);
        saveOrders();

        cout << "Purchase Request Created (ID: " << po.id << ")\n";
    }

    void approveOrder() {
        int id;
        cout << "Enter Order ID to Approve: ";
        cin >> id;

        for (auto &o : orders) {
            if (o.id == id) {
                char confirm;
                cout << "Approve Order? (Y/N): ";
                cin >> confirm;
                if(confirm == 'Y' || confirm == 'y') {
                    o.status = OrderStatus::Approved;
                    time_t now = time(0);
                    o.approvalDate = string(ctime(&now));
                    if (!o.approvalDate.empty() && o.approvalDate.back() == '\n') o.approvalDate.pop_back();
                    saveOrders();
                    cout << "Order Approved!\n";
                } else {
                    cout << "Approval Cancelled.\n";
                }
                return;
            }
        }
        cout << "Order Not Found!\n";
    }

    void viewOrders() {
        cout << "\n====== PURCHASE ORDERS ======\n";
        for (auto &o : orders) {
            cout << "ID: " << o.id
                 << " | Vendor: " << o.vendor
                 << " | Item: " << o.item
                 << " | Qty: " << o.quantity
                 << " | Total: " << o.totalAmount()
                 << " | Status: " << o.getStatusStr()
                 << " | Created: " << o.creationDate
                 << " | Approved: " << o.approvalDate << endl;
        }
        cout << "=============================\n";
    }
};

/* ================= MAIN MENU ================= */
int displayMenu() {
    int choice;
    cout << "\n===== BUSINESS MANAGEMENT SYSTEM =====\n";
    cout << "1. Add Transaction\n";
    cout << "2. Generate Analytics Report\n";
    cout << "3. Create Purchase Request\n";
    cout << "4. Approve Purchase Order\n";
    cout << "5. View Purchase Orders\n";
    cout << "6. Exit\n";
    cout << "Enter Choice: ";
    cin >> choice;
    return choice;
}

/* ================= MAIN FUNCTION ================= */
int main() {
    AnalyticsSystem analytics;
    ProcurementSystem procurement;

    analytics.loadTransactions();
    procurement.loadOrders();

    int choice;
    do {
        choice = displayMenu();
        switch (choice) {
        case 1:
            analytics.addTransaction();
            break;
        case 2:
            analytics.generateReport();
            break;
        case 3:
            procurement.createRequest();
            break;
        case 4:
            procurement.approveOrder();
            break;
        case 5:
            procurement.viewOrders();
            break;
        case 6:
            cout << "Exiting Program...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 6);

    return 0;
}