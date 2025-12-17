# Jorne ZMK Keyboard Configuration

Custom ZMK firmware configuration for the Jorne split keyboard with rotary encoder support.

## Features

- Split keyboard (left/right halves via Bluetooth)
- Rotary encoder with smooth mouse scrolling
- Nice!Nano v2 compatible
- 4 layers keymap

## Hardware

- **MCU**: Nice!Nano v2 (nRF52840)
- **Encoder**: EC11 rotary encoder (left side)
- **Layout**: 6x4 split with 3 thumb keys per side

## Encoder Configuration

### Hardware Setup (`jorne.dtsi`)

```dts
encoder_left: encoder_left {
    compatible = "alps,ec11";
    a-gpios = <&pro_micro 3 (GPIO_ACTIVE_LOW | GPIO_PULL_UP)>;
    b-gpios = <&pro_micro 2 (GPIO_ACTIVE_LOW | GPIO_PULL_UP)>;
    steps = <80>;
    status = "disabled";
};
```

| Setting | Value | Description |
|---------|-------|-------------|
| `a-gpios` | Pro Micro pin 3 | Encoder A signal |
| `b-gpios` | Pro Micro pin 2 | Encoder B signal |
| `steps` | 80 | Pulses per rotation |
| `GPIO_ACTIVE_LOW` | - | Signal polarity |

### Enable Encoder (`jorne_left.overlay`)

```dts
&encoder_left {
    status = "okay";
};
```

### Kconfig Settings (`jorne.conf`)

```ini
# Encoder driver
CONFIG_EC11=y
CONFIG_EC11_TRIGGER_GLOBAL_THREAD=y

# Pointing/Mouse support
CONFIG_ZMK_POINTING=y
CONFIG_ZMK_POINTING_SMOOTH_SCROLLING=y
```

## Scroll Configuration

### Scroll Speed & Sensitivity (`jorne.keymap`)

```dts
#define ZMK_POINTING_DEFAULT_MOVE_VAL 1200   // Mouse movement speed
#define ZMK_POINTING_DEFAULT_SCRL_VAL 900    // Scroll velocity per tick
```

### Input Processors (Scaling)

```dts
&msc_input_listener { 
    input-processors = <&zip_scroll_scaler 4 1>;  // 4x multiplier
};
```

| Scaler Value | Effect |
|--------------|--------|
| `2 1` | 2x multiplier (default) |
| `4 1` | 4x multiplier (more responsive) |
| `8 1` | 8x multiplier (very responsive) |

### Scroll Behavior Tuning

```dts
&msc {
    acceleration-exponent = <0>;    // 0 = uniform speed, 1 = acceleration curve
    time-to-max-speed-ms = <40>;    // Time to reach max speed (lower = faster)
    delay-ms = <0>;                 // Delay before scroll starts
};
```

| Setting | Value | Description |
|---------|-------|-------------|
| `acceleration-exponent` | `<0>` | Uniform speed - consistent scroll per tick |
| `acceleration-exponent` | `<1>` | Acceleration curve - slow start, speeds up |
| `time-to-max-speed-ms` | `<40>` | Faster acceleration (default: 300) |

### Scroll Behavior Definition

```dts
Scroll_Down_Up: Scroll_Down_Up {
    compatible = "zmk,behavior-sensor-rotate";
    #sensor-binding-cells = <0>;
    bindings = <&msc SCRL_DOWN>, <&msc SCRL_UP>;
    tap-ms = <20>;
};
```

### Usage in Keymap

```dts
sensor-bindings = <&Scroll_Down_Up>;
```

## Tuning Guide

### Scroll Not Responsive Enough?

1. **Increase scaler multiplier**:
   ```dts
   &msc_input_listener { input-processors = <&zip_scroll_scaler 8 1>; };
   ```

2. **Increase scroll velocity**:
   ```dts
   #define ZMK_POINTING_DEFAULT_SCRL_VAL 1500
   ```

3. **Use uniform speed** (no acceleration):
   ```dts
   &msc { acceleration-exponent = <0>; };
   ```

### Scroll Too Fast?

1. **Decrease scaler multiplier**:
   ```dts
   &msc_input_listener { input-processors = <&zip_scroll_scaler 2 1>; };
   ```

2. **Decrease scroll velocity**:
   ```dts
   #define ZMK_POINTING_DEFAULT_SCRL_VAL 400
   ```

## Pin Mapping Reference

| Function | Pro Micro Pin | Nice!Nano GPIO |
|----------|---------------|----------------|
| Encoder A | 3 | P0.22 |
| Encoder B | 2 | P0.02 |

## Building

Firmware is built automatically via GitHub Actions. Push changes to trigger a build.

## References

- [ZMK Pointing Configuration](https://zmk.dev/docs/config/pointing)
- [ZMK Mouse Emulation](https://zmk.dev/docs/keymaps/behaviors/mouse-emulation)
- [ZMK Encoder Integration](https://zmk.dev/docs/development/hardware-integration/encoders)
- Inspired by [Michila's CorneV4](https://github.com/Haha1609/Michila)

