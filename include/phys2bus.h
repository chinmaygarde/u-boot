/*
 * Copyright 2015 Stephen Warren
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _BUS_ADDR_H
#define _BUS_ADDR_H

#ifdef CONFIG_PHYS_TO_BUS
static unsigned long phys_to_bus(unsigned long phys);
static unsigned long bus_to_phys(unsigned long bus);
#else
static inline unsigned long phys_to_bus(unsigned long phys)
{
	return phys;
}

static inline unsigned long bus_to_phys(unsigned long bus)
{
	return bus;
}
#endif

#endif
