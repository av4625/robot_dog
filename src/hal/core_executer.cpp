#include "core_executer.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace hal
{

void core_executer::execute(std::function<void()> func) const
{
    /**
     * I don't like having to create a pointer to the function object using new
     * here. The problem is that `func` needs to be kept alive if it was passed
     * into the task. You could do this buy putting it in an unordered_map
     * member variable and then passing an instance and the map key to the task.
     * With this approach you would need synchronisation as there could be
     * multiple tasks created trying to access the map. They are all on the same
     * core so shouldn't be doing it togther, but because they are all the same
     * priority they use round robin synchronisation. This means _I think_ that
     * one task could be halted while accessing the map and then another process
     * started and then it could access the map.
     */
    const std::function<void()>* func_ptr{new std::function<void()>(func)};

    xTaskCreatePinnedToCore(
        executable,          // Task function.
        "Executer Task",     // Name of task.
        5000,                // Stack size of task
        &func_ptr,           // Parameter of the task
        10,                  // Priority of the task
        NULL,                // Task handle to keep track of created task
        1);                  // Pin task to core 1
}

void core_executer::executable(void* data)
{
    if (data != NULL)
    {
        (*reinterpret_cast<std::function<void()>*>(data))();
        delete data;
    }

    vTaskDelete(NULL);
}

}
