#ifndef GUIPANEL_H
#define GUIPANEL_H

#include <QWidget>
#include <QSerialPort>
#include <QMessageBox>
#include <QTcpSocket>
#include "qmqtt.h"
#include <QTimer>

namespace Ui {
class GUIPanel;
}


class GUIPanel : public QWidget
{
    Q_OBJECT
    
public:
    //GUIPanel(QWidget *parent = 0);
    explicit GUIPanel(QWidget *parent = 0);
    ~GUIPanel(); // Da problemas
    
private slots:
    void readRequest();
    void on_pingButton_clicked();
    void on_runButton_clicked();
    void on_statusButton_clicked();


    void on_init_button_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_config_carga_button_pressed();

    void on_boton_cerrar_pressed();

    void on_pushButton_pressed();

    void onMQTT_Connected(void);

    void onMQTT_subscribed(const QString &topic);

    //void onMQTT_Received(const QMQTT::Message &message);

    void onMQTT_Disconnected();

    void onMQTT_Error(const QMQTT::ClientError error);

    void startClient();

    void on_btn_pres_asl_pressed();

    void on_btn_temp_max_pressed();

    void on_btn_temp_min_pressed();

    void on_btn_hr_max_pressed();

    void on_btn_hr_min_pressed();

    void on_btn_pres_max_pressed();

    void on_btn_pres_min_pressed();

    void on_btn_acc_max_pressed();

    void on_btn_acc_min_pressed();

    void on_validarbtn_pressed();

    void on_tasaCombobox_currentIndexChanged(int index);

    void on_brokerConButton_pressed();

    void on_brokerPublico_checkStateChanged(const Qt::CheckState &arg1);

    void on_acercaDeBTN_pressed();

    void on_timer_timeout();

    void on_timer_wait_timeout();

    void on_refrescarPuertos_clicked();

    void on_pushButton_2_pressed();

private: // funciones privadas
    void pingDevice();
    void startSlave();
    void processError(const QString &s);
    void activateRunButton();
    void pingResponseReceived();
    void enviar_estado_carga();

private:
    Ui::GUIPanel *ui;
    int transactionCount;
    bool fConnected;
    QSerialPort serial;
    QByteArray incommingDataBuffer;
    QString LastError;
    QMessageBox ventanaPopUp;
    QPixmap original;
    QPixmap original_lat;
    QMessageBox ventana_datos_crudo;
    QMQTT::Client *_client;
    bool fMQTTconnected;
    QString pub_topic;
    bool carga_configurada;
    bool carga_estable;
    uint8_t contador_aceleracion;
    uint8_t contador_angulos;
    uint8_t suscrito_stats;

    typedef struct{
        float pres_max;
        float pres_min;
        float hr_max;
        float hr_min;
        float acc_max;
        float acc_min;
        float temp_max;
        float temp_min;
        uint8_t confgd;
    }Intervalos_carga;

    Intervalos_carga intervals;

    uint8_t valor_max_contador_envio;

    uint8_t sensores_conectados;

    QMessageBox ventanaAbout;

    uint8_t contadorPing;

    QTimer *timerPing;

    bool pingSentFlag;

    uint8_t contadorVer;

    QMessageBox ventanaGracias;

};

#endif // GUIPANEL_H
