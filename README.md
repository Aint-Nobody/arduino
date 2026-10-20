# ESP8266 WIFI-MONITOR

Look at ALL WiFi MAC Adresses around you.
Collect and analyse them in all way you can imagine.
> 
The UI is nearly only UART based.
But for some reasons also a HTTP Server is include.
>
Use newest .ino or 
ready made build .bin in assets.
...4M2M.bin for 4MB device like D1Mini.
...1M512.bin for 1MB devices like ESP-01.
Use a Terminal that supports esc commands.

(For devices with flash >1MB)
For local MAC Vendor lookup function,
extract all files from Flash.Basis.fur.MAC.Vendor.zip.
Put all files into the littleFS using the build in http server.
Before you have to config your wifi access credentials.(Menu >e>9 (zeit/ntp) >2+3)
Then main menu >7
Or for a own AP, menu >e>c>2+3 
than main menu >7
ESC always jump back to main menu.
Ctrl+o toggle between online/offline mode.

There are many functions build in,
read the descriptions on top of each menu.

There is also a hidden menu for system
preferences/functions. (main menu >e>E)

The project is still under construction.
Firmware is beta and sometimes a bit confuse in menu structures this time.
A description over all is at work 😉

> Sorry for all UI Text is German.
> Google translate is your friend 😜
>
<img width="540" height="390" alt="hlogo" src="https://github.com/user-attachments/assets/c47242de-a210-43ce-8301-8964f8f21ae2" />


