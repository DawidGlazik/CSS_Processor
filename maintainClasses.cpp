#include "maintainClasses.h"

Selector* GetLast(Selector* firstNode) {
	if (firstNode == nullptr) return nullptr;
	Selector* temp = firstNode;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return temp;
}

Attribute* GetLast(Attribute* firstNode) {
	if (firstNode == nullptr) return nullptr;
	Attribute* temp = firstNode;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return temp;
}

Block* GetLast(Block* firstNode) {
	if (firstNode == nullptr) return nullptr;
	Block* temp = firstNode;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return temp;
}

void addSelector(Selector* firstSelector, Selector* newSelector, char name[]) {
	newSelector = new Selector(strlen(name));
	strcpy(newSelector->name, name);
	Selector* last = GetLast(firstSelector);
	newSelector->next = nullptr;
	newSelector->previous = last;
	if (last == nullptr) return;
	last->next = newSelector;
}

void addAttribute(Attribute* firstAttr, Attribute* newAttr, char name[], char value[]) {
	newAttr = new Attribute(strlen(name), strlen(value));
	strcpy(newAttr->name, name);
	strcpy(newAttr->value, value);
	newAttr->next = nullptr;
	Attribute* last = GetLast(firstAttr);
	newAttr->previous = last;
	if (last == nullptr) return;
	last->next = newAttr;
}

void deleteBlock(Block*& firstBlock, Block*& Block) {
	if (Block == nullptr) return;
	if (Block->next != nullptr) Block->next->prev = Block->prev;
	if (Block->prev != nullptr) Block->prev->next = Block->next;
	else firstBlock = Block->next;
}