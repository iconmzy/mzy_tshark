/****************************************************************************
** Meta object code from reading C++ file 'byte_view_text.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widgets/byte_view_text.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'byte_view_text.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ByteViewText_t {
    QByteArrayData data[20];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ByteViewText_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ByteViewText_t qt_meta_stringdata_ByteViewText = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ByteViewText"
QT_MOC_LITERAL(1, 13, 11), // "byteHovered"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "pos"
QT_MOC_LITERAL(4, 30, 12), // "byteSelected"
QT_MOC_LITERAL(5, 43, 23), // "byteViewSettingsChanged"
QT_MOC_LITERAL(6, 67, 16), // "setMonospaceFont"
QT_MOC_LITERAL(7, 84, 9), // "mono_font"
QT_MOC_LITERAL(8, 94, 22), // "updateByteViewSettings"
QT_MOC_LITERAL(9, 117, 12), // "markProtocol"
QT_MOC_LITERAL(10, 130, 5), // "start"
QT_MOC_LITERAL(11, 136, 6), // "length"
QT_MOC_LITERAL(12, 143, 9), // "markField"
QT_MOC_LITERAL(13, 153, 9), // "scroll_to"
QT_MOC_LITERAL(14, 163, 12), // "markAppendix"
QT_MOC_LITERAL(15, 176, 9), // "copyBytes"
QT_MOC_LITERAL(16, 186, 19), // "setHexDisplayFormat"
QT_MOC_LITERAL(17, 206, 8), // "QAction*"
QT_MOC_LITERAL(18, 215, 6), // "action"
QT_MOC_LITERAL(19, 222, 20) // "setCharacterEncoding"

    },
    "ByteViewText\0byteHovered\0\0pos\0"
    "byteSelected\0byteViewSettingsChanged\0"
    "setMonospaceFont\0mono_font\0"
    "updateByteViewSettings\0markProtocol\0"
    "start\0length\0markField\0scroll_to\0"
    "markAppendix\0copyBytes\0setHexDisplayFormat\0"
    "QAction*\0action\0setCharacterEncoding"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ByteViewText[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       5,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   81,    2, 0x0a /* Public */,
       8,    0,   84,    2, 0x0a /* Public */,
       9,    2,   85,    2, 0x0a /* Public */,
      12,    3,   90,    2, 0x0a /* Public */,
      12,    2,   97,    2, 0x2a /* Public | MethodCloned */,
      14,    2,  102,    2, 0x0a /* Public */,
      15,    1,  107,    2, 0x08 /* Private */,
      16,    1,  110,    2, 0x08 /* Private */,
      19,    1,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QFont,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   10,   11,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void ByteViewText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ByteViewText *_t = static_cast<ByteViewText *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->byteHovered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->byteSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->byteViewSettingsChanged(); break;
        case 3: _t->setMonospaceFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 4: _t->updateByteViewSettings(); break;
        case 5: _t->markProtocol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->markField((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 7: _t->markField((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->markAppendix((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->copyBytes((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setHexDisplayFormat((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 11: _t->setCharacterEncoding((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 11:
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
            typedef void (ByteViewText::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ByteViewText::byteHovered)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ByteViewText::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ByteViewText::byteSelected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ByteViewText::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ByteViewText::byteViewSettingsChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ByteViewText::staticMetaObject = {
    { &QAbstractScrollArea::staticMetaObject, qt_meta_stringdata_ByteViewText.data,
      qt_meta_data_ByteViewText,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ByteViewText::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ByteViewText::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ByteViewText.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IDataPrintable"))
        return static_cast< IDataPrintable*>(this);
    if (!strcmp(_clname, "org.wireshark.Qt.UI.IDataPrintable"))
        return static_cast< IDataPrintable*>(this);
    return QAbstractScrollArea::qt_metacast(_clname);
}

int ByteViewText::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ByteViewText::byteHovered(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ByteViewText::byteSelected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ByteViewText::byteViewSettingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
