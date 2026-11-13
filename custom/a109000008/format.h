#ifndef A109000008_FORMAT_H
#define A109000008_FORMAT_H
#define KIND 8
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Record { char state; int seconds; };
static_assert(sizeof(Record) == 8, "Record size");
#endif
