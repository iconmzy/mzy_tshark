/****************************************************************************
** Meta object code from reading C++ file 'search_frame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../search_frame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'search_frame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SearchFrame_t {
    QByteArrayData data[17];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchFrame_t qt_meta_stringdata_SearchFrame = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SearchFrame"
QT_MOC_LITERAL(1, 12, 14), // "setCaptureFile"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 13), // "capture_file*"
QT_MOC_LITERAL(4, 42, 2), // "cf"
QT_MOC_LITERAL(5, 45, 19), // "findFrameWithFilter"
QT_MOC_LITERAL(6, 65, 8), // "QString&"
QT_MOC_LITERAL(7, 74, 6), // "filter"
QT_MOC_LITERAL(8, 81, 39), // "on_searchInComboBox_currentIn..."
QT_MOC_LITERAL(9, 121, 3), // "idx"
QT_MOC_LITERAL(10, 125, 43), // "on_charEncodingComboBox_curre..."
QT_MOC_LITERAL(11, 169, 23), // "on_caseCheckBox_toggled"
QT_MOC_LITERAL(12, 193, 7), // "checked"
QT_MOC_LITERAL(13, 201, 41), // "on_searchTypeComboBox_current..."
QT_MOC_LITERAL(14, 243, 29), // "on_searchLineEdit_textChanged"
QT_MOC_LITERAL(15, 273, 21), // "on_findButton_clicked"
QT_MOC_LITERAL(16, 295, 23) // "on_cancelButton_clicked"

    },
    "SearchFrame\0setCaptureFile\0\0capture_file*\0"
    "cf\0findFrameWithFilter\0QString&\0filter\0"
    "on_searchInComboBox_currentIndexChanged\0"
    "idx\0on_charEncodingComboBox_currentIndexChanged\0"
    "on_caseCheckBox_toggled\0checked\0"
    "on_searchTypeComboBox_currentIndexChanged\0"
    "on_searchLineEdit_textChanged\0"
    "on_findButton_clicked\0on_cancelButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchFrame[] = {

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
       1,    1,   59,    2, 0x0a /* Public */,
       5,    1,   62,    2, 0x0a /* Public */,
       8,    1,   65,    2, 0x08 /* Private */,
      10,    1,   68,    2, 0x08 /* Private */,
      11,    1,   71,    2, 0x08 /* Private */,
      13,    1,   74,    2, 0x08 /* Private */,
      14,    1,   77,    2, 0x08 /* Private */,
      15,    0,   80,    2, 0x08 /* Private */,
      16,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SearchFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchFrame *_t = static_cast<SearchFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCaptureFile((*reinterpret_cast< capture_file*(*)>(_a[1]))); break;
        case 1: _t->findFrameWithFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_searchInComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_charEncodingComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_caseCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_searchTypeComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_searchLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_findButton_clicked(); break;
        case 8: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject SearchFrame::staticMetaObject = {
    { &AccordionFrame::staticMetaObject, qt_meta_stringdata_SearchFrame.data,
      qt_meta_data_SearchFrame,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SearchFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SearchFrame.stringdata0))
        return static_cast<void*>(this);
    return AccordionFrame::qt_metacast(_clname);
}

int SearchFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AccordionFrame::qt_metacall(_c, _id, _a);
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
