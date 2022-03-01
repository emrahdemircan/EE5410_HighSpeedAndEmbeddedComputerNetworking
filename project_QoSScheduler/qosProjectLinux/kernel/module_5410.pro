HEADERS += \
    stats.h \
    skbInfo.h \
    outputQueueModule.h \
    netlink.h \
    ethernet.h \
    scheduler.h
SOURCES += \
    stats.c \
    outputQueueModule.c \
    netlink.c \
    ethernetSender.c \
    ethernetReceiver.c \
    ethernetScheduler.c
OTHER_FILES += \
    outputQueueModule.x \
    Makefile
