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

