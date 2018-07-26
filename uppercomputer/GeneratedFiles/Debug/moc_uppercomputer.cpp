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
    QByteArrayData data[11];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uppercomputer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uppercomputer_t qt_meta_stringdata_uppercomputer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "uppercomputer"
QT_MOC_LITERAL(1, 14, 8), // "sendPose"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "Mat"
QT_MOC_LITERAL(4, 28, 4), // "pose"
QT_MOC_LITERAL(5, 33, 11), // "sendFeature"
QT_MOC_LITERAL(6, 45, 7), // "feature"
QT_MOC_LITERAL(7, 53, 10), // "startTimer"
QT_MOC_LITERAL(8, 64, 13), // "displayCamera"
QT_MOC_LITERAL(9, 78, 11), // "displayPose"
QT_MOC_LITERAL(10, 90, 11) // "receivePose"

    },
    "uppercomputer\0sendPose\0\0Mat\0pose\0"
    "sendFeature\0feature\0startTimer\0"
    "displayCamera\0displayPose\0receivePose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uppercomputer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,
       9,    0,   52,    2, 0x0a /* Public */,
      10,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,

 // slots: parameters
    QMetaType::Void,
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
        case 0: _t->sendPose((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 1: _t->sendFeature((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 2: _t->startTimer(); break;
        case 3: _t->displayCamera(); break;
        case 4: _t->displayPose(); break;
        case 5: _t->receivePose((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (uppercomputer::*_t)(Mat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&uppercomputer::sendPose)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (uppercomputer::*_t)(Mat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&uppercomputer::sendFeature)) {
                *result = 1;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void uppercomputer::sendPose(Mat _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void uppercomputer::sendFeature(Mat _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
