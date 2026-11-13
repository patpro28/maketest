#ifndef A109000004_FORMAT_H
#define A109000004_FORMAT_H
#define KIND 4
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Record { char code[8]; int score[3]; };
static_assert(sizeof(Record) == 20, "Record size");
#endif
