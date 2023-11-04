#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

//Put your SSID & Password/
const char* ssid = "Blaze2oi";  // Enter SSID here
const char* password = "8007174434";  //Enter Password here

WebServer server(80);

// DHT Sensor
uint8_t DHTPin = 4; 
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();              

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  
  server.handleClient();
  
}

void handle_OnConnect() {

 Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  Serial.println(Temperature);
  Serial.println(Humidity);
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){
String ptr="<!DOCTYPE html><html>\n";
ptr+="<head>\n";
ptr+="<meta charset=\"utf-8\">\n";
ptr+="<link rel=\"stylesheet\" href=\"style2.css\" >\n";
        ptr+="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
ptr+="        <title>DASHBOARD</title>\n";
      ptr+="<style>\n;"
       ptr+="body{\n;"
  ptr+="margin-top: auto;\n";
  ptr+="background:rgb(247, 235, 235);\n";
  ptr+="font-family: system-ui, -apple-system, BlinkMacSystemFont, \'Segoe UI\', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;\n";
ptr+="}\n";
ptr+=".parent {\n";
    /* border: 4px solid rgb(255, 255, 255); */
    ptr+="border-radius: 20px;\n";
    ptr+="display: flex ;\n";
    ptr+="justify-content: space-evenly;\n";
    ptr+="line-height: 4rem;\n";
    ptr+="align-items: center;\n";
    ptr+="flex-wrap: wrap;\n";
  ptr+="}\n";
  ptr+=".cc{\n";
    ptr+="margin: 20px;\n";
  ptr+="}\n";
  ptr+=".child {\n";
    ptr+="width: 50%;\n";
    ptr+="padding: 20px;\n";
    ptr+="border: 4px solid green;\n";
    ptr+="margin: auto;\n";
  ptr+="}\n";
  ptr+="IMG{\n";
    ptr+="image-orientation: from-image;\n";
    ptr+="display: block;\n";
    ptr+="width: 25%;\n";
    ptr+="margin-left: 10px;\n";
    ptr+="margin-right: 10px;\n";
    ptr+="overflow: hidden;\n";
    ptr+="border-radius: 10px;\n";
    
  ptr+="}\n";
   ptr+="button{\n";
    ptr+="border-radius: 1000px;\n";
    ptr+="align-items: center;\n";
    ptr+="padding: 15px 32px;\n";
    ptr+="margin-left: 550px;\n";
    ptr+="margin-top: 20px;\n";
    ptr+="margin-right: 10px;\n";
    ptr+="color: antiquewhite;\n";
    ptr+="background-color:rgb(17, 59, 148);\n";
    ptr+="font-size: 20px;\n";
    ptr+="width: 30%;\n";
  ptr+="} \n";
  
  ptr+="h2\n";
  ptr+="{\n";
   ptr+=" text-align: center;\n";
   ptr+=" align-items: flex-end;\n";
   ptr+=" font-size: 80px;\n";
ptr+="  }\n";

ptr+=".parent h1{\n";
  ptr+="text-align: center;\n";
  ptr+="color: rgb(0, 0, 0);\n";
  ptr+="margin-right: 10px;\n";
  ptr+="margin-bottom: 2rem;\n";
ptr+="}\n";
ptr+=".parent h2{\n";
 ptr+=" color: rgb(0, 0, 0);\n";
ptr+="}\n";
ptr+="#aa img{\n";
 ptr+=" height: 200px;\n";
 ptr+=" width: 340px;\n";
ptr+="}\n";
    ptr+=" /* Start of Navbar  */\n";
ptr+=".navbar{\n";
  ptr+="background-color: rgb(0, 162, 255);\n";
 ptr+=" box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);\n";
 ptr+=" text-decoration: none;\n";

ptr+="}\n";
ptr+=".navbar li{\n";
  ptr+="float: left;\n";
  ptr+="list-style: none;\n";
  ptr+="margin: 15px 15px;\n";
  ptr+="font-size: 35px;\n";
  ptr+="}\n";
ptr+=".navbar ul{\n";
  ptr+="overflow: auto;\n";
  ptr+="display: flex;\n";
    ptr+="justify-content:flex-end;\n";
    ptr+="line-height: 0.5rem;\n";
    ptr+="align-items: right;\n";
    ptr+="margin-bottom: 20px;\n";
    ptr+="margin-top: 0px;\n";
ptr+="}\n";
ptr+=".navbar li a{\n";
  ptr+="padding: 3px 3px;\n";
  ptr+="text-decoration: none;\n";
  ptr+="padding-left: 0px;\n";
  ptr+="padding-right: 0px;\n";
  ptr+="align-items: right;\n";
  ptr+="padding-bottom: 0px;\n";
ptr+="}\n";
ptr+="/* .navbar li a:hover{\n";
  ptr+="color: rgb(0, 12, 116);\n";
ptr+="} */\n";
ptr+=".logo{\n";
  ptr+="position: absolute;\n";
  ptr+="height: auto;\n";
  ptr+="left: 10px;\n";
  ptr+="width: 100px;\n";
  ptr+="border-radius: 10px;\n";
  ptr+="padding-left: 25px;\n";
  ptr+="top: -14px;\n";
  ptr+="zoom: 1.6;\n";
ptr+="}\n";
ptr+="/* End of Navbar \n";
ptr+="Start of Side bar  */\n";
ptr+=".side-nav{\n";
 ptr+=" width: 70px;\n";
  ptr+="height: 100%;\n";
  ptr+="position: fixed;\n";
  ptr+="text-decoration: none;\n";
  ptr+="top: 0;\n";
  ptr+="left: 0;\n";
  ptr+="padding: 30px 15px;\n";
  ptr+="background: rgba(255, 255, 255, 0.2);\n";
  ptr+="backdrop-filter: blur(5px);\n";
  ptr+="display: flex;\n";
  ptr+="justify-content: space-between;\n";
  ptr+="flex-direction: column;\n";
  ptr+="transition: width 0.4s;\n";
  ptr+="box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);\n";
ptr+="}\n";
ptr+=".user{\n";
  ptr+="display: flex;\n";
  ptr+="align-items: center;\n";
  ptr+="justify-content: space-between;\n";
  ptr+="width: 60px;\n";
  ptr+="font-size: 12px;\n";
  ptr+="padding: 10px;\n";
  ptr+="border-radius: 8px;\n";
  ptr+="margin-left: auto;\n";
  ptr+="margin-right: auto;\n";
  ptr+="overflow: hidden;\n";
ptr+="}\n";
ptr+=".user div{\n";
  ptr+="display: none; \n";
ptr+="}\n";
ptr+=".user h2{\n";
  ptr+="font-size: 15px;\n";
  ptr+="font-weight: 600;\n";
  ptr+="white-space: nowrap;\n";
  ptr+="}\n";
ptr+=".user-img{\n";
 ptr+="width: 40px;\n";
  ptr+="border-radius: 50%;\n";
  ptr+="margin: auto;\n";
  ptr+="zoom: 1.3;\n";
ptr+="}\n";
ptr+=".star-img{\n";
  ptr+="width: 30px;\n";
  ptr+="display: none;\n";
ptr+="}\n";
ptr+="ul{\n";
  ptr+="list-style: none;\n";
  ptr+="padding: 0 15px;\n";
ptr+="}\n";
ptr+="ul li{\n";
  ptr+="margin: 20px 0;\n";
  ptr+="display: flex;\n";
  ptr+="align-items: center;\n";
  ptr+="justify-content: center;\n";
  ptr+="cursor: pointer;\n";
  ptr+="color: black;\n";
ptr+="}\n";
ptr+="ul li img{\n";
  ptr+="width: 30px;\n";
ptr+="  margin-right: 0px;\n";
ptr+="}\n";
ptr+="ul li p{\n";
ptr+="white-space: nowrap;\n";
ptr+="display: none;\n";
ptr+="  text-decoration: none; \n";
ptr+="}\n";
ptr+=".side-nav:hover{\n";
  ptr+="width: 250px;\n";
ptr+="}\n";
ptr+=".side-nav:hover .user div{\n";
  ptr+="display: block;\n";
ptr+="}\n";
ptr+=".side-nav:hover .user{\n";
  ptr+="width: 100%;\n";
ptr+="  background: rgba(255,255, 255, 0.2);\n";
  ptr+="backdrop-filter: blur(5px);\n";
ptr+="}\n";
ptr+=".side-nav:hover .star-img{\n";
  ptr+="display: block;\n";
ptr+="}\n";
ptr+=".side-nav:hover .user-img{\n";
  ptr+="margin: 0;\n";
  ptr+="zoom: 1.1;\n";
ptr+="}\n";
ptr+=".side-nav:hover ul li p{\n";
  ptr+="display: block;\n";
  ptr+="text-decoration: none;\n";
ptr+="}\n";
ptr+=".side-nav:hover ul li img{\n";
  ptr+="margin-right: 10px;\n";
ptr+="}\n";
ptr+=".side-nav:hover ul li{\n";
  ptr+="justify-content: flex-start;\n";
ptr+="}\n";

ptr+=".propic{\n";
ptr+="zoom: 1.7;\n";
ptr+="}\n";
ptr+=".propicc{\n";
  ptr+="zoom: 1.75;\n";
  ptr+="}\n";
ptr+="</style>\n";
 ptr+="   </head>\n";
 ptr+="   <body>\n";
 ptr+="       <header>\n";
 ptr+="           <nav class=\"navbar\">\n";
 ptr+="               <img src=\"images/nayalogo (2).png\" class=\"logo\">\n";
 ptr+="               <ul>\n";
 ptr+="                   <li><b><a href=\"index.php\"><img src=\"images/nayahomepic.png\" class=\"propicc\" zoom></a></li></b>\n";
 ptr+="                   <li><b><a href=\"profile5.html\"><img src=\"images/profilepic.png\" class=\"propic\"></a></li></b>\n";
 ptr+="               </ul>\n";
 ptr+="           </nav>\n";
 ptr+="           </header>\n";
 ptr+="           <div class=\"headerr\">\n";
 ptr+="           <div class=\"side-nav\">\n";
 ptr+="               <div class=\"user\">\n";
 ptr+="                   <img src=\"images/user.png\" class=\"user-img\">\n";
 ptr+="               <div>\n";
 ptr+="                   <h2>Arjun Naik</h2>\n";
 ptr+="                       <p>arjunnaik0402@gmail.com</p>\n";
 ptr+="                   </div>\n";
 ptr+="                   <img src=\"images/star.png\" class=\"star-img\">\n";
 ptr+="           </div>\n";
 ptr+="                   <ul>\n";
 ptr+="                       <a href=\"index.php\" style=\"text-decoration: none;\" ><li><img src=\"images/dashboard.png\"><p>Home</p></li></a>\n";
 ptr+="                       <a href=\"profile5.html\" style=\"text-decoration: none;\"><li><img src=\"images/reports.png\"><p>Profile</p></li></a>\n";
 ptr+="                       <li><img src=\"images/projects.png\"><p>Tutorial</p></li>\n";
 ptr+="                       <a href=\"aboutpage.php\" style=\"text-decoration: none;\"><li><img src=\"images/members.png\"><p>About Us</p></li></a>\n";
 ptr+="                       <li><img src=\"images/messages.png\"><p>Contact Us</p></li>\n";
 ptr+="                   </ul>\n";
 ptr+="                   <ul>\n";
 ptr+="<a href=\"logout.php\" style=\"text-decoration: none;\"><li><img src=\"images/logout.png\"><b><p>Log Out</p></b></li></a>\n";
 ptr+="                   </ul>\n";
 ptr+="               </div>\n";
 ptr+="           </div>\n";
 ptr+="       <div class=\"container\">\n";
 ptr+="       <div class=\"parent\" id=\"aa\">\n";
 ptr+="              <div class=\"cc\"><h1>HEARTBEAT</h1></div>\n";              
 ptr+="              <div><IMG class=\"img_deg \" SRC=\"images/heartbeat.gif \" width=\"190\" height=\"135\"></div>\n"; 
 ptr+="               <div><h2 id=\"count-el \"><span>0</span></h2></div>       </div>\n"; 
 ptr+="               <div class=\"parent \" id=\"bb \"><h1>TEMPERATURE</h1>\n";                 
 ptr+="                   <IMG class=\"img_deg\" SRC=\"images/temp.gif \" width=\"-500\" height=\"175\"> \n";
 ptr+="                   <h2 id=\"temp-el\"><span>0</span></h2></span>\n";                
 ptr+="               </div>\n";
 ptr+="               <button type=\"button\" class=\"btn btn-log\" onclick=\"start()\">Start</button>\n";
 ptr+="           </div>\n" ;             
  ptr+="              <script src=\"index.js\"></script>\n" ;            
  ptr+="  </body></html>\n";
  return ptr;
}