#ifndef A109000006_FORMAT_H
#define A109000006_FORMAT_H
#define KIND 6
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Record { unsigned char kind; int quantity; };
static_assert(sizeof(Record) == 8, "Record size");
#endif
