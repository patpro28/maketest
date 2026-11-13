#ifndef A109000010_FORMAT_H
#define A109000010_FORMAT_H
#define KIND 10
static_assert(sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(unsigned short) == 2, "Basic type sizes");
struct Header { char magic[4]; unsigned int n; };
struct Date { unsigned short year; unsigned char month; unsigned char day; };
struct Record { Date date; int temperature; };
static_assert(sizeof(Record) == 8, "Record size");
static_assert(sizeof(Header) == 8, "Header size");
static_assert(sizeof(Date) == 4, "Date size");
#endif
