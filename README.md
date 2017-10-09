# Dynamixel XH430-V210
This is a code which is aimed to control the Dynamixel XH430-V210 motor. The operation of the motor consists in driving the motor to two specific positions without exceeding a giving torque, *open* and *closed* positions. In order to do this, a *current-based Position control* is implemented.

---

## Dependencies
* **OpenCM9.04**
* **OpenCM 485 EXP**
* **OpenCM IDE:** [Robotis](http://support.robotis.com/en/techsupport_eng.htm#software/robotis_opencm.htm)

---
## Guide lines for driving the motor using the OpenCM 485 EXP board
* Connect the OpenCM 485 EXP board to a 24V source.
* Approach the Dynamixel motor's shaft to the initial position (*open position*) manually.
* Power on the OpenCM expansion board.
* Hold **Button1** until the blue led turns on.
* Push **Button2** until the green led turns on and then release it in order to drive the motor to absolute initial position.
* It is time to drive the Dynamixel!, be sure that the workbench has been already set it up. Hold **Button2** and push **Button1** until the red led turns on and then release them in order to drive the motor to *closed Position*.
* **Warning**: Once you have finished using the system, return the motor to the initial position before powering off the motor or the OpenCM expansion board. Notice that the next time the controller is going to initialize the motor, it will drive the shaft to the absolute position taking in account only on turn.

<!--![OpenCM9.0 + 485 EXP board](figure/PenCM.png){width=50%}-->

<div style="text-align:center;">
<img src="figure/PenCM.png" alt="Drawing" width= "500px"/>
OpenCM9.0 + 485 EXP board
</div>

```bash
python
```

```python
import cad2xls
obj = cad2xls.GetParameters()
obj.filePath = 'path_to_stp_file'
obj.loadCAD()
obj.writeTxt()
```
---
## Running the code in Linux

[![Running the code!](https://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://www.youtube.com/watch?v=RIBDlxeZS7M&feature=youtu.be)
