#ifndef A109000005_FORMAT_H
#define A109000005_FORMAT_H
#define KIND 5
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Header { int n; long long initial; };
struct Record { unsigned char type; long long amount; };
static_assert(sizeof(Record) == 16, "Record size");
static_assert(sizeof(Header) == 16, "Header size");
#endif
