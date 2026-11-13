#ifndef A109000001_FORMAT_H
#define A109000001_FORMAT_H
#define KIND 1
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Record { int id; int value; };
static_assert(sizeof(Record) == 8, "Record size");
#endif
