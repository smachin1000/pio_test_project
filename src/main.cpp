/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <TeensyThreads.h>

#include "Arduino.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// Pin 3 on my Teensy 3.1 is wired to an additional LED.
#define LED_OUTPUT_2 3

static const int DEFAULT_STACK_SIZE = 128;

static void t1_thread_func(void* arg);
static void t2_thread_func(void* arg);

void setup()
{
    // initialize LED digital pin as an output.
    pinMode(LED_OUTPUT_2, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
            
    const int t1_id = threads.addThread(t1_thread_func, nullptr, DEFAULT_STACK_SIZE);
    if (t1_id == -1) {
        Serial.println("error creating thread t1");
    }

    const int t2_id = threads.addThread(t2_thread_func, nullptr, DEFAULT_STACK_SIZE);
    if (t2_id == -1) {
        Serial.println("error creating thread t2");
    }
}

void loop()
{
    // Nothing to do in loop function now
    delay(1);
}

static void t1_thread_func(void* arg) {
    while (true) {
        digitalWrite(LED_BUILTIN, HIGH);
        threads.delay(500);
        
	digitalWrite(LED_BUILTIN, LOW);
        threads.delay(500);
    }
}

static void t2_thread_func(void* arg) {
    while (true) {
        digitalWrite(LED_OUTPUT_2, HIGH);
        threads.delay(250);
        
	digitalWrite(LED_OUTPUT_2, LOW);
        threads.delay(250);
    }
}
