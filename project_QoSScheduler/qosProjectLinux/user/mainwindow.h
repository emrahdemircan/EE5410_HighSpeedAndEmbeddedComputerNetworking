#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QString>
#include <QTimer>
/********************************************************************************/
/* INCLUDES */
/********************************************************************************/
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <linux/netlink.h>

#include "netlink.h"
#include "ethernet.h"
#include "scheduler.h"
#include "stats.h"


/********************************************************************************/
/* DEFINES */
/********************************************************************************/
#define MESSAGEQ_KEY_skNlThread	0xAB58
#define MESSAGE_TEXT_SIZE	MAX_PAYLOAD_LEN

typedef struct
{
        long mtype;
        char mtext[MESSAGE_TEXT_SIZE];
} T_MSGBUF;

#define MESSAGE_TYPE_DUMMY	1
#define MESSAGE_TYPE_QUIT	2
#define MESSAGE_TYPE_NL		3

typedef struct
{
    int threadNo;
    void* ptr;
}T_THREAD_INPUT;

class SkNlThread;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    protected:
        void closeEvent(QCloseEvent *event);
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        Ui::MainWindow *ui;
        T_STATS allStats;
        void printStats(void);
    private:
        int usrPid;
        QTimer *statsTimer;
        SkNlThread *skNl;
    private slots:
        void on_egressLinkRateComboBox_currentIndexChanged(int index);
        void on_queueLengthSelectComboBox_currentIndexChanged(int index);
        void on_backlogTimeSelectComboBox_currentIndexChanged(int index);
        void on_schSelectComboBox_currentIndexChanged(int index);
        void on_sysStopButton_clicked();
        void on_sysStartButton_clicked();
    signals:
        void log(const QString &qStr);
    public slots:
        void showLog(const QString &qStr);
        void reqStats(void);
        void showStats(void);
        void setKernelModuleState(unsigned short isStarted);
};

class SkNlThread : public QThread
{
    Q_OBJECT
    private:
        MainWindow *mainW;
        int skNlMsgQId;
        /*stats*/
        int numNlMsgSent;
        int numNlMsgRcvd;
    public:
        SkNlThread(MainWindow *wPtr);
        int nlModuleHandler(T_MSG_NL_SHORT *msg, int msgLen, int msgSeq, int pid);
        int usrPid;
        bool stopThread;        
        int initNetlinkSocket(void);
        void nlSendMsg(unsigned short moduleId, unsigned int srcPid, unsigned int dstPid, void* data, unsigned int dataLen);
        void sendMsgShort(unsigned short msgType);
        void sendMsgLong(unsigned short msgType, void* data, unsigned int dataLen);
        int closeNetlinkSocket(void);
        void run();
    signals:
        void log(const QString &qStr);
        void showStats(void);
        void setKernelModuleState(unsigned short isStarted);
};

#endif // MAINWINDOW_H
