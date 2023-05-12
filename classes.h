#pragma once
#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;
#define T 8
#define MAX_LENGTH 256

class Selector {
public:
	char* name;
	Selector* next;
	Selector* previous;
	Selector() {
		name = new char[100];
		next = nullptr;
		previous = nullptr;
	}
	Selector(size_t size) {
		name = new char[size];
		next = nullptr;
		previous = nullptr;
	}
	~Selector() {
		delete previous;
		delete next;
		delete[] name;
	}
};

class Attribute {
public:
	char* name;
	char* value;
	Attribute* next;
	Attribute* previous;
	Attribute() {
		name = new char[100];
		value = new char[100];
		next = nullptr;
		previous = nullptr;
	}
	Attribute(size_t sizeN, size_t sizeV) {
		name = new char[sizeN];
		value = new char[sizeV];
		next = nullptr;
		previous = nullptr;
	}
	~Attribute() {
		delete previous;
		delete next;
		delete[] value;
		delete[] name;
	}
};

class Section {
public:
	Selector* firstSelector;
	Selector* lastSelector;
	Selector* selector;

	Attribute* firstAttr;
	Attribute* lastAttr;
	Attribute* attr;

	Section() {
		firstSelector = nullptr;
		lastSelector = nullptr;
		selector = nullptr;
		firstAttr = nullptr;
		lastAttr = nullptr;
		attr = nullptr;
	}
	~Section() {
		attr->~Attribute();
		lastAttr->~Attribute();
		firstAttr->~Attribute();
		selector->~Selector();
		lastSelector->~Selector();
		firstSelector->~Selector();
	}
};

class Block {
public:
	Section* section;
	Block* next;
	Block* prev;
	int taken;
	Block() {
		section = new Section[T];
		taken = 0;
		next = nullptr;
		prev = nullptr;
	}
	~Block() {
		delete prev;
		delete next;
		delete[] section;
	}
};
