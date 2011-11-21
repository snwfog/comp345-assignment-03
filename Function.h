/**
 *  Function.h
 *  comp345-assignment-03
 *
 */

#ifndef FUNCTION_H
#define FUNCTION_H
#include <ncurses.h>

/**
 * Roll function mimicing the d20 roll syntax
 */
int roll(int range);
int roll(int range, int count, int modifier = 0);
int rollBaseStats();

/**
 *  Helper functions
 */

// character stats to modifier
int toModifier(int n);


#endif
