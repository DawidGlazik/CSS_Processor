#include "functions.h"

int main()
{
	Block* firstBlock;
	Block* lastBlock;
	Block* block = new Block();
	block->next = nullptr;
	block->prev = nullptr;
	firstBlock = block;
	lastBlock = block;
	struct counters counter;
	char x;
	char* temp = new char[MAX_LENGTH];
	int i = 0;
	counter.Tcounter = 0;
	counter.Scounter = 0;
	counter.Acounter = 0;
	counter.Ccounter = 0;
	char* bufAttrName = new char[MAX_LENGTH];
	int isCSS = 1;
	char* first = new char[MAX_LENGTH];
	char second;
	char* third = new char[MAX_LENGTH];
	int executeCmd = 0;
	int flagCommand = 0;

	while (x = getchar()) {
		if(x == '\xff') exit(1);
		switch (x){
		case '\t':case ' ': 
			if (i == 0) break;
			else {
				temp[i] = x;
				i++;
				break;
			}
		case '\n':
			if (isCSS == 0 && executeCmd == 1) {
				removeLastWhite(temp, &i);
				strcpy(third, temp);
				executeCommand(firstBlock, lastBlock, first, second, third);
				executeCmd = 0;
				counter.Ccounter = 0;
				flagCommand = 0;
			}
			break;
		case ',':
			if (isCSS) {
				removeLastWhite(temp, &i);
				if (counter.Scounter == 0) {
					block->section[counter.Tcounter].selector = buildSelector(block->section[counter.Tcounter].firstSelector, block->section[counter.Tcounter].lastSelector, temp);
				}
				else {
					if(!isDuplicate(block->section[counter.Tcounter].firstSelector, temp)) addSelector(block->section[counter.Tcounter].firstSelector, block->section[counter.Tcounter].selector, temp);
				}
				counter.Scounter++;
			}
			else {
				if (i > 0 && (temp[i - 1] == ' ' || temp[i - 1] == '\t')) temp[i - 1] = '\0';
				else temp[i] = '\0';
				counter.Ccounter++;
				if (counter.Ccounter == 1) {
					strcpy(first, temp);
				}
				else if (counter.Ccounter == 2) {
					second = temp[i - 1];
					executeCmd = 1;
				}
				i = 0;
				flagCommand = 1;
			}
			break;
		case '{':
			if (!isCSS) break;
			removeLastWhite(temp, &i);
			if (counter.Scounter == 0 && strcmp(temp, "") != 0) block->section[counter.Tcounter].selector = buildSelector(block->section[counter.Tcounter].firstSelector, block->section[counter.Tcounter].lastSelector, temp);
			else if (!isDuplicate(block->section[counter.Tcounter].firstSelector, temp)) addSelector(block->section[counter.Tcounter].firstSelector, block->section[counter.Tcounter].selector, temp);
			parseAttributes(&counter, block, lastBlock, temp, bufAttrName);
			break;
		case '?':
			checkIfCommand(firstBlock, &isCSS, &i, temp, x, flagCommand);
			break;
		case '*':
			checkIfCSS(&isCSS, &i, temp, x);
			break;
		default:
			if (x < ' ') break;
			temp[i] = x;
			i++;
			break;
		}
	}
	delete[] third;
	delete[] first;
	delete[] bufAttrName;
	delete[] temp;
}
