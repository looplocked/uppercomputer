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
    QByteArrayData data[7];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uppercomputer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uppercomputer_t qt_meta_stringdata_uppercomputer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "uppercomputer"
QT_MOC_LITERAL(1, 14, 16), // "startCameraTimer"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "displayCamera"
QT_MOC_LITERAL(4, 46, 14), // "startPoseTimer"
QT_MOC_LITERAL(5, 61, 11), // "readyToRead"
QT_MOC_LITERAL(6, 73, 14) // "socketReadData"

    },
    "uppercomputer\0startCameraTimer\0\0"
    "displayCamera\0startPoseTimer\0readyToRead\0"
    "socketReadData"
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
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
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
        case 0: _t->startCameraTimer(); break;
        case 1: _t->displayCamera(); break;
        case 2: _t->startPoseTimer(); break;
        case 3: _t->readyToRead(); break;
        case 4: _t->socketReadData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
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
QT_END_MOC_NAMESPACE
