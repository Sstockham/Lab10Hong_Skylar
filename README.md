# Renode setup
The Raspberry Pico needs configuration files for Renode to work properly.

* On MacOS, the installation location is `/Applications/Renode.app/Contents/MacOs`
* On Linux, the location for Debian, Fedora, and Arch is `/opt/renode`
* On Windows, the location is `C://Program Files/Renode`

To add the Pico configuration files:
1. Copy `rp2040_spinlock.py` and `rp2040_divider.py` to the `scripts/pydev` directory of your Renode installation.
1. Copy `rpi_pico_rp2040_w.repl` to the `platforms/cpus` directory.

## Here are our Power results:

Measurement #1:
5v at 21 mA

Measurement #2:
5v at 23 mA

Measurement #1:
5v at 21.3 mA

We can see that measurement 2 had the highest power consumption, suggesting that simply running a thread results in a roughly 10% total power increase.
