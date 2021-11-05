/****************************************************************************
** Meta object code from reading C++ file 'resolved_addresses_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../resolved_addresses_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resolved_addresses_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ResolvedAddressesDialog_t {
    QByteArrayData data[11];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ResolvedAddressesDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ResolvedAddressesDialog_t qt_meta_stringdata_ResolvedAddressesDialog = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ResolvedAddressesDialog"
QT_MOC_LITERAL(1, 24, 34), // "on_cmbDataType_currentIndexCh..."
QT_MOC_LITERAL(2, 59, 0), // ""
QT_MOC_LITERAL(3, 60, 3), // "val"
QT_MOC_LITERAL(4, 64, 30), // "on_txtSearchFilter_textChanged"
QT_MOC_LITERAL(5, 95, 4), // "text"
QT_MOC_LITERAL(6, 100, 40), // "on_cmbPortFilterType_currentI..."
QT_MOC_LITERAL(7, 141, 28), // "on_txtPortFilter_textChanged"
QT_MOC_LITERAL(8, 170, 11), // "changeEvent"
QT_MOC_LITERAL(9, 182, 7), // "QEvent*"
QT_MOC_LITERAL(10, 190, 5) // "event"

    },
    "ResolvedAddressesDialog\0"
    "on_cmbDataType_currentIndexChanged\0\0"
    "val\0on_txtSearchFilter_textChanged\0"
    "text\0on_cmbPortFilterType_currentIndexChanged\0"
    "on_txtPortFilter_textChanged\0changeEvent\0"
    "QEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ResolvedAddressesDialog[] = {

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
       1,    1,   39,    2, 0x09 /* Protected */,
       4,    1,   42,    2, 0x09 /* Protected */,
       6,    1,   45,    2, 0x09 /* Protected */,
       7,    1,   48,    2, 0x09 /* Protected */,
       8,    1,   51,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void ResolvedAddressesDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ResolvedAddressesDialog *_t = static_cast<ResolvedAddressesDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cmbDataType_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_txtSearchFilter_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_cmbPortFilterType_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_txtPortFilter_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->changeEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ResolvedAddressesDialog::staticMetaObject = {
    { &GeometryStateDialog::staticMetaObject, qt_meta_stringdata_ResolvedAddressesDialog.data,
      qt_meta_data_ResolvedAddressesDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ResolvedAddressesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ResolvedAddressesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ResolvedAddressesDialog.stringdata0))
        return static_cast<void*>(this);
    return GeometryStateDialog::qt_metacast(_clname);
}

int ResolvedAddressesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GeometryStateDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
