/****************************************************************************
** Meta object code from reading C++ file 'filter_action.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../filter_action.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filter_action.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FilterAction_t {
    QByteArrayData data[19];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FilterAction_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FilterAction_t qt_meta_stringdata_FilterAction = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FilterAction"
QT_MOC_LITERAL(1, 13, 14), // "groupTriggered"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "QAction*"
QT_MOC_LITERAL(4, 38, 19), // "copyActionTriggered"
QT_MOC_LITERAL(5, 58, 6), // "Action"
QT_MOC_LITERAL(6, 65, 11), // "ActionApply"
QT_MOC_LITERAL(7, 77, 14), // "ActionColorize"
QT_MOC_LITERAL(8, 92, 10), // "ActionCopy"
QT_MOC_LITERAL(9, 103, 10), // "ActionFind"
QT_MOC_LITERAL(10, 114, 13), // "ActionPrepare"
QT_MOC_LITERAL(11, 128, 15), // "ActionWebLookup"
QT_MOC_LITERAL(12, 144, 10), // "ActionType"
QT_MOC_LITERAL(13, 155, 15), // "ActionTypePlain"
QT_MOC_LITERAL(14, 171, 13), // "ActionTypeNot"
QT_MOC_LITERAL(15, 185, 13), // "ActionTypeAnd"
QT_MOC_LITERAL(16, 199, 12), // "ActionTypeOr"
QT_MOC_LITERAL(17, 212, 16), // "ActionTypeAndNot"
QT_MOC_LITERAL(18, 229, 15) // "ActionTypeOrNot"

    },
    "FilterAction\0groupTriggered\0\0QAction*\0"
    "copyActionTriggered\0Action\0ActionApply\0"
    "ActionColorize\0ActionCopy\0ActionFind\0"
    "ActionPrepare\0ActionWebLookup\0ActionType\0"
    "ActionTypePlain\0ActionTypeNot\0"
    "ActionTypeAnd\0ActionTypeOr\0ActionTypeAndNot\0"
    "ActionTypeOrNot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FilterAction[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       2,   28, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       4,    0,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // enums: name, flags, count, data
       5, 0x0,    6,   36,
      12, 0x0,    6,   48,

 // enum data: key, value
       6, uint(FilterAction::ActionApply),
       7, uint(FilterAction::ActionColorize),
       8, uint(FilterAction::ActionCopy),
       9, uint(FilterAction::ActionFind),
      10, uint(FilterAction::ActionPrepare),
      11, uint(FilterAction::ActionWebLookup),
      13, uint(FilterAction::ActionTypePlain),
      14, uint(FilterAction::ActionTypeNot),
      15, uint(FilterAction::ActionTypeAnd),
      16, uint(FilterAction::ActionTypeOr),
      17, uint(FilterAction::ActionTypeAndNot),
      18, uint(FilterAction::ActionTypeOrNot),

       0        // eod
};

void FilterAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FilterAction *_t = static_cast<FilterAction *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->groupTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->copyActionTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject FilterAction::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_FilterAction.data,
      qt_meta_data_FilterAction,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FilterAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FilterAction::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FilterAction.stringdata0))
        return static_cast<void*>(this);
    return QAction::qt_metacast(_clname);
}

int FilterAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
