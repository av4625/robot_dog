# Gamepad

## PS4Controller Library

This library wouldn't build, I had to make the following changes to make it
build (below change no longer required with the change below it required):

In `ps4_int.h` change:

```
#define CONFIG_IDF_COMPATIBILITY IDF_COMPATIBILITY_MASTER_21165ED
```
To:
```
#define CONFIG_IDF_COMPATIBILITY IDF_COMPATIBILITY_MASTER_21AF1D7
```

Fix the above bug with the following:

In `ps4_spp.c` change:

```
#if CONFIG_IDF_COMPATIBILITY >= IDF_COMPATIBILITY_MASTER_D9CE0BB
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_NON_DISCOVERABLE);
#elif CONFIG_IDF_COMPATIBILITY >= IDF_COMPATIBILITY_MASTER_21AF1D7
    esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE);
#endif
```
To:
```
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 0, 0)
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_NON_DISCOVERABLE);
#else
    esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE);
#endif
```

Bug is described [here](https://github.com/aed3/PS4-esp32/pull/42).
The PS4 library is a port of the PS3 library and the PS3 library fixed this
issue by doing the above, not yet brought across to the PS$ library.
[PS3 Library](https://github.com/jvpernis/esp32-ps3/commit/dbcea43a8a246fef6e07b613eee0ea6973c71963#diff-bf97464f9295f9fbbe47a511b4123edc2404ef903e3ef6e4ed79d27dff6640e5)


There is also a bug in library around the events, I created a
[pull request](https://github.com/aed3/PS4-esp32/pull/43) to fix the issue.

## Controller Values
* Stick left: -128
* Stick right: 127
* Stick up: 127
* Stick down: -128
