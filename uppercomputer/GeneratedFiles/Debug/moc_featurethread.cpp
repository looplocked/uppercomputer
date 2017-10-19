/****************************************************************************
** Meta object code from reading C++ file 'featurethread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../featurethread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'featurethread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FeatureThread_t {
    QByteArrayData data[8];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FeatureThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FeatureThread_t qt_meta_stringdata_FeatureThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FeatureThread"
QT_MOC_LITERAL(1, 14, 11), // "gotAFeature"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "featureX"
QT_MOC_LITERAL(4, 36, 8), // "featureY"
QT_MOC_LITERAL(5, 45, 11), // "featurearea"
QT_MOC_LITERAL(6, 57, 10), // "featureang"
QT_MOC_LITERAL(7, 68, 10) // "getFeature"

    },
    "FeatureThread\0gotAFeature\0\0featureX\0"
    "featureY\0featurearea\0featureang\0"
    "getFeature"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FeatureThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void FeatureThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FeatureThread *_t = static_cast<FeatureThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gotAFeature((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 1: _t->getFeature(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FeatureThread::*_t)(double , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FeatureThread::gotAFeature)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FeatureThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FeatureThread.data,
      qt_meta_data_FeatureThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FeatureThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FeatureThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FeatureThread.stringdata0))
        return static_cast<void*>(const_cast< FeatureThread*>(this));
    return QThread::qt_metacast(_clname);
}

int FeatureThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FeatureThread::gotAFeature(double _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
