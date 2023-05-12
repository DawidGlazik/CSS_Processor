#pragma once
#include "classes.h"

Selector* GetLast(Selector* firstNode);

Attribute* GetLast(Attribute* firstNode);

Block* GetLast(Block* firstNode);

void addSelector(Selector* firstSelector, Selector* newSelector, char name[]);

void addAttribute(Attribute* firstAttr, Attribute* newAttr, char name[], char value[]);

void deleteBlock(Block*& firstBlock, Block*& Block);