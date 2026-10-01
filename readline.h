#ifndef READLINE_H
#define READLINE_H

/**********************************************************
 * readline: Skips leading white-space characters, then   *
 *           reads the remainder of the input line and    *
 *           stores it in s. Truncates the line if its    *
 *           length exceeds n. Returns the number of      *
 *           characters stored.                           *
 **********************************************************/
int readline(char s[], int n);

#endif
