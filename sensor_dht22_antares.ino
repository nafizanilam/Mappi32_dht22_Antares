#include <DHT.h>
#include <AntaresESP8266HTTP.h>
  
#define DHTPIN 2
#define DHTTYPE DHT22

#define ACCESSKEY "ef87e8f206709322:3d22421484b63f89"
#define projectName "MONITOR_DHT22"
#define deviceName "Monitoring_dht22"

#define WIFISSID "KMTek"
#define PASSWORD "KMTek123"

DHT dht(DHTPIN, DHTTYPE);

AntaresESP8266HTTP antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(WIFISSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  antares.add("temperature", temp);
  antares.add("humidity", hum);

  antares.send(projectName, deviceName);
  delay(5000);

  Serial.println("Suhu : " + String(temp));
  Serial.println("Kelembaban : " + String(hum));
  Serial.println();
  delay(1000);
}
