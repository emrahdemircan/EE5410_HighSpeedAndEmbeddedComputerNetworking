/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Jan 27 13:06:42 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   30,   11,   11, 0x08,
      87,   30,   11,   11, 0x08,
     141,   30,   11,   11, 0x08,
     195,   30,   11,   11, 0x08,
     241,   11,   11,   11, 0x08,
     268,   11,   11,   11, 0x08,
     296,   12,   11,   11, 0x0a,
     313,   11,   11,   11, 0x0a,
     324,   11,   11,   11, 0x0a,
     346,  336,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0qStr\0log(QString)\0index\0"
    "on_egressLinkRateComboBox_currentIndexChanged(int)\0"
    "on_queueLengthSelectComboBox_currentIndexChanged(int)\0"
    "on_backlogTimeSelectComboBox_currentIndexChanged(int)\0"
    "on_schSelectComboBox_currentIndexChanged(int)\0"
    "on_sysStopButton_clicked()\0"
    "on_sysStartButton_clicked()\0"
    "showLog(QString)\0reqStats()\0showStats()\0"
    "isStarted\0setKernelModuleState(unsigned short)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: log((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: on_egressLinkRateComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_queueLengthSelectComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_backlogTimeSelectComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: on_schSelectComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_sysStopButton_clicked(); break;
        case 6: on_sysStartButton_clicked(); break;
        case 7: showLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: reqStats(); break;
        case 9: showStats(); break;
        case 10: setKernelModuleState((*reinterpret_cast< unsigned short(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::log(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_SkNlThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x05,
      30,   11,   11,   11, 0x05,
      52,   42,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SkNlThread[] = {
    "SkNlThread\0\0qStr\0log(QString)\0showStats()\0"
    "isStarted\0setKernelModuleState(unsigned short)\0"
};

const QMetaObject SkNlThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SkNlThread,
      qt_meta_data_SkNlThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkNlThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkNlThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkNlThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkNlThread))
        return static_cast<void*>(const_cast< SkNlThread*>(this));
    return QThread::qt_metacast(_clname);
}

int SkNlThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: log((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: showStats(); break;
        case 2: setKernelModuleState((*reinterpret_cast< unsigned short(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SkNlThread::log(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SkNlThread::showStats()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SkNlThread::setKernelModuleState(unsigned short _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
