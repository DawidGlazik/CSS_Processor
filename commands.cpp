#include "commands.h"

int sectionNumber(Block* firstBlock) {
	int count = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].firstAttr != nullptr) count++;
		}
		traverser = traverser->next;
	}
	return count;
}

int selectorNumber(Block* firstBlock, int index) {
	int count = 0;
	int sum = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].firstAttr != nullptr) ++count;
			if (count == index) {
				Selector* traverser2 = traverser->section[i].firstSelector;
				while (traverser2 != nullptr) {
					sum++;
					traverser2 = traverser2->next;
				}
				return sum;
			}
		}
		traverser = traverser->next;
	}
	return -1;
}

int attributeNumber(Block* firstBlock, int index) {
	int count = 0;
	int sum = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].firstAttr != nullptr) ++count;
			if (count == index) {
				Attribute* traverser2 = traverser->section[i].firstAttr;
				while (traverser2 != nullptr) {
					sum++;
					traverser2 = traverser2->next;
				}
				return sum;
			}
		}
		traverser = traverser->next;
	}
	return -1;
}

void printExactSelector(Block* firstBlock, int indexB, int indexS) {
	int count1 = 0;
	int count2 = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].firstAttr != nullptr) count1++;
			if (indexB == count1) {
				if (traverser->section[i].selector != nullptr) {
					Selector* traverser2 = traverser->section[i].firstSelector;
					while (traverser2 != nullptr) {
						count2++;
						if (count2 == indexS && strcmp(traverser2->name, "") != 0) {
							cout << indexB << ",S," << indexS << " == " << traverser2->name << endl;
							return;
						}
						traverser2 = traverser2->next;
					}
				}
			}
		}
		traverser = traverser->next;
	}
}

void printExactAttribute(Block* firstBlock, int index, char name[]) {
	int count = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].attr != nullptr) ++count;
			if (count == index) {
				Attribute* traverser2 = traverser->section[i].firstAttr;
				while (traverser2 != nullptr) {
					if (strcmp(traverser2->name, name) == 0) {
						cout << index << ",A," << name << " == " << traverser2->value << endl;
						return;
					}
					traverser2 = traverser2->next;
				}
				return;
			}
		}
		traverser = traverser->next;
	}
}

int numberOfExactAttribute(Block* firstBlock, char name[]) {
	int count = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].attr != nullptr) {
				Attribute* traverser2 = traverser->section[i].firstAttr;
				while (traverser2 != nullptr) {
					if (strcmp(traverser2->name, name) == 0) {
						count++;
					}
					traverser2 = traverser2->next;
				}
			}
		}
		traverser = traverser->next;
	}
	return count;
}

int numberOfExactSelector(Block* firstBlock, char name[]) {
	int count = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].attr != nullptr) {
				Selector* traverser2 = traverser->section[i].firstSelector;
				while (traverser2 != nullptr) {
					if (strcmp(traverser2->name, name) == 0) {
						count++;
					}
					traverser2 = traverser2->next;
				}
			}
		}
		traverser = traverser->next;
	}
	return count;
}

void printAttributeOfSelector(Block* lastBlock, char nameA[], char nameS[]) {
	Block* traverser = lastBlock;
	while (traverser != nullptr) {
		for (int i = T - 1; i >= 0; i--) {
			if (traverser->section[i].attr != nullptr) {
				Selector* traverser2 = traverser->section[i].firstSelector;
				while (traverser2 != nullptr) {
					if (strcmp(traverser2->name, nameS) == 0) {
						Attribute* traverser3 = traverser->section[i].firstAttr;
						while (traverser3 != nullptr) {
							if (strcmp(traverser3->name, nameA) == 0) {
								cout << nameS << ",E," << nameA << " == " << traverser3->value << endl;
								return;
							}
							traverser3 = traverser3->next;
						}
					}
					traverser2 = traverser2->next;
				}
			}
		}
		traverser = traverser->prev;
	}
}

void deleteSection(Block* firstBlock, int index) {
	int count = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].attr != nullptr) ++count;
			if (count == index) {
				traverser->taken--;
				traverser->section[i].attr = nullptr;
				traverser->section[i].firstAttr = nullptr;
				traverser->section[i].lastAttr = nullptr;
				traverser->section[i].selector = nullptr;
				traverser->section[i].firstSelector = nullptr;
				traverser->section[i].lastSelector = nullptr;
				cout << index << ",D,* == deleted" << endl;
				return;
			}
		}
		if (traverser->taken == 0) deleteBlock(firstBlock, traverser);
		traverser = traverser->next;
	}
}

void deleteExactAttribute(Block* firstBlock, int index, char name[]) {
	int count = 0;
	Block* traverser = firstBlock;
	while (traverser != nullptr) {
		for (int i = 0; i < T; i++) {
			if (traverser->section[i].attr != nullptr) ++count;
			if (count == index) {
				Attribute* traverser2 = traverser->section[i].firstAttr;
				while (traverser2 != nullptr) {
					if (strcmp(traverser2->name, name) == 0) {
						if (traverser2->next != nullptr) traverser2->next->previous = traverser2->previous;
						if (traverser2->previous != nullptr) traverser2->previous->next = traverser2->next;
						else traverser->section[i].firstAttr = traverser2->next;
						cout << index << ",D," << name << " == deleted" << endl;
						if (traverser->section[i].firstAttr == nullptr) {
							traverser->taken--;
							traverser->section[i].attr = nullptr;
							traverser->section[i].selector = nullptr;
							traverser->section[i].firstSelector = nullptr;
							traverser->section[i].lastSelector = nullptr;
						}
						return;
					}
					traverser2 = traverser2->next;
				}
			}
		}
		if (traverser->taken == 0) deleteBlock(firstBlock, traverser);
		traverser = traverser->next;
	}
}