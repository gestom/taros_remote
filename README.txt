remote_control.ino runs on Arduino Nano board, obtains values from the reciever and send them over Serial
test.cpp is a c++ nodes, which obtains values from the Serial (from Arduino) and publishes them on the /joy topic 

to connect the reciever to Arduino Nano:
Connect top row (out of three on the reciever) of channels 1 to 8 to pins D2 to D9 (ch1 = D2, ch2 = D3...)
Connect middle row of B/VCC to 5V and bottom row of B/VCC to GND

to upload the code to the board:
upload it from Arduino.ino: https://www.arduino.cc/en/software
in Tools set Board to Arduino Nano and Processer to ATmega328P (Old Bootloader) and Port to whichever port, that appeared after you pluged the arduino in (most likely /dev/ttyUSB0)

add udev rule:
in repository /etc/udev/rules.d create new file (e.g. 71-remote_control.rules) and paste this into it: 
ACTION=="add", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", SYMLINK+="remote_control", MODE+="0777"

to run the code:
compile with catkin build
$ roscore
$ rosrun remote_control_3 testcode
$ rostopic echo /joy

PS:
when you turn the transmitter on switches have to be at their 0 positions (if not, it beeps to alert you)

