# av4 hotswap

[Av4](https://iv-works.com/av4/) - an acrylic board with arisu layout

The project owner failed to provide qmk source code and the promise of VIAL port never come true.
Referencing the [arisu pcb](https://github.com/FateNozomi/arisu-pcb) and its `config.h`, I reverse engineered the pinouts and created the `config.h` that works on my *Av4.1HS* pcb.
The via json `av4_via.json` is also included.

The *Av4.1HS* pcb is based on the arisu with the following modifications:
1. column9 is changed to PB2 (pin 10)
2. L1-L22 [WS2812B](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf) LEDs are added and they are daisy chained (L1 Dout -> L2 Din)
3. L1 [WS2812B](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf) Din pin is connected to PB7 (pin 12)
4. The MOSI test point is connected to PB7 (pin 12) instead of the correct PB2 (pin 10)
   - I suspect the pcb designer forgot to move the traces when they were changing column9


* Keyboard Maintainer: [MorganTL](https://github.com/MorganTL)
* Hardware Supported: *Av4.1HS*
* Hardware Availability: [av4 hotswap pcb](https://iv-works.com/product/av4-pcb/)

Make example for this keyboard (after setting up your build environment):

    make iv_works/av4_hotswap:default

Flashing example for this keyboard:

    make iv_works/av4_hotswap:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
