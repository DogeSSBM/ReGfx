#include "Includes.h"

typedef struct{
    Coord origin;
}Camera;

struct Rule_s;
struct Node_s;
struct Term_s;
struct TermList_s;
struct RuleList_s;
struct MatchList_s;
struct SubStr_s;
struct ParseFeed_s;

typedef enum{
    T_STR,  // string
    T_FMT,  // format string
    T_NUM,  // number
    T_OPR,  // operator
    T_LST   // term list
}TermType;

typedef enum{O_AND, O_OR, O_LP, O_RP}Operator;

typedef struct Term_s{
    TermType type;
    union{
        char *str;
        char *fmt;
        uint num;
        Operator opr;
        struct TermList_s *list;
    };
}Term;

typedef struct TermList_s{
    Term *term;
    struct TermList_s *next;
}TermList;


typedef struct RuleList_s{
    TermList *l;
    TermList *r;
    struct RuleList_s *next;
}RuleList;

typedef struct MatchList_s{
    struct Node_s *node;
    RuleList *rule;
    uint index;
    struct MatchList_s *next;
}MatchList;

typedef struct Node_s{
    MatchList *parent;
    char *str;
    MatchList *child;
}Node;

typedef struct SubStr_s{
    char *pos;
    uint len;
    char *rest;
}SubStr;

typedef struct ParseFeed_s{
    char *pos;
    uint len;
    TermList *terms;
}ParseFeed;

ParseFeed parseStr(ParseFeed feed)
{

}

ParseFeed parseFmt(ParseFeed feed)
{

}

ParseFeed parseNum(ParseFeed feed)
{

}

ParseFeed parseOpr(ParseFeed feed)
{

}

ParseFeed parseLst(ParseFeed feed)
{

}

ParseFeed parse(ParseFeed feed)
{
    switch(*feed.pos){
        case '\"':
            return parseStr(feed);
            break;
        case '$':
            return parseFmt(feed);
            break;
        case '0'...'9':
            return parseNum(feed);
    };
    pos.
}

int main(int argc, char const *argv[])
{
	Length window = {800, 600};
	init();
	setWindowLen(window);

	while(1){
		Ticks frameStart = getTicks();
		clear();



		draw();
		events(frameStart + TPF);
	}
	return 0;
}
