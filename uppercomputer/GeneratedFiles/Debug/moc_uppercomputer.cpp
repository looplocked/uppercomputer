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
    QByteArrayData data[12];
    char stringdata0[118];
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
QT_MOC_LITERAL(3, 24, 14), // "vector<double>"
QT_MOC_LITERAL(4, 39, 4), // "pose"
QT_MOC_LITERAL(5, 44, 13), // "vector<Point>"
QT_MOC_LITERAL(6, 58, 7), // "feature"
QT_MOC_LITERAL(7, 66, 10), // "startTimer"
QT_MOC_LITERAL(8, 77, 2), // "ms"
QT_MOC_LITERAL(9, 80, 13), // "displayCamera"
QT_MOC_LITERAL(10, 94, 11), // "displayPose"
QT_MOC_LITERAL(11, 106, 11) // "receiveData"

    },
    "uppercomputer\0sendData\0\0vector<double>\0"
    "pose\0vector<Point>\0feature\0startTimer\0"
    "ms\0displayCamera\0displayPose\0receiveData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uppercomputer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   44,    2, 0x0a /* Public */,
       9,    0,   47,    2, 0x0a /* Public */,
      10,    0,   48,    2, 0x0a /* Public */,
      11,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void uppercomputer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        uppercomputer *_t = static_cast<uppercomputer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendData((*reinterpret_cast< vector<double>(*)>(_a[1])),(*reinterpret_cast< vector<Point>(*)>(_a[2]))); break;
        case 1: _t->startTimer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->displayCamera(); break;
        case 3: _t->displayPose(); break;
        case 4: _t->receiveData((*reinterpret_cast< vector<double>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (uppercomputer::*_t)(vector<double> , vector<Point> );
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void uppercomputer::sendData(vector<double> _t1, vector<Point> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
