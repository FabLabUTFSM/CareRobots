# Motor test

This code has been programed to test the motors conections. 

Once it is uploaded to the board, the motors shouls move ClockWise, stop with a delay of one second and then move Counterclockwise, making the robot spin around its axis. 

In case the robot moves in any other direction rather than spinning, it means that a motor has been conected in a wrong way and its moving in an oposite direction than the other ones. 

To change this go to: 

```
bool motor1 = true;
bool motor2 = true;
bool motor3 = true;
```
This boolean variables define the motor spinning direction, changing this value will change it. 

In case that the motor doesn't move, check the motor conection pins in the line: 

```
const int pinMotor[]= {12,27,15,33,22,23};// {moto1CW,motor1CCW,moto2CW,motor2CCW,moto3CW,motor3CCW}
const int pinEnable[]={13,32,14};
```