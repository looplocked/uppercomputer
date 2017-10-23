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
    QByteArrayData data[18];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uppercomputer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uppercomputer_t qt_meta_stringdata_uppercomputer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "uppercomputer"
QT_MOC_LITERAL(1, 14, 15), // "startImageTimer"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "showImage"
QT_MOC_LITERAL(4, 41, 3), // "Mat"
QT_MOC_LITERAL(5, 45, 9), // "originimg"
QT_MOC_LITERAL(6, 55, 10), // "featureimg"
QT_MOC_LITERAL(7, 66, 8), // "closeCam"
QT_MOC_LITERAL(8, 75, 17), // "startFeatureTimer"
QT_MOC_LITERAL(9, 93, 10), // "disFeature"
QT_MOC_LITERAL(10, 104, 8), // "featurex"
QT_MOC_LITERAL(11, 113, 8), // "featurey"
QT_MOC_LITERAL(12, 122, 11), // "featurearea"
QT_MOC_LITERAL(13, 134, 10), // "featureang"
QT_MOC_LITERAL(14, 145, 12), // "closeFeature"
QT_MOC_LITERAL(15, 158, 14), // "startPoseTimer"
QT_MOC_LITERAL(16, 173, 11), // "readyToRead"
QT_MOC_LITERAL(17, 185, 14) // "socketReadData"

    },
    "uppercomputer\0startImageTimer\0\0showImage\0"
    "Mat\0originimg\0featureimg\0closeCam\0"
    "startFeatureTimer\0disFeature\0featurex\0"
    "featurey\0featurearea\0featureang\0"
    "closeFeature\0startPoseTimer\0readyToRead\0"
    "socketReadData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uppercomputer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    2,   60,    2, 0x0a /* Public */,
       7,    0,   65,    2, 0x0a /* Public */,
       8,    0,   66,    2, 0x0a /* Public */,
       9,    4,   67,    2, 0x0a /* Public */,
      14,    0,   76,    2, 0x0a /* Public */,
      15,    0,   77,    2, 0x0a /* Public */,
      16,    0,   78,    2, 0x0a /* Public */,
      17,    0,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   10,   11,   12,   13,
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
        case 0: _t->startImageTimer(); break;
        case 1: _t->showImage((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        case 2: _t->closeCam(); break;
        case 3: _t->startFeatureTimer(); break;
        case 4: _t->disFeature((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 5: _t->closeFeature(); break;
        case 6: _t->startPoseTimer(); break;
        case 7: _t->readyToRead(); break;
        case 8: _t->socketReadData(); break;
        default: ;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
