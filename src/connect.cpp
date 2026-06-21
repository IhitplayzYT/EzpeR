#include <WiFi.h>
#include <ESPmDNS.h>
#include "../lib/credentials.hpp"
#include "../lib/consts.hpp"

extern String piBaseUrl;
void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(WIFI_RETRY_DELAY_MS);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());
}

// Resolves Pi via mDNS, retries until found. Sets global piBaseUrl on success.
bool discoverPi() {
  if (!MDNS.begin("esp32reader")) {
    Serial.println("mDNS init failed");
    return false;
  }
  Serial.println("Querying mDNS for Pi server...");
  IPAddress piIp = MDNS.queryHost(PI_MDNS_HOSTNAME);
  int attempts = 0;
  while (piIp == IPAddress(0, 0, 0, 0) && attempts < 10) {
    delay(MDNS_QUERY_RETRY_MS);
    piIp = MDNS.queryHost(PI_MDNS_HOSTNAME);
    attempts++;
  }
  if (piIp == IPAddress(0, 0, 0, 0)) {
    Serial.println("Pi not found via mDNS");
    return false;
  }
  piBaseUrl = "http://" + piIp.toString();
  Serial.print("Pi found at: ");
  Serial.println(piBaseUrl);
  return true;
}