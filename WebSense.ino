// Most of this code written by Mitch Kelly mitchkelly24@gmail.com
// If you use it, Email me.

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10,60,30, 3);
IPAddress gateway(10,60,30, 1);
EthernetServer server(80);

#define NUM_READS 100
float readavg(int sensorpin){
  // lifted from http://www.elcojacobs.com/eleminating-noise-from-sensor-readings-on-arduino-with-digital-filtering/
  int sortedValues[NUM_READS];
  for(int i=0;i<NUM_READS;i++){
     int value = analogRead(sensorpin);
     int j;
     if(value<sortedValues[0] || i==0){
        j=0; //insert at first position
     }
     else{
       for(j=1;j<i;j++){
          if(sortedValues[j-1]<=value && sortedValues[j]>=value){
            // j is insert position
            break;
          }
       }
     }
     for(int k=i;k>j;k--){
       // move all values higher than current reading up one position
       sortedValues[k]=sortedValues[k-1];
     }
     sortedValues[j]=value; //insert current reading
  }
  //return scaled mode of 10 values
  float returnval = 0;
  for(int i=NUM_READS/2-5;i<(NUM_READS/2+5);i++){
     returnval +=sortedValues[i];
  }
  returnval = returnval/10;
  // return returnval*1100/1023; // not sure if we're using the 1.1v ref
  return returnval;
}

int r1 = 51000;
int r2 = 5100;
float div = r2/(r1 + r2)

void setup() {
  Serial.begin(9600);
  while (!Serial) {
     pinMode(A0, INPUT); // ACS712 - WAFN Load (A)
     pinMode(A1, INPUT); // ACS712 - Panel Supply (A)
     pinMode(A2, INPUT); // Divider - 230W Panel (V) [R1:51 R2:5k1 ]
     pinMode(A3, INPUT); // Divider - 120W Panel (V) [R1:51 R2:5k1 ]
     pinMode(A4, INPUT); // Divider - WAFN Battery (V) [R1:51 R2:5k1 ]
     pinMode(A5, INPUT); // Divider - WARG Battery (V) [R1:51 R2:5k1 ]
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
          client.println("Content-Type: text/html; charset=utf-8");
          client.println("Connnection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><head>");
          // add a meta refresh tag, so the browser pulls again every 15 seconds:
          client.println("<meta http-equiv=\"refresh\" content=\"15\">");
          client.println("<title>TIC Hill monitoring</title>");
          client.println("</head><body>");
          // output the value of each analog input pin

  float average2 = 0;
  for(int i2 = 0; i2 < 500; i2++) {
    average2 = average2 + (.0264 * analogRead(A2) ) / 1023 * 6.20;
  }
  float average3 = 0;
  for(int i3 = 0; i3 < 500; i3++) {
    average3 = average3 + (.0264 * analogRead(A3) ) / 1023 * 6.20;
  }
  float average4 = 0;
  for(int i4 = 0; i4 < 500; i4++) {
    average4 = average4 + (.0264 * analogRead(A4) ) / 1023 * 6.20;
  }
  float average5 = 0;
  for(int i5 = 0; i5 < 500; i5++) {
    average5 = average5 + (.0264 * analogRead(A5) ) / 1023 * 4.3;
  }

  float average0 = 0;
  for(int i0 = 0; i0 < 1000; i0++) {
    average0 = average0 + (.0264 * analogRead(A0) -13.47) / 490;
  }
  float average1 = 0;
  for(int i1 = 0; i1 < 1000; i1++) {
    average1 = average1 + (.0264 * analogRead(A1) -13.47) / 490;

  }
        /* OLD VALUES FROM MITCH
          average2 = average2 + (.0264 * analogRead(A2) ) / 1023 * 6.20;
          average3 = average3 + (.0264 * analogRead(A3) ) / 1023 * 6.20;
          average4 = average4 + (.0264 * analogRead(A4) ) / 1023 * 6.20;
          average5 = average5 + (.0264 * analogRead(A5) ) / 1023 * 4.3;
          average0 = average0 + (.0264 * analogRead(A0) -13.47) / 490;
          average1 = average1 + (.0264 * analogRead(A1) -13.47) / 490;
       */

	// adc value is already averaged so we can convert directly
	/* for the ACS712 calculations there are several contradicting calculations:
	     http://embedded-lab.com/blog/?p=4529 says 0.0264 * (U - 512)
             http://www.lucadentella.it/en/2011/11/29/sensore-di-corrente-con-arduino/ says 0.026 * U - 13.51
             datasheet at https://www.sparkfun.com/datasheets/BreakoutBoards/0712.pdf - 30A model has 66mV/A sensitivity 
        */
	float a0current = 0.0742 * readavg(0) - 37.87 ;
	float a1current = 0.0742 * readavg(1) - 37.87 ;
	float a2volts = readavg(2) / 12.55 ;
	float a3volts = readavg(3) / 12.55 ;
	float a4volts = readavg(4) / 12.76 ;
	float a5volts = readavg(5) / 18.10 ;

      }

  {
// Simple Math to work out rough charging current to about .5A~ Resolution
float ACC = average1 * average3 / 14.7;

            client.print("<p>Welcome to TIC Hill Arduino EtherTen Listening on IP: ");
            client.print(Ethernet.localIP());
            client.println("</p>");

            client.println("<pre >"); // DEBUG AHOY! 
            client.println("Current A0");
            client.println(analogRead(A0));
            client.println(readavg(0));
            client.println(average0);
            client.println(a0current);
            client.println("Current A1");
            client.println(analogRead(A1));
            client.println(readavg(1));
            client.println(average1);
            client.println(a1current);
            client.println("Volts A2");
            client.println(analogRead(A2));
            client.println(readavg(2));
            client.println(average2);
            client.println(a2volts);
            client.println("Volts A3");
            client.println(analogRead(A3));
            client.println(readavg(3));
            client.println(average3);
            client.println(a2volts);
            client.println("Volts A4");
            client.println(analogRead(A4));
            client.println(readavg(4));
            client.println(average4);
            client.println(a4volts);
            client.println("Volts A5");
            client.println(analogRead(A5));
            client.println(readavg(5));
            client.println(average5);
            client.println(a5volts);
            client.println("</pre >"); // we now resume our normal scheduling

            client.println("<table border=\"1\">");
            client.print("<tr>");
            client.print("<th>Sensor Name</th>");
            client.print("<th>Sensor Reading</th>");
            client.print("<th>Units</th>");
            client.println("</tr>");
            client.print("<tr>");
            client.print("<td>ACS712 Sensor A0 (WAFN LOAD (12V))</td><td>");
            client.print(average0);
            client.println("</td><td>Amps</td></tr>");
            client.print("<tr>");
            client.print("<td>ACS712 Sensor A1 (WAFN Panel Curr (24V))</td><td>");
            client.print(average1);
            client.println("</td><td>Amps</td></tr>");
            client.print("<tr>");
            client.print("<td>ACS712 Sensor A1 (Actual Chg Curr @14.7V)</td><td>");
            client.print(ACC);
            client.println("</td><td>Amps</td></tr>");
            client.print("<tr>");
            client.print("<td>Voltage Sensor A2 (WAFN 230W PV)</td><td>");
            client.print(average2);
            client.println("</td><td>Volts</td></tr>");
            client.print("<tr>");
            client.print("<td>Voltage Sensor A3 (WAFN 180W PV)</td><td>");
            client.print(average3);
            client.print("</td><td>Volts</td></tr>");
            client.print("<tr>");
            client.print("<td>Voltage Sensor A4 (WAFN Batteries)</td><td>");
            client.print(average4);
            client.print("</td><td>Volts</td></tr>");
            client.print("<tr>");
            client.print("<td>Voltage Sensor A5 (WARG Batteries)</td><td>");
            client.print(average5);
            client.print("</td><td>Volts</td></tr>");
            client.println("</table>");

          client.println("<p>Machine Readable <a href=\"http://www.json.org/\">JSON</a> follows below:</p>");
          client.println("<pre>");
          // json version of output
          client.print("{ \"TIC\": {");
          client.print(" \"WAFN_LOAD_A\": ");
          client.print(average0);
          client.print(", \"WAFN_PANEL_A\": ");
          client.print(average1);
          client.print(", \"CHARGE_A\": ");
          client.print(ACC);
          client.print(", \"WAFN_PV230_V\": ");
          client.print(average2);
          client.print(", \"WAFN_PV180_V\": ");
          client.print(average3);
          client.print(", \"WAFN_BATT_V\": ");
          client.print(average4);
          client.print(", \"WARG_BATT_V\": ");
          client.print(average5);
          client.println("}}");
          client.println("</pre>");

          client.println("<p>This page is served directly from a Freetronics EtherTen over the <a href=\"http://www.wafreenet.org/\">WAFreenet Wireless Network</a></p>");
          client.println("</body></html>");

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
