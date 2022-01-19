/****************************************************************************
** Meta object code from reading C++ file 'packet_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../packet_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packet_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PacketDialog_t {
    QByteArrayData data[13];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PacketDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PacketDialog_t qt_meta_stringdata_PacketDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PacketDialog"
QT_MOC_LITERAL(1, 13, 23), // "showProtocolPreferences"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 11), // "module_name"
QT_MOC_LITERAL(4, 50, 22), // "editProtocolPreference"
QT_MOC_LITERAL(5, 73, 11), // "preference*"
QT_MOC_LITERAL(6, 85, 4), // "pref"
QT_MOC_LITERAL(7, 90, 12), // "pref_module*"
QT_MOC_LITERAL(8, 103, 6), // "module"
QT_MOC_LITERAL(9, 110, 26), // "on_buttonBox_helpRequested"
QT_MOC_LITERAL(10, 137, 18), // "captureFileClosing"
QT_MOC_LITERAL(11, 156, 11), // "setHintText"
QT_MOC_LITERAL(12, 168, 17) // "FieldInformation*"

    },
    "PacketDialog\0showProtocolPreferences\0"
    "\0module_name\0editProtocolPreference\0"
    "preference*\0pref\0pref_module*\0module\0"
    "on_buttonBox_helpRequested\0"
    "captureFileClosing\0setHintText\0"
    "FieldInformation*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PacketDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    2,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   47,    2, 0x08 /* Private */,
      10,    0,   48,    2, 0x08 /* Private */,
      11,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,

       0        // eod
};

void PacketDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PacketDialog *_t = static_cast<PacketDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showProtocolPreferences((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->editProtocolPreference((*reinterpret_cast< preference*(*)>(_a[1])),(*reinterpret_cast< pref_module*(*)>(_a[2]))); break;
        case 2: _t->on_buttonBox_helpRequested(); break;
        case 3: _t->captureFileClosing(); break;
        case 4: _t->setHintText((*reinterpret_cast< FieldInformation*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FieldInformation* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PacketDialog::*_t)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketDialog::showProtocolPreferences)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PacketDialog::*_t)(preference * , pref_module * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketDialog::editProtocolPreference)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PacketDialog::staticMetaObject = {
    { &WiresharkDialog::staticMetaObject, qt_meta_stringdata_PacketDialog.data,
      qt_meta_data_PacketDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PacketDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PacketDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PacketDialog.stringdata0))
        return static_cast<void*>(this);
    return WiresharkDialog::qt_metacast(_clname);
}

int PacketDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WiresharkDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PacketDialog::showProtocolPreferences(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PacketDialog::editProtocolPreference(preference * _t1, pref_module * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
