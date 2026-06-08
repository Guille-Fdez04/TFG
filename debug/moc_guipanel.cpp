/****************************************************************************
** Meta object code from reading C++ file 'guipanel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../guipanel.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guipanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGUIPanelENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGUIPanelENDCLASS = QtMocHelpers::stringData(
    "GUIPanel",
    "readRequest",
    "",
    "on_pingButton_clicked",
    "on_runButton_clicked",
    "on_statusButton_clicked",
    "on_init_button_clicked",
    "on_horizontalSlider_valueChanged",
    "value",
    "on_config_carga_button_pressed",
    "on_boton_cerrar_pressed",
    "on_pushButton_pressed",
    "onMQTT_Connected",
    "onMQTT_subscribed",
    "topic",
    "onMQTT_Disconnected",
    "onMQTT_Error",
    "QMQTT::ClientError",
    "error",
    "startClient",
    "on_btn_pres_asl_pressed",
    "on_btn_temp_max_pressed",
    "on_btn_temp_min_pressed",
    "on_btn_hr_max_pressed",
    "on_btn_hr_min_pressed",
    "on_btn_pres_max_pressed",
    "on_btn_pres_min_pressed",
    "on_btn_acc_max_pressed",
    "on_btn_acc_min_pressed",
    "on_validarbtn_pressed",
    "on_tasaCombobox_currentIndexChanged",
    "index",
    "on_brokerConButton_pressed",
    "on_brokerPublico_checkStateChanged",
    "Qt::CheckState",
    "arg1",
    "on_acercaDeBTN_pressed",
    "on_timer_timeout",
    "on_timer_wait_timeout",
    "on_refrescarPuertos_clicked",
    "on_pushButton_2_pressed"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGUIPanelENDCLASS_t {
    uint offsetsAndSizes[82];
    char stringdata0[9];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[22];
    char stringdata4[21];
    char stringdata5[24];
    char stringdata6[23];
    char stringdata7[33];
    char stringdata8[6];
    char stringdata9[31];
    char stringdata10[24];
    char stringdata11[22];
    char stringdata12[17];
    char stringdata13[18];
    char stringdata14[6];
    char stringdata15[20];
    char stringdata16[13];
    char stringdata17[19];
    char stringdata18[6];
    char stringdata19[12];
    char stringdata20[24];
    char stringdata21[24];
    char stringdata22[24];
    char stringdata23[22];
    char stringdata24[22];
    char stringdata25[24];
    char stringdata26[24];
    char stringdata27[23];
    char stringdata28[23];
    char stringdata29[22];
    char stringdata30[36];
    char stringdata31[6];
    char stringdata32[27];
    char stringdata33[35];
    char stringdata34[15];
    char stringdata35[5];
    char stringdata36[23];
    char stringdata37[17];
    char stringdata38[22];
    char stringdata39[28];
    char stringdata40[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGUIPanelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGUIPanelENDCLASS_t qt_meta_stringdata_CLASSGUIPanelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "GUIPanel"
        QT_MOC_LITERAL(9, 11),  // "readRequest"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 21),  // "on_pingButton_clicked"
        QT_MOC_LITERAL(44, 20),  // "on_runButton_clicked"
        QT_MOC_LITERAL(65, 23),  // "on_statusButton_clicked"
        QT_MOC_LITERAL(89, 22),  // "on_init_button_clicked"
        QT_MOC_LITERAL(112, 32),  // "on_horizontalSlider_valueChanged"
        QT_MOC_LITERAL(145, 5),  // "value"
        QT_MOC_LITERAL(151, 30),  // "on_config_carga_button_pressed"
        QT_MOC_LITERAL(182, 23),  // "on_boton_cerrar_pressed"
        QT_MOC_LITERAL(206, 21),  // "on_pushButton_pressed"
        QT_MOC_LITERAL(228, 16),  // "onMQTT_Connected"
        QT_MOC_LITERAL(245, 17),  // "onMQTT_subscribed"
        QT_MOC_LITERAL(263, 5),  // "topic"
        QT_MOC_LITERAL(269, 19),  // "onMQTT_Disconnected"
        QT_MOC_LITERAL(289, 12),  // "onMQTT_Error"
        QT_MOC_LITERAL(302, 18),  // "QMQTT::ClientError"
        QT_MOC_LITERAL(321, 5),  // "error"
        QT_MOC_LITERAL(327, 11),  // "startClient"
        QT_MOC_LITERAL(339, 23),  // "on_btn_pres_asl_pressed"
        QT_MOC_LITERAL(363, 23),  // "on_btn_temp_max_pressed"
        QT_MOC_LITERAL(387, 23),  // "on_btn_temp_min_pressed"
        QT_MOC_LITERAL(411, 21),  // "on_btn_hr_max_pressed"
        QT_MOC_LITERAL(433, 21),  // "on_btn_hr_min_pressed"
        QT_MOC_LITERAL(455, 23),  // "on_btn_pres_max_pressed"
        QT_MOC_LITERAL(479, 23),  // "on_btn_pres_min_pressed"
        QT_MOC_LITERAL(503, 22),  // "on_btn_acc_max_pressed"
        QT_MOC_LITERAL(526, 22),  // "on_btn_acc_min_pressed"
        QT_MOC_LITERAL(549, 21),  // "on_validarbtn_pressed"
        QT_MOC_LITERAL(571, 35),  // "on_tasaCombobox_currentIndexC..."
        QT_MOC_LITERAL(607, 5),  // "index"
        QT_MOC_LITERAL(613, 26),  // "on_brokerConButton_pressed"
        QT_MOC_LITERAL(640, 34),  // "on_brokerPublico_checkStateCh..."
        QT_MOC_LITERAL(675, 14),  // "Qt::CheckState"
        QT_MOC_LITERAL(690, 4),  // "arg1"
        QT_MOC_LITERAL(695, 22),  // "on_acercaDeBTN_pressed"
        QT_MOC_LITERAL(718, 16),  // "on_timer_timeout"
        QT_MOC_LITERAL(735, 21),  // "on_timer_wait_timeout"
        QT_MOC_LITERAL(757, 27),  // "on_refrescarPuertos_clicked"
        QT_MOC_LITERAL(785, 23)   // "on_pushButton_2_pressed"
    },
    "GUIPanel",
    "readRequest",
    "",
    "on_pingButton_clicked",
    "on_runButton_clicked",
    "on_statusButton_clicked",
    "on_init_button_clicked",
    "on_horizontalSlider_valueChanged",
    "value",
    "on_config_carga_button_pressed",
    "on_boton_cerrar_pressed",
    "on_pushButton_pressed",
    "onMQTT_Connected",
    "onMQTT_subscribed",
    "topic",
    "onMQTT_Disconnected",
    "onMQTT_Error",
    "QMQTT::ClientError",
    "error",
    "startClient",
    "on_btn_pres_asl_pressed",
    "on_btn_temp_max_pressed",
    "on_btn_temp_min_pressed",
    "on_btn_hr_max_pressed",
    "on_btn_hr_min_pressed",
    "on_btn_pres_max_pressed",
    "on_btn_pres_min_pressed",
    "on_btn_acc_max_pressed",
    "on_btn_acc_min_pressed",
    "on_validarbtn_pressed",
    "on_tasaCombobox_currentIndexChanged",
    "index",
    "on_brokerConButton_pressed",
    "on_brokerPublico_checkStateChanged",
    "Qt::CheckState",
    "arg1",
    "on_acercaDeBTN_pressed",
    "on_timer_timeout",
    "on_timer_wait_timeout",
    "on_refrescarPuertos_clicked",
    "on_pushButton_2_pressed"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGUIPanelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  206,    2, 0x08,    1 /* Private */,
       3,    0,  207,    2, 0x08,    2 /* Private */,
       4,    0,  208,    2, 0x08,    3 /* Private */,
       5,    0,  209,    2, 0x08,    4 /* Private */,
       6,    0,  210,    2, 0x08,    5 /* Private */,
       7,    1,  211,    2, 0x08,    6 /* Private */,
       9,    0,  214,    2, 0x08,    8 /* Private */,
      10,    0,  215,    2, 0x08,    9 /* Private */,
      11,    0,  216,    2, 0x08,   10 /* Private */,
      12,    0,  217,    2, 0x08,   11 /* Private */,
      13,    1,  218,    2, 0x08,   12 /* Private */,
      15,    0,  221,    2, 0x08,   14 /* Private */,
      16,    1,  222,    2, 0x08,   15 /* Private */,
      19,    0,  225,    2, 0x08,   17 /* Private */,
      20,    0,  226,    2, 0x08,   18 /* Private */,
      21,    0,  227,    2, 0x08,   19 /* Private */,
      22,    0,  228,    2, 0x08,   20 /* Private */,
      23,    0,  229,    2, 0x08,   21 /* Private */,
      24,    0,  230,    2, 0x08,   22 /* Private */,
      25,    0,  231,    2, 0x08,   23 /* Private */,
      26,    0,  232,    2, 0x08,   24 /* Private */,
      27,    0,  233,    2, 0x08,   25 /* Private */,
      28,    0,  234,    2, 0x08,   26 /* Private */,
      29,    0,  235,    2, 0x08,   27 /* Private */,
      30,    1,  236,    2, 0x08,   28 /* Private */,
      32,    0,  239,    2, 0x08,   30 /* Private */,
      33,    1,  240,    2, 0x08,   31 /* Private */,
      36,    0,  243,    2, 0x08,   33 /* Private */,
      37,    0,  244,    2, 0x08,   34 /* Private */,
      38,    0,  245,    2, 0x08,   35 /* Private */,
      39,    0,  246,    2, 0x08,   36 /* Private */,
      40,    0,  247,    2, 0x08,   37 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
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
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 34,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GUIPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSGUIPanelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGUIPanelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGUIPanelENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GUIPanel, std::true_type>,
        // method 'readRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pingButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_runButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_statusButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_init_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_horizontalSlider_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_config_carga_button_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_boton_cerrar_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMQTT_Connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMQTT_subscribed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onMQTT_Disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMQTT_Error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QMQTT::ClientError, std::false_type>,
        // method 'startClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_pres_asl_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_temp_max_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_temp_min_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_hr_max_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_hr_min_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_pres_max_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_pres_min_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_acc_max_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_acc_min_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_validarbtn_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tasaCombobox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_brokerConButton_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_brokerPublico_checkStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Qt::CheckState &, std::false_type>,
        // method 'on_acercaDeBTN_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_timer_timeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_timer_wait_timeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_refrescarPuertos_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_2_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GUIPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUIPanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->readRequest(); break;
        case 1: _t->on_pingButton_clicked(); break;
        case 2: _t->on_runButton_clicked(); break;
        case 3: _t->on_statusButton_clicked(); break;
        case 4: _t->on_init_button_clicked(); break;
        case 5: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->on_config_carga_button_pressed(); break;
        case 7: _t->on_boton_cerrar_pressed(); break;
        case 8: _t->on_pushButton_pressed(); break;
        case 9: _t->onMQTT_Connected(); break;
        case 10: _t->onMQTT_subscribed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->onMQTT_Disconnected(); break;
        case 12: _t->onMQTT_Error((*reinterpret_cast< std::add_pointer_t<QMQTT::ClientError>>(_a[1]))); break;
        case 13: _t->startClient(); break;
        case 14: _t->on_btn_pres_asl_pressed(); break;
        case 15: _t->on_btn_temp_max_pressed(); break;
        case 16: _t->on_btn_temp_min_pressed(); break;
        case 17: _t->on_btn_hr_max_pressed(); break;
        case 18: _t->on_btn_hr_min_pressed(); break;
        case 19: _t->on_btn_pres_max_pressed(); break;
        case 20: _t->on_btn_pres_min_pressed(); break;
        case 21: _t->on_btn_acc_max_pressed(); break;
        case 22: _t->on_btn_acc_min_pressed(); break;
        case 23: _t->on_validarbtn_pressed(); break;
        case 24: _t->on_tasaCombobox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 25: _t->on_brokerConButton_pressed(); break;
        case 26: _t->on_brokerPublico_checkStateChanged((*reinterpret_cast< std::add_pointer_t<Qt::CheckState>>(_a[1]))); break;
        case 27: _t->on_acercaDeBTN_pressed(); break;
        case 28: _t->on_timer_timeout(); break;
        case 29: _t->on_timer_wait_timeout(); break;
        case 30: _t->on_refrescarPuertos_clicked(); break;
        case 31: _t->on_pushButton_2_pressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QMQTT::ClientError >(); break;
            }
            break;
        }
    }
}

const QMetaObject *GUIPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUIPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGUIPanelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GUIPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}
QT_WARNING_POP
