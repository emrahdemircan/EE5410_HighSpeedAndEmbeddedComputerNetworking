# -------------------------------------------------
# Project created by QtCreator 2011-01-05T09:06:12
# -------------------------------------------------
QT += core \
    widgets
TARGET = user_5410
TEMPLATE = app
INCLUDEPATH += ../kernel/
SOURCES += main.cpp \
    mainwindow.cpp
HEADERS += mainwindow.h \
    ../kernel/stats.h \
    ../kernel/netlink.h \
    ../kernel/scheduler.h \
    ../kernel/ethernet.h
FORMS += mainwindow.ui
