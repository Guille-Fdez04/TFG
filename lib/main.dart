import 'dart:io';

import 'package:flutter/material.dart'; //Libreria basica para la IU
import 'package:mqtt_client/mqtt_client.dart'; //Cliente MQTT
import 'dart:async'; //Para ejecutar funciones asincronas
import 'package:mqtt_client/mqtt_server_client.dart'; //Servidor MQTT
import 'package:percent_indicator/flutter_percent_indicator.dart'; //Libreria para mostrar las barras indicadoras
import 'dart:convert'; //Para conversiones de datos
import 'package:percent_indicator/percent_indicator.dart'; //Para tener las barras indicadoras


//Variables globales
bool servidorConectado = false; 
String dirIP = '10.0.2.2'; //Direccion IP del servidor MQTT, por defecto 10.0.2.2
late MqttServerClient client; //Cliente MQTT

void main() {
  runApp(const MyApp());
}

//Widget raiz de la aplicacion, de este cuelgan todos los demas
class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(home: MqttPage());
  }
}

//Creo un widget Form para recoger el texto introducido
class MyCustomForm extends StatefulWidget {
  const MyCustomForm({super.key, required this.controladorTexto});

  final TextEditingController controladorTexto;
  //final String defaultVal;

  @override
  State<MyCustomForm> createState() => _MyCustomFormState();
}

//Defino la clase correspondiente al estado
//En esta clase se almacena la informacion correspondiente al estado
class _MyCustomFormState extends State<MyCustomForm> {
  @override
  Widget build(BuildContext context) {
    return TextFormField(
      decoration: const InputDecoration(border: OutlineInputBorder()),
      controller: widget.controladorTexto,
      autofocus: true,
    );
  }
}

//Pagina principal donde se muestran todos los widgets con la informacion
//y se realizan las interacciones con el usuario
class MqttPage extends StatefulWidget {
  const MqttPage({super.key});

  @override
  State<MqttPage> createState() => _MqttPageState();
}

//Estado del widget MqttPage
class _MqttPageState extends State<MqttPage> {
  //Para conectarse a mi pc se usa el puerto 10.0.2.2, que equivale a usar localhost en mi pc

  //VARIABLES DE LA CLASE
  double temperatura = 0.0;
  double hr = 0.0;
  int pres = 0;
  bool test = false;
  bool estabilidad = false;
  String altitud = "0";
  double cabeceo = 0,
      alabeo = 0,
      posicion_aceleracion_x = 117.0,
      posicion_aceleracion_y = 117.0,
      aceleracionZ = 1.2,
      aceleracionMaxima = 1.0;
  String txtEstabilidad = "CARGA SIN CONFIGURAR";
  String txtConexion = "DESCONECTADO";
  String usuario = "";
  String pwd = "";
  String topicIntroducido = "carga";
  String statusText = "";
  bool suscrito = false;
  bool brokerPublico = false;

  final controladorUsuario = TextEditingController();
  final controladorContrasena = TextEditingController();
  final controladorTopic = TextEditingController();
  final controladorIP = TextEditingController();

  @override
  void initState() {
    super.initState();
  }

  //Callback para cuando se desconecta el servidor
  void onDisconnected() {
    setState(() {
      servidorConectado = false;
    });
  }

  //Callback para cuando la conexion ha tenido exito
  void onConnected() {
    setState(() {
      servidorConectado = true;
      statusText = "CONECTADO";
    });
  }

  //Callback para cuando nos hemos suscrito a un topic
  void onSubscribed(String topic) {
    setState(() {
      suscrito = true;
      statusText = "Suscrito al topic $topic";
    });
    //Si nos hemos suscrito con exito al topic, escuchamos los mensajes del servidor, y reaccionamos
    client.updates!.listen(
      (List<MqttReceivedMessage<MqttMessage?>> messages) {
        final recMess = messages[0].payload as MqttPublishMessage;

        final payload = MqttPublishPayload.bytesToStringAsString(
          recMess.payload.message,
        );

        final data = jsonDecode(payload);

        //Hemos recibido un mensaje, ahora comprobamos de que mensaje se trata

        if (messages[0].topic == "/$topicIntroducido/temperatura") {
          setState(() {
            temperatura = (data["valor"] as num).toDouble();
            if (temperatura > 100.0) {
              temperatura = 100.0;
            } else if (temperatura < 0.0) {
              temperatura = 0;
            }
          });
        } else if (messages[0].topic == "/$topicIntroducido/hr") {
          setState(() {
            hr = (data["valor"] as num).toDouble();
          });
        } else if (messages[0].topic == "/$topicIntroducido/presion") {
          setState(() {
            pres = (data["valor"] / 100 as num).toInt();
          });
        } else if (messages[0].topic == "/$topicIntroducido/altitud") {
          setState(() {
            altitud =
                ("${data["parte_entera"].toString()}.${data["parte_fraccionaria"].toString()}");
          });
        } else if (messages[0].topic == "/$topicIntroducido/angulos") {
          setState(() {
            cabeceo = (data["cabeceo"] as num).toDouble();
            alabeo = (data["alabeo"] as num).toDouble();
          });
        } else if (messages[0].topic == "/$topicIntroducido/aceleracion") {
          setState(() {
            posicion_aceleracion_x =
                (125 - 8 + 42 * ((data["valor_x"] as num).toDouble()));
            posicion_aceleracion_y =
                (125 - 8 + 42 * -((data["valor_y"] as num).toDouble()));
            aceleracionZ = (data["valor_z"] as num).toDouble();
            aceleracionMaxima = (data["max_G"] as num).toDouble();
          });
        } else if (messages[0].topic == "/$topicIntroducido/estabilidad") {
          setState(() {
            if (data["valor"] == true) {
              txtEstabilidad = "CARGA ESTABLE";
              estabilidad = true;
            } else {
              txtEstabilidad = "CARGA INESTABLE";
              estabilidad = false;
            }
          });
          }
      },
      onError: (e) {
        //print("onError valor $e");
        setState(() {
          statusText = "Servidor desconectado";
        });
      },
    );
  }

  //Funcion que realiza la conexion al servidor mqtt
  Future<void> connectMQTT() async {
    //Inicializacion del cliente
    client = MqttServerClient(dirIP, usuario);

    //%%%%%%%%%%Configuracion del cliente%%%%%%%%%%%%
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    client.logging(on: false); //No vamos a usar logging

    client.setProtocolV311(); //MQTT version 3.1.1

    final connMess = MqttConnectMessage()
        .withClientIdentifier(usuario) //ID del cliente igual al usuario
        .startClean(); //Iniciamos un nuevo cliente cada vez que se reinicia la aplicacion

    if(brokerPublico == false){
      connMess.authenticateAs(usuario, pwd); //Credenciales de autenticacion (usuario,contraseña)
    }

    client.connectionMessage = connMess;

    //Registro las manejadoras
    client.onDisconnected = onDisconnected;
    client.onConnected = onConnected;
    client.onSubscribed = onSubscribed;
    client.port = 1883;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    try {
      await client.connect(); //Se intenta conectar el cliente con el servidor
    } on NoConnectionException catch (e) { //Si falla la conexion
      servidorConectado = false;
      //print("Client Exception -  $e");

      if (client.connectionStatus!.returnCode ==
          MqttConnectReturnCode.notAuthorized) {
        statusText = "USUARIO Y CONTRASEÑA INCORRECTOS";
      }

      client.disconnect();
      setState(() {
        txtConexion = "DESCONECTADO, ERROR DEL CLIENTE";
      });
    } on SocketException {
      servidorConectado = false;

      setState(() {
        txtConexion = "NO SE HA PODIDO CONECTAR CON EL SERVIDOR";
      });

      client.disconnect();
    } on OSError catch (e) {
      servidorConectado = false;
      //print("OS Error valor $e");
    }
  }

  @override
  Widget build(BuildContext context) { //UI
    if (servidorConectado == true) {
      txtConexion = "$dirIP CONECTADO";
    } else {
      txtConexion = "DESCONECTADO";
    }

    //Widget para tener distintas ventanas "Tabs"
    return DefaultTabController(
      length: 3, //Numero de TABS que tiene nuestra app
      child: Scaffold(
        appBar: AppBar(
          title: Text(
            "VISUALIZADOR MQTT - Guillermo Fernández Torres",
            style: TextStyle(fontSize: 14),
          ),
          bottom: TabBar(
            tabs: [ //Iconos de las Tabs
              Tab(icon: Icon(Icons.settings)),
              Tab(icon: Icon(Icons.speed)),
              Tab(icon: Icon(Icons.my_location)),
            ],
          ),
        ),
        body: TabBarView(
          children: [
            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //_____________TAB 1_____________
            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            Padding(
              padding: EdgeInsets.all(15),
              child: Column(
                children: [
                  Text('SERVIDOR $txtConexion', style: TextStyle(fontSize: 15)),

                  SizedBox(height: 15),

                  Text(
                    'Dirección del servidor: ',
                    style: TextStyle(fontSize: 15),
                  ),

                  MyCustomForm(
                    controladorTexto: controladorIP,
                  ), //Direccion IP del servidor

                  SizedBox(height: 15),

                  Text('Introduzca usuario: ', style: TextStyle(fontSize: 15)),

                  MyCustomForm(controladorTexto: controladorUsuario,
                  ), //Usuario

                  Text(
                    'Introduzca contraseña: ',
                    style: TextStyle(fontSize: 15),
                  ),

                  MyCustomForm(
                    controladorTexto: controladorContrasena,
                  ), //Contraseña

                  SizedBox(height: 10),

                  if (!servidorConectado)
                    ElevatedButton(
                      onPressed: () {
                        if ((controladorUsuario.text == "" ||
                            controladorContrasena.text == "") && brokerPublico == false) {
                          //GESTIONAR USUARIO Y CONTRASEÑA EN BLANCO
                          setState(() {
                            statusText = "INTRODUZCA USUARIO Y CONTRASEÑA";
                          });
                        } else {
                          if (controladorIP.text == "") {
                            statusText = "Introduzca una dirección IP";
                          } else {
                            usuario = controladorUsuario.text;
                            pwd = controladorContrasena.text;
                            dirIP = controladorIP.text;
                            setState(() {
                              statusText = "Conectando...";
                            });
                            connectMQTT();
                          }
                        }
                      },
                      style: ElevatedButton.styleFrom(
                        textStyle: TextStyle(fontSize: 15),
                      ),
                      child: Text('Conectar al servidor'),
                    ),

                  if (servidorConectado)
                    ElevatedButton(
                      onPressed: () {
                        client.disconnect();
                        statusText = "DESCONECTADO";
                      },
                      style: ElevatedButton.styleFrom(
                        textStyle: TextStyle(fontSize: 15),
                      ),
                      child: Text('Desconectar del servidor'),
                    ),

                  SizedBox(height: 10),

                  Text('Introduzca el Topic: ', style: TextStyle(fontSize: 15)),

                  MyCustomForm(controladorTexto: controladorTopic,
                  ), //Topic

                  SizedBox(height: 15),

                  if(!suscrito)
                  ElevatedButton(onPressed: (){
                    topicIntroducido = controladorTopic.text;
                        if (topicIntroducido != "") {
                          client.subscribe(
                            "/$topicIntroducido/#",
                            MqttQos.atMostOnce,
                          );
                        } else {
                          statusText = "Introduzca un topic válido";
                        }
                  }, 
                  child: Text('Conectar al topic', style: TextStyle(fontSize: 15),)),

                  if(suscrito)
                  ElevatedButton(onPressed: (){
                    setState((){
                      client.unsubscribe(topicIntroducido);
                      suscrito = false;
                    });
                  }, 
                  child: Text('Desconectar del topic', style: TextStyle(fontSize: 15),)),

                  SizedBox(height: 10),

                  Text(statusText, style: TextStyle(fontSize: 15)),

                  SizedBox(height: 10),

                  Text('Usar un broker público (Sin usuario ni contraseña)', style: TextStyle(fontSize: 12),),
                  Checkbox(
                    value:brokerPublico,
                    onChanged: (bool ?value){
                      setState(() {
                        brokerPublico = value!;
                      });
                    },
                  ),
                ],
              ),
            ),

            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //_____________TAB 2_____________
            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            Column(
              children: [
                Text('SERVIDOR $txtConexion', style: TextStyle(fontSize: 15)),

                SizedBox(height: 15),

                Text('Temperatura:', style: TextStyle(fontSize: 15)),
                Padding(
                  padding: EdgeInsets.only(left: 60.0, top: 5.0, bottom: 5.0),
                  child: LinearPercentIndicator(
                    width: 300.0,
                    lineHeight: 40.0,
                    percent:
                        (temperatura /
                        100.0), //Asumiendo que el maximo son 100ºC y el minimo 0ºC
                    backgroundColor: Colors.blueGrey,
                    progressColor: Colors.indigo,
                    center: Text(
                      "${temperatura.toStringAsFixed(2)} ºC",
                      style: TextStyle(
                        fontSize: 15,
                        fontWeight: FontWeight.bold,
                        color: Colors.white,
                      ),
                    ),
                  ),
                ),
                Text('Humedad relativa: ', style: TextStyle(fontSize: 15)),
                Padding(
                  padding: EdgeInsets.only(left: 60.0, top: 5.0, bottom: 5.0),
                  child: LinearPercentIndicator(
                    width: 300.0,
                    lineHeight: 40.0,
                    percent:
                        (hr /
                        100), //Asumiendo que el maximo son 100% y el minimo 0%
                    backgroundColor: Colors.blueGrey,
                    progressColor: Colors.indigoAccent,
                    center: Text(
                      "${hr.toStringAsFixed(2)} %",
                      style: TextStyle(
                        fontSize: 15,
                        fontWeight: FontWeight.bold,
                        color: Colors.white,
                      ),
                    ),
                  ),
                ),
                Text('Presión :', style: TextStyle(fontSize: 15)),
                Padding(
                  padding: EdgeInsets.only(left: 60.0, top: 5.0, bottom: 5.0),
                  child: LinearPercentIndicator(
                    width: 300.0,
                    lineHeight: 40.0,
                    percent: (pres/(2.0*1013.25)), //Asumiendo que el maximo son 2 atm y el minimo 0 atm
                    backgroundColor: Colors.blueGrey,
                    progressColor: Colors.lightBlue,
                    center: Text(
                      "${pres.toStringAsFixed(0)} hPa",
                      style: TextStyle(
                        fontSize: 15,
                        fontWeight: FontWeight.bold,
                        color: Colors.white,
                      ),
                    ),
                  ),
                ),
                Text("Altitud: $altitud m", style: TextStyle(fontSize: 15)),
                Padding(
                  padding: EdgeInsets.all(20.0),
                  child: Row(
                    children: [
                      Column(
                        children: [
                          Stack(
                            children: [
                              Image(
                                image: AssetImage('assets/background_inc.png'),
                                width: 180,
                                height: 180,
                              ),
                              Transform.rotate(
                                angle: -(cabeceo * (3.1416 / 180.0)),
                                child: Image(
                                  image: AssetImage('assets/lateral_inc.png'),
                                  width: 180,
                                  height: 180,
                                ),
                              ),
                            ],
                          ),
                          Text(
                            'Cabeceo: $cabeceo º',
                            style: TextStyle(fontSize: 15.0),
                          ),
                        ],
                      ),
                      SizedBox(width: 10.0),
                      Column(
                        children: [
                          Stack(
                            children: [
                              Image(
                                image: AssetImage('assets/background_inc.png'),
                                width: 180,
                                height: 180,
                              ),
                              Transform.rotate(
                                angle: -(alabeo * (3.1416 / 180.0)),
                                child: Image(
                                  image: AssetImage('assets/frontal_inc.png'),
                                  width: 180,
                                  height: 180,
                                ),
                              ),
                            ],
                          ),
                          Text(
                            'Alabeo: $alabeo º',
                            style: TextStyle(fontSize: 15),
                          ),
                        ],
                      ),
                    ],
                  ),
                ),
                Text(
                  txtEstabilidad,
                  style: TextStyle(fontSize: 15.0, fontWeight: FontWeight.bold),
                ),
              ],
            ),

            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //_____________TAB 3_____________
            //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            Column(
              children: [
                Text('SERVIDOR $txtConexion', style: TextStyle(fontSize: 15)),

                SizedBox(height: 15),

                SizedBox(height: 10.0),
                Stack(
                  children: [
                    Image(
                      image: AssetImage('assets/Acelerometro.png'),
                      width: 250,
                      height: 250,
                    ),
                    Transform.translate(
                      offset: Offset(
                        posicion_aceleracion_x,
                        posicion_aceleracion_y,
                      ),
                      child: Image(
                        image: AssetImage('assets/pointer.png'),
                        height: 16,
                        width: 16,
                      ),
                    ),
                  ],
                ),
                SizedBox(
                  height: 15.0,
                ), //percent: 0.5 + (aceleracionZ * (1.0 / 8.0))
                LinearPercentIndicator(
                  width: MediaQuery.of(context).size.width - 20,
                  percent: 0.5 + (aceleracionZ * (1.0 / 8.0)),
                  lineHeight: 40.0,
                  backgroundColor: Colors.blueGrey,
                  progressColor: Colors.indigo,
                  center: Text(
                    'Eje Z: ${aceleracionZ.toStringAsFixed(3)} g',
                    style: TextStyle(
                      color: Colors.white,
                      fontSize: 15,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),

                SizedBox(height: 15.0),

                Text("Aceleración Máxima: ${aceleracionMaxima.toStringAsFixed(3)} g",
                style: TextStyle(fontSize: 15),),

                Padding(
                  padding: EdgeInsets.all(12),
                  child: Text(
                    txtEstabilidad,
                    style: TextStyle(
                      fontSize: 15.0,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
