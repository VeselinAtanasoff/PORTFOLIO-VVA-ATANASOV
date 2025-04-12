//Changes after feedback:removed the MutexHandler function as its functionality is already handled by the freeRTOS library.
#include <Arduino.h>

#define SCENE_SIZE 6

const int greenLed = 13;  // Sprinkler 1
const int yellowLed = 12; // Sprinkler 2
const int redLed = 14;    // Sprinkler 3

String Scene1[] = {"sp1 on", "wait 10", "sp1 off", "sp2 on", "wait 5", "sp2 off"};
String Scene2[] = {"sp1 on", "wait 2", "sp1 off", "sp3 on", "wait 3", "sp3 off"};
String Scene3[] = {"sp2 on", "wait 4", "sp2 off", "sp3 on", "wait 4", "sp3 off"};

SemaphoreHandle_t sp1Mutex;
SemaphoreHandle_t sp2Mutex;
SemaphoreHandle_t sp3Mutex;

QueueHandle_t stepsQueue;

void executeScene(String scene[]);
void readSerial(void *parameters);
void chooseScene(String msg);
void scene1(void *parameters);
void scene2(void *parameters);
void scene3(void *parameters);
void addStepsToQueue(String scene[]);
void executeSceneFromQueue(void *parameters);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  sp1Mutex = xSemaphoreCreateMutex();
  sp2Mutex = xSemaphoreCreateMutex();
  sp3Mutex = xSemaphoreCreateMutex();
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  xTaskCreate(readSerial, "readSerial", 2048, NULL, 1, NULL); // This task is created here, so it runs from the beginning
  stepsQueue = xQueueCreate(10, sizeof(String));
  if (stepsQueue == NULL)
  {
    Serial.println("Queue creation failed");
  }
  xTaskCreate(executeSceneFromQueue, "executeSceneFromQueue", 4096, NULL, 1, NULL);
}

void loop()
{

  vTaskDelay(100 / portTICK_PERIOD_MS);
}

void executeScene(String scene[])
{
  for (int i = 0; i < SCENE_SIZE; i++)
  {
    String command = scene[i];
    if (command == "sp1 on")
    {
      xSemaphoreTake(sp1Mutex, portMAX_DELAY);
      digitalWrite(greenLed, HIGH);
    }
    else if (command == "sp1 off")
    {
      digitalWrite(greenLed, LOW);
      xSemaphoreGive(sp1Mutex);
    }
    else if (command == "sp2 on")
    {
      xSemaphoreTake(sp2Mutex, portMAX_DELAY);
      digitalWrite(yellowLed, HIGH);
    }
    else if (command == "sp2 off")
    {
      digitalWrite(yellowLed, LOW);
      xSemaphoreGive(sp2Mutex);
    }
    else if (command == "sp3 on")
    {
      xSemaphoreTake(sp3Mutex, portMAX_DELAY);
      digitalWrite(redLed, HIGH);
    }
    else if (command == "sp3 off")
    {
      digitalWrite(redLed, LOW);
      xSemaphoreGive(sp3Mutex);
    }
    else if (command.startsWith("wait"))
    {
      int time = command.substring(5).toInt();
      vTaskDelay(time * 1000 / portTICK_PERIOD_MS);
    }else{
      Serial.println("Invalid command");
    }
  }
}

void chooseScene(String msg)
{
  // Execute the scene depending on the message received
  if (msg == "1")
  {
    Serial.println("Scene 1");
    msg = "";
    // xTaskCreate(scene1, "scene1", 4096, NULL, 1, NULL);
    addStepsToQueue(Scene1);
  }
  else if (msg == "2")
  {
    Serial.println("Scene 2");
    msg = "";
    // xTaskCreate(scene2, "scene2", 4096, NULL, 1, NULL);
    addStepsToQueue(Scene2);
  }
  else if (msg == "3")
  {
    Serial.println("Scene 3");
    msg = "";
    // xTaskCreate(scene3, "scene3", 4096, NULL, 1, NULL);
    addStepsToQueue(Scene3);
  }else{
    Serial.println("Invalid scene");
  }
}

void readSerial(void *parameters)
{
  // This task runs forever, reading the serial port
  for (;;)
  {
    if (Serial.available() > 0)
    {
      String msg = Serial.readString();
      msg.trim();
      Serial.println("Message received:" + msg);
      chooseScene(msg);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void scene1(void *parameters)
{
  executeScene(Scene1);
  vTaskDelete(NULL);
}

void scene2(void *parameters)
{
  executeScene(Scene2);
  vTaskDelete(NULL);
}

void scene3(void *parameters)
{
  executeScene(Scene3);
  vTaskDelete(NULL);
}

void addStepsToQueue(String scene[])
{
  for (int i = 0; i < SCENE_SIZE; i++)
  {
    String command = scene[i];
    xQueueSend(stepsQueue, &command, portMAX_DELAY);
  }
}

void executeSceneFromQueue(void *parameters)
{
  String command;
  while (xQueueReceive(stepsQueue, &command, portMAX_DELAY) == pdTRUE)
  {
    if (command == "sp1 on")
    {
      digitalWrite(greenLed, HIGH);
    }
    else if (command == "sp1 off")
    {
      digitalWrite(greenLed, LOW);
    }
    else if (command == "sp2 on")
    {
      digitalWrite(yellowLed, HIGH);
    }
    else if (command == "sp2 off")
    {
      digitalWrite(yellowLed, LOW);
    }
    else if (command == "sp3 on")
    {
      digitalWrite(redLed, HIGH);
    }
    else if (command == "sp3 off")
    {
      digitalWrite(redLed, LOW);
    }
    else if (command.startsWith("wait"))
    {
      int time = command.substring(5).toInt();
      vTaskDelay(time * 1000 / portTICK_PERIOD_MS);
    }
  }
  vTaskDelete(NULL);
}
