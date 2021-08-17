/****************************************************************************
** Meta object code from reading C++ file 'column_editor_frame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../column_editor_frame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'column_editor_frame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ColumnEditorFrame_t {
    QByteArrayData data[11];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ColumnEditorFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ColumnEditorFrame_t qt_meta_stringdata_ColumnEditorFrame = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ColumnEditorFrame"
QT_MOC_LITERAL(1, 18, 12), // "columnEdited"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 25), // "on_typeComboBox_activated"
QT_MOC_LITERAL(4, 58, 5), // "index"
QT_MOC_LITERAL(5, 64, 32), // "on_fieldsNameLineEdit_textEdited"
QT_MOC_LITERAL(6, 97, 6), // "fields"
QT_MOC_LITERAL(7, 104, 32), // "on_occurrenceLineEdit_textEdited"
QT_MOC_LITERAL(8, 137, 10), // "occurrence"
QT_MOC_LITERAL(9, 148, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(10, 170, 21) // "on_buttonBox_accepted"

    },
    "ColumnEditorFrame\0columnEdited\0\0"
    "on_typeComboBox_activated\0index\0"
    "on_fieldsNameLineEdit_textEdited\0"
    "fields\0on_occurrenceLineEdit_textEdited\0"
    "occurrence\0on_buttonBox_rejected\0"
    "on_buttonBox_accepted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ColumnEditorFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x08 /* Private */,
       5,    1,   48,    2, 0x08 /* Private */,
       7,    1,   51,    2, 0x08 /* Private */,
       9,    0,   54,    2, 0x08 /* Private */,
      10,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ColumnEditorFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ColumnEditorFrame *_t = static_cast<ColumnEditorFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->columnEdited(); break;
        case 1: _t->on_typeComboBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_fieldsNameLineEdit_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_occurrenceLineEdit_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_buttonBox_rejected(); break;
        case 5: _t->on_buttonBox_accepted(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ColumnEditorFrame::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColumnEditorFrame::columnEdited)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ColumnEditorFrame::staticMetaObject = {
    { &AccordionFrame::staticMetaObject, qt_meta_stringdata_ColumnEditorFrame.data,
      qt_meta_data_ColumnEditorFrame,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ColumnEditorFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ColumnEditorFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ColumnEditorFrame.stringdata0))
        return static_cast<void*>(this);
    return AccordionFrame::qt_metacast(_clname);
}

int ColumnEditorFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AccordionFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ColumnEditorFrame::columnEdited()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
