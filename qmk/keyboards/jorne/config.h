// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Split keyboard settings */
#define MASTER_LEFT                    // Left side is always the master (USB connected)

/* Encoder settings */
#define ENCODER_RESOLUTION 4           // Number of pulses per detent

/* Debounce settings */
#define DEBOUNCE 5                     // Debounce time in ms

/* Tapping settings for layer-tap and mod-tap */
#define TAPPING_TERM 200               // Time in ms to distinguish tap from hold
#define TAPPING_TERM_PER_KEY           // Allow per-key tapping term customization
#define PERMISSIVE_HOLD                // Makes tap-hold keys more responsive

/* Mouse key settings */
#define MOUSEKEY_DELAY 10
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_MAX_SPEED 10
#define MOUSEKEY_TIME_TO_MAX 30
