#include "functions.h"

int isDuplicate(Selector* firstSelector, char name[]) {
	Selector* traverser = firstSelector;
	while (traverser != nullptr) {
		if (strcmp(traverser->name, name) == 0) return 1;
		traverser = traverser->next;
	}
	return 0;
}

int isDuplicate(Attribute* firstAttr, char name[], char value[]) {
	Attribute* traverser = firstAttr;
	while (traverser != nullptr) {
		if (strcmp(traverser->name, name) == 0) {
			traverser->value = new char[strlen(value)];
			strcpy(traverser->value, value);
			return 1;
		}
		traverser = traverser->next;
	}
	return 0;
}

Selector* buildSelector(Selector*& firstSelector, Selector*& lastSelector, char name[]) {
	Selector* selector = new Selector(strlen(name));
	selector->next = nullptr;
	selector->previous = nullptr;
	firstSelector = selector;
	lastSelector = selector;
	strcpy(selector->name, name);
	return selector;
}

Attribute* buildAttribute(Attribute*& firstAttr, Attribute*& lastAttr, char nameA[], char nameV[]) {
	Attribute* attribute = new Attribute(strlen(nameA), strlen(nameV));
	strcpy(attribute->name, nameA);
	strcpy(attribute->value, nameV);
	attribute->next = nullptr;
	attribute->previous = nullptr;
	firstAttr = attribute;
	lastAttr = attribute;
	return attribute;
}

void executeCommand(Block* firstBlock, Block* lastBlock, char first[], char second, char third[]) {
	int argument1 = 0;
	int argument2 = 0;
	if (int(first[0]) >= 49 && int(first[0]) <= 57) argument1 = atoi(first);
	if (int(third[0]) >= 49 && int(third[0]) <= 57) argument2 = atoi(third);
	switch (second) {
	case 'A':
		if (argument1 != 0) {
			if (strcmp(third, "?") == 0 && attributeNumber(firstBlock, argument1) != -1) cout << argument1 << "," << second << "," << third << " == " << attributeNumber(firstBlock, argument1) << endl;
			else printExactAttribute(firstBlock, argument1, third);
		}
		else cout << first << "," << second << "," << third << " == " << numberOfExactAttribute(firstBlock, first) << endl;
		break;
	case 'S':
		if (argument1 != 0 && argument2 != 0) printExactSelector(firstBlock, argument1, argument2);
		else if (argument1 != 0) {
			if (selectorNumber(firstBlock, argument1) != -1) cout << argument1 << "," << second << "," << third << " == " << selectorNumber(firstBlock, argument1) << endl;
		}
		else cout << first << "," << second << "," << third << " == " << numberOfExactSelector(firstBlock, first) << endl;
		break;
	case 'D':
		if (strcmp(third, "*") != 0) deleteExactAttribute(firstBlock, argument1, third);
		else deleteSection(firstBlock, argument1);
		break;
	case 'E':
		printAttributeOfSelector(lastBlock, third, first);
		break;
	}
}

void checkIfCommand(Block* firstBlock, int* isCSS, int* i, char temp[], char x, int flagCommand) {
	if (*isCSS == 0 && *i == 0 && flagCommand == 0) {
		cout << "? == " << sectionNumber(firstBlock) << endl;
		return;
	}
	temp[*i] = x;
	*i = *i + 1;
	if (*i == 4) {
		temp[*i] = '\0';
		if (strcmp(temp, "????") == 0) {
			*isCSS = 0;
			*i = 0;
			return;
		}
	}
	return;
}

void removeLastWhite(char temp[], int* i) {
	if (*i > 0 && (temp[*i - 1] == ' ' || temp[*i - 1] == '\t')) temp[*i - 1] = '\0';
	else temp[*i] = '\0';
	*i = 0;
}

void checkIfCSS(int* isCSS, int* i, char temp[], char x) {
	temp[*i] = x;
	*i = *i + 1;
	if (*i == 4) {
		removeLastWhite(temp, i);
		if (strcmp(temp, "****") == 0) {
			*isCSS = 1;
		}
	}
}

void parseAttributes(struct counters* count, Block*& block, Block*& lastBlock, char temp[], char bufAttrName[]) {
	int flag = 0;
	int j = 0;
	while (flag == 0) {
		char x = getchar();
		switch (x) {
		case '\n': break;
		case '\t':case ' ':
			if (j == 0) break;
			else {
				temp[j] = x;
				j++;
				break;
			}
		case ':':
			removeLastWhite(temp, &j);
			strcpy(bufAttrName, temp);
			break;
		case ';':
			removeLastWhite(temp, &j);
			if (count->Acounter == 0) {
				block->section[count->Tcounter].attr = buildAttribute(block->section[count->Tcounter].firstAttr, block->section[count->Tcounter].lastAttr, bufAttrName, temp);
				block->taken++;
			}
			else {
				if (!isDuplicate(block->section[count->Tcounter].firstAttr, bufAttrName, temp)) addAttribute(block->section[count->Tcounter].firstAttr, block->section[count->Tcounter].attr, bufAttrName, temp);
			}
			count->Acounter++;
			break;
		case '}': {
			if (j != 0) {
				removeLastWhite(temp, &j);
				if (!isDuplicate(block->section[count->Tcounter].firstAttr, bufAttrName, temp)) addAttribute(block->section[count->Tcounter].firstAttr, block->section[count->Tcounter].attr, bufAttrName, temp);
			}
			flag = 1;
			count->Tcounter++;
			count->Scounter = 0;
			count->Acounter = 0;
			if (count->Tcounter == T) {
				block = new Block();
				block->next = nullptr;
				block->prev = lastBlock;
				lastBlock->next = block;
				lastBlock = block;
				count->Tcounter = 0;
			}
			break;
		}
		default:
			if (x < ' ') break;
			temp[j] = x;
			j++;
			break;
		}
	}
}