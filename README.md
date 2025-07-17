Selecting the correct design pattern in software engineering is crucial for effective problem-solving. This guide streamlines the process, enabling you to make informed decisions between patterns based on your specific needs. 

It provides concise descriptions and valuable use cases for each pattern, making it easier to understand and apply them in real-world scenarios. 

To select a pattern, we must first go through the problem identification. If the problem is related to: 
### 🔸 Object creation? → Creational patterns
### 🔸 Object assembly? → Structural patterns
### 🔸 Object interactions? → Behavioral patterns

So, let's dive in.

### 𝟭. 𝗖𝗿𝗲𝗮𝘁𝗶𝗼𝗻𝗮𝗹 𝗣𝗮𝘁𝘁𝗲𝗿𝗻𝘀
 🔹 **Singleton:** Use when a single instance of a class is needed. Some examples are logging and database connections. 
 
 🔹 **Factory Method:** Decouple object creation from usage. For example, you create different types of database connections based on configuration.
 
 🔹 **Abstract Factory:** Create families of related objects. For example, I build parsers for different file formats.
 
 🔹 **Builder:** Constructing complex objects step by step. For example, if you need to create a complex domain object.
 
 🔹 **Prototype:** Creating duplicate objects and reusing cached objects to reduce database calls.

### 𝟮. 𝗦𝘁𝗿𝘂𝗰𝘁𝘂𝗿𝗮𝗹 𝗣𝗮𝘁𝘁𝗲𝗿𝗻𝘀
 🔹 **Adapter:** Make incompatible interfaces compatible. For example, it integrates a new logging library into an existing system that expects a different interface.
 
 🔹 **Composite:** Represent part-whole hierarchies. For example, graphic objects in a drawing application can be grouped and treated uniformly
 
 🔹 **Proxy:** Control access to objects. For example, lazy loading of a high-resolution image in a web application.
 
 🔹 **Decorator:** Dynamically add/remove behavior. For example, we are implementing compression or encryption on top of file streams.
 
 🔹 **Bridge:** Decouple abstraction from implementation. For example, I am separating platform-specific code from core logic.

### 𝟯. 𝗕𝗲𝗵𝗮𝘃𝗶𝗼𝗿𝗮𝗹 𝗣𝗮𝘁𝘁𝗲𝗿𝗻𝘀
 🔹 **Strategy:** Define a family of algorithms. These algorithms enable users to select from various sorting or compression algorithms.
 
 🔹 **Observer:** Maintain a consistent state by being notified of changes and, for example, notifying subscribers of events in a messaging system.
 
 🔹 **Command:** Encapsulate a request as an object. For example, I implement undo/redo functionality in a text or image editor.
 
 🔹 **State:** Encapsulate state-specific behavior. For example, we are handling different states of a user interface element (e.g., enabled, disabled, selected).
 
 🔹 **Template Method:** Define the skeleton of an algorithm in operation, deferring some steps to subclasses and implementing a base class for unit testing with customizable setup and teardown steps.

## 🧱 1. Creational Patterns

### [1.1] Factory Design Pattern  
**Purpose:** Creates objects without specifying the exact class/type.

**Real-Life Analogy:**  
You go to a **vehicle factory** and say you want a "Bike" or "Car". You don’t care how it’s made, just that it returns the appropriate vehicle.

**C Example:**
```c
#include <stdio.h>
#include <string.h>

typedef struct {
    void (*start)(void);
} Vehicle;

void startCar() { printf("Car started\n"); }
void startBike() { printf("Bike started\n"); }

Vehicle* createVehicle(const char* type) {
    static Vehicle car = { .start = startCar };
    static Vehicle bike = { .start = startBike };

    if (strcmp(type, "Car") == 0) return &car;
    if (strcmp(type, "Bike") == 0) return &bike;
    return NULL;
}
```

---

### [1.2] Singleton Pattern  
**Purpose:** Ensures a class has only one instance.

**Real-Life Analogy:**  
There should be only **one President** in a country. You don’t create a new one each time you need a leader.

**C Example:**
```c
#include <stdio.h>

typedef struct {
    int data;
} President;

President* getPresidentInstance() {
    static President instance = {0}; // initialized once
    return &instance;
}
```

---

## 🧩 2. Structural Patterns

### [2.1] Adapter Pattern  
**Purpose:** Allows classes with incompatible interfaces to work together.

**Real-Life Analogy:**  
Your laptop has a USB-C port, but your pen drive is USB-A. You use an **adapter**.

**C Example:**
```c
#include <stdio.h>

void usbA() {
    printf("Using USB-A device\n");
}

typedef struct {
    void (*connect)(void);
} UsbC;

void adapterConnect() {
    usbA(); // adapts usbA to USB-C
}

UsbC getAdapter() {
    UsbC usbC = { .connect = adapterConnect };
    return usbC;
}
```

---

### [2.2] Facade Pattern  
**Purpose:** Hides complex subsystems behind a simpler interface.

**Real-Life Analogy:**  
You press one button on a **remote**, but internally it handles turning on TV, speakers, and set-top box.

**C Example:**
```c
#include <stdio.h>

void turnOnTV() { printf("TV ON\n"); }
void turnOnSoundSystem() { printf("Sound System ON\n"); }

void pressPowerButton() {
    turnOnTV();
    turnOnSoundSystem();
}
```

---

### [2.3] Proxy Pattern  
**Purpose:** Controls access to another object (with logging, permission, etc.)

**Real-Life Analogy:**  
A **secretary** (proxy) controls access to a **boss**.

**C Example:**
```c
#include <stdio.h>

void realAccess() {
    printf("Accessing confidential data\n");
}

void proxyAccess(int hasPermission) {
    if (hasPermission)
        realAccess();
    else
        printf("Access Denied\n");
}
```

---

## 🔁 3. Behavioral Patterns

### [3.1] Observer Pattern  
**Purpose:** Notifies subscribers when the subject changes.

**Real-Life Analogy:**  
You **subscribe to a YouTube channel**, and you get notified when a new video is uploaded.

**C Example:**
```c
#include <stdio.h>

typedef void (*Observer)();

void observer1() { printf("Observer 1 notified\n"); }
void observer2() { printf("Observer 2 notified\n"); }

void notifyAll(Observer observers[], int count) {
    for (int i = 0; i < count; i++)
        observers[i]();
}
```

---

### [3.2] Strategy Pattern  
**Purpose:** Allows changing the algorithm at runtime.

**Real-Life Analogy:**  
You can pay by **Cash, UPI, or Card** — strategy changes but the goal is same: Pay.

**C Example:**  
```c
#include <stdio.h>

// Define strategy type
typedef void (*PayStrategy)();

// Strategies
void payCash()  { printf("Paid by Cash\n"); }
void payUPI()   { printf("Paid by UPI\n"); }
void payCard()  { printf("Paid by Card\n"); }

// Context
void makePayment(PayStrategy strategy) {
    strategy();  // Call selected strategy
}

// Main
int main() {
    makePayment(payCash);   // Output: Paid by Cash
    makePayment(payUPI);    // Output: Paid by UPI
    makePayment(payCard);   // Output: Paid by Card
    return 0;
}
```

---

### [3.3] State Pattern  
**Purpose:** Allows object to change behavior based on internal state.

**Real-Life Analogy:**  
A **traffic light** changes its behavior (red/yellow/green) based on current state.

**C Example:**
```c
#include <stdio.h>

typedef void (*StateFunction)();

void redLight() { printf("Stop!\n"); }
void greenLight() { printf("Go!\n"); }

typedef struct {
    StateFunction currentState;
} TrafficLight;

void changeState(TrafficLight* light, StateFunction newState) {
    light->currentState = newState;
}

void operate(TrafficLight* light) {
    light->currentState();
}

```

### ✅ Design Patterns Overview
**🧱Creational Patterns**
1.Factory – Used to create different smart devices.
2.Singleton – Ensures only one instance of the SmartHomeController.

**🧠Behavioral Patterns**
**1.Adapter – Adapts legacy devices to the smart interface.**
2.Facade – Provides a simplified interface to control all devices.
3.Proxy – Acts as a proxy between the user and actual device (e.g., for logging or access control).

**🏗️Structural Patterns**
1.Observer – Notifies devices of events (e.g., power cut).
2.Strategy – Switch device operation modes (eco, turbo, etc.).
3.State – Track and change device state (on, off, standby).
