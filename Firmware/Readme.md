# ESP-32 Wifi Firmware information

This code, suposed to be the most usefull, it he Wifi for ESP32 code, the current version is built for the [ESP-WROOM-32 32 Pins board](https://www.amazon.com/-/es/KeeYees-Development-Bluetooth-Microcontroller-ESP-WROOM-32/dp/B07QCP2451/ref=sr_1_1?__mk_es_US=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=ESP-WROOM-32+32+Pins+board&qid=1597701582&sr=8-1). 

## Hardware conections: 

The motor asociated pins are intended to work for the following conection: 

<p align="center">
  <img width="400"  src="https://github.com/FabLabUTFSM/CareRobots/blob/master/Images/Fritizing.png">
</p>

## ESP32 pin selection

It is important to coinsider that ESP32 is pin sensitive. Eventhough pins are GPIO (General Purpose) not of them fit every use. 

First coinsider the following pinmap: 

<p align="center">
  <img width="800"  src="https://github.com/FabLabUTFSM/CareRobots/blob/master/Images/ESP32-Pinout.png">
</p>

Wich shows with pins have an ADC, PWM function (all pins in ESP32 are PWM), etc.

At the moment of choosing each pin, you **MUST** coinsider the following recomendation from [ESP easy](https://espeasy.readthedocs.io/en/latest/Reference/GPIO.html#best-pins-to-use-on-esp32): 

<p align="center">
  <img width="800"  src="https://github.com/FabLabUTFSM/CareRobots/blob/master/Images/esp32Pins.PNG">
</p>

As you can see, some pins have constrains at the moment of booting the board. 
** ESP32 can't be conected to the other parts of the circuit at the moment of booting **

If you are using a diferent board, or diferents pins, change the pinMotor array in line 6: 

``` 
    const int pinMotor[]= {12,27,33,15,32,14};// {moto1CW,motor1CCW,moto2CW,motor2CCW,moto3CW,motor3CCW}
```

## Firmware configuration

To enable the board to connect to your wifi network, modify the lines 9 and 10: 

``` 
    const char* ssid = "MIT";  // Enter SSID here
    const char* password = " YourPassword";  //Enter Password here
```
If your wifi doesn't have a password just comment that line and define the type of wifi you will use:

```
  WiFi.begin(ssid);
  //WiFi.begin(ssid,password); 
```
If the speed of the robot doesn't adjust to your requierment, you can change the variable 

```
const int motorSpeed = 10;
```

Upwards is faster and downwards is slower. 

## Libraries

- [AnalogWrite.h](https://github.com/ERROPiX/ESP32_AnalogWrite)

## To do

### Firmware
- Add fail after 10 iterations for wifi conection.
- Test omniwheels functions:

  The omniwheels where designed using the following structure: 

    <p align="center">
      <img width="400"  src="https://github.com/FabLabUTFSM/CareRobots/blob/master/Images/Omniwheel.jpg">
    </p>
- PWM in ESP: ESP doesn't have the arduino analogWrite standar function. They have [Led Control](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html#_CPPv413ledc_set_duty11ledc_mode_t14ledc_channel_t8uint32_t), eventhough the library [AnalogWrite.h](https://github.com/ERROPiX/ESP32_AnalogWrite) fix this issue, it increases the memory usage. 
  - Change the code to use Led Control commands. 

### Hardware
- Find or desing a charge circuit for the battery  [reference](https://www.amazon.com/Battery-Controller-Protection-Digital-Display/dp/B07415C9VJ/ref=asc_df_B07415C9VJ/?tag=hyprod-20&linkCode=df0&hvadid=316620274234&hvpos=&hvnetw=g&hvrand=1440459751665623902&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9061331&hvtargid=pla-613182190031&th=1)
- Design a better layout for the board
- Design enclosure for circuits (Faraday cage).
- Fritzing ==> 32pin EPS32

## Sobre el Ensamble

Por favor documenten bien, esto es muy importante si queremos trabajar de forma distribuida, tomen fotos de **TODO!!!!!!**: 

- Fotos de las piezas antes de ensamblar

<img src="https://github.com/FabLabUTFSM/CareRobots/blob/wifi-ESP32/Images/documentacion1.png" width=600  >

- Fotos de los sistemas durante el ensamble:

<img src="https://github.com/FabLabUTFSM/CareRobots/blob/wifi-ESP32/Images/documentacion2.png" width=600  >

- Fotos de medidas o pasos claves

<img src="https://github.com/FabLabUTFSM/CareRobots/blob/wifi-ESP32/Images/documentacion3.png" width=600  >

- Fotos del sistema ensamblado y funcionando: 

<img src="https://github.com/FabLabUTFSM/CareRobots/blob/wifi-ESP32/Images/documentacion4.png" width=600  >

Videos de la contruccion de los sistemas tambien son muy utiles!!!

**Esto para todos los sistemas y subsistemas**

Por favor, cada segundo invertido en buena documentacion es un segundo ganado en replicabilidad del proyecto y por ende un segundo ganado en el desarrollo de los robots. 


## **TroubleShoot**

- Its preferable to flash the ESP32 board not conected to the pin, chinese version are not able to be flashed if conected.
- WiFi run only in local network: 
  - Alonos Rodriguez (Friend from IOLed team): Router firewall problem. Check port forward solution, wich will allows to comunicate directly to the router, and it will send us to the ESP32 through a local IP. 


## Test1 19/09 - Results

- Wifi works only with the local network. 
- Doesn't work if we unpluged the ESP from the computer. 