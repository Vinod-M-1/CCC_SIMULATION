Mini_Banking_System

This project is a simulation of a mini banking system created for the CCC (Computer Concepts & C++) assignment.
It demonstrates how stack and vector data structures can be applied in a banking environment.

The repository contains two parts:

🌐 A web-based simulation using HTML, CSS, and JavaScript

⚙️ A C++ implementation (bank.cpp) showing the underlying data structure logic

The C++ file is included for academic documentation and does not affect website deployment on platforms like Vercel.

📘 Concepts Implemented
1️⃣ Stack — Transaction History (LIFO)

Transactions follow a Last-In First-Out order.
Each new transaction is pushed to the top of the stack.

In C++ → stack<T>

In JavaScript → unshift() to simulate LIFO

2️⃣ Vector — Account Storage

Accounts are stored in a vector-like structure:

In C++ → vector<Account>

In JavaScript → array stored in localStorage

Account operations supported:

➕ Creation

🔍 Search

✏️ Update

🧾 Transaction recording

3️⃣ Banking Operations Simulated

The system implements:

🧑‍💼 Create account

🔐 Login

💰 Deposit

💸 Withdraw

🔁 Transfer

📦 Stack-based transaction history

📊 Admin-level account overview

These operations are implemented in both the C++ version and the web simulation.

📂 Project Structure
/
├── index.html
├── login.html
├── register.html
├── user.html
├── admin.html
│
├── css/
├── js/
│
├── bank.cpp
└── README.md

📄 About the C++ File

bank.cpp includes:

Vector-based account management

Stack-based transaction history

Menu-driven banking simulation

This file is part of the assignment’s documentation.
It will not affect deployment since static hosting platforms ignore .cpp files.

🎯 Purpose

The project demonstrates how core data structures — stack and vector — can be used to model real-world systems such as banking, both through:

A C++ implementation, and

A web-based simulation

This highlights how theoretical concepts translate into practical applications.
