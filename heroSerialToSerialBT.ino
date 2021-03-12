//HeroJR Bluetooth the Serial Bridge (supports 7,E,1)
//2021 dabone
//based off the Bluetooth Serial Bridge Arduino Example
//
//This sketch powers up and waits for a bluetooth serial connection. If a connection doesn't happen in 5 minutes, it forces the esp32 into a deep sleep mode to save battery.
//If a connection is made within 5 minutes, it stays powered on and will allow you to reconnect at anytime until it's reset.
//
//I'm powering the esp32 from the remote control connector,P204 and using a buck converter to provide +5 to the ESP32.
//Output pins to use for the rs232 converter board are RX0 and TX0.
//Power your rs232 board using the 3.3v output pin of the esp32
//This kills all power to the circuit while the robot is in sleep mode.


char RobotName[] = "HeroJr-BlueTooth";                                                //Name Your Robot's Bluetooth
#define BTtimeout 300000                                                              //How Many Milliseconds to wait before powerdown. 60000 is one minute 300000 is five minutes.


#include "BluetoothSerial.h"
#include "driver/uart.h"                                                              
#include "soc/uart_struct.h"                                                          
#define LED 2
bool isconnected = false;
bool hasconnected = false;
unsigned long lastchecked;
unsigned long elapsed; 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  delay(3000);                // Insert a 3 second pause on startup, without this bluetooth fails to fully init.
  pinMode(LED,OUTPUT);
  lastchecked = millis();
  uart_intr_config_t uart_intr;                                                      //Lets turn down the fifo buffers, It defaults to 120 characters, but we want just 1 before it sends them out. 
  uart_intr.intr_enable_mask = UART_RXFIFO_FULL_INT_ENA_M
                             | UART_RXFIFO_TOUT_INT_ENA_M
                             | UART_FRM_ERR_INT_ENA_M
                             | UART_RXFIFO_OVF_INT_ENA_M
                             | UART_BRK_DET_INT_ENA_M
                             | UART_PARITY_ERR_INT_ENA_M;
  uart_intr.rxfifo_full_thresh = 1;
  uart_intr.rx_timeout_thresh = 10;
  uart_intr.txfifo_empty_intr_thresh = 10;
  uart_intr_config(UART_NUM_0, &uart_intr);
  Serial.begin(9600,SERIAL_7E1);                                                     //Serial Settings for the HERO Jr.... Don't you love 80's tech?
  SerialBT.begin(RobotName);                                                         //Start the Bluetooth Serial Port. Any baud rate, or parity, esp32 translates to 9600,7,e,1. But keep in mind, it takes
                                                                                     //time to process your input. For Teraterm, I'm using 9600 8,n,1. with 5ms Character Delay, and 300ms line delay.
                                                                                     //the line delay can be shortened, unless you are replacing existing basic lines... The Hero Jr is SLOW.....
}


void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    SerialBT.println("Client Connected");
    digitalWrite(LED,HIGH);
    isconnected = true;
    hasconnected = true;
  }
 
  if(event == ESP_SPP_CLOSE_EVT ){
    isconnected = false;
    digitalWrite(LED,LOW);
    }
}

int serialbridge() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
}


void loop() {


SerialBT.register_callback(callback);                                             //Check the status of the Bluetooth Connection

  
  if (!isconnected && !hasconnected) {                                            //Do we have a incoming connection active? and also, has there ever been a active incoming connection?
    elapsed = millis() - lastchecked;                                             //If neither is true, then lets check for the time out. If we get to the final timeout, put the esp32
    if(elapsed > BTtimeout){                                                      //in deep sleep mode to save battery power on the robot.
      esp_deep_sleep_start();
    }
  }


  if (isconnected) {                                                              //If we have a active connection, process serial data on the bridge
    serialbridge ();
  }
}
