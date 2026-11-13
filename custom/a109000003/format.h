#ifndef A109000003_FORMAT_H
#define A109000003_FORMAT_H
#define KIND 3
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Record { int id; int quantity; long long price; };
static_assert(sizeof(Record) == 16, "Record size");
#endif
