# README

## Used components

### Microcontroller
Arduino Nano 328 SKU DFR0010 (from DFRobot)
[wiki](https://wiki.dfrobot.com/Arduino_Nano_328__SKU__DFR0010_)

### Current sensor
ACS712 5A

### Motor driver
[Cytron MD13S](https://www.cytron.io/p-13amp-6v-30v-dc-motor-driver)

### Motor
JGB37-555

# Troubleshooting

## Arduino-ide

```
[18644:1223/101056.126347:FATAL:setuid_sandbox_host.cc(158)] The SUID sandbox helper binary was found, but is not configured correctly. Rather than run without sandboxing I'm aborting now. You need to make sure that /home/justyna-halicz-szymanska/Programy/arduino-ide_2.3.7_Linux_64bit/chrome-sandbox is owned by root and has mode 4755.
Pułapka debuggera/breakpoint (zrzut pamięci)
```

solution
```
sudo chown root chrome-sandbox
sudo chmod g+x,u+s chrome-sandbox
```
