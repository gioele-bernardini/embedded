#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include <stdio.h>

#include "uart.h"

/**
 * UART baudrate configuration.
 */
const uint32_t uart_baudrate = 115200;

/***
 * Declaration of functions
 */
void vTaskAFunction(void *pvParameters);
void vTaskBFunction(void *pvParameters);

void vSimpleDelay();

/* The counter which is used to check when a task should be deleted */
int counter = 0;

/* The handle to TaskA, which can be used to delete TaskA */
TaskHandle_t xTaskAHandle = NULL;

/* semaphore handle */
SemaphoreHandle_t xMutex = 0;

/*-----------------------------------------------------------*/
int main(void) {
  // Initialize UART
  uart_init(uart_baudrate);

  BaseType_t result = pdPASS;

  uart_println("Creating TaskA.");
  char *pcParameters1 = "TaskA is running and running.";
  result = xTaskCreate(vTaskAFunction, "TaskA", 1000, (void *)pcParameters1, 1,
                       &xTaskAHandle);
  if (result != pdPASS) {
    uart_println("Error creating TaskA task.");
    return 0;
  }

  uart_println("Creating TaskB.");
  char *pcParameters2 = "TaskB is running and running.";
  result = xTaskCreate(vTaskBFunction, "TaskB", 1000, (void *)pcParameters2, 1,
                       NULL);
  if (result != pdPASS) {
    uart_println("Error creating TaskB task.");
    return 0;
  }

  xMutex = xSemaphoreCreateMutex();

  // Start the tasks
  vTaskStartScheduler();

  /* The following line should never be reached.
   * Otherwise there was insufficient FreeRTOS heap
   * memory available for the task to be created.
   */
  return 0;
}
/*-----------------------------------------------------------*/

void vTaskAFunction(void *pvParameters) {
  char *message = (char *)pvParameters;
  uart_println("Start TaskA.");

  while (1) {
    xSemaphoreTake(xMutex, portMAX_DELAY);
    uart_println(message);
    xSemaphoreGive(xMutex);
    vSimpleDelay();
  }
}

void vTaskBFunction(void *pvParameters) {
  char *message = (char *)pvParameters;
  uart_println("Start TaskB.");

  while (1) {
    xSemaphoreTake(xMutex, portMAX_DELAY);
    uart_println("%d: ", counter);
    uart_println(message);
    xSemaphoreGive(xMutex);
    if (counter == 10) {
      vTaskDelete(xTaskAHandle);
    } else if (counter == 20) {
      vTaskDelete(NULL);
    }
    counter++;
    vSimpleDelay();
  }
}
// m1_3_3e//

/***
 * Wait for a given amount of time
 */
void vSimpleDelay() {
  uint32_t i;
  for (i = 0; i < 100000; i++) {
  }
}

/* -------------------------------------------------------------------------
 * Default FreeRTOS hooks
 * ------------------------------------------------------------------------- */

void vApplicationMallocFailedHook(void) {
  /* vApplicationMallocFailedHook() will only be called if
  configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
  function that will get called if a call to pvPortMalloc() fails.
  pvPortMalloc() is called internally by the kernel whenever a task, queue,
  timer or semaphore is created.  It is also called by various parts of the
  demo application.  If heap_1.c or heap_2.c are used, then the size of the
  heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
  FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
  to query the size of free heap space that remains (although it does not
  provide information on how the remaining heap might be fragmented). */
  taskDISABLE_INTERRUPTS();
  for (;;)
    ;
}
/* ------------------------------------------------------------------------- */

void vApplicationIdleHook(void) {
  /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
  to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
  task.  It is essential that code added to this hook function never attempts
  to block in any way (for example, call xQueueReceive() with a block time
  specified, or call vTaskDelay()).  If the application makes use of the
  vTaskDelete() API function (as this demo application does) then it is also
  important that vApplicationIdleHook() is permitted to return to its calling
  function, because it is the responsibility of the idle task to clean up
  memory allocated by the kernel to any task that has since been deleted. */
}
/* ------------------------------------------------------------------------- */

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
  (void)pcTaskName;
  (void)pxTask;

  /* Run time stack overflow checking is performed if
  configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
  function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  for (;;)
    ;
}
/* ------------------------------------------------------------------------- */

void *malloc(size_t xSize) {
  /* There should not be a heap defined, so trap any attempts to call
  malloc. */
  Interrupt_disableMaster();
  for (;;)
    ;
}
/* ------------------------------------------------------------------------- */

/*-----------------------------------------------------------*/

void vPreSleepProcessing(uint32_t ulExpectedIdleTime) {}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void) {
  /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */

  /* The full demo includes a software timer demo/test that requires
   prodding periodically from the tick interrupt. */
  // vTimerPeriodicISRTests();
  /* Call the periodic event group from ISR demo. */
  // vPeriodicEventGroupsProcessing();
  /* Use task notifications from an interrupt. */
  // xNotifyTaskFromISR();
  /* Use mutexes from interrupts. */
  // vInterruptSemaphorePeriodicTest();
}
/*-----------------------------------------------------------*/
