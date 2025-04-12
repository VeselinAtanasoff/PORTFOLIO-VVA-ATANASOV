#include "Dashboard.h"
#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Nothing";
const char *password = "fontyssucks";

const char *mqttserver = "test.mosquitto.org";
const int mqttport = 1883;
const char *mqttUser = "";
const char *mqttPassword = "";

uint32_t timeout = 8000;
uint32_t lastReceivedTimeTires = 0;
uint32_t lastReceivedTimeEngine = 0;
uint32_t lastReceivedTimeLights = 0;
uint32_t lastReceivedTimeSpeed = 0;
uint32_t speedTimeout = 1000;

WiFiClient espClient;
PubSubClient client(espClient);

MCP_CAN CAN(CS_PIN);

void callback(char *topic, byte *payload, unsigned int length);
void reconnect();

Dashboard::Dashboard(int intPin)
    : intPin(intPin)
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Conneceting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    client.setServer(mqttserver, mqttport);
    client.setCallback(callback);

    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");

        if (client.connect("userid"))
        {
            Serial.println("Connected to MQTT");
            client.subscribe("LightSwitchCar");
            client.subscribe("EngineSpeedControl");
            client.subscribe("EngineBrakeControl");
        }
        else
        {
            Serial.println("Failed with state ");
            Serial.print(client.state());
            Serial.println("");
            delay(2000);
        }
    }

    pinMode(potPin, INPUT);
    pinMode(leftIndicatorBtnPin, INPUT);
    pinMode(rightIndicatorBtnPin, INPUT);
    pinMode(headlightsBtnPin, INPUT);
    pinMode(brakesBtnPin, INPUT);
    if (CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK)
    {
        CAN.setMode(MCP_NORMAL);
        pinMode(intPin, INPUT);
        Serial.println("MCP2515 Initialized Successfully!");
    }
    else
    {
        Serial.println("Error Initializing MCP2515...");
        while (1)
            ;
    }

    lcd = new LCDScreen();

    lcd->Clear();
    lcd->PrintFirstRow("Temp:OK PSI:OK", 0);
    lcd->PrintSecondRow("E:OK T:OK L:OK", 0);
}

void Dashboard::CANListener()
{
    unsigned char len = 0;
    unsigned char buf[16];
    unsigned long canId = 0;

    while (1)
    {
        if (!digitalRead(intPin))
        {
            if (CAN.readMsgBuf(&canId, &len, buf) == CAN_OK)
            {
                Serial.print("ID: ");
                canId = canId & 0x7FF;
                Serial.println(canId, HEX);
                Serial.print(" Data: ");
                for (int i = 0; i < len; i++)
                {
                    Serial.print(buf[i], HEX);
                    Serial.println(" ");
                }

                switch (canId)
                {
                case HIGH_TEMP_ID:
                    HandleHighTempWarning();
                    break;
                case LOW_PSI_ID:
                    HandleLowPSIWarning();
                    break;
                case TEMP_OK_ID:
                    HandleTempOK();
                    break;
                case PSI_OK_ID:
                    HandlePSIOK();
                    break;
                case PSI_ID:
                    HandlePSI(buf[0]);
                    lastReceivedTimeTires = millis();
                    break;
                case TEMP_ID:
                    HandleTemp(buf[0]);
                    lastReceivedTimeEngine = millis();
                    break;
                case LIGHTS_PING_ID:
                    lastReceivedTimeLights = millis();
                    break;
                default:
                    break;
                }
            }
        }
        if (!client.connected())
        {
            reconnect(); // Reconnect if the connection is lost
        }
        client.loop();
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}

void Dashboard::ButtonListener()
{
    const int buttonPins[4] = {
        leftIndicatorBtnPin,
        rightIndicatorBtnPin,
        headlightsBtnPin,
        brakesBtnPin};

    // Debounce variables
    const int debounceDelay = 50;                             // 50 ms
    static int buttonState[4] = {HIGH, HIGH, HIGH, HIGH};     // Current stable state
    static int lastButtonState[4] = {HIGH, HIGH, HIGH, HIGH}; // Previous stable state
    static unsigned long lastDebounceTime[4] = {0, 0, 0, 0};  // Time of last change

    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            int reading = digitalRead(buttonPins[i]);

            // Detect state change
            if (reading != lastButtonState[i])
            {
                lastDebounceTime[i] = millis(); // Reset debounce timer
            }

            // Check if stable for debounceDelay
            if ((millis() - lastDebounceTime[i]) > debounceDelay)
            {
                // If the button state has changed
                if (reading != buttonState[i])
                {
                    buttonState[i] = reading;

                    // If the button is pressed
                    if (buttonState[i] == LOW) // Assuming active LOW
                    {
                        SendCANMessageBasedOnButton(i);
                    }
                }
            }

            lastButtonState[i] = reading; // Update last state
        }

        vTaskDelay(pdMS_TO_TICKS(20)); // Task delay
    }
}

void Dashboard::PotentiometerListener()
{
    const int potMin = 0;
    const int potMax = 1023;
    const int scaledMin = 0;
    const int scaledMax = 7000;
    int lastRPM = -1;

    while (true)
    {
        int rawPotValue = analogRead(potPin);

        rawPotValue = constrain(rawPotValue, potMin, potMax);

        int scaledRPMValue = map(rawPotValue, potMin, potMax, scaledMin, scaledMax);

        if (scaledRPMValue != lastRPM)
        {
            SendCANMessageBasedOnPot(scaledRPMValue);
            lastRPM = scaledRPMValue;
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void Dashboard::SendCANMessageBasedOnButton(int buttonIndex)
{
    uint8_t messageId;
    uint8_t payload;
    switch (buttonIndex)
    {
    case 0: // Left indicator
    {
        messageId = INDICATOR_ID;
        payload = 'L';
        Serial.println("left indicator");
        break;
    }
    case 1: // Right indicator
    {
        messageId = INDICATOR_ID;
        payload = 'R';
        Serial.println("right indicator");
        break;
    }
    case 2: // Headlights
    {
        messageId = HEADLIGHTS_ID;
        payload = 1;
        Serial.println("headlights");
        break;
    }
    case 3: // Brakes
    {
        messageId = BRAKES_ID;
        payload = 'B';
        Serial.println("brakes");
        break;
    }
    default:
        Serial.println("Invalid button index received in SendCANMessageBasedOnButton.");
        return;
    }

    int sendState = CAN.sendMsgBuf(messageId, 0, 1, &payload);
    if (sendState == CAN_OK)
    {
        Serial.print("Message sent for button ");
        Serial.println(buttonIndex);
    }
    else
    {
        Serial.println(sendState);
        Serial.println("Error sending CAN message...");
    }
}

void Dashboard::SendCANMessageBasedOnPot(int rpmValue)
{
    uint8_t payload[2];

    payload[0] = (rpmValue >> 8) & 0xFF;
    payload[1] = rpmValue & 0xFF;

    if (millis() - lastReceivedTimeSpeed > speedTimeout)
    {
        if (CAN.sendMsgBuf(SPEED_ID, 0, 2, payload) == CAN_OK)
        {
            Serial.print("RPM value sent: ");
            Serial.println(rpmValue);

            char payload[10];
            snprintf(payload, sizeof(payload), "%d", rpmValue);
            client.publish("EngineSpeedControl", payload);

            lastReceivedTimeSpeed = millis();
        }
        else
        {
            Serial.println(CAN.sendMsgBuf(SPEED_ID, 0, 2, payload));
            Serial.println("Error sending CAN message for RPM value...");
        }
    }
}

void Dashboard::HandleHighTempWarning()
{
    lcd->PrintFirstRow("Temp:WN", 0);
}

void Dashboard::HandleLowPSIWarning()
{
    lcd->PrintFirstRow("PSI:WN", 8);
}

void Dashboard::HandleTempOK()
{
    lcd->PrintFirstRow("Temp:OK", 0);
}

void Dashboard::HandlePSIOK()
{
    lcd->PrintFirstRow("PSI:OK", 8);
}

void Dashboard::HandlePSI(int PSI)
{
    char payload[10];
    snprintf(payload, sizeof(payload), "%d", PSI);
    client.publish("TiresPSIReading", payload);
}

void Dashboard::HandleTemp(int temp)
{
    char payload[10];
    snprintf(payload, sizeof(payload), "%d", temp);
    client.publish("EngineTempReading", payload);
}

void Dashboard::StatusCheck()
{
    while (1)
    {
        PingLight();
        if (millis() - lastReceivedTimeTires > timeout)
        {
            Serial.println("Tires not responding");
            lcd->PrintSecondRow("T:WN", 5);
            char payload[10];
            snprintf(payload, sizeof(payload), "Twn");
            client.publish("TiresNodeStatus", payload);
        }
        else
        {
            lcd->PrintSecondRow("T:OK", 5);
            char payload[10];
            snprintf(payload, sizeof(payload), "Tok");
            client.publish("TiresNodeStatus", payload);
        }

        if (millis() - lastReceivedTimeEngine > timeout)
        {
            Serial.println("Engine not responding");
            lcd->PrintSecondRow("E:WN", 0);
            char payload[10];
            snprintf(payload, sizeof(payload), "Ewn");
            client.publish("EngineNodeStatus", payload);
        }
        else
        {
            lcd->PrintSecondRow("E:OK", 0);
            char payload[10];
            snprintf(payload, sizeof(payload), "Eok");
            client.publish("EngineNodeStatus", payload);
        }

        if (millis() - lastReceivedTimeLights > timeout)
        {
            Serial.println("Lights not responding");
            lcd->PrintSecondRow("L:WN", 10);
            char payload[10];
            snprintf(payload, sizeof(payload), "Lwn");
            client.publish("LightsNodeStatus", payload);
        }
        else
        {
            lcd->PrintSecondRow("L:OK", 10);
            client.publish("LightsNodeStatus", "Lok");
        }

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}

void Dashboard::PingLight()
{
    uint8_t payload = 0x01; // Payload is empty for a ping message

    // Send the ping message
    if (CAN.sendMsgBuf(LIGHTS_PING_ID, 0, 1, &payload) == CAN_OK)
    {
        Serial.println("Ping sent to lights node");
    }
    else
    {
        Serial.println("Error sending ping message...");
        return;
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println();
    Serial.print("Message received on topic: ");
    Serial.println(topic);

    Serial.print("Message: ");
    char message[length + 1];         // Create a buffer with an extra byte for the null terminator
    memcpy(message, payload, length); // Copy the payload to the buffer
    message[length] = '\0';           // Null-terminate the string

    Serial.println(message); // Print the message

    uint8_t canPayload;
    int messageID;

    // Handle topics and messages
    if (strcmp(topic, "LightSwitchCar") == 0)
    {
        if (strcmp(message, "H") == 0)
        {
            canPayload = 1;
            messageID = HEADLIGHTS_ID;
        }
        else if (strcmp(message, "L") == 0)
        {
            canPayload = 'L';
            messageID = INDICATOR_ID;
        }
        else if (strcmp(message, "R") == 0)
        {
            canPayload = 'R';
            messageID = INDICATOR_ID;
        }

        if (CAN.sendMsgBuf(messageID, 0, 1, &canPayload) == CAN_OK)
        {
            Serial.println("Lights MQTT");
        }
    }
    else if (strcmp(topic, "EngineSpeedControl") == 0)
    {
        Serial.print("Engine Speed Control: ");
        Serial.println(message);
        messageID = SPEED_ID;
        int rpmValue = atoi(message);
        uint8_t canPayload2Bytes[2];

        canPayload2Bytes[0] = (rpmValue >> 8) & 0xFF;
        canPayload2Bytes[1] = rpmValue & 0xFF;

        if (CAN.sendMsgBuf(messageID, 0, 2, canPayload2Bytes) == CAN_OK)
        {
            Serial.println("Speed MQTT");
        }
    }
    else if (strcmp(topic, "EngineBrakeControl") == 0)
    {
        if (strcmp(message, "B") == 0)
        {
            canPayload = 'B';
            messageID = BRAKES_ID;
            if (CAN.sendMsgBuf(messageID, 0, 1, &canPayload) == CAN_OK)
            {
                Serial.println("Brakes MQTT");
            }
        }
    }
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.println("Attempting MQTT connection...");
        if (client.connect("DashboardNode"))
        {
            Serial.println("Connected to MQTT broker");
            client.subscribe("LightSwitchCar");
            client.subscribe("EngineSpeedControl");
            client.subscribe("EngineBrakeControl");
        }
        else
        {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}