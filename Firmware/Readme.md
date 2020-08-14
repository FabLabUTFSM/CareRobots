# ESP-32 Wifi Firmware information

This code, suposed to be the most usefull, it he Wifi for ESP32 code. 

## Hardware conections: 

The motor asociated pins are intended to work for the following conection: 

<p align="center">
  <img width="400"  src="https://github.com/FabLabUTFSM/CareRobots/blob/master/Images/Fritizing.png">
</p>

If you are using a diferent board, or diferents pins, change the pinMotor array in line 6: 

``` 
    const int pinMotor[]= {12,27,33,15,32,14};// {moto1CW,motor1CCW,moto2CW,motor2CCW,moto3CW,motor3CCW}
```

## Wifi configuration

To enable the board to connect to your wifi network, modify the lines 9 and 10: 

``` 
    const char* ssid = "MIT";  // Enter SSID here
    const char* password = " YourPassword";  //Enter Password here
```
If your wifi doesnt have a password just comment that line and define the type of wifi you will use:

```
  WiFi.begin(ssid);
  //WiFi.begin(ssid,password); 
```

## To do

### Firmware
- First tets. 

The omniwheels where designed using the following structure: 

<p align="center">
  <img width="400"  src="https://github.com/FabLabUTFSM/CareRobots/blob/master/Images/Omniwheel.jpg">
</p>

### Hardware
- Find or desing a charge circuit for the battery
- Design a beter layout for the board

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
