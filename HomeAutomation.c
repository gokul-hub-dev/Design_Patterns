#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========== Singleton Pattern ==========
typedef struct {
    char name[20];
} SmartHomeController;

SmartHomeController* get_controller_instance() {
    static SmartHomeController instance = {"MainController"};
    return &instance;
}

// ========== Factory Pattern ==========
typedef struct SmartDevice {
    char type[20];
    void (*turn_on)(struct SmartDevice*);
    void (*turn_off)(struct SmartDevice*);
} SmartDevice;

void light_on(SmartDevice* d) { printf("%s Light ON\n", d->type); }
void light_off(SmartDevice* d) { printf("%s Light OFF\n", d->type); }

SmartDevice* create_device(const char* type) {
    SmartDevice* device = (SmartDevice*)malloc(sizeof(SmartDevice));
    strcpy(device->type, type);
    device->turn_on = light_on;
    device->turn_off = light_off;
    return device;
}

// ========== Adapter Pattern ==========
typedef struct {
    void (*old_switch_on)();
    void (*old_switch_off)();
} LegacyDevice;

void legacy_on() { printf("Legacy device is ON (manual switch)\n"); }
void legacy_off() { printf("Legacy device is OFF (manual switch)\n"); }

typedef struct {
    SmartDevice base;
    LegacyDevice* legacy;
} LegacyAdapter;

void adapter_on(SmartDevice* d) {
    LegacyAdapter* a = (LegacyAdapter*)d;
    a->legacy->old_switch_on();
}
void adapter_off(SmartDevice* d) {
    LegacyAdapter* a = (LegacyAdapter*)d;
    a->legacy->old_switch_off();
}

SmartDevice* create_legacy_adapter() {
    LegacyAdapter* adapter = (LegacyAdapter*)malloc(sizeof(LegacyAdapter));
    adapter->legacy = (LegacyDevice*)malloc(sizeof(LegacyDevice));
    adapter->legacy->old_switch_on = legacy_on;
    adapter->legacy->old_switch_off = legacy_off;
    strcpy(adapter->base.type, "Legacy");
    adapter->base.turn_on = adapter_on;
    adapter->base.turn_off = adapter_off;
    return (SmartDevice*)adapter;
}

// ========== Proxy Pattern ==========
typedef struct {
    SmartDevice* real_device;
} DeviceProxy;

void proxy_on(SmartDevice* d) {
    DeviceProxy* proxy = (DeviceProxy*)d;
    printf("[LOG] Proxy turning ON %s\n", proxy->real_device->type);
    proxy->real_device->turn_on(proxy->real_device);
}
void proxy_off(SmartDevice* d) {
    DeviceProxy* proxy = (DeviceProxy*)d;
    printf("[LOG] Proxy turning OFF %s\n", proxy->real_device->type);
    proxy->real_device->turn_off(proxy->real_device);
}

SmartDevice* create_proxy(SmartDevice* real) {
    DeviceProxy* proxy = (DeviceProxy*)malloc(sizeof(DeviceProxy));
    proxy->real_device = real;
    SmartDevice* d = (SmartDevice*)proxy;
    strcpy(d->type, "ProxyDevice");
    d->turn_on = proxy_on;
    d->turn_off = proxy_off;
    return d;
}

// ========== Facade Pattern ==========
typedef struct {
    SmartDevice* light;
    SmartDevice* fan;
} HomeFacade;

void facade_all_on(HomeFacade* h) {
    h->light->turn_on(h->light);
    h->fan->turn_on(h->fan);
}
void facade_all_off(HomeFacade* h) {
    h->light->turn_off(h->light);
    h->fan->turn_off(h->fan);
}

// ========== Observer Pattern ==========
#define MAX_OBSERVERS 5
typedef void (*EventHandler)();

EventHandler observers[MAX_OBSERVERS];
int observer_count = 0;

void add_observer(EventHandler h) {
    if (observer_count < MAX_OBSERVERS)
        observers[observer_count++] = h;
}

void notify_observers() {
    for (int i = 0; i < observer_count; ++i)
        observers[i]();
}

void emergency_shutdown() {
    printf("[OBSERVER] Emergency shutdown triggered!\n");
}

// ========== Strategy Pattern ==========
typedef void (*ModeStrategy)();

void eco_mode() { printf("Device running in ECO mode\n"); }
void turbo_mode() { printf("Device running in TURBO mode\n"); }

void run_strategy(ModeStrategy mode) {
    mode();
}

// ========== State Pattern ==========
typedef enum { OFF, ON, STANDBY } DeviceState;

typedef struct {
    DeviceState state;
} StatefulDevice;

void print_state(StatefulDevice* d) {
    switch (d->state) {
        case ON: printf("Device is ON\n"); break;
        case OFF: printf("Device is OFF\n"); break;
        case STANDBY: printf("Device is in STANDBY\n"); break;
    }
}

// ========== Main Demo ==========
int main() {
    // Singleton
    SmartHomeController* controller = get_controller_instance();
    printf("Controller: %s\n", controller->name);

    // Factory
    SmartDevice* light = create_device("LivingRoom");
    SmartDevice* fan = create_device("Bedroom");

    // Adapter
    SmartDevice* legacy = create_legacy_adapter();

    // Proxy
    SmartDevice* proxied_light = create_proxy(light);

    // Facade
    HomeFacade home = { proxied_light, fan };

    // Observer
    add_observer(emergency_shutdown);
    notify_observers();

    // Strategy
    run_strategy(eco_mode);
    run_strategy(turbo_mode);

    // State
    StatefulDevice dev = { ON };
    print_state(&dev);
    dev.state = STANDBY;
    print_state(&dev);

    // Facade usage
    facade_all_on(&home);
    facade_all_off(&home);

    // Adapter usage
    legacy->turn_on(legacy);
    legacy->turn_off(legacy);

    return 0;
}