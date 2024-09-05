#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include "EmotionsDisplay.h"
#include "driver/dac.h"
#include "sound.h"
#include "motor.h"
#include <WiFi.h>
#include <sign.h>
#include <ESPmDNS.h> // Include the mDNS library

const char *ssid = "vishnuprasad.c";
const char *password = "vishnuprasad";






String data;
int eye_flag=0;

WiFiServer server(80);

#define OLED_SDA 21//i2c
#define OLED_SCL 22//i2c

#define DAC_CHANNEL DAC_CHANNEL_1

Adafruit_SH1106 display(OLED_SDA, OLED_SCL);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay() {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
}





void emotionsDisplayTask(void *parameter) {
  int mood = 0;
  int left = 0;
  int right = 0;
  int hold = 0;

  for (;;) {
    int indexMood = data.indexOf("mood-");
    int indexLeft = data.indexOf("left-");
    int indexRight = data.indexOf("right-");
    int indexHold = data.indexOf("hold-");

    // Serial.println("indexMood");
    //   Serial.println(indexMood);
    //      Serial.println("indexLeft");
    //   Serial.println(indexLeft);
    //      Serial.println("indexRight");
    //   Serial.println(indexRight);
    //      Serial.println("indexHold");
    //   Serial.println(indexHold);

   if (indexMood != -1 && indexLeft != -1 && indexRight != -1 && indexHold != -1) {
      String moodValue = data.substring(indexMood + 5, data.indexOf(",", indexMood));
      String leftValue = data.substring(indexLeft + 5, data.indexOf(",", indexLeft));
      String rightValue = data.substring(indexRight + 6, data.indexOf(",", indexRight));
      String holdValue = data.substring(indexHold + 5);


      mood = moodValue.toInt();
      left = leftValue.toInt();
      right = rightValue.toInt();
      hold = holdValue.toInt();
    }

    emotionsDisplay(mood, left, right, hold);
  
  }
}

void emotionsSound(void *parameter) {
  int value=0;
  for (;;) {

  
        int indexvalue = data.indexOf("Sound-");

        if(eye_flag){
        sound_eye();
        eye_flag=0;
        }

        if (indexvalue != -1 ) {
        String str = data.substring(indexvalue + 6, data.indexOf("/", indexvalue));
       
        value = str.toInt();
     

        switch (value) {
        case 1:
        
             if(eye_flag){
    sound_eye();
     
     eye_flag=0;
     }

         
        break;

        case 2:
          sound_happy();
          vTaskDelay(1000);
        break;

        case 3:
          sound_hey();
          vTaskDelay(1000);

        break;

        case 4:
          sound_doubt();
          vTaskDelay(1000);
        break;

        case 5:
          sound_left();
          vTaskDelay(1000);
        break;

        case 6:
        
          sound_right();
          vTaskDelay(1000);

        break;

        case 7:
          sound_sad();
          vTaskDelay(1000);

        break;

        case 8:
          sound_angry();
          vTaskDelay(1000);
        break;
        }



        }



  }
}

void LED(void *parameter) {

 server.begin();

  for (;;) {


      // Do something with the data
        if (data == "HIGH") {
          digitalWrite(2, HIGH);
        } else if (data == "LOW") {
          digitalWrite(2, LOW);
          }

        


     vTaskDelay(100);
  }
}

void MOTOR(void *parameter) {
  int M1 = 0;
  int M2 = 0;

  for (;;) {
    int indexM1 = data.indexOf("M1-");
    int indexM2 = data.indexOf("M2-");

    if (indexM1 != -1 && indexM2 != -1) {
      String m1Value = data.substring(indexM1 + 3, data.indexOf(",", indexM1));
      String m2Value = data.substring(indexM2 + 3, data.indexOf("/", indexM2));

      M1 = m1Value.toInt();
      M2 = m2Value.toInt();

      if (data.startsWith("Forward")) {
        MOTORforward(M1, M2);
        Serial.println("MOTORforward");
      } else if (data.startsWith("Backward")) {
        MOTORbackward(M1, M2);
        Serial.println("MOTORbackward");
      } else if (data.startsWith("Right")) {
        MOTORright(M1, M2);
        Serial.println("MOTORright");
      } else if (data.startsWith("Left")) {
        MOTORleft(M1, M2);
        Serial.println("MOTORleft");
      }
    }

    vTaskDelay(100);
  }
}

void sensorTask(void *parameter) {

 server.begin();

  for (;;) {

if(digitalRead(4)!=0){
  Serial.println("on");
  Serial.println(digitalRead(5));
}
if(digitalRead(5)!=0){
    Serial.println("Touch sonsor on");
}
        


     vTaskDelay(100);
  }
}


void setup() {


  dac_output_enable(DAC_CHANNEL);
  MOTORinit();
  Serial.begin(115200);
  Serial.println("Booting");
  initDisplay();
  pinMode(2, OUTPUT);  // Set the LED pin mode
  pinMode(4,INPUT);//ir sensor
  pinMode(5,INPUT);//Touch sensor



  // Connect to WiFi
  WiFi.begin(ssid, password);
  int frame = 0;
  while (WiFi.status() != WL_CONNECTED) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(9, 34);
    display.print("Connecting...");
    display.setCursor(25, 9);
    display.print(ssid);
    display.drawBitmap(4, 3, image_wifi_bits, 19, 16, 1);
    display.display();
delay(4000);
 Serial.print(".");
    for(int i=0;i<100;i++){
    display.clearDisplay();
    display.drawBitmap(32, 0, frames[frame], 64, 64, 1);
    display.display();
    frame = (frame + 1) % FRAME_COUNT;
    delay(42);
    if(WiFi.status() == WL_CONNECTED)
    break;
    }

  }

    frame = 0;
     for(int i=0;i<20;i++){
    display.clearDisplay();
    display.drawBitmap(32, 0, frames_load[frame], 64, 64, 1);
    display.display();
    frame = (frame + 1) % FRAME_COUNT;
    delay(42);
    }



  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize mDNS with a hostname
  if (!MDNS.begin("Defmo32")) { // Change "esp32cam" to your desired hostname
    Serial.println("Error starting mDNS");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  Serial.println("You can now connect using http://Defmo32.local/");

  // Start the web server
  server.begin();

  display.clearDisplay();
  display.setTextColor(1);
  display.setCursor(9, 8);
  display.print("Successfully connected");
  display.setCursor(7, 33);
  display.print("IP address: ");
  display.setTextSize(1);
  display.setCursor(7, 45);
  display.print(WiFi.localIP());
  display.display();
  delay(5000);

  //while (client.connected());

  xTaskCreate(emotionsDisplayTask, "Emotions Task", 4096, NULL, 1, NULL);
  xTaskCreate(emotionsSound, "Sound Task", 4096, NULL, 1, NULL);
  xTaskCreate(MOTOR, "motor Task",4096 , NULL, 1, NULL);
  xTaskCreate(LED, "LEDexg Task", 4096, NULL, 2, NULL);
  xTaskCreate(sensorTask, "sensor Task", 4096, NULL, 2, NULL);

}

void loop() {
  // Nothing needed here; everything is handled in the tasks
    WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {  // If you get a client,
    Serial.println("New Client.");  // Print a message out the serial port

    while (client.connected()) {  // Loop while the client's connected
      if (client.available()) {  // If there's bytes to read from the client,
        data = client.readStringUntil('\n');  // Read a line of data
        Serial.print("Received: ");
        Serial.println(data);

        if(digitalRead(4)!=0){
         client.println("IR-ON"); 
         delay(100);
        }
        else{
          client.println("IR-OFF");
          delay(100); 
        }

          if(digitalRead(5)!=0){
          client.println("Touch-ON");
          }


        

      }
    }

    // Close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
