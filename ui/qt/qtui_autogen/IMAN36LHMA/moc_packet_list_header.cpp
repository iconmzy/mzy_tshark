/****************************************************************************
** Meta object code from reading C++ file 'packet_list_header.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widgets/packet_list_header.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packet_list_header.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PacketListHeader_t {
    QByteArrayData data[20];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PacketListHeader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PacketListHeader_t qt_meta_stringdata_PacketListHeader = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PacketListHeader"
QT_MOC_LITERAL(1, 17, 16), // "resetColumnWidth"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 3), // "col"
QT_MOC_LITERAL(4, 39, 13), // "updatePackets"
QT_MOC_LITERAL(5, 53, 6), // "redraw"
QT_MOC_LITERAL(6, 60, 21), // "showColumnPreferences"
QT_MOC_LITERAL(7, 82, 9), // "pane_name"
QT_MOC_LITERAL(8, 92, 10), // "editColumn"
QT_MOC_LITERAL(9, 103, 6), // "column"
QT_MOC_LITERAL(10, 110, 14), // "columnsChanged"
QT_MOC_LITERAL(11, 125, 25), // "columnVisibilityTriggered"
QT_MOC_LITERAL(12, 151, 12), // "setAlignment"
QT_MOC_LITERAL(13, 164, 8), // "QAction*"
QT_MOC_LITERAL(14, 173, 15), // "showColumnPrefs"
QT_MOC_LITERAL(15, 189, 12), // "doEditColumn"
QT_MOC_LITERAL(16, 202, 14), // "doResolveNames"
QT_MOC_LITERAL(17, 217, 15), // "resizeToContent"
QT_MOC_LITERAL(18, 233, 12), // "removeColumn"
QT_MOC_LITERAL(19, 246, 13) // "resizeToWidth"

    },
    "PacketListHeader\0resetColumnWidth\0\0"
    "col\0updatePackets\0redraw\0showColumnPreferences\0"
    "pane_name\0editColumn\0column\0columnsChanged\0"
    "columnVisibilityTriggered\0setAlignment\0"
    "QAction*\0showColumnPrefs\0doEditColumn\0"
    "doResolveNames\0resizeToContent\0"
    "removeColumn\0resizeToWidth"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PacketListHeader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,
       8,    1,   88,    2, 0x06 /* Public */,
      10,    0,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   92,    2, 0x09 /* Protected */,
      12,    1,   93,    2, 0x09 /* Protected */,
      14,    0,   96,    2, 0x09 /* Protected */,
      15,    0,   97,    2, 0x09 /* Protected */,
      16,    0,   98,    2, 0x09 /* Protected */,
      17,    0,   99,    2, 0x09 /* Protected */,
      18,    0,  100,    2, 0x09 /* Protected */,
      19,    0,  101,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PacketListHeader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PacketListHeader *_t = static_cast<PacketListHeader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resetColumnWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updatePackets((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->showColumnPreferences((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->editColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->columnsChanged(); break;
        case 5: _t->columnVisibilityTriggered(); break;
        case 6: _t->setAlignment((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 7: _t->showColumnPrefs(); break;
        case 8: _t->doEditColumn(); break;
        case 9: _t->doResolveNames(); break;
        case 10: _t->resizeToContent(); break;
        case 11: _t->removeColumn(); break;
        case 12: _t->resizeToWidth(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PacketListHeader::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListHeader::resetColumnWidth)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PacketListHeader::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListHeader::updatePackets)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PacketListHeader::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListHeader::showColumnPreferences)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PacketListHeader::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListHeader::editColumn)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (PacketListHeader::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketListHeader::columnsChanged)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject PacketListHeader::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_PacketListHeader.data,
      qt_meta_data_PacketListHeader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PacketListHeader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PacketListHeader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PacketListHeader.stringdata0))
        return static_cast<void*>(this);
    return QHeaderView::qt_metacast(_clname);
}

int PacketListHeader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void PacketListHeader::resetColumnWidth(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PacketListHeader::updatePackets(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PacketListHeader::showColumnPreferences(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PacketListHeader::editColumn(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PacketListHeader::columnsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
