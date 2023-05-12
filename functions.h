#pragma once
#include "commands.h"

struct counters {
	int Tcounter;
	int Scounter;
	int Acounter;
	int Ccounter;
};

int isDuplicate(Selector* firstSelector, char name[]);

int isDuplicate(Attribute* firstAttr, char name[], char value[]);

Selector* buildSelector(Selector*& firstSelector, Selector*& lastSelector, char name[]);

Attribute* buildAttribute(Attribute*& firstAttr, Attribute*& lastAttr, char nameA[], char nameV[]);

void executeCommand(Block* firstBlock, Block* lastBlock, char first[], char second, char third[]);

void checkIfCommand(Block* firstBlock, int* isCSS, int* i, char temp[], char x, int flagCommand);

void removeLastWhite(char temp[], int* i);

void checkIfCSS(int* isCSS, int* i, char temp[], char x);

void parseAttributes(struct counters* count, Block*& block, Block*& lastBlock, char temp[], char bufAttrName[]);