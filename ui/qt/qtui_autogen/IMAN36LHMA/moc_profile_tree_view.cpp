/****************************************************************************
** Meta object code from reading C++ file 'profile_tree_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widgets/profile_tree_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'profile_tree_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProfileUrlLinkDelegate_t {
    QByteArrayData data[1];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProfileUrlLinkDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProfileUrlLinkDelegate_t qt_meta_stringdata_ProfileUrlLinkDelegate = {
    {
QT_MOC_LITERAL(0, 0, 22) // "ProfileUrlLinkDelegate"

    },
    "ProfileUrlLinkDelegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProfileUrlLinkDelegate[] = {

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

void ProfileUrlLinkDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ProfileUrlLinkDelegate::staticMetaObject = {
    { &UrlLinkDelegate::staticMetaObject, qt_meta_stringdata_ProfileUrlLinkDelegate.data,
      qt_meta_data_ProfileUrlLinkDelegate,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ProfileUrlLinkDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProfileUrlLinkDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProfileUrlLinkDelegate.stringdata0))
        return static_cast<void*>(this);
    return UrlLinkDelegate::qt_metacast(_clname);
}

int ProfileUrlLinkDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UrlLinkDelegate::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ProfileTreeEditDelegate_t {
    QByteArrayData data[1];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProfileTreeEditDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProfileTreeEditDelegate_t qt_meta_stringdata_ProfileTreeEditDelegate = {
    {
QT_MOC_LITERAL(0, 0, 23) // "ProfileTreeEditDelegate"

    },
    "ProfileTreeEditDelegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProfileTreeEditDelegate[] = {

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

void ProfileTreeEditDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ProfileTreeEditDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_ProfileTreeEditDelegate.data,
      qt_meta_data_ProfileTreeEditDelegate,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ProfileTreeEditDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProfileTreeEditDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProfileTreeEditDelegate.stringdata0))
        return static_cast<void*>(this);
    return QItemDelegate::qt_metacast(_clname);
}

int ProfileTreeEditDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ProfileTreeView_t {
    QByteArrayData data[9];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProfileTreeView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProfileTreeView_t qt_meta_stringdata_ProfileTreeView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ProfileTreeView"
QT_MOC_LITERAL(1, 16, 11), // "itemUpdated"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "selectionChanged"
QT_MOC_LITERAL(4, 46, 14), // "QItemSelection"
QT_MOC_LITERAL(5, 61, 8), // "selected"
QT_MOC_LITERAL(6, 70, 10), // "deselected"
QT_MOC_LITERAL(7, 81, 7), // "clicked"
QT_MOC_LITERAL(8, 89, 5) // "index"

    },
    "ProfileTreeView\0itemUpdated\0\0"
    "selectionChanged\0QItemSelection\0"
    "selected\0deselected\0clicked\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProfileTreeView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   30,    2, 0x09 /* Protected */,
       7,    1,   35,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void, QMetaType::QModelIndex,    8,

       0        // eod
};

void ProfileTreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProfileTreeView *_t = static_cast<ProfileTreeView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemUpdated(); break;
        case 1: _t->selectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 2: _t->clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
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
            typedef void (ProfileTreeView::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProfileTreeView::itemUpdated)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ProfileTreeView::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_ProfileTreeView.data,
      qt_meta_data_ProfileTreeView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ProfileTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProfileTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProfileTreeView.stringdata0))
        return static_cast<void*>(this);
    return QTreeView::qt_metacast(_clname);
}

int ProfileTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ProfileTreeView::itemUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
