/****************************************************************************
** Meta object code from reading C++ file 'funnel_statistics.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../funnel_statistics.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'funnel_statistics.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FunnelStatistics_t {
    QByteArrayData data[12];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FunnelStatistics_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FunnelStatistics_t qt_meta_stringdata_FunnelStatistics = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FunnelStatistics"
QT_MOC_LITERAL(1, 17, 15), // "openCaptureFile"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "cf_path"
QT_MOC_LITERAL(4, 42, 6), // "filter"
QT_MOC_LITERAL(5, 49, 16), // "setDisplayFilter"
QT_MOC_LITERAL(6, 66, 20), // "FilterAction::Action"
QT_MOC_LITERAL(7, 87, 6), // "action"
QT_MOC_LITERAL(8, 94, 24), // "FilterAction::ActionType"
QT_MOC_LITERAL(9, 119, 10), // "filterType"
QT_MOC_LITERAL(10, 130, 21), // "funnelActionTriggered"
QT_MOC_LITERAL(11, 152, 24) // "displayFilterTextChanged"

    },
    "FunnelStatistics\0openCaptureFile\0\0"
    "cf_path\0filter\0setDisplayFilter\0"
    "FilterAction::Action\0action\0"
    "FilterAction::ActionType\0filterType\0"
    "funnelActionTriggered\0displayFilterTextChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FunnelStatistics[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    3,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   46,    2, 0x0a /* Public */,
      11,    1,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 6, 0x80000000 | 8,    4,    7,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void FunnelStatistics::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FunnelStatistics *_t = static_cast<FunnelStatistics *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openCaptureFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->setDisplayFilter((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< FilterAction::Action(*)>(_a[2])),(*reinterpret_cast< FilterAction::ActionType(*)>(_a[3]))); break;
        case 2: _t->funnelActionTriggered(); break;
        case 3: _t->displayFilterTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (FunnelStatistics::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FunnelStatistics::openCaptureFile)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FunnelStatistics::*_t)(QString , FilterAction::Action , FilterAction::ActionType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FunnelStatistics::setDisplayFilter)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject FunnelStatistics::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FunnelStatistics.data,
      qt_meta_data_FunnelStatistics,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FunnelStatistics::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FunnelStatistics::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FunnelStatistics.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FunnelStatistics::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void FunnelStatistics::openCaptureFile(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FunnelStatistics::setDisplayFilter(QString _t1, FilterAction::Action _t2, FilterAction::ActionType _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
