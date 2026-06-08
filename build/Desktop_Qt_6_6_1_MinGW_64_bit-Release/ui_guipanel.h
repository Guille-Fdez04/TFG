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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "analogwidgets/led.h"
#include "qwt_thermo.h"

QT_BEGIN_NAMESPACE

class Ui_GUIPanel
{
public:
    QFrame *frame_datos_raw;
    QVBoxLayout *verticalLayout;
    QLabel *label_11;
    QLabel *accel_stats;
    QLabel *label_12;
    QLabel *gyro_stats;
    QLabel *label_13;
    QLabel *magneto_stats;
    QLabel *label_cpu;
    QFrame *line_2;
    QLabel *estado_mqtt;
    QFrame *config_emergente;
    QLabel *label_4;
    QPushButton *boton_cerrar;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_5;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *btn_pres_asl;
    QPlainTextEdit *txt_pres_min;
    QPlainTextEdit *txt_pres_max;
    QPushButton *btn_acc_max;
    QPlainTextEdit *txt_hr_max;
    QPushButton *btn_pres_max;
    QPushButton *btn_pres_min;
    QLineEdit *txt_pres_asl;
    QPushButton *btn_hr_max;
    QPlainTextEdit *txt_temp_min;
    QPlainTextEdit *txt_hr_min;
    QPushButton *btn_acc_min;
    QPlainTextEdit *txt_acc_max;
    QPlainTextEdit *txt_acc_min;
    QPlainTextEdit *txt_temp_max;
    QPushButton *btn_hr_min;
    QPushButton *btn_temp_min;
    QPushButton *btn_temp_max;
    QLabel *label_14;
    QPushButton *validarbtn;
    QLabel *label_10;
    QLabel *label_9;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QSplitter *splitter;
    QLabel *serialPortLabel;
    QComboBox *serialPortComboBox;
    QPushButton *refrescarPuertos;
    QPushButton *runButton;
    QPushButton *pingButton;
    QGridLayout *grid_superior;
    QLabel *label_20;
    QPushButton *acercaDeBTN;
    QLineEdit *usuario;
    QPushButton *brokerConButton;
    QLineEdit *contrasenia;
    QComboBox *tasaCombobox;
    QLabel *label_19;
    QCheckBox *publicBrokerCheck;
    QLabel *label_21;
    QPushButton *init_button;
    QPushButton *pushButton_2;
    QFormLayout *ventanas;
    QFrame *ventana_izq;
    QGridLayout *gridLayout_2;
    QLabel *Txttemp;
    Led *ledpres;
    QwtThermo *Barra_pres;
    QLabel *Txtpres;
    Led *ledtemp;
    Led *ledhr;
    QLabel *TxtHR;
    QwtThermo *Barra_temp;
    QwtThermo *Barra_hr;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *config_carga_button;
    QFrame *ventana_der;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLCDNumber *maxG_display;
    QFrame *frame_3;
    QLabel *fondo_accel;
    Led *led;
    QLabel *label_18;
    QFrame *frame_4;
    QLabel *label;
    QLabel *inc_horiz;
    QFrame *frame_5;
    QLabel *label_2;
    QLabel *inc_frontal;
    QwtThermo *Thermo_ejez;
    QFrame *line;
    QPlainTextEdit *TxtAlt;
    QTextEdit *txt_estado_carga;
    QLineEdit *alabeo_txt;
    QLineEdit *cabeceo_txt;
    QHBoxLayout *horizontalLayout;
    QPushButton *statusButton;
    QLabel *statusLabel;
    QGroupBox *groupBox_2;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *dirMQTT;
    QLineEdit *puertoMQTT;
    QLabel *label_17;
    QLineEdit *topic_txt;

    void setupUi(QWidget *GUIPanel)
    {
        if (GUIPanel->objectName().isEmpty())
            GUIPanel->setObjectName("GUIPanel");
        GUIPanel->resize(1220, 772);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GUIPanel->sizePolicy().hasHeightForWidth());
        GUIPanel->setSizePolicy(sizePolicy);
        GUIPanel->setMinimumSize(QSize(1220, 772));
        GUIPanel->setMaximumSize(QSize(1220, 772));
        frame_datos_raw = new QFrame(GUIPanel);
        frame_datos_raw->setObjectName("frame_datos_raw");
        frame_datos_raw->setGeometry(QRect(6, 110, 486, 471));
        frame_datos_raw->setAutoFillBackground(true);
        frame_datos_raw->setFrameShape(QFrame::StyledPanel);
        frame_datos_raw->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_datos_raw);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        label_11 = new QLabel(frame_datos_raw);
        label_11->setObjectName("label_11");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_11);

        accel_stats = new QLabel(frame_datos_raw);
        accel_stats->setObjectName("accel_stats");
        accel_stats->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(accel_stats);

        label_12 = new QLabel(frame_datos_raw);
        label_12->setObjectName("label_12");
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_12);

        gyro_stats = new QLabel(frame_datos_raw);
        gyro_stats->setObjectName("gyro_stats");
        gyro_stats->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(gyro_stats);

        label_13 = new QLabel(frame_datos_raw);
        label_13->setObjectName("label_13");
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_13);

        magneto_stats = new QLabel(frame_datos_raw);
        magneto_stats->setObjectName("magneto_stats");
        magneto_stats->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(magneto_stats);

        label_cpu = new QLabel(frame_datos_raw);
        label_cpu->setObjectName("label_cpu");
        label_cpu->setFont(font);
        label_cpu->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_cpu);

        line_2 = new QFrame(frame_datos_raw);
        line_2->setObjectName("line_2");
        line_2->setFrameShadow(QFrame::Raised);
        line_2->setLineWidth(4);
        line_2->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line_2);

        estado_mqtt = new QLabel(frame_datos_raw);
        estado_mqtt->setObjectName("estado_mqtt");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Roboto")});
        font1.setPointSize(13);
        font1.setBold(false);
        font1.setItalic(false);
        estado_mqtt->setFont(font1);

        verticalLayout->addWidget(estado_mqtt);

        config_emergente = new QFrame(GUIPanel);
        config_emergente->setObjectName("config_emergente");
        config_emergente->setEnabled(true);
        config_emergente->setGeometry(QRect(520, 110, 691, 481));
        config_emergente->setMinimumSize(QSize(600, 0));
        config_emergente->setMaximumSize(QSize(800, 16777215));
        config_emergente->setAutoFillBackground(true);
        config_emergente->setFrameShape(QFrame::StyledPanel);
        config_emergente->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(config_emergente);
        label_4->setObjectName("label_4");
        label_4->setEnabled(true);
        label_4->setGeometry(QRect(20, 0, 361, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setItalic(true);
        label_4->setFont(font2);
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
        label_8->setGeometry(QRect(8, 230, 91, 91));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/images/pressure.png")));
        label_8->setScaledContents(true);
        label_5 = new QLabel(config_emergente);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(4, 320, 101, 91));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/images/accel.png")));
        label_5->setScaledContents(true);
        gridLayoutWidget = new QWidget(config_emergente);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(50, 60, 631, 441));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btn_pres_asl = new QPushButton(gridLayoutWidget);
        btn_pres_asl->setObjectName("btn_pres_asl");
        btn_pres_asl->setMinimumSize(QSize(30, 30));
        btn_pres_asl->setMaximumSize(QSize(30, 30));
        QFont font3;
        font3.setPointSize(10);
        btn_pres_asl->setFont(font3);

        gridLayout->addWidget(btn_pres_asl, 4, 1, 1, 1);

        txt_pres_min = new QPlainTextEdit(gridLayoutWidget);
        txt_pres_min->setObjectName("txt_pres_min");
        txt_pres_min->setMinimumSize(QSize(100, 50));
        txt_pres_min->setMaximumSize(QSize(100, 50));

        gridLayout->addWidget(txt_pres_min, 2, 0, 1, 1);

        txt_pres_max = new QPlainTextEdit(gridLayoutWidget);
        txt_pres_max->setObjectName("txt_pres_max");
        txt_pres_max->setMinimumSize(QSize(100, 50));
        txt_pres_max->setMaximumSize(QSize(100, 50));

        gridLayout->addWidget(txt_pres_max, 2, 2, 1, 1);

        btn_acc_max = new QPushButton(gridLayoutWidget);
        btn_acc_max->setObjectName("btn_acc_max");
        btn_acc_max->setMinimumSize(QSize(30, 30));
        btn_acc_max->setMaximumSize(QSize(30, 30));
        btn_acc_max->setFont(font3);

        gridLayout->addWidget(btn_acc_max, 3, 3, 1, 1);

        txt_hr_max = new QPlainTextEdit(gridLayoutWidget);
        txt_hr_max->setObjectName("txt_hr_max");
        txt_hr_max->setMinimumSize(QSize(100, 50));
        txt_hr_max->setMaximumSize(QSize(100, 50));

        gridLayout->addWidget(txt_hr_max, 1, 2, 1, 1);

        btn_pres_max = new QPushButton(gridLayoutWidget);
        btn_pres_max->setObjectName("btn_pres_max");
        btn_pres_max->setMinimumSize(QSize(30, 30));
        btn_pres_max->setMaximumSize(QSize(30, 30));
        btn_pres_max->setFont(font3);

        gridLayout->addWidget(btn_pres_max, 2, 3, 1, 1);

        btn_pres_min = new QPushButton(gridLayoutWidget);
        btn_pres_min->setObjectName("btn_pres_min");
        btn_pres_min->setMinimumSize(QSize(30, 30));
        btn_pres_min->setMaximumSize(QSize(30, 30));
        btn_pres_min->setFont(font3);

        gridLayout->addWidget(btn_pres_min, 2, 1, 1, 1);

        txt_pres_asl = new QLineEdit(gridLayoutWidget);
        txt_pres_asl->setObjectName("txt_pres_asl");
        txt_pres_asl->setMinimumSize(QSize(100, 30));
        txt_pres_asl->setMaximumSize(QSize(100, 30));

        gridLayout->addWidget(txt_pres_asl, 4, 0, 1, 1);

        btn_hr_max = new QPushButton(gridLayoutWidget);
        btn_hr_max->setObjectName("btn_hr_max");
        btn_hr_max->setMinimumSize(QSize(30, 30));
        btn_hr_max->setMaximumSize(QSize(30, 30));
        btn_hr_max->setFont(font3);

        gridLayout->addWidget(btn_hr_max, 1, 3, 1, 1);

        txt_temp_min = new QPlainTextEdit(gridLayoutWidget);
        txt_temp_min->setObjectName("txt_temp_min");
        txt_temp_min->setMinimumSize(QSize(100, 50));
        txt_temp_min->setMaximumSize(QSize(100, 50));

        gridLayout->addWidget(txt_temp_min, 0, 0, 1, 1);

        txt_hr_min = new QPlainTextEdit(gridLayoutWidget);
        txt_hr_min->setObjectName("txt_hr_min");
        txt_hr_min->setMinimumSize(QSize(100, 50));
        txt_hr_min->setMaximumSize(QSize(100, 50));

        gridLayout->addWidget(txt_hr_min, 1, 0, 1, 1);

        btn_acc_min = new QPushButton(gridLayoutWidget);
        btn_acc_min->setObjectName("btn_acc_min");
        btn_acc_min->setMinimumSize(QSize(30, 30));
        btn_acc_min->setMaximumSize(QSize(30, 30));
        btn_acc_min->setFont(font3);

        gridLayout->addWidget(btn_acc_min, 3, 1, 1, 1);

        txt_acc_max = new QPlainTextEdit(gridLayoutWidget);
        txt_acc_max->setObjectName("txt_acc_max");
        txt_acc_max->setMinimumSize(QSize(100, 50));
        txt_acc_max->setMaximumSize(QSize(100, 50));

        gridLayout->addWidget(txt_acc_max, 3, 2, 1, 1);

        txt_acc_min = new QPlainTextEdit(gridLayoutWidget);
        txt_acc_min->setObjectName("txt_acc_min");
        txt_acc_min->setMinimumSize(QSize(100, 50));
        txt_acc_min->setMaximumSize(QSize(100, 50));

        gridLayout->addWidget(txt_acc_min, 3, 0, 1, 1);

        txt_temp_max = new QPlainTextEdit(gridLayoutWidget);
        txt_temp_max->setObjectName("txt_temp_max");
        sizePolicy.setHeightForWidth(txt_temp_max->sizePolicy().hasHeightForWidth());
        txt_temp_max->setSizePolicy(sizePolicy);
        txt_temp_max->setMinimumSize(QSize(100, 50));
        txt_temp_max->setMaximumSize(QSize(100, 50));
        txt_temp_max->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        gridLayout->addWidget(txt_temp_max, 0, 2, 1, 1);

        btn_hr_min = new QPushButton(gridLayoutWidget);
        btn_hr_min->setObjectName("btn_hr_min");
        btn_hr_min->setMinimumSize(QSize(30, 30));
        btn_hr_min->setMaximumSize(QSize(30, 30));
        btn_hr_min->setFont(font3);

        gridLayout->addWidget(btn_hr_min, 1, 1, 1, 1);

        btn_temp_min = new QPushButton(gridLayoutWidget);
        btn_temp_min->setObjectName("btn_temp_min");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_temp_min->sizePolicy().hasHeightForWidth());
        btn_temp_min->setSizePolicy(sizePolicy1);
        btn_temp_min->setMinimumSize(QSize(30, 30));
        btn_temp_min->setMaximumSize(QSize(30, 30));
        btn_temp_min->setFont(font3);

        gridLayout->addWidget(btn_temp_min, 0, 1, 1, 1);

        btn_temp_max = new QPushButton(gridLayoutWidget);
        btn_temp_max->setObjectName("btn_temp_max");
        btn_temp_max->setMinimumSize(QSize(30, 30));
        btn_temp_max->setMaximumSize(QSize(30, 30));
        btn_temp_max->setFont(font3);

        gridLayout->addWidget(btn_temp_max, 0, 3, 1, 1);

        label_14 = new QLabel(config_emergente);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 430, 121, 31));
        QFont font4;
        font4.setPointSize(12);
        label_14->setFont(font4);
        validarbtn = new QPushButton(config_emergente);
        validarbtn->setObjectName("validarbtn");
        validarbtn->setGeometry(QRect(430, 0, 141, 31));
        QFont font5;
        font5.setPointSize(10);
        font5.setBold(true);
        validarbtn->setFont(font5);
        label_10 = new QLabel(config_emergente);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(100, 40, 239, 27));
        QFont font6;
        font6.setPointSize(12);
        font6.setBold(true);
        label_10->setFont(font6);
        label_10->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(config_emergente);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(400, 40, 240, 27));
        label_9->setFont(font6);
        label_9->setAlignment(Qt::AlignCenter);
        gridLayout_5 = new QGridLayout(GUIPanel);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setHorizontalSpacing(0);
        gridLayout_5->setVerticalSpacing(2);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        groupBox = new QGroupBox(GUIPanel);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(400, 80));
        groupBox->setMaximumSize(QSize(400, 80));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setHorizontalSpacing(0);
        gridLayout_4->setVerticalSpacing(4);
        gridLayout_4->setContentsMargins(2, 0, 2, 4);
        splitter = new QSplitter(groupBox);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        serialPortLabel = new QLabel(splitter);
        serialPortLabel->setObjectName("serialPortLabel");
        serialPortLabel->setMinimumSize(QSize(100, 30));
        serialPortLabel->setMaximumSize(QSize(100, 30));
        splitter->addWidget(serialPortLabel);
        serialPortComboBox = new QComboBox(splitter);
        serialPortComboBox->setObjectName("serialPortComboBox");
        serialPortComboBox->setMinimumSize(QSize(105, 30));
        serialPortComboBox->setMaximumSize(QSize(105, 30));
        splitter->addWidget(serialPortComboBox);

        gridLayout_4->addWidget(splitter, 0, 0, 2, 1);

        refrescarPuertos = new QPushButton(groupBox);
        refrescarPuertos->setObjectName("refrescarPuertos");
        refrescarPuertos->setMinimumSize(QSize(30, 30));
        refrescarPuertos->setMaximumSize(QSize(30, 30));
        refrescarPuertos->setText(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/159061.png"), QSize(), QIcon::Normal, QIcon::Off);
        refrescarPuertos->setIcon(icon);

        gridLayout_4->addWidget(refrescarPuertos, 0, 1, 2, 1);

        runButton = new QPushButton(groupBox);
        runButton->setObjectName("runButton");
        runButton->setMinimumSize(QSize(110, 30));
        runButton->setMaximumSize(QSize(110, 30));

        gridLayout_4->addWidget(runButton, 0, 2, 1, 1);

        pingButton = new QPushButton(groupBox);
        pingButton->setObjectName("pingButton");
        pingButton->setMinimumSize(QSize(110, 30));
        pingButton->setMaximumSize(QSize(110, 30));

        gridLayout_4->addWidget(pingButton, 1, 2, 1, 1);


        horizontalLayout_3->addWidget(groupBox);

        grid_superior = new QGridLayout();
        grid_superior->setSpacing(6);
        grid_superior->setObjectName("grid_superior");
        label_20 = new QLabel(GUIPanel);
        label_20->setObjectName("label_20");
        label_20->setMinimumSize(QSize(120, 30));
        label_20->setMaximumSize(QSize(120, 30));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Roboto")});
        font7.setPointSize(10);
        label_20->setFont(font7);

        grid_superior->addWidget(label_20, 1, 1, 1, 1);

        acercaDeBTN = new QPushButton(GUIPanel);
        acercaDeBTN->setObjectName("acercaDeBTN");
        acercaDeBTN->setMinimumSize(QSize(80, 30));
        acercaDeBTN->setMaximumSize(QSize(80, 30));

        grid_superior->addWidget(acercaDeBTN, 0, 5, 1, 1);

        usuario = new QLineEdit(GUIPanel);
        usuario->setObjectName("usuario");
        usuario->setMinimumSize(QSize(150, 30));
        usuario->setMaximumSize(QSize(150, 30));

        grid_superior->addWidget(usuario, 0, 2, 1, 1);

        brokerConButton = new QPushButton(GUIPanel);
        brokerConButton->setObjectName("brokerConButton");
        brokerConButton->setMinimumSize(QSize(150, 40));
        brokerConButton->setMaximumSize(QSize(150, 40));

        grid_superior->addWidget(brokerConButton, 1, 0, 1, 1);

        contrasenia = new QLineEdit(GUIPanel);
        contrasenia->setObjectName("contrasenia");
        contrasenia->setMinimumSize(QSize(150, 30));
        contrasenia->setMaximumSize(QSize(150, 30));

        grid_superior->addWidget(contrasenia, 0, 4, 1, 1);

        tasaCombobox = new QComboBox(GUIPanel);
        tasaCombobox->setObjectName("tasaCombobox");
        tasaCombobox->setMinimumSize(QSize(60, 30));
        tasaCombobox->setMaximumSize(QSize(60, 30));

        grid_superior->addWidget(tasaCombobox, 1, 2, 1, 1);

        label_19 = new QLabel(GUIPanel);
        label_19->setObjectName("label_19");
        label_19->setMinimumSize(QSize(110, 30));
        label_19->setMaximumSize(QSize(110, 30));
        label_19->setFont(font7);

        grid_superior->addWidget(label_19, 0, 1, 1, 1);

        publicBrokerCheck = new QCheckBox(GUIPanel);
        publicBrokerCheck->setObjectName("publicBrokerCheck");
        publicBrokerCheck->setMinimumSize(QSize(130, 30));
        publicBrokerCheck->setMaximumSize(QSize(130, 30));
        publicBrokerCheck->setChecked(false);

        grid_superior->addWidget(publicBrokerCheck, 1, 3, 1, 1);

        label_21 = new QLabel(GUIPanel);
        label_21->setObjectName("label_21");
        label_21->setMinimumSize(QSize(100, 30));
        label_21->setMaximumSize(QSize(100, 30));
        label_21->setFont(font7);

        grid_superior->addWidget(label_21, 0, 3, 1, 1);

        init_button = new QPushButton(GUIPanel);
        init_button->setObjectName("init_button");
        init_button->setMinimumSize(QSize(150, 40));
        init_button->setMaximumSize(QSize(150, 40));

        grid_superior->addWidget(init_button, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(GUIPanel);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(50, 30));
        pushButton_2->setMaximumSize(QSize(50, 30));
        pushButton_2->setLayoutDirection(Qt::LeftToRight);

        grid_superior->addWidget(pushButton_2, 1, 5, 1, 1);


        horizontalLayout_3->addLayout(grid_superior);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        ventanas = new QFormLayout();
        ventanas->setSpacing(6);
        ventanas->setObjectName("ventanas");
        ventana_izq = new QFrame(GUIPanel);
        ventana_izq->setObjectName("ventana_izq");
        ventana_izq->setMinimumSize(QSize(500, 600));
        ventana_izq->setMaximumSize(QSize(500, 600));
        ventana_izq->setFrameShape(QFrame::Box);
        ventana_izq->setFrameShadow(QFrame::Sunken);
        ventana_izq->setLineWidth(3);
        ventana_izq->setMidLineWidth(1);
        gridLayout_2 = new QGridLayout(ventana_izq);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setHorizontalSpacing(7);
        gridLayout_2->setVerticalSpacing(20);
        gridLayout_2->setContentsMargins(0, 0, 3, 0);
        Txttemp = new QLabel(ventana_izq);
        Txttemp->setObjectName("Txttemp");
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Roboto")});
        font8.setPointSize(16);
        Txttemp->setFont(font8);

        gridLayout_2->addWidget(Txttemp, 0, 0, 1, 1);

        ledpres = new Led(ventana_izq);
        ledpres->setObjectName("ledpres");
        ledpres->setMaximumSize(QSize(16777215, 30));
        ledpres->setColor(QColor(0, 255, 0));

        gridLayout_2->addWidget(ledpres, 4, 1, 1, 1);

        Barra_pres = new QwtThermo(ventana_izq);
        Barra_pres->setObjectName("Barra_pres");
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Barra_pres->sizePolicy().hasHeightForWidth());
        Barra_pres->setSizePolicy(sizePolicy2);
        Barra_pres->setLayoutDirection(Qt::LeftToRight);
        Barra_pres->setAutoFillBackground(false);
        Barra_pres->setLowerBound(940.000000000000000);
        Barra_pres->setUpperBound(1200.000000000000000);
        Barra_pres->setOrientation(Qt::Horizontal);
        Barra_pres->setAlarmEnabled(true);
        Barra_pres->setAlarmLevel(40.000000000000000);
        Barra_pres->setSpacing(4);
        Barra_pres->setBorderWidth(2);
        Barra_pres->setPipeWidth(30);
        Barra_pres->setValue(1013.000000000000000);

        gridLayout_2->addWidget(Barra_pres, 5, 0, 1, 2);

        Txtpres = new QLabel(ventana_izq);
        Txtpres->setObjectName("Txtpres");
        Txtpres->setFont(font8);

        gridLayout_2->addWidget(Txtpres, 4, 0, 1, 1);

        ledtemp = new Led(ventana_izq);
        ledtemp->setObjectName("ledtemp");
        ledtemp->setMaximumSize(QSize(50, 30));
        ledtemp->setColor(QColor(0, 255, 0));

        gridLayout_2->addWidget(ledtemp, 0, 1, 1, 1);

        ledhr = new Led(ventana_izq);
        ledhr->setObjectName("ledhr");
        ledhr->setMaximumSize(QSize(16777215, 30));
        ledhr->setColor(QColor(0, 255, 0));

        gridLayout_2->addWidget(ledhr, 2, 1, 1, 1);

        TxtHR = new QLabel(ventana_izq);
        TxtHR->setObjectName("TxtHR");
        TxtHR->setFont(font8);

        gridLayout_2->addWidget(TxtHR, 2, 0, 1, 1);

        Barra_temp = new QwtThermo(ventana_izq);
        Barra_temp->setObjectName("Barra_temp");
        sizePolicy2.setHeightForWidth(Barra_temp->sizePolicy().hasHeightForWidth());
        Barra_temp->setSizePolicy(sizePolicy2);
        Barra_temp->setLayoutDirection(Qt::LeftToRight);
        Barra_temp->setAutoFillBackground(false);
        Barra_temp->setOrientation(Qt::Horizontal);
        Barra_temp->setAlarmEnabled(true);
        Barra_temp->setAlarmLevel(100.000000000000000);
        Barra_temp->setSpacing(4);
        Barra_temp->setBorderWidth(2);
        Barra_temp->setPipeWidth(30);
        Barra_temp->setValue(20.500000000000000);

        gridLayout_2->addWidget(Barra_temp, 1, 0, 1, 2);

        Barra_hr = new QwtThermo(ventana_izq);
        Barra_hr->setObjectName("Barra_hr");
        sizePolicy2.setHeightForWidth(Barra_hr->sizePolicy().hasHeightForWidth());
        Barra_hr->setSizePolicy(sizePolicy2);
        Barra_hr->setLayoutDirection(Qt::LeftToRight);
        Barra_hr->setAutoFillBackground(false);
        Barra_hr->setOrientation(Qt::Horizontal);
        Barra_hr->setAlarmEnabled(true);
        Barra_hr->setAlarmLevel(100.000000000000000);
        Barra_hr->setSpacing(4);
        Barra_hr->setBorderWidth(2);
        Barra_hr->setPipeWidth(30);
        Barra_hr->setValue(30.000000000000000);

        gridLayout_2->addWidget(Barra_hr, 3, 0, 1, 2);

        frame = new QFrame(ventana_izq);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(500, 100));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(80);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy3);
        pushButton->setMinimumSize(QSize(200, 80));
        pushButton->setMaximumSize(QSize(200, 80));
        pushButton->setFont(font);
        pushButton->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_2->addWidget(pushButton);

        config_carga_button = new QPushButton(frame);
        config_carga_button->setObjectName("config_carga_button");
        sizePolicy3.setHeightForWidth(config_carga_button->sizePolicy().hasHeightForWidth());
        config_carga_button->setSizePolicy(sizePolicy3);
        config_carga_button->setMinimumSize(QSize(200, 80));
        config_carga_button->setMaximumSize(QSize(200, 80));
        config_carga_button->setFont(font);
        config_carga_button->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_2->addWidget(config_carga_button);


        gridLayout_2->addWidget(frame, 6, 0, 1, 2);


        ventanas->setWidget(0, QFormLayout::LabelRole, ventana_izq);

        ventana_der = new QFrame(GUIPanel);
        ventana_der->setObjectName("ventana_der");
        ventana_der->setMinimumSize(QSize(500, 600));
        ventana_der->setMaximumSize(QSize(800, 600));
        ventana_der->setFrameShape(QFrame::Box);
        ventana_der->setFrameShadow(QFrame::Plain);
        ventana_der->setLineWidth(3);
        ventana_der->setMidLineWidth(1);
        gridLayout_3 = new QGridLayout(ventana_der);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        label_3 = new QLabel(ventana_der);
        label_3->setObjectName("label_3");
        QFont font9;
        font9.setPointSize(24);
        label_3->setFont(font9);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 2, 3, 1, 2);

        maxG_display = new QLCDNumber(ventana_der);
        maxG_display->setObjectName("maxG_display");
        maxG_display->setMinimumSize(QSize(0, 45));
        maxG_display->setFrameShape(QFrame::WinPanel);
        maxG_display->setFrameShadow(QFrame::Sunken);
        maxG_display->setLineWidth(2);
        maxG_display->setSmallDecimalPoint(false);
        maxG_display->setSegmentStyle(QLCDNumber::Flat);
        maxG_display->setProperty("value", QVariant(0.000000000000000));

        gridLayout_3->addWidget(maxG_display, 4, 4, 1, 1);

        frame_3 = new QFrame(ventana_der);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(250, 250));
        frame_3->setMaximumSize(QSize(250, 250));
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

        gridLayout_3->addWidget(frame_3, 0, 3, 2, 2);

        label_18 = new QLabel(ventana_der);
        label_18->setObjectName("label_18");
        QFont font10;
        font10.setFamilies({QString::fromUtf8("Roboto")});
        font10.setPointSize(14);
        label_18->setFont(font10);

        gridLayout_3->addWidget(label_18, 4, 3, 1, 1);

        frame_4 = new QFrame(ventana_der);
        frame_4->setObjectName("frame_4");
        frame_4->setMinimumSize(QSize(200, 200));
        frame_4->setMaximumSize(QSize(200, 200));
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
        sizePolicy.setHeightForWidth(inc_horiz->sizePolicy().hasHeightForWidth());
        inc_horiz->setSizePolicy(sizePolicy);
        inc_horiz->setPixmap(QPixmap(QString::fromUtf8(":/images/lateral_inc.png")));
        inc_horiz->setScaledContents(false);
        inc_horiz->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(frame_4, 0, 0, 1, 1);

        frame_5 = new QFrame(ventana_der);
        frame_5->setObjectName("frame_5");
        frame_5->setMinimumSize(QSize(200, 200));
        frame_5->setMaximumSize(QSize(200, 200));
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
        sizePolicy.setHeightForWidth(inc_frontal->sizePolicy().hasHeightForWidth());
        inc_frontal->setSizePolicy(sizePolicy);
        inc_frontal->setPixmap(QPixmap(QString::fromUtf8(":/images/frontal_inc.png")));
        inc_frontal->setScaledContents(false);
        inc_frontal->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(frame_5, 1, 0, 3, 1);

        Thermo_ejez = new QwtThermo(ventana_der);
        Thermo_ejez->setObjectName("Thermo_ejez");
        Thermo_ejez->setLowerBound(-3.000000000000000);
        Thermo_ejez->setUpperBound(3.000000000000000);
        Thermo_ejez->setOrientation(Qt::Horizontal);
        Thermo_ejez->setAlarmEnabled(true);
        Thermo_ejez->setAlarmLevel(1.500000000000000);
        Thermo_ejez->setPipeWidth(20);
        Thermo_ejez->setValue(1.200000000000000);

        gridLayout_3->addWidget(Thermo_ejez, 3, 3, 1, 2);

        line = new QFrame(ventana_der);
        line->setObjectName("line");
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(5);
        line->setFrameShape(QFrame::HLine);

        gridLayout_3->addWidget(line, 5, 0, 2, 5);

        TxtAlt = new QPlainTextEdit(ventana_der);
        TxtAlt->setObjectName("TxtAlt");
        sizePolicy1.setHeightForWidth(TxtAlt->sizePolicy().hasHeightForWidth());
        TxtAlt->setSizePolicy(sizePolicy1);
        TxtAlt->setMinimumSize(QSize(200, 60));
        TxtAlt->setMaximumSize(QSize(200, 60));
        QFont font11;
        font11.setPointSize(18);
        TxtAlt->setFont(font11);
        TxtAlt->setReadOnly(true);

        gridLayout_3->addWidget(TxtAlt, 8, 0, 1, 1);

        txt_estado_carga = new QTextEdit(ventana_der);
        txt_estado_carga->setObjectName("txt_estado_carga");
        txt_estado_carga->setEnabled(true);
        sizePolicy1.setHeightForWidth(txt_estado_carga->sizePolicy().hasHeightForWidth());
        txt_estado_carga->setSizePolicy(sizePolicy1);
        txt_estado_carga->setMinimumSize(QSize(470, 60));
        txt_estado_carga->setMaximumSize(QSize(470, 60));
        txt_estado_carga->setLayoutDirection(Qt::LeftToRight);
        txt_estado_carga->setReadOnly(true);

        gridLayout_3->addWidget(txt_estado_carga, 8, 2, 1, 1);

        alabeo_txt = new QLineEdit(ventana_der);
        alabeo_txt->setObjectName("alabeo_txt");
        alabeo_txt->setMaximumSize(QSize(120, 16777215));
        alabeo_txt->setFont(font9);
        alabeo_txt->setAlignment(Qt::AlignCenter);
        alabeo_txt->setReadOnly(true);
        alabeo_txt->setClearButtonEnabled(false);

        gridLayout_3->addWidget(alabeo_txt, 2, 2, 1, 1);

        cabeceo_txt = new QLineEdit(ventana_der);
        cabeceo_txt->setObjectName("cabeceo_txt");
        cabeceo_txt->setMaximumSize(QSize(120, 16777215));
        cabeceo_txt->setFont(font9);
        cabeceo_txt->setAlignment(Qt::AlignCenter);
        cabeceo_txt->setReadOnly(true);
        cabeceo_txt->setClearButtonEnabled(false);

        gridLayout_3->addWidget(cabeceo_txt, 0, 2, 1, 1);

        label_18->raise();
        line->raise();
        frame_3->raise();
        frame_4->raise();
        frame_5->raise();
        Thermo_ejez->raise();
        maxG_display->raise();
        cabeceo_txt->raise();
        label_3->raise();
        TxtAlt->raise();
        txt_estado_carga->raise();
        alabeo_txt->raise();

        ventanas->setWidget(0, QFormLayout::FieldRole, ventana_der);


        gridLayout_5->addLayout(ventanas, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, -1, -1, 4);
        statusButton = new QPushButton(GUIPanel);
        statusButton->setObjectName("statusButton");
        sizePolicy1.setHeightForWidth(statusButton->sizePolicy().hasHeightForWidth());
        statusButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(statusButton);

        statusLabel = new QLabel(GUIPanel);
        statusLabel->setObjectName("statusLabel");
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(statusLabel);

        groupBox_2 = new QGroupBox(GUIPanel);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMinimumSize(QSize(781, 61));
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
        label_17->setGeometry(QRect(450, 30, 63, 20));
        topic_txt = new QLineEdit(groupBox_2);
        topic_txt->setObjectName("topic_txt");
        topic_txt->setGeometry(QRect(520, 30, 201, 26));

        horizontalLayout->addWidget(groupBox_2);


        gridLayout_5->addLayout(horizontalLayout, 2, 0, 1, 1);

        config_emergente->raise();
        frame_datos_raw->raise();
        QWidget::setTabOrder(serialPortComboBox, pingButton);
        QWidget::setTabOrder(pingButton, runButton);

        retranslateUi(GUIPanel);

        tasaCombobox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(GUIPanel);
    } // setupUi

    void retranslateUi(QWidget *GUIPanel)
    {
        GUIPanel->setWindowTitle(QCoreApplication::translate("GUIPanel", "GUIPanel", nullptr));
        label_11->setText(QCoreApplication::translate("GUIPanel", "Aceler\303\263metro (g): ", nullptr));
        accel_stats->setText(QCoreApplication::translate("GUIPanel", "Eje X: 0.002 Eje Y: 0.120 Eje Z: 1.352", nullptr));
        label_12->setText(QCoreApplication::translate("GUIPanel", "Giroscopio (\302\272/s):", nullptr));
        gyro_stats->setText(QCoreApplication::translate("GUIPanel", "Eje X: 1.6251 Eje Y: 0.12498 Eje Z: 3.1594", nullptr));
        label_13->setText(QCoreApplication::translate("GUIPanel", "Magnet\303\263metro (\316\274T): ", nullptr));
        magneto_stats->setText(QCoreApplication::translate("GUIPanel", "Eje X: 50.2 Eje Y: 12 Eje Z: 120", nullptr));
        label_cpu->setText(QCoreApplication::translate("GUIPanel", "Uso de CPU: 32%", nullptr));
        estado_mqtt->setText(QCoreApplication::translate("GUIPanel", "ESTADO MQTT: conectado a /carga/#", nullptr));
        label_4->setText(QCoreApplication::translate("GUIPanel", "CONFIGURACI\303\223N CARGA", nullptr));
        boton_cerrar->setText(QCoreApplication::translate("GUIPanel", "Cerrar", nullptr));
        label_6->setText(QString());
        label_7->setText(QString());
        label_8->setText(QString());
        label_5->setText(QString());
        btn_pres_asl->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_acc_max->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_pres_max->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_pres_min->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_hr_max->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_acc_min->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_hr_min->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_temp_min->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        btn_temp_max->setText(QCoreApplication::translate("GUIPanel", "\342\234\224", nullptr));
        label_14->setText(QCoreApplication::translate("GUIPanel", "P ASL (hPa)", nullptr));
        validarbtn->setText(QCoreApplication::translate("GUIPanel", "VALIDAR TODO", nullptr));
        label_10->setText(QCoreApplication::translate("GUIPanel", "VALOR M\303\215NIMO", nullptr));
        label_9->setText(QCoreApplication::translate("GUIPanel", "VALOR M\303\201XIMO", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GUIPanel", "Conexi\303\263n USB", nullptr));
        serialPortLabel->setText(QCoreApplication::translate("GUIPanel", "Puerto Serie:", nullptr));
        runButton->setText(QCoreApplication::translate("GUIPanel", "Inicio", nullptr));
        pingButton->setText(QCoreApplication::translate("GUIPanel", "Ping", nullptr));
        label_20->setText(QCoreApplication::translate("GUIPanel", "Tasa de env\303\255o:", nullptr));
        acercaDeBTN->setText(QCoreApplication::translate("GUIPanel", "Acerca de", nullptr));
        usuario->setText(QCoreApplication::translate("GUIPanel", "usuario", nullptr));
        brokerConButton->setText(QCoreApplication::translate("GUIPanel", "CONECTAR BROKER", nullptr));
        contrasenia->setText(QCoreApplication::translate("GUIPanel", "usuario", nullptr));
        tasaCombobox->setCurrentText(QString());
        label_19->setText(QCoreApplication::translate("GUIPanel", "Usuario:", nullptr));
        publicBrokerCheck->setText(QCoreApplication::translate("GUIPanel", "Broker publico", nullptr));
        label_21->setText(QCoreApplication::translate("GUIPanel", "Contrase\303\261a:", nullptr));
        init_button->setText(QCoreApplication::translate("GUIPanel", "Conectar Sensores", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GUIPanel", "Ver 1.2", nullptr));
        Txttemp->setText(QCoreApplication::translate("GUIPanel", "Temperatura: --.-- \302\272C", nullptr));
#if QT_CONFIG(tooltip)
        ledpres->setToolTip(QCoreApplication::translate("GUIPanel", "Color Led component", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        ledpres->setWhatsThis(QCoreApplication::translate("GUIPanel", "Led indicator", nullptr));
#endif // QT_CONFIG(whatsthis)
        Txtpres->setText(QCoreApplication::translate("GUIPanel", "Presi\303\263n: ---- hPa", nullptr));
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
        TxtHR->setText(QCoreApplication::translate("GUIPanel", "Humedad Relativa: --.-- %", nullptr));
        pushButton->setText(QCoreApplication::translate("GUIPanel", "Datos en crudo", nullptr));
        config_carga_button->setText(QCoreApplication::translate("GUIPanel", "Configurar carga", nullptr));
        label_3->setText(QCoreApplication::translate("GUIPanel", "Eje Z", nullptr));
        fondo_accel->setText(QString());
#if QT_CONFIG(tooltip)
        led->setToolTip(QCoreApplication::translate("GUIPanel", "Color Led component", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        led->setWhatsThis(QCoreApplication::translate("GUIPanel", "Led indicator", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_18->setText(QCoreApplication::translate("GUIPanel", "M\303\241xima G", nullptr));
        label->setText(QString());
        inc_horiz->setText(QString());
        label_2->setText(QString());
        inc_frontal->setText(QString());
        TxtAlt->setPlainText(QCoreApplication::translate("GUIPanel", "Altitud: -- m", nullptr));
        txt_estado_carga->setHtml(QCoreApplication::translate("GUIPanel", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA SIN CONFIGURAR</span></p></body></html>", nullptr));
        alabeo_txt->setText(QCoreApplication::translate("GUIPanel", "00\302\272", nullptr));
        cabeceo_txt->setText(QCoreApplication::translate("GUIPanel", "00\302\272", nullptr));
        statusButton->setText(QCoreApplication::translate("GUIPanel", "Estado:", nullptr));
        statusLabel->setText(QCoreApplication::translate("GUIPanel", "Detenido", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("GUIPanel", "Configuraci\303\263n MQTT", nullptr));
        label_15->setText(QCoreApplication::translate("GUIPanel", "Puerto:", nullptr));
        label_16->setText(QCoreApplication::translate("GUIPanel", "Direcci\303\263n:", nullptr));
        dirMQTT->setText(QCoreApplication::translate("GUIPanel", "localhost", nullptr));
        puertoMQTT->setText(QCoreApplication::translate("GUIPanel", "1883", nullptr));
        label_17->setText(QCoreApplication::translate("GUIPanel", "Nombre:", nullptr));
        topic_txt->setText(QCoreApplication::translate("GUIPanel", "carga", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIPanel: public Ui_GUIPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIPANEL_H
