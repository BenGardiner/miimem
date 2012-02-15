/*
 * miimem -- a command-line utility to read+write MII PHY registers
 *
 * Copyright (C) 2012, Nanometrics Inc.
 * Ben Gardiner <bengardiner@nanometrics.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdlib.h>
#include <stdio.h>

#include "mii.h"

const char *usage = "Usage: %s DEVICE ADDR OFFSET [ DATA ]\n"
  "Read-from or write-to the ADDRessed PHY at given OFFSET\n"
  "\n"
  "\tDEVICE\tthe net device to open e.g. eth0\n"
  "\tADDR\tthe number address of the PHY on the MDIO bus of DEVICE\n"
  "\tOFFSET\t\tregister memory offset in the PHY memory map\n"
  "\tDATA\t\tdata to be written\n\n"
  "When DATA is not given OFFSET is read, otherwise DATA is written to OFFSET\n";

int main(int argc, char **argv)
{
  int skfd;
  static struct ifreq ifr;

  int ret = 0;
  char access_type = 'r';
  int addr, offset;
  int writeval = 0;
  int read_result = 0;

  if (argc < 4)
  {
    fprintf(stderr, usage, argv[0]);
    exit(-1);
  }
  addr = strtoul(argv[2], 0, 0);
  offset = strtoul(argv[3], 0, 0);

  if (argc > 4)
  {
    access_type = 'w';
    writeval = strtoul(argv[4], 0, 0);
  }

  skfd = mdio_init(&ifr, argv[1], addr);
  if (skfd < 0)
  {
    perror("mdio_init");
    exit(-1);
  }

  if (access_type == 'w')
  {
    mdio_write(&ifr, skfd, offset, writeval);
    read_result = mdio_read(&ifr, skfd, offset);
    printf("Written 0x%X; readback 0x%X\n", writeval, read_result);
    fflush(stdout);
  }
  else
  {
    read_result = mdio_read(&ifr, skfd, offset);
    printf("Value at offset 0x%X of address 0x%X: 0x%X\n", offset, addr, read_result);
    fflush(stdout);
  }

  mdio_finish(skfd);
  return ret;
}
