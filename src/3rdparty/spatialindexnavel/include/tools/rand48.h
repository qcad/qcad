#pragma once

extern void srand48(long seed);
extern unsigned short *seed48(unsigned short xseed[3]);
extern long nrand48(unsigned short xseed[3]);
extern long mrand48(void);
extern long lrand48(void);
extern void lcong48(unsigned short p[7]);
extern long jrand48(unsigned short xseed[3]);
extern double erand48(unsigned short xseed[3]);
extern double drand48(void);
