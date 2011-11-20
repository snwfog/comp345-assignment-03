/**
 *  Function.h
 *  comp345-assignment-03
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**
 * Roll function mimicing the d20 roll syntax
 */
int roll(int range);
int roll(int range, int count, int modifier = 0);
int rollBaseStats();

#endif
