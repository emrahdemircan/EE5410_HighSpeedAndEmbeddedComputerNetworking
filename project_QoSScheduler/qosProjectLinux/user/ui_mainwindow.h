/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Jan 27 13:06:32 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *schSelectComboBox;
    QLabel *label_12;
    QComboBox *egressLinkRateComboBox;
    QLabel *label_2;
    QComboBox *backlogTimeSelectComboBox;
    QLabel *label_3;
    QComboBox *queueLengthSelectComboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *sysStartButton;
    QPushButton *sysStopButton;
    QTabWidget *tabWidget;
    QWidget *statTab;
    QVBoxLayout *verticalLayout;
    QTableWidget *statsTable;
    QGridLayout *gridLayout_10;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QProgressBar *progressBar_Q1_Length;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QProgressBar *progressBar_Q2_Length;
    QGridLayout *gridLayout_4;
    QLabel *label_6;
    QProgressBar *progressBar_Q3_Length;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    QProgressBar *progressBar_Q4_Length;
    QGridLayout *gridLayout_6;
    QLabel *label_8;
    QProgressBar *progressBar_Q5_Length;
    QGridLayout *gridLayout_7;
    QLabel *label_9;
    QProgressBar *progressBar_Q6_Length;
    QGridLayout *gridLayout_8;
    QLabel *label_10;
    QProgressBar *progressBar_Q7_Length;
    QGridLayout *gridLayout_9;
    QLabel *label_11;
    QProgressBar *progressBar_Q8_Length;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *logEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 800);
        QFont font;
        font.setPointSize(8);
        MainWindow->setFont(font);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setLocale(QLocale(QLocale::Turkish, QLocale::Turkey));
        MainWindow->setIconSize(QSize(24, 24));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_12 = new QGridLayout(centralWidget);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(6);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        schSelectComboBox = new QComboBox(centralWidget);
        schSelectComboBox->setObjectName(QString::fromUtf8("schSelectComboBox"));

        gridLayout->addWidget(schSelectComboBox, 0, 1, 1, 1);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 0, 2, 1, 1);

        egressLinkRateComboBox = new QComboBox(centralWidget);
        egressLinkRateComboBox->setObjectName(QString::fromUtf8("egressLinkRateComboBox"));

        gridLayout->addWidget(egressLinkRateComboBox, 0, 3, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 4, 1, 1);

        backlogTimeSelectComboBox = new QComboBox(centralWidget);
        backlogTimeSelectComboBox->setObjectName(QString::fromUtf8("backlogTimeSelectComboBox"));

        gridLayout->addWidget(backlogTimeSelectComboBox, 0, 5, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 6, 1, 1);

        queueLengthSelectComboBox = new QComboBox(centralWidget);
        queueLengthSelectComboBox->setObjectName(QString::fromUtf8("queueLengthSelectComboBox"));

        gridLayout->addWidget(queueLengthSelectComboBox, 0, 7, 1, 1);

        horizontalSpacer = new QSpacerItem(138, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 8, 1, 1);

        sysStartButton = new QPushButton(centralWidget);
        sysStartButton->setObjectName(QString::fromUtf8("sysStartButton"));

        gridLayout->addWidget(sysStartButton, 0, 9, 1, 1);

        sysStopButton = new QPushButton(centralWidget);
        sysStopButton->setObjectName(QString::fromUtf8("sysStopButton"));

        gridLayout->addWidget(sysStopButton, 0, 10, 1, 1);


        gridLayout_11->addLayout(gridLayout, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setFont(font);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        statTab = new QWidget();
        statTab->setObjectName(QString::fromUtf8("statTab"));
        verticalLayout = new QVBoxLayout(statTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        statsTable = new QTableWidget(statTab);
        if (statsTable->columnCount() < 13)
            statsTable->setColumnCount(13);
        QFont font1;
        font1.setPointSize(6);
        font1.setBold(true);
        font1.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        statsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        statsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        statsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font1);
        statsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font1);
        statsTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font1);
        statsTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font1);
        statsTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font1);
        statsTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font1);
        statsTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font1);
        statsTable->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        statsTable->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        statsTable->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        statsTable->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        if (statsTable->rowCount() < 15)
            statsTable->setRowCount(15);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(4, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(5, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(6, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(7, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(8, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(9, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(10, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(11, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(12, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(13, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        statsTable->setVerticalHeaderItem(14, __qtablewidgetitem27);
        QBrush brush(QColor(0, 170, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setFont(font2);
        __qtablewidgetitem28->setBackground(brush);
        statsTable->setItem(0, 0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setBackground(brush);
        statsTable->setItem(0, 1, __qtablewidgetitem29);
        QBrush brush1(QColor(0, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        __qtablewidgetitem30->setFont(font2);
        __qtablewidgetitem30->setBackground(brush1);
        statsTable->setItem(0, 2, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        __qtablewidgetitem31->setBackground(brush1);
        statsTable->setItem(0, 3, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        __qtablewidgetitem32->setFont(font2);
        __qtablewidgetitem32->setBackground(brush1);
        statsTable->setItem(0, 4, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        __qtablewidgetitem33->setBackground(brush1);
        statsTable->setItem(0, 5, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        __qtablewidgetitem34->setBackground(brush1);
        statsTable->setItem(0, 6, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        __qtablewidgetitem35->setBackground(brush1);
        statsTable->setItem(0, 7, __qtablewidgetitem35);
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        __qtablewidgetitem36->setFont(font3);
        __qtablewidgetitem36->setBackground(brush1);
        statsTable->setItem(0, 8, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        __qtablewidgetitem37->setFont(font2);
        __qtablewidgetitem37->setBackground(brush1);
        statsTable->setItem(0, 9, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        __qtablewidgetitem38->setBackground(brush1);
        statsTable->setItem(0, 10, __qtablewidgetitem38);
        QBrush brush2(QColor(199, 255, 227, 255));
        brush2.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        __qtablewidgetitem39->setFont(font2);
        __qtablewidgetitem39->setBackground(brush2);
        statsTable->setItem(0, 11, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        __qtablewidgetitem40->setBackground(brush2);
        statsTable->setItem(0, 12, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        statsTable->setItem(1, 0, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        statsTable->setItem(1, 1, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        statsTable->setItem(1, 2, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        statsTable->setItem(1, 3, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        statsTable->setItem(1, 4, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        statsTable->setItem(1, 5, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        statsTable->setItem(1, 6, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        statsTable->setItem(1, 7, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        statsTable->setItem(1, 8, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        statsTable->setItem(1, 9, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        statsTable->setItem(1, 10, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        statsTable->setItem(1, 11, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        statsTable->setItem(1, 12, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        statsTable->setItem(2, 0, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        statsTable->setItem(2, 1, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        statsTable->setItem(2, 2, __qtablewidgetitem56);
        QFont font4;
        font4.setItalic(true);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        __qtablewidgetitem57->setFont(font4);
        statsTable->setItem(2, 3, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        __qtablewidgetitem58->setFont(font4);
        statsTable->setItem(2, 4, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        __qtablewidgetitem59->setFont(font4);
        statsTable->setItem(2, 5, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        __qtablewidgetitem60->setFont(font4);
        statsTable->setItem(2, 6, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        __qtablewidgetitem61->setFont(font4);
        statsTable->setItem(2, 7, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        __qtablewidgetitem62->setFont(font4);
        statsTable->setItem(2, 8, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        __qtablewidgetitem63->setFont(font4);
        statsTable->setItem(2, 9, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        __qtablewidgetitem64->setFont(font4);
        statsTable->setItem(2, 10, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        statsTable->setItem(2, 11, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        statsTable->setItem(2, 12, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        statsTable->setItem(3, 0, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        statsTable->setItem(3, 1, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        statsTable->setItem(3, 2, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        statsTable->setItem(3, 3, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        statsTable->setItem(3, 4, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        statsTable->setItem(3, 5, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        statsTable->setItem(3, 6, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        statsTable->setItem(3, 7, __qtablewidgetitem74);
        QFont font5;
        font5.setItalic(false);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        __qtablewidgetitem75->setFont(font5);
        statsTable->setItem(3, 8, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        statsTable->setItem(3, 9, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        statsTable->setItem(3, 10, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        statsTable->setItem(3, 11, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        statsTable->setItem(3, 12, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        statsTable->setItem(4, 0, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        statsTable->setItem(4, 1, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        statsTable->setItem(4, 2, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        statsTable->setItem(4, 3, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        statsTable->setItem(4, 4, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        statsTable->setItem(4, 5, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        statsTable->setItem(4, 6, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        statsTable->setItem(4, 7, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        statsTable->setItem(4, 8, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        statsTable->setItem(4, 9, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        statsTable->setItem(4, 10, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        statsTable->setItem(4, 11, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        statsTable->setItem(4, 12, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        statsTable->setItem(5, 0, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        statsTable->setItem(5, 1, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        statsTable->setItem(5, 2, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        statsTable->setItem(5, 3, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        statsTable->setItem(5, 4, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        statsTable->setItem(5, 5, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        statsTable->setItem(5, 6, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        statsTable->setItem(5, 7, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        statsTable->setItem(5, 8, __qtablewidgetitem101);
        QTableWidgetItem *__qtablewidgetitem102 = new QTableWidgetItem();
        statsTable->setItem(5, 9, __qtablewidgetitem102);
        QTableWidgetItem *__qtablewidgetitem103 = new QTableWidgetItem();
        statsTable->setItem(5, 10, __qtablewidgetitem103);
        QTableWidgetItem *__qtablewidgetitem104 = new QTableWidgetItem();
        statsTable->setItem(5, 11, __qtablewidgetitem104);
        QTableWidgetItem *__qtablewidgetitem105 = new QTableWidgetItem();
        statsTable->setItem(5, 12, __qtablewidgetitem105);
        QTableWidgetItem *__qtablewidgetitem106 = new QTableWidgetItem();
        statsTable->setItem(6, 0, __qtablewidgetitem106);
        QTableWidgetItem *__qtablewidgetitem107 = new QTableWidgetItem();
        statsTable->setItem(6, 1, __qtablewidgetitem107);
        QTableWidgetItem *__qtablewidgetitem108 = new QTableWidgetItem();
        __qtablewidgetitem108->setFont(font3);
        statsTable->setItem(6, 2, __qtablewidgetitem108);
        QTableWidgetItem *__qtablewidgetitem109 = new QTableWidgetItem();
        statsTable->setItem(6, 3, __qtablewidgetitem109);
        QTableWidgetItem *__qtablewidgetitem110 = new QTableWidgetItem();
        statsTable->setItem(6, 4, __qtablewidgetitem110);
        QTableWidgetItem *__qtablewidgetitem111 = new QTableWidgetItem();
        statsTable->setItem(6, 5, __qtablewidgetitem111);
        QTableWidgetItem *__qtablewidgetitem112 = new QTableWidgetItem();
        statsTable->setItem(6, 6, __qtablewidgetitem112);
        QTableWidgetItem *__qtablewidgetitem113 = new QTableWidgetItem();
        statsTable->setItem(6, 7, __qtablewidgetitem113);
        QTableWidgetItem *__qtablewidgetitem114 = new QTableWidgetItem();
        statsTable->setItem(6, 8, __qtablewidgetitem114);
        QTableWidgetItem *__qtablewidgetitem115 = new QTableWidgetItem();
        statsTable->setItem(6, 9, __qtablewidgetitem115);
        QTableWidgetItem *__qtablewidgetitem116 = new QTableWidgetItem();
        statsTable->setItem(6, 10, __qtablewidgetitem116);
        QTableWidgetItem *__qtablewidgetitem117 = new QTableWidgetItem();
        statsTable->setItem(6, 11, __qtablewidgetitem117);
        QTableWidgetItem *__qtablewidgetitem118 = new QTableWidgetItem();
        statsTable->setItem(6, 12, __qtablewidgetitem118);
        QTableWidgetItem *__qtablewidgetitem119 = new QTableWidgetItem();
        statsTable->setItem(7, 0, __qtablewidgetitem119);
        QTableWidgetItem *__qtablewidgetitem120 = new QTableWidgetItem();
        statsTable->setItem(7, 1, __qtablewidgetitem120);
        QTableWidgetItem *__qtablewidgetitem121 = new QTableWidgetItem();
        statsTable->setItem(7, 2, __qtablewidgetitem121);
        QTableWidgetItem *__qtablewidgetitem122 = new QTableWidgetItem();
        statsTable->setItem(7, 3, __qtablewidgetitem122);
        QTableWidgetItem *__qtablewidgetitem123 = new QTableWidgetItem();
        statsTable->setItem(7, 4, __qtablewidgetitem123);
        QTableWidgetItem *__qtablewidgetitem124 = new QTableWidgetItem();
        statsTable->setItem(7, 5, __qtablewidgetitem124);
        QTableWidgetItem *__qtablewidgetitem125 = new QTableWidgetItem();
        statsTable->setItem(7, 6, __qtablewidgetitem125);
        QTableWidgetItem *__qtablewidgetitem126 = new QTableWidgetItem();
        statsTable->setItem(7, 7, __qtablewidgetitem126);
        QTableWidgetItem *__qtablewidgetitem127 = new QTableWidgetItem();
        statsTable->setItem(7, 8, __qtablewidgetitem127);
        QTableWidgetItem *__qtablewidgetitem128 = new QTableWidgetItem();
        statsTable->setItem(7, 9, __qtablewidgetitem128);
        QTableWidgetItem *__qtablewidgetitem129 = new QTableWidgetItem();
        statsTable->setItem(7, 10, __qtablewidgetitem129);
        QTableWidgetItem *__qtablewidgetitem130 = new QTableWidgetItem();
        statsTable->setItem(7, 11, __qtablewidgetitem130);
        QTableWidgetItem *__qtablewidgetitem131 = new QTableWidgetItem();
        statsTable->setItem(7, 12, __qtablewidgetitem131);
        QTableWidgetItem *__qtablewidgetitem132 = new QTableWidgetItem();
        statsTable->setItem(8, 0, __qtablewidgetitem132);
        QTableWidgetItem *__qtablewidgetitem133 = new QTableWidgetItem();
        statsTable->setItem(8, 1, __qtablewidgetitem133);
        QTableWidgetItem *__qtablewidgetitem134 = new QTableWidgetItem();
        statsTable->setItem(8, 2, __qtablewidgetitem134);
        QTableWidgetItem *__qtablewidgetitem135 = new QTableWidgetItem();
        statsTable->setItem(8, 3, __qtablewidgetitem135);
        QTableWidgetItem *__qtablewidgetitem136 = new QTableWidgetItem();
        __qtablewidgetitem136->setFont(font3);
        statsTable->setItem(8, 4, __qtablewidgetitem136);
        QTableWidgetItem *__qtablewidgetitem137 = new QTableWidgetItem();
        statsTable->setItem(8, 5, __qtablewidgetitem137);
        QTableWidgetItem *__qtablewidgetitem138 = new QTableWidgetItem();
        statsTable->setItem(8, 6, __qtablewidgetitem138);
        QTableWidgetItem *__qtablewidgetitem139 = new QTableWidgetItem();
        statsTable->setItem(8, 7, __qtablewidgetitem139);
        QTableWidgetItem *__qtablewidgetitem140 = new QTableWidgetItem();
        statsTable->setItem(8, 8, __qtablewidgetitem140);
        QTableWidgetItem *__qtablewidgetitem141 = new QTableWidgetItem();
        statsTable->setItem(8, 9, __qtablewidgetitem141);
        QTableWidgetItem *__qtablewidgetitem142 = new QTableWidgetItem();
        statsTable->setItem(8, 10, __qtablewidgetitem142);
        QTableWidgetItem *__qtablewidgetitem143 = new QTableWidgetItem();
        statsTable->setItem(8, 11, __qtablewidgetitem143);
        QTableWidgetItem *__qtablewidgetitem144 = new QTableWidgetItem();
        statsTable->setItem(8, 12, __qtablewidgetitem144);
        QTableWidgetItem *__qtablewidgetitem145 = new QTableWidgetItem();
        statsTable->setItem(9, 0, __qtablewidgetitem145);
        QTableWidgetItem *__qtablewidgetitem146 = new QTableWidgetItem();
        statsTable->setItem(9, 1, __qtablewidgetitem146);
        QTableWidgetItem *__qtablewidgetitem147 = new QTableWidgetItem();
        statsTable->setItem(9, 2, __qtablewidgetitem147);
        QTableWidgetItem *__qtablewidgetitem148 = new QTableWidgetItem();
        statsTable->setItem(9, 3, __qtablewidgetitem148);
        QTableWidgetItem *__qtablewidgetitem149 = new QTableWidgetItem();
        __qtablewidgetitem149->setFont(font3);
        statsTable->setItem(9, 4, __qtablewidgetitem149);
        QTableWidgetItem *__qtablewidgetitem150 = new QTableWidgetItem();
        statsTable->setItem(9, 5, __qtablewidgetitem150);
        QTableWidgetItem *__qtablewidgetitem151 = new QTableWidgetItem();
        statsTable->setItem(9, 6, __qtablewidgetitem151);
        QTableWidgetItem *__qtablewidgetitem152 = new QTableWidgetItem();
        statsTable->setItem(9, 7, __qtablewidgetitem152);
        QTableWidgetItem *__qtablewidgetitem153 = new QTableWidgetItem();
        statsTable->setItem(9, 8, __qtablewidgetitem153);
        QTableWidgetItem *__qtablewidgetitem154 = new QTableWidgetItem();
        statsTable->setItem(9, 9, __qtablewidgetitem154);
        QTableWidgetItem *__qtablewidgetitem155 = new QTableWidgetItem();
        statsTable->setItem(9, 10, __qtablewidgetitem155);
        QTableWidgetItem *__qtablewidgetitem156 = new QTableWidgetItem();
        statsTable->setItem(9, 11, __qtablewidgetitem156);
        QTableWidgetItem *__qtablewidgetitem157 = new QTableWidgetItem();
        statsTable->setItem(9, 12, __qtablewidgetitem157);
        QTableWidgetItem *__qtablewidgetitem158 = new QTableWidgetItem();
        statsTable->setItem(10, 0, __qtablewidgetitem158);
        QTableWidgetItem *__qtablewidgetitem159 = new QTableWidgetItem();
        statsTable->setItem(10, 1, __qtablewidgetitem159);
        QTableWidgetItem *__qtablewidgetitem160 = new QTableWidgetItem();
        __qtablewidgetitem160->setFont(font3);
        statsTable->setItem(10, 2, __qtablewidgetitem160);
        QTableWidgetItem *__qtablewidgetitem161 = new QTableWidgetItem();
        statsTable->setItem(10, 3, __qtablewidgetitem161);
        QTableWidgetItem *__qtablewidgetitem162 = new QTableWidgetItem();
        __qtablewidgetitem162->setFont(font3);
        statsTable->setItem(10, 4, __qtablewidgetitem162);
        QTableWidgetItem *__qtablewidgetitem163 = new QTableWidgetItem();
        statsTable->setItem(10, 5, __qtablewidgetitem163);
        QTableWidgetItem *__qtablewidgetitem164 = new QTableWidgetItem();
        statsTable->setItem(10, 6, __qtablewidgetitem164);
        QTableWidgetItem *__qtablewidgetitem165 = new QTableWidgetItem();
        statsTable->setItem(10, 7, __qtablewidgetitem165);
        QTableWidgetItem *__qtablewidgetitem166 = new QTableWidgetItem();
        statsTable->setItem(10, 8, __qtablewidgetitem166);
        QTableWidgetItem *__qtablewidgetitem167 = new QTableWidgetItem();
        statsTable->setItem(10, 9, __qtablewidgetitem167);
        QTableWidgetItem *__qtablewidgetitem168 = new QTableWidgetItem();
        statsTable->setItem(10, 10, __qtablewidgetitem168);
        QTableWidgetItem *__qtablewidgetitem169 = new QTableWidgetItem();
        statsTable->setItem(10, 11, __qtablewidgetitem169);
        QTableWidgetItem *__qtablewidgetitem170 = new QTableWidgetItem();
        statsTable->setItem(10, 12, __qtablewidgetitem170);
        QTableWidgetItem *__qtablewidgetitem171 = new QTableWidgetItem();
        statsTable->setItem(11, 0, __qtablewidgetitem171);
        QTableWidgetItem *__qtablewidgetitem172 = new QTableWidgetItem();
        statsTable->setItem(11, 1, __qtablewidgetitem172);
        QTableWidgetItem *__qtablewidgetitem173 = new QTableWidgetItem();
        __qtablewidgetitem173->setFont(font3);
        statsTable->setItem(11, 2, __qtablewidgetitem173);
        QTableWidgetItem *__qtablewidgetitem174 = new QTableWidgetItem();
        statsTable->setItem(11, 3, __qtablewidgetitem174);
        QTableWidgetItem *__qtablewidgetitem175 = new QTableWidgetItem();
        statsTable->setItem(11, 4, __qtablewidgetitem175);
        QTableWidgetItem *__qtablewidgetitem176 = new QTableWidgetItem();
        statsTable->setItem(11, 5, __qtablewidgetitem176);
        QTableWidgetItem *__qtablewidgetitem177 = new QTableWidgetItem();
        statsTable->setItem(11, 8, __qtablewidgetitem177);
        QTableWidgetItem *__qtablewidgetitem178 = new QTableWidgetItem();
        statsTable->setItem(11, 9, __qtablewidgetitem178);
        QTableWidgetItem *__qtablewidgetitem179 = new QTableWidgetItem();
        statsTable->setItem(12, 0, __qtablewidgetitem179);
        QTableWidgetItem *__qtablewidgetitem180 = new QTableWidgetItem();
        statsTable->setItem(12, 1, __qtablewidgetitem180);
        QTableWidgetItem *__qtablewidgetitem181 = new QTableWidgetItem();
        __qtablewidgetitem181->setFont(font3);
        statsTable->setItem(12, 2, __qtablewidgetitem181);
        QTableWidgetItem *__qtablewidgetitem182 = new QTableWidgetItem();
        statsTable->setItem(12, 3, __qtablewidgetitem182);
        QTableWidgetItem *__qtablewidgetitem183 = new QTableWidgetItem();
        statsTable->setItem(12, 4, __qtablewidgetitem183);
        QTableWidgetItem *__qtablewidgetitem184 = new QTableWidgetItem();
        statsTable->setItem(12, 5, __qtablewidgetitem184);
        QTableWidgetItem *__qtablewidgetitem185 = new QTableWidgetItem();
        statsTable->setItem(12, 8, __qtablewidgetitem185);
        QTableWidgetItem *__qtablewidgetitem186 = new QTableWidgetItem();
        statsTable->setItem(12, 9, __qtablewidgetitem186);
        QTableWidgetItem *__qtablewidgetitem187 = new QTableWidgetItem();
        statsTable->setItem(13, 0, __qtablewidgetitem187);
        QTableWidgetItem *__qtablewidgetitem188 = new QTableWidgetItem();
        statsTable->setItem(13, 1, __qtablewidgetitem188);
        QTableWidgetItem *__qtablewidgetitem189 = new QTableWidgetItem();
        statsTable->setItem(13, 2, __qtablewidgetitem189);
        QTableWidgetItem *__qtablewidgetitem190 = new QTableWidgetItem();
        statsTable->setItem(13, 3, __qtablewidgetitem190);
        QTableWidgetItem *__qtablewidgetitem191 = new QTableWidgetItem();
        statsTable->setItem(13, 4, __qtablewidgetitem191);
        QTableWidgetItem *__qtablewidgetitem192 = new QTableWidgetItem();
        statsTable->setItem(13, 5, __qtablewidgetitem192);
        QTableWidgetItem *__qtablewidgetitem193 = new QTableWidgetItem();
        statsTable->setItem(13, 8, __qtablewidgetitem193);
        QTableWidgetItem *__qtablewidgetitem194 = new QTableWidgetItem();
        statsTable->setItem(13, 9, __qtablewidgetitem194);
        QTableWidgetItem *__qtablewidgetitem195 = new QTableWidgetItem();
        statsTable->setItem(14, 0, __qtablewidgetitem195);
        QTableWidgetItem *__qtablewidgetitem196 = new QTableWidgetItem();
        statsTable->setItem(14, 1, __qtablewidgetitem196);
        QTableWidgetItem *__qtablewidgetitem197 = new QTableWidgetItem();
        __qtablewidgetitem197->setFont(font3);
        statsTable->setItem(14, 2, __qtablewidgetitem197);
        QTableWidgetItem *__qtablewidgetitem198 = new QTableWidgetItem();
        statsTable->setItem(14, 3, __qtablewidgetitem198);
        QTableWidgetItem *__qtablewidgetitem199 = new QTableWidgetItem();
        __qtablewidgetitem199->setFont(font3);
        statsTable->setItem(14, 4, __qtablewidgetitem199);
        QTableWidgetItem *__qtablewidgetitem200 = new QTableWidgetItem();
        statsTable->setItem(14, 5, __qtablewidgetitem200);
        QTableWidgetItem *__qtablewidgetitem201 = new QTableWidgetItem();
        statsTable->setItem(14, 8, __qtablewidgetitem201);
        QTableWidgetItem *__qtablewidgetitem202 = new QTableWidgetItem();
        statsTable->setItem(14, 9, __qtablewidgetitem202);
        statsTable->setObjectName(QString::fromUtf8("statsTable"));
        statsTable->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(statsTable->sizePolicy().hasHeightForWidth());
        statsTable->setSizePolicy(sizePolicy2);
        statsTable->setMinimumSize(QSize(100, 280));
        statsTable->setMaximumSize(QSize(16777215, 16777215));
        QFont font6;
        font6.setPointSize(6);
        statsTable->setFont(font6);
        statsTable->setAutoScrollMargin(20);
        statsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        statsTable->setSelectionMode(QAbstractItemView::NoSelection);
        statsTable->setCornerButtonEnabled(false);
        statsTable->setRowCount(15);
        statsTable->horizontalHeader()->setVisible(false);
        statsTable->horizontalHeader()->setDefaultSectionSize(101);
        statsTable->horizontalHeader()->setMinimumSectionSize(101);
        statsTable->horizontalHeader()->setStretchLastSection(false);
        statsTable->verticalHeader()->setVisible(false);
        statsTable->verticalHeader()->setCascadingSectionResizes(false);
        statsTable->verticalHeader()->setDefaultSectionSize(16);
        statsTable->verticalHeader()->setMinimumSectionSize(16);
        statsTable->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(statsTable);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(statTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        progressBar_Q1_Length = new QProgressBar(statTab);
        progressBar_Q1_Length->setObjectName(QString::fromUtf8("progressBar_Q1_Length"));
        progressBar_Q1_Length->setMinimumSize(QSize(140, 0));
        progressBar_Q1_Length->setFont(font);
        progressBar_Q1_Length->setMaximum(100);
        progressBar_Q1_Length->setValue(0);

        gridLayout_2->addWidget(progressBar_Q1_Length, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_2, 0, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_5 = new QLabel(statTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        progressBar_Q2_Length = new QProgressBar(statTab);
        progressBar_Q2_Length->setObjectName(QString::fromUtf8("progressBar_Q2_Length"));
        progressBar_Q2_Length->setMinimumSize(QSize(140, 0));
        progressBar_Q2_Length->setMaximum(100);
        progressBar_Q2_Length->setValue(0);

        gridLayout_3->addWidget(progressBar_Q2_Length, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_3, 0, 2, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_6 = new QLabel(statTab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        progressBar_Q3_Length = new QProgressBar(statTab);
        progressBar_Q3_Length->setObjectName(QString::fromUtf8("progressBar_Q3_Length"));
        progressBar_Q3_Length->setMinimumSize(QSize(140, 0));
        progressBar_Q3_Length->setMinimum(0);
        progressBar_Q3_Length->setMaximum(100);
        progressBar_Q3_Length->setValue(-1);

        gridLayout_4->addWidget(progressBar_Q3_Length, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_4, 0, 3, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_7 = new QLabel(statTab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        progressBar_Q4_Length = new QProgressBar(statTab);
        progressBar_Q4_Length->setObjectName(QString::fromUtf8("progressBar_Q4_Length"));
        progressBar_Q4_Length->setMinimumSize(QSize(140, 0));
        progressBar_Q4_Length->setMaximum(100);
        progressBar_Q4_Length->setValue(0);

        gridLayout_5->addWidget(progressBar_Q4_Length, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_5, 0, 4, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_8 = new QLabel(statTab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        progressBar_Q5_Length = new QProgressBar(statTab);
        progressBar_Q5_Length->setObjectName(QString::fromUtf8("progressBar_Q5_Length"));
        progressBar_Q5_Length->setMinimumSize(QSize(140, 0));
        progressBar_Q5_Length->setMaximum(100);
        progressBar_Q5_Length->setValue(0);

        gridLayout_6->addWidget(progressBar_Q5_Length, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_6, 0, 5, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_9 = new QLabel(statTab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_9, 0, 0, 1, 1);

        progressBar_Q6_Length = new QProgressBar(statTab);
        progressBar_Q6_Length->setObjectName(QString::fromUtf8("progressBar_Q6_Length"));
        progressBar_Q6_Length->setMinimumSize(QSize(140, 0));
        progressBar_Q6_Length->setMaximum(100);
        progressBar_Q6_Length->setValue(0);

        gridLayout_7->addWidget(progressBar_Q6_Length, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_7, 0, 6, 1, 1);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_10 = new QLabel(statTab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_10, 0, 0, 1, 1);

        progressBar_Q7_Length = new QProgressBar(statTab);
        progressBar_Q7_Length->setObjectName(QString::fromUtf8("progressBar_Q7_Length"));
        progressBar_Q7_Length->setMinimumSize(QSize(140, 0));
        progressBar_Q7_Length->setMaximum(100);
        progressBar_Q7_Length->setValue(0);

        gridLayout_8->addWidget(progressBar_Q7_Length, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_8, 0, 7, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_11 = new QLabel(statTab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_11, 0, 0, 1, 1);

        progressBar_Q8_Length = new QProgressBar(statTab);
        progressBar_Q8_Length->setObjectName(QString::fromUtf8("progressBar_Q8_Length"));
        progressBar_Q8_Length->setMinimumSize(QSize(140, 0));
        progressBar_Q8_Length->setMaximum(100);
        progressBar_Q8_Length->setValue(0);

        gridLayout_9->addWidget(progressBar_Q8_Length, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 0, 8, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_2, 0, 9, 1, 1);


        verticalLayout->addLayout(gridLayout_10);

        logEdit = new QTextEdit(statTab);
        logEdit->setObjectName(QString::fromUtf8("logEdit"));
        sizePolicy1.setHeightForWidth(logEdit->sizePolicy().hasHeightForWidth());
        logEdit->setSizePolicy(sizePolicy1);
        logEdit->setMinimumSize(QSize(10, 1));
        logEdit->setMaximumSize(QSize(16777215, 16777215));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Courier 10 Pitch"));
        font7.setPointSize(9);
        logEdit->setFont(font7);
        logEdit->setAutoFillBackground(false);
        logEdit->setFrameShape(QFrame::StyledPanel);
        logEdit->setFrameShadow(QFrame::Sunken);
        logEdit->setLineWidth(1);
        logEdit->setMidLineWidth(0);
        logEdit->setLineWrapColumnOrWidth(1);
        logEdit->setReadOnly(true);

        verticalLayout->addWidget(logEdit);

        tabWidget->addTab(statTab, QString());

        gridLayout_11->addWidget(tabWidget, 1, 0, 1, 1);


        gridLayout_12->addLayout(gridLayout_11, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Output Queue Control", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "QOS Scheduler Type:", 0, QApplication::UnicodeUTF8));
        schSelectComboBox->clear();
        schSelectComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "FIFO", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Round Robin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Weighted Round Robin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Deficit Round Robin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "WF2Q", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "DTABLE", 0, QApplication::UnicodeUTF8)
        );
        label_12->setText(QApplication::translate("MainWindow", "Eggress Link Rate in MBits/sec:", 0, QApplication::UnicodeUTF8));
        egressLinkRateComboBox->clear();
        egressLinkRateComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("MainWindow", "Backlog Time in mSecs:", 0, QApplication::UnicodeUTF8));
        backlogTimeSelectComboBox->clear();
        backlogTimeSelectComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "25", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "250", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "4000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "5000", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("MainWindow", "Queue Length In KB:", 0, QApplication::UnicodeUTF8));
        queueLengthSelectComboBox->clear();
        queueLengthSelectComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "250", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1000", 0, QApplication::UnicodeUTF8)
        );
        sysStartButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        sysStopButton->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = statsTable->isSortingEnabled();
        statsTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = statsTable->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Ethernet RX", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = statsTable->item(0, 2);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Ethernet Scheduler", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = statsTable->item(0, 11);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Ethernet Tx", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = statsTable->item(1, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Eth. Pack. In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = statsTable->item(1, 1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = statsTable->item(1, 2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Eth. Pack. In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = statsTable->item(1, 3);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = statsTable->item(1, 11);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Eth. Pack. In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = statsTable->item(1, 12);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = statsTable->item(2, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Queued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = statsTable->item(2, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = statsTable->item(2, 3);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "Queued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = statsTable->item(2, 4);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "Not queued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = statsTable->item(2, 5);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "Dequeued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = statsTable->item(2, 6);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "Min Q Delay(sec:nsec)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = statsTable->item(2, 7);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "Max Q Delay(sec:nsec)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = statsTable->item(2, 8);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "Avg Q Delay (msec)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = statsTable->item(2, 9);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "Current Q Size", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = statsTable->item(2, 10);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "Overflowed Bytes", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = statsTable->item(2, 11);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "Queued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = statsTable->item(2, 12);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = statsTable->item(3, 0);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "Not queued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = statsTable->item(3, 1);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = statsTable->item(3, 2);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "Queue 1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = statsTable->item(3, 3);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = statsTable->item(3, 4);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = statsTable->item(3, 5);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = statsTable->item(3, 6);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = statsTable->item(3, 7);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = statsTable->item(3, 8);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = statsTable->item(3, 9);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = statsTable->item(3, 10);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = statsTable->item(3, 11);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "Not queued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = statsTable->item(3, 12);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = statsTable->item(4, 0);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "Dequeued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = statsTable->item(4, 1);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = statsTable->item(4, 2);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "Queue 2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = statsTable->item(4, 3);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = statsTable->item(4, 4);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem39 = statsTable->item(4, 5);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem40 = statsTable->item(4, 6);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem41 = statsTable->item(4, 7);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem42 = statsTable->item(4, 8);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem43 = statsTable->item(4, 9);
        ___qtablewidgetitem43->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem44 = statsTable->item(4, 10);
        ___qtablewidgetitem44->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem45 = statsTable->item(4, 11);
        ___qtablewidgetitem45->setText(QApplication::translate("MainWindow", "Dequeued", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem46 = statsTable->item(4, 12);
        ___qtablewidgetitem46->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem47 = statsTable->item(5, 0);
        ___qtablewidgetitem47->setText(QApplication::translate("MainWindow", "Processed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem48 = statsTable->item(5, 1);
        ___qtablewidgetitem48->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem49 = statsTable->item(5, 2);
        ___qtablewidgetitem49->setText(QApplication::translate("MainWindow", "Queue 3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem50 = statsTable->item(5, 3);
        ___qtablewidgetitem50->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem51 = statsTable->item(5, 4);
        ___qtablewidgetitem51->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem52 = statsTable->item(5, 5);
        ___qtablewidgetitem52->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem53 = statsTable->item(5, 6);
        ___qtablewidgetitem53->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem54 = statsTable->item(5, 7);
        ___qtablewidgetitem54->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem55 = statsTable->item(5, 8);
        ___qtablewidgetitem55->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem56 = statsTable->item(5, 9);
        ___qtablewidgetitem56->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem57 = statsTable->item(5, 10);
        ___qtablewidgetitem57->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem58 = statsTable->item(5, 11);
        ___qtablewidgetitem58->setText(QApplication::translate("MainWindow", "Processed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem59 = statsTable->item(5, 12);
        ___qtablewidgetitem59->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem60 = statsTable->item(6, 0);
        ___qtablewidgetitem60->setText(QApplication::translate("MainWindow", "Data Processed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem61 = statsTable->item(6, 1);
        ___qtablewidgetitem61->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem62 = statsTable->item(6, 2);
        ___qtablewidgetitem62->setText(QApplication::translate("MainWindow", "Queue 4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem63 = statsTable->item(6, 3);
        ___qtablewidgetitem63->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem64 = statsTable->item(6, 4);
        ___qtablewidgetitem64->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem65 = statsTable->item(6, 5);
        ___qtablewidgetitem65->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem66 = statsTable->item(6, 6);
        ___qtablewidgetitem66->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem67 = statsTable->item(6, 7);
        ___qtablewidgetitem67->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem68 = statsTable->item(6, 8);
        ___qtablewidgetitem68->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem69 = statsTable->item(6, 9);
        ___qtablewidgetitem69->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem70 = statsTable->item(6, 10);
        ___qtablewidgetitem70->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem71 = statsTable->item(6, 11);
        ___qtablewidgetitem71->setText(QApplication::translate("MainWindow", "Data Processed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem72 = statsTable->item(6, 12);
        ___qtablewidgetitem72->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem73 = statsTable->item(7, 0);
        ___qtablewidgetitem73->setText(QApplication::translate("MainWindow", "IPC Processed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem74 = statsTable->item(7, 1);
        ___qtablewidgetitem74->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem75 = statsTable->item(7, 2);
        ___qtablewidgetitem75->setText(QApplication::translate("MainWindow", "Queue 5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem76 = statsTable->item(7, 3);
        ___qtablewidgetitem76->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem77 = statsTable->item(7, 4);
        ___qtablewidgetitem77->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem78 = statsTable->item(7, 5);
        ___qtablewidgetitem78->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem79 = statsTable->item(7, 6);
        ___qtablewidgetitem79->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem80 = statsTable->item(7, 7);
        ___qtablewidgetitem80->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem81 = statsTable->item(7, 8);
        ___qtablewidgetitem81->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem82 = statsTable->item(7, 9);
        ___qtablewidgetitem82->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem83 = statsTable->item(7, 10);
        ___qtablewidgetitem83->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem84 = statsTable->item(7, 11);
        ___qtablewidgetitem84->setText(QApplication::translate("MainWindow", "IPC Processed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem85 = statsTable->item(7, 12);
        ___qtablewidgetitem85->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem86 = statsTable->item(8, 2);
        ___qtablewidgetitem86->setText(QApplication::translate("MainWindow", "Queue 6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem87 = statsTable->item(8, 3);
        ___qtablewidgetitem87->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem88 = statsTable->item(8, 4);
        ___qtablewidgetitem88->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem89 = statsTable->item(8, 5);
        ___qtablewidgetitem89->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem90 = statsTable->item(8, 6);
        ___qtablewidgetitem90->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem91 = statsTable->item(8, 7);
        ___qtablewidgetitem91->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem92 = statsTable->item(8, 8);
        ___qtablewidgetitem92->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem93 = statsTable->item(8, 9);
        ___qtablewidgetitem93->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem94 = statsTable->item(8, 10);
        ___qtablewidgetitem94->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem95 = statsTable->item(8, 11);
        ___qtablewidgetitem95->setText(QApplication::translate("MainWindow", "Eth. Pack. Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem96 = statsTable->item(8, 12);
        ___qtablewidgetitem96->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem97 = statsTable->item(9, 2);
        ___qtablewidgetitem97->setText(QApplication::translate("MainWindow", "Queue 7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem98 = statsTable->item(9, 3);
        ___qtablewidgetitem98->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem99 = statsTable->item(9, 4);
        ___qtablewidgetitem99->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem100 = statsTable->item(9, 5);
        ___qtablewidgetitem100->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem101 = statsTable->item(9, 6);
        ___qtablewidgetitem101->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem102 = statsTable->item(9, 7);
        ___qtablewidgetitem102->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem103 = statsTable->item(9, 8);
        ___qtablewidgetitem103->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem104 = statsTable->item(9, 9);
        ___qtablewidgetitem104->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem105 = statsTable->item(9, 10);
        ___qtablewidgetitem105->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem106 = statsTable->item(9, 11);
        ___qtablewidgetitem106->setText(QApplication::translate("MainWindow", "Send Succeded", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem107 = statsTable->item(9, 12);
        ___qtablewidgetitem107->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem108 = statsTable->item(10, 2);
        ___qtablewidgetitem108->setText(QApplication::translate("MainWindow", "Queue 8", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem109 = statsTable->item(10, 3);
        ___qtablewidgetitem109->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem110 = statsTable->item(10, 4);
        ___qtablewidgetitem110->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem111 = statsTable->item(10, 5);
        ___qtablewidgetitem111->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem112 = statsTable->item(10, 6);
        ___qtablewidgetitem112->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem113 = statsTable->item(10, 7);
        ___qtablewidgetitem113->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem114 = statsTable->item(10, 8);
        ___qtablewidgetitem114->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem115 = statsTable->item(10, 9);
        ___qtablewidgetitem115->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem116 = statsTable->item(10, 10);
        ___qtablewidgetitem116->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem117 = statsTable->item(10, 11);
        ___qtablewidgetitem117->setText(QApplication::translate("MainWindow", "Send Failed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem118 = statsTable->item(10, 12);
        ___qtablewidgetitem118->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem119 = statsTable->item(11, 2);
        ___qtablewidgetitem119->setText(QApplication::translate("MainWindow", "Processed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem120 = statsTable->item(11, 3);
        ___qtablewidgetitem120->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem121 = statsTable->item(12, 2);
        ___qtablewidgetitem121->setText(QApplication::translate("MainWindow", "Data Processed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem122 = statsTable->item(12, 3);
        ___qtablewidgetitem122->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem123 = statsTable->item(13, 2);
        ___qtablewidgetitem123->setText(QApplication::translate("MainWindow", "Send Succeded", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem124 = statsTable->item(13, 3);
        ___qtablewidgetitem124->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem125 = statsTable->item(14, 2);
        ___qtablewidgetitem125->setText(QApplication::translate("MainWindow", "Send Failed", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem126 = statsTable->item(14, 3);
        ___qtablewidgetitem126->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        statsTable->setSortingEnabled(__sortingEnabled);

        label_4->setText(QApplication::translate("MainWindow", "Q1 Usage", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Q2 Usage", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Q3 Usage", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Q4 Usage", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Q5 Usage", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Q6 Usage", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Q7 Usage", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Q8 Usage", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(statTab), QApplication::translate("MainWindow", "Statistics and Logs", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
