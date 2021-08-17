/****************************************************************************
** Meta object code from reading C++ file 'conversation_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../conversation_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'conversation_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConversationTreeWidget_t {
    QByteArrayData data[5];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConversationTreeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConversationTreeWidget_t qt_meta_stringdata_ConversationTreeWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ConversationTreeWidget"
QT_MOC_LITERAL(1, 23, 15), // "updateStartTime"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 8), // "absolute"
QT_MOC_LITERAL(4, 49, 21) // "filterActionTriggered"

    },
    "ConversationTreeWidget\0updateStartTime\0"
    "\0absolute\0filterActionTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConversationTreeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    0,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

       0        // eod
};

void ConversationTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConversationTreeWidget *_t = static_cast<ConversationTreeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateStartTime((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->filterActionTriggered(); break;
        default: ;
        }
    }
}

const QMetaObject ConversationTreeWidget::staticMetaObject = {
    { &TrafficTableTreeWidget::staticMetaObject, qt_meta_stringdata_ConversationTreeWidget.data,
      qt_meta_data_ConversationTreeWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConversationTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConversationTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConversationTreeWidget.stringdata0))
        return static_cast<void*>(this);
    return TrafficTableTreeWidget::qt_metacast(_clname);
}

int ConversationTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TrafficTableTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_ConversationDialog_t {
    QByteArrayData data[25];
    char stringdata0[382];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConversationDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConversationDialog_t qt_meta_stringdata_ConversationDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ConversationDialog"
QT_MOC_LITERAL(1, 19, 12), // "filterAction"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 6), // "filter"
QT_MOC_LITERAL(4, 40, 20), // "FilterAction::Action"
QT_MOC_LITERAL(5, 61, 6), // "action"
QT_MOC_LITERAL(6, 68, 24), // "FilterAction::ActionType"
QT_MOC_LITERAL(7, 93, 4), // "type"
QT_MOC_LITERAL(8, 98, 22), // "openFollowStreamDialog"
QT_MOC_LITERAL(9, 121, 13), // "follow_type_t"
QT_MOC_LITERAL(10, 135, 5), // "guint"
QT_MOC_LITERAL(11, 141, 10), // "stream_num"
QT_MOC_LITERAL(12, 152, 14), // "sub_stream_num"
QT_MOC_LITERAL(13, 167, 18), // "openTcpStreamGraph"
QT_MOC_LITERAL(14, 186, 10), // "graph_type"
QT_MOC_LITERAL(15, 197, 18), // "captureFileClosing"
QT_MOC_LITERAL(16, 216, 17), // "currentTabChanged"
QT_MOC_LITERAL(17, 234, 28), // "conversationSelectionChanged"
QT_MOC_LITERAL(18, 263, 32), // "on_displayFilterCheckBox_toggled"
QT_MOC_LITERAL(19, 296, 7), // "checked"
QT_MOC_LITERAL(20, 304, 12), // "followStream"
QT_MOC_LITERAL(21, 317, 8), // "graphTcp"
QT_MOC_LITERAL(22, 326, 26), // "on_buttonBox_helpRequested"
QT_MOC_LITERAL(23, 353, 20), // "displayFilterSuccess"
QT_MOC_LITERAL(24, 374, 7) // "success"

    },
    "ConversationDialog\0filterAction\0\0"
    "filter\0FilterAction::Action\0action\0"
    "FilterAction::ActionType\0type\0"
    "openFollowStreamDialog\0follow_type_t\0"
    "guint\0stream_num\0sub_stream_num\0"
    "openTcpStreamGraph\0graph_type\0"
    "captureFileClosing\0currentTabChanged\0"
    "conversationSelectionChanged\0"
    "on_displayFilterCheckBox_toggled\0"
    "checked\0followStream\0graphTcp\0"
    "on_buttonBox_helpRequested\0"
    "displayFilterSuccess\0success"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConversationDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   69,    2, 0x06 /* Public */,
       8,    3,   76,    2, 0x06 /* Public */,
      13,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   86,    2, 0x0a /* Public */,
      16,    0,   87,    2, 0x08 /* Private */,
      17,    0,   88,    2, 0x08 /* Private */,
      18,    1,   89,    2, 0x08 /* Private */,
      20,    0,   92,    2, 0x08 /* Private */,
      21,    0,   93,    2, 0x08 /* Private */,
      22,    0,   94,    2, 0x08 /* Private */,
      23,    1,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 10, 0x80000000 | 10,    7,   11,   12,
    QMetaType::Void, QMetaType::Int,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,

       0        // eod
};

void ConversationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConversationDialog *_t = static_cast<ConversationDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->filterAction((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< FilterAction::Action(*)>(_a[2])),(*reinterpret_cast< FilterAction::ActionType(*)>(_a[3]))); break;
        case 1: _t->openFollowStreamDialog((*reinterpret_cast< follow_type_t(*)>(_a[1])),(*reinterpret_cast< guint(*)>(_a[2])),(*reinterpret_cast< guint(*)>(_a[3]))); break;
        case 2: _t->openTcpStreamGraph((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->captureFileClosing(); break;
        case 4: _t->currentTabChanged(); break;
        case 5: _t->conversationSelectionChanged(); break;
        case 6: _t->on_displayFilterCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->followStream(); break;
        case 8: _t->graphTcp(); break;
        case 9: _t->on_buttonBox_helpRequested(); break;
        case 10: _t->displayFilterSuccess((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ConversationDialog::*_t)(QString , FilterAction::Action , FilterAction::ActionType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConversationDialog::filterAction)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ConversationDialog::*_t)(follow_type_t , guint , guint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConversationDialog::openFollowStreamDialog)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ConversationDialog::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConversationDialog::openTcpStreamGraph)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ConversationDialog::staticMetaObject = {
    { &TrafficTableDialog::staticMetaObject, qt_meta_stringdata_ConversationDialog.data,
      qt_meta_data_ConversationDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConversationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConversationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConversationDialog.stringdata0))
        return static_cast<void*>(this);
    return TrafficTableDialog::qt_metacast(_clname);
}

int ConversationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TrafficTableDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ConversationDialog::filterAction(QString _t1, FilterAction::Action _t2, FilterAction::ActionType _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConversationDialog::openFollowStreamDialog(follow_type_t _t1, guint _t2, guint _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConversationDialog::openTcpStreamGraph(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
