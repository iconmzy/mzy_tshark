/****************************************************************************
** Meta object code from reading C++ file 'rtp_player_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../rtp_player_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtp_player_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RtpPlayerDialog_t {
    QByteArrayData data[40];
    char stringdata0[798];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RtpPlayerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RtpPlayerDialog_t qt_meta_stringdata_RtpPlayerDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "RtpPlayerDialog"
QT_MOC_LITERAL(1, 16, 10), // "goToPacket"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "packet_num"
QT_MOC_LITERAL(4, 39, 12), // "retapPackets"
QT_MOC_LITERAL(5, 52, 13), // "rescanPackets"
QT_MOC_LITERAL(6, 66, 12), // "rescale_axes"
QT_MOC_LITERAL(7, 79, 13), // "updateWidgets"
QT_MOC_LITERAL(8, 93, 12), // "graphClicked"
QT_MOC_LITERAL(9, 106, 12), // "QMouseEvent*"
QT_MOC_LITERAL(10, 119, 5), // "event"
QT_MOC_LITERAL(11, 125, 18), // "graphDoubleClicked"
QT_MOC_LITERAL(12, 144, 15), // "updateHintLabel"
QT_MOC_LITERAL(13, 160, 10), // "resetXAxis"
QT_MOC_LITERAL(14, 171, 15), // "setPlayPosition"
QT_MOC_LITERAL(15, 187, 4), // "secs"
QT_MOC_LITERAL(16, 192, 16), // "setPlaybackError"
QT_MOC_LITERAL(17, 209, 14), // "playback_error"
QT_MOC_LITERAL(18, 224, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(19, 246, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(20, 268, 24), // "on_actionReset_triggered"
QT_MOC_LITERAL(21, 293, 25), // "on_actionZoomIn_triggered"
QT_MOC_LITERAL(22, 319, 26), // "on_actionZoomOut_triggered"
QT_MOC_LITERAL(23, 346, 29), // "on_actionMoveLeft10_triggered"
QT_MOC_LITERAL(24, 376, 30), // "on_actionMoveRight10_triggered"
QT_MOC_LITERAL(25, 407, 28), // "on_actionMoveLeft1_triggered"
QT_MOC_LITERAL(26, 436, 29), // "on_actionMoveRight1_triggered"
QT_MOC_LITERAL(27, 466, 29), // "on_actionGoToPacket_triggered"
QT_MOC_LITERAL(28, 496, 40), // "on_streamTreeWidget_itemSelec..."
QT_MOC_LITERAL(29, 537, 37), // "on_streamTreeWidget_itemDoubl..."
QT_MOC_LITERAL(30, 575, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(31, 592, 4), // "item"
QT_MOC_LITERAL(32, 597, 6), // "column"
QT_MOC_LITERAL(33, 604, 43), // "on_outputDeviceComboBox_curre..."
QT_MOC_LITERAL(34, 648, 29), // "on_jitterSpinBox_valueChanged"
QT_MOC_LITERAL(35, 678, 37), // "on_timingComboBox_currentInde..."
QT_MOC_LITERAL(36, 716, 22), // "on_todCheckBox_toggled"
QT_MOC_LITERAL(37, 739, 7), // "checked"
QT_MOC_LITERAL(38, 747, 26), // "on_buttonBox_helpRequested"
QT_MOC_LITERAL(39, 774, 23) // "currentOutputDeviceName"

    },
    "RtpPlayerDialog\0goToPacket\0\0packet_num\0"
    "retapPackets\0rescanPackets\0rescale_axes\0"
    "updateWidgets\0graphClicked\0QMouseEvent*\0"
    "event\0graphDoubleClicked\0updateHintLabel\0"
    "resetXAxis\0setPlayPosition\0secs\0"
    "setPlaybackError\0playback_error\0"
    "on_playButton_clicked\0on_stopButton_clicked\0"
    "on_actionReset_triggered\0"
    "on_actionZoomIn_triggered\0"
    "on_actionZoomOut_triggered\0"
    "on_actionMoveLeft10_triggered\0"
    "on_actionMoveRight10_triggered\0"
    "on_actionMoveLeft1_triggered\0"
    "on_actionMoveRight1_triggered\0"
    "on_actionGoToPacket_triggered\0"
    "on_streamTreeWidget_itemSelectionChanged\0"
    "on_streamTreeWidget_itemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_outputDeviceComboBox_currentIndexChanged\0"
    "on_jitterSpinBox_valueChanged\0"
    "on_timingComboBox_currentIndexChanged\0"
    "on_todCheckBox_toggled\0checked\0"
    "on_buttonBox_helpRequested\0"
    "currentOutputDeviceName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RtpPlayerDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       1,  206, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  154,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  157,    2, 0x08 /* Private */,
       5,    1,  158,    2, 0x08 /* Private */,
       5,    0,  161,    2, 0x28 /* Private | MethodCloned */,
       7,    0,  162,    2, 0x08 /* Private */,
       8,    1,  163,    2, 0x08 /* Private */,
      11,    1,  166,    2, 0x08 /* Private */,
      12,    0,  169,    2, 0x08 /* Private */,
      13,    0,  170,    2, 0x08 /* Private */,
      14,    1,  171,    2, 0x08 /* Private */,
      16,    1,  174,    2, 0x08 /* Private */,
      18,    0,  177,    2, 0x08 /* Private */,
      19,    0,  178,    2, 0x08 /* Private */,
      20,    0,  179,    2, 0x08 /* Private */,
      21,    0,  180,    2, 0x08 /* Private */,
      22,    0,  181,    2, 0x08 /* Private */,
      23,    0,  182,    2, 0x08 /* Private */,
      24,    0,  183,    2, 0x08 /* Private */,
      25,    0,  184,    2, 0x08 /* Private */,
      26,    0,  185,    2, 0x08 /* Private */,
      27,    0,  186,    2, 0x08 /* Private */,
      28,    0,  187,    2, 0x08 /* Private */,
      29,    2,  188,    2, 0x08 /* Private */,
      33,    1,  193,    2, 0x08 /* Private */,
      34,    1,  196,    2, 0x08 /* Private */,
      35,    1,  199,    2, 0x08 /* Private */,
      36,    1,  202,    2, 0x08 /* Private */,
      38,    0,  205,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30, QMetaType::Int,   31,   32,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,   37,
    QMetaType::Void,

 // properties: name, type, flags
      39, QMetaType::QString, 0x00095001,

       0        // eod
};

void RtpPlayerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RtpPlayerDialog *_t = static_cast<RtpPlayerDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->goToPacket((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->retapPackets(); break;
        case 2: _t->rescanPackets((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->rescanPackets(); break;
        case 4: _t->updateWidgets(); break;
        case 5: _t->graphClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->graphDoubleClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->updateHintLabel(); break;
        case 8: _t->resetXAxis(); break;
        case 9: _t->setPlayPosition((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setPlaybackError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_playButton_clicked(); break;
        case 12: _t->on_stopButton_clicked(); break;
        case 13: _t->on_actionReset_triggered(); break;
        case 14: _t->on_actionZoomIn_triggered(); break;
        case 15: _t->on_actionZoomOut_triggered(); break;
        case 16: _t->on_actionMoveLeft10_triggered(); break;
        case 17: _t->on_actionMoveRight10_triggered(); break;
        case 18: _t->on_actionMoveLeft1_triggered(); break;
        case 19: _t->on_actionMoveRight1_triggered(); break;
        case 20: _t->on_actionGoToPacket_triggered(); break;
        case 21: _t->on_streamTreeWidget_itemSelectionChanged(); break;
        case 22: _t->on_streamTreeWidget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 23: _t->on_outputDeviceComboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->on_jitterSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 25: _t->on_timingComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_todCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->on_buttonBox_helpRequested(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (RtpPlayerDialog::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RtpPlayerDialog::goToPacket)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        RtpPlayerDialog *_t = static_cast<RtpPlayerDialog *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->currentOutputDeviceName(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject RtpPlayerDialog::staticMetaObject = {
    { &WiresharkDialog::staticMetaObject, qt_meta_stringdata_RtpPlayerDialog.data,
      qt_meta_data_RtpPlayerDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RtpPlayerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RtpPlayerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RtpPlayerDialog.stringdata0))
        return static_cast<void*>(this);
    return WiresharkDialog::qt_metacast(_clname);
}

int RtpPlayerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WiresharkDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void RtpPlayerDialog::goToPacket(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
