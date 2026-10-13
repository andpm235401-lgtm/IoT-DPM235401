#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Cổng Web Server mặc định là 80
WebServer server(80);

const int ledPin = 2;
bool ledState = LOW;

// Giao diện Web hiển thị trên trình duyệt
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>ESP32 Web Server - Chuong 6</title>";
  html += "<style>body { font-family: Arial; text-align: center; margin-top: 50px;}";
  html += ".btn { padding: 15px 30px; font-size: 20px; border-radius: 8px; text-decoration: none; color: white; display: inline-block; margin: 10px;}";
  html += ".btn-on { background-color: #28a745; }";
  html += ".btn-off { background-color: #dc3545; }</style></head><body>";
  html += "<h2>HE THONG DIEU KHIEN LED QUA WIFI (CHUONG 6)</h2>";
  html += "<p>Trang thai LED hien tai: <b>" + String(ledState ? "DANG BAT" : "DANG TAT") + "</b></p>";
  html += "<a class='btn btn-on' href='/led/on'>BAT LED</a>";
  html += "<a class='btn btn-off' href='/led/off'>TAT LED</a>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

// Bật LED
void handleLedOn() {
  ledState = HIGH;
  digitalWrite(ledPin, ledState);
  Serial.println("Yeu cau tu Web: BAT LED");
  server.sendHeader("Location", "/");
  server.send(303);
}

// Tắt LED
void handleLedOff() {
  ledState = LOW;
  digitalWrite(ledPin, ledState);
  Serial.println("Yeu cau tu Web: TAT LED");
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  Serial.println("\nDang ket noi WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n-> WiFi Da Ket Noi Thanh Cong!");
  Serial.print("Dia chi Web Server: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);

  server.begin();
  Serial.println("Web Server da san sang nhan lenh!");
}

void loop() {
  server.handleClient();
}