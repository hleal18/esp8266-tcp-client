/*
    Conexion a un servidor TCP remoto al cual
    se le envían y se reciben paquetes
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char *ssid = "******";
const char *password = "******";

const char *remote_tcp_server = "192.168.1.5";
uint16_t remote_tcp_port = 1200;

char incoming_message[255];

void setup()
{
    Serial.begin(115200);
    Serial.println();
    // Conexion a la red wifi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
}

void loop()
{
    // Permite crear conexiones TCP (Sockets).
    WiFiClient tcpclient;

    // Prueba que la conexion con el servidor TCP pueda realizarse
    if (!tcpclient.connect(remote_tcp_server, remote_tcp_port))
    {
        Serial.println("Connection failed.");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    Serial.println("Conexión al servidor TCP correcto.");
    // Se envía la petición al servidor.
    tcpclient.println("Datos que recibirá el servidor");
    // Se recibe la información desde el servidor.
    String line = tcpclient.readStringUntil('\r');
    Serial.println("Datos recibidos del servidor: ");
    Serial.println(line);

    Serial.println("Cerrando la conexion");
    tcpclient.stop();

    // Se retoma la conexion despues de 5 segundos.
    delay(5000);
}