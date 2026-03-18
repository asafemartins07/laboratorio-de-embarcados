/* CÓDIGO UTILIZANDO IA COMO AUXILIO DE DESENVOLVIMENTO (JSON) */
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NOME-REDE-WIFI";
const char* senha = "SENHA-REDE-WIFI";

WebServer server(80);

String ultimoJSON = "{}";

void handleDados() {
  server.send(200, "application/json", ultimoJSON);
}

void setup() {
  Serial.begin(115200);

  // Conectar ao WiFi
  WiFi.begin(ssid, senha);
  Serial.print("Conectando ao WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());

  // Rota HTTP
  server.on("/dados", handleDados);
  server.begin();
}

void loop() {
  server.handleClient();

  // Se o Arduino enviar JSON pela Serial, armazenar
  if (Serial.available()) {
    ultimoJSON = Serial.readStringUntil('\n');
  }
}

