// Most of this code written by Mitch Kelly mitchkelly24@gmail.com
// If you use it, Email me.

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10,60,140, 4);
IPAddress gateway(10,60,140, 1);
EthernetServer server(80);

void setup() {
  Serial.begin(9600);
   while (!Serial) {
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
 
       // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
                    // add a meta refresh tag, so the browser pulls again every 5 seconds:
          client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          // output the value of each analog input pin
    
    int vPin2Read = analogRead(A2);
    float vPin2Real = vPin2Read / 1023.0 * 52.50;

   int vPin3Read = analogRead(A3);
    float vPin3Real = vPin3Read / 1023.0 * 52.50;

   int vPin4Read = analogRead(A4);
    float vPin4Real = vPin4Read / 1023.0 * 52.50;

    int vPin5Read = analogRead(A5);
    float vPin5Real = vPin5Read / 1023.0 * 52.50;

  float average0 = 0;
  for(int i0 = 0; i0 < 1000; i0++) {
    average0 = average0 + (.0264 * analogRead(A0) -13.47) / 490;
  }
  float average1 = 0;
  for(int i1 = 0; i1 < 1000; i1++) {
    average1 = average1 + (.0264 * analogRead(A1) -13.47) / 490;
  }

  {
  //  for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
  //          int sensorReading = analogRead(analogChannel);
            client.print("Welcome to TIC Hill Arduino EtherTen Listening on IP: ");       
            client.println(Ethernet.localIP());  
            client.println("<hr>");       
            client.print("<table border=2>");
            client.print("<tr>");
            client.print("<td>");
            client.print("<b> Sensor Name </b>");
            client.print("</td>");
            client.print("<td>");
            client.print("<b> Sensor Reading </b>");
            client.print("</td>");
            client.print("<td>");
            client.print("<b> Sensor Measurement </b>");
            client.print("</td>");
            client.println("<br>");
            client.print("<tr>"); 
            client.print("<td>"); 
            client.print("ACS712 Sensor A0 (WAFreeNet Panels)");
            client.print("</td>"); 
            client.print("<td>"); 
            client.print(average0);
            client.print("<td>"); 
            client.print("Amps");
            client.print("</td>"); 
            client.print("</tr>");
            client.print("<tr>");
            client.print("</td>"); 
            client.print("<td>"); 
            client.print("ACS712 Sensor A1 (WAFreeNet Load)");
            client.print("</td>"); 
            client.print("<td>");
            client.print(average1);
            client.print("<td>"); 
            client.print("Amps");
            client.print("</td>"); 
            client.print("</tr>");
            client.print("<tr>");
            client.print("</td>");
            client.print("<td>");
            client.print("Voltage Sensor A2 (WAFreeNet Panels)");
            client.print("</td>");
            client.print("<td>");
            client.print(vPin2Real);
            client.print("<td>"); 
            client.print("Volts");
            client.print("</td>"); 
            client.print("</tr>");
            client.print("<tr>");
            client.print("</td>");
            client.print("<td>");
            client.print("Voltage Sensor A3 (WAFreeNet Batteries)");
            client.print("</td>");
            client.print("<td>");
            client.print(vPin3Real);
            client.print("<td>"); 
            client.print("Volts");
            client.print("</td>"); 
            client.print("</tr>");
            client.print("<tr>");
            client.print("</td>");
            client.print("<td>");       
            client.print("Voltage Sensor A4 (WARG Panels)");
            client.print("</td>");
            client.print("<td>");
            client.print(vPin4Real);
            client.print("<td>"); 
            client.print("Volts");
            client.print("</td>"); 
            client.print("</tr>");
            client.print("<tr>");
            client.print("</td>");
            client.print("<td>");       
            client.print("Voltage Sensor A5 (WARG Batteries)");
            client.print("</td>");
            client.print("<td>");
            client.print(vPin5Real);
            client.print("<td>"); 
            client.print("Volts");
            client.print("</td>"); 
            client.print("</tr>");
            client.print("</td>");
            client.print("</table>");

            client.println("<hr>");
            
            client.println("This project was created by Mitch Kelly (VK6FLEX) for monitoring vital statistics of WAFreeNet solar power sites, Information on this device and the code used to program it can be found on my website http://www.gnu.pw/projects/. I can be E-Mailed on mitckelly24 at gmail.com");
          client.println("<br>");
           client.println("This page is served directly from a Freetronics EtherTen over the WAFreenet Wireless Network www.wafreenet.org");
          client.println("</html>");
          client.println("<br>");
          client.println("<br>");
          client.println("<br>");
          client.println("The following lines are for debug and graphing purposes:");
          client.println("<br>");
          client.println("<br>");

          client.println("BEGIN DEBUG");
          client.println("<br>");
          client.println("WAFNPANELAMPS: ");
          client.print(average0);
          client.println("<br>");
          client.println("WAFNLOADAMPS: ");
          client.print(average1);
          client.println("<br>");
          client.println("WAFNPANELVOLTS: ");
          client.print(vPin2Real);
          client.println("<br>");
          client.println("WAFNBATTVOLTS: ");
          client.print(vPin3Real);
          client.println("<br>");
          client.println("WARGPANELVOLTS: ");
          client.print(vPin4Real);
          client.println("<br>");
          client.println("WARGBATTVOLTS: ");
          client.print(vPin5Real);
          client.println("<br>");
          client.println("<br>");

          client.print("WAFNPANELAMPS,");
          client.print(average0);
          client.print(",");
          client.print("WAFNLOADAMPS,");
          client.print(average1);
          client.print(",");
          client.print("WAFNPANELVOLTS,");
          client.print(vPin2Real);
          client.print(",");
          client.print("WAFNBATTVOLTS,");
          client.print(vPin3Real);
          client.print(",");
          client.print("WARGPANELVOLTS,");
          client.print(vPin4Real);
          client.print(",");
          client.print("WARGBATTVOLTS,");
          client.println(vPin5Real);
          client.print("<br>");
  
          client.print("<br>");
          client.println("END DEBUG");


  }
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

