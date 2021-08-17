/****************************************************************************
** Meta object code from reading C++ file 'astringlist_list_model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../models/astringlist_list_model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'astringlist_list_model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AStringListListModel_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AStringListListModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AStringListListModel_t qt_meta_stringdata_AStringListListModel = {
    {
QT_MOC_LITERAL(0, 0, 20) // "AStringListListModel"

    },
    "AStringListListModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AStringListListModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void AStringListListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject AStringListListModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_AStringListListModel.data,
      qt_meta_data_AStringListListModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AStringListListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AStringListListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AStringListListModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int AStringListListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_AStringListListSortFilterProxyModel_t {
    QByteArrayData data[8];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AStringListListSortFilterProxyModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AStringListListSortFilterProxyModel_t qt_meta_stringdata_AStringListListSortFilterProxyModel = {
    {
QT_MOC_LITERAL(0, 0, 35), // "AStringListListSortFilterProx..."
QT_MOC_LITERAL(1, 36, 9), // "setFilter"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 25), // "AStringListListFilterType"
QT_MOC_LITERAL(4, 73, 16), // "FilterByContains"
QT_MOC_LITERAL(5, 90, 13), // "FilterByStart"
QT_MOC_LITERAL(6, 104, 18), // "FilterByEquivalent"
QT_MOC_LITERAL(7, 123, 10) // "FilterNone"

    },
    "AStringListListSortFilterProxyModel\0"
    "setFilter\0\0AStringListListFilterType\0"
    "FilterByContains\0FilterByStart\0"
    "FilterByEquivalent\0FilterNone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AStringListListSortFilterProxyModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       1,   22, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // enums: name, flags, count, data
       3, 0x0,    4,   26,

 // enum data: key, value
       4, uint(AStringListListSortFilterProxyModel::FilterByContains),
       5, uint(AStringListListSortFilterProxyModel::FilterByStart),
       6, uint(AStringListListSortFilterProxyModel::FilterByEquivalent),
       7, uint(AStringListListSortFilterProxyModel::FilterNone),

       0        // eod
};

void AStringListListSortFilterProxyModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AStringListListSortFilterProxyModel *_t = static_cast<AStringListListSortFilterProxyModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AStringListListSortFilterProxyModel::staticMetaObject = {
    { &QSortFilterProxyModel::staticMetaObject, qt_meta_stringdata_AStringListListSortFilterProxyModel.data,
      qt_meta_data_AStringListListSortFilterProxyModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AStringListListSortFilterProxyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AStringListListSortFilterProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AStringListListSortFilterProxyModel.stringdata0))
        return static_cast<void*>(this);
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int AStringListListSortFilterProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_AStringListListUrlProxyModel_t {
    QByteArrayData data[1];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AStringListListUrlProxyModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AStringListListUrlProxyModel_t qt_meta_stringdata_AStringListListUrlProxyModel = {
    {
QT_MOC_LITERAL(0, 0, 28) // "AStringListListUrlProxyModel"

    },
    "AStringListListUrlProxyModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AStringListListUrlProxyModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void AStringListListUrlProxyModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject AStringListListUrlProxyModel::staticMetaObject = {
    { &QIdentityProxyModel::staticMetaObject, qt_meta_stringdata_AStringListListUrlProxyModel.data,
      qt_meta_data_AStringListListUrlProxyModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AStringListListUrlProxyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AStringListListUrlProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AStringListListUrlProxyModel.stringdata0))
        return static_cast<void*>(this);
    return QIdentityProxyModel::qt_metacast(_clname);
}

int AStringListListUrlProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIdentityProxyModel::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
