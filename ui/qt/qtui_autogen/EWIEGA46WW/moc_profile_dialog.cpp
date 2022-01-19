/****************************************************************************
** Meta object code from reading C++ file 'profile_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../profile_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'profile_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProfileDialog_t {
    QByteArrayData data[20];
    char stringdata0[339];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProfileDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProfileDialog_t qt_meta_stringdata_ProfileDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ProfileDialog"
QT_MOC_LITERAL(1, 14, 18), // "currentItemChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 1), // "c"
QT_MOC_LITERAL(4, 36, 1), // "p"
QT_MOC_LITERAL(5, 38, 14), // "exportProfiles"
QT_MOC_LITERAL(6, 53, 25), // "exportAllPersonalProfiles"
QT_MOC_LITERAL(7, 79, 13), // "importFromZip"
QT_MOC_LITERAL(8, 93, 19), // "importFromDirectory"
QT_MOC_LITERAL(9, 113, 24), // "on_newToolButton_clicked"
QT_MOC_LITERAL(10, 138, 27), // "on_deleteToolButton_clicked"
QT_MOC_LITERAL(11, 166, 25), // "on_copyToolButton_clicked"
QT_MOC_LITERAL(12, 192, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(13, 214, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(14, 236, 26), // "on_buttonBox_helpRequested"
QT_MOC_LITERAL(15, 263, 11), // "dataChanged"
QT_MOC_LITERAL(16, 275, 13), // "filterChanged"
QT_MOC_LITERAL(17, 289, 16), // "selectionChanged"
QT_MOC_LITERAL(18, 306, 16), // "selectedProfiles"
QT_MOC_LITERAL(19, 323, 15) // "QModelIndexList"

    },
    "ProfileDialog\0currentItemChanged\0\0c\0"
    "p\0exportProfiles\0exportAllPersonalProfiles\0"
    "importFromZip\0importFromDirectory\0"
    "on_newToolButton_clicked\0"
    "on_deleteToolButton_clicked\0"
    "on_copyToolButton_clicked\0"
    "on_buttonBox_accepted\0on_buttonBox_rejected\0"
    "on_buttonBox_helpRequested\0dataChanged\0"
    "filterChanged\0selectionChanged\0"
    "selectedProfiles\0QModelIndexList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProfileDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x08 /* Private */,
       1,    1,  104,    2, 0x28 /* Private | MethodCloned */,
       1,    0,  107,    2, 0x28 /* Private | MethodCloned */,
       5,    1,  108,    2, 0x08 /* Private */,
       5,    0,  111,    2, 0x28 /* Private | MethodCloned */,
       7,    0,  112,    2, 0x08 /* Private */,
       8,    0,  113,    2, 0x08 /* Private */,
       9,    0,  114,    2, 0x08 /* Private */,
      10,    0,  115,    2, 0x08 /* Private */,
      11,    0,  116,    2, 0x08 /* Private */,
      12,    0,  117,    2, 0x08 /* Private */,
      13,    0,  118,    2, 0x08 /* Private */,
      14,    0,  119,    2, 0x08 /* Private */,
      15,    1,  120,    2, 0x08 /* Private */,
      16,    1,  123,    2, 0x08 /* Private */,
      17,    0,  126,    2, 0x08 /* Private */,
      18,    0,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::QModelIndex,    3,    4,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    0x80000000 | 19,

       0        // eod
};

void ProfileDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProfileDialog *_t = static_cast<ProfileDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentItemChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 1: _t->currentItemChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->currentItemChanged(); break;
        case 3: _t->exportProfiles((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->exportProfiles(); break;
        case 5: _t->importFromZip(); break;
        case 6: _t->importFromDirectory(); break;
        case 7: _t->on_newToolButton_clicked(); break;
        case 8: _t->on_deleteToolButton_clicked(); break;
        case 9: _t->on_copyToolButton_clicked(); break;
        case 10: _t->on_buttonBox_accepted(); break;
        case 11: _t->on_buttonBox_rejected(); break;
        case 12: _t->on_buttonBox_helpRequested(); break;
        case 13: _t->dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 14: _t->filterChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->selectionChanged(); break;
        case 16: { QModelIndexList _r = _t->selectedProfiles();
            if (_a[0]) *reinterpret_cast< QModelIndexList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject ProfileDialog::staticMetaObject = {
    { &GeometryStateDialog::staticMetaObject, qt_meta_stringdata_ProfileDialog.data,
      qt_meta_data_ProfileDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ProfileDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProfileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProfileDialog.stringdata0))
        return static_cast<void*>(this);
    return GeometryStateDialog::qt_metacast(_clname);
}

int ProfileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GeometryStateDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
