#include "mqtt.h"
#include "./beacon/beacon.h"


WiFiClient wifiClient;
PubSubClient mqttClient(RASP_BROKER_IP, PORTA, wifiClient);

void Mqtt::wifiConnect() {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }
  WiFi.begin(SSIDRASP, PASS);
  Serial.println("Conectando à rede WiFi");
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Não conectado ao WiFi");
    delay(2000);
    ESP.restart();
  }
  Serial.println("");
  Serial.println("Conectado à rede WiFi");
  WiFi.mode(WIFI_STA);
}


void Mqtt::mqtt(String beacon[], int tamanho) {
  if (mqttClient.connect(nome_servidor, MQTT_USER, MQTT_SENHA)) {
    Serial.println("Conectado ao broker MQTT");
  } else {
    Serial.println("Falha ao conectar ao broker MQTT");
  }

  if (mqttClient.connected()) {
    String mensagem;
    for (int i = 0; i < tamanho; i++) {
        mensagem = mensagem + beacon[i];
    }

    mqttClient.publish(nome_servidor, mensagem.c_str());
    //Serial.println(mensagem);
  }
}
