/****************************************************************************
** Meta object code from reading C++ file 'export_object_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../export_object_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'export_object_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExportObjectDialog_t {
    QByteArrayData data[20];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExportObjectDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExportObjectDialog_t qt_meta_stringdata_ExportObjectDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ExportObjectDialog"
QT_MOC_LITERAL(1, 19, 4), // "show"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "accept"
QT_MOC_LITERAL(4, 32, 12), // "captureEvent"
QT_MOC_LITERAL(5, 45, 12), // "CaptureEvent"
QT_MOC_LITERAL(6, 58, 1), // "e"
QT_MOC_LITERAL(7, 60, 26), // "on_buttonBox_helpRequested"
QT_MOC_LITERAL(8, 87, 20), // "on_buttonBox_clicked"
QT_MOC_LITERAL(9, 108, 16), // "QAbstractButton*"
QT_MOC_LITERAL(10, 125, 6), // "button"
QT_MOC_LITERAL(11, 132, 37), // "on_cmbContentType_currentInde..."
QT_MOC_LITERAL(12, 170, 5), // "index"
QT_MOC_LITERAL(13, 176, 16), // "modelDataChanged"
QT_MOC_LITERAL(14, 193, 7), // "topLeft"
QT_MOC_LITERAL(15, 201, 4), // "from"
QT_MOC_LITERAL(16, 206, 2), // "to"
QT_MOC_LITERAL(17, 209, 14), // "modelRowsReset"
QT_MOC_LITERAL(18, 224, 17), // "currentHasChanged"
QT_MOC_LITERAL(19, 242, 7) // "current"

    },
    "ExportObjectDialog\0show\0\0accept\0"
    "captureEvent\0CaptureEvent\0e\0"
    "on_buttonBox_helpRequested\0"
    "on_buttonBox_clicked\0QAbstractButton*\0"
    "button\0on_cmbContentType_currentIndexChanged\0"
    "index\0modelDataChanged\0topLeft\0from\0"
    "to\0modelRowsReset\0currentHasChanged\0"
    "current"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExportObjectDialog[] = {

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
       3,    0,   60,    2, 0x08 /* Private */,
       4,    1,   61,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    1,   65,    2, 0x08 /* Private */,
      11,    1,   68,    2, 0x08 /* Private */,
      13,    3,   71,    2, 0x08 /* Private */,
      17,    0,   78,    2, 0x08 /* Private */,
      18,    1,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,   14,   15,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   19,

       0        // eod
};

void ExportObjectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ExportObjectDialog *_t = static_cast<ExportObjectDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->show(); break;
        case 1: _t->accept(); break;
        case 2: _t->captureEvent((*reinterpret_cast< CaptureEvent(*)>(_a[1]))); break;
        case 3: _t->on_buttonBox_helpRequested(); break;
        case 4: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 5: _t->on_cmbContentType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->modelDataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->modelRowsReset(); break;
        case 8: _t->currentHasChanged((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ExportObjectDialog::staticMetaObject = {
    { &WiresharkDialog::staticMetaObject, qt_meta_stringdata_ExportObjectDialog.data,
      qt_meta_data_ExportObjectDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ExportObjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExportObjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExportObjectDialog.stringdata0))
        return static_cast<void*>(this);
    return WiresharkDialog::qt_metacast(_clname);
}

int ExportObjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WiresharkDialog::qt_metacall(_c, _id, _a);
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
