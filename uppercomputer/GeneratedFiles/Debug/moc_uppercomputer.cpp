/****************************************************************************
** Meta object code from reading C++ file 'uppercomputer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../uppercomputer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uppercomputer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_uppercomputer_t {
    QByteArrayData data[15];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uppercomputer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uppercomputer_t qt_meta_stringdata_uppercomputer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "uppercomputer"
QT_MOC_LITERAL(1, 14, 8), // "sendData"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "vector<float>"
QT_MOC_LITERAL(4, 38, 4), // "pose"
QT_MOC_LITERAL(5, 43, 7), // "feature"
QT_MOC_LITERAL(6, 51, 16), // "startCameraTimer"
QT_MOC_LITERAL(7, 68, 13), // "displayCamera"
QT_MOC_LITERAL(8, 82, 14), // "startPoseTimer"
QT_MOC_LITERAL(9, 97, 11), // "readyToRead"
QT_MOC_LITERAL(10, 109, 14), // "socketReadData"
QT_MOC_LITERAL(11, 124, 16), // "serverNewConnect"
QT_MOC_LITERAL(12, 141, 14), // "startMoveTimer"
QT_MOC_LITERAL(13, 156, 9), // "jointMove"
QT_MOC_LITERAL(14, 166, 22) // "moveSocketDisconnected"

    },
    "uppercomputer\0sendData\0\0vector<float>\0"
    "pose\0feature\0startCameraTimer\0"
    "displayCamera\0startPoseTimer\0readyToRead\0"
    "socketReadData\0serverNewConnect\0"
    "startMoveTimer\0jointMove\0"
    "moveSocketDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uppercomputer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   69,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,
      13,    0,   76,    2, 0x0a /* Public */,
      14,    0,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void uppercomputer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        uppercomputer *_t = static_cast<uppercomputer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendData((*reinterpret_cast< vector<float>(*)>(_a[1])),(*reinterpret_cast< vector<float>(*)>(_a[2]))); break;
        case 1: _t->startCameraTimer(); break;
        case 2: _t->displayCamera(); break;
        case 3: _t->startPoseTimer(); break;
        case 4: _t->readyToRead(); break;
        case 5: _t->socketReadData(); break;
        case 6: _t->serverNewConnect(); break;
        case 7: _t->startMoveTimer(); break;
        case 8: _t->jointMove(); break;
        case 9: _t->moveSocketDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (uppercomputer::*_t)(vector<float> , vector<float> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&uppercomputer::sendData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject uppercomputer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_uppercomputer.data,
      qt_meta_data_uppercomputer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *uppercomputer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uppercomputer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_uppercomputer.stringdata0))
        return static_cast<void*>(const_cast< uppercomputer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int uppercomputer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void uppercomputer::sendData(vector<float> _t1, vector<float> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
