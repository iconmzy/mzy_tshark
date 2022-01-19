/****************************************************************************
** Meta object code from reading C++ file 'filter_expression_frame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../filter_expression_frame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filter_expression_frame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FilterExpressionFrame_t {
    QByteArrayData data[11];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FilterExpressionFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FilterExpressionFrame_t qt_meta_stringdata_FilterExpressionFrame = {
    {
QT_MOC_LITERAL(0, 0, 21), // "FilterExpressionFrame"
QT_MOC_LITERAL(1, 22, 21), // "showPreferencesDialog"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "pane_name"
QT_MOC_LITERAL(4, 55, 24), // "filterExpressionsChanged"
QT_MOC_LITERAL(5, 80, 13), // "updateWidgets"
QT_MOC_LITERAL(6, 94, 48), // "on_filterExpressionPreference..."
QT_MOC_LITERAL(7, 143, 28), // "on_labelLineEdit_textChanged"
QT_MOC_LITERAL(8, 172, 36), // "on_displayFilterLineEdit_text..."
QT_MOC_LITERAL(9, 209, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(10, 231, 21) // "on_buttonBox_rejected"

    },
    "FilterExpressionFrame\0showPreferencesDialog\0"
    "\0pane_name\0filterExpressionsChanged\0"
    "updateWidgets\0"
    "on_filterExpressionPreferencesPushButton_clicked\0"
    "on_labelLineEdit_textChanged\0"
    "on_displayFilterLineEdit_textChanged\0"
    "on_buttonBox_accepted\0on_buttonBox_rejected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FilterExpressionFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   58,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    1,   60,    2, 0x08 /* Private */,
       8,    1,   63,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FilterExpressionFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FilterExpressionFrame *_t = static_cast<FilterExpressionFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showPreferencesDialog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->filterExpressionsChanged(); break;
        case 2: _t->updateWidgets(); break;
        case 3: _t->on_filterExpressionPreferencesPushButton_clicked(); break;
        case 4: _t->on_labelLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_displayFilterLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_buttonBox_accepted(); break;
        case 7: _t->on_buttonBox_rejected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (FilterExpressionFrame::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FilterExpressionFrame::showPreferencesDialog)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FilterExpressionFrame::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FilterExpressionFrame::filterExpressionsChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject FilterExpressionFrame::staticMetaObject = {
    { &AccordionFrame::staticMetaObject, qt_meta_stringdata_FilterExpressionFrame.data,
      qt_meta_data_FilterExpressionFrame,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FilterExpressionFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FilterExpressionFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FilterExpressionFrame.stringdata0))
        return static_cast<void*>(this);
    return AccordionFrame::qt_metacast(_clname);
}

int FilterExpressionFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AccordionFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void FilterExpressionFrame::showPreferencesDialog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FilterExpressionFrame::filterExpressionsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
