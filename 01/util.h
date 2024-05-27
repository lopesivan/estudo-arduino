#ifndef UTIL_H
#define UTIL_H

/*****************************************************************************
 *                                                                           *
 * ---------------------------- Public Interface --------------------------- *
 *                                                                           *
 *****************************************************************************/

#define BV(bit)              (1 << bit)
#define setBit(byte, bit)    (byte |= BV(bit))
#define clearBit(byte, bit)  (byte &= ~BV(bit))
#define toggleBit(byte, bit) (byte ^= BV(bit))

#endif 		// UTIL_H
/* -*- vim: set ts=4 sw=4 tw=78 ft=header: -*- */
