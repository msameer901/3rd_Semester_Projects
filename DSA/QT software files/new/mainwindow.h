#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <algorithm> // Required for priority sorting logic

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Data structures for Banking and Budgeting
struct Transaction {
    int id;
    int accountNumber;
    std::string type;
    float amount;
    float balanceAfter;
    std::string category; // Updated manually in Module 2
};

struct Account {
    int accountNumber;
    std::string name;
    float balance;
    std::vector<Transaction> history; // Vector used as a dynamic history list
};
// --- MODULE 3 STRUCTURE ---
struct Customer {
    int id;
    std::string name;
    int rowNumber;
    bool isPriority; // 1 for VIP, 0 for Normal
};
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Core Data Members
    std::vector<Account> accountsList;
    int globalTxId = 1; // System-generated unique ID for transactions
    // --- FIX: DECLARE THE QUEUE HERE ---
    std::vector<Customer> customerQueue; // This resolves your error
    // Helper functions
    Account* findAccount(int accNo);
    void refreshM2Display();

private slots:
    // Module 1 Slots
    void on_btnM1Enter_clicked();
    void on_comboM1Part_currentIndexChanged(int index);

    // Module 2 Slots (Manual connection)
    void classifyTransaction();
    void on_comboM2Part_currentIndexChanged(int index);
    // --- MODULE 3 SLOTS ---
    void on_btnM3Enter_clicked();
    void on_comboM3Part_currentIndexChanged(int index);
    // UI Navigation
    void toggleMenu();
};

#endif // MAINWINDOW_H
