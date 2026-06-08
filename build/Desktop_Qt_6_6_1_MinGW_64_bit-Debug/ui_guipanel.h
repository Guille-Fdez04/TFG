/********************************************************************************
** Form generated from reading UI file 'guipanel.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIPANEL_H
#define UI_GUIPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "analogwidgets/led.h"
#include "qwt_plot.h"
#include "qwt_thermo.h"

QT_BEGIN_NAMESPACE

class Ui_GUIPanel
{
public:
    QLabel *statusLabel;
    QPushButton *statusButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    QPlainTextEdit *Txttemp;
    QPlainTextEdit *TxtHR;
    QPlainTextEdit *Txtpres;
    QwtThermo *Barra_temp;
    QwtThermo *Barra_hr;
    QwtThermo *Barra_pres;
    Led *ledtemp;
    Led *ledhr;
    Led *ledpres;
    QFrame *frame_datos_raw;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_cpu;
    QLabel *gyro_stats;
    QLabel *magneto_stats;
    QLabel *accel_stats;
    QFrame *frame_2;
    QFrame *line;
    QPlainTextEdit *TxtAlt;
    QFrame *frame_3;
    QLabel *fondo_accel;
    Led *led;
    QFrame *frame_4;
    QLabel *label;
    QLabel *inc_horiz;
    QFrame *frame_5;
    QLabel *label_2;
    QLabel *inc_frontal;
    QTextEdit *txt_estado_carga;
    QwtThermo *Thermo_ejez;
    QLCDNumber *maxG_display;
    QTextEdit *textEdit_2;
    QLineEdit *cabeceo_txt;
    QLineEdit *alabeo_txt;
    QLabel *label_3;
    QFrame *config_emergente;
    QLabel *label_4;
    QPushButton *boton_cerrar;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_5;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *txt_acc_max;
    QLabel *label_9;
    QPlainTextEdit *txt_hr_min;
    QPlainTextEdit *txt_pres_max;
    QPushButton *btn_acc_max;
    QPlainTextEdit *txt_temp_min;
    QPushButton *btn_pres_asl;
    QPushButton *btn_pres_max;
    QPushButton *btn_temp_min;
    QPushButton *btn_pres_min;
    QLabel *label_10;
    QPushButton *btn_temp_max;
    QPlainTextEdit *txt_hr_max;
    QLineEdit *txt_pres_asl;
    QPlainTextEdit *txt_pres_min;
    QPlainTextEdit *txt_temp_max;
    QPushButton *btn_acc_min;
    QPlainTextEdit *txt_acc_min;
    QPushButton *btn_hr_min;
    QPushButton *btn_hr_max;
    QLabel *label_14;
    QPushButton *validarbtn;
    QPushButton *config_carga_button;
    QPushButton *pushButton;
    QWidget *tab_2;
    QwtPlot *grafica_g;
    QGroupBox *groupBox;
    QSplitter *splitter;
    QLabel *serialPortLabel;
    QComboBox *serialPortComboBox;
    QPushButton *runButton;
    QPushButton *pingButton;
    QPushButton *init_button;
    QGroupBox *groupBox_2;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *dirMQTT;
    QLineEdit *puertoMQTT;
    QLabel *label_17;
    QLineEdit *topic_txt;
    QLabel *estado_mqtt;

    void setupUi(QWidget *GUIPanel)
    {
        if (GUIPanel->objectName().isEmpty())
            GUIPanel->setObjectName("GUIPanel");
        GUIPanel->resize(1244, 738);
        statusLabel = new QLabel(GUIPanel);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(80, 690, 281, 20));
        statusButton = new QPushButton(GUIPanel);
        statusButton->setObjectName("statusButton");
        statusButton->setGeometry(QRect(10, 690, 51, 21));
        tabWidget = new QTabWidget(GUIPanel);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 50, 1201, 621));
        tabWidget->setLayoutDirection(Qt::RightToLeft);
        tab = new QWidget();
        tab->setObjectName("tab");
        frame = new QFrame(tab);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 491, 501));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(3);
        frame->setMidLineWidth(1);
        Txttemp = new QPlainTextEdit(frame);
        Txttemp->setObjectName("Txttemp");
        Txttemp->setEnabled(true);
        Txttemp->setGeometry(QRect(40, 10, 241, 51));
        QFont font;
        font.setPointSize(16);
        Txttemp->setFont(font);
        Txttemp->setAutoFillBackground(true);
        Txttemp->setReadOnly(true);
        TxtHR = new QPlainTextEdit(frame);
        TxtHR->setObjectName("TxtHR");
        TxtHR->setEnabled(true);
        TxtHR->setGeometry(QRect(30, 180, 311, 51));
        TxtHR->setFont(font);
        TxtHR->setAutoFillBackground(false);
        TxtHR->setReadOnly(true);
        Txtpres = new QPlainTextEdit(frame);
        Txtpres->setObjectName("Txtpres");
        Txtpres->setEnabled(true);
        Txtpres->setGeometry(QRect(30, 340, 281, 51));
        Txtpres->setFont(font);
        Txtpres->setAutoFillBackground(false);
        Txtpres->setReadOnly(true);
        Barra_temp = new QwtThermo(frame);
        Barra_temp->setObjectName("Barra_temp");
        Barra_temp->setGeometry(QRect(10, 70, 471, 71));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Barra_temp->sizePolicy().hasHeightForWidth());
        Barra_temp->setSizePolicy(sizePolicy);
        Barra_temp->setLayoutDirection(Qt::LeftToRight);
        Barra_temp->setAutoFillBackground(false);
        Barra_temp->setOrientation(Qt::Horizontal);
        Barra_temp->setAlarmEnabled(true);
        Barra_temp->setAlarmLevel(100.000000000000000);
        Barra_temp->setSpacing(4);
        Barra_temp->setBorderWidth(2);
        Barra_temp->setPipeWidth(30);
        Barra_hr = new QwtThermo(frame);
        Barra_hr->setObjectName("Barra_hr");
        Barra_hr->setGeometry(QRect(10, 240, 471, 71));
        sizePolicy.setHeightForWidth(Barra_hr->sizePolicy().hasHeightForWidth());
        Barra_hr->setSizePolicy(sizePolicy);
        Barra_hr->setLayoutDirection(Qt::LeftToRight);
        Barra_hr->setAutoFillBackground(false);
        Barra_hr->setOrientation(Qt::Horizontal);
        Barra_hr->setAlarmEnabled(true);
        Barra_hr->setAlarmLevel(100.000000000000000);
        Barra_hr->setSpacing(4);
        Barra_hr->setBorderWidth(2);
        Barra_hr->setPipeWidth(30);
        Barra_hr->setValue(25.000000000000000);
        Barra_pres = new QwtThermo(frame);
        Barra_pres->setObjectName("Barra_pres");
        Barra_pres->setGeometry(QRect(10, 410, 471, 71));
        sizePolicy.setHeightForWidth(Barra_pres->sizePolicy().hasHeightForWidth());
        Barra_pres->setSizePolicy(sizePolicy);
        Barra_pres->setLayoutDirection(Qt::LeftToRight);
        Barra_pres->setAutoFillBackground(false);
        Barra_pres->setLowerBound(980.000000000000000);
        Barra_pres->setUpperBound(1100.000000000000000);
        Barra_pres->setOrientation(Qt::Horizontal);
        Barra_pres->setAlarmEnabled(true);
        Barra_pres->setAlarmLevel(40.000000000000000);
        Barra_pres->setSpacing(4);
        Barra_pres->setBorderWidth(2);
        Barra_pres->setPipeWidth(30);
        ledtemp = new Led(frame);
        ledtemp->setObjectName("ledtemp");
        ledtemp->setGeometry(QRect(390, 20, 41, 31));
        ledtemp->setColor(QColor(0, 255, 0));
        ledhr = new Led(frame);
        ledhr->setObjectName("ledhr");
        ledhr->setGeometry(QRect(380, 190, 41, 31));
        ledhr->setColor(QColor(0, 255, 0));
        ledpres = new Led(frame);
        ledpres->setObjectName("ledpres");
        ledpres->setGeometry(QRect(380, 350, 41, 31));
        ledpres->setColor(QColor(0, 255, 0));
        frame_datos_raw = new QFrame(frame);
        frame_datos_raw->setObjectName("frame_datos_raw");
        frame_datos_raw->setGeometry(QRect(10, 10, 471, 481));
        frame_datos_raw->setAutoFillBackground(true);
        frame_datos_raw->setFrameShape(QFrame::StyledPanel);
        frame_datos_raw->setFrameShadow(QFrame::Raised);
        label_11 = new QLabel(frame_datos_raw);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(100, 10, 271, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label_11->setFont(font1);
        label_11->setAlignment(Qt::AlignCenter);
        label_12 = new QLabel(frame_datos_raw);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(100, 140, 271, 31));
        label_12->setFont(font1);
        label_12->setAlignment(Qt::AlignCenter);
        label_13 = new QLabel(frame_datos_raw);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(100, 280, 271, 31));
        label_13->setFont(font1);
        label_13->setAlignment(Qt::AlignCenter);
        label_cpu = new QLabel(frame_datos_raw);
        label_cpu->setObjectName("label_cpu");
        label_cpu->setGeometry(QRect(100, 400, 271, 31));
        label_cpu->setFont(font1);
        label_cpu->setAlignment(Qt::AlignCenter);
        gyro_stats = new QLabel(frame_datos_raw);
        gyro_stats->setObjectName("gyro_stats");
        gyro_stats->setGeometry(QRect(40, 210, 401, 21));
        gyro_stats->setAlignment(Qt::AlignCenter);
        magneto_stats = new QLabel(frame_datos_raw);
        magneto_stats->setObjectName("magneto_stats");
        magneto_stats->setGeometry(QRect(20, 340, 441, 21));
        magneto_stats->setAlignment(Qt::AlignCenter);
        accel_stats = new QLabel(frame_datos_raw);
        accel_stats->setObjectName("accel_stats");
        accel_stats->setGeometry(QRect(22, 80, 441, 21));
        accel_stats->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(tab);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(490, 0, 701, 581));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Plain);
        frame_2->setLineWidth(3);
        frame_2->setMidLineWidth(1);
        line = new QFrame(frame_2);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 489, 701, 31));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(5);
        line->setFrameShape(QFrame::HLine);
        TxtAlt = new QPlainTextEdit(frame_2);
        TxtAlt->setObjectName("TxtAlt");
        TxtAlt->setGeometry(QRect(10, 520, 201, 51));
        QFont font2;
        font2.setPointSize(18);
        TxtAlt->setFont(font2);
        TxtAlt->setReadOnly(true);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(440, 10, 250, 250));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        fondo_accel = new QLabel(frame_3);
        fondo_accel->setObjectName("fondo_accel");
        fondo_accel->setGeometry(QRect(0, 0, 250, 250));
        fondo_accel->setLayoutDirection(Qt::LeftToRight);
        fondo_accel->setPixmap(QPixmap(QString::fromUtf8(":/images/Acelerometro.png")));
        fondo_accel->setScaledContents(true);
        led = new Led(frame_3);
        led->setObjectName("led");
        led->setGeometry(QRect(117, 117, 16, 16));
        led->setColor(QColor(0, 255, 0));
        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(30, 20, 200, 200));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_4);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 200, 200));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/background_inc.png")));
        label->setScaledContents(true);
        inc_horiz = new QLabel(frame_4);
        inc_horiz->setObjectName("inc_horiz");
        inc_horiz->setGeometry(QRect(0, 0, 200, 200));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(inc_horiz->sizePolicy().hasHeightForWidth());
        inc_horiz->setSizePolicy(sizePolicy1);
        inc_horiz->setPixmap(QPixmap(QString::fromUtf8(":/images/lateral_inc.png")));
        inc_horiz->setScaledContents(false);
        inc_horiz->setAlignment(Qt::AlignCenter);
        frame_5 = new QFrame(frame_2);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(30, 250, 200, 200));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame_5);
        label_2->setObjectName("label_2");
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(0, 0, 200, 200));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/background_inc.png")));
        label_2->setScaledContents(true);
        inc_frontal = new QLabel(frame_5);
        inc_frontal->setObjectName("inc_frontal");
        inc_frontal->setGeometry(QRect(0, 0, 200, 200));
        sizePolicy1.setHeightForWidth(inc_frontal->sizePolicy().hasHeightForWidth());
        inc_frontal->setSizePolicy(sizePolicy1);
        inc_frontal->setPixmap(QPixmap(QString::fromUtf8(":/images/frontal_inc.png")));
        inc_frontal->setScaledContents(false);
        inc_frontal->setAlignment(Qt::AlignCenter);
        txt_estado_carga = new QTextEdit(frame_2);
        txt_estado_carga->setObjectName("txt_estado_carga");
        txt_estado_carga->setEnabled(true);
        txt_estado_carga->setGeometry(QRect(280, 510, 411, 61));
        txt_estado_carga->setReadOnly(true);
        Thermo_ejez = new QwtThermo(frame_2);
        Thermo_ejez->setObjectName("Thermo_ejez");
        Thermo_ejez->setGeometry(QRect(470, 360, 191, 61));
        Thermo_ejez->setUpperBound(3.000000000000000);
        Thermo_ejez->setOrientation(Qt::Horizontal);
        Thermo_ejez->setAlarmEnabled(true);
        Thermo_ejez->setAlarmLevel(1.500000000000000);
        Thermo_ejez->setPipeWidth(20);
        Thermo_ejez->setValue(1.200000000000000);
        maxG_display = new QLCDNumber(frame_2);
        maxG_display->setObjectName("maxG_display");
        maxG_display->setGeometry(QRect(580, 450, 101, 41));
        maxG_display->setFrameShape(QFrame::WinPanel);
        maxG_display->setFrameShadow(QFrame::Sunken);
        maxG_display->setLineWidth(2);
        maxG_display->setSmallDecimalPoint(false);
        maxG_display->setSegmentStyle(QLCDNumber::Flat);
        maxG_display->setProperty("value", QVariant(1.200000000000000));
        textEdit_2 = new QTextEdit(frame_2);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(450, 450, 111, 41));
        cabeceo_txt = new QLineEdit(frame_2);
        cabeceo_txt->setObjectName("cabeceo_txt");
        cabeceo_txt->setGeometry(QRect(250, 100, 101, 51));
        QFont font3;
        font3.setPointSize(24);
        cabeceo_txt->setFont(font3);
        cabeceo_txt->setAlignment(Qt::AlignCenter);
        cabeceo_txt->setReadOnly(true);
        cabeceo_txt->setClearButtonEnabled(false);
        alabeo_txt = new QLineEdit(frame_2);
        alabeo_txt->setObjectName("alabeo_txt");
        alabeo_txt->setGeometry(QRect(250, 320, 101, 51));
        alabeo_txt->setFont(font3);
        alabeo_txt->setAlignment(Qt::AlignCenter);
        alabeo_txt->setReadOnly(true);
        alabeo_txt->setClearButtonEnabled(false);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(530, 310, 91, 51));
        label_3->setFont(font3);
        config_emergente = new QFrame(frame_2);
        config_emergente->setObjectName("config_emergente");
        config_emergente->setEnabled(true);
        config_emergente->setGeometry(QRect(10, 10, 681, 491));
        config_emergente->setAutoFillBackground(true);
        config_emergente->setFrameShape(QFrame::StyledPanel);
        config_emergente->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(config_emergente);
        label_4->setObjectName("label_4");
        label_4->setEnabled(true);
        label_4->setGeometry(QRect(20, 0, 361, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial")});
        font4.setPointSize(16);
        font4.setBold(true);
        font4.setItalic(true);
        label_4->setFont(font4);
        label_4->setAlignment(Qt::AlignCenter);
        boton_cerrar = new QPushButton(config_emergente);
        boton_cerrar->setObjectName("boton_cerrar");
        boton_cerrar->setGeometry(QRect(630, 0, 51, 31));
        boton_cerrar->setCheckable(false);
        boton_cerrar->setChecked(false);
        boton_cerrar->setAutoDefault(false);
        boton_cerrar->setFlat(false);
        label_6 = new QLabel(config_emergente);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 80, 81, 71));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/images/thermo.png")));
        label_6->setScaledContents(true);
        label_7 = new QLabel(config_emergente);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 160, 61, 61));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/images/humidity.png")));
        label_7->setScaledContents(true);
        label_8 = new QLabel(config_emergente);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 230, 91, 91));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/images/pressure.png")));
        label_8->setScaledContents(true);
        label_5 = new QLabel(config_emergente);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 320, 101, 91));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/images/accel.png")));
        label_5->setScaledContents(true);
        gridLayoutWidget = new QWidget(config_emergente);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(110, 40, 571, 441));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(10);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        txt_acc_max = new QPlainTextEdit(gridLayoutWidget);
        txt_acc_max->setObjectName("txt_acc_max");

        gridLayout->addWidget(txt_acc_max, 4, 3, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName("label_9");
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(true);
        label_9->setFont(font5);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 0, 3, 1, 1);

        txt_hr_min = new QPlainTextEdit(gridLayoutWidget);
        txt_hr_min->setObjectName("txt_hr_min");

        gridLayout->addWidget(txt_hr_min, 2, 1, 1, 1);

        txt_pres_max = new QPlainTextEdit(gridLayoutWidget);
        txt_pres_max->setObjectName("txt_pres_max");

        gridLayout->addWidget(txt_pres_max, 3, 3, 1, 1);

        btn_acc_max = new QPushButton(gridLayoutWidget);
        btn_acc_max->setObjectName("btn_acc_max");
        QFont font6;
        font6.setPointSize(20);
        btn_acc_max->setFont(font6);

        gridLayout->addWidget(btn_acc_max, 4, 2, 1, 1);

        txt_temp_min = new QPlainTextEdit(gridLayoutWidget);
        txt_temp_min->setObjectName("txt_temp_min");

        gridLayout->addWidget(txt_temp_min, 1, 1, 1, 1);

        btn_pres_asl = new QPushButton(gridLayoutWidget);
        btn_pres_asl->setObjectName("btn_pres_asl");
        btn_pres_asl->setFont(font6);

        gridLayout->addWidget(btn_pres_asl, 5, 2, 1, 1);

        btn_pres_max = new QPushButton(gridLayoutWidget);
        btn_pres_max->setObjectName("btn_pres_max");
        btn_pres_max->setFont(font6);

        gridLayout->addWidget(btn_pres_max, 3, 2, 1, 1);

        btn_temp_min = new QPushButton(gridLayoutWidget);
        btn_temp_min->setObjectName("btn_temp_min");
        btn_temp_min->setFont(font6);

        gridLayout->addWidget(btn_temp_min, 1, 0, 1, 1);

        btn_pres_min = new QPushButton(gridLayoutWidget);
        btn_pres_min->setObjectName("btn_pres_min");
        btn_pres_min->setFont(font6);

        gridLayout->addWidget(btn_pres_min, 3, 0, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");
        label_10->setFont(font5);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_10, 0, 1, 1, 1);

        btn_temp_max = new QPushButton(gridLayoutWidget);
        btn_temp_max->setObjectName("btn_temp_max");
        btn_temp_max->setFont(font6);

        gridLayout->addWidget(btn_temp_max, 1, 2, 1, 1);

        txt_hr_max = new QPlainTextEdit(gridLayoutWidget);
        txt_hr_max->setObjectName("txt_hr_max");

        gridLayout->addWidget(txt_hr_max, 2, 3, 1, 1);

        txt_pres_asl = new QLineEdit(gridLayoutWidget);
        txt_pres_asl->setObjectName("txt_pres_asl");

        gridLayout->addWidget(txt_pres_asl, 5, 3, 1, 1);

        txt_pres_min = new QPlainTextEdit(gridLayoutWidget);
        txt_pres_min->setObjectName("txt_pres_min");

        gridLayout->addWidget(txt_pres_min, 3, 1, 1, 1);

        txt_temp_max = new QPlainTextEdit(gridLayoutWidget);
        txt_temp_max->setObjectName("txt_temp_max");
        sizePolicy1.setHeightForWidth(txt_temp_max->sizePolicy().hasHeightForWidth());
        txt_temp_max->setSizePolicy(sizePolicy1);
        txt_temp_max->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        gridLayout->addWidget(txt_temp_max, 1, 3, 1, 1);

        btn_acc_min = new QPushButton(gridLayoutWidget);
        btn_acc_min->setObjectName("btn_acc_min");
        btn_acc_min->setFont(font6);

        gridLayout->addWidget(btn_acc_min, 4, 0, 1, 1);

        txt_acc_min = new QPlainTextEdit(gridLayoutWidget);
        txt_acc_min->setObjectName("txt_acc_min");

        gridLayout->addWidget(txt_acc_min, 4, 1, 1, 1);

        btn_hr_min = new QPushButton(gridLayoutWidget);
        btn_hr_min->setObjectName("btn_hr_min");
        btn_hr_min->setFont(font6);

        gridLayout->addWidget(btn_hr_min, 2, 0, 1, 1);

        btn_hr_max = new QPushButton(gridLayoutWidget);
        btn_hr_max->setObjectName("btn_hr_max");
        btn_hr_max->setFont(font6);

        gridLayout->addWidget(btn_hr_max, 2, 2, 1, 1);

        label_14 = new QLabel(config_emergente);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 430, 121, 31));
        QFont font7;
        font7.setPointSize(12);
        label_14->setFont(font7);
        validarbtn = new QPushButton(config_emergente);
        validarbtn->setObjectName("validarbtn");
        validarbtn->setGeometry(QRect(430, 0, 141, 31));
        QFont font8;
        font8.setPointSize(10);
        font8.setBold(true);
        validarbtn->setFont(font8);
        config_carga_button = new QPushButton(tab);
        config_carga_button->setObjectName("config_carga_button");
        config_carga_button->setGeometry(QRect(280, 500, 201, 81));
        config_carga_button->setFont(font1);
        pushButton = new QPushButton(tab);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 500, 211, 81));
        pushButton->setFont(font1);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        grafica_g = new QwtPlot(tab_2);
        grafica_g->setObjectName("grafica_g");
        grafica_g->setGeometry(QRect(50, 50, 551, 461));
        tabWidget->addTab(tab_2, QString());
        groupBox = new QGroupBox(GUIPanel);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 471, 80));
        splitter = new QSplitter(groupBox);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(20, 30, 221, 24));
        splitter->setOrientation(Qt::Horizontal);
        serialPortLabel = new QLabel(splitter);
        serialPortLabel->setObjectName("serialPortLabel");
        splitter->addWidget(serialPortLabel);
        serialPortComboBox = new QComboBox(splitter);
        serialPortComboBox->setObjectName("serialPortComboBox");
        splitter->addWidget(serialPortComboBox);
        runButton = new QPushButton(groupBox);
        runButton->setObjectName("runButton");
        runButton->setGeometry(QRect(270, 30, 98, 27));
        pingButton = new QPushButton(groupBox);
        pingButton->setObjectName("pingButton");
        pingButton->setGeometry(QRect(390, 30, 61, 27));
        init_button = new QPushButton(GUIPanel);
        init_button->setObjectName("init_button");
        init_button->setGeometry(QRect(490, 20, 151, 41));
        groupBox_2 = new QGroupBox(GUIPanel);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(440, 670, 781, 61));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(0, 30, 63, 20));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(160, 30, 81, 21));
        dirMQTT = new QLineEdit(groupBox_2);
        dirMQTT->setObjectName("dirMQTT");
        dirMQTT->setGeometry(QRect(250, 30, 181, 26));
        puertoMQTT = new QLineEdit(groupBox_2);
        puertoMQTT->setObjectName("puertoMQTT");
        puertoMQTT->setGeometry(QRect(60, 30, 71, 31));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(460, 30, 63, 20));
        topic_txt = new QLineEdit(groupBox_2);
        topic_txt->setObjectName("topic_txt");
        topic_txt->setGeometry(QRect(520, 30, 201, 26));
        estado_mqtt = new QLabel(GUIPanel);
        estado_mqtt->setObjectName("estado_mqtt");
        estado_mqtt->setGeometry(QRect(750, 20, 461, 41));
        QFont font9;
        font9.setFamilies({QString::fromUtf8("Roboto")});
        font9.setPointSize(13);
        font9.setBold(false);
        font9.setItalic(false);
        estado_mqtt->setFont(font9);
        QWidget::setTabOrder(serialPortComboBox, pingButton);
        QWidget::setTabOrder(pingButton, runButton);

        retranslateUi(GUIPanel);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GUIPanel);
    } // setupUi

    void retranslateUi(QWidget *GUIPanel)
    {
        GUIPanel->setWindowTitle(QCoreApplication::translate("GUIPanel", "GUIPanel", nullptr));
        statusLabel->setText(QCoreApplication::translate("GUIPanel", "Detenido", nullptr));
        statusButton->setText(QCoreApplication::translate("GUIPanel", "Estado:", nullptr));
        Txttemp->setPlainText(QCoreApplication::translate("GUIPanel", "Temperatura: - \302\272C", nullptr));
        TxtHR->setPlainText(QCoreApplication::translate("GUIPanel", "Humedad Relativa: - %", nullptr));
        Txtpres->setPlainText(QCoreApplication::translate("GUIPanel", "Presi\303\263n: 101325 Pa", nullptr));
#if QT_CONFIG(tooltip)
        ledtemp->setToolTip(QCoreApplication::translate("GUIPanel", "Color Led component", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        ledtemp->setWhatsThis(QCoreApplication::translate("GUIPanel", "Led indicator", nullptr));
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(tooltip)
        ledhr->setToolTip(QCoreApplication::translate("GUIPanel", "Color Led component", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        ledhr->setWhatsThis(QCoreApplication::translate("GUIPanel", "Led indicator", nullptr));
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(tooltip)
        ledpres->setToolTip(QCoreApplication::translate("GUIPanel", "Color Led component", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        ledpres->setWhatsThis(QCoreApplication::translate("GUIPanel", "Led indicator", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_11->setText(QCoreApplication::translate("GUIPanel", "Aceler\303\263metro (m/s^2): ", nullptr));
        label_12->setText(QCoreApplication::translate("GUIPanel", "Giroscopio (\302\272/s):", nullptr));
        label_13->setText(QCoreApplication::translate("GUIPanel", "Magnet\303\263metro (m/s^2): ", nullptr));
        label_cpu->setText(QCoreApplication::translate("GUIPanel", "Uso de CPU: ", nullptr));
        gyro_stats->setText(QCoreApplication::translate("GUIPanel", "TextLabel", nullptr));
        magneto_stats->setText(QCoreApplication::translate("GUIPanel", "TextLabel", nullptr));
        accel_stats->setText(QCoreApplication::translate("GUIPanel", "Eje X: 99999 Eje Y: 99999 Eje Z: 999999", nullptr));
        TxtAlt->setPlainText(QCoreApplication::translate("GUIPanel", "Altitud: -- m", nullptr));
        fondo_accel->setText(QString());
#if QT_CONFIG(tooltip)
        led->setToolTip(QCoreApplication::translate("GUIPanel", "Color Led component", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        led->setWhatsThis(QCoreApplication::translate("GUIPanel", "Led indicator", nullptr));
#endif // QT_CONFIG(whatsthis)
        label->setText(QString());
        inc_horiz->setText(QString());
        label_2->setText(QString());
        inc_frontal->setText(QString());
        txt_estado_carga->setHtml(QCoreApplication::translate("GUIPanel", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA SIN CONFIGURAR</span></p></body></html>", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("GUIPanel", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">M\303\241xima G:</span></p></body></html>", nullptr));
        cabeceo_txt->setText(QCoreApplication::translate("GUIPanel", "00\302\272", nullptr));
        alabeo_txt->setText(QCoreApplication::translate("GUIPanel", "00\302\272", nullptr));
        label_3->setText(QCoreApplication::translate("GUIPanel", "Eje Z", nullptr));
        label_4->setText(QCoreApplication::translate("GUIPanel", "CONFIGURACI\303\223N CARGA", nullptr));
        boton_cerrar->setText(QCoreApplication::translate("GUIPanel", "Cerrar", nullptr));
        label_6->setText(QString());
        label_7->setText(QString());
        label_8->setText(QString());
        label_5->setText(QString());
        label_9->setText(QCoreApplication::translate("GUIPanel", "VALOR M\303\201XIMO", nullptr));
        btn_acc_max->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_pres_asl->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_pres_max->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_temp_min->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_pres_min->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        label_10->setText(QCoreApplication::translate("GUIPanel", "VALOR M\303\215NIMO", nullptr));
        btn_temp_max->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_acc_min->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_hr_min->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_hr_max->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        label_14->setText(QCoreApplication::translate("GUIPanel", "P ASL (hPa)", nullptr));
        validarbtn->setText(QCoreApplication::translate("GUIPanel", "VALIDAR TODO", nullptr));
        config_carga_button->setText(QCoreApplication::translate("GUIPanel", "Configurar carga", nullptr));
        pushButton->setText(QCoreApplication::translate("GUIPanel", "Datos en crudo", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("GUIPanel", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("GUIPanel", "Page", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GUIPanel", "Conexi\303\263n USB", nullptr));
        serialPortLabel->setText(QCoreApplication::translate("GUIPanel", "Puerto Serie:", nullptr));
        runButton->setText(QCoreApplication::translate("GUIPanel", "Inicio", nullptr));
        pingButton->setText(QCoreApplication::translate("GUIPanel", "Ping", nullptr));
        init_button->setText(QCoreApplication::translate("GUIPanel", "Conectar Aplicaci\303\263n", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("GUIPanel", "Configuraci\303\263n MQTT", nullptr));
        label_15->setText(QCoreApplication::translate("GUIPanel", "Puerto:", nullptr));
        label_16->setText(QCoreApplication::translate("GUIPanel", "Direcci\303\263n:", nullptr));
        dirMQTT->setText(QCoreApplication::translate("GUIPanel", "localhost", nullptr));
        puertoMQTT->setText(QCoreApplication::translate("GUIPanel", "1883", nullptr));
        label_17->setText(QCoreApplication::translate("GUIPanel", "Topic:", nullptr));
        topic_txt->setText(QCoreApplication::translate("GUIPanel", "carga", nullptr));
        estado_mqtt->setText(QCoreApplication::translate("GUIPanel", "ESTADO MQTT: DESCONECTADO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIPanel: public Ui_GUIPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIPANEL_H
