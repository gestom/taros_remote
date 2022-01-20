#include <ros/ros.h>
#include <serial/serial.h>
#include <sensor_msgs/Joy.h>

serial::Serial ser;

char *arrayChar[8];
float result[8];

int main (int argc, char** argv){
    
    ros::init(argc, argv, "serial_example_node");
    ros::NodeHandle n;
    ros::Publisher myTopic = n.advertise<sensor_msgs::Joy>("joy", 1000);

    try
    {
        ser.setPort("/dev/remote_control");
        ser.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }

    ros::Rate loop_rate(5);
    while(ros::ok()){

	    ros::spinOnce();

	    if(ser.available()){

		    sensor_msgs::Joy axe_msg;

		    std::string serialString = ser.read(ser.available());

		    char *serialChar = new char[serialString.length() + 1];
		    strcpy(serialChar, serialString.c_str());
		    printf("%s\n",serialChar); 
		    arrayChar[0] = strtok(serialChar, " ");
		    for(int i = 1; i < 9; i++){
			    arrayChar[i] = strtok(NULL, " ");
		    }

		    for(int i = 0; i < 8; i++){
			    result[i] = atof(arrayChar[i]);
		    }

		    for(int i = 0; i < 7; i++){
			    axe_msg.axes.push_back(result[i]);
		    }
		    axe_msg.buttons.push_back(result[7]);

		    myTopic.publish(axe_msg);
	    }
	    loop_rate.sleep();
    }
}

