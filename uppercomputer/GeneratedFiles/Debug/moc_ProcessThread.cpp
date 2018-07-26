/****************************************************************************
** Meta object code from reading C++ file 'ProcessThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProcessThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProcessThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProcessThread_t {
    QByteArrayData data[14];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProcessThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProcessThread_t qt_meta_stringdata_ProcessThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ProcessThread"
QT_MOC_LITERAL(1, 14, 8), // "sendPose"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "Mat"
QT_MOC_LITERAL(4, 28, 4), // "pose"
QT_MOC_LITERAL(5, 33, 10), // "initThread"
QT_MOC_LITERAL(6, 44, 9), // "initjacob"
QT_MOC_LITERAL(7, 54, 8), // "initpose"
QT_MOC_LITERAL(8, 63, 11), // "initfeature"
QT_MOC_LITERAL(9, 75, 11), // "giventarget"
QT_MOC_LITERAL(10, 87, 11), // "receivePose"
QT_MOC_LITERAL(11, 99, 7), // "newpose"
QT_MOC_LITERAL(12, 107, 14), // "receiveFeature"
QT_MOC_LITERAL(13, 122, 10) // "newfeature"

    },
    "ProcessThread\0sendPose\0\0Mat\0pose\0"
    "initThread\0initjacob\0initpose\0initfeature\0"
    "giventarget\0receivePose\0newpose\0"
    "receiveFeature\0newfeature"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProcessThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    4,   37,    2, 0x0a /* Public */,
      10,    1,   46,    2, 0x0a /* Public */,
      12,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    6,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 3,   11,
    QMetaType::Void, 0x80000000 | 3,   13,

       0        // eod
};

void ProcessThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProcessThread *_t = static_cast<ProcessThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendPose((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 1: _t->initThread((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< Mat(*)>(_a[3])),(*reinterpret_cast< Mat(*)>(_a[4]))); break;
        case 2: _t->receivePose((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 3: _t->receiveFeature((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ProcessThread::*_t)(Mat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProcessThread::sendPose)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ProcessThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ProcessThread.data,
      qt_meta_data_ProcessThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProcessThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProcessThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessThread.stringdata0))
        return static_cast<void*>(const_cast< ProcessThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ProcessThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ProcessThread::sendPose(Mat _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
