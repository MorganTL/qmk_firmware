/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// #define ROTATIONAL_TRANSFORM_ANGLE 0
#define POINTING_DEVICE_INVERT_Y

/* PMW3360 Settings */
#define PMW33XX_LIFTOFF_DISTANCE 0x00
#define PMW33XX_CS_PIN GP5
#define SPI_SCK_PIN GP2
#define SPI_MISO_PIN GP0
#define SPI_MOSI_PIN GP7

// see https://github.com/finrod09/qmk_userspace_features/tree/main/maccel for more detail
// goto https://www.desmos.com/calculator/k9vr0y2gev for graphical acceleration function
#define MOUSE_EXTENDED_REPORT
#define MACCEL_TAKEOFF 2.0      // lower/higher value = curve takes off more smoothly/abruptly
#define MACCEL_GROWTH_RATE 0.1 // lower/higher value = curve reaches its upper limit slower/faster 
#define MACCEL_OFFSET 5       // lower/higher value = acceleration kicks in earlier/later
#define MACCEL_LIMIT 0.15        // lower limit of accel curve (minimum acceleration factor)

// DPI settings
#define PLOOPY_DPI_OPTIONS { 800, 850, 900 }
#define PLOOPY_DPI_DEFAULT 0
