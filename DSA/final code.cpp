#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const int MAX_ACCOUNTS = 100;

// Basic account
struct BasicAccount {
  int accountNumber;
  string name;
  float balance;
};

// Transaction
struct Transaction {
  int id;      // also used as time order
  string type; // "DEPOSIT", "WITHDRAW"
  float amount;
  string timeStamp;   // not used for logic
  float balanceAfter; // only used in history
  Transaction *next;  // for linked list; nullptr when unused

  bool operator<(const Transaction &other) const {
    return amount < other.amount;
  }
  bool operator==(const Transaction &other) const {
    return id == other.id && amount == other.amount;
  }
};

// =====================================================
// MODULE 1 – TRANSACTION & ACCOUNT MANAGEMENT
// =====================================================

// ---------- PART 1: SIMPLE ACCOUNTS USING ARRAY ----------

BasicAccount p1Accounts[MAX_ACCOUNTS];
int p1Count = 0;

void p1_createAccount() {
  cout << "\n=== [M1-P1] Create Account ===\n";
  if (p1Count >= MAX_ACCOUNTS) {
    cout << "Array full.\n";
    return;
  }
  BasicAccount acc;
  cout << "Enter account number: ";
  cin >> acc.accountNumber;
  cout << "Enter name (single word): ";
  cin >> acc.name;
  cout << "Enter initial balance: ";
  cin >> acc.balance;
  p1Accounts[p1Count++] = acc;
  cout << "Account created.\n";
}

void p1_displayAll() {
  cout << "\n=== [M1-P1] Display All Accounts ===\n";
  if (p1Count == 0) {
    cout << "No accounts.\n";
    return;
  }
  for (int i = 0; i < p1Count; i++) {
    cout << "Account " << i + 1 << ":\n";
    cout << "  Number : " << p1Accounts[i].accountNumber << "\n";
    cout << "  Name   : " << p1Accounts[i].name << "\n";
    cout << "  Balance: " << p1Accounts[i].balance << "\n\n";
  }
}

void p1_searchAccount() {
  cout << "\n=== [M1-P1] Search Account ===\n";
  int accNo;
  cout << "Enter account number: ";
  cin >> accNo;
  bool found = false;
  for (int i = 0; i < p1Count; i++) {
    if (p1Accounts[i].accountNumber == accNo) {
      cout << "\n--- Account Found ---\n";
      cout << "Number : " << p1Accounts[i].accountNumber << "\n";
      cout << "Name   : " << p1Accounts[i].name << "\n";
      cout << "Balance: " << p1Accounts[i].balance << "\n";
      found = true;
      break;
    }
  }
  if (!found)
    cout << "Account not found.\n";
}

// ---------- PART 2: LINKED LIST TRANSACTION HISTORY ----------

struct AccountWithHistory {
  int accountNumber;
  string name;
  float balance;
  Transaction *historyHead;

  AccountWithHistory() {
    accountNumber = 0;
    name = "";
    balance = 0.0f;
    historyHead = nullptr;
  }
};

AccountWithHistory p2Accounts[MAX_ACCOUNTS];
int p2Count = 0;

int p2_findIndex(int accNo) {
  for (int i = 0; i < p2Count; i++)
    if (p2Accounts[i].accountNumber == accNo)
      return i;
  return -1;
}

// global store of ALL transactions done in Module 1
vector<Transaction> allTransactions;
int globalTxId = 1;

void p2_createAccount() {
  cout << "\n=== [M1-P2] Create Account with History ===\n";
  if (p2Count >= MAX_ACCOUNTS) {
    cout << "Array full.\n";
    return;
  }
  AccountWithHistory acc;
  cout << "Enter account number: ";
  cin >> acc.accountNumber;
  cout << "Enter name (single word): ";
  cin >> acc.name;
  cout << "Enter initial balance: ";
  cin >> acc.balance;
  p2Accounts[p2Count++] = acc;
  cout << "Account created.\n";
}

void p2_addTransaction(AccountWithHistory &acc, const string &type,
                       float amount) {
  Transaction *node = new Transaction;
  node->id = globalTxId++;
  node->type = type;
  node->amount = amount;
  node->balanceAfter = acc.balance;
  node->timeStamp = "";
  node->next = nullptr;

  // add to linked list
  if (acc.historyHead == nullptr)
    acc.historyHead = node;
  else {
    Transaction *t = acc.historyHead;
    while (t->next)
      t = t->next;
    t->next = node;
  }

  allTransactions.push_back(*node);
}

void p2_deposit() {
  cout << "\n=== [M1-P2] Deposit ===\n";
  int accNo;
  float amount;
  cout << "Enter account number: ";
  cin >> accNo;
  int idx = p2_findIndex(accNo);
  if (idx == -1) {
    cout << "Account not found.\n";
    return;
  }

  cout << "Enter amount: ";
  cin >> amount;
  p2Accounts[idx].balance += amount;
  p2_addTransaction(p2Accounts[idx], "DEPOSIT", amount);
  cout << "New balance: " << p2Accounts[idx].balance << "\n";
}

void p2_withdraw() {
  cout << "\n=== [M1-P2] Withdraw ===\n";
  int accNo;
  float amount;
  cout << "Enter account number: ";
  cin >> accNo;
  int idx = p2_findIndex(accNo);
  if (idx == -1) {
    cout << "Account not found.\n";
    return;
  }

  cout << "Enter amount: ";
  cin >> amount;
  if (amount > p2Accounts[idx].balance) {
    cout << "Insufficient balance.\n";
    return;
  }
  p2Accounts[idx].balance -= amount;
  p2_addTransaction(p2Accounts[idx], "WITHDRAW", amount);
  cout << "New balance: " << p2Accounts[idx].balance << "\n";
}

void p2_showHistory() {
  cout << "\n=== [M1-P2] Show History ===\n";
  int accNo;
  cout << "Enter account number: ";
  cin >> accNo;
  int idx = p2_findIndex(accNo);
  if (idx == -1) {
    cout << "Account not found.\n";
    return;
  }

  Transaction *t = p2Accounts[idx].historyHead;
  if (!t) {
    cout << "No transactions.\n";
    return;
  }

  cout << "\n--- History for account " << p2Accounts[idx].accountNumber
       << " ---\n";
  while (t) {
    cout << "ID: " << t->id << " | Type: " << t->type
         << " | Amount: " << t->amount << " | BalanceAfter: " << t->balanceAfter
         << "\n";
    t = t->next;
  }
}

void p2_displayAll() {
  cout << "\n=== [M1-P2] Display All Accounts ===\n";
  if (p2Count == 0) {
    cout << "No accounts.\n";
    return;
  }
  for (int i = 0; i < p2Count; i++) {
    cout << "Account " << i + 1 << ":\n";
    cout << "  Number : " << p2Accounts[i].accountNumber << "\n";
    cout << "  Name   : " << p2Accounts[i].name << "\n";
    cout << "  Balance: " << p2Accounts[i].balance << "\n\n";
  }
}

// ---------- PART 3: UNDO / REDO WITH STACKS ----------

struct TxAction {
  string type;
  float amount;
  float oldBalance;
  float newBalance;
};

float p3Balance = 0.0f;
stack<TxAction> undoStack;
stack<TxAction> redoStack;

void p3_apply(const string &type, float amount) {
  TxAction a;
  a.type = type;
  a.amount = amount;
  a.oldBalance = p3Balance;

  if (type == "DEPOSIT") {
    p3Balance += amount;
  } else if (type == "WITHDRAW") {
    if (amount > p3Balance) {
      cout << "Insufficient balance.\n";
      return;
    }
    p3Balance -= amount;
  } else {
    cout << "Unknown type.\n";
    return;
  }

  a.newBalance = p3Balance;
  undoStack.push(a);
  while (!redoStack.empty())
    redoStack.pop();

  cout << "Applied. Balance: " << p3Balance << "\n";
}

void p3_undo() {
  if (undoStack.empty()) {
    cout << "Nothing to undo.\n";
    return;
  }
  TxAction last = undoStack.top();
  undoStack.pop();
  p3Balance = last.oldBalance;
  redoStack.push(last);
  cout << "Undo done. Balance: " << p3Balance << "\n";
}

void p3_redo() {
  if (redoStack.empty()) {
    cout << "Nothing to redo.\n";
    return;
  }
  TxAction last = redoStack.top();
  redoStack.pop();
  p3Balance = last.newBalance;
  undoStack.push(last);
  cout << "Redo done. Balance: " << p3Balance << "\n";
}

// ---------- PART 4: SEARCHING + SORTING DEMOS ----------

int linearSearchAccount(BasicAccount arr[], int n, int accNo) {
  for (int i = 0; i < n; i++)
    if (arr[i].accountNumber == accNo)
      return i;
  return -1;
}

int binarySearchAccount(BasicAccount arr[], int n, int accNo) {
  int low = 0, high = n - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid].accountNumber == accNo)
      return mid;
    else if (arr[mid].accountNumber < accNo)
      low = mid + 1;
    else
      high = mid - 1;
  }
  return -1;
}

void sortAccountsByNumber(BasicAccount arr[], int n) {
  sort(arr, arr + n, [](const BasicAccount &a, const BasicAccount &b) {
    return a.accountNumber < b.accountNumber;
  });
}

void sortTransactionsByAmount(Transaction tx[], int n) {
  sort(tx, tx + n, [](const Transaction &a, const Transaction &b) {
    return a.amount < b.amount;
  });
}

void sortTransactionsById(Transaction tx[], int n) {
  sort(tx, tx + n,
       [](const Transaction &a, const Transaction &b) { return a.id < b.id; });
}

// ---------- PART 5: OPERATOR OVERLOADING DEMO ----------

ostream &operator<<(ostream &os, const Transaction &t) {
  os << "[ID:" << t.id << ", Type:" << t.type << ", Amount:" << t.amount << "]";
  return os;
}

// ---------- MODULE 1 MENU ----------

void runModule1() {
  int choice;
  do {
    cout << "\n================= MODULE 1: TRANSACTION & ACCOUNT MANAGEMENT "
            "=================\n";
    cout << "1. Part 1 - Basic accounts (array)\n";
    cout << "2. Part 2 - Accounts with transaction history\n";
    cout << "3. Part 3 - Undo/Redo (stacks)\n";
    cout << "4. Part 4 - Searching & sorting demo\n";
    cout << "5. Part 5 - Operator overloading demo\n";
    cout << "6. Back to main menu\n";
    cout << "Enter your choice for Module 1: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      int c;
      do {
        cout << "\n--- M1-P1 Menu ---\n";
        cout << "1. Create account\n";
        cout << "2. Display all\n";
        cout << "3. Search account\n";
        cout << "4. Back\n";
        cout << "Choice: ";
        cin >> c;
        if (c == 1)
          p1_createAccount();
        else if (c == 2)
          p1_displayAll();
        else if (c == 3)
          p1_searchAccount();
        else if (c != 4)
          cout << "Invalid choice.\n";
      } while (c != 4);
      break;
    }
    case 2: {
      int c;
      do {
        cout << "\n--- M1-P2 Menu (transaction history) ---\n";
        cout << "1. Create account with history\n";
        cout << "2. Display accounts\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Show history\n";
        cout << "6. Back\n";
        cout << "Choice: ";
        cin >> c;
        if (c == 1)
          p2_createAccount();
        else if (c == 2)
          p2_displayAll();
        else if (c == 3)
          p2_deposit();
        else if (c == 4)
          p2_withdraw();
        else if (c == 5)
          p2_showHistory();
        else if (c != 6)
          cout << "Invalid choice.\n";
      } while (c != 6);
      break;
    }
    case 3: {
      int c;
      do {
        cout << "\n--- M1-P3 Menu (undo/redo) ---\n";
        cout << "Current balance: " << p3Balance << "\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Back\n";
        cout << "Choice: ";
        cin >> c;
        float amount;
        if (c == 1) {
          cout << "Amount: ";
          cin >> amount;
          p3_apply("DEPOSIT", amount);
        } else if (c == 2) {
          cout << "Amount: ";
          cin >> amount;
          p3_apply("WITHDRAW", amount);
        } else if (c == 3)
          p3_undo();
        else if (c == 4)
          p3_redo();
        else if (c != 5)
          cout << "Invalid choice.\n";
      } while (c != 5);
      break;
    }
    case 4: {
      cout << "\n--- M1-P4 Searching & Sorting Demo ---\n";
      BasicAccount accs[3] = {
          {102, "Ali", 5000}, {301, "Sara", 9000}, {210, "Usman", 7000}};
      int nAcc = 3;
      cout << "Linear search for account 210:\n";
      int key = 210;
      int idxL = linearSearchAccount(accs, nAcc, key);
      if (idxL != -1)
        cout << "Found at index " << idxL << " (unsorted)\n";
      else
        cout << "Not found.\n";

      cout << "\nSorting and binary searching:\n";
      sortAccountsByNumber(accs, nAcc);
      int idxB = binarySearchAccount(accs, nAcc, key);
      if (idxB != -1)
        cout << "Found at index " << idxB << " (after sort)\n";
      else
        cout << "Not found.\n";

      Transaction tx[4] = {{3, "DEPOSIT", 2000, "14:00", 0, nullptr},
                           {1, "DEPOSIT", 500, "09:00", 0, nullptr},
                           {4, "WITHDRAW", 800, "16:00", 0, nullptr},
                           {2, "WITHDRAW", 300, "11:00", 0, nullptr}};
      int nTx = 4;
      cout << "\nTransactions sorted by amount:\n";
      sortTransactionsByAmount(tx, nTx);
      for (int i = 0; i < nTx; i++) {
        cout << "ID:" << tx[i].id << "  Type:" << tx[i].type
             << "  Amount:" << tx[i].amount << "\n";
      }
      break;
    }
    case 5: {
      cout << "\n--- M1-P5 Operator Overloading Demo ---\n";
      vector<Transaction> tx = {{3, "DEPOSIT", 2000, "14:00", 0, nullptr},
                                {1, "DEPOSIT", 500, "09:00", 0, nullptr},
                                {4, "WITHDRAW", 800, "16:00", 0, nullptr},
                                {2, "WITHDRAW", 300, "11:00", 0, nullptr}};
      cout << "Original list:\n";
      for (const auto &t : tx)
        cout << t << "\n";

      sort(tx.begin(), tx.end());
      cout << "\nSorted by amount:\n";
      for (const auto &t : tx)
        cout << t << "\n";

      cout << "\nCompare tx[0] and tx[1]:\n";
      if (tx[0] < tx[1])
        cout << tx[0] << " has smaller amount than " << tx[1] << "\n";
      else
        cout << tx[0] << " has greater/equal amount than " << tx[1] << "\n";
      break;
    }
    case 6:
      cout << "Returning from Module 1...\n";
      break;
    default:
      cout << "Invalid choice.\n";
    }
  } while (choice != 6);
}

// MODULE 2 – BUDGET CLASSIFICATION & ANALYSIS
// (USER-DRIVEN CLASSIFICATION OF MODULE 1 TRANSACTIONS)

struct Category {
  string name;
  bool operator==(const Category &other) const { return name == other.name; }
};

void runModule2() {
  cout << "\n================= MODULE 2: BUDGET CLASSIFICATION & ANALYSIS "
          "=================\n";

  if (allTransactions.empty()) {
    cout << "No transactions stored from Module 1 yet.\n";
    cout
        << "Go to Module 1 -> Part 2 and perform deposits/withdrawals first.\n";
    return;
  }

  Category categories[5] = {
      {"Food"}, {"Utilities"}, {"Education"}, {"Government"}, {"Others"}};

  vector<int> txCategory(allTransactions.size(), 4); // default Others

  cout << "\nWe will now classify the transactions you already entered in "
          "Module 1.\n";
  cout << "Categories:\n";
  cout << " 0 - Food\n 1 - Utilities\n 2 - Education\n 3 - Government\n 4 - "
          "Others\n";

  for (size_t i = 0; i < allTransactions.size(); ++i) {
    const Transaction &t = allTransactions[i];
    cout << "\nTransaction ID " << t.id << " | Type: " << t.type
         << " | Amount: " << t.amount << "\n";
    int choice;
    do {
      cout << "Enter category number (0-4) for this transaction: ";
      cin >> choice;
      if (choice < 0 || choice > 4)
        cout << "Invalid category. Please enter between 0 and 4.\n";
    } while (choice < 0 || choice > 4);
    txCategory[i] = choice;

    if (categories[choice] == categories[0]) {
      cout << "   (Matched using operator== : Food Category)\n";
    }
  }

  cout << "\n===== FINAL CLASSIFIED TRANSACTIONS =====\n";
  for (size_t i = 0; i < allTransactions.size(); ++i) {
    const Transaction &t = allTransactions[i];
    cout << "ID " << t.id << " | Type: " << t.type << " | Amount: " << t.amount
         << " --> " << categories[txCategory[i]].name << "\n";
  }

  cout << "\nReturning from Module 2...\n";
}

// MODULE 3 – CUSTOMER QUEUE & EVENT SIMULATION (USER INPUT)

struct Customer {
  int id;
  string name;
};

struct VIPCustomer {
  int id;
  string name;
  int priority; // 1 = highest, bigger = lower
};

struct CompareVIP {
  bool operator()(const VIPCustomer &a, const VIPCustomer &b) const {
    return a.priority > b.priority; // smaller number : higher priority
  }
};

const int MAX_EVENTS = 5;

struct CircularEventQueue {
  int events[MAX_EVENTS];
  int front;
  int rear;
  int count;

  CircularEventQueue() {
    front = 0;
    rear = -1;
    count = 0;
  }

  bool isEmpty() { return count == 0; }
  bool isFull() { return count == MAX_EVENTS; }

  bool enqueue(int value) {
    if (isFull()) {
      cout << "Event queue is full, cannot add: " << value << endl;
      return false;
    }
    rear = (rear + 1) % MAX_EVENTS;
    events[rear] = value;
    count++;
    return true;
  }

  bool dequeue(int &outValue) {
    if (isEmpty()) {
      return false;
    }
    outValue = events[front];
    front = (front + 1) % MAX_EVENTS;
    count--;
    return true;
  }
};

struct ActivationRecord {
  int callNumber;
  int currentEvent;
};

const int MAX_CALLS = 20;
ActivationRecord callStack[MAX_CALLS];
int callTop = -1;

void pushActivation(int callNumber, int eventValue) {
  if (callTop + 1 < MAX_CALLS) {
    callTop++;
    callStack[callTop].callNumber = callNumber;
    callStack[callTop].currentEvent = eventValue;
  }
}

void popActivation() {
  if (callTop >= 0) {
    callTop--;
  }
}

void simulateEventsRecursively(CircularEventQueue &q, int level = 1) {
  int value;
  if (!q.dequeue(value)) {
    cout << "No more events to process (recursion stops).\n";
    return;
  }

  pushActivation(level, value);
  cout << "Enter call level " << level << " (processing event value = " << value
       << ")\n";

  cout << "Processing event value: " << value << endl;

  simulateEventsRecursively(q, level + 1);

  cout << "Exit  call level " << level << " (event value was = " << value
       << ")\n";
  popActivation();
}

void runModule3() {
  cout << "\n================= MODULE 3: CUSTOMER QUEUE & EVENT SIMULATION "
          "=================\n";

  // ---------- Input normal customers ----------
  queue<Customer> normalQueue;
  int nNormal;
  cout << "How many normal customers? ";
  cin >> nNormal;
  for (int i = 0; i < nNormal; ++i) {
    Customer c;
    cout << "Enter normal customer " << i + 1 << " ID: ";
    cin >> c.id;
    cout << "Enter name (single word): ";
    cin >> c.name;
    normalQueue.push(c);
  }

  // ---------- Input VIP customers ----------
  priority_queue<VIPCustomer, vector<VIPCustomer>, CompareVIP> vipQueue;
  int nVip;
  cout << "How many VIP customers? ";
  cin >> nVip;
  for (int i = 0; i < nVip; ++i) {
    VIPCustomer v;
    cout << "Enter VIP customer " << i + 1 << " ID: ";
    cin >> v.id;
    cout << "Enter name (single word): ";
    cin >> v.name;
    cout << "Enter priority (1 = highest, bigger = lower): ";
    cin >> v.priority;
    vipQueue.push(v);
  }

  // ---------- Input events for circular queue ----------
  CircularEventQueue eventQueue;
  int nEvents;
  cout << "How many events (max " << MAX_EVENTS << ")? ";
  cin >> nEvents;
  if (nEvents > MAX_EVENTS)
    nEvents = MAX_EVENTS;
  for (int i = 0; i < nEvents; ++i) {
    int v;
    cout << "Enter event value " << i + 1 << ": ";
    cin >> v;
    eventQueue.enqueue(v);
  }

  cout << "\nRecursive event simulation with activation records:\n";
  simulateEventsRecursively(eventQueue);

  cout << "\nServing VIP customers (by priority):\n";
  while (!vipQueue.empty()) {
    VIPCustomer currentVIP = vipQueue.top();
    vipQueue.pop();
    cout << "Serving VIP ID: " << currentVIP.id << ", Name: " << currentVIP.name
         << ", Priority: " << currentVIP.priority << endl;
  }

  cout << "\nServing normal customers (FIFO):\n";
  while (!normalQueue.empty()) {
    Customer current = normalQueue.front();
    normalQueue.pop();
    cout << "Serving customer ID: " << current.id << ", Name: " << current.name
         << endl;
  }

  cout << "\nReturning from Module 3...\n";
}

// MASTER MAIN MENU

int main() {
  int choice;
  do {
    cout << "\n================= INTELLIGENT BANKING MANAGEMENT SYSTEM "
            "=================\n";
    cout << "1. Module 1 - Transaction & Account Management\n";
    cout << "2. Module 2 - Budget Classification & Analysis (classify stored "
            "transactions)\n";
    cout << "3. Module 3 - Customer Queue & Event Simulation\n";
    cout << "4. Exit\n";
    cout << "Choose module: ";
    cin >> choice;

    switch (choice) {
    case 1:
      runModule1();
      break;
    case 2:
      runModule2();
      break;
    case 3:
      runModule3();
      break;
    case 4:
      cout << "Exiting program...\n";
      break;
    default:
      cout << "Invalid choice.\n";
    }
  } while (choice != 4);

  return 0;
}