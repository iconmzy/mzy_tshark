/****************************************************************************
** Meta object code from reading C++ file 'packet_list_model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../models/packet_list_model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packet_list_model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PacketListModel_t {
    QByteArrayData data[17];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PacketListModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PacketListModel_t qt_meta_stringdata_PacketListModel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PacketListModel"
QT_MOC_LITERAL(1, 16, 10), // "goToPacket"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 19), // "maxLineCountChanged"
QT_MOC_LITERAL(4, 48, 8), // "ih_index"
QT_MOC_LITERAL(5, 57, 17), // "itemHeightChanged"
QT_MOC_LITERAL(6, 75, 22), // "bgColorizationProgress"
QT_MOC_LITERAL(7, 98, 5), // "first"
QT_MOC_LITERAL(8, 104, 4), // "last"
QT_MOC_LITERAL(9, 109, 4), // "sort"
QT_MOC_LITERAL(10, 114, 6), // "column"
QT_MOC_LITERAL(11, 121, 13), // "Qt::SortOrder"
QT_MOC_LITERAL(12, 135, 5), // "order"
QT_MOC_LITERAL(13, 141, 16), // "flushVisibleRows"
QT_MOC_LITERAL(14, 158, 11), // "dissectIdle"
QT_MOC_LITERAL(15, 170, 5), // "reset"
QT_MOC_LITERAL(16, 176, 21) // "emitItemHeightChanged"

    },
    "PacketListModel\0goToPacket\0\0"
    "maxLineCountChanged\0ih_index\0"
    "itemHeightChanged\0bgColorizationProgress\0"
    "first\0last\0sort\0column\0Qt::SortOrder\0"
    "order\0flushVisibleRows\0dissectIdle\0"
    "reset\0emitItemHeightChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PacketListModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       3,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,
       6,    2,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   78,    2, 0x0a /* Public */,
       9,    1,   83,    2, 0x2a /* Public | MethodCloned */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    1,   87,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x2a /* Public | MethodCloned */,
      16,    1,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   10,   12,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,

       0        // eod
};

void PacketListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PacketListModel *_t = static_cast<PacketListModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->goToPacket((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->maxLineCountChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->itemHeightChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->bgColorizationProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sort((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Qt::SortOrder(*)>(_a[2]))); break;
        case 5: _t->sort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->flushVisibleRows(); break;
        case 7: _t->dissectIdle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->dissectIdle(); break;
        case 9: _t->emitItemHeightChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PacketListModel::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListModel::goToPacket)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PacketListModel::*_t)(const QModelIndex & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListModel::maxLineCountChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PacketListModel::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListModel::itemHeightChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PacketListModel::*_t)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListModel::bgColorizationProgress)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject PacketListModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_PacketListModel.data,
      qt_meta_data_PacketListModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PacketListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PacketListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PacketListModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractItemModel::qt_metacast(_clname);
}

int PacketListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void PacketListModel::goToPacket(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PacketListModel::maxLineCountChanged(const QModelIndex & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< PacketListModel *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PacketListModel::itemHeightChanged(const QModelIndex & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PacketListModel::bgColorizationProgress(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
