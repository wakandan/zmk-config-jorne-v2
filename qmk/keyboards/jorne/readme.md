# Jorne Keyboard - QMK Firmware

A split ergonomic keyboard with 46 keys (6×3 + 3 thumb keys per side, plus an extra column) based on the Corne/CRKBD layout.

## Features

- Split keyboard (serial communication)
- Pro Micro compatible (ATmega32U4)
- Rotary encoder support (one per side)
- 4 layers: Base (QWERTY), Navigation, Numbers, Symbols

## Hardware

- **MCU**: ATmega32U4 (Pro Micro)
- **Matrix**: 4 rows × 7 columns per half
- **Diode Direction**: COL2ROW
- **Communication**: Half-duplex serial on pin D2

### Pin Configuration

| Function | Left Half | Right Half |
|----------|-----------|------------|
| Rows     | D4, C6, D7, E6 | D4, C6, D7, E6 |
| Columns  | F4, F5, F6, F7, B1, B3, B2 | F4, F5, F6, F7, B1, B3, B4 |
| Serial   | D2 | D2 |
| Encoder A | B5 | B5 |
| Encoder B | B6 | B6 |

## Building

### Prerequisites

1. Install QMK: `brew install qmk/qmk/qmk` (or see https://docs.qmk.fm/newbs_getting_started)
2. Run `qmk setup` to clone the QMK firmware repository
3. Ensure toolchains are in PATH:
   ```bash
   export PATH="/opt/homebrew/opt/avr-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:/opt/homebrew/opt/avr-binutils/bin:$PATH"
   ```

### Build Steps

```bash
# 1. Copy this keyboard folder to qmk_firmware/keyboards/
cp -r qmk/keyboards/jorne ~/qmk_firmware/keyboards/jorne_custom

# 2. Build firmware
qmk compile -kb jorne_custom -km default

# 3. Flash left half (enter bootloader first - short RST to GND twice)
qmk flash -kb jorne_custom -km default -bl avrdude-split-left

# 4. Flash right half
qmk flash -kb jorne_custom -km default -bl avrdude-split-right
```

## Flashing

1. Connect the **left** half via USB
2. Short RST and GND twice quickly to enter bootloader (LED will pulse)
3. Run flash command within 8 seconds
4. Repeat for **right** half

## Layers

### Layer 0: Base (QWERTY)
```
┌──────┬──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┬──────┐
│ Tab  │  Q   │  W   │  E   │  R   │  T   │                    │  Y   │  U   │  I   │  O   │  P   │  [   │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│ Esc  │ Ctrl │  A   │  S   │  D   │ F/L1 │  G   │      │  H   │ J/L2 │  K   │  L   │  ;   │  '   │Enter │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤      ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│ Esc  │Shift │  Z   │  X   │  C   │  V   │  B   │      │  N   │  M   │  ,   │  .   │  /   │Shift │  ↑   │
└──────┴──────┴──────┴──────┼──────┼──────┼──────┤      ├──────┼──────┼──────┼──────┴──────┴──────┴──────┘
                            │MO(3) │ Alt  │ GUI  │      │Space │ Bksp │MO(3) │
                            └──────┴──────┴──────┘      └──────┴──────┴──────┘
```
- **F/L1**: Tap for F, Hold for Layer 1 (Navigation)
- **J/L2**: Tap for J, Hold for Layer 2 (Numbers)
- **MO(3)**: Hold for Layer 3 (Symbols)

### Layer 1: Navigation
```
┌──────┬──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┬──────┐
│      │      │      │      │      │      │                    │ Home │ PgUp │ PgDn │ End  │  -   │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │ HELD │      │      │Cmd+[ │⇧⌘+[  │⇧⌘+]  │Cmd+] │  =   │  _   │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤      ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │      │      │  ←   │  ↓   │  ↑   │  →   │      │      │      │
└──────┴──────┴──────┴──────┼──────┼──────┼──────┤      ├──────┼──────┼──────┼──────┴──────┴──────┴──────┘
                            │      │      │      │      │      │      │      │
                            └──────┴──────┴──────┘      └──────┴──────┴──────┘
```

### Layer 2: Numbers & Symbols
```
┌──────┬──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┬──────┐
│      │  1   │  2   │  3   │  4   │  5   │                    │  6   │  7   │  8   │  9   │  0   │  -   │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │  6   │  7   │  8   │  9   │  0   │      │  ^   │ HELD │  *   │  (   │  )   │  _   │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤      ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │      │      │      │      │      │      │      │      │      │
└──────┴──────┴──────┴──────┼──────┼──────┼──────┤      ├──────┼──────┼──────┼──────┴──────┴──────┴──────┘
                            │      │      │      │      │      │      │      │
                            └──────┴──────┴──────┘      └──────┴──────┴──────┘
```

### Layer 3: Symbols
```
┌──────┬──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┬──────┐
│Cmd+` │  !   │  @   │  #   │  $   │  %   │                    │  ^   │  &   │  *   │  (   │  )   │  _   │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │  1   │  2   │  3   │  4   │  5   │      │  6   │  7   │  8   │  9   │  0   │  -   │      │
├──────┼──────┼──────┼──────┼──────┼──────┼──────┤      ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │  `   │  `   │  `   │  ~   │  |   │      │  ]   │  [   │  {   │  }   │  \   │  `   │      │
└──────┴──────┴──────┴──────┼──────┼──────┼──────┤      ├──────┼──────┼──────┼──────┴──────┴──────┴──────┘
                            │ HELD │      │      │      │      │⌥Bksp │ HELD │
                            └──────┴──────┴──────┘      └──────┴──────┴──────┘
```

## Encoder Functions

| Layer | CCW (Counter-clockwise) | CW (Clockwise) |
|-------|------------------------|----------------|
| Base  | Volume Down | Volume Up |
| Nav   | Page Up | Page Down |
| Num   | Left Arrow | Right Arrow |
| Sym   | Brightness Down | Brightness Up |

## Customization

Edit `keymaps/default/keymap.c` to customize:
- Key mappings
- Layer definitions
- Encoder functions
- Tapping term (tap vs hold timing)

## Matrix Layout Note

QMK split keyboards use a mirrored matrix where:
- Left half: rows 0-3, columns 0-6
- Right half: rows 4-7, columns 6-0 (mirrored)

This allows both halves to use the same matrix scanning code.

## Troubleshooting

### Keyboard not recognized
- Check USB cable (must support data transfer)
- Try different USB port
- Re-flash firmware

### Split halves not communicating
- Check TRRS cable connection
- Ensure both halves have firmware flashed
- Check serial pin (D2) soldering

### Encoders not working
- Verify encoder wiring to B5 and B6 pins
- Adjust `ENCODER_RESOLUTION` in config.h if steps feel wrong

## License

GPL-2.0-or-later
