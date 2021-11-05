/****************************************************************************
** Meta object code from reading C++ file 'extcap_argument_multiselect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../extcap_argument_multiselect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extcap_argument_multiselect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExtArgMultiSelect_t {
    QByteArrayData data[4];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExtArgMultiSelect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExtArgMultiSelect_t qt_meta_stringdata_ExtArgMultiSelect = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ExtArgMultiSelect"
QT_MOC_LITERAL(1, 18, 11), // "itemChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14) // "QStandardItem*"

    },
    "ExtArgMultiSelect\0itemChanged\0\0"
    "QStandardItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExtArgMultiSelect[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void ExtArgMultiSelect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ExtArgMultiSelect *_t = static_cast<ExtArgMultiSelect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ExtArgMultiSelect::staticMetaObject = {
    { &ExtcapArgument::staticMetaObject, qt_meta_stringdata_ExtArgMultiSelect.data,
      qt_meta_data_ExtArgMultiSelect,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ExtArgMultiSelect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExtArgMultiSelect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExtArgMultiSelect.stringdata0))
        return static_cast<void*>(this);
    return ExtcapArgument::qt_metacast(_clname);
}

int ExtArgMultiSelect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ExtcapArgument::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
