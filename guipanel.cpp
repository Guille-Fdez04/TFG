#include "guipanel.h"
#include "ui_guipanel.h"
#include <QSerialPort>      // Comunicacion por el puerto serie
#include <QSerialPortInfo>  // Comunicacion por el puerto serie



#include<stdint.h>      // Cabecera para usar tipos de enteros con tamaño
#include<stdbool.h>     // Cabecera para usar booleanos

#include <QPainter>

#include <QJsonObject>
#include <QJsonDocument>

extern "C" {
#include "serial2USBprotocol.h"    // Cabecera de funciones de gestión de tramas; se indica que está en C, ya que QTs
// se integra en C++, y el C puede dar problemas si no se indica.
}

#include "usb_messages_table.h"



GUIPanel::GUIPanel(QWidget *parent) :  // Constructor de la clase
    QWidget(parent),
    ui(new Ui::GUIPanel)               // Indica que guipanel.ui es el interfaz grafico de la clase
  , transactionCount(0)
{
    ui->setupUi(this);                // Conecta la clase con su interfaz gráfico.
    setWindowTitle(tr("Interfaz PC")); // Título de la ventana

    // Conexion por el puerto serie-USB
    fConnected=false;                 // Todavía no hemos establecido la conexión USB
    ui->serialPortComboBox->clear(); // Vacía de componentes la comboBox
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        // La identificación nos permite que SOLO aparezcan los interfaces tipo USB serial de Texas Instrument
        if ((info.vendorIdentifier()==0x1CBE) && (info.productIdentifier()==0x0002))
        {
            ui->serialPortComboBox->addItem(info.portName());
        }
    ui->serialPortComboBox->setFocus();
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readRequest()));

    ui->pingButton->setEnabled(false);
    ui->init_button->setEnabled(false);

    //Inicializa la ventana pop-up PING
    ventanaPopUp.setIcon(QMessageBox::Information);
    ventanaPopUp.setText(tr("Status: RESPUESTA A PING RECIBIDA"));
    ventanaPopUp.setStandardButtons(QMessageBox::Ok);
    ventanaPopUp.setWindowTitle(tr("Evento"));
    ventanaPopUp.setParent(this,Qt::Popup);

    //Inicializa la ventana pop up de advertencia de placa no conectada
    ventana_datos_crudo.setIcon(QMessageBox::Information);
    ventana_datos_crudo.setWindowTitle(tr("AVISO"));
    ventana_datos_crudo.setParent(this,Qt::Popup);
    ventana_datos_crudo.setText(tr("¡DISPOSITIVO NO CONECTADO!"));
    ventana_datos_crudo.setStandardButtons(QMessageBox::Ok);

    //Inicializacion de las ventanas con informacion, y de los estados iniciales de los pixmap de los indicadores
    original = ui->inc_frontal->pixmap();
    original_lat = ui->inc_horiz->pixmap();
    ui->config_emergente->setVisible(false);
    ui->frame_datos_raw->setVisible(false);
    ui->Barra_hr->setAlarmEnabled(false);
    ui->Barra_temp->setAlarmEnabled(false);
    ui->Barra_pres->setAlarmEnabled(false);
    ui->accel_stats->setVisible(false);
    ui->gyro_stats->setVisible(false);
    ui->magneto_stats->setVisible(false);
    ui->pushButton->setEnabled(false);


    QString text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aaaaaa;\">CARGA SIN CONFIGURAR</span></p></body></html>";

    ui->txt_estado_carga->setHtml(text);

    //Inicialmente, la carga esta estable y sin configurar
    carga_configurada = 0;
    carga_estable = 1;
    intervals.confgd = 0;

    //Inicializo los contadores
    contador_aceleracion = 0;
    contador_angulos = 0;
    valor_max_contador_envio = 0;
    contadorPing = 0;
    contadorVer = 0;

    //Inicializacion de MQTT
    _client=new QMQTT::Client(QHostAddress::LocalHost, 1883); //localhost y lo otro son valores por defecto
    connect(_client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));
    connect(_client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(const QMQTT::Message &)));
    connect(_client, SIGNAL(subscribed(const QString &)), this, SLOT(onMQTT_subscribed(const QString &)));
    connect(_client, SIGNAL(disconnected()),this,SLOT(onMQTT_Disconnected()));
    connect(_client,SIGNAL(error(const QMQTT::ClientError error)),this, SLOT(onMQTT_Error(const QMQTT::ClientError error)));

    fMQTTconnected=false; //Hasta que no se presione el boton de conectar, no se establece la conexion mqtt
    sensores_conectados = 0;
    pingSentFlag = false;


    //Muestro los posibles valores para regular la velocidad a la que se mandan datos al servidor MQTT
    ui->tasaCombobox->addItem("/1");
    ui->tasaCombobox->addItem("/2");
    ui->tasaCombobox->addItem("/4");
    ui->tasaCombobox->addItem("/8");

    //Creo un contador
    timerPing = new QTimer(this);
    connect(timerPing,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));

    }

GUIPanel::~GUIPanel() // Destructor de la clase
{
    delete ui;   // Borra el interfaz gráfico asociado a la clase
}


//Rutina que inicializa el cliente MQTT
void GUIPanel::startClient()
{
    _client->setHostName(ui->dirMQTT->text());
    _client->setPort(ui->puertoMQTT->text().toInt());
    _client->setKeepAlive(300);
    _client->setCleanSession(true);
    _client->setClientId(ui->usuario->text());
    //_client->setUsername(ui->usuario->text());
    //_client->setPassword(ui->contrasenia->text().toUtf8());
    //Si quiero usar el test.mosquitto.org no puedo usar usuario y contraseña


    if(!(ui->publicBrokerCheck->isChecked())){
        _client->setUsername(ui->usuario->text());
        _client->setPassword(ui->contrasenia->text().toUtf8());
    }
    _client->connectToHost();


}

//SLOT que se activa al suscribirse a un topic
void GUIPanel::onMQTT_subscribed(const QString &topic)
{
    QString txt = "ESTADO MQTT: CONECTADO AL TOPIC: ";
    ui->estado_mqtt->setText(txt.append(topic));
}

//SLOT que se activa cuando se ha completado la conexion cliente-broker
void GUIPanel::onMQTT_Connected()
{
    fMQTTconnected=true;
    ui->brokerConButton->setText("Desconectar Broker");
    pub_topic = ui->topic_txt->text();
    QString txt = "/";
    txt.append(pub_topic + "/#");

    //Me suscribo al topic
    _client->subscribe(txt,0);

    ventana_datos_crudo.setText("BROKER CONECTADO");
    ventana_datos_crudo.setStyleSheet("background-color: white");
    ventana_datos_crudo.setModal(true);
    ventana_datos_crudo.show();

}

//SLOT que se activa cuando se desconecta el broker
void GUIPanel::onMQTT_Disconnected() {

    fMQTTconnected = false;
    ui->estado_mqtt->setText("Estado MQTT: DESCONECTADO");
    //Si no se ha introducido, se muestra un popup con un aviso
    ventana_datos_crudo.setText("BROKER MQTT Desconectado");
    ventana_datos_crudo.setStyleSheet("background-color: white");
    ventana_datos_crudo.setModal(true);
    ventana_datos_crudo.show();
    ui->brokerConButton->setText("Reconectar broker");

}

//SLOT que se activa cuando hay un problema del broker
void GUIPanel::onMQTT_Error(const QMQTT::ClientError error){

    if(error == (QMQTT::SocketConnectionRefusedError)){
        ventana_datos_crudo.setText("ERROR: Se ha rechazado la conexión");
    }

    if(error == QMQTT::MqttBadUserNameOrPasswordError){
        ventana_datos_crudo.setText("ERROR: Usuario y/o contraseña incorrectos");
    }
    else{
        ventana_datos_crudo.setText("ERROR");
    }

    ventana_datos_crudo.setStyleSheet("background-color: white");
    ventana_datos_crudo.setModal(true);
    ventana_datos_crudo.show();
}

void GUIPanel::readRequest()
{
    int StopCharPosition,StartCharPosition,tam;   // Solo uso notacin hungara en los elementos que se van a
    // intercambiar con el micro - para control de tamaño -
    uint8_t *pui8Frame; // Puntero a zona de memoria donde reside la trama recibida
    void *ptrtoparam;
    uint8_t ui8Message; // Para almacenar el mensaje de la trama entrante


    incommingDataBuffer.append(serial.readAll()); // Añade el contenido del puerto serie USB al array de bytes 'incommingDataBuffer'
    // así vamos acumulando  en el array la información que va llegando

    // Busca la posición del primer byte de fin de trama (0xFD) en el array. Si no estuviera presente,
    // salimos de la funcion, en caso contrario, es que ha llegado al menos una trama.
    // Hay que tener en cuenta que pueden haber llegado varios paquetes juntos.
    StopCharPosition=incommingDataBuffer.indexOf((char)STOP_FRAME_CHAR,0);
    while (StopCharPosition>=0)
    {
        //Ahora buscamos el caracter de inicio correspondiente.
        StartCharPosition=incommingDataBuffer.lastIndexOf((char)START_FRAME_CHAR,0); //Este seria el primer caracter de inicio que va delante...

        if (StartCharPosition<0)
        {
            //En caso de que no lo encuentre, no debo de hacer nada, pero debo vaciar las primeras posiciones hasta STOP_FRAME_CHAR (inclusive)
            incommingDataBuffer.remove(0,StopCharPosition+1);
            LastError=QString("Status:Fallo trozo paquete recibido");
        } else
        {
            incommingDataBuffer.remove(0,StartCharPosition); //Si hay datos anteriores al caracter de inicio, son un trozo de trama incompleto. Los tiro.
            tam=StopCharPosition-StartCharPosition+1;//El tamanio de la trama es el numero de bytes desde inicio hasta fin, ambos inclusive.
            if (tam>=MINIMUM_FRAME_SIZE)
            {
                pui8Frame=(uint8_t*)incommingDataBuffer.data(); // Puntero de trama al inicio del array de bytes
                pui8Frame++; //Nos saltamos el caracter de inicio.
                tam-=2; //Descontamos los bytes de inicio y fin del tamanio del paquete

                // Paso 1: Destuffing y cálculo del CRC. Si todo va bien, obtengo la trama
                // con valores actualizados y sin bytes de CRC.
                tam=destuff_and_check_checksum((unsigned char *)pui8Frame,tam);
                if (tam>=0)
                {
                    //El paquete está bien, luego procedo a tratarlo.
                    ui8Message=decode_message_type(pui8Frame); // Obtencion del byte de Mensaje
                    tam=get_message_param_pointer(pui8Frame,tam,&ptrtoparam);
                    switch(ui8Message) // Segun el mensaje tengo que hacer cosas distintas
                    {

                    case MENSAJE_PING:
                    {

                        if(pingSentFlag == true){

                            pingSentFlag = false;
                            contadorPing = 0;
                        }

                        else{
                            pingResponseReceived();
                        }
                    }



                        break;

                    case MENSAJE_NO_IMPLEMENTADO:
                    {
                        // En otros mensajes hay que extraer los parametros de la trama y copiarlos
                        // a una estructura para poder procesar su informacion
                        PARAM_MENSAJE_NO_IMPLEMENTADO parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0)
                        {
                            // Muestra en una etiqueta (statuslabel) del GUI el mensaje
                            ui->statusLabel->setText(tr("  Mensaje rechazado,"));
                        }
                        else
                        {
                            // TRATAMIENTO DE ERRORES
                        }
                    }
                        break;

                    case MENSAJE_TEMP:{

                        PARAM_MENSAJE_TEMP parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0){
                            float temp;
                            temp = (float) parametro.parte_entera;
                            temp += (((float) (parametro.parte_fraccionaria)))/100.0;
                            ui->Barra_temp->setValue(temp);
                            ui->Txttemp->setText("Temperatura: " + QString::number(parametro.parte_entera) + "." + QString::number(parametro.parte_fraccionaria) + " ºC");

                            //Si estamos conectados al broker mqtt, se publica un mensaje
                            if(fMQTTconnected == 1){
                                QJsonObject objeto;
                                objeto["valor"] = temp;
                                QJsonDocument documento(objeto);
                                QString txt = "/";

                                QMQTT::Message msg(0, txt.append(pub_topic + "/temperatura"), documento.toJson());
                                // msg.setRetain(true);
                                _client->publish(msg); //Se publica el mensaje en el topic indicado

                            }


                            if(carga_configurada == 1){
                                //Se comprueba si la carga sigue siendo estable
                                QColor tmp;

                                if(temp > intervals.temp_max){
                                    carga_estable = 0;
                                    tmp.setRgb(255,0,0);
                                    ui->ledtemp->setColor(tmp);
                                    QString text;
                                    text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA INESTABLE</span></p></body></html>";
                                    ui->txt_estado_carga->setHtml(text);
                                }
                                else if(temp < intervals.temp_min){
                                    carga_estable = 0;
                                    tmp.setRgb(0,0,255);
                                    ui->ledtemp->setColor(tmp);
                                    QString text;
                                    text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA INESTABLE</span></p></body></html>";
                                    ui->txt_estado_carga->setHtml(text);
                                }
                                else{
                                    tmp.setRgb(0,255,0);
                                    ui->ledtemp->setColor(tmp);
                                }
                                enviar_estado_carga();
                            }

                        }}

                        break;

                    case MENSAJE_HR:
                    {
                        PARAM_MENSAJE_HR parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0){
                            ui->TxtHR->setText("Humedad Relativa: " + QString::number(parametro.parte_entera) + "." + QString::number(parametro.parte_fraccionaria) + " %");
                            float temp;
                            temp = (float) parametro.parte_entera;
                            temp += ( (float) (parametro.parte_fraccionaria)/10.0);
                            ui->Barra_hr->setValue(temp);

                            //Si estamos conectados al broker mqtt, se publica un mensaje
                            if(fMQTTconnected == 1){
                                QJsonObject objeto;
                                objeto["valor"] = temp;
                                QJsonDocument documento(objeto);
                                QString txt = "/";
                                QMQTT::Message msg(0, txt.append(pub_topic + "/hr"), documento.toJson());
                                // msg.setRetain(true);
                                _client->publish(msg); //Se publica el mensaje en el topic indicado
                            }


                            if(carga_configurada == 1){
                                //Se comprueba si la carga sigue siendo estable
                                QColor tmp;

                                if(temp > intervals.hr_max){
                                    carga_estable = 0;
                                    tmp.setRgb(255,0,0);
                                    ui->ledhr->setColor(tmp);
                                    QString text;
                                    text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA INESTABLE</span></p></body></html>";
                                    ui->txt_estado_carga->setHtml(text);
                                }
                                else if(temp < intervals.hr_min){
                                    carga_estable = 0;
                                    tmp.setRgb(0,0,255);
                                    ui->ledhr->setColor(tmp);
                                    QString text;
                                    text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA INESTABLE</span></p></body></html>";
                                    ui->txt_estado_carga->setHtml(text);
                                }
                                else{

                                    tmp.setRgb(0,255,0);
                                    ui->ledhr->setColor(tmp);
                                }
                                enviar_estado_carga();
                            }


                        }
                    }

                        break;

                    case MENSAJE_PRES:
                    {
                        PARAM_MENSAJE_PRESION parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0){

                            ui->Txtpres->setText("Presión: " + QString::number(parametro.presion/100) + " hPa");
                            ui->TxtAlt->setPlainText("Altitud: " + QString::number(parametro.parte_entera_altitud) + " m");
                            ui->Barra_pres->setValue(parametro.presion/100);

                            //Si estamos conectados al broker mqtt, se publica un mensaje
                            if(fMQTTconnected == 1){
                                QJsonObject objeto;
                                objeto["valor"] = parametro.presion;
                                QJsonDocument documento(objeto);
                                QString txt = "/";
                                QMQTT::Message msg(0, txt.append(pub_topic + "/presion"), documento.toJson());
                                // msg.setRetain(true);
                                _client->publish(msg); //Se publica el mensaje en el topic indicado

                                objeto["parte_entera"] = parametro.parte_entera_altitud;
                                objeto["parte_fraccionaria"] = (int32_t) parametro.parte_fraccionaria_altitud;
                                QJsonDocument documento2(objeto);
                                QMQTT::Message msg2(0, "/" + pub_topic + "/altitud", documento2.toJson());
                                _client->publish(msg2);
                            }


                            if(carga_configurada == 1){
                                //Se comprueba si la carga sigue siendo estable
                                QColor tmp;

                                if((float)parametro.presion > intervals.pres_max){
                                    carga_estable = 0;
                                    tmp.setRgb(255,0,0);
                                    ui->ledpres->setColor(tmp);
                                    QString text;
                                    text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA INESTABLE</span></p></body></html>";
                                    ui->txt_estado_carga->setHtml(text);
                                }
                                else if((float)parametro.presion < intervals.pres_min){
                                    carga_estable = 0;
                                    tmp.setRgb(0,0,255);
                                    ui->ledpres->setColor(tmp);
                                    QString text;
                                    text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA INESTABLE</span></p></body></html>";
                                    ui->txt_estado_carga->setHtml(text);
                                }
                                else{

                                    tmp.setRgb(0,255,0);
                                    ui->ledpres->setColor(tmp);
                                }
                                enviar_estado_carga();
                            }



                        }

                    }
                    break;

                    case MENSAJE_ACELERACION:
                    {
                        PARAM_MENSAJE_ACELERACION parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0){
                            //int32_t parte_entera[4];
                            //uint32_t parte_fraccionaria[4];
                            float datos[4];
                            datos[0] = parametro.ejeX;
                            datos[1] = parametro.ejeY;
                            datos[2] = parametro.ejeZ;
                            datos[3] = parametro.maximo;

                            QString texto = "Eje X: ";
                            texto.append(QString::number(parametro.ejeX) + "    Eje Y: " + QString::number(parametro.ejeY) + "   Eje Z: "+ QString::number(parametro.ejeZ));
                            ui->accel_stats->setText(texto);

                            // for (int i = 0; i < 4; i++){
                            //     if(datos[i] > 0){
                            //         signo = 1;
                            //     }
                            //     else{
                            //         signo = 0;
                            //     }
                            //     float valor_abs = fabs(datos[i]);
                            //     parte_entera[i] = (int32_t) valor_abs * signo;
                            //     parte_fraccionaria[i] = (uint32_t)round((valor_abs - (int32_t)valor_abs)*1000);
                            // }

                            //Para la representacion en el plano de 2 ejes del acelerometro, dado que la imagen son 250*250 pixeles,
                            //y quiero representar un valor normalizado de 0G a 3G, siendo el centro de la imagen 125*125, un valor
                            //de 1 G en un eje se corresponde con la posicion 42 * 1G + 125 - 8, ya que el tamaño del circulo puntero es 16*16
                            uint16_t coordenada_x, coordenada_y;
                            coordenada_x = (uint16_t)(125 - 8 + 42 * datos[0]);
                            coordenada_y = (uint16_t) (125 - 8 + 42 * -datos[1]);

                            ui->led->setGeometry(coordenada_x,coordenada_y,16,16);
                            ui->Thermo_ejez->setValue(datos[2]);
                            ui->maxG_display->display(datos[3]);



                            //Si estamos conectados al broker mqtt, se publica un mensaje
                            if(fMQTTconnected == 1){

                                //Para no saturar el servidor mqtt, se manda solo una actualizacion de la aceleracion por cada 10 mensajes de la placa
                                if(contador_aceleracion == valor_max_contador_envio){
                                    contador_aceleracion = 0;
                                    QJsonObject objeto;
                                    objeto["valor_x"] = datos[0];
                                    objeto["valor_y"] = datos[1];
                                    objeto["valor_z"] = datos[2];
                                    objeto["max_G"] = datos[3];
                                    QJsonDocument documento(objeto);
                                    QMQTT::Message msg(0,"/" + pub_topic + "/aceleracion", documento.toJson());
                                    // msg.setRetain(true);
                                    _client->publish(msg); //Se publica el mensaje en el topic indicado
                                }
                                else{
                                    contador_aceleracion++;
                                }

                            }


                            if(carga_configurada == 1){
                                //Se comprueba si la carga sigue siendo estable
                                QColor tmp;

                                if(datos[3] > intervals.acc_max){
                                    carga_estable = 0;
                                    tmp.setRgb(255,0,0);
                                    ui->led->setColor(tmp);
                                    QString text;
                                    text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA INESTABLE</span></p></body></html>";
                                    ui->txt_estado_carga->setHtml(text);
                                }
                                else if(datos[3] < intervals.acc_min){
                                    carga_estable = 0;
                                    tmp.setRgb(0,0,255);
                                    ui->led->setColor(tmp);
                                    QString text;
                                    text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CARGA INESTABLE</span></p></body></html>";
                                    ui->txt_estado_carga->setHtml(text);
                                }
                                else{

                                    tmp.setRgb(0,255,0);
                                    ui->led->setColor(tmp);
                                }
                                enviar_estado_carga();
                            }
                        }

                    }
                    break;

                    case MENSAJE_ANGULOS:
                    {
                        PARAM_MENSAJE_ANGULOS parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0){

                            ui->inc_horiz->setPixmap(original_lat.transformed(QTransform().rotate(-parametro.cabeceo)));
                            ui->cabeceo_txt->setText(QString::number(parametro.cabeceo).append("º"));
                            ui->inc_frontal->setPixmap(original.transformed(QTransform().rotate(-parametro.alabeo)));
                            ui->alabeo_txt->setText(QString::number(parametro.alabeo).append("º"));
                            //Si estamos conectados al broker mqtt, se publica un mensaje
                            if(fMQTTconnected == 1){
                                if(contador_angulos == valor_max_contador_envio){
                                    contador_angulos = 0;
                                    QJsonObject objeto;
                                    objeto["cabeceo"] = parametro.cabeceo;
                                    objeto["alabeo"] = parametro.alabeo;
                                    QJsonDocument documento(objeto);
                                    QMQTT::Message msg(0, "/" + pub_topic + "/angulos", documento.toJson());
                                    // msg.setRetain(true);
                                    _client->publish(msg); //Se publica el mensaje en el topic indicado
                                }
                                else{
                                    contador_angulos++;
                                }

                            }
                        }

                    }
                    break;

                    case MENSAJE_GIROSCOPIO:
                    {
                        PARAM_MENSAJE_GIROSCOPIO parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0){
                            QString texto = "Eje X: ";
                            texto.append(QString::number(parametro.ejeX) + "    Eje Y: " + QString::number(parametro.ejeY) + "   Eje Z: "+ QString::number(parametro.ejeZ));
                            ui->gyro_stats->setText(texto);
                        }
                    }
                    break;

                    case MENSAJE_CPU:
                    {
                        PARAM_MENSAJE_CPU parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0){
                            QString texto = "Uso de la CPU: ";

                            ui->label_cpu->setText(texto.append(QString::number(parametro.cpu)).append(" %"));
                        }
                    }

                    case MENSAJE_MAGNETO:
                    {
                        PARAM_MENSAJE_MAGNETO parametro;
                        if (check_and_extract_message_param(ptrtoparam, tam, sizeof(parametro),&parametro)>0){
                            QString txt = "Eje X: ";
                            txt.append(QString::number(parametro.ejex*1000000.0) + "   Eje Y: " + QString::number(parametro.ejey*1000000.0) + "   Eje Z: " + QString::number(parametro.ejez*1000000.0));
                            ui->magneto_stats->setText(txt);
                        }

                    }
                    break;

                    default:
                        //Este error lo notifico mediante la señal statusChanged
                        LastError=QString("Status: Recibido paquete inesperado");
                        ui->statusLabel->setText(tr("  Recibido paquete inesperado,"));
                        break;
                    }
                }
                else
                {
                    LastError=QString("Status: Error de stuffing o CRC");
                    ui->statusLabel->setText(tr(" Error de stuffing o CRC"));
                 }
            }
            else
            {

                // B. La trama no está completa o no tiene el tamano adecuado... no lo procesa
                //Este error lo notifico mediante la señal statusChanged
                LastError=QString("Status: Error trozo paquete recibido");
                ui->statusLabel->setText(tr(" Fallo trozo paquete recibido"));
            }
            incommingDataBuffer.remove(0,StopCharPosition-StartCharPosition+1); //Elimino el trozo que ya he procesado
        }

        StopCharPosition=incommingDataBuffer.indexOf((char)STOP_FRAME_CHAR,0); //Compruebo si el se ha recibido alguna trama completa mas. (Para ver si tengo que salir del bucle o no
    } //Fin del while....
}

// Funciones auxiliares a la gestión comunicación USB

// Establecimiento de la comunicación USB serie a través del interfaz seleccionado en la comboBox, tras pulsar el
// botón RUN del interfaz gráfico. Se establece una comunicacion a 9600bps 8N1 y sin control de flujo en el objeto
// 'serial' que es el que gestiona la comunicación USB serie en el interfaz QT
void GUIPanel::startSlave()
{
    if (serial.portName() != ui->serialPortComboBox->currentText()) {
        serial.close();
        serial.setPortName(ui->serialPortComboBox->currentText());

        if (!serial.open(QIODevice::ReadWrite)) {
            processError(tr("No puedo abrir el puerto %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setBaudRate(9600)) {
            processError(tr("No puedo establecer tasa de 9600bps en el puerto %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setDataBits(QSerialPort::Data8)) {
            processError(tr("No puedo establecer 8bits de datos en el puerto %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setParity(QSerialPort::NoParity)) {
            processError(tr("NO puedo establecer parida en el puerto %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setStopBits(QSerialPort::OneStop)) {
            processError(tr("No puedo establecer 1bitStop en el puerto %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setFlowControl(QSerialPort::NoFlowControl)) {
            processError(tr("No puedo establecer el control de flujo en el puerto %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }
    }

    ui->runButton->setEnabled(false);

    // Se indica que se ha realizado la conexión en la etiqueta 'statusLabel'
    ui->statusLabel->setText(tr("Estado: Ejecucion, conectado al puerto %1.")
                             .arg(ui->serialPortComboBox->currentText()));

    // Y se habilitan los controles
    ui->pingButton->setEnabled(true);
    ui->init_button->setEnabled(true);

    // Variable indicadora de conexión a TRUE, para que se permita enviar mensajes en respuesta
    // a eventos del interfaz gráfico
    fConnected=true;


}

// Funcion auxiliar de procesamiento de errores de comunicación (usada por startSlave)
void GUIPanel::processError(const QString &s)
{
    activateRunButton(); // Activa el botón RUN
    // Muestra en la etiqueta de estado la razón del error (notese la forma de pasar argumentos a la cadena de texto)
    ui->statusLabel->setText(tr("Status: Not running, %1.").arg(s));
}

// Funcion de habilitacion del boton de inicio/conexion
void GUIPanel::activateRunButton()
{
    ui->runButton->setEnabled(true);
}

// Funciones SLOT que se crean automaticamente desde QTDesigner al activar una señal de un Widget del interfaz gráfico
// Se suelen asociar a funciones auxiliares, en muchos caso, por comodidad.

// SLOT asociada a pulsación del botón RUN
void GUIPanel::on_runButton_clicked()
{
    startSlave();

    //con la placa conectada, activamos el temporizador que salta cada 2 segundos enviando un msg ping
    timerPing -> start(2000);
}

// SLOT asociada a pulsación del botón PING
void GUIPanel::on_pingButton_clicked()
{
   pingDevice();
}

// SLOT asociada al borrado del mensaje de estado al pulsar el boton
void GUIPanel::on_statusButton_clicked()
{
    ui->statusLabel->setText(tr(""));
}

// Funciones de usuario asociadas a la respuesta a mensajes. La estructura va a ser muy parecida en casi todos los
// casos. Se va a crear una trama de un tamaño maximo (100), y se le van a introducir los elementos de
// num_secuencia, mensaje, y parametros.

// Envío de un mensaje PING

void GUIPanel::pingDevice()
{
    uint8_t paquete[MAX_FRAME_SIZE];
    int size;

    if (fConnected) // Para que no se intenten enviar datos si la conexion USB no esta activa
    {
        // El mensaje PING no necesita parametros; de ahí el NULL, y el 0 final.
        // No vamos a usar el mecanismo de numeracion de tramas; pasamos un 0 como n de trama
        size=create_frame(paquete, MENSAJE_PING, nullptr, 0, MAX_FRAME_SIZE);
        // Si la trama se creó correctamente, se escribe el paquete por el puerto serie USB
        if (size>0) serial.write((const char*)paquete,size);
    }
}

void GUIPanel::pingResponseReceived()

{
    // Ventana popUP para el caso de mensaje PING; no te deja definirla en un "caso"
    ventanaPopUp.setStyleSheet("background-color: lightgrey");
    ventanaPopUp.setModal(true);
    ventanaPopUp.show();
}



void GUIPanel::on_init_button_clicked()
//Cuando se presiona el boton de iniciar conexion
{

    uint8_t paquete[MAX_FRAME_SIZE];
    int size;


    if(fConnected == 1){

        if(sensores_conectados == 0){
            //Informamos a la placa de que el cliente QT esta conectado
            PARAM_MENSAJE_APLICACION parametro;
            sensores_conectados = 1;
            parametro.estado=sensores_conectados;
            size=create_frame(paquete, MENSAJE_APLICACION, &parametro, sizeof(parametro), MAX_FRAME_SIZE);
            if (size>0) serial.write((const char*)paquete,size);
            ui->init_button->setText("Desconectar sensores");
            ui->accel_stats->setVisible(true);
            ui->gyro_stats->setVisible(true);
            ui->magneto_stats->setVisible(true);
            ui->pushButton->setEnabled(true);
        }
        else{
            //Informamos a la placa de que el cliente QT se quiere descoenctar
            PARAM_MENSAJE_APLICACION parametro;
            sensores_conectados = 0;
            parametro.estado=sensores_conectados;
            size=create_frame(paquete, MENSAJE_APLICACION, &parametro, sizeof(parametro), MAX_FRAME_SIZE);
            if (size>0) serial.write((const char*)paquete,size);
            ui->init_button->setText("Conectar sensores");
            ui->accel_stats->setVisible(false);
            ui->gyro_stats->setVisible(false);
            ui->magneto_stats->setVisible(false);
            ui->pushButton->setEnabled(false);
        }
    }
    else{
        //Si la placa no esta conectada se muestra un popup con un aviso
        ventana_datos_crudo.setText("¡DISPOSITIVO NO CONECTADO!");
        ventana_datos_crudo.setStyleSheet("background-color: lightgray");
        ventana_datos_crudo.setModal(true);
        ventana_datos_crudo.show();
    }


}


//BORRAR PARA VERSION FINAL
void GUIPanel::on_horizontalSlider_valueChanged(int value)
{
    ui->inc_horiz->setPixmap(original_lat.transformed(QTransform().rotate(-value)));
    ui->cabeceo_txt->setText(QString::number(value).append("º"));
    ui->inc_frontal->setPixmap(original.transformed(QTransform().rotate(-value)));
    ui->alabeo_txt->setText(QString::number(value).append("º"));
}

//Se muestra el panel de configuracion de la carga
void GUIPanel::on_config_carga_button_pressed()
{
    ui->config_emergente->setVisible(true);
    }

//Se oculta el panel de configuracion de la carga
void GUIPanel::on_boton_cerrar_pressed()
{
    ui->config_emergente->setVisible(false);
}


void GUIPanel::on_pushButton_pressed()
{
    //Boton para mostrar los datos en crudo
    if(fConnected == 1){
        bool estado = ui->frame_datos_raw->isVisible();
        ui->frame_datos_raw->setVisible(!estado);
    }
    else{
        //Si la placa no esta conectada se muestra un popup con un aviso
        ventana_datos_crudo.setStyleSheet("background-color: lightgrey");
        ventana_datos_crudo.setModal(true);
        ventana_datos_crudo.show();

    }
}

//Se envia el valor introducido a la placa
void GUIPanel::on_btn_pres_asl_pressed()
{
    uint8_t paquete[MAX_FRAME_SIZE];
    int size;

    PARAM_MENSAJE_PRES_ASL parametro;

    parametro.presasl = (ui->txt_pres_asl->text().toFloat())*100;

    size=create_frame(paquete, MENSAJE_PRESION_ASL, &parametro,sizeof(parametro), MAX_FRAME_SIZE);
    // Si la trama se creó correctamente, se escribe el paquete por el puerto serie USB
    if (size>0) serial.write((const char*)paquete,size);
}


//****************BOTONES DE CONFIRMACION DE LIMITES DE LAS MAGNITUDES*****************
//*************************************************************************************
void GUIPanel::on_btn_temp_max_pressed()
{
    intervals.temp_max = ui->txt_temp_max->toPlainText().toFloat();
    intervals.confgd = intervals.confgd | 1;
    ui->btn_temp_max->setEnabled(false);
}void GUIPanel::on_btn_temp_min_pressed()
{
    intervals.temp_min = ui->txt_temp_min->toPlainText().toFloat();
    intervals.confgd = intervals.confgd | 2;
    ui->btn_temp_min->setEnabled(false);
}
void GUIPanel::on_btn_hr_max_pressed()
{
    intervals.hr_max = ui->txt_hr_max->toPlainText().toFloat();
    intervals.confgd = intervals.confgd | 4;
    ui->btn_hr_max->setEnabled(false);
}
void GUIPanel::on_btn_hr_min_pressed()
{
    intervals.hr_min = ui->txt_hr_min->toPlainText().toFloat();
    intervals.confgd = intervals.confgd | 8;
    ui->btn_hr_min->setEnabled(false);
}


void GUIPanel::on_btn_pres_max_pressed()
{
    intervals.pres_max = (ui->txt_pres_max->toPlainText().toFloat())*100.0;
    intervals.confgd = intervals.confgd | 16;
    ui->btn_pres_max->setEnabled(false);
}


void GUIPanel::on_btn_pres_min_pressed()
{
    intervals.pres_min = (ui->txt_pres_min->toPlainText().toFloat())*100.0;
    intervals.confgd = intervals.confgd | 32;
    ui->btn_pres_min->setEnabled(false);
}


void GUIPanel::on_btn_acc_max_pressed()
{
    intervals.acc_max = ui->txt_acc_max->toPlainText().toFloat();
    intervals.confgd = intervals.confgd | 64;
    ui->btn_acc_max->setEnabled(false);
}


void GUIPanel::on_btn_acc_min_pressed()
{
    intervals.acc_min = ui->txt_acc_min->toPlainText().toFloat();
    intervals.confgd = intervals.confgd | 128;
    ui->btn_acc_min->setEnabled(false);
}

//*************************************************************************************


//Boton para validar los limites introducidos
void GUIPanel::on_validarbtn_pressed()
{
    QString text;

    if(fConnected == 1){
        if(intervals.confgd==255){

            //Si se han configurado todas las magnitudes
            //(los 8 bits del byte confgd estan puestos a 1)
            text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#27c204;\">CARGA ESTABLE</span></p></body></html>";
            carga_configurada = 1;

            //Se resetean los botones por si se quieren modificar los valores
            ui->btn_temp_max->setEnabled(true);
            ui->btn_temp_min->setEnabled(true);
            ui->btn_hr_max->setEnabled(true);
            ui->btn_hr_min->setEnabled(true);
            ui->btn_pres_max->setEnabled(true);
            ui->btn_pres_min->setEnabled(true);
            ui->btn_acc_max->setEnabled(true);
            ui->btn_acc_min->setEnabled(true);

            //Se resetea el estado de la carga a estable
            carga_estable = true;

            //Se ajustan los límites de los indicadores a los valores introducidos
            ui->Barra_hr->setLowerBound(intervals.hr_min);
            ui->Barra_hr->setUpperBound(intervals.hr_max);
            ui->Barra_pres->setUpperBound(intervals.pres_max/100);
            ui->Barra_pres->setLowerBound(intervals.pres_min/100);
            ui->Barra_temp->setUpperBound(intervals.temp_max);
            ui->Barra_temp->setLowerBound(intervals.temp_min);

        }
        else{
            //Configuracion invalida
            text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:700; color:#aa0003;\">CONFIGURACIÓN INVÁLIDA</span></p></body></html>";
        }

    }
    else{
        //No se ha conectado la placa
        text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\nhr { height: 1px; border-width: 0; }\nli.unchecked::marker { content: \"\\2610\"; }\nli.checked::marker { content: \"\\2612\"; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:21pt; font-weight:700; color:#aa0003;\">DISPOSITIVO NO CONECTADO</span></p></body></html>";
    }
    ui->txt_estado_carga->setHtml(text);

}


void GUIPanel::enviar_estado_carga(){

    QJsonObject objeto;
    objeto["valor"] = carga_estable;
    QJsonDocument documento(objeto);
    QMQTT::Message msg(0, "/" + pub_topic + "/estabilidad", documento.toJson());
    _client->publish(msg); //Se publica el mensaje en el topic indicado
}


void GUIPanel::on_tasaCombobox_currentIndexChanged(int index)
{
    uint8_t diccionario[4] = {0,1,3,7};
    if(index>-1){
        valor_max_contador_envio = diccionario[index];
    }
    else{
        valor_max_contador_envio = 1;
    }
}


void GUIPanel::on_brokerConButton_pressed()
{
    if(fConnected == 1){

        if(fMQTTconnected == false){
            //Comprobamos si se ha introducido un usuario y contraseña
            if(!ui->publicBrokerCheck->isChecked()){
                if((ui->contrasenia->text() != "") && (ui->usuario->text() != "")){
                    startClient(); //Activamos el cliente mqtt
                }
                else{
                    //Si no se ha introducido, se muestra un popup con un aviso
                    ventana_datos_crudo.setText("INTRODUCE USUARIO Y CONTRASEÑA");
                    ventana_datos_crudo.setStyleSheet("background-color: white");
                    ventana_datos_crudo.setModal(true);
                    ventana_datos_crudo.show();
                }
            }
            else{
                startClient();
            }
        }
        else{
            _client->disconnectFromHost();
        }


    }
    else{
        //Si la placa no esta conectada se muestra un popup con un aviso
        ventana_datos_crudo.setText("¡DISPOSITIVO NO CONECTADO!");
        ventana_datos_crudo.setStyleSheet("background-color: lightgray");
        ventana_datos_crudo.setModal(true);
        ventana_datos_crudo.show();
    }

}



void GUIPanel::on_brokerPublico_checkStateChanged(const Qt::CheckState &arg1)
{

}


void GUIPanel::on_acercaDeBTN_pressed()
{
    ventanaAbout.aboutQt(this,"Acerca de Qt");
}

//SLOT que se ejecuta cuando el timer llega a 0
void GUIPanel::on_timer_timeout(){
    //Se manda mensaje ping y se espera a recibir, si no se recibe, se intenta varias veces
    //si despues de esas veces no se recibe respuesta, placa desconectada
    pingSentFlag = true;
    QTimer::singleShot(1000,this,SLOT(on_timer_wait_timeout()));
    pingDevice();


}



void GUIPanel::on_timer_wait_timeout(){
    if(pingSentFlag == true){
        ++contadorPing;
        if(contadorPing == 2){
            fConnected = false;
            serial.close();
            serial.setPortName("");
            ui->runButton->setEnabled(true);
            ui->pingButton->setEnabled(false);
            ventana_datos_crudo.setText("¡DISPOSITIVO DESCONECTADO!");
            ventana_datos_crudo.setStyleSheet("background-color: lightgray");
            ventana_datos_crudo.setModal(true);
            ventana_datos_crudo.show();
        }
    }
}

void GUIPanel::on_refrescarPuertos_clicked()
{
    ui->serialPortComboBox->clear(); // Vacía de componentes la comboBox
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        // La identificación nos permite que SOLO aparezcan los interfaces tipo USB serial de Texas Instrument
        if ((info.vendorIdentifier()==0x1CBE) && (info.productIdentifier()==0x0002))
        {
            ui->serialPortComboBox->addItem(info.portName());
        }
    ui->serialPortComboBox->setFocus();
}


void GUIPanel::on_pushButton_2_pressed()
{
    contadorVer++;
    if(contadorVer == 5){

        contadorVer = 0;
        ventanaGracias.setWindowTitle("Gracias a tod@s :)");
        ventanaGracias.setText("Dedicado a: Lucía, Patri, Jose, Jaime, Mar, Raúl, María, Irene, Viñu, Marta, Marina, Andrea, Luis, Nano y Pablo.\nGracias.\n");
        ventanaGracias.setStandardButtons(QMessageBox::Ok);
        ventanaGracias.setStyleSheet(
            "QMessageBox { background-color: black; }"
            "QLabel { color: yellow; }"
            "QPushButton { background-color: yellow; color: black; }"
            );
        ventanaGracias.show();
    }
}

