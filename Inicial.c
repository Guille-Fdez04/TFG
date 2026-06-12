#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"       // TIVA: Definiciones del mapa de memoria
#include "inc/hw_types.h"        // TIVA: Definiciones API
#include "inc/hw_ints.h"         // TIVA: Definiciones para configuracion de interrupciones
#include "driverlib/gpio.h"      // TIVA: Funciones API de GPIO
#include "driverlib/pin_map.h"   // TIVA: Mapa de pines del chip
#include "driverlib/rom.h"       // TIVA: Funciones API incluidas en ROM de micro (ROM_)
#include "driverlib/rom_map.h"   // TIVA: Para usar la opciÃ³n MAP en las funciones API (MAP_)
#include "driverlib/sysctl.h"    // TIVA: Funciones API control del sistema
#include "driverlib/uart.h"      // TIVA: Funciones API manejo UART
#include "driverlib/interrupt.h" // TIVA: Funciones API manejo de interrupciones
#include "utils/uartstdioMod.h"  // TIVA: Funciones API UARTSTDIO (printf)
#include "driverlib/adc.h"       // TIVA: Funciones API manejo de ADC
#include "driverlib/timer.h"     // TIVA: Funciones API manejo de timers
#include "drivers/buttons.h"     // TIVA: Funciones API manejo de botones
#include "drivers/rgb.h"         // TIVA: Funciones API manejo de leds con PWM
#include "FreeRTOS.h"            // FreeRTOS: definiciones generales
#include "task.h"                // FreeRTOS: definiciones relacionadas con tareas
#include "semphr.h"              // FreeRTOS: definiciones relacionadas con semaforos
#include "queue.h"               // FreeRTOS: definiciones relacionadas con colas de mensajes
#include "event_groups.h"
#include "timers.h"
#include "utils/cpu_usage.h"
#include "commands.h"
#include <serial2USBprotocol.h>
#include <usb_dev_serial.h>
#include "usb_messages_table.h"
#include "driverlib/debug.h"

//INCLUDES DEL PROTOCOLO I2C
#include "sensorlib/i2cm_drv.h"

//INCLUDES PARA EL SENSOR DE PRESION
#include "sensorlib/hw_bmp180.h"
#include "sensorlib/bmp180.h"

//INCLUDES PARA EL SENSOR DE HUMEDAD
#include "sensorlib/hw_sht21.h"
#include "sensorlib/sht21.h"

//INCLUDES PARA EL GIROSCOPO, ACELEROMETRO Y MAGNETOMETRO
#include "sensorlib/hw_mpu9150.h"
#include "sensorlib/hw_ak8975.h"
#include "sensorlib/ak8975.h"
#include "sensorlib/mpu9150.h"
#include "sensorlib/comp_dcm.h"

//INCLUDES PARA EL SENSOR DE TEMPERATURA
#include "sensorlib/tmp006.h"
#include "sensorlib/hw_tmp006.h"

//Definiciones de I2C y de los registros de los sensores
//---------------BMP180-----------------------------
#define BMP180_I2C_ADDRESS      0x77 //Definicion I2C del sensor
#define BMP180CTRL_MEAS 0xF4 //Registro de control
#define BMP180_OSS_MASK 0xC0 //1100 0000 -> Mascara para modificar solo el valor de oversampling



//---------------SHT21-----------------------------
#define SHT21_I2C_ADDRESS  0x40

//--------------MPU9150-------------------------
#define MPU9150_I2C_ADDRESS     0x68
#define g 9.807

//--------------TMP006------------------------------
#define TMP006_I2C_ADDRESS      0x41


#define SENSORESTASKPRIO 1
#define SENSORESTASKSIZE 256

#define BIT_CARGA_CONF 0x01

// Variables globales "main"
uint8_t freeRTOSIniciado = 0;
uint32_t g_ui32CPUUsage;
uint32_t g_ui32SystemClock;
uint8_t flag_creado=0;
uint8_t aplicacion_conectada = 0;
const float alpha = 0.1; //Constante para el filtro del MPU
float presion_asl = 102700.0f; //Presion a nivel del mar en Pa (valor por defecto)
uint8_t estadoLED=0;
uint8_t enviarUART=0;





// Variables de recursos IPC
TimerHandle_t timer_presion;
TimerHandle_t timer_boton;
SemaphoreHandle_t semaforo_presion;
SemaphoreHandle_t semaforo_humedad;
SemaphoreHandle_t semaforo_aceleracion;
SemaphoreHandle_t semaforo_temperatura;
SemaphoreHandle_t mutex_i2c;
SemaphoreHandle_t mutex_uart;
SemaphoreHandle_t mutex_usb;
static TaskHandle_t tarea_accel;
static TaskHandle_t tarea_pres;
void TimerBotonCallback(TimerHandle_t pxTimer );

//INSTANCIA GLOBAL DE I2C
tI2CMInstance g_sI2CInst;


//VARIABLES GLOBALES PARA EL SENSOR BMP180
tBMP180 g_sBMP180Inst;
volatile uint_fast8_t g_vui8DataFlag_bmp180;
volatile uint_fast8_t g_vui8ErrorFlag_bmp180;

//VARIABLES GLOBALES PARA EL SENSOR SHT21
tSHT21 g_sSHT21Inst;
volatile uint_fast8_t g_vui8DataFlag_sht21;
volatile uint_fast8_t g_vui8ErrorFlag_sht21;

//VARIALBES GLOBALES PARA EL SENSOR MPU9150
tMPU9150 g_sMPU9150Inst;
tCompDCM g_sCompDCMInst;
volatile uint_fast8_t g_vui8I2CDoneFlag_mpu9150;
volatile uint_fast8_t g_vui8ErrorFlag_mpu9150;

//VARIABLES GLOBALES PARA EL SENSOR TMP006
tTMP006 g_sTMP006Inst;
volatile uint_fast8_t g_vui8DataFlag_tmp006;
volatile uint_fast8_t g_vui8ErrorFlag_tmp006;





//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ulLine)
{
    if(!g_vui8ErrorFlag_bmp180){
        while(1) //Si la ejecucion esta aqui dentro, es que el RTOS o alguna de las bibliotecas de perifericos han comprobado que hay un error
            { //Mira el arbol de llamadas en el depurador y los valores de nombrefich y linea para encontrar posibles pistas.

            }
    }
    else{

        //Ha fallado el sensor de presion
        //Intento recuperarme del error reiniciandolo


    }
}
#endif



void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

//Esto se ejecuta cada Tick del sistema. LLeva la estadistica de uso de la CPU (tiempo que la CPU ha estado funcionando)
void vApplicationTickHook( void )
{
    static uint8_t ui8Count = 0;

    if (++ui8Count == 10)
    {
        g_ui32CPUUsage = CPUUsageTick();
        ui8Count = 0;
    }
    //return;
}

//Esto se ejecuta cada vez que entra a funcionar la tarea Idle
void vApplicationIdleHook (void)
{
    SysCtlSleep();
}

//Esto se ejecuta cada vez que se produce un fallo de asignacio de heap
void vApplicationMallocFailedHook (void)
{
    while(1);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//================= FUNCIONES DE CALLBACK =====================================
//Se pone el flag correspondiente a 1, y se deja que la tarea se encargue de realizar el trabajo

void BMP180AppCallback(void* pvCallbackData, uint_fast8_t ui8Status)
{
    if(ui8Status == I2CM_STATUS_SUCCESS)
    {
        g_vui8DataFlag_bmp180 = 1;

    }
    g_vui8ErrorFlag_bmp180 = ui8Status;
}

void SHT21AppCallback(void* pvCallbackData, uint_fast8_t ui8Status)
{
    if(ui8Status == I2CM_STATUS_SUCCESS)
    {
        g_vui8DataFlag_sht21 = 1;

    }
    g_vui8ErrorFlag_sht21 = ui8Status;
}

void
MPU9150AppCallback(void *pvCallbackData, uint_fast8_t ui8Status)
{

    if(ui8Status == I2CM_STATUS_SUCCESS)
    {
        g_vui8I2CDoneFlag_mpu9150 = 1;

    }


    g_vui8ErrorFlag_mpu9150 = ui8Status;
}

void
TMP006AppCallback(void *pvCallbackData, uint_fast8_t ui8Status)
{

    if(ui8Status == I2CM_STATUS_SUCCESS)
    {
        g_vui8DataFlag_tmp006 = 1;
    }


    g_vui8ErrorFlag_tmp006 = ui8Status;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



//*****************************************************************************
//================= MANEJADORA DE INTERRUPCION ===============================
void
I2CIntHandler(void)
{

    I2CMIntHandler(&g_sI2CInst);
}


//*****************************************************************************


//*****************************************************************************
//================= MANEJADORAS DE ERROR ======================================
void AppErrorHandler(char *pcFilename, uint_fast32_t ui32Line){
    //Ha ocurrido un error
    while(1){}
}


//*****************************************************************************


//*****************************************************************************
//================= FUNCIONES DE ESPERA =======================================
void BMP180AppI2CWait(char *pcFilename, uint_fast32_t ui32Line){

    uint8_t suspenderTarea=0;
    //Detengo las tareas, para que no interrumpan la transacción I2C
    vTaskSuspendAll();

    while((g_vui8DataFlag_bmp180 == 0) && (g_vui8ErrorFlag_bmp180 == 0)){

        //MAP_SysCtlSleep();

    }

    if(g_vui8ErrorFlag_bmp180) // Ha ocurrido un error
    {
        //Ha ocurrido un error, se intenta resolver reiniciando el periferico
        g_vui8DataFlag_bmp180 = 0;
        g_vui8ErrorFlag_bmp180 = 0;
        uint8_t contador=0;

        // Initialize the BMP180.

        BMP180Init(&g_sBMP180Inst, &g_sI2CInst, BMP180_I2C_ADDRESS,
                   BMP180AppCallback, &g_sBMP180Inst);

        MAP_SysCtlDelay(MAP_SysCtlClockGet()/10);

        while(!g_vui8DataFlag_bmp180 && contador<=20)
        {
            contador++;
        }

        g_vui8DataFlag_bmp180 = 0;


        if(g_vui8ErrorFlag_bmp180 || contador == 20){
            //Si el error persiste, se suspende la tarea
            suspenderTarea=1;

        }


        //AppErrorHandler(pcFilename, ui32Line);
    }

    //Si no hay errores, se resumen las tareas de FreeRTOS
    if(!xTaskResumeAll()){
        taskYIELD();
    }

    if(suspenderTarea){
        vTaskSuspend(tarea_pres);
        g_vui8ErrorFlag_bmp180 = 0;
    }

    g_vui8DataFlag_bmp180 = 0;

}

void
SHT21AppI2CWait(char *pcFilename, uint_fast32_t ui32Line)
{

    //Si se han creado las tareas de FreeRTOS, las suspendemos para que al I2C le de tiempo a completar la transaccion
    if(freeRTOSIniciado == 1){
        vTaskSuspendAll();
    }

    while((g_vui8DataFlag_sht21 == 0) && (g_vui8ErrorFlag_sht21 == 0))
    {
        MAP_SysCtlSleep();
    }


    if(g_vui8ErrorFlag_sht21)
    {
        AppErrorHandler(pcFilename, ui32Line);
    }

    //Si no hay errores, se resumen las tareas de FreeRTOS
    if(freeRTOSIniciado == 1){
        if(!xTaskResumeAll()){
                taskYIELD();
            }
    }

    g_vui8DataFlag_sht21 = 0;
}

void
MPU9150AppI2CWait(char *pcFilename, uint_fast32_t ui32Line)
{

    //Si se han creado las tareas de FreeRTOS, las suspendemos para que al I2C le de tiempo a completar la transaccion
    if(freeRTOSIniciado == 1){
        vTaskSuspendAll();
    }

    while((g_vui8I2CDoneFlag_mpu9150 == 0) && (g_vui8ErrorFlag_mpu9150 == 0))
    {
        MAP_SysCtlSleep();
    }


    if(g_vui8ErrorFlag_mpu9150)
    {
        AppErrorHandler(pcFilename, ui32Line);
    }

    //Si no hay errores, se resumen las tareas de FreeRTOS
    if(freeRTOSIniciado == 1){
        if(!xTaskResumeAll()){
            taskYIELD();
        }
    }

    g_vui8I2CDoneFlag_mpu9150 = 0;
}

TMP006AppI2CWait(char *pcFilename, uint_fast32_t ui32Line){

    //Si se han creado las tareas de FreeRTOS, las suspendemos para que al I2C le de tiempo a completar la transaccion
    if(freeRTOSIniciado == 1){
        vTaskSuspendAll();
    }

    while((g_vui8DataFlag_tmp006 == 0) && (g_vui8ErrorFlag_tmp006 == 0))
    {
        MAP_SysCtlSleep();
    }


    if(g_vui8ErrorFlag_tmp006)
    {
        AppErrorHandler(pcFilename, ui32Line);
    }


    //Si no hay errores, se resumen las tareas de FreeRTOS
    if(freeRTOSIniciado == 1){
        if(!xTaskResumeAll()){
            taskYIELD();
        }
    }

    g_vui8DataFlag_tmp006 = 0;
}

//*****************************************************************************


void vTimerCallback( TimerHandle_t pxTimer ){
    //Callback del timer que controla la frecuencia con la que se hacen las lecturas de presion y humedad
    xSemaphoreGive(semaforo_presion);
    xSemaphoreGive(semaforo_humedad);

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//------------------------------FUNCIONES DE INICIALIZACION-------------------------------------------

void InicializarI2C(void){
    //Funcion que inicializa to lo necesario para el uso del protocolo i2C

    // The I2C3 peripheral must be enabled before use.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Configure the pin muxing for I2C3 functions on port D0 and D1.
    // This step is not necessary if your part does not support pin muxing.
    //
    MAP_GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    MAP_GPIOPinConfigure(GPIO_PD1_I2C3SDA);

    // Select the I2C function for these pins.  This function will also
    // configure the GPIO pins pins for I2C operation, setting them to
    // open-drain operation with weak pull-ups.  Consult the data sheet
    // to see which functions are allocated per pin.
    //
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
    MAP_GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);

    MAP_IntMasterEnable(); //Activo las interrupciones

    //
    // Initialize the I2C3 peripheral.
    //
    I2CMInit(&g_sI2CInst, I2C3_BASE, INT_I2C3, 0xff, 0xff, MAP_SysCtlClockGet());

    ROM_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_I2C3); //Activo el periferico en modo de bajo consumo

}

void InicializarMPU9150(void){


    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //Se habilita el puerto B para las interrupciones
    ROM_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_GPIOB); //Tambien en modo de bajo consumo

    //Se configuran las interrupciones que va a generar el sensor
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_2);
    MAP_GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);
    IntPrioritySet(INT_GPIOB,configMAX_SYSCALL_INTERRUPT_PRIORITY); //Le damos maxima prioridad a la interrupcion para poder usar


    //Funcion de inicializacion de la libreria sensorlib
    MPU9150Init(&g_sMPU9150Inst, &g_sI2CInst, MPU9150_I2C_ADDRESS,
                    MPU9150AppCallback, &g_sMPU9150Inst);

    MPU9150AppI2CWait(__FILE__, __LINE__);


    //Configuraciones del sensor


    //Ancho de banda de los sensores
    MPU9150ReadModifyWrite(&g_sMPU9150Inst, MPU9150_O_CONFIG,
                           ~MPU9150_CONFIG_DLPF_CFG_M, MPU9150_CONFIG_DLPF_CFG_5_5,
                           MPU9150AppCallback, &g_sMPU9150Inst);

    //
    // Wait for transaction to complete
    //
    MPU9150AppI2CWait(__FILE__, __LINE__);

    //Fondo de escala del acelerometro de 4G

    MPU9150ReadModifyWrite(&g_sMPU9150Inst, MPU9150_O_ACCEL_CONFIG,
                           ~MPU9150_ACCEL_CONFIG_ACCEL_HPF_2_5HZ,
                           MPU9150_ACCEL_CONFIG_AFS_SEL_4G, MPU9150AppCallback,
                           &g_sMPU9150Inst);

    MPU9150AppI2CWait(__FILE__, __LINE__);

    //Fondo de escala del giroscopio de 500 º/s
    MPU9150ReadModifyWrite(&g_sMPU9150Inst, MPU9150_O_GYRO_CONFIG,
                           ~MPU9150_GYRO_CONFIG_FS_SEL_M ,
                           MPU9150_GYRO_CONFIG_FS_SEL_500, MPU9150AppCallback,
                           &g_sMPU9150Inst);

    MPU9150AppI2CWait(__FILE__, __LINE__);


    //Configuro las interrupciones

    //Pin activo a nivel bajo, borrado del flag al realizar la lectura, latch en el pin de la interrupcion
    MPU9150ReadModifyWrite(&g_sMPU9150Inst, MPU9150_O_INT_PIN_CFG,
                ~(MPU9150_INT_PIN_CFG_INT_LEVEL | MPU9150_INT_PIN_CFG_INT_RD_CLEAR
                        | MPU9150_INT_PIN_CFG_LATCH_INT_EN),
                MPU9150_INT_PIN_CFG_INT_LEVEL | MPU9150_INT_PIN_CFG_INT_RD_CLEAR
                        | MPU9150_INT_PIN_CFG_LATCH_INT_EN, MPU9150AppCallback,
                &g_sMPU9150Inst);

    MPU9150AppI2CWait(__FILE__, __LINE__);


    //Seleccion de la frecuencia de muestreo, la frecuencia de muestreo es 1 kHz, ya que el ancho de banda de los filtros es 5 Hz, la frecuencia dividida con el
    //divisor es: f_div = 1 kHz/(div + 1)

    MPU9150ReadModifyWrite(&g_sMPU9150Inst, MPU9150_O_SMPLRT_DIV,
                           ~MPU9150_SMPLRT_DIV_M, 4, MPU9150AppCallback, &g_sMPU9150Inst); //Frecuencia de muestreo de division de 200 Hz


    MPU9150AppI2CWait(__FILE__, __LINE__);

    CompDCMInit(&g_sCompDCMInst, 1.0f / 200.0f, 0.2f, 0.6f, 0.2f); //Inicializacion del sistema de DCM


}

void InicializarBMP180(void){

    g_vui8DataFlag_bmp180 = 0;
        g_vui8ErrorFlag_bmp180 = 0;

    // Initialize the BMP180.

    BMP180Init(&g_sBMP180Inst, &g_sI2CInst, BMP180_I2C_ADDRESS,
               BMP180AppCallback, &g_sBMP180Inst);

    MAP_SysCtlDelay(MAP_SysCtlClockGet()/10);

    while(!g_vui8DataFlag_bmp180)
    {
    }

    g_vui8DataFlag_bmp180 = 0;

    //Configuracion de oversampling
    BMP180ReadModifyWrite(&g_sBMP180Inst,BMP180CTRL_MEAS,0x3F,0xC0,BMP180AppCallback,&g_sBMP180Inst);
    while(!g_vui8DataFlag_bmp180)
        {
        }

        g_vui8DataFlag_bmp180 = 0;

}

void InicializarSHT21(void){

    //Orden de inicializacion
    SHT21Init(&g_sSHT21Inst, &g_sI2CInst, SHT21_I2C_ADDRESS,
                  SHT21AppCallback, &g_sSHT21Inst);
    SHT21AppI2CWait(__FILE__, __LINE__);

    //En el punto 5.1 del datasheet del sensor se especifica que el sensor tarda,
    //como maximo, 15 ms hasta que esta listo para aceptar comandos, por eso hacemos una espera de 20 ms
    MAP_SysCtlDelay(MAP_SysCtlClockGet() / (50 * 3));

}

void InicializarTMP006(void){

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); //Se habilita el puerto E para las interrupciones
    ROM_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_GPIOE); //Tambien en modo de bajo consumo


    MAP_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_0);
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_PIN_0);
    MAP_GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
    IntPrioritySet(INT_GPIOE,configMAX_SYSCALL_INTERRUPT_PRIORITY); //Le damos maxima prioridad a la interrupcion para poder usar
        //funciones de FreeRTOS dentro de la ISR

    TMP006Init(&g_sTMP006Inst, &g_sI2CInst, TMP006_I2C_ADDRESS,
                   TMP006AppCallback, &g_sTMP006Inst);

    TMP006AppI2CWait(__FILE__, __LINE__);

    MAP_SysCtlDelay(MAP_SysCtlClockGet() / (100 * 3));

    //Activamos el bit de DRDY data ready

    TMP006ReadModifyWrite(&g_sTMP006Inst, TMP006_O_CONFIG,
                          ~TMP006_CONFIG_EN_DRDY_PIN_M,
                          TMP006_CONFIG_EN_DRDY_PIN, TMP006AppCallback,
                          &g_sTMP006Inst);

    TMP006AppI2CWait(__FILE__, __LINE__);

    //Tasa de conversion por defecto (Todo)
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Filtrado de los angulos
float filtro(float entrada, float salida, float coeficiente, float max, float min){
    float temp = entrada - salida;
    if(temp> max){
        temp = (max - 0.1f);
    }
    if(temp < min){
        temp = (min + 0.1f);
    }
    temp = salida + (coeficiente*temp);
    if(temp> max){
        temp = (max - 1);
    }
    if(temp < min){
        temp = (min + 0.1f);
    }
    return temp;
}



//Pequeña rutina para mandar un mensaje por USB
void mandarporUSB(int32_t i32Numdatos,uint8_t *pui8Frame){

    if(xSemaphoreTake(mutex_usb,2000/portTICK_PERIOD_MS) == pdTRUE){
        //Si el semaforo esta abierto, mandamos el paquete
        send_frame(pui8Frame,i32Numdatos);
        xSemaphoreGive(mutex_usb);
    }
    else{
        //Si no, entendemos que la aplicacion se ha desconectado
        aplicacion_conectada=0;
    }

}


//*****************************************************************************
//
// Codigo de tarea que procesa los mensajes recibidos a traves del canal USB
//
//*****************************************************************************
static portTASK_FUNCTION( USBMessageProcessingTask, pvParameters ){

    uint8_t pui8Frame[MAX_FRAME_SIZE];	//Ojo, esto hace que esta tarea necesite bastante pila
    int32_t i32Numdatos;
    uint8_t ui8Message;
    void *ptrtoreceivedparam;
    uint32_t ui32Errors=0;


    ( void ) pvParameters;


    for(;;)
    {
        //Espera hasta que se reciba una trama con datos serializados por el interfaz USB
        i32Numdatos=receive_frame(pui8Frame,MAX_FRAME_SIZE); //Esta funcion es bloqueante
        if (i32Numdatos>0)
        {	//Si no hay error, proceso la trama que ha llegado.
            i32Numdatos=destuff_and_check_checksum(pui8Frame,i32Numdatos); // Primero, "destuffing" y comprobaciï¿½n checksum
            if (i32Numdatos<0)
            {
                //Error de checksum (PROT_ERROR_BAD_CHECKSUM), ignorar el paquete
                ui32Errors++;
                // Procesamiento del error (TODO, POR HACER!!)
            }
            else
            {
                //El paquete esta bien, luego procedo a tratarlo.
                //Obtiene el valor del campo mensaje
                ui8Message=decode_message_type(pui8Frame);
                //Obtiene un puntero al campo de parametros y su tamanio.
                i32Numdatos=get_message_param_pointer(pui8Frame,i32Numdatos,&ptrtoreceivedparam);
                switch(ui8Message)
                {
                case MENSAJE_PING :

                    //A un mensaje de ping se responde con el propio mensaje
                    i32Numdatos=create_frame(pui8Frame,ui8Message,0,0,MAX_FRAME_SIZE);
                    if (i32Numdatos>=0)
                    {
                        xSemaphoreTake(mutex_usb,portMAX_DELAY);
                        send_frame(pui8Frame,i32Numdatos);
                        xSemaphoreGive(mutex_usb);
                    }

                    break;

                case MENSAJE_APLICACION:
                {

                    PARAM_MENSAJE_APLICACION parametro;
                    if (check_and_extract_message_param(ptrtoreceivedparam, i32Numdatos, sizeof(parametro),&parametro)>0){
                        aplicacion_conectada = parametro.estado;
                    }

                }
                break;

                case MENSAJE_PRESION_ASL:
                {
                    PARAM_MENSAJE_PRES_ASL parametro;
                    if (check_and_extract_message_param(ptrtoreceivedparam, i32Numdatos, sizeof(parametro),&parametro)>0){
                        presion_asl = parametro.presasl;
                    }
                }
                break;
                default:
                {
                    PARAM_MENSAJE_NO_IMPLEMENTADO parametro;
                    parametro.message=ui8Message;
                    //El mensaje esta bien pero no esta implementado
                    i32Numdatos=create_frame(pui8Frame,MENSAJE_NO_IMPLEMENTADO,&parametro,sizeof(parametro),MAX_FRAME_SIZE);
                    if (i32Numdatos>=0)
                    {
                        xSemaphoreTake(mutex_usb,portMAX_DELAY);
                        send_frame(pui8Frame,i32Numdatos);
                        xSemaphoreGive(mutex_usb);
                    }
                    break;
                }
                }// switch
            }
        }else{ // if (ui32Numdatos >0)
            //Error de recepcion de trama(PROT_ERROR_RX_FRAME_TOO_LONG), ignorar el paquete
            ui32Errors++;

        }
    }
}


static portTASK_FUNCTION(TEMPTASK, pvParameters){

    float tAmbiente, tObjeto;
    float val_abs;
    int32_t parte_entera;
    uint32_t parte_fraccionaria;
    int8_t signo;

    uint8_t pui8Frame[MAX_FRAME_SIZE];
    int32_t i32Numdatos;


    UARTprintf("\033[2J");    // Clear screen
    UARTprintf("\033[H");     // Cursor a (0,0)

    UARTprintf("Temperatura:\n");
    UARTprintf("Altitud:\n");
    UARTprintf("HR:\n");
    UARTprintf("Aceleracion: \n");
    UARTprintf("Tilt: \n");
    UARTprintf("Giroscopio :\n");
    UARTprintf("Uso de CPU: \n");

    //Una vez creados los recursos FreeRTOS, se activan las interrupciones
    MAP_IntEnable(INT_GPIOE);

    while(1){

        //Espera eficiente hasta que salta la interrupcion
        xSemaphoreTake( semaforo_temperatura,portMAX_DELAY);

        //Se leen los datos de I2C
        xSemaphoreTake(mutex_i2c,portMAX_DELAY);
        TMP006DataRead(&g_sTMP006Inst, TMP006AppCallback, &g_sTMP006Inst);
        TMP006AppI2CWait(__FILE__,__LINE__);
        xSemaphoreGive(mutex_i2c);

        //Se obtiene el valor de la temperatura en punto flotante
        TMP006DataTemperatureGetFloat(&g_sTMP006Inst, &tAmbiente, &tObjeto);


        //Se convierte en punto fijo para mandarlo por el terminal de depuracion
        if(tAmbiente > 0){
            signo = 1;
        }

        else{
            signo = -1;
        }

        val_abs = fabs(tAmbiente);

        parte_entera = (int32_t)(val_abs*signo);
        parte_fraccionaria = (uint32_t)((val_abs - (uint32_t)val_abs)*100);

        if(aplicacion_conectada == 1){

                PARAM_MENSAJE_TEMP mensaje_enviar_temp;
                mensaje_enviar_temp.parte_entera = parte_entera;
                mensaje_enviar_temp.parte_fraccionaria = parte_fraccionaria;

                i32Numdatos = create_frame(pui8Frame,MENSAJE_TEMP,&mensaje_enviar_temp,sizeof(mensaje_enviar_temp),MAX_FRAME_SIZE);
                if(i32Numdatos > 0){

//                    xSemaphoreTake(mutex_usb,portMAX_DELAY);
//                    send_frame(pui8Frame,i32Numdatos);
//                    xSemaphoreGive(mutex_usb);

                    mandarporUSB(i32Numdatos,pui8Frame);

                }



        }

        if(enviarUART){
        xSemaphoreTake(mutex_uart,portMAX_DELAY);
        UARTprintf("\033[1;1HTemperatura: %d.%02d ºC",parte_entera,parte_fraccionaria);
        xSemaphoreGive(mutex_uart);
        }

    }

}

static portTASK_FUNCTION(PRESIONTASK, pvParameters){


    uint8_t pui8Frame[MAX_FRAME_SIZE];
    int32_t i32Numdatos;

    float fPressure,fAltitud, fAltitud_filtrado;
    //float fTemp;
    int32_t parte_entera, pres_entera;
    uint32_t parte_fraccionaria, pres_fraccionaria;


    //Arrancamos el timer
    if( xTimerStart(timer_presion, 0 ) != pdPASS )
    {
        /* No se pudo arrancar el timer. */
        while(1);
    }else
        vTimerSetTimerID(timer_presion,(void*)20);

    while(1){


        //Espero a que pase el periodo de muestreo
        xSemaphoreTake( semaforo_presion,portMAX_DELAY);

        //Cojo el mutex del interfaz i2c
        xSemaphoreTake(mutex_i2c,portMAX_DELAY);

        BMP180DataRead(&g_sBMP180Inst, BMP180AppCallback, &g_sBMP180Inst); //Doy la orden al driver de leer los datos
        BMP180AppI2CWait(__FILE__,__LINE__);

        //Lectura de la preion
        BMP180DataPressureGetFloat(&g_sBMP180Inst, &fPressure);

        xSemaphoreGive(mutex_i2c);

        //Obtengo el valor de la presion, y mediante la ecuacion del datasheet la convierto a altitud

        fAltitud = 44330.0f*(1.0f - powf((fPressure/presion_asl),(1.0f/5.255f)));

        fAltitud_filtrado = filtro(fAltitud, fAltitud_filtrado, 0.65, 10000.0, -1000.0);

        //Convierto el valor de punto flotante a punto fijo

        float valor_abs = fabs(fAltitud_filtrado);
        int8_t signo;
        if(fAltitud_filtrado > 0){
            signo = 1;
        }
        else{
            signo = -1;
        }

        parte_entera = (int32_t) (valor_abs * signo);
        parte_fraccionaria = (uint32_t)((valor_abs - (uint32_t)valor_abs)*100);

//        valor_abs = fabs(fTemp);
//        if(fTemp > 0){
//            signo = 1;
//        }
//        else{
//            signo = -1;
//        }
//
//        temp_entera = (int32_t) (valor_abs * signo);
//        temp_fraccionaria = (uint32_t)((valor_abs - (uint32_t)valor_abs)*100);

        valor_abs = fabs(fPressure);
        if(fPressure > 0){
            signo = 1;
        }
        else{
            signo = -1;
        }

        pres_entera = (int32_t) (valor_abs * signo);
        pres_fraccionaria = (uint32_t)((valor_abs - (uint32_t)valor_abs)*100);

            if(aplicacion_conectada == 1){
                PARAM_MENSAJE_PRESION mensaje_enviar_presion;
                mensaje_enviar_presion.presion = pres_entera;
                mensaje_enviar_presion.parte_entera_altitud = parte_entera;
                mensaje_enviar_presion.parte_fraccionaria_altitud = parte_fraccionaria;


                i32Numdatos = create_frame(pui8Frame,MENSAJE_PRES,&mensaje_enviar_presion,sizeof(mensaje_enviar_presion),MAX_FRAME_SIZE);
                if(i32Numdatos > 0){

//                    xSemaphoreTake(mutex_usb,portMAX_DELAY);
//                    send_frame(pui8Frame,i32Numdatos);
//                    xSemaphoreGive(mutex_usb);

                    mandarporUSB(i32Numdatos,pui8Frame);

                }
            }

            if(enviarUART){
            xSemaphoreTake(mutex_uart,portMAX_DELAY);
            UARTprintf("\033[2;1HAltitud:   %d.%02d m  || Presion:  %d.%02d  Pa   ", parte_entera,parte_fraccionaria, pres_entera, pres_fraccionaria);
            xSemaphoreGive(mutex_uart);
            }
    }
}

static portTASK_FUNCTION(HUMEDADTASK, pvParameters){

    float fHumidity;
    int32_t i32IntegerPart, i32FractionPart;

    uint8_t pui8Frame[MAX_FRAME_SIZE];
    int32_t i32Numdatos;

    while(1){


        xSemaphoreTake(semaforo_humedad,portMAX_DELAY);

        //Primero se manda el comando de lectura de la humedad relativa

        xSemaphoreTake(mutex_i2c,portMAX_DELAY);
        SHT21Write(&g_sSHT21Inst, SHT21_CMD_MEAS_RH, g_sSHT21Inst.pui8Data, 0,
                   SHT21AppCallback, &g_sSHT21Inst);


        SHT21AppI2CWait(__FILE__, __LINE__);
        xSemaphoreGive(mutex_i2c);


        vTaskDelay(30/portTICK_PERIOD_MS); //En el datasheet se indica que hay que esperar, como minimo 29 ms


        xSemaphoreTake(mutex_i2c,portMAX_DELAY);
        SHT21DataRead(&g_sSHT21Inst, SHT21AppCallback, &g_sSHT21Inst);
        SHT21AppI2CWait(__FILE__, __LINE__);
        xSemaphoreGive(mutex_i2c);


        SHT21DataHumidityGetFloat(&g_sSHT21Inst, &fHumidity);

        fHumidity *= 100.0f; //La HR nos la devuelve en una escala de 0.0 a 1.0, la convertimos a porcentaje
        i32IntegerPart = (int32_t) fHumidity;
        i32FractionPart = (int32_t) (fHumidity * 10.0f);
        i32FractionPart = i32FractionPart - (i32IntegerPart * 10);
        if(i32FractionPart < 0)
        {
            i32FractionPart *= -1;
        }

        if(aplicacion_conectada == 1){
            PARAM_MENSAJE_HR mensaje_enviar_hr;
            mensaje_enviar_hr.parte_entera = i32IntegerPart;
            mensaje_enviar_hr.parte_fraccionaria = i32FractionPart;

            i32Numdatos = create_frame(pui8Frame,MENSAJE_HR,&mensaje_enviar_hr,sizeof(mensaje_enviar_hr),MAX_FRAME_SIZE);
            if(i32Numdatos > 0){

                xSemaphoreTake(mutex_usb,portMAX_DELAY);
                send_frame(pui8Frame,i32Numdatos);
                xSemaphoreGive(mutex_usb);

            }

            PARAM_MENSAJE_CPU parametro;
            parametro.cpu = (g_ui32CPUUsage+32768) >> 16;
            i32Numdatos = create_frame(pui8Frame,MENSAJE_CPU,&parametro,sizeof(parametro),MAX_FRAME_SIZE);
            if(i32Numdatos > 0){

//                xSemaphoreTake(mutex_usb,portMAX_DELAY);
//                send_frame(pui8Frame,i32Numdatos);
//                xSemaphoreGive(mutex_usb);

                mandarporUSB(i32Numdatos,pui8Frame);

            }

        }

        if(enviarUART){
        xSemaphoreTake(mutex_uart,portMAX_DELAY);
        UARTprintf("\033[3;1HHR:  %d.%2d %%  ", i32IntegerPart, i32FractionPart);
        xSemaphoreGive(mutex_uart);
        }

    }

}


static portTASK_FUNCTION(ACELERACIONTASK, pvParameters){

    uint8_t pui8Frame[MAX_FRAME_SIZE];
    int32_t i32Numdatos;

    float temp=0.0;
    float pfDatos[6];
    float *pfAccel = pfDatos;
    float *pfGyro = pfDatos + 3;
    float magneto[3];
    float aceleracion_maxima=0.0, cabeceo=0.0, alabeo=0.0, valor_abs, cabeceo_filtrado=0.0, alabeo_filtrado=0.0;
    const float pi = 3.141592654f;
    int i;
    int8_t signo;
    uint8_t contador_mensajes=0, DCM_iniciado = 0;

    int32_t parte_entera[6]; //X,Y,Z,maximo,alabeo,cabeceo
    uint32_t parte_fraccionaria[6];

    MAP_IntEnable(INT_GPIOB);
    //Activo las interrupciones
    MPU9150ReadModifyWrite(&g_sMPU9150Inst, MPU9150_O_INT_ENABLE,
                           ~(MPU9150_INT_ENABLE_DATA_RDY_EN), MPU9150_INT_ENABLE_DATA_RDY_EN,
                           MPU9150AppCallback, &g_sMPU9150Inst);
    MPU9150AppI2CWait(__FILE__, __LINE__);


    while(1){


        xSemaphoreTake(semaforo_aceleracion,portMAX_DELAY);


        //Leemos los datos del sensor mediante i2c

        xSemaphoreTake(mutex_i2c,portMAX_DELAY);
        MPU9150DataRead(&g_sMPU9150Inst, MPU9150AppCallback, &g_sMPU9150Inst);
        MPU9150AppI2CWait(__FILE__, __LINE__);
        xSemaphoreGive(mutex_i2c);

        //Recogemos los datos de aceleracion
        MPU9150DataAccelGetFloat(&g_sMPU9150Inst, pfAccel, pfAccel + 1,
                                 pfAccel + 2);


        //Recogemos los datos del giroscopio (rad/s)

        MPU9150DataGyroGetFloat(&g_sMPU9150Inst, pfGyro, pfGyro + 1,
                                pfGyro + 2);

        //Recogemos los datos del magnetometro (T)
        MPU9150DataMagnetoGetFloat(&g_sMPU9150Inst, magneto, magneto + 1,
                                   magneto + 2);

        //Para ajustar los angulos al sistema NED, hay que intercambiar los ejes X e Y del gyro y del accel
        //El magneto ya tiene el sistema de referencia NED
        temp = pfAccel[1];
        pfAccel[1] = -pfAccel[0];
        pfAccel[0] = -temp;


        temp = pfGyro[1];
        pfGyro[1] = pfGyro[0];
        pfGyro[0] = temp;



        if(DCM_iniciado == 0){
            //Primera iteracion del bucle
            DCM_iniciado = 1;
            CompDCMMagnetoUpdate(&g_sCompDCMInst, magneto[0], magneto[1],
                                 magneto[2]);
            CompDCMAccelUpdate(&g_sCompDCMInst, pfAccel[0], pfAccel[1],
                               pfAccel[2]);
            CompDCMGyroUpdate(&g_sCompDCMInst, pfGyro[0], pfGyro[1],
                              pfGyro[2]);
            CompDCMStart(&g_sCompDCMInst);
        }
        else{
            //Ya esta funcionando el DCM
            CompDCMMagnetoUpdate(&g_sCompDCMInst, magneto[0], magneto[1],
                                 magneto[2]);
            CompDCMAccelUpdate(&g_sCompDCMInst, pfAccel[0], pfAccel[1],
                               pfAccel[2]);
            CompDCMGyroUpdate(&g_sCompDCMInst, pfGyro[0], pfGyro[1],
                              pfGyro[2]);
            CompDCMUpdate(&g_sCompDCMInst);
        }

        CompDCMComputeEulers(&g_sCompDCMInst, &alabeo, &cabeceo,
                             NULL); //Angulos en radianes

        //Paso los angulos a grados
        alabeo = alabeo * (180.0/pi);
        cabeceo = cabeceo* (180.0/pi);

        //Se comprueba si hay un nuevo valor maximo, y se convierten los datos a parte entera y fraccionaria
        for(i = 0; i< 3; i++){

            if(pfAccel[i] > 0){
                signo = 1;
            }
            else{
                signo = -1;
            }
            valor_abs = fabs(pfAccel[i])/g;

            if(valor_abs > aceleracion_maxima){
                aceleracion_maxima = valor_abs * signo;
                parte_entera[3] = (int32_t) valor_abs * signo;
                parte_fraccionaria[3] = (uint32_t)round((valor_abs - (int32_t)valor_abs)*1000);
            }
            parte_entera[i] = (int32_t) valor_abs * signo;
            parte_fraccionaria[i] = (uint32_t)round((valor_abs - (int32_t)valor_abs)*1000);
        }

        //Filtrado de los ángulos
        cabeceo_filtrado = filtro(cabeceo, cabeceo_filtrado,alpha,90.0,-90.0);
        alabeo_filtrado = filtro(alabeo,alabeo_filtrado, alpha, 90.0, -90.0);

        if(contador_mensajes==20){
            contador_mensajes = 0;
            if(enviarUART){
            xSemaphoreTake(mutex_uart,portMAX_DELAY);
            UARTprintf("\033[4;1HAceleracion: Eje X: %d.%03d\t EjeY: %d.%03d\t Eje Z: %d.%03d ",parte_entera[0], parte_fraccionaria[0],parte_entera[1],parte_fraccionaria[1] ,parte_entera[2],parte_fraccionaria[2]);
            UARTprintf("Maxima G: %d.%03d\n",parte_entera[3],parte_fraccionaria[3]);
            UARTprintf("\033[5;1HTilt: Cabeceo: %d º Alabeo: %d º   \n",(int32_t) cabeceo_filtrado, (int32_t) alabeo_filtrado);
            xSemaphoreGive(mutex_uart);
            }


            for(i = 0; i< 3; i++){

                pfGyro[i] = pfGyro[i]* (180.0/pi); //Convierto de rad/s a º/s

                signo = (pfGyro[i] < 0) ? -1  : 1;
                valor_abs = fabs(pfGyro[i]);

                parte_entera[i] = (int32_t) valor_abs * signo;
                parte_fraccionaria[i] = (uint32_t)round((valor_abs - (int32_t)valor_abs)*1000);
            }

            if(enviarUART){
            xSemaphoreTake(mutex_uart,portMAX_DELAY);
            UARTprintf("\033[6;1HGiroscopio: Eje x: %d.%03d º/s\t Eje y: %d.%03d º/s\t Eje z: %d.%03d º/s  \n",parte_entera[0], parte_fraccionaria[0],parte_entera[1],parte_fraccionaria[1] ,parte_entera[2]);
            xSemaphoreGive(mutex_uart);
            }

            if(enviarUART){
            xSemaphoreTake(mutex_uart,portMAX_DELAY);
            UARTprintf("\033[7;1HUso de CPU: %2u%% \n",(g_ui32CPUUsage+32768) >> 16);
            xSemaphoreGive(mutex_uart);
            }

            //Mando a la aplicacion los datos

            if(aplicacion_conectada == 1){

                PARAM_MENSAJE_ACELERACION parametro;
                parametro.ejeX = (pfAccel[0]/g);
                parametro.ejeY = (pfAccel[1]/g);
                parametro.ejeZ = (pfAccel[2]/g);
                parametro.maximo = aceleracion_maxima;

                i32Numdatos = create_frame(pui8Frame,MENSAJE_ACELERACION,&parametro,sizeof(parametro),MAX_FRAME_SIZE);
                if(i32Numdatos > 0){

//                    xSemaphoreTake(mutex_usb,portMAX_DELAY);
//                    send_frame(pui8Frame,i32Numdatos);
//                    xSemaphoreGive(mutex_usb);
                    mandarporUSB(i32Numdatos,pui8Frame);

                }

                PARAM_MENSAJE_ANGULOS parametro2;
                parametro2.alabeo = (int32_t) alabeo;
                parametro2.cabeceo = (int32_t) cabeceo;


                i32Numdatos = create_frame(pui8Frame,MENSAJE_ANGULOS,&parametro2,sizeof(parametro2),MAX_FRAME_SIZE);
                if(i32Numdatos > 0){

//                    xSemaphoreTake(mutex_usb,portMAX_DELAY);
//                    send_frame(pui8Frame,i32Numdatos);
//                    xSemaphoreGive(mutex_usb);
                    mandarporUSB(i32Numdatos,pui8Frame);

                }

                PARAM_MENSAJE_GIROSCOPIO parametro3;
                parametro3.ejeX = pfGyro[0];
                parametro3.ejeY = pfGyro[1];
                parametro3.ejeZ = pfGyro[2];

                i32Numdatos = create_frame(pui8Frame,MENSAJE_GIROSCOPIO,&parametro3,sizeof(parametro3),MAX_FRAME_SIZE);
                if(i32Numdatos > 0){

//                    xSemaphoreTake(mutex_usb,portMAX_DELAY);
//                    send_frame(pui8Frame,i32Numdatos);
//                    xSemaphoreGive(mutex_usb);

                    mandarporUSB(i32Numdatos,pui8Frame);

                }

                PARAM_MENSAJE_MAGNETO parametro4;
                parametro4.ejex = magneto[0];
                parametro4.ejey = magneto[1];
                parametro4.ejez = magneto[2];

                i32Numdatos = create_frame(pui8Frame,MENSAJE_MAGNETO,&parametro4,sizeof(parametro4),MAX_FRAME_SIZE);
                if(i32Numdatos > 0){

//                    xSemaphoreTake(mutex_usb,portMAX_DELAY);
//                    send_frame(pui8Frame,i32Numdatos);
//                    xSemaphoreGive(mutex_usb);

                    mandarporUSB(i32Numdatos,pui8Frame);

                }
            }
        }
        else{
            contador_mensajes++;
        }

    }

}


int main(void)
{

    //
    // Reloj del sistema definido a 40MHz
    //
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // Obtiene el reloj del sistema
    g_ui32SystemClock = SysCtlClockGet();

    //Habilita el clock gating de los perifericos durante el bajo consumo --> perifericos que se desee activos en modo Sleep
    //                                                                        deben habilitarse con SysCtlPeripheralSleepEnable
    MAP_SysCtlPeripheralClockGating(true);

    //INICIALIZACION DE COSAS DE I2C
    //---------------------------------------------------------
    //---------------------------------------------------------

    InicializarI2C();
    InicializarBMP180();
    InicializarSHT21();
    InicializarMPU9150();
    InicializarTMP006();


    //--------------------------------------------------------
    //--------------------------------------------------------


    //%----------------HABILITACION BOTONES------------------------
    //Inicializa los botones (el puerto F) y habilita sus interrupciones
    ButtonsInit();
    MAP_GPIOIntTypeSet(GPIO_PORTF_BASE, ALL_BUTTONS,GPIO_BOTH_EDGES);
    MAP_IntPrioritySet(INT_GPIOF,configMAX_SYSCALL_INTERRUPT_PRIORITY);// Misma prioridad que configMAX_SYSCALL_INTERRUPT_PRIORITY
    // Una prioridad menor (mayor numero) podria dar problemas si la interrupcion
    // ejecuta llamadas a funciones de FreeRTOS
    MAP_GPIOIntEnable(GPIO_PORTF_BASE,ALL_BUTTONS);
    //ROM_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_GPIOF);
    MAP_IntEnable(INT_GPIOF);
    //%----------------HABILITACION BOTONES------------------------

    //Inicializo el sistema RGB
    uint32_t RGBArray[3] = {0, 0, 0xFFFF};  //Inicialmente el LED se enciende de color azul (UART INACTIVA)
    RGBInit(0);
    RGBIntensitySet(0.40);
    RGBColorSet(RGBArray);
    RGBEnable();

    // Inicializa el subsistema de medida del uso de CPU (mide el tiempo que la CPU no esta dormida)
       // Para eso utiliza un timer, que aqui hemos puesto que sea el TIMER3 (ultimo parametro que se pasa a la funcion)
       // (y por tanto este no se deberia utilizar para otra cosa).
       CPUUsageInit(g_ui32SystemClock, configTICK_RATE_HZ/10, 3);


       // Inicializa el sistema de depuraciÃ³n e interprete de comandos por terminal UART
       if (initCommandLine(512,tskIDLE_PRIORITY + 1) != pdPASS)
       {
           while(1);
       }


    USBSerialInit(32,32);	//Inicializo el  sistema USB
    //
    // Crea la tarea que gestiona los mensajes USB (definidos en USBMessageProcessingTask)
    //
    if(xTaskCreate(USBMessageProcessingTask, (portCHAR *)"usbser",512, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
    {
        while(1);
    }

    if((xTaskCreate(HUMEDADTASK, "humedad", SENSORESTASKSIZE,NULL,tskIDLE_PRIORITY + SENSORESTASKPRIO, NULL) != pdPASS))
    {
        while(1);
    }


    if((xTaskCreate(ACELERACIONTASK, "aceleracion", 512,NULL,tskIDLE_PRIORITY + SENSORESTASKPRIO, &tarea_accel) != pdPASS)){
        while(1);
    }

    if((xTaskCreate(TEMPTASK, "temperatura", 256,NULL,tskIDLE_PRIORITY + SENSORESTASKPRIO, NULL) != pdPASS)){
        while(1);
    }

    if((xTaskCreate(PRESIONTASK, "presion", SENSORESTASKSIZE*2,NULL,tskIDLE_PRIORITY + SENSORESTASKPRIO + 1, &tarea_pres) != pdPASS))
    {
        while(1);
    }

    //Creacion de recursos de FreeRTOS

    //Timer para controlar el sensor de presion y el de humedad relativa
    timer_presion = xTimerCreate( "TemporizadorPresion", configTICK_RATE_HZ, pdTRUE, NULL, vTimerCallback);
    if(timer_presion == NULL){
        while(1);
    }

    //Timer para el antirrebotes del boton
    timer_boton = xTimerCreate("TemporizadorBoton", (configTICK_RATE_HZ/4), pdFALSE,NULL,TimerBotonCallback);


    //Semaforo para una espera eficiente de la lectura
    semaforo_presion = xSemaphoreCreateBinary();
    if(semaforo_presion == NULL){
        while(1);
    }

    semaforo_humedad = xSemaphoreCreateBinary();
    if(semaforo_humedad == NULL){
        while(1);
    }

    mutex_i2c = xSemaphoreCreateMutex();
    if(mutex_i2c == NULL){
        while(1);
    }
    mutex_uart = xSemaphoreCreateMutex();
    if(mutex_uart == NULL){
        while(1);
    }

    semaforo_aceleracion = xSemaphoreCreateBinary();
    if(semaforo_aceleracion == NULL){
        while(1);
    }

    semaforo_temperatura = xSemaphoreCreateBinary();
    if(semaforo_temperatura == NULL){
            while(1);
        }

    mutex_usb = xSemaphoreCreateMutex();
    if(mutex_usb == NULL){
        while(1);
    }


    //

    //
    // Pone en marcha el planificador. La llamada NO tiene retorno
    //
    vTaskStartScheduler();  //el RTOS habilita las interrupciones al entrar aqui, asi que no hace falta habilitarlas
    freeRTOSIniciado = 1;
    while(1)
    {
        //Si llego aqui es que algo raro ha pasado
    }
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//------------------------------RTI DEL MPU9150-------------------------------------------
void
IntGPIOb(void)
{
    unsigned long ulStatus;

    ulStatus = GPIOIntStatus(GPIO_PORTB_BASE, true);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    //
    // Clear all the pin interrupts that are set
    //
    GPIOIntClear(GPIO_PORTB_BASE, ulStatus);

    if(ulStatus & GPIO_PIN_2)
    {

            xSemaphoreGiveFromISR(semaforo_aceleracion,&xHigherPriorityTaskWoken);

            //¿Hemos activado una tarea de mayor prioridad durante la interrupcion?
            portYIELD_FROM_ISR( xHigherPriorityTaskWoken);
    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//------------------------------RTI DEL TMP006-------------------------------------------
void
IntGPIOe(void)
{
    uint32_t ui32Status;

    ui32Status = GPIOIntStatus(GPIO_PORTE_BASE, true);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    GPIOIntClear(GPIO_PORTE_BASE, ui32Status);

    if(ui32Status & GPIO_PIN_0)
    {
        xSemaphoreGiveFromISR(semaforo_temperatura,&xHigherPriorityTaskWoken);

        //¿Hemos activado una tarea de mayor prioridad durante la interrupcion?
        portYIELD_FROM_ISR( xHigherPriorityTaskWoken);

    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//------------------------------RTI DE LOS BOTONES-------------------------------------------
void ButtonsHandler(void){
    int32_t i32Status = MAP_GPIOPinRead(GPIO_PORTF_BASE,RIGHT_BUTTON);
    BaseType_t xHigherPriorityTaskWoken=pdFALSE;

    if((i32Status & RIGHT_BUTTON) == 0){
        //Se ha presionado el boton derecho
        xTimerResetFromISR(timer_boton,&xHigherPriorityTaskWoken);

    }
    else{
        //Se ha soltado el boton derecho
        xTimerStopFromISR(timer_boton,&xHigherPriorityTaskWoken);
    }

    MAP_GPIOIntClear(GPIO_PORTF_BASE,ALL_BUTTONS);
}


void TimerBotonCallback(TimerHandle_t pxTimer ){

    if(enviarUART){
                enviarUART = 0;
                uint32_t RGBArray[3] = {0, 0, 0xFFFF};  //LED AZUL (UART INACTIVA)
                RGBIntensitySet(0.40);
                RGBColorSet(RGBArray);
            }
            else{
                enviarUART = 1;
                uint32_t RGBArray[3] = {0, 0xFFFF, 0};  //LED VERDE (UART ACTIVA)
                RGBIntensitySet(0.40);
                RGBColorSet(RGBArray);
            }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
