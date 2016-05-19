#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
#include "HashTable.h"

#define PASS "Pass"
#define FAIL "Fail"
/*
    General testing of node/linked list/hashtable functionality.

    I realize this test suite is pretty limited (doesn't give
    the best info about what failed and why) -- don't have a ton
    of programming time this weekend, so I want to just bang it
    out. Still useful when combined with breakpoints.
*/

void enterTest(char* testName) 
{
    printf("Beginning test: %s\n", testName);
}

void exitTest(char* testName, bool result) 
{
    printf("Ending test: %s.\tResult: %s\n", testName, (result) ? PASS : FAIL);
}

void enterCase(char* caseName) 
{
    printf("    Beginning case: %s\n", caseName);
}

void exitCase(char* caseName, bool result) 
{
    printf("    Ending case: %s.\tResult: %s\n", caseName, (result) ? PASS : FAIL);
}

/*
bool exampleCase() 
{
    enterCase("Remove Node");
    bool result = false;
    exitCase("Remove Node", result);
    return result;
}
*/

bool createListCase() 
{
    enterCase("List Creation");
    linked_list * testList = createList();
    bool result = testList != NULL && testList->head == NULL && testList->length == 0;
    exitCase("List Creation", result);
    destroyList(&testList);
    return result;
}

bool addNodeCase() 
{
    enterCase("Add Node");
    linked_list * testList = createList();
    addNode(testList, "Key 1", "Value 1");
    addNode(testList, "Key 2", "Value 2");
    addNode(testList, "Key 3", "Value 3");
    
    bool result = strcmp(testList->head->key, "Key 1") == 0 &&
                  strcmp(testList->head->value, "Value 1") == 0 &&
                  strcmp(testList->head->next->key, "Key 2") == 0 &&
                  strcmp(testList->head->next->value, "Value 2") == 0 &&
                  strcmp(testList->head->next->next->key, "Key 3") == 0 &&
                  strcmp(testList->head->next->next->value, "Value 3") == 0 &&
                  testList->length == 3;

    exitCase("Add Node", result);
    destroyList(&testList);
    return result;
}

bool removeNodeCase() 
{
    enterCase("Remove Node");
    bool result = false;
    linked_list * testList = createList();
    addNode(testList, "Key 1", "Value 1");
    addNode(testList, "Key 2", "Value 2");
    addNode(testList, "Key 3", "Value 3");
    removeNode(testList, "Key 2");
    result = strcmp(testList->head->key, "Key 1") == 0 &&
             strcmp(testList->head->value, "Value 1") == 0 &&
             strcmp(testList->head->next->key, "Key 3") == 0 &&
             strcmp(testList->head->next->value, "Value 3") == 0 &&
             testList->length == 2;
    exitCase("Remove Node", result);
    destroyList(&testList);
    return result;
}

bool removeAllNodesCase() 
{
    enterCase("Remove All Nodes");
    linked_list * testList = createList();
    addNode(testList, "Key 1", "Value 1");
    addNode(testList, "Key 2", "Value 2");
    addNode(testList, "Key 3", "Value 3");
    addNode(testList, "Key 4", "Value 4");
    removeNode(testList, "Key 2");
    // Removing in this order to see if the list is preserved as expected
    // and that there are no issues with removing the head of the list.
    removeNode(testList, "Key 1");
    removeNode(testList, "Key 3");
    removeNode(testList, "Key 4");
    bool result = !testList->head && testList->length == 0;
    // Making sure we can still add nodes even if we've removed all nodes
    addNode(testList, "Key 1 Again", "Value 1 Again");
    result = result && testList->length == 1 && strcmp(testList->head->key, "Key 1 Again") == 0 && strcmp(testList->head->value, "Value 1 Again") == 0;
    exitCase("Remove All Nodes", result);
    destroyList(&testList);
    return result;
}

bool destroyListCase() 
{
    // This is probably the worst test case. Not sure how to
    // verify that everything's been freed properly.
    // At this point, we're just checking that the function finished
    // and set our list pointer to NULL.
    enterCase("Destroy List");
    linked_list * testList = createList();
    addNode(testList, "Key 1", "Value 1");
    addNode(testList, "Key 2", "Value 2");
    addNode(testList, "Key 3", "Value 3");
    removeNode(testList, "Key 2");
    addNode(testList, "Key 4", "Value 4");
    destroyList(&testList);
    bool result = !testList;
    exitCase("Destroy List", result);
    return result;
}

bool lengthCase() 
{
    enterCase("Length Check");
    bool result;
    linked_list * testList = createList();
    result = testList->length == 0;
    addNode(testList, "Key 1", "Value 1");
    result = result && testList->length == 1;
    addNode(testList, "Key 2", "Value 2");
    result = result && testList->length == 2;
    addNode(testList, "Key 3", "Value 3");
    result = result && testList->length == 3;
    addNode(testList, "Key 4", "Value 4");
    result = result && testList->length == 4;
    removeNode(testList, "Key 2");
    result = result && testList->length == 3;
    removeNode(testList, "Key 1");
    result = result && testList->length == 2;
    removeNode(testList, "Key 3");
    result = result && testList->length == 1;
    removeNode(testList, "Key 4");
    result = result && testList->length == 0;
    addNode(testList, "Key A", "Value A");
    result = result && testList->length == 1;
    addNode(testList, "Key B", "Value B");
    result = result && testList->length == 2;
    exitCase("Length Check", result);
    destroyList(&testList);
    return result;
}

bool runLinkedListTests() 
{
    enterTest("Linked List");
    bool result = true;
    if (result) result = createListCase();
    if (result) result = addNodeCase();
    if (result) result = removeNodeCase();
    if (result) result = removeAllNodesCase();
    if (result) result = destroyListCase();
    if (result) result = lengthCase();
    exitTest("Linked List", result);
    return result;
}

bool createHashtableCase() 
{
    enterCase("Hashtable Creation");
    hashtable * testTable = createTable(13);
    bool result = testTable && testTable->length == 13 && testTable->array;
    exitCase("Hashtable Creation", result);
    destroyTable(&testTable);
    return result;
}

bool destroyHashtableCase() 
{
    // Again, not the best test. Just testing that our call succeeded
    // and that our table is now NULL.
    enterCase("Hashtable Destruction");
    hashtable * testTable = createTable(13);
    insertIntoTable(testTable, "pumpkin", "1"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "2"); // hash of 5
    insertIntoTable(testTable, "ryan", "2"); //hash of 0
    insertIntoTable(testTable, "alex", "3"); //hash of 10
    insertIntoTable(testTable, "tedddddd", "4"); //hash of 11
    removeFromTable(testTable, "ryan");
    removeFromTable(testTable, "pumpkin"); // At the moment, we only remove the first instance
    destroyTable(&testTable);
    bool result = !testTable;
    exitCase("Hashtable Destructionn", result);
    return result;
}

bool generateHashCase() 
{
    enterCase("Hashing Algorithm");
    hashtable * testTable = createTable(13);
    int hash = generateHash(testTable, "pumpkin");
    bool result = testTable && testTable->length == 13 && testTable->array && hash == 5;
    exitCase("Hashing Algorithm", result);
    destroyTable(&testTable);
    return result;
}

bool insertIntoHashtableCase() 
{
    enterCase("Insert into Hashtable");
    hashtable * testTable = createTable(13);
    insertIntoTable(testTable, "pumpkin", "1"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "2"); // hash of 5
    insertIntoTable(testTable, "ryan", "2"); //hash of 0
    insertIntoTable(testTable, "alex", "3"); //hash of 10
    insertIntoTable(testTable, "tedddddd", "4"); //hash of 11
    // So messy. Gross.
    bool result = testTable &&
        testTable->length == 13 &&
        testTable->array &&
        testTable->array[0]->length == 1 &&
        strcmp(testTable->array[0]->head->key, "ryan") == 0 &&
        strcmp(testTable->array[0]->head->value, "2") == 0 &&
        testTable->array[5]->length == 2 &&
        strcmp(testTable->array[5]->head->key, "pumpkin") == 0 &&
        strcmp(testTable->array[5]->head->value, "1") == 0 &&
        strcmp(testTable->array[5]->head->next->key, "pumpkin") == 0 &&
        strcmp(testTable->array[5]->head->next->value, "2") == 0 &&
        testTable->array[10]->length == 1 &&
        strcmp(testTable->array[10]->head->key, "alex") == 0 &&
        strcmp(testTable->array[10]->head->value, "3") == 0 &&
        testTable->array[11]->length == 1 &&
        strcmp(testTable->array[11]->head->key, "tedddddd") == 0 &&
        strcmp(testTable->array[11]->head->value, "4") == 0;
    exitCase("Insert into Hashtable", result);
    destroyTable(&testTable);
    return result;
}

bool removeFromHashtableCase() 
{
    enterCase("Remove from Hashtable");
    hashtable * testTable = createTable(13);
    insertIntoTable(testTable, "pumpkin", "1"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "2"); // hash of 5
    insertIntoTable(testTable, "ryan", "2"); //hash of 0
    insertIntoTable(testTable, "alex", "3"); //hash of 10
    insertIntoTable(testTable, "tedddddd", "4"); //hash of 11
    removeFromTable(testTable, "ryan");
    removeFromTable(testTable, "pumpkin"); // At the moment, we only remove the first instance
    // So messy. Gross.
    bool result = testTable &&
        testTable->length == 13 &&
        testTable->array &&
        testTable->array[0]->length == 0 &&
        !testTable->array[0]->head &&
        testTable->array[5]->length == 1 &&
        strcmp(testTable->array[5]->head->key, "pumpkin") == 0 &&
        strcmp(testTable->array[5]->head->value, "2") == 0 &&
        !testTable->array[5]->head->next &&
        testTable->array[10]->length == 1 &&
        strcmp(testTable->array[10]->head->key, "alex") == 0 &&
        strcmp(testTable->array[10]->head->value, "3") == 0 &&
        testTable->array[11]->length == 1 &&
        strcmp(testTable->array[11]->head->key, "tedddddd") == 0 &&
        strcmp(testTable->array[11]->head->value, "4") == 0;
    exitCase("Remove from Hashtable", result);
    destroyTable(&testTable);
    return result;
}

bool getNodeFromTableCase() 
{
    enterCase("Get Node from Hashtable");
    hashtable * testTable = createTable(13);
    insertIntoTable(testTable, "pumpkin", "1"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "2"); // hash of 5
    insertIntoTable(testTable, "ryan", "2"); //hash of 0
    insertIntoTable(testTable, "alex", "3"); //hash of 10
    insertIntoTable(testTable, "tedddddd", "4"); //hash of 11
    removeFromTable(testTable, "ryan");
    removeFromTable(testTable, "pumpkin"); // At the moment, we only remove the first instance
    node* gottenNode = getNodeFromTable(testTable, "pumpkin");
    // So messy. Gross.
    bool result = testTable &&
        testTable->length == 13 &&
        testTable->array &&
        testTable->array[0]->length == 0 &&
        !testTable->array[0]->head &&
        testTable->array[5]->length == 1 &&
        strcmp(testTable->array[5]->head->key, "pumpkin") == 0 &&
        strcmp(testTable->array[5]->head->value, "2") == 0 &&
        !testTable->array[5]->head->next &&
        testTable->array[10]->length == 1 &&
        strcmp(testTable->array[10]->head->key, "alex") == 0 &&
        strcmp(testTable->array[10]->head->value, "3") == 0 &&
        testTable->array[11]->length == 1 &&
        strcmp(testTable->array[11]->head->key, "tedddddd") == 0 &&
        strcmp(testTable->array[11]->head->value, "4") == 0 &&
        strcmp(gottenNode->key, "pumpkin") == 0 &&
        strcmp(gottenNode->value, "2") == 0 &&
        !gottenNode->next;
    exitCase("Get Node from Hashtable", result);
    destroyTable(&testTable);
    return result;
}

bool getNumberOfNodesCase() 
{
    enterCase("Hashtable Node Count");
    hashtable * testTable = createTable(17);
    insertIntoTable(testTable, "pumpkin", "1"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "2"); // hash of 5
    insertIntoTable(testTable, "ryan", "2"); //hash of 0
    insertIntoTable(testTable, "alex", "3"); //hash of 10
    insertIntoTable(testTable, "tedddddd", "4"); //hash of 11
    removeFromTable(testTable, "ryan");
    removeFromTable(testTable, "pumpkin"); // At the moment, we only remove the first instance
    bool result = getNumberOfNodes(testTable) == 3;
    exitCase("Hashtable Node Count", result);
    destroyTable(&testTable);
    return result;
}

bool printHistogramCase() 
{
    enterCase("Print Histogram");
    hashtable * testTable = createTable(13);
    insertIntoTable(testTable, "pumpkin", "1"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "2"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "3"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "4"); // hash of 5
    insertIntoTable(testTable, "pumpkin", "5"); // hash of 5
    insertIntoTable(testTable, "suzette", "6"); 
    insertIntoTable(testTable, "frankenstein", "7"); 
    insertIntoTable(testTable, "ryan", "2");
    insertIntoTable(testTable, "alex", "3");
    insertIntoTable(testTable, "manirith", "4");
    insertIntoTable(testTable, "is", "4");
    insertIntoTable(testTable, "leaving", "4");
    insertIntoTable(testTable, "sadface", "4");
    insertIntoTable(testTable, ":(", "4");
    removeFromTable(testTable, "ryan");
    printf("\n\n");
    printHistogram(testTable);
    printf("\n\n");
    bool result = true;
    exitCase("Print Histogram", result);
    destroyTable(&testTable);
    return result;
}

bool runHashtableTests() 
{
    enterTest("Hashtable");
    bool result = true;
    if (result) result = createHashtableCase();
    if (result) result = destroyHashtableCase();
    if (result) result = generateHashCase();
    if (result) result = insertIntoHashtableCase();
    if (result) result = removeFromHashtableCase();
    if (result) result = getNodeFromTableCase();
    if (result) result = getNumberOfNodesCase();
    if (result) result = printHistogramCase(); 
    exitTest("Hashtable", result);
    return result;
}

int main(void) 
{
    bool result = true;
    while (true)
    {
        if (result) result = runLinkedListTests();
        if (result) result = runHashtableTests();
        if (result) printf("All tests passed!\n");
        else printf("Some failures occured. :(\n");
    }
    return 0;
}