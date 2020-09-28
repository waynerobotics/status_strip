#include <ros.h>
#include <std_msgs/String.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PINLEFT            3
#define NUMPIXELS          25

#define imu = 0; 
#define camera = 1; 
#define gps = 2; 
#define lidar = 3; 
#define driver = 4;

char s[6]={'1','1','0','1','1','\0'};


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PINLEFT, NEO_GRB + NEO_KHZ800);

ros::NodeHandle nh;

void messageCb( const std_msgs::String& status_string){
  
//  s = {'1','1','0','1','1','\0'}; // main algorithm test  
  
  
//  for (int i = 0; i < 5; i++) {
//    for(int j=i*5; j< (i+1)*5; j++){
//        strip.setPixelColor(j, strip.Color(255*(s[i]=='0'), 255*(s[i]=='1'), 0));
//        strip.show();
//    }
//  }

  //status.py 25 leds on the strip. 5 pixels represent each of [IMU, Camera, GPS, LiDAR, Motor Driver] in that order.
  for (int i = 0; i < 5; i++) {
    for(int j=i*5; j< (i+1)*5; j++){
        strip.setPixelColor(j, strip.Color(255*(status_string.data[i]=='0'), 255*(status_string.data[i]=='1'), 0));
        strip.show();
    }
  }

  digitalWrite(13, HIGH);   // blink the led
}


ros::Subscriber<std_msgs::String> sub("status_led_strip", &messageCb );

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  
  strip.begin(); // This initializes the NeoPixel library.
  strip.setBrightness(125);

  //Initialize with all RED pixels
  for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
        strip.show();
  } 


}

void loop()
{
  nh.spinOnce();
  delay(200);
}
