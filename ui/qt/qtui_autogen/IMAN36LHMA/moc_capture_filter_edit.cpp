/****************************************************************************
** Meta object code from reading C++ file 'capture_filter_edit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widgets/capture_filter_edit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'capture_filter_edit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CaptureFilterEdit_t {
    QByteArrayData data[19];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CaptureFilterEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CaptureFilterEdit_t qt_meta_stringdata_CaptureFilterEdit = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CaptureFilterEdit"
QT_MOC_LITERAL(1, 18, 26), // "captureFilterSyntaxChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 5), // "valid"
QT_MOC_LITERAL(4, 52, 12), // "startCapture"
QT_MOC_LITERAL(5, 65, 11), // "addBookmark"
QT_MOC_LITERAL(6, 77, 6), // "filter"
QT_MOC_LITERAL(7, 84, 11), // "checkFilter"
QT_MOC_LITERAL(8, 96, 18), // "updateBookmarkMenu"
QT_MOC_LITERAL(9, 115, 10), // "saveFilter"
QT_MOC_LITERAL(10, 126, 12), // "removeFilter"
QT_MOC_LITERAL(11, 139, 11), // "showFilters"
QT_MOC_LITERAL(12, 151, 13), // "prepareFilter"
QT_MOC_LITERAL(13, 165, 18), // "applyCaptureFilter"
QT_MOC_LITERAL(14, 184, 20), // "setFilterSyntaxState"
QT_MOC_LITERAL(15, 205, 5), // "state"
QT_MOC_LITERAL(16, 211, 7), // "err_msg"
QT_MOC_LITERAL(17, 219, 15), // "bookmarkClicked"
QT_MOC_LITERAL(18, 235, 11) // "clearFilter"

    },
    "CaptureFilterEdit\0captureFilterSyntaxChanged\0"
    "\0valid\0startCapture\0addBookmark\0filter\0"
    "checkFilter\0updateBookmarkMenu\0"
    "saveFilter\0removeFilter\0showFilters\0"
    "prepareFilter\0applyCaptureFilter\0"
    "setFilterSyntaxState\0state\0err_msg\0"
    "bookmarkClicked\0clearFilter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CaptureFilterEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    0,   87,    2, 0x06 /* Public */,
       5,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    0,   93,    2, 0x0a /* Public */,
      10,    0,   94,    2, 0x0a /* Public */,
      11,    0,   95,    2, 0x0a /* Public */,
      12,    0,   96,    2, 0x0a /* Public */,
      13,    0,   97,    2, 0x08 /* Private */,
       7,    1,   98,    2, 0x08 /* Private */,
      14,    3,  101,    2, 0x08 /* Private */,
      17,    0,  108,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,    6,   15,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CaptureFilterEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CaptureFilterEdit *_t = static_cast<CaptureFilterEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->captureFilterSyntaxChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->startCapture(); break;
        case 2: _t->addBookmark((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->checkFilter(); break;
        case 4: _t->updateBookmarkMenu(); break;
        case 5: _t->saveFilter(); break;
        case 6: _t->removeFilter(); break;
        case 7: _t->showFilters(); break;
        case 8: _t->prepareFilter(); break;
        case 9: _t->applyCaptureFilter(); break;
        case 10: _t->checkFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->setFilterSyntaxState((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 12: _t->bookmarkClicked(); break;
        case 13: _t->clearFilter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CaptureFilterEdit::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CaptureFilterEdit::captureFilterSyntaxChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CaptureFilterEdit::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CaptureFilterEdit::startCapture)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CaptureFilterEdit::*_t)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CaptureFilterEdit::addBookmark)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CaptureFilterEdit::staticMetaObject = {
    { &SyntaxLineEdit::staticMetaObject, qt_meta_stringdata_CaptureFilterEdit.data,
      qt_meta_data_CaptureFilterEdit,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CaptureFilterEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CaptureFilterEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CaptureFilterEdit.stringdata0))
        return static_cast<void*>(this);
    return SyntaxLineEdit::qt_metacast(_clname);
}

int CaptureFilterEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SyntaxLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void CaptureFilterEdit::captureFilterSyntaxChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CaptureFilterEdit::startCapture()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CaptureFilterEdit::addBookmark(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
