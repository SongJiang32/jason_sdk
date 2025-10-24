# jason_sdk

This Motor SDK supports multiple motors.

Support List:

|Brand|Type|Release|
|-|-|-|
|Unitree|A1</br>B1</br>GO-M8010-6|✅</br>✅</br>✅|
|xiaomi|CyberGear|coming soon|
|RobStride|03|⚪|

> [!NOTE]
> Add your "header files" under "include" or your "library files" under "lib".
> 
> What is src? The folder where your source files are places.

## Build

```
mkdir build && cd build
cmake .. && make
```

## Use

```
$ sudo chmod +666 /dev/ttyUSB*
$ sudo ./unitree_GO_M8010_6
```

## Fireware & Configuration
[Unitree](https://support.unitree.com/home/en/Motor_SDK_Dev_Guide/related_configuration)

## Parameters

The default kp,kd value is 0.02.

Please read "legControl.h" in the corresponding path if you need to use motor.

```
$ cat /jason_legged_sdk/include/unitree/legControl/legControl.h
```
