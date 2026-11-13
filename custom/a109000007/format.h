#ifndef A109000007_FORMAT_H
#define A109000007_FORMAT_H
#define KIND 7
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Record { int x; int y; };
static_assert(sizeof(Record) == 8, "Record size");
#endif
