/****************************************************************************
** Meta object code from reading C++ file 'enabled_protocols_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../enabled_protocols_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'enabled_protocols_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EnabledProtocolsDialog_t {
    QByteArrayData data[11];
    char stringdata0[278];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EnabledProtocolsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EnabledProtocolsDialog_t qt_meta_stringdata_EnabledProtocolsDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "EnabledProtocolsDialog"
QT_MOC_LITERAL(1, 23, 25), // "on_invert_button__clicked"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 29), // "on_enable_all_button__clicked"
QT_MOC_LITERAL(4, 80, 30), // "on_disable_all_button__clicked"
QT_MOC_LITERAL(5, 111, 32), // "on_search_line_edit__textChanged"
QT_MOC_LITERAL(6, 144, 36), // "on_cmbSearchType_currentIndex..."
QT_MOC_LITERAL(7, 181, 38), // "on_cmbProtocolType_currentInd..."
QT_MOC_LITERAL(8, 220, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(9, 242, 26), // "on_buttonBox_helpRequested"
QT_MOC_LITERAL(10, 269, 8) // "fillTree"

    },
    "EnabledProtocolsDialog\0on_invert_button__clicked\0"
    "\0on_enable_all_button__clicked\0"
    "on_disable_all_button__clicked\0"
    "on_search_line_edit__textChanged\0"
    "on_cmbSearchType_currentIndexChanged\0"
    "on_cmbProtocolType_currentIndexChanged\0"
    "on_buttonBox_accepted\0on_buttonBox_helpRequested\0"
    "fillTree"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EnabledProtocolsDialog[] = {

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
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       6,    1,   65,    2, 0x08 /* Private */,
       7,    1,   68,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EnabledProtocolsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EnabledProtocolsDialog *_t = static_cast<EnabledProtocolsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_invert_button__clicked(); break;
        case 1: _t->on_enable_all_button__clicked(); break;
        case 2: _t->on_disable_all_button__clicked(); break;
        case 3: _t->on_search_line_edit__textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_cmbSearchType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_cmbProtocolType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_buttonBox_accepted(); break;
        case 7: _t->on_buttonBox_helpRequested(); break;
        case 8: _t->fillTree(); break;
        default: ;
        }
    }
}

const QMetaObject EnabledProtocolsDialog::staticMetaObject = {
    { &GeometryStateDialog::staticMetaObject, qt_meta_stringdata_EnabledProtocolsDialog.data,
      qt_meta_data_EnabledProtocolsDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *EnabledProtocolsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EnabledProtocolsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EnabledProtocolsDialog.stringdata0))
        return static_cast<void*>(this);
    return GeometryStateDialog::qt_metacast(_clname);
}

int EnabledProtocolsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GeometryStateDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
