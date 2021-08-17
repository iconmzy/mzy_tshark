/****************************************************************************
** Meta object code from reading C++ file 'voip_calls_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../voip_calls_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'voip_calls_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VoipCallsDialog_t {
    QByteArrayData data[25];
    char stringdata0[311];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VoipCallsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VoipCallsDialog_t qt_meta_stringdata_VoipCallsDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VoipCallsDialog"
QT_MOC_LITERAL(1, 16, 12), // "updateFilter"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 6), // "filter"
QT_MOC_LITERAL(4, 37, 5), // "force"
QT_MOC_LITERAL(5, 43, 18), // "captureFileChanged"
QT_MOC_LITERAL(6, 62, 13), // "capture_file*"
QT_MOC_LITERAL(7, 76, 2), // "cf"
QT_MOC_LITERAL(8, 79, 10), // "goToPacket"
QT_MOC_LITERAL(9, 90, 10), // "packet_num"
QT_MOC_LITERAL(10, 101, 11), // "changeEvent"
QT_MOC_LITERAL(11, 113, 7), // "QEvent*"
QT_MOC_LITERAL(12, 121, 5), // "event"
QT_MOC_LITERAL(13, 127, 18), // "captureFileClosing"
QT_MOC_LITERAL(14, 146, 9), // "selectAll"
QT_MOC_LITERAL(15, 156, 9), // "copyAsCSV"
QT_MOC_LITERAL(16, 166, 10), // "copyAsYAML"
QT_MOC_LITERAL(17, 177, 15), // "switchTimeOfDay"
QT_MOC_LITERAL(18, 193, 25), // "on_callTreeView_activated"
QT_MOC_LITERAL(19, 219, 5), // "index"
QT_MOC_LITERAL(20, 225, 20), // "on_buttonBox_clicked"
QT_MOC_LITERAL(21, 246, 16), // "QAbstractButton*"
QT_MOC_LITERAL(22, 263, 6), // "button"
QT_MOC_LITERAL(23, 270, 26), // "on_buttonBox_helpRequested"
QT_MOC_LITERAL(24, 297, 13) // "updateWidgets"

    },
    "VoipCallsDialog\0updateFilter\0\0filter\0"
    "force\0captureFileChanged\0capture_file*\0"
    "cf\0goToPacket\0packet_num\0changeEvent\0"
    "QEvent*\0event\0captureFileClosing\0"
    "selectAll\0copyAsCSV\0copyAsYAML\0"
    "switchTimeOfDay\0on_callTreeView_activated\0"
    "index\0on_buttonBox_clicked\0QAbstractButton*\0"
    "button\0on_buttonBox_helpRequested\0"
    "updateWidgets"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VoipCallsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,
       1,    1,   89,    2, 0x26 /* Public | MethodCloned */,
       5,    1,   92,    2, 0x06 /* Public */,
       8,    1,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   98,    2, 0x09 /* Protected */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    0,  103,    2, 0x08 /* Private */,
      16,    0,  104,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,
      18,    1,  106,    2, 0x08 /* Private */,
      20,    1,  109,    2, 0x08 /* Private */,
      23,    0,  112,    2, 0x08 /* Private */,
      24,    0,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   19,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VoipCallsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VoipCallsDialog *_t = static_cast<VoipCallsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateFilter((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->updateFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->captureFileChanged((*reinterpret_cast< capture_file*(*)>(_a[1]))); break;
        case 3: _t->goToPacket((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 5: _t->captureFileClosing(); break;
        case 6: _t->selectAll(); break;
        case 7: _t->copyAsCSV(); break;
        case 8: _t->copyAsYAML(); break;
        case 9: _t->switchTimeOfDay(); break;
        case 10: _t->on_callTreeView_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 12: _t->on_buttonBox_helpRequested(); break;
        case 13: _t->updateWidgets(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (VoipCallsDialog::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VoipCallsDialog::updateFilter)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VoipCallsDialog::*_t)(capture_file * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VoipCallsDialog::captureFileChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (VoipCallsDialog::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VoipCallsDialog::goToPacket)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject VoipCallsDialog::staticMetaObject = {
    { &WiresharkDialog::staticMetaObject, qt_meta_stringdata_VoipCallsDialog.data,
      qt_meta_data_VoipCallsDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VoipCallsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VoipCallsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VoipCallsDialog.stringdata0))
        return static_cast<void*>(this);
    return WiresharkDialog::qt_metacast(_clname);
}

int VoipCallsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WiresharkDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void VoipCallsDialog::updateFilter(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void VoipCallsDialog::captureFileChanged(capture_file * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VoipCallsDialog::goToPacket(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
