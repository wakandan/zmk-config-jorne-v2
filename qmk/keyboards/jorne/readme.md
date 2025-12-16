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

## QMK Installation

### macOS (Homebrew)

**Option 1: Using Homebrew (Recommended)**

```bash
# Install QMK CLI
brew install qmk/qmk/qmk

# Setup QMK (clones qmk_firmware repository to ~/qmk_firmware)
qmk setup
```

**Option 2: Using pipx (Alternative)**

```bash
# Install pipx if not already installed
brew install pipx
pipx ensurepath

# Install QMK via pipx
pipx install qmk

# Setup QMK
qmk setup
```

### Install Required Toolchains

The AVR toolchain is required for Pro Micro (ATmega32U4):

```bash
# Install AVR toolchain
brew tap osx-cross/avr
brew install avr-gcc@8 avr-binutils

# Add to PATH (add this to your ~/.zshrc or ~/.bashrc)
export PATH="/opt/homebrew/opt/avr-gcc@8/bin:/opt/homebrew/opt/avr-binutils/bin:$PATH"

# Reload shell or run
source ~/.zshrc
```

### Verify Installation

```bash
# Check QMK installation
qmk doctor

# Should show: QMK is ready to go
```

### Windows

```bash
# Use QMK MSYS
# Download from: https://msys.qmk.fm/

# After installing, open QMK MSYS and run:
qmk setup
```

### Linux (Debian/Ubuntu)

```bash
# Install dependencies
sudo apt install -y git python3-pip

# Install QMK
python3 -m pip install --user qmk

# Setup QMK
qmk setup

# Install AVR toolchain
sudo apt install -y avr-libc gcc-avr avrdude
```

## Building the Firmware

### Step 1: Copy Keyboard to QMK

```bash
# Copy this keyboard folder to qmk_firmware/keyboards/
cp -r qmk/keyboards/jorne ~/qmk_firmware/keyboards/jorne

# Or create a symlink (useful for development)
ln -s "$(pwd)/qmk/keyboards/jorne" ~/qmk_firmware/keyboards/jorne
```

### Step 2: Compile

```bash
# Navigate to QMK firmware directory
cd ~/qmk_firmware

# Compile the firmware
qmk compile -kb jorne -km default
```

If successful, you'll see output like:
```
Compiling keymap with make...
[OK] Compiled firmware: jorne_default.hex
```

The compiled firmware will be at `~/qmk_firmware/jorne_default.hex`

## Flashing the Firmware

### Using QMK Toolbox (GUI - Recommended for Beginners)

1. Download [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)
2. Open QMK Toolbox
3. Load the `.hex` file
4. Connect keyboard half via USB
5. Enter bootloader mode (see below)
6. Click "Flash"
7. Repeat for other half

### Using Command Line

**Flash Left Half:**
```bash
# Put left half in bootloader mode first, then run:
qmk flash -kb jorne -km default -bl avrdude-split-left
```

**Flash Right Half:**
```bash
# Put right half in bootloader mode first, then run:
qmk flash -kb jorne -km default -bl avrdude-split-right
```

**Alternative (auto-detect):**
```bash
# This will auto-detect the bootloader
qmk flash -kb jorne -km default
```

### Entering Bootloader Mode (Pro Micro)

**Method 1: Reset Button (if available)**
- Press the reset button twice quickly

**Method 2: Short RST to GND**
- Use tweezers or a wire to short the RST and GND pins twice quickly
- The LED will pulse/fade indicating bootloader mode

**Method 3: Bootmagic Reset**
- Hold the top-left key while plugging in USB

> ⚠️ **Important**: You have ~8 seconds to flash after entering bootloader mode!

### Flashing Both Halves

For split keyboards, you need to flash **both halves**:

1. **Flash Left Half First**
   - Connect left half via USB
   - Enter bootloader mode
   - Flash with `-bl avrdude-split-left`

2. **Flash Right Half**
   - Disconnect left half
   - Connect right half via USB
   - Enter bootloader mode
   - Flash with `-bl avrdude-split-right`

3. **Test**
   - Connect both halves with TRRS cable
   - Connect left half to computer via USB
   - Both halves should work

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
