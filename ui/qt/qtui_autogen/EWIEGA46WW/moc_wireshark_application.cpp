/****************************************************************************
** Meta object code from reading C++ file 'wireshark_application.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wireshark_application.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wireshark_application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WiresharkApplication_t {
    QByteArrayData data[58];
    char stringdata0[880];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WiresharkApplication_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WiresharkApplication_t qt_meta_stringdata_WiresharkApplication = {
    {
QT_MOC_LITERAL(0, 0, 20), // "WiresharkApplication"
QT_MOC_LITERAL(1, 21, 14), // "appInitialized"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 19), // "localInterfaceEvent"
QT_MOC_LITERAL(4, 57, 11), // "const char*"
QT_MOC_LITERAL(5, 69, 6), // "ifname"
QT_MOC_LITERAL(6, 76, 5), // "added"
QT_MOC_LITERAL(7, 82, 2), // "up"
QT_MOC_LITERAL(8, 85, 25), // "localInterfaceListChanged"
QT_MOC_LITERAL(9, 111, 15), // "openCaptureFile"
QT_MOC_LITERAL(10, 127, 7), // "cf_path"
QT_MOC_LITERAL(11, 135, 14), // "display_filter"
QT_MOC_LITERAL(12, 150, 4), // "type"
QT_MOC_LITERAL(13, 155, 18), // "openCaptureOptions"
QT_MOC_LITERAL(14, 174, 21), // "recentPreferencesRead"
QT_MOC_LITERAL(15, 196, 25), // "updateRecentCaptureStatus"
QT_MOC_LITERAL(16, 222, 8), // "filename"
QT_MOC_LITERAL(17, 231, 4), // "size"
QT_MOC_LITERAL(18, 236, 10), // "accessible"
QT_MOC_LITERAL(19, 247, 12), // "splashUpdate"
QT_MOC_LITERAL(20, 260, 17), // "register_action_e"
QT_MOC_LITERAL(21, 278, 6), // "action"
QT_MOC_LITERAL(22, 285, 7), // "message"
QT_MOC_LITERAL(23, 293, 15), // "profileChanging"
QT_MOC_LITERAL(24, 309, 18), // "profileNameChanged"
QT_MOC_LITERAL(25, 328, 12), // "const gchar*"
QT_MOC_LITERAL(26, 341, 12), // "profile_name"
QT_MOC_LITERAL(27, 354, 14), // "columnsChanged"
QT_MOC_LITERAL(28, 369, 24), // "captureFilterListChanged"
QT_MOC_LITERAL(29, 394, 24), // "displayFilterListChanged"
QT_MOC_LITERAL(30, 419, 24), // "filterExpressionsChanged"
QT_MOC_LITERAL(31, 444, 23), // "packetDissectionChanged"
QT_MOC_LITERAL(32, 468, 18), // "preferencesChanged"
QT_MOC_LITERAL(33, 487, 24), // "addressResolutionChanged"
QT_MOC_LITERAL(34, 512, 17), // "columnDataChanged"
QT_MOC_LITERAL(35, 530, 18), // "checkDisplayFilter"
QT_MOC_LITERAL(36, 549, 13), // "fieldsChanged"
QT_MOC_LITERAL(37, 563, 16), // "reloadLuaPlugins"
QT_MOC_LITERAL(38, 580, 21), // "openStatCommandDialog"
QT_MOC_LITERAL(39, 602, 9), // "menu_path"
QT_MOC_LITERAL(40, 612, 3), // "arg"
QT_MOC_LITERAL(41, 616, 8), // "userdata"
QT_MOC_LITERAL(42, 625, 22), // "openTapParameterDialog"
QT_MOC_LITERAL(43, 648, 7), // "cfg_str"
QT_MOC_LITERAL(44, 656, 13), // "captureActive"
QT_MOC_LITERAL(45, 670, 15), // "zoomRegularFont"
QT_MOC_LITERAL(46, 686, 4), // "font"
QT_MOC_LITERAL(47, 691, 17), // "zoomMonospaceFont"
QT_MOC_LITERAL(48, 709, 19), // "clearRecentCaptures"
QT_MOC_LITERAL(49, 729, 21), // "refreshRecentCaptures"
QT_MOC_LITERAL(50, 751, 19), // "captureEventHandler"
QT_MOC_LITERAL(51, 771, 12), // "CaptureEvent"
QT_MOC_LITERAL(52, 784, 15), // "flushAppSignals"
QT_MOC_LITERAL(53, 800, 10), // "updateTaps"
QT_MOC_LITERAL(54, 811, 7), // "cleanup"
QT_MOC_LITERAL(55, 819, 23), // "ifChangeEventsAvailable"
QT_MOC_LITERAL(56, 843, 18), // "itemStatusFinished"
QT_MOC_LITERAL(57, 862, 17) // "refreshPacketData"

    },
    "WiresharkApplication\0appInitialized\0"
    "\0localInterfaceEvent\0const char*\0"
    "ifname\0added\0up\0localInterfaceListChanged\0"
    "openCaptureFile\0cf_path\0display_filter\0"
    "type\0openCaptureOptions\0recentPreferencesRead\0"
    "updateRecentCaptureStatus\0filename\0"
    "size\0accessible\0splashUpdate\0"
    "register_action_e\0action\0message\0"
    "profileChanging\0profileNameChanged\0"
    "const gchar*\0profile_name\0columnsChanged\0"
    "captureFilterListChanged\0"
    "displayFilterListChanged\0"
    "filterExpressionsChanged\0"
    "packetDissectionChanged\0preferencesChanged\0"
    "addressResolutionChanged\0columnDataChanged\0"
    "checkDisplayFilter\0fieldsChanged\0"
    "reloadLuaPlugins\0openStatCommandDialog\0"
    "menu_path\0arg\0userdata\0openTapParameterDialog\0"
    "cfg_str\0captureActive\0zoomRegularFont\0"
    "font\0zoomMonospaceFont\0clearRecentCaptures\0"
    "refreshRecentCaptures\0captureEventHandler\0"
    "CaptureEvent\0flushAppSignals\0updateTaps\0"
    "cleanup\0ifChangeEventsAvailable\0"
    "itemStatusFinished\0refreshPacketData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WiresharkApplication[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      26,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  204,    2, 0x06 /* Public */,
       3,    3,  205,    2, 0x06 /* Public */,
       8,    0,  212,    2, 0x06 /* Public */,
       9,    3,  213,    2, 0x06 /* Public */,
      13,    0,  220,    2, 0x06 /* Public */,
      14,    0,  221,    2, 0x06 /* Public */,
      15,    3,  222,    2, 0x06 /* Public */,
      19,    2,  229,    2, 0x06 /* Public */,
      23,    0,  234,    2, 0x06 /* Public */,
      24,    1,  235,    2, 0x06 /* Public */,
      27,    0,  238,    2, 0x06 /* Public */,
      28,    0,  239,    2, 0x06 /* Public */,
      29,    0,  240,    2, 0x06 /* Public */,
      30,    0,  241,    2, 0x06 /* Public */,
      31,    0,  242,    2, 0x06 /* Public */,
      32,    0,  243,    2, 0x06 /* Public */,
      33,    0,  244,    2, 0x06 /* Public */,
      34,    0,  245,    2, 0x06 /* Public */,
      35,    0,  246,    2, 0x06 /* Public */,
      36,    0,  247,    2, 0x06 /* Public */,
      37,    0,  248,    2, 0x06 /* Public */,
      38,    3,  249,    2, 0x06 /* Public */,
      42,    3,  256,    2, 0x06 /* Public */,
      44,    1,  263,    2, 0x06 /* Public */,
      45,    1,  266,    2, 0x06 /* Public */,
      47,    1,  269,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      48,    0,  272,    2, 0x0a /* Public */,
      49,    0,  273,    2, 0x0a /* Public */,
      50,    1,  274,    2, 0x0a /* Public */,
      52,    0,  277,    2, 0x0a /* Public */,
      53,    0,  278,    2, 0x08 /* Private */,
      54,    0,  279,    2, 0x08 /* Private */,
      55,    0,  280,    2, 0x08 /* Private */,
      56,    3,  281,    2, 0x08 /* Private */,
      56,    2,  288,    2, 0x28 /* Private | MethodCloned */,
      56,    1,  293,    2, 0x28 /* Private | MethodCloned */,
      56,    0,  296,    2, 0x28 /* Private | MethodCloned */,
      57,    0,  297,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::UInt,   10,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::Bool,   16,   17,   18,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 4,   21,   22,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,
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
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, QMetaType::VoidStar,   39,   40,   41,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::VoidStar,   43,   40,   41,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QFont,   46,
    QMetaType::Void, QMetaType::QFont,   46,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 51,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::Bool,   16,   17,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,   16,   17,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WiresharkApplication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WiresharkApplication *_t = static_cast<WiresharkApplication *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->appInitialized(); break;
        case 1: _t->localInterfaceEvent((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->localInterfaceListChanged(); break;
        case 3: _t->openCaptureFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 4: _t->openCaptureOptions(); break;
        case 5: _t->recentPreferencesRead(); break;
        case 6: _t->updateRecentCaptureStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 7: _t->splashUpdate((*reinterpret_cast< register_action_e(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 8: _t->profileChanging(); break;
        case 9: _t->profileNameChanged((*reinterpret_cast< const gchar*(*)>(_a[1]))); break;
        case 10: _t->columnsChanged(); break;
        case 11: _t->captureFilterListChanged(); break;
        case 12: _t->displayFilterListChanged(); break;
        case 13: _t->filterExpressionsChanged(); break;
        case 14: _t->packetDissectionChanged(); break;
        case 15: _t->preferencesChanged(); break;
        case 16: _t->addressResolutionChanged(); break;
        case 17: _t->columnDataChanged(); break;
        case 18: _t->checkDisplayFilter(); break;
        case 19: _t->fieldsChanged(); break;
        case 20: _t->reloadLuaPlugins(); break;
        case 21: _t->openStatCommandDialog((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        case 22: _t->openTapParameterDialog((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        case 23: _t->captureActive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->zoomRegularFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 25: _t->zoomMonospaceFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 26: _t->clearRecentCaptures(); break;
        case 27: _t->refreshRecentCaptures(); break;
        case 28: _t->captureEventHandler((*reinterpret_cast< CaptureEvent(*)>(_a[1]))); break;
        case 29: _t->flushAppSignals(); break;
        case 30: _t->updateTaps(); break;
        case 31: _t->cleanup(); break;
        case 32: _t->ifChangeEventsAvailable(); break;
        case 33: _t->itemStatusFinished((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 34: _t->itemStatusFinished((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 35: _t->itemStatusFinished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 36: _t->itemStatusFinished(); break;
        case 37: _t->refreshPacketData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::appInitialized)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(const char * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::localInterfaceEvent)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::localInterfaceListChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(QString , QString , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::openCaptureFile)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::openCaptureOptions)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::recentPreferencesRead)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(const QString & , qint64 , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::updateRecentCaptureStatus)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(register_action_e , const char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::splashUpdate)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::profileChanging)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(const gchar * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::profileNameChanged)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::columnsChanged)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::captureFilterListChanged)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::displayFilterListChanged)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::filterExpressionsChanged)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::packetDissectionChanged)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::preferencesChanged)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::addressResolutionChanged)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::columnDataChanged)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::checkDisplayFilter)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::fieldsChanged)) {
                *result = 19;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::reloadLuaPlugins)) {
                *result = 20;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(const QString & , const char * , void * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::openStatCommandDialog)) {
                *result = 21;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(const QString , const QString , void * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::openTapParameterDialog)) {
                *result = 22;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::captureActive)) {
                *result = 23;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(const QFont & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::zoomRegularFont)) {
                *result = 24;
                return;
            }
        }
        {
            typedef void (WiresharkApplication::*_t)(const QFont & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WiresharkApplication::zoomMonospaceFont)) {
                *result = 25;
                return;
            }
        }
    }
}

const QMetaObject WiresharkApplication::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_WiresharkApplication.data,
      qt_meta_data_WiresharkApplication,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WiresharkApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WiresharkApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WiresharkApplication.stringdata0))
        return static_cast<void*>(this);
    return QApplication::qt_metacast(_clname);
}

int WiresharkApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 38;
    }
    return _id;
}

// SIGNAL 0
void WiresharkApplication::appInitialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WiresharkApplication::localInterfaceEvent(const char * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WiresharkApplication::localInterfaceListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WiresharkApplication::openCaptureFile(QString _t1, QString _t2, unsigned int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WiresharkApplication::openCaptureOptions()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void WiresharkApplication::recentPreferencesRead()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void WiresharkApplication::updateRecentCaptureStatus(const QString & _t1, qint64 _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WiresharkApplication::splashUpdate(register_action_e _t1, const char * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void WiresharkApplication::profileChanging()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void WiresharkApplication::profileNameChanged(const gchar * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void WiresharkApplication::columnsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void WiresharkApplication::captureFilterListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void WiresharkApplication::displayFilterListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void WiresharkApplication::filterExpressionsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void WiresharkApplication::packetDissectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void WiresharkApplication::preferencesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void WiresharkApplication::addressResolutionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void WiresharkApplication::columnDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void WiresharkApplication::checkDisplayFilter()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void WiresharkApplication::fieldsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void WiresharkApplication::reloadLuaPlugins()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void WiresharkApplication::openStatCommandDialog(const QString & _t1, const char * _t2, void * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void WiresharkApplication::openTapParameterDialog(const QString _t1, const QString _t2, void * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void WiresharkApplication::captureActive(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void WiresharkApplication::zoomRegularFont(const QFont & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void WiresharkApplication::zoomMonospaceFont(const QFont & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
