#pragma once
#include "maintainClasses.h"

int sectionNumber(Block* firstBlock);											//?

int selectorNumber(Block* firstBlock, int index);								//i,S,?

int attributeNumber(Block* firstBlock, int index);								//i,A,?

void printExactSelector(Block* firstBlock, int indexB, int indexS);				//i,S,j

void printExactAttribute(Block* firstBlock, int index, char name[]);			//i,A,n

int numberOfExactAttribute(Block* firstBlock, char name[]);						//n,A,?

int numberOfExactSelector(Block* firstBlock, char name[]);						//z,S,?

void printAttributeOfSelector(Block* lastBlock, char nameA[], char nameS[]);	//z,E,n

void deleteSection(Block* firstBlock, int index);								//i,D,*

void deleteExactAttribute(Block* firstBlock, int index, char name[]);			//i,D,n

