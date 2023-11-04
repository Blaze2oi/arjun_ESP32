#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "Blaze2oi";
const char* password = "8007174434";

WebServer server(80);

void setup() {
  Serial.begin(9600);
  delay(100);
  sensors.begin();
  
  Serial.println("Connecting to " + String(ssid));
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/getTemperature", handle_GetTemperature); // New endpoint to get temperature
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(1000); // Add a delay to avoid frequent updates
}

void handle_OnConnect() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (tempC != DEVICE_DISCONNECTED_C) {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  } else {
    Serial.println("Error: Could not read temperature data");
  }

  String html = SendHTML(tempC);
  server.send(200, "text/html", html);
}

void handle_GetTemperature() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  
  if (tempC != DEVICE_DISCONNECTED_C) {
    server.send(200, "text/plain", String(tempC));
  } else {
    server.send(200, "text/plain", "Error");
  }
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat){
String ptr="<!DOCTYPE html><html>\n";
ptr+="<head>\n";
ptr+="<meta charset=\"utf-8\">\n";
ptr+="<link rel=\"stylesheet\" href=\"style2.css\" >\n";
ptr+="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
ptr+="        <title>DASHBOARD</title>\n";
      ptr+="<style>\n";
       ptr+="body{\n";
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
 ptr+="                   <li><b><a href=\"index.php\"><img src=\"https://www.shutterstock.com/image-vector/home-vector-icon-on-transparent-260nw-1135839725.jpg\" class=\"propicc\" zoom></a></li></b>\n";
 ptr+="                   <li><b><a href=\"profile5.html\"><img src=\"https://previews.123rf.com/images/urfandadashov/urfandadashov1809/urfandadashov180902667/109317646-profile-pic-vector-icon-isolated-on-transparent-background-profile-pic-logo-concept.jpg\" class=\"propic\"></a></li></b>\n";
 ptr+="               </ul>\n";
 ptr+="           </nav>\n";
 ptr+="           </header>\n";
 ptr+="           <div class=\"headerr\">\n";
 ptr+="           <div class=\"side-nav\">\n";
 ptr+="               <div class=\"user\">\n";
 ptr+="                   <img src=\"https://cdn.icon-icons.com/icons2/2468/PNG/512/user_icon_149329.png\" class=\"user-img\">\n";
 ptr+="               <div>\n";
 ptr+="                   <h2>Arjun Naik</h2>\n";
 ptr+="                       <p>arjunnaik0402@gmail.com</p>\n";
 ptr+="                   </div>\n";
 ptr+="                   <img src=\"data:image/png;base64,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\" class=\"star-img\">\n";
 ptr+="           </div>\n";
 ptr+="                   <ul>\n";
 ptr+="                       <a href=\"index.php\" style=\"text-decoration: none;\" ><li><img src=\"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcS_r6PLtFOOOCCpIWNRkaQ6WBDklJAWc4bcrQ&usqp=CAU\"><p>Home</p></li></a>\n";
 ptr+="                       <a href=\"profile5.html\" style=\"text-decoration: none;\"><li><img src=\"https://previews.123rf.com/images/urfandadashov/urfandadashov1808/urfandadashov180818748/108198256-bar-graph-vector-icon-isolated-on-transparent-background-bar-graph-logo-concept.jpg\"><p>Profile</p></li></a>\n";
 ptr+="                       <li><img src=\"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQNQUNjl_CJJDkEuZJoeTxGGZSiOT-hNJPHIw&usqp=CAU\"><p>Tutorial</p></li>\n";
 ptr+="                       <a href=\"aboutpage.php\" style=\"text-decoration: none;\"><li><img src=\"data:image/png;base64,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\"><p>About Us</p></li></a>\n";
 ptr+="                       <li><img src=\"data:image/png;base64,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\"><p>Contact Us</p></li>\n";
 ptr+="                   </ul>\n";
 ptr+="                   <ul>\n";
 ptr+="<a href=\"logout.php\" style=\"text-decoration: none;\"><li><img src=\"https://png.pngtree.com/png-vector/20190411/ourmid/pngtree-vector-logout-icon-png-image_925699.jpg\"><b><p>Log Out</p></b></li></a>\n";
 ptr+="                   </ul>\n";
 ptr+="               </div>\n";
 ptr+="           </div>\n";
 ptr+="       <div class=\"container\">\n";
 ptr+="       <div class=\"parent\" id=\"aa\">\n";
 ptr+="              <div class=\"cc\"><h1>HEARTBEAT</h1></div>\n";              
 ptr+="              <div><IMG class=\"img_deg \" SRC=\"https://cdn.britannica.com/25/214625-050-A37D76CC/heart-rate-monitor-illustration-heartbeat.jpg\" width=\"190\" height=\"135\"></div>\n"; 
 ptr+="               <div><h2 id=\"count-el \"><span>0</span></h2></div>       </div>\n"; 
 ptr+="               <div class=\"parent \" id=\"bb \"><h1>TEMPERATURE</h1>\n";                 
 ptr+="                   <IMG class=\"img_deg\" SRC=\"https://c8.alamy.com/comp/2D6MBMC/thermometer-cartoon-illustration-isolated-on-white-meteorology-thermostat-vector-icon-measure-level-warm-and-cold-temperature-measurement-blue-an-2D6MBMC.jpg\" width=\"-500\" height=\"175\"> \n";
 ptr+="                   <div><h2 id=\"temp-el\"><span>0</span></h2></div>\n"; 
 ptr+="                   <h1>°C</h1>\n";
 ptr+="               </div>\n";
 ptr+="           </div>\n" ;   
 ptr+="           </div>\n" ;   
  ptr+="              <script src=\"index.js\"></script>\n" ;  

ptr+="  <script>\n" ;
ptr+="        function updateTemperature() {\n" ;
ptr+="            var xhttp = new XMLHttpRequest();\n" ;
ptr+="            xhttp.onreadystatechange = function() {\n" ;
ptr+="                if (this.readyState == 4 && this.status == 200) {\n" ;
ptr+="                    document.getElementById(\"temp-el\").innerHTML = \'<span>\' + this.responseText + \'</span>\';\n" ;
ptr+="                }\n" ;
ptr+="            };\n" ;
ptr+="            xhttp.open(\"GET\", \"/getTemperature\", true);\n" ;
ptr+="            xhttp.send();\n" ;
ptr+="        }\n" ;
ptr+="        setInterval(updateTemperature, 5000);\n" ;
ptr+="    </script>\n" ;

  ptr+="  </body></html>\n";
  return ptr;
}