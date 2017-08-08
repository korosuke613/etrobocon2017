#include "rtos/Thread.h"

#include "mbed.h"

namespace rtos {

// Private function only called in constructor, thus mutex is unneeded.
void Thread::constructor(osPriority priority,
        uint32_t stack_size, unsigned char *stack_pointer) {
    _tid = 0;
    _dynamic_stack = (stack_pointer == NULL);

    _thread_def.tpriority = priority;
    _thread_def.stacksize = stack_size;
    _thread_def.stack_pointer = (uint32_t*)stack_pointer;
    _thread_def.instances = 1;
}

void Thread::constructor(Callback<void()> task,
        osPriority priority, uint32_t stack_size, unsigned char *stack_pointer) {
    constructor(priority, stack_size, stack_pointer);

    switch (start(task)) {
        case osErrorResource:
            error("OS ran out of threads!\n");
            break;
        case osErrorParameter:
            error("Thread already running!\n");
            break;
        case osErrorNoMemory:
            error("Error allocating the stack memory\n");
        default:
            break;
    }
}

osStatus Thread::start(Callback<void()> task) {
    _mutex.lock();

    if (_tid != 0) {
        _mutex.unlock();
        return osErrorParameter;
    }

    _thread_def.pthread = Thread::_thunk;
    if (_thread_def.stack_pointer == NULL) {
        _thread_def.stack_pointer = new uint32_t[_thread_def.stacksize/sizeof(uint32_t)];
        MBED_ASSERT(_thread_def.stack_pointer != NULL);
    }

#if 0 // TODO: max_stack is not support yet
    //Fill the stack with a magic word for maximum usage checking
    for (uint32_t i = 0; i < (_thread_def.stacksize / sizeof(uint32_t)); i++) {
        _thread_def.stack_pointer[i] = 0xE25A2EA5;
    }
#endif

    _task = task;
    _tid = osThreadCreate(&_thread_def, this);
    if (_tid == NULL) {
        if (_dynamic_stack) {
            delete[] (_thread_def.stack_pointer);
            _thread_def.stack_pointer = (uint32_t*)NULL;
        }
        _mutex.unlock();
        _join_sem.release();
        return osErrorResource;
    }

    _mutex.unlock();
    return osOK;
}

osStatus Thread::terminate() {
    osStatus ret;
    _mutex.lock();

    // Set the Thread's tid to NULL and
    // release the semaphore before terminating
    // since this thread could be terminating itself
    osThreadId local_id = _tid;
    _join_sem.release();
    _tid = (osThreadId)NULL;

    ret = osThreadTerminate(local_id);

    _mutex.unlock();
    return ret;
}

osStatus Thread::wait(uint32_t millisec) {
    return osDelay(millisec);
}

Thread::~Thread() {
    // terminate is thread safe
    terminate();

    if (_dynamic_stack) {
        delete[] (_thread_def.stack_pointer);
        _thread_def.stack_pointer = (uint32_t*)NULL;
    }
}

void Thread::_thunk(const void * thread_ptr)
{
    Thread *t = (Thread*)thread_ptr;
    t->_task();
    t->_mutex.lock();
    t->_tid = (osThreadId)NULL;
    t->_join_sem.release();
    // rtos will release the mutex automatically
}

// TODO: modify upstream USBHost
extern "C"
void wait_ms(int ms) {
    Thread::wait(ms);
}

}

