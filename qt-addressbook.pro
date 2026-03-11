QT += core gui widgets sql

CONFIG += c++17

TARGET = qt-addressbook
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    test_contacts.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
