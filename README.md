# Qt Address Book Application

## Overview

This project is a **simple Address Book Management Application** developed using **Qt and C++**.
The application allows users to store and manage contacts with basic CRUD operations.

Each contact includes the following fields:

* Name
* Mobile Number
* Email Address
* Birthday

The application provides a simple graphical interface for adding, editing, deleting, and viewing contacts.

---

## Features

* View stored contacts in a table
* Add new contacts
* Edit existing contacts
* Delete contacts
* Field validation (email format check)
* SQLite database for persistent storage
* Unit test file included
* Clean and modular Qt project structure

---

## Technologies Used

* **C++**
* **Qt Widgets**
* **Qt SQL (SQLite)**
* **Qt Test (Unit Testing)**
* **qmake build system**

---

## Project Structure

```
qt-addressbook
│
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── qt-addressbook.pro
├── test_contacts.cpp
└── README.md
```

---

## Build Instructions (Debian / Ubuntu)

Install Qt dependencies:

```
sudo apt update
sudo apt install qtbase5-dev qt5-qmake build-essential
```

Build the project:

```
qmake qt-addressbook.pro
make
```

Run the application:

```
./qt-addressbook
```

---

## Application Usage

1. Launch the application.
2. The stored contacts will automatically appear in the table.
3. Use the buttons below the table:

* **Add** → Add a new contact
* **Edit** → Modify an existing contact
* **Delete** → Remove a contact

All contacts are stored in an **SQLite database**, so they remain saved even after restarting the application.

---

## Unit Tests

Basic unit tests are included in:

```
test_contacts.cpp
```

These tests validate:

* Database connection
* Contact insertion
* Email validation

---

## Author

Aditya Wagh

---

## License

This project is for **educational purposes**.
