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
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/sockios.h>

#ifndef __GLIBC__
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#endif
#include <linux/mii.h>
#include <linux/sockios.h>

#include "mii.h"

int mdio_init(struct ifreq *ifr, const char *ifname, const int phyaddr)
{
  int skfd;
  struct mii_ioctl_data *mii = (struct mii_ioctl_data *) &ifr->ifr_data;

  if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket");
    return skfd;
  }

  strncpy(ifr->ifr_name, ifname, IFNAMSIZ);
  if (ioctl(skfd, SIOCGMIIPHY, ifr) < 0)
  {
    if (errno != ENODEV)
      fprintf(stderr, "SIOCGMIIPHY on %s failed: %s\n", ifname, strerror(errno));
    return -ENODEV;
  }

  mii->phy_id = phyaddr;
  return skfd;
}

void mdio_finish(int skfd)
{
  close(skfd);
}

int mdio_read(struct ifreq *ifr, int skfd, int offset)
{
  struct mii_ioctl_data *mii = (struct mii_ioctl_data *) &ifr->ifr_data;
  mii->reg_num = offset;
  if (ioctl(skfd, SIOCGMIIREG, ifr) < 0)
  {
    fprintf(stderr, "SIOCGMIIREG on %s failed: %s\n", ifr->ifr_name, strerror(errno));
    return -1;
  }
  return mii->val_out;
}

int mdio_write(struct ifreq *ifr, int skfd, int offset, int value)
{
  int ret = 0;
  struct mii_ioctl_data *mii = (struct mii_ioctl_data *) &ifr->ifr_data;
  mii->reg_num = offset;
  mii->val_in = value;
  if ((ret = ioctl(skfd, SIOCSMIIREG, ifr)) < 0)
  {
    fprintf(stderr, "SIOCSMIIREG on %s failed: %s\n", ifr->ifr_name, strerror(errno));
  }
  return ret;
}
