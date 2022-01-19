/****************************************************************************
** Meta object code from reading C++ file 'preference_editor_frame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../preference_editor_frame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preference_editor_frame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PreferenceEditorFrame_t {
    QByteArrayData data[18];
    char stringdata0[334];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PreferenceEditorFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PreferenceEditorFrame_t qt_meta_stringdata_PreferenceEditorFrame = {
    {
QT_MOC_LITERAL(0, 0, 21), // "PreferenceEditorFrame"
QT_MOC_LITERAL(1, 22, 23), // "showProtocolPreferences"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 11), // "module_name"
QT_MOC_LITERAL(4, 59, 14), // "editPreference"
QT_MOC_LITERAL(5, 74, 11), // "preference*"
QT_MOC_LITERAL(6, 86, 4), // "pref"
QT_MOC_LITERAL(7, 91, 12), // "pref_module*"
QT_MOC_LITERAL(8, 104, 6), // "module"
QT_MOC_LITERAL(9, 111, 22), // "uintLineEditTextEdited"
QT_MOC_LITERAL(10, 134, 7), // "new_str"
QT_MOC_LITERAL(11, 142, 24), // "stringLineEditTextEdited"
QT_MOC_LITERAL(12, 167, 23), // "rangeLineEditTextEdited"
QT_MOC_LITERAL(13, 191, 23), // "browsePushButtonClicked"
QT_MOC_LITERAL(14, 215, 38), // "on_modulePreferencesToolButto..."
QT_MOC_LITERAL(15, 254, 35), // "on_preferenceLineEdit_returnP..."
QT_MOC_LITERAL(16, 290, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(17, 312, 21) // "on_buttonBox_rejected"

    },
    "PreferenceEditorFrame\0showProtocolPreferences\0"
    "\0module_name\0editPreference\0preference*\0"
    "pref\0pref_module*\0module\0"
    "uintLineEditTextEdited\0new_str\0"
    "stringLineEditTextEdited\0"
    "rangeLineEditTextEdited\0browsePushButtonClicked\0"
    "on_modulePreferencesToolButton_clicked\0"
    "on_preferenceLineEdit_returnPressed\0"
    "on_buttonBox_accepted\0on_buttonBox_rejected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PreferenceEditorFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   77,    2, 0x0a /* Public */,
       4,    1,   82,    2, 0x2a /* Public | MethodCloned */,
       4,    0,   85,    2, 0x2a /* Public | MethodCloned */,
       9,    1,   86,    2, 0x08 /* Private */,
      11,    1,   89,    2, 0x08 /* Private */,
      12,    1,   92,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,
      16,    0,   98,    2, 0x08 /* Private */,
      17,    0,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PreferenceEditorFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PreferenceEditorFrame *_t = static_cast<PreferenceEditorFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showProtocolPreferences((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->editPreference((*reinterpret_cast< preference*(*)>(_a[1])),(*reinterpret_cast< pref_module*(*)>(_a[2]))); break;
        case 2: _t->editPreference((*reinterpret_cast< preference*(*)>(_a[1]))); break;
        case 3: _t->editPreference(); break;
        case 4: _t->uintLineEditTextEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->stringLineEditTextEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->rangeLineEditTextEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->browsePushButtonClicked(); break;
        case 8: _t->on_modulePreferencesToolButton_clicked(); break;
        case 9: _t->on_preferenceLineEdit_returnPressed(); break;
        case 10: _t->on_buttonBox_accepted(); break;
        case 11: _t->on_buttonBox_rejected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PreferenceEditorFrame::*_t)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PreferenceEditorFrame::showProtocolPreferences)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PreferenceEditorFrame::staticMetaObject = {
    { &AccordionFrame::staticMetaObject, qt_meta_stringdata_PreferenceEditorFrame.data,
      qt_meta_data_PreferenceEditorFrame,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PreferenceEditorFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PreferenceEditorFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PreferenceEditorFrame.stringdata0))
        return static_cast<void*>(this);
    return AccordionFrame::qt_metacast(_clname);
}

int PreferenceEditorFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AccordionFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void PreferenceEditorFrame::showProtocolPreferences(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
