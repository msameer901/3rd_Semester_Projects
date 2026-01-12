#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ================= MODULE 1 SETUP =================
    ui->comboM1Part->addItems({
        "Create Account",
        "Search Account",
        "Display All Accounts",
        "Deposit",
        "Withdraw",
        "Show History"
    });

    // ================= MODULE 2 SETUP =================
    ui->comboM2Part->addItems({
        "Categorize Transaction",
        "Show All Categorizations"
    });
    // ================= MODULE 3 SETUP =================
    // Paste the lines here:
    ui->comboM3Part->clear();
    ui->comboM3Part->addItems({"", "Add Customer", "Display Queue"});
    ui->m3InputBar->hide();

    // Also, don't forget to link your button to show Page M3
    connect(ui->pushButton_3, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->pageM3);
    });

    // Requirement: Show category codes for reference
    ui->label->setText("IBMS");
    ui->inputDescription->hide();

    // ================= NAVIGATION =================
    // Inside your MainWindow Constructor
    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->pageM1);
        // Hide menu if it's currently open (width > 0)
        if (ui->sideMenu->width() > 0) toggleMenu();
    });

    connect(ui->pushButton_2, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->pageM2);
        refreshM2Display(); // Ensure data is updated upon entry
        if (ui->sideMenu->width() > 0) toggleMenu();
    });

    connect(ui->pushButton_3, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->pageM3);
        if (ui->sideMenu->width() > 0) toggleMenu();
    });
    // ================= MANUAL CONNECTIONS =================
    // Manually connecting the Enter button for Module 2 classification
    connect(ui->btnClassify, &QPushButton::clicked,
            this, &MainWindow::classifyTransaction);

    connect(ui->inputDescription, &QLineEdit::returnPressed,
            this, &MainWindow::classifyTransaction);
}

MainWindow::~MainWindow() {
    delete ui;
}

// =====================================================
// MODULE 1: ACCOUNT & TRANSACTION MANAGEMENT
// =====================================================

void MainWindow::on_comboM1Part_currentIndexChanged(int) {
    QString selection = ui->comboM1Part->currentText();
    ui->m1InputBar->clear();
    ui->m1Output->clear();

    // Hide input bar for 'Display All Accounts' as only the Enter button is needed
    if (selection == "Display All Accounts") {
        ui->m1InputBar->hide();
    } else {
        ui->m1InputBar->show();
        // Dynamically change the guide text based on selection
        if (selection == "Search Account" || selection == "Show History")
            ui->m1InputBar->setPlaceholderText("Enter Account ID only");
        else if (selection == "Deposit" || selection == "Withdraw")
            ui->m1InputBar->setPlaceholderText("ID, Amount");
        else if (selection == "Create Account")
            ui->m1InputBar->setPlaceholderText("ID, Name, Balance");
    }
}

void MainWindow::on_btnM1Enter_clicked() {
    QString sel = ui->comboM1Part->currentText();
    QString input = ui->m1InputBar->text().trimmed();

    if (sel == "Create Account") {
        auto p = input.split(",");
        if (p.size() == 3) {
            accountsList.push_back({p[0].toInt(), p[1].toStdString(), p[2].toFloat(), {}});
            ui->m1Output->append("Account Created Successfully");
        }
    }
    else if (sel == "Deposit" || sel == "Withdraw") {
        auto p = input.split(",");
        if (p.size() == 2) {
            Account* acc = findAccount(p[0].toInt());
            if (!acc) {
                ui->m1Output->append("Account not found.");
                return;
            }

            float amt = p[1].toFloat();
            if (sel == "Withdraw" && amt > acc->balance) {
                ui->m1Output->append("Insufficient Balance!");
                return;
            }

            acc->balance += (sel == "Deposit") ? amt : -amt;

            // Generate unique transaction ID
            Transaction tx {
                globalTxId++, acc->accountNumber,
                sel.toStdString(), amt, acc->balance, ""
            };
            acc->history.push_back(tx);

            ui->m1Output->append(sel + " Done. Amount: $" + QString::number(amt) + " | TxID: " + QString::number(tx.id));
            ui->m1Output->append("New Total Balance: $" + QString::number(acc->balance));
        }
    }
    else if (sel == "Search Account") {
        Account* acc = findAccount(input.toInt()); // ID only search
        if (acc) ui->m1Output->append("Found: " + QString::fromStdString(acc->name) + " | Bal: $" + QString::number(acc->balance));
        else ui->m1Output->append("ID not found.");
    }
    else if (sel == "Display All Accounts") {
        ui->m1Output->clear();
        for (const auto& acc : accountsList) {
            ui->m1Output->append("ID: " + QString::number(acc.accountNumber) + " | Bal: $" + QString::number(acc.balance));
        }
    }
    else if (sel == "Show History") {
        Account* acc = findAccount(input.toInt()); // ID only history
        if (acc) {
            ui->m1Output->clear();
            ui->m1Output->append("--- History for Account " + input + " ---");
            for (const auto& tx : acc->history) {
                ui->m1Output->append("TxID: " + QString::number(tx.id) + " | " + QString::fromStdString(tx.type) + ": $" + QString::number(tx.amount));
            }
        }
    }
    ui->m1InputBar->clear();
}

// =====================================================
// MODULE 2: BUDGET CLASSIFICATION (NUMERIC)
// =====================================================

void MainWindow::on_comboM2Part_currentIndexChanged(int) {
    ui->lblResult->clear();
    // Requirement: Show input only for categorization
    ui->inputDescription->setVisible(ui->comboM2Part->currentText() == "Categorize Transaction");
}

void MainWindow::classifyTransaction() {
    QString input = ui->inputDescription->text().trimmed();
    auto p = input.split(",");

    if (p.size() != 2) {
        ui->lblResult->append("Use format: TxID,CategoryCode(0-4)");
        return;
    }

    int txId = p[0].toInt();
    int code = p[1].toInt();
    QStringList cats = {"Food","Utilities","Education","Government","Others"};

    if (code < 0 || code > 4) {
        ui->lblResult->append("Invalid Code. Use 0-4.");
        return;
    }

    bool found = false;
    // CRITICAL: Use '&' to modify the actual account and transaction
    for (auto &acc : accountsList) {
        for (auto &tx : acc.history) {
            if (tx.id == txId) {
                tx.category = cats[code].toStdString(); // Now it saves to memory
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (found) {
        ui->lblResult->append("ID " + QString::number(txId) + " saved as " + cats[code]);
        refreshM2Display(); // Update the display immediately
    } else {
        ui->lblResult->append("Transaction ID not found.");
    }
    ui->inputDescription->clear();
}
void MainWindow::refreshM2Display() {
    ui->lblResult->clear();
    ui->lblResult->append("<b>--- All Categorized Transactions ---</b>");
    bool dataFound = false;

    for (const auto &acc : accountsList) {
        for (const auto &tx : acc.history) {
            // Check if a category was actually set
            if (!tx.category.empty()) {
                dataFound = true;
                QString cat = QString::fromStdString(tx.category);
                ui->lblResult->append("TxID: " + QString::number(tx.id) +
                                      " | Amt: $" + QString::number(tx.amount, 'f', 2) +
                                      " | Category: " + cat);
            }
        }
    }

    if (!dataFound) {
        ui->lblResult->append("No categorized transactions found.");
    }
}
// MODULE 3: CUSTOMER QUEUE MANAGEMENT
// =====================================================

void MainWindow::on_comboM3Part_currentIndexChanged(int) {
    QString selection = ui->comboM3Part->currentText();
    ui->m3InputBar->clear();
    ui->m3Output->clear();

    if (selection == "Add Customer") {
        ui->m3InputBar->show();
        // Provides the user with the specific data format
        ui->m3InputBar->setPlaceholderText("ID, Name, Row, Priority(1/0)");
    } else {
        ui->m3InputBar->hide(); // Hide bar for 'Display Queue'
    }
}

void MainWindow::on_btnM3Enter_clicked() {
    QString selection = ui->comboM3Part->currentText();
    QString input = ui->m3InputBar->text().trimmed();

    if (selection == "Add Customer") {
        QStringList parts = input.split(",");
        if (parts.size() == 4) {
            Customer c;
            c.id = parts[0].trimmed().toInt();
            c.name = parts[1].trimmed().toStdString();
            c.rowNumber = parts[2].trimmed().toInt();
            c.isPriority = (parts[3].trimmed() == "1"); // 1 for Priority, 0 for Normal

            customerQueue.push_back(c);
            ui->m3Output->append("Customer Added: " + QString::fromStdString(c.name));
        } else {
            ui->m3Output->append("<span style='color:orange;'>Error: Use format ID,Name,Row,Priority</span>");
        }
    }
    else if (selection == "Display Queue") {
        ui->m3Output->clear();
        ui->m3Output->append("<b>--- Current Sorted Queue ---</b>");

        // SORTING LOGIC: Priority first, then Row Number
        std::sort(customerQueue.begin(), customerQueue.end(), [](const Customer& a, const Customer& b) {
            // First: Move Priority-1 (true) to the front
            if (a.isPriority != b.isPriority)
                return a.isPriority > b.isPriority;

            // Second: Sort by ascending row number
            return a.rowNumber < b.rowNumber;
        });

        if (customerQueue.empty()) {
            ui->m3Output->append("No customers in the queue.");
        } else {
            for (const auto& c : customerQueue) {
                QString status = c.isPriority ? "[PRIORITY]" : "[NORMAL]";
                ui->m3Output->append(QString("%1 Row: %2 | ID: %3 | Name: %4")
                                         .arg(status)
                                         .arg(c.rowNumber)
                                         .arg(c.id)
                                         .arg(QString::fromStdString(c.name)));
            }
        }
    }
    ui->m3InputBar->clear();
}
// =====================================================
// HELPERS
// =====================================================

Account* MainWindow::findAccount(int accNo) {
    for (auto &acc : accountsList) {
        if (acc.accountNumber == accNo) return &acc;
    }
    return nullptr;
}

void MainWindow::toggleMenu() {
    QPropertyAnimation *a = new QPropertyAnimation(ui->sideMenu, "minimumWidth");
    a->setDuration(300);
    a->setStartValue(ui->sideMenu->width());
    a->setEndValue(0); // Animated sliding sidebar
    a->start(QAbstractAnimation::DeleteWhenStopped);
}
