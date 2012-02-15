#### miimem

A command-line utility to peek/poke MII PHY registers

#### Usage
     Usage: ./miimem DEVICE ADDR OFFSET [ DATA ]
     Read-from or write-to the ADDRessed PHY at given OFFSET
     
             DEVICE  the net device to open e.g. eth0
             ADDR    the number address of the PHY on the MDIO bus of DEVICE
             OFFSET          register memory offset in the PHY memory map
             DATA            data to be written
     
     When DATA is not given OFFSET is read, otherwise DATA is written to OFFSET

####

The command-line interface was inspired by the devmem2 utility by Jan-Derk Bakker [1]

[1] http://sources.buildroot.net/devmem2.c, for example / no homepage
