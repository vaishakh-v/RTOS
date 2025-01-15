#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Task handles
TaskHandle_t task1_handle = NULL; // Initialize task1 handle as NULL
TaskHandle_t task2_handle = NULL;

// Task 1: A simple blinking LED task
void Task1(void *pvParameters) {
  while (1) {
    Serial.println("Task 1 is running...");
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}

// Task 2: Monitor and manage Task1
void Task2(void *pvParameters) {
  int counter = 0;
  while (1) {
    counter++;

    // Suspend Task1 after 5 seconds
    if (counter == 5 && task1_handle != NULL) {
      Serial.println("Suspending Task 1...");
      vTaskSuspend(task1_handle);
    }

    // Resume Task1 after 10 seconds
    if (counter == 10 && task1_handle != NULL) {
      Serial.println("Resuming Task 1...");
      vTaskResume(task1_handle);
    }

    // Delete Task1 after 15 seconds
    if (counter == 15 && task1_handle != NULL) {
      Serial.println("Deleting Task 1...");
      vTaskDelete(task1_handle);
      task1_handle = NULL; // Set handle to NULL after deletion
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}

void setup() {
  Serial.begin(115200);

  // Create Task1
  xTaskCreate(Task1, "Task 1", 1000, NULL, 1, &task1_handle);
  Serial.println("Task 1 created.");

  // Create Task2
  xTaskCreate(Task2, "Task 2", 1000, NULL, 1, &task2_handle);
  Serial.println("Task 2 created.");
}

void loop() {
  // Main loop can run other non-blocking code
}
