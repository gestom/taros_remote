  /*#include <ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Joy.h>*/


#define ch1 2
#define ch2 3
#define ch3 4
#define ch4 5
#define ch5 6
#define ch6 7
#define ch7 8
#define ch8 9

float valueCH[8];
float axis[8];
int32_t button[1];

/*ros::NodeHandle nh;

sensor_msgs::Joy axe_msg;
ros::Publisher joy("/joy", &axe_msg);*/

void setup(){
  /*nh.initNode();
  nh.advertise(joy);*/
  Serial.begin(115200);
}

void loop(){
  valueCH[0] = pulseIn(ch1, HIGH);
  valueCH[1] = pulseIn(ch2, HIGH);
  valueCH[2] = pulseIn(ch3, HIGH);
  valueCH[3] = pulseIn(ch4, HIGH);
  valueCH[4] = pulseIn(ch6, HIGH);
  valueCH[5] = pulseIn(ch7, HIGH);
  valueCH[6] = pulseIn(ch8, HIGH);
  
  for(int i = -1; i++, i < 7;){
    axis[i] = ((valueCH[i] - 1500) / 500) * 1.4;
    if((axis[i] < 0.06) && (axis[i] > -0.06)) {
        axis[i] = 0;
      }
    if(axis[i] > 0.98) {
        axis[i] = 1;
      }
    if(axis[i] < -0.98) {
        axis[i] = -1;
      } 
  }
  
  valueCH[7] = pulseIn(ch5, HIGH);
  if (valueCH[7] < 1500){
    axis[7] = 0;
  }else{
    axis[7] = 1;
  }

  for(int i = -1; i++, i < 8;){
    
    if(i == 7){
      Serial.println(axis[i]);
    }else{
      Serial.print(axis[i]);
      Serial.print("  ");
    }
  }
  /*axe_msg.axes = axis;
  axe_msg.axes_length = 7;
  axe_msg.buttons = button;
  axe_msg.buttons_length = 1;
  joy.publish( &axe_msg );
  nh.spinOnce();*/
}
