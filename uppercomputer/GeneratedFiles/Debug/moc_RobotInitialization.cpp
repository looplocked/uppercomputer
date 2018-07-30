/****************************************************************************
** Meta object code from reading C++ file 'RobotInitialization.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RobotInitialization.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RobotInitialization.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RobotInitialization_t {
    QByteArrayData data[13];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RobotInitialization_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RobotInitialization_t qt_meta_stringdata_RobotInitialization = {
    {
QT_MOC_LITERAL(0, 0, 19), // "RobotInitialization"
QT_MOC_LITERAL(1, 20, 9), // "initReady"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "Mat"
QT_MOC_LITERAL(4, 35, 9), // "initjacob"
QT_MOC_LITERAL(5, 45, 8), // "initpose"
QT_MOC_LITERAL(6, 54, 7), // "feature"
QT_MOC_LITERAL(7, 62, 11), // "giventarget"
QT_MOC_LITERAL(8, 74, 10), // "getFeature"
QT_MOC_LITERAL(9, 85, 12), // "moveNextStep"
QT_MOC_LITERAL(10, 98, 15), // "startInitialize"
QT_MOC_LITERAL(11, 114, 13), // "moveAndRecord"
QT_MOC_LITERAL(12, 128, 14) // "extractFeature"

    },
    "RobotInitialization\0initReady\0\0Mat\0"
    "initjacob\0initpose\0feature\0giventarget\0"
    "getFeature\0moveNextStep\0startInitialize\0"
    "moveAndRecord\0extractFeature"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RobotInitialization[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   44,    2, 0x06 /* Public */,
       8,    0,   53,    2, 0x06 /* Public */,
       9,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   55,    2, 0x0a /* Public */,
      11,    0,   56,    2, 0x0a /* Public */,
      12,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RobotInitialization::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RobotInitialization *_t = static_cast<RobotInitialization *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initReady((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< Mat(*)>(_a[3])),(*reinterpret_cast< Mat(*)>(_a[4]))); break;
        case 1: _t->getFeature(); break;
        case 2: _t->moveNextStep(); break;
        case 3: _t->startInitialize(); break;
        case 4: _t->moveAndRecord(); break;
        case 5: _t->extractFeature(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RobotInitialization::*_t)(Mat , Mat , Mat , Mat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotInitialization::initReady)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RobotInitialization::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotInitialization::getFeature)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (RobotInitialization::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotInitialization::moveNextStep)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject RobotInitialization::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RobotInitialization.data,
      qt_meta_data_RobotInitialization,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RobotInitialization::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RobotInitialization::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RobotInitialization.stringdata0))
        return static_cast<void*>(const_cast< RobotInitialization*>(this));
    return QObject::qt_metacast(_clname);
}

int RobotInitialization::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void RobotInitialization::initReady(Mat _t1, Mat _t2, Mat _t3, Mat _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RobotInitialization::getFeature()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void RobotInitialization::moveNextStep()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
