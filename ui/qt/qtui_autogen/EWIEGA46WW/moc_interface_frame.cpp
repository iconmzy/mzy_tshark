/****************************************************************************
** Meta object code from reading C++ file 'interface_frame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../interface_frame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interface_frame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InterfaceFrame_t {
    QByteArrayData data[30];
    char stringdata0[463];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InterfaceFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InterfaceFrame_t qt_meta_stringdata_InterfaceFrame = {
    {
QT_MOC_LITERAL(0, 0, 14), // "InterfaceFrame"
QT_MOC_LITERAL(1, 15, 17), // "showExtcapOptions"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "device_name"
QT_MOC_LITERAL(4, 46, 12), // "startCapture"
QT_MOC_LITERAL(5, 59, 20), // "itemSelectionChanged"
QT_MOC_LITERAL(6, 80, 20), // "typeSelectionChanged"
QT_MOC_LITERAL(7, 101, 24), // "updateSelectedInterfaces"
QT_MOC_LITERAL(8, 126, 20), // "interfaceListChanged"
QT_MOC_LITERAL(9, 147, 22), // "toggleHiddenInterfaces"
QT_MOC_LITERAL(10, 170, 9), // "getPoints"
QT_MOC_LITERAL(11, 180, 3), // "idx"
QT_MOC_LITERAL(12, 184, 10), // "PointList*"
QT_MOC_LITERAL(13, 195, 3), // "pts"
QT_MOC_LITERAL(14, 199, 13), // "showRunOnFile"
QT_MOC_LITERAL(15, 213, 15), // "showContextMenu"
QT_MOC_LITERAL(16, 229, 3), // "pos"
QT_MOC_LITERAL(17, 233, 29), // "interfaceTreeSelectionChanged"
QT_MOC_LITERAL(18, 263, 14), // "QItemSelection"
QT_MOC_LITERAL(19, 278, 8), // "selected"
QT_MOC_LITERAL(20, 287, 10), // "deselected"
QT_MOC_LITERAL(21, 298, 30), // "on_interfaceTree_doubleClicked"
QT_MOC_LITERAL(22, 329, 5), // "index"
QT_MOC_LITERAL(23, 335, 24), // "on_interfaceTree_clicked"
QT_MOC_LITERAL(24, 360, 16), // "updateStatistics"
QT_MOC_LITERAL(25, 377, 20), // "actionButton_toggled"
QT_MOC_LITERAL(26, 398, 7), // "checked"
QT_MOC_LITERAL(27, 406, 21), // "triggeredIfTypeButton"
QT_MOC_LITERAL(28, 428, 29), // "on_warningLabel_linkActivated"
QT_MOC_LITERAL(29, 458, 4) // "link"

    },
    "InterfaceFrame\0showExtcapOptions\0\0"
    "device_name\0startCapture\0itemSelectionChanged\0"
    "typeSelectionChanged\0updateSelectedInterfaces\0"
    "interfaceListChanged\0toggleHiddenInterfaces\0"
    "getPoints\0idx\0PointList*\0pts\0showRunOnFile\0"
    "showContextMenu\0pos\0interfaceTreeSelectionChanged\0"
    "QItemSelection\0selected\0deselected\0"
    "on_interfaceTree_doubleClicked\0index\0"
    "on_interfaceTree_clicked\0updateStatistics\0"
    "actionButton_toggled\0checked\0"
    "triggeredIfTypeButton\0"
    "on_warningLabel_linkActivated\0link"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InterfaceFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    0,  102,    2, 0x06 /* Public */,
       5,    0,  103,    2, 0x06 /* Public */,
       6,    0,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  105,    2, 0x0a /* Public */,
       8,    0,  106,    2, 0x0a /* Public */,
       9,    0,  107,    2, 0x0a /* Public */,
      10,    2,  108,    2, 0x0a /* Public */,
      14,    0,  113,    2, 0x0a /* Public */,
      15,    1,  114,    2, 0x0a /* Public */,
      17,    2,  117,    2, 0x08 /* Private */,
      21,    1,  122,    2, 0x08 /* Private */,
      23,    1,  125,    2, 0x08 /* Private */,
      24,    0,  128,    2, 0x08 /* Private */,
      25,    1,  129,    2, 0x08 /* Private */,
      27,    0,  132,    2, 0x08 /* Private */,
      28,    1,  133,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,   11,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   16,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 18,   19,   20,
    QMetaType::Void, QMetaType::QModelIndex,   22,
    QMetaType::Void, QMetaType::QModelIndex,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,

       0        // eod
};

void InterfaceFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InterfaceFrame *_t = static_cast<InterfaceFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showExtcapOptions((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->startCapture(); break;
        case 2: _t->itemSelectionChanged(); break;
        case 3: _t->typeSelectionChanged(); break;
        case 4: _t->updateSelectedInterfaces(); break;
        case 5: _t->interfaceListChanged(); break;
        case 6: _t->toggleHiddenInterfaces(); break;
        case 7: _t->getPoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< PointList*(*)>(_a[2]))); break;
        case 8: _t->showRunOnFile(); break;
        case 9: _t->showContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 10: _t->interfaceTreeSelectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 11: _t->on_interfaceTree_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 12: _t->on_interfaceTree_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->updateStatistics(); break;
        case 14: _t->actionButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->triggeredIfTypeButton(); break;
        case 16: _t->on_warningLabel_linkActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (InterfaceFrame::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InterfaceFrame::showExtcapOptions)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (InterfaceFrame::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InterfaceFrame::startCapture)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (InterfaceFrame::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InterfaceFrame::itemSelectionChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (InterfaceFrame::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InterfaceFrame::typeSelectionChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject InterfaceFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_InterfaceFrame.data,
      qt_meta_data_InterfaceFrame,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *InterfaceFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceFrame.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int InterfaceFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void InterfaceFrame::showExtcapOptions(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InterfaceFrame::startCapture()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void InterfaceFrame::itemSelectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void InterfaceFrame::typeSelectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
