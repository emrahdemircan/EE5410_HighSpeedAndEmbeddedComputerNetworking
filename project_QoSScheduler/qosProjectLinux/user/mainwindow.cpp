#include "mainwindow.h"
#include "ui_mainwindow.h"

/********************************************************************************/
/* GLOBALS */
/********************************************************************************/
/*netlink socket*/
int sockFd;
struct sockaddr_nl srcAddr;
struct sockaddr_nl dstAddr;
/*send message*/
unsigned char sendBuffer[NLMSG_SPACE(MAX_PAYLOAD_LEN)];
struct iovec sendIov;
struct msghdr sendMsg;
/*receive message*/
unsigned char recvBuffer[NLMSG_SPACE(MAX_PAYLOAD_LEN)];
struct iovec recvIov;
struct msghdr recvMsg;
char logBuf[500];
T_MSG_NL_SHORT testMsgShort;
T_MSG_NL_LONG testMsgLong;

/********************************************************************************/
/* FUNCTIONS */
/********************************************************************************/
SkNlThread::SkNlThread(MainWindow* wPtr):QThread()
{
    usrPid = getpid();
    mainW = wPtr;
    sprintf(logBuf,"%s: %d\n", __FUNCTION__, this->usrPid);
    emit log(logBuf);
    stopThread = false;
    skNlMsgQId = -1;
    numNlMsgSent = 0;
    numNlMsgRcvd = 0;
}/*SkNlThread*/

int SkNlThread::initNetlinkSocket(void)
{
        emit log("initNetlinkSocket:\n");
        /*initialize stats*/
        numNlMsgSent = 0;
        numNlMsgRcvd = 0;
        /*initialize receive buffer*/
        recvIov.iov_base = (void*)recvBuffer;
        recvIov.iov_len = NLMSG_SPACE(MAX_PAYLOAD_LEN);
        recvMsg.msg_iov = &recvIov;
        recvMsg.msg_iovlen = 1;
        /*initialize send buffer*/
        sendIov.iov_base = (void*)sendBuffer;
        sendIov.iov_len = NLMSG_SPACE(MAX_PAYLOAD_LEN);
        sendMsg.msg_iov = &sendIov;
        sendMsg.msg_iovlen = 1;

        emit log("initNetlinkSocket: Creating netlink socket.\n");
        sockFd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
        if(sockFd<0)
        {
                emit log("initNetlinkSocket: Creating netlink socket failed!\n");
                return -1;
        }

        emit log("initNetlinkSocket: Binding netlink socket.\n");
        memset(&srcAddr, 0, sizeof(struct sockaddr_nl));
        srcAddr.nl_family = AF_NETLINK;
        srcAddr.nl_pid = getpid();
        if( bind(sockFd, (struct sockaddr*)&srcAddr, sizeof(struct sockaddr_nl)) == -1)
        {
            emit log("initNetlinkSocket: Binding netlink socket failed!\n");
        }
        emit log("initNetlinkSocket: Netlink socket created.\n");
        return 1;
}/*initNetlinkSocket*/

void SkNlThread::nlSendMsg(unsigned short moduleId, unsigned int srcPid, unsigned int dstPid, void* data, unsigned int dataLen)
{
        struct nlmsghdr *nlh;

        //emit log("nlSendMsg:\n");

        if( ( (data == NULL) && (dataLen>0) ) || (dataLen>T_MSG_NL_LONG_SIZE))
        {
                sprintf(logBuf,"%s: data/len error!\n", __FUNCTION__);
                emit log(logBuf);
                return;
        }
        numNlMsgSent++;

        memset(&dstAddr, 0, sizeof(struct sockaddr_nl));
        dstAddr.nl_family = AF_NETLINK;
        dstAddr.nl_pid = dstPid;
        dstAddr.nl_groups = 0; /*unicast*/

        sendMsg.msg_name = (void*)&dstAddr;
        sendMsg.msg_namelen = sizeof(struct sockaddr_nl);

        nlh = (struct nlmsghdr*)sendIov.iov_base;
        memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD_LEN));
        memcpy(NLMSG_DATA(nlh), data, dataLen);
        sendIov.iov_len = NLMSG_SPACE(dataLen);
        nlh->nlmsg_pid = srcPid;
        nlh->nlmsg_type = moduleId;
        nlh->nlmsg_len = dataLen;
        nlh->nlmsg_seq = numNlMsgSent;
        nlh->nlmsg_flags = 0;

        /*sprintf(logBuf,"%s: TX(%d) moduleId (%d) srcPid(%d) dstPid(%d)\n", __FUNCTION__, numNlMsgSent, moduleId, srcPid, dstPid);
        emit log(logBuf);*/

        if( sendmsg(sockFd, &sendMsg, 0) == -1 )
        {
            sprintf(logBuf,"%s: sendmsg failed! errno(%d)\n", __FUNCTION__, errno);
            emit log(logBuf);
        }
}/*nlSendMsg*/

void SkNlThread::sendMsgShort(unsigned short msgType)
{
    testMsgShort.msgType = msgType;
    nlSendMsg(NL_NLMODULE, usrPid, 0/*kernel pid*/,&testMsgShort, sizeof(T_MSG_NL_SHORT));
}/*testSendMsg*/

void SkNlThread::sendMsgLong(unsigned short msgType,void* data, unsigned int dataLen)
{
    testMsgLong.msgType = msgType;
    memcpy(testMsgLong.payload,data,(dataLen<T_MSG_NL_LONG_SIZE ? dataLen:T_MSG_NL_LONG_SIZE));
    nlSendMsg(NL_NLMODULE, usrPid, 0/*kernel pid*/,&testMsgLong, sizeof(T_MSG_NL_LONG));
}/*testSendMsg*/

int SkNlThread::closeNetlinkSocket(void)
{
        /*close socket and exit*/
        emit log("closeNetlinkSocket:\n");
        close(sockFd);
        return 1;
}/*closeNetlinkSocket*/

void SkNlThread::run()
{
    int ret;
    int recvLen;
    struct nlmsghdr *nlh;
    int pid;
    int nlMsgType;
    int nlMsgLen;
    int nlMsgSeq;

    /*connect this objects signals to the other objects slots...*/
    QObject::connect(this, SIGNAL(log(const QString &)), mainW, SLOT(showLog(const QString &)));
    QObject::connect(this, SIGNAL(showStats(void)), mainW, SLOT(showStats(void)));
    QObject::connect(this, SIGNAL(setKernelModuleState(unsigned short)), mainW, SLOT(setKernelModuleState(unsigned short)));

    emit log("SkNlThread: all signals connected\n");
    system("insmod ../kernel/module_5410.ko");
    /*start netlink socket*/
    ret = initNetlinkSocket();
    if(ret == -1)
    {
            goto PATH_QUIT;
    }

    /*send an echo request to myself*/
    testMsgShort.msgType = NL_MSGTYPE_ECHO_REQ;
    nlSendMsg(NL_NLMODULE, usrPid, usrPid,&testMsgShort,sizeof(T_MSG_NL_SHORT));

    emit log("SkNlThread: started.\n");

    /************************************************************************/
    /* enter the thread loop */
    /************************************************************************/
    while(stopThread!=true)
    {

            /*sprintf(logBuf,"%s:\n", __FUNCTION__);
            emit log(logBuf);*/
            /*receive a message from netlink socket...*/
            memset(recvBuffer,0,NLMSG_SPACE(MAX_PAYLOAD_LEN));
            /*soket zaten blocking*/
            recvLen = recvmsg(sockFd, &recvMsg, 0/* MSG_WAITALL*/);
            /*sprintf(logBuf,"%s: recvLen: %d\n", __FUNCTION__, recvLen);
            emit log(logBuf);*/
            if( (recvLen > 0) && (recvLen<=NLMSG_SPACE(MAX_PAYLOAD_LEN)))
            {
                    numNlMsgRcvd++;
                    nlh =(struct nlmsghdr*)recvMsg.msg_iov->iov_base;
                    pid = nlh->nlmsg_pid;
                    nlMsgType = nlh->nlmsg_type;
                    nlMsgLen = nlh->nlmsg_len;
                    nlMsgSeq = nlh->nlmsg_seq;
                    /*sprintf(logBuf,"%s: RX(%d): pid:%d msgType:%d msgLen:%d msgSeq:%d.\n", __FUNCTION__, numNlMsgRcvd, pid, nlMsgType, nlMsgLen,nlMsgSeq);
                    emit log(logBuf);*/
                    memcpy(recvBuffer,NLMSG_DATA(nlh), nlh->nlmsg_len);
                    switch(nlMsgType)
                    {
                            case NL_NLMODULE:
                                /*sprintf(logBuf,"%s: NL_NLMODULE\n", __FUNCTION__);
                                emit log(logBuf);*/
                                nlModuleHandler((T_MSG_NL_SHORT*)recvBuffer,nlMsgLen-NLMSG_HDRLEN,nlMsgSeq,pid);
                            break;
                            default:
				/*sprintf(logBuf,"%s: moduleId: default(0x%04x)!\n", __FUNCTION__,nlMsgType);
				emit log(logBuf);*/
                            break;
                    }
            }
            yieldCurrentThread();
    }
PATH_QUIT:
    emit log("skNlThread: PATH_QUIT\n");
    closeNetlinkSocket();

    system("rmmod module_5410.ko");

    if(skNlMsgQId > 0)
    {
            emit log("skNlThread: Removing skNlMsgQId.\n");
            ret = msgctl(skNlMsgQId, IPC_RMID, NULL);
            skNlMsgQId = -1;
    }
    emit log("skNlThread: stopped.\n");
    return;
}/*SkNlThread::run*/


int SkNlThread::nlModuleHandler(T_MSG_NL_SHORT *msg, int msgLen, int msgSeq, int pid)
{
    switch(msg->msgType)
    {
        case NL_MSGTYPE_ECHO_REQ:
            emit log("SkNlThread: Received NL_MSGTYPE_ECHO_REQ.\n");
            testMsgShort.msgType = NL_MSGTYPE_ECHO_REP;
            nlSendMsg(NL_NLMODULE, usrPid, pid,&testMsgShort,sizeof(T_MSG_NL_SHORT));
            testMsgShort.msgType = NL_MSGTYPE_ECHO_REQ;
            nlSendMsg(NL_NLMODULE, usrPid, 0,&testMsgShort,sizeof(T_MSG_NL_SHORT));
        break;
        case NL_MSGTYPE_ECHO_REP:
            emit log("SkNlThread: Received NL_MSGTYPE_ECHO_REP.\n");
        break;
        case NL_MSGTYPE_KILL:
            emit log("SkNlThread: Received NL_MSGTYPE_KILL");
            stopThread = true;
        break;
        case NL_MSGTYPE_STATS_REP:
                //emit log("SkNlThread: Received NL_MSGTYPE_STATS_REP.\n");
                memset(&(mainW->allStats), 0, sizeof(T_STATS));
                /*msg->payload msgLen-2 uzunlugunda*/
                if((msgLen-2) == sizeof(T_STATS))
                {
                        memcpy(&(mainW->allStats),((T_MSG_NL_LONG*)msg)->payload, sizeof(T_STATS));
                }
                else
                {
                        sprintf(logBuf,"%s: msgLen(%d) != sizeof(T_STATS = %d)\n",__FUNCTION__,msgLen,sizeof(T_STATS));
                        emit log(logBuf);
                }
                emit showStats();
        break;
        case NL_MSGTYPE_LOG:
                emit log((const char*)(((T_MSG_NL_LONG*)msg)->payload));
        break;
        case NL_MSGTYPE_MODULESTARTED:
            emit log("SkNlThread: Received NL_MSGTYPE_MODULESTARTED.\n");
            emit setKernelModuleState(1);
        break;
        case NL_MSGTYPE_MODULESTOPPED:
            emit log("SkNlThread: Received NL_MSGTYPE_MODULESTOPPED.\n");
            emit setKernelModuleState(0);
        break;
        case NL_MSGTYPE_ACK:
            emit log("SkNlThread: Received NL_MSGTYPE_ACK");
        break;
        default:
            sprintf(logBuf,"%s: msgType: default(0x%04x) msgLen:%d msgSeq:%d!\n", __FUNCTION__,msg->msgType,msgLen,msgSeq);
            emit log(logBuf);
        break;
    }
    return 1;
}/*nlModuleHandler*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    usrPid = getpid();

    /*connect log signal to showLog slot*/
    QObject::connect(this, SIGNAL(log(const QString &)), this, SLOT(showLog(const QString &)));

    /*disable the stop button*/
    ui->sysStopButton->setEnabled(false);

    /*reset all stats*/
    memset(&allStats,0,sizeof(T_STATS));

    /*create threads*/
    skNl = new SkNlThread(this);
    skNl->start();

    /*initialize stats request timer*/
    statsTimer = new QTimer();
    connect(statsTimer, SIGNAL(timeout()), this, SLOT(reqStats()));
    statsTimer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;    
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    /*stop and delete stats timer.*/
    statsTimer->stop();
    delete statsTimer;

    /*stopnd delete threads.*/
    testMsgShort.msgType = NL_MSGTYPE_KILL;
    skNl->nlSendMsg(NL_NLMODULE, skNl->usrPid, skNl->usrPid,&testMsgShort,sizeof(T_MSG_NL_SHORT));
    skNl->QThread::wait(1000);
    delete skNl;
    event = NULL;
}

/********************************/
/* printStats */
/********************************/
void MainWindow::printStats(void)
{
    int i;
    double avgMSecs;    
    //double avgNSecs;
    double totalMsecs;
    /*ethernetRx*/
    ui->statsTable->item(1,1)->setText( QString("%1").arg(allStats.ethernetRx.ethernetPacketIn));
    ui->statsTable->item(2,1)->setText( QString("%1").arg(allStats.ethernetRx.queued));
    ui->statsTable->item(3,1)->setText( QString("%1").arg(allStats.ethernetRx.notQueued));
    ui->statsTable->item(4,1)->setText( QString("%1").arg(allStats.ethernetRx.dequeued));
    ui->statsTable->item(5,1)->setText( QString("%1").arg(allStats.ethernetRx.processed));
    ui->statsTable->item(6,1)->setText( QString("%1").arg(allStats.ethernetRx.dataProcessed));
    ui->statsTable->item(7,1)->setText( QString("%1").arg(allStats.ethernetRx.ipcProcessed));

    /*ethernetSch*/
    ui->statsTable->item(1,3)->setText( QString("%1").arg(allStats.ethernetSch.ethernetPacketIn));
    for(i=0; i<NUM_OF_ETHERNET_PRIORITY_CLASSES; i++)
    {
        /*********/
        /*queue i*/
        /*********/
        ui->statsTable->item(i+3,3)->setText( QString("%1").arg(allStats.ethernetSch.queueStats[i].queued));
        ui->statsTable->item(i+3,4)->setText( QString("%1").arg(allStats.ethernetSch.queueStats[i].notQueued));
        ui->statsTable->item(i+3,5)->setText( QString("%1").arg(allStats.ethernetSch.queueStats[i].dequeued));
        ui->statsTable->item(i+3,6)->setText( QString("%1:%2")
                                            .arg(allStats.ethernetSch.queueStats[i].delayStats.minQueueDelay.tv_sec)
                                            .arg(allStats.ethernetSch.queueStats[i].delayStats.minQueueDelay.tv_nsec));
        ui->statsTable->item(i+3,7)->setText( QString("%1:%2")
                                            .arg(allStats.ethernetSch.queueStats[i].delayStats.maxQueueDelay.tv_sec)
                                            .arg(allStats.ethernetSch.queueStats[i].delayStats.maxQueueDelay.tv_nsec));

        /*calculate average delay and print it.*/
        totalMsecs = 1000*allStats.ethernetSch.queueStats[i].delayStats.totalQueueDelay.tv_sec + allStats.ethernetSch.queueStats[i].delayStats.totalQueueDelay.tv_nsec/1000000;
        if(allStats.ethernetSch.queueStats[i].delayStats.queueDelayProcessed)
        {
            avgMSecs = totalMsecs/allStats.ethernetSch.queueStats[i].delayStats.queueDelayProcessed;
            //avgNSecs = (allStats.ethernetSch.queueStats[i].delayStats.totalQueueDelay.tv_nsec/allStats.ethernetSch.queueStats[i].delayStats.queueDelayProcessed);
            //avgNSecs+= (allStats.ethernetSch.queueStats[i].delayStats.totalQueueDelay.tv_sec/allStats.ethernetSch.queueStats[i].delayStats.queueDelayProcessed)*1000000000;

        }
        else
        {
            avgMSecs = 0;
           // avgNSecs = 0;
        }
        ui->statsTable->item(i+3,8)->setText( QString("%1").arg(avgMSecs));

        ui->statsTable->item(i+3,9)->setText( QString("%1").arg(allStats.ethernetSch.queueStats[i].qCurrentSize));
        ui->statsTable->item(i+3,10)->setText( QString("%1").arg(allStats.ethernetSch.queueStats[i].qOverflowBytes));
    }
    ui->progressBar_Q1_Length->setValue(allStats.ethernetSch.queueStats[0].qUsage);
    ui->progressBar_Q2_Length->setValue(allStats.ethernetSch.queueStats[1].qUsage);
    ui->progressBar_Q3_Length->setValue(allStats.ethernetSch.queueStats[2].qUsage);
    ui->progressBar_Q4_Length->setValue(allStats.ethernetSch.queueStats[3].qUsage);
    ui->progressBar_Q5_Length->setValue(allStats.ethernetSch.queueStats[4].qUsage);
    ui->progressBar_Q6_Length->setValue(allStats.ethernetSch.queueStats[5].qUsage);
    ui->progressBar_Q7_Length->setValue(allStats.ethernetSch.queueStats[6].qUsage);
    ui->progressBar_Q8_Length->setValue(allStats.ethernetSch.queueStats[7].qUsage);

    ui->statsTable->item(11,3)->setText( QString("%1").arg(allStats.ethernetSch.processed));
    ui->statsTable->item(12,3)->setText( QString("%1").arg(allStats.ethernetSch.dataProcessed));
    ui->statsTable->item(13,3)->setText( QString("%1").arg(allStats.ethernetSch.sndSucceeded));
    ui->statsTable->item(14,3)->setText( QString("%1").arg(allStats.ethernetSch.sndFailed));

    /*ethernetTx*/
    ui->statsTable->item(1,12)->setText( QString("%1").arg(allStats.ethernetTx.ethernetPacketIn));
    ui->statsTable->item(2,12)->setText( QString("%1").arg(allStats.ethernetTx.queued));
    ui->statsTable->item(3,12)->setText( QString("%1").arg(allStats.ethernetTx.notQueued));
    ui->statsTable->item(4,12)->setText( QString("%1").arg(allStats.ethernetTx.dequeued));
    ui->statsTable->item(5,12)->setText( QString("%1").arg(allStats.ethernetTx.processed));
    ui->statsTable->item(6,12)->setText( QString("%1").arg(allStats.ethernetTx.dataProcessed));
    ui->statsTable->item(7,12)->setText( QString("%1").arg(allStats.ethernetTx.ipcProcessed));
    ui->statsTable->item(8,12)->setText( QString("%1").arg(allStats.ethernetTx.ethernetPacketOut));
    ui->statsTable->item(9,12)->setText( QString("%1").arg(allStats.ethernetTx.sndSucceeded));
    ui->statsTable->item(10,12)->setText( QString("%1").arg(allStats.ethernetTx.sndFailed));

}/*printStats*/

void MainWindow::showLog(const QString &qStr)
{
    ui->logEdit->insertPlainText(qStr);
    QTextCursor c =  ui->logEdit->textCursor();
    c.movePosition(QTextCursor::End);
    ui->logEdit->setTextCursor(c);
}

void MainWindow::reqStats(void)
{
    skNl->sendMsgShort(NL_MSGTYPE_STATS_REQ);
}

void MainWindow::showStats(void)
{
    printStats();
}

void MainWindow::setKernelModuleState(unsigned short isStarted)
{
    if(isStarted)
    {
        sprintf(logBuf,"%s: kernel module started.\n", __FUNCTION__);
        emit log(logBuf);
        ui->schSelectComboBox->setEnabled(false);
        ui->backlogTimeSelectComboBox->setEnabled(false);
        ui->queueLengthSelectComboBox->setEnabled(false);
        ui->egressLinkRateComboBox->setEnabled(false);
        ui->sysStartButton->setEnabled(false);
        ui->sysStopButton->setEnabled(true);
    }
    else
    {
        sprintf(logBuf,"%s: kernel module stopped.\n", __FUNCTION__);
        emit log(logBuf);
        ui->schSelectComboBox->setEnabled(true);
        ui->backlogTimeSelectComboBox->setEnabled(true);
        ui->queueLengthSelectComboBox->setEnabled(true);
        ui->egressLinkRateComboBox->setEnabled(true);
        ui->sysStartButton->setEnabled(true);
        ui->sysStopButton->setEnabled(false);
    }
}

void MainWindow::on_sysStartButton_clicked()
{
    on_schSelectComboBox_currentIndexChanged(ui->schSelectComboBox->currentIndex());
    on_backlogTimeSelectComboBox_currentIndexChanged(ui->backlogTimeSelectComboBox->currentIndex());
    on_queueLengthSelectComboBox_currentIndexChanged(ui->queueLengthSelectComboBox->currentIndex());
    on_egressLinkRateComboBox_currentIndexChanged(ui->egressLinkRateComboBox->currentIndex());
    skNl->sendMsgShort(NL_MSGTYPE_MODULESTART);
    sprintf(logBuf,"%s: System start command was sent.\n", __FUNCTION__);
    emit log(logBuf);
}

void MainWindow::on_sysStopButton_clicked()
{
    skNl->sendMsgShort(NL_MSGTYPE_MODULESTOP);
    sprintf(logBuf,"%s: System stop command was sent.\n", __FUNCTION__);
    emit log(logBuf);
}


void MainWindow::on_schSelectComboBox_currentIndexChanged(int index)
{
    sprintf(logBuf,"%s: index(%d)\n", __FUNCTION__, index);
    emit log(logBuf);
    switch(index)
    {
        case FIFO:
            emit log("\t FIFO scheduler selected.\n");
        break;
        case ROUND_ROBIN:
            emit log("\t ROUND_ROBIN scheduler selected.\n");
        break;
        case WEIGHTED_ROUND_ROBIN:
            emit log("\t WEIGHTED_ROUND_ROBIN scheduler selected.\n");
        break;
        case DEFICIT_ROUND_ROBIN:
            emit log("\t DEFICIT_ROUND_ROBIN scheduler selected.\n");
        break;
        case WF2Q:
            emit log("\t WF2Q scheduler selected.\n");
        break;
        case DTABLE:
            emit log("\t DTABLE scheduler selected.\n");
        break;
        default:
            emit log("\t Scheduler selection error!\n");
            return;
        break;
    }
    skNl->sendMsgLong(NL_MSGTYPE_CHANGE_SCHEDULER,&index,sizeof(int));
}


void MainWindow::on_backlogTimeSelectComboBox_currentIndexChanged(int index)
{
    int msecs;
    /*get the selected text and convert it to integer.*/
    msecs = ui->backlogTimeSelectComboBox->currentText().toInt();
    sprintf(logBuf,"%s: index(%d): %d mSecs\n", __FUNCTION__, index,msecs);
    emit log(logBuf);
    skNl->sendMsgLong(NL_MSGTYPE_SET_BACKLOG_TIME,&msecs,sizeof(int));
}

void MainWindow::on_queueLengthSelectComboBox_currentIndexChanged(int index)
{
    int bytes;
    /*get the selected text and convert it to integer.*/
    bytes = ONEKILOBYTES*ui->queueLengthSelectComboBox->currentText().toInt();
    sprintf(logBuf,"%s: index(%d): %d bytes\n", __FUNCTION__, index,bytes);
    emit log(logBuf);
    skNl->sendMsgLong(NL_MSGTYPE_SET_SCHEDULERQUEUE_LENGTH,&bytes,sizeof(int));
}

void MainWindow::on_egressLinkRateComboBox_currentIndexChanged(int index)
{
    int rate;
    rate = ui->egressLinkRateComboBox->currentText().toInt();
    sprintf(logBuf,"%s: index(%d): rate: %d MBits/sec\n", __FUNCTION__, index,rate);
    emit log(logBuf);
    skNl->sendMsgLong(NL_MSGTYPE_SET_EGRESS_LINK_RATE,&rate,sizeof(int));
}
