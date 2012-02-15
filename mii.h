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

#ifndef MII_H
#define MII_H

#include <net/if.h>

int mdio_init(struct ifreq *ifr, const char *ifname, const int phyaddr);

void mdio_finish(int skfd);

int mdio_read(struct ifreq *ifr, int skfd, int offset);

int mdio_write(struct ifreq *ifr, int skfd, int offset, int value);

#endif /* MII_H */
