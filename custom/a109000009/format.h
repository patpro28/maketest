#ifndef A109000009_FORMAT_H
#define A109000009_FORMAT_H
#define KIND 9
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Record { char code[12]; int stock; };
static_assert(sizeof(Record) == 16, "Record size");
#endif
