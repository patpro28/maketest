#ifndef A109000002_FORMAT_H
#define A109000002_FORMAT_H
#define KIND 2
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Header { int n; int threshold; };
struct Record { int id; int score; };
static_assert(sizeof(Record) == 8, "Record size");
static_assert(sizeof(Header) == 8, "Header size");
#endif
