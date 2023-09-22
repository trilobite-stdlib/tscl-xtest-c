/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.code.blog>
*/
#ifndef TRILOBITE_XMOCK_H
#define TRILOBITE_XMOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "xtest.h"

// Define mock function return types based on types.
typedef int xmock_int;
typedef int8_t xmock_int8_t;
typedef int16_t xmock_int16_t;
typedef int32_t xmock_int32_t;
typedef int64_t xmock_int64_t;
typedef unsigned int xmock_uint;
typedef uint8_t xmock_uint8_t;
typedef uint16_t xmock_uint16_t;
typedef uint32_t xmock_uint32_t;
typedef uint64_t xmock_uint64_t;
typedef uint8_t xmock_hex8_t;
typedef uint16_t xmock_hex16_t;
typedef uint32_t xmock_hex32_t;
typedef uint64_t xmock_hex64_t;
typedef float xmock_float;
typedef double xmock_double;

// Define a macro for char type.
typedef char xmock_char;

// Define a macro for char * type.
typedef char *xmock_string;

typedef void *xmock_default;

// Define a mocked function using macro concatenation.
// This macro provides a way to define mocked functions with specified return types and arguments.
#define XMOCK_FUNC(type, name) type xmock_##name(type arg)

/**
 * @file mock_data_structures.h
 *
 * @brief Mock Data Structures
 *
 * This file defines a set of mock data structures and associated functions for educational
 * purposes. These data structures are simplified versions of common data structures used
 * in computer science and software development.
 *
 * 1. Mock Stack:
 *    - The `XMockStack` structure represents a stack, a Last-In, First-Out (LIFO) data structure.
 *    - It consists of an array (`data`) to store stack elements, the current size (`size`) of
 *      the stack, and the maximum capacity (`capacity`) of the stack.
 *    - Functions:
 *      - `XMockStack* xmock_stack_create(int capacity)`:
 *        Creates and initializes a mock stack with the given capacity.
 *      - `void xmock_stack_push(XMockStack* stack, int element)`:
 *        Pushes an element onto the stack.
 *      - `int xmock_stack_pop(XMockStack* stack)`:
 *        Pops an element from the stack.
 *      - `int xmock_stack_size(XMockStack* stack)`:
 *        Returns the current size of the stack.
 *      - `void xmock_stack_destroy(XMockStack* stack)`:
 *        Destroys the mock stack and releases allocated resources.
 *
 * 2. Mock Doubly Linked List:
 *    - The `XMockDoublyLinkedList` structure represents a doubly linked list.
 *    - It consists of nodes (`XMockNode`) with integer data, where each node has pointers to
 *      the previous (`prev`) and next (`next`) nodes.
 *    - The linked list maintains pointers to the `head` (first node) and `tail` (last node),
 *      as well as the current size (`size`) of the list.
 *    - Functions:
 *      - `XMockDoublyLinkedList* xmock_doubly_linked_list_create()`:
 *        Creates and initializes a mock doubly linked list.
 *      - `void xmock_doubly_linked_list_push_front(XMockDoublyLinkedList* list, int data)`:
 *        Inserts an element at the beginning of the list.
 *      - `void xmock_doubly_linked_list_push_back(XMockDoublyLinkedList* list, int data)`:
 *        Inserts an element at the end of the list.
 *      - `int xmock_doubly_linked_list_pop_front(XMockDoublyLinkedList* list)`:
 *        Removes and returns the first element of the list.
 *      - `int xmock_doubly_linked_list_pop_back(XMockDoublyLinkedList* list)`:
 *        Removes and returns the last element of the list.
 *      - `int xmock_doubly_linked_list_size(XMockDoublyLinkedList* list)`:
 *        Returns the current size of the list.
 *      - `void xmock_doubly_linked_list_destroy(XMockDoublyLinkedList* list)`:
 *        Destroys the mock doubly linked list and releases allocated resources.
 *
 * 3. Mock Queue:
 *    - The `XMockQueue` structure represents a queue, a First-In, First-Out (FIFO) data structure.
 *    - It consists of an array (`data`) to store queue elements, pointers to the `front` and `rear`
 *      indices, the current size (`size`) of the queue, and the maximum capacity (`capacity`) of
 *      the queue.
 *    - Functions:
 *      - `XMockQueue* xmock_queue_create(int capacity)`:
 *        Creates and initializes a mock queue with the given capacity.
 *      - `void xmock_queue_enqueue(XMockQueue* queue, int element)`:
 *        Enqueues an element into the queue.
 *      - `int xmock_queue_dequeue(XMockQueue* queue)`:
 *        Dequeues and returns the front element of the queue.
 *      - `int xmock_queue_size(XMockQueue* queue)`:
 *        Returns the current size of the queue.
 *      - `void xmock_queue_destroy(XMockQueue* queue)`:
 *        Destroys the mock queue and releases allocated resources.
 *
 * 4. Mock Map:
 *    - The `XMockMap` structure represents a simple key-value map.
 *    - It consists of an array of key-value pairs (`entries`), the current size (`size`) of the map,
 *      and a maximum size defined by `XMOCK_MAP_MAX_SIZE`.
 *    - Functions:
 *      - `XMockMap* xmock_map_create()`:
 *        Creates and initializes a mock map.
 *      - `void xmock_map_put(XMockMap* map, int key, int value)`:
 *        Puts a key-value pair into the map.
 *      - `int xmock_map_get(XMockMap* map, int key)`:
 *        Gets the value associated with a key from the map.
 *      - `int xmock_map_contains(XMockMap* map, int key)`:
 *        Checks if a key exists in
 */

//
// MOCK STACK
//

// Define the mock stack structure
typedef struct {
    int* data;      // Array to store stack elements
    int size;       // Current size of the stack
    int capacity;   // Maximum capacity of the stack
} XMockStack;

// Create and initialize a mock stack
// @param capacity: Maximum capacity of the stack
// @return: A pointer to the newly created stack
XTEST_API XMockStack* xmock_stack_create(int capacity);

// Push an element onto the mock stack
// @param stack: Pointer to the stack
// @param element: Element to be pushed onto the stack
XTEST_API void xmock_stack_push(XMockStack* stack, int element);

// Pop an element from the mock stack
// @param stack: Pointer to the stack
// @return: The popped element
XTEST_API int xmock_stack_pop(XMockStack* stack);

// Get the size of the mock stack
// @param stack: Pointer to the stack
// @return: Current size of the stack
XTEST_API int xmock_stack_size(XMockStack* stack);

// Destroy the mock stack and release resources
// @param stack: Pointer to the stack to be destroyed
XTEST_API void xmock_stack_destroy(XMockStack* stack);


//
// MOCK LINKED LIST
//

// Define the mock doubly linked list node structure
typedef struct XMockNode {
    int data;                   // Data stored in the node
    struct XMockNode* prev;     // Pointer to the previous node
    struct XMockNode* next;     // Pointer to the next node
} XMockNode;

// Define the mock doubly linked list structure
typedef struct {
    XMockNode* head;            // Pointer to the first node
    XMockNode* tail;            // Pointer to the last node
    int size;                   // Current size of the list
} XMockDoublyLinkedList;

// @brief Create and initialize a mock doubly linked list.
// @return A pointer to the created mock doubly linked list or NULL if allocation fails.
XTEST_API XMockDoublyLinkedList* xmock_doubly_linked_list_create();

// @brief Insert an element at the beginning of the list.
// @param list The mock doubly linked list to which the element will be added.
// @param data The data to insert.
XTEST_API void xmock_doubly_linked_list_push_front(XMockDoublyLinkedList* list, int data);

// @brief Insert an element at the end of the list.
// @param list The mock doubly linked list to which the element will be added.
// @param data The data to insert.
XTEST_API void xmock_doubly_linked_list_push_back(XMockDoublyLinkedList* list, int data);

// @brief Remove and return the first element of the list.
// @param list The mock doubly linked list from which the first element will be removed.
// @return The value of the first element or 0 if the list is empty.
XTEST_API int xmock_doubly_linked_list_pop_front(XMockDoublyLinkedList* list);

// @brief Remove and return the last element of the list.
// @param list The mock doubly linked list from which the last element will be removed.
// @return The value of the last element or 0 if the list is empty.
XTEST_API int xmock_doubly_linked_list_pop_back(XMockDoublyLinkedList* list);

// @brief Get the size of the list.
// @param list The mock doubly linked list for which to determine the size.
// @return The current size of the list.
XTEST_API int xmock_doubly_linked_list_size(XMockDoublyLinkedList* list);

// @brief Destroy the mock doubly linked list and release allocated resources.
// @param list The mock doubly linked list to destroy.
XTEST_API void xmock_doubly_linked_list_destroy(XMockDoublyLinkedList* list);


//
// XMOCK QUEUE
//

// @brief Define the mock queue structure.
typedef struct {
    int* data;       // @brief Array to store queue elements.
    int front;       // @brief Index of the front element.
    int rear;        // @brief Index of the rear element.
    int size;        // @brief Current size of the queue.
    int capacity;    // @brief Maximum capacity of the queue.
} XMockQueue;

// @brief Create and initialize a mock queue.
// @param capacity The maximum capacity of the queue.
// @return A pointer to the created mock queue or NULL if allocation fails.
XTEST_API XMockQueue* xmock_queue_create(int capacity);

// @brief Enqueue an element into the mock queue.
// @param queue The mock queue to which the element will be enqueued.
// @param element The element to be enqueued.
XTEST_API void xmock_queue_enqueue(XMockQueue* queue, int element);

// @brief Dequeue and return the front element of the mock queue.
// @param queue The mock queue from which the front element will be dequeued.
// @return The front element of the queue or 0 if the queue is empty.
XTEST_API int xmock_queue_dequeue(XMockQueue* queue);

// @brief Get the size of the mock queue.
// @param queue The mock queue for which to determine the size.
// @return The current size of the queue.
XTEST_API int xmock_queue_size(XMockQueue* queue);

// @brief Destroy the mock queue and release allocated resources.
// @param queue The mock queue to destroy.
XTEST_API void xmock_queue_destroy(XMockQueue* queue);



//
// XMOCK MAP
//

// @brief Define the maximum number of key-value pairs the mock map can hold.
#define XMOCK_MAP_MAX_SIZE 100

// @brief Define the key-value pair structure.
typedef struct {
    int key;    // @brief The key of the entry.
    int value;  // @brief The value associated with the key.
} XMockMapEntry;

// @brief Define the mock map structure.
typedef struct {
    XMockMapEntry entries[XMOCK_MAP_MAX_SIZE];  // @brief Array of key-value pairs.
    int size;                                   // @brief Current number of entries in the map.
} XMockMap;

// @brief Create and initialize a mock map.
XTEST_API XMockMap* xmock_map_create();

// @brief Put a key-value pair into the mock map.
// @param map The mock map to which the entry will be added.
// @param key The key of the entry to add.
// @param value The value associated with the key.
XTEST_API void xmock_map_put(XMockMap* map, int key, int value);

// @brief Get the value associated with a key from the mock map.
// @param map The mock map to search for the key.
// @param key The key to look up in the map.
// @return The value associated with the key or 0 if the key is not found.
XTEST_API int xmock_map_get(XMockMap* map, int key);

// @brief Check if a key exists in the mock map.
// @param map The mock map to check for the key.
// @param key The key to check for existence.
// @return 1 if the key exists in the map, 0 otherwise.
XTEST_API int xmock_map_contains(XMockMap* map, int key);

// @brief Remove a key-value pair from the mock map.
// @param map The mock map from which the entry will be removed.
// @param key The key of the entry to remove.
XTEST_API void xmock_map_remove(XMockMap* map, int key);

// @brief Get the number of key-value pairs in the mock map.
// @param map The mock map for which to count the entries.
// @return The number of key-value pairs in the map.
XTEST_API int xmock_map_size(XMockMap* map);

// @brief Destroy the mock map and release allocated resources.
// @param map The mock map to destroy.
XTEST_API void xmock_map_destroy(XMockMap* map);


/**
 * @brief Mock Hardware Emulation Structures
 *
 * These structures, namely XMockSensor, XMockMotor, and XMockActuator, are designed
 * to emulate the behavior of various hardware components in a simulated environment.
 * They serve as placeholders for representing sensors, motors, and actuators, allowing
 * developers to create, manipulate, and interact with these virtual hardware components
 * for testing and simulation purposes.
 *
 * XMockSensor:
 *   - Represents a simulated sensor.
 *   - Contains a sensor ID for unique identification and a floating-point value
 *     to mimic sensor readings.
 *
 * XMockMotor:
 *   - Represents a simulated motor.
 *   - Contains a motor ID for unique identification and an integer value to represent
 *     the motor's speed.
 *
 * XMockActuator:
 *   - Represents a simulated actuator.
 *   - Contains an actuator ID for unique identification and an integer state, which
 *     can be either 0 for OFF or 1 for ON, to mimic the actuator's status.
 *
 * These structures are intended for use in software testing, debugging, and simulation
 * scenarios, allowing developers to model and simulate interactions with hardware
 * components without the need for physical hardware. They can be customized and extended
 * to simulate various hardware behaviors and are particularly useful in scenarios where
 * real hardware is unavailable or costly to access.
 *
 * Usage:
 *   - Initialize these structures using the provided initialization functions.
 *   - Interact with the hardware mock components by setting or reading their values.
 *   - Simulate hardware actions such as starting or stopping motors or changing sensor
 *     readings using the provided functions.
 *   - Customize these structures and functions as needed to match specific hardware
 *     behaviors in your simulated environment.
 *
 * Note: These mock structures are not intended for use in production code and are
 * solely designed for testing and simulation purposes.
 */

/**
 * @brief Structure representing a sensor in a simulated environment.
 */
typedef struct {
    uint8_t sensor_id; ///< The sensor's unique identifier.
    float value;       ///< The sensor's value.
} XMockSensor;

/**
 * @brief Structure representing a motor in a simulated environment.
 */
typedef struct {
    uint8_t motor_id; ///< The motor's unique identifier.
    int speed;        ///< The motor's speed.
} XMockMotor;

/**
 * @brief Structure representing an actuator in a simulated environment.
 */
typedef struct {
    uint8_t actuator_id; ///< The actuator's unique identifier.
    int state;           ///< The actuator's state (0 for OFF, 1 for ON).
} XMockActuator;

/**
 * @brief Initializes an XMockSensor instance.
 *
 * This function sets the sensor's ID and initializes its value to 0.0f.
 *
 * @param sensor Pointer to the XMockSensor instance to initialize.
 * @param id     The sensor's unique identifier.
 *
 * @return None.
 */
void xmock_sensor_init(XMockSensor *sensor, uint8_t id);

/**
 * @brief Reads the value from an XMockSensor.
 *
 * This function simulates reading a sensor value (replace with actual sensor behavior).
 * For demonstration, we increment the sensor's value by 0.1f with each read.
 *
 * @param sensor Pointer to the XMockSensor instance to read from.
 *
 * @return The current sensor value.
 */
float xmock_sensor_read(XMockSensor *sensor);

/**
 * @brief Initializes an XMockMotor instance.
 *
 * This function sets the motor's ID and initializes its speed to 0.
 *
 * @param motor Pointer to the XMockMotor instance to initialize.
 * @param id    The motor's unique identifier.
 *
 * @return None.
 */
XTEST_API void xmock_motor_init(XMockMotor *motor, uint8_t id);

/**
 * @brief Sets the speed of an XMockMotor.
 *
 * @param motor Pointer to the XMockMotor instance to set the speed for.
 * @param speed The desired speed to set.
 *
 * @return None.
 */
XTEST_API void xmock_motor_set_speed(XMockMotor *motor, int speed);

/**
 * @brief Gets the current speed of an XMockMotor.
 *
 * @param motor Pointer to the XMockMotor instance to get the speed from.
 *
 * @return The current speed of the motor.
 */
XTEST_API int xmock_motor_get_speed(XMockMotor *motor);

/**
 * @brief Starts an XMockMotor.
 *
 * This function simulates starting the motor (replace with actual motor start logic).
 * For demonstration, it prints a message indicating that the motor has started.
 *
 * @param motor Pointer to the XMockMotor instance to start.
 *
 * @return None.
 */
XTEST_API void xmock_motor_start(XMockMotor *motor);

/**
 * @brief Stops an XMockMotor.
 *
 * This function simulates stopping the motor (replace with actual motor stop logic).
 * For demonstration, it prints a message indicating that the motor has stopped.
 *
 * @param motor Pointer to the XMockMotor instance to stop.
 *
 * @return None.
 */
XTEST_API void xmock_motor_stop(XMockMotor *motor);

/**
 * @brief Initializes an XMockActuator instance.
 *
 * This function sets the actuator's ID and initializes its state to OFF (0).
 *
 * @param actuator Pointer to the XMockActuator instance to initialize.
 * @param id       The actuator's unique identifier.
 *
 * @return None.
 */
XTEST_API void xmock_actuator_init(XMockActuator *actuator, uint8_t id);

/**
 * @brief Turns on an XMockActuator.
 *
 * This function sets the state of the actuator to ON (1).
 *
 * @param actuator Pointer to the XMockActuator instance to turn on.
 *
 * @return None.
 */
XTEST_API void xmock_actuator_turn_on(XMockActuator *actuator);

/**
 * @brief Turns off an XMockActuator.
 *
 * This function sets the state of the actuator to OFF (0).
 *
 * @param actuator Pointer to the XMockActuator instance to turn off.
 *
 * @return None.
 */
XTEST_API void xmock_actuator_turn_off(XMockActuator *actuator);

/**
 * @brief Gets the current state of an XMockActuator.
 *
 * @param actuator Pointer to the XMockActuator instance to get the state from.
 *
 * @return The current state of the actuator (0 for OFF, 1 for ON).
 */
XTEST_API int xmock_actuator_get_state(XMockActuator *actuator);

/**
 * @brief Mock Peripheral Emulation Structures
 *
 * These structures represent a range of mock peripheral types commonly found in microcontroller-based
 * systems. They are designed for use in simulated environments to mimic the behavior and configuration
 * of real hardware peripherals, enabling developers to test and prototype software without the need
 * for physical hardware. These mock peripheral types include UART, I2S, CAN, Bluetooth, Modbus, SPI,
 * and I2C, each with its own set of attributes to model specific functionality.
 *
 * XMockUART:
 *   - Represents a simulated UART (Universal Asynchronous Receiver-Transmitter) peripheral.
 *   - Includes attributes such as UART ID, baud rate, data bits, stop bits, and parity settings.
 *
 * XMockI2S:
 *   - Represents a simulated I2S (Inter-IC Sound) peripheral.
 *   - Contains attributes like I2S ID, sample rate, data format, and channel mode settings.
 *
 * XMockCAN:
 *   - Represents a simulated CAN (Controller Area Network) peripheral.
 *   - Includes attributes such as CAN ID and bitrate settings.
 *
 * XMockBluetooth:
 *   - Represents a simulated Bluetooth peripheral.
 *   - Contains attributes like Bluetooth ID to emulate Bluetooth device interactions.
 *
 * XMockModbus:
 *   - Represents a simulated Modbus peripheral.
 *   - Includes attributes such as Modbus ID and baud rate for Modbus communication.
 *
 * XMockSPI:
 *   - Represents a simulated SPI (Serial Peripheral Interface) peripheral.
 *   - Contains attributes like SPI ID, SPI mode, clock speed, data order, chip select,
 *     data bits, and duplex mode settings.
 *
 * XMockI2C:
 *   - Represents a simulated I2C (Inter-Integrated Circuit) peripheral.
 *   - Includes attributes like I2C ID, I2C speed, device address, transfer direction,
 *     repeated start condition, and acknowledge settings.
 *
 * These structures are intended for use in software testing, debugging, and simulation scenarios,
 * allowing developers to model and simulate interactions with a wide range of microcontroller
 * peripherals. By customizing and extending these structures, developers can create versatile
 * mock peripherals that closely resemble real hardware components in their virtual environments.
 *
 * Usage:
 *   - Initialize these structures using the provided initialization functions.
 *   - Configure and interact with the mock peripherals using their respective attributes.
 *   - Customize these structures to match specific peripheral behaviors in your simulated
 *     microcontroller environment.
 *
 * Note: These mock structures are not intended for use in production code and are solely
 * designed for testing and simulation purposes.
 */

// Mock UART Peripheral Structure
typedef struct {
    uint8_t uart_id;
    uint32_t baud_rate; // Baud rate in bits per second
    uint8_t data_bits;  // Number of data bits (e.g., 8 bits)
    uint8_t stop_bits;  // Number of stop bits (e.g., 1 stop bit)
    uint8_t parity;     // Parity setting (e.g., none, even, odd)
} XMockUART;

// Mock I2S Peripheral Structure
typedef struct {
    uint8_t i2s_id;
    uint32_t sample_rate; // Sample rate in Hz
    uint8_t data_format;  // Data format (e.g., I2S, PCM)
    uint8_t channel_mode; // Channel mode (e.g., stereo, mono)
} XMockI2S;

// Mock CAN Peripheral Structure
typedef struct {
    uint8_t can_id;
    uint32_t bitrate; // Bitrate in bits per second
} XMockCAN;

// Mock Bluetooth Peripheral Structure
typedef struct {
    uint8_t bluetooth_id;
} XMockBluetooth;

// Mock Modbus Peripheral Structure
typedef struct {
    uint8_t modbus_id;
    uint32_t baud_rate; // Baud rate in bits per second
} XMockModbus;

// Mock SPI Peripheral Structure
typedef struct {
    uint8_t spi_id;
    uint8_t spi_mode;       // SPI mode (0, 1, 2, or 3)
    uint32_t clock_speed;   // Clock speed in Hz
    uint8_t data_order;     // Data order (MSB first or LSB first)
    uint8_t chip_select;    // Chip select state (0 or 1)
    uint8_t data_bits;      // Number of data bits (e.g., 8 bits)
    uint8_t duplex_mode;    // Duplex mode (full or half)
} XMockSPI;

// Mock I2C Peripheral Structure
typedef struct {
    uint8_t i2c_id;
    uint32_t i2c_speed;      // I2C speed or frequency
    uint8_t device_address;  // I2C device address
    uint8_t transfer_dir;    // Transfer direction (read or write)
    uint8_t repeated_start;  // Repeated start condition (0 or 1)
    uint8_t acknowledge;     // Acknowledge setting (0 or 1)
} XMockI2C;

// Initialization function for mock peripheral
void xmock_uart_init(XMockUART *uart, uint8_t id, uint32_t baud_rate, uint8_t data_bits, uint8_t stop_bits, uint8_t parity);
void xmock_i2s_init(XMockI2S *i2s, uint8_t id, uint32_t sample_rate, uint8_t data_format, uint8_t channel_mode);
void xmock_can_init(XMockCAN *can, uint8_t id, uint32_t bitrate);
void xmock_bluetooth_init(XMockBluetooth *bluetooth, uint8_t id);
void xmock_modbus_init(XMockModbus *modbus, uint8_t id, uint32_t baud_rate);
void xmock_i2c_init(XMockI2C *i2c, uint8_t id, uint32_t speed, uint8_t address, uint8_t dir, uint8_t start, uint8_t ack);
void xmock_spi_init(XMockSPI *spi, uint8_t id, uint8_t mode, uint32_t speed, uint8_t order, uint8_t cs, uint8_t bits, uint8_t duplex);

// Transmit function for mock peripheral
void xmock_uart_transmit(XMockUART *uart, uint8_t *tx_buffer, uint32_t length);
void xmock_i2s_transmit(XMockI2S *i2s, uint8_t *tx_buffer, uint32_t length);
void xmock_can_transmit(XMockCAN *can, uint8_t *tx_buffer, uint32_t length);
void xmock_bluetooth_transmit(XMockBluetooth *bluetooth, uint8_t *tx_buffer, uint32_t length);
void xmock_modbus_transmit(XMockModbus *modbus, uint8_t *tx_buffer, uint32_t length);
void xmock_i2c_write(XMockI2C *i2c, uint8_t device_address, uint8_t *data, uint32_t length);
void xmock_spi_transfer(XMockSPI *spi, uint8_t *tx_buffer, uint8_t *rx_buffer, uint32_t length);

// Receive function for mock peripheral
void xmock_uart_receive(XMockUART *uart, uint8_t *rx_buffer, uint32_t length);
void xmock_can_receive(XMockCAN *can, uint8_t *rx_buffer, uint32_t length);
void xmock_bluetooth_receive(XMockBluetooth *bluetooth, uint8_t *rx_buffer, uint32_t length);
void xmock_modbus_receive(XMockModbus *modbus, uint8_t *rx_buffer, uint32_t length);
void xmock_i2c_read(XMockI2C *i2c, uint8_t device_address, uint8_t *data, uint32_t length);

/**
 * @brief Mock Microcontroller Emulation Structures
 *
 * These structures, namely XMockStMicroGPIO, XMockArduinoUnoGPIO, and XMockRaspberryPiGPIO,
 * are designed to emulate the behavior of microcontroller GPIO (General-Purpose Input/Output)
 * ports in a simulated environment. They serve as placeholders for representing GPIO ports
 * with their associated registers and allow developers to create, configure, and interact
 * with these virtual GPIO ports for testing and simulation purposes.
 *
 * XMockStMicroGPIO:
 *   - Represents a simulated GPIO port for STMicroelectronics microcontrollers.
 *   - Contains registers such as MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, and AFR.
 *
 * XMockArduinoUnoGPIO:
 *   - Represents a simulated GPIO port for Arduino Uno microcontroller.
 *   - Contains DDRB, PORTB, and PINB registers to simulate port behavior.
 *
 * XMockRaspberryPiGPIO:
 *   - Represents a simulated GPIO port for Raspberry Pi microcontroller.
 *   - Contains GPFSEL, GPSET, GPCLR, GPLEV, and GPEDS registers for GPIO control.
 *
 * These structures are intended for use in software testing, debugging, and simulation
 * scenarios, allowing developers to model and simulate interactions with microcontroller
 * GPIO ports without the need for actual hardware. They can be customized and extended
 * to simulate various GPIO-related behaviors and are particularly useful in scenarios
 * where real microcontrollers or development boards are unavailable or costly to access.
 *
 * Usage:
 *   - Initialize these structures using the provided initialization functions.
 *   - Interact with the GPIO ports by setting or reading their registers.
 *   - Customize and extend these structures and functions to model specific GPIO behaviors
 *     in your simulated microcontroller environment.
 *
 * Note: These mock structures are not intended for use in production code and are solely
 * designed for testing and simulation purposes.
 */

typedef struct {
    volatile uint32_t GPFSEL[6];   // Function Select Registers 0-5
    volatile uint32_t Reserved0;
    volatile uint32_t GPSET[2];    // Pin Output Set Registers 0-1
    volatile uint32_t Reserved1;
    volatile uint32_t GPCLR[2];    // Pin Output Clear Registers 0-1
    volatile uint32_t Reserved2;
    volatile uint32_t GPLEV[2];    // Pin Level Registers 0-1
} XMockRaspberryPiGPIO;

#define XMOCK_GPIO_PI3 ((XMockRaspberryPiGPIO *)0x3F200000)
#define XMOCK_GPIO_PI4 ((XMockRaspberryPiGPIO *)0xFE200000)
#define XMOCK_GPIO_ZERO ((XMockRaspberryPiGPIO *)0x3F200000)

typedef struct {
    volatile uint32_t MODER;    // Mode register
    volatile uint32_t OTYPER;   // Output type register
    volatile uint32_t OSPEEDR;  // Output speed register
    volatile uint32_t PUPDR;    // Pull-up/pull-down register
    volatile uint32_t IDR;      // Input data register
    volatile uint32_t ODR;      // Output data register
    volatile uint32_t BSRR;     // Bit set/reset register
} XMockStMicroGPIO;

#define XMOCK_GPIOA_DISCOVERY ((XMockStMicroGPIO *)0x40020000U)
#define XMOCK_GPIOB_DISCOVERY ((XMockStMicroGPIO *)0x40020400U)

typedef struct {
    volatile uint8_t PINB; // Input Pins Register B
    volatile uint8_t DDRB; // Data Direction Register B
    volatile uint8_t PORTB; // Port B Data Register

    volatile uint8_t PINC; // Input Pins Register C
    volatile uint8_t DDRC; // Data Direction Register C
    volatile uint8_t PORTC; // Port C Data Register

    volatile uint8_t PIND; // Input Pins Register D
    volatile uint8_t DDRD; // Data Direction Register D
    volatile uint8_t PORTD; // Port D Data Register
} XMockArduinoUnoGPIO;

#define XMOCK_GPIO_UNO_PORTB ((XMockArduinoUnoGPIO *)0x25)
#define XMOCK_GPIO_UNO_PORTC ((XMockArduinoUnoGPIO *)0x28)
#define XMOCK_GPIO_UNO_PORTD ((XMockArduinoUnoGPIO *)0x2B)

/**
 * @brief Initializes a GPIO pin as an output.
 *
 * This function sets the MODER (mode register) bits of the given GPIO pin to
 * configure it as a digital output pin.
 *
 * @param gpio Pointer to the mock GPIO structure representing the GPIO port.
 * @param pin  The pin number to be initialized as an output (0-15).
 *
 * @return None.
 */

XTEST_API void xmock_stm32_gpio_init_output(XMockStMicroGPIO *gpio, uint32_t pin);
XTEST_API void xmock_raspi_gpio_init_output(XMockRaspberryPiGPIO *gpio, uint32_t pin);
XTEST_API void xmock_arduino_uno_gpio_init_output(XMockArduinoUnoGPIO *gpio, uint8_t pin);

/**
 * @brief Sets the state (high or low) of a GPIO pin.
 *
 * This function sets the state of the given GPIO pin by manipulating the BSRR
 * (Bit Set/Reset Register) bits.
 *
 * @param gpio   Pointer to the mock GPIO structure representing the GPIO port.
 * @param pin    The pin number whose state is to be set (0-15).
 * @param state  The desired state for the pin (0 for low, non-zero for high).
 *
 * @return None.
 */

XTEST_API void xmock_stm32_gpio_set_state(XMockStMicroGPIO *gpio, uint32_t pin, uint32_t state);
XTEST_API void xmock_raspi_gpio_set_state(XMockRaspberryPiGPIO *gpio, uint32_t pin, uint32_t state);
XTEST_API void xmock_arduino_uno_gpio_set_state(XMockArduinoUnoGPIO *gpio, uint8_t pin, uint8_t state);

/**
 * @brief Reads the state (high or low) of a GPIO pin.
 *
 * This function reads the state of the given GPIO pin by shifting the IDR
 * (Input Data Register) bits and masking the result to obtain the state.
 *
 * @param gpio Pointer to the mock GPIO structure representing the GPIO port.
 * @param pin  The pin number whose state is to be read (0-15).
 *
 * @return The state of the pin (0 for low, 1 for high).
 */

XTEST_API uint32_t xmock_stm32_gpio_read_state(XMockStMicroGPIO *gpio, uint32_t pin);
XTEST_API uint32_t xmock_raspi_gpio_read_state(XMockRaspberryPiGPIO *gpio, uint32_t pin);
XTEST_API uint8_t xmock_arduino_uno_gpio_read_state(XMockArduinoUnoGPIO *gpio, uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif
