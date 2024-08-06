#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4
#define MIN 2

typedef struct Product {
    int id;
    char name[50];
    float price;
    int stock;
    char category[50];
    char description[100];
} Product;

typedef struct BTreeNode {
    Product products[MAX + 1];
    int count;
    struct BTreeNode *link[MAX + 1];
} BTreeNode;

BTreeNode *root;

// Create a node
BTreeNode *createNode(Product product, BTreeNode *child) {
    BTreeNode *newNode;
    newNode = (BTreeNode *)malloc(sizeof(BTreeNode));
    newNode->products[1] = product;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

// Insert a product
void insertNode(Product product, int pos, BTreeNode *node, BTreeNode *child) {
    int j = node->count;
    while (j > pos) {
        node->products[j + 1] = node->products[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->products[j + 1] = product;
    node->link[j + 1] = child;
    node->count++;
}

// Split a node
void splitNode(Product product, Product *pval, int pos, BTreeNode *node, BTreeNode *child, BTreeNode **newNode) {
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = (BTreeNode *)malloc(sizeof(BTreeNode));
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->products[j - median] = node->products[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        insertNode(product, pos, node, child);
    } else {
        insertNode(product, pos - median, *newNode, child);
    }

    *pval = node->products[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

// Set the value in the node
int setValue(Product product, Product *pval, BTreeNode *node, BTreeNode **child) {
    int pos;
    if (!node) {
        *pval = product;
        *child = NULL;
        return 1;
    }

    if (product.id < node->products[1].id) {
        pos = 0;
    } else {
        for (pos = node->count; (product.id < node->products[pos].id && pos > 1); pos--);
        if (product.id == node->products[pos].id) {
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (setValue(product, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            insertNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Insert a product
void insert(Product product) {
    int flag;
    Product i;
    BTreeNode *child;

    flag = setValue(product, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

// Search for a product
void search(Product *product, int id, BTreeNode *node) {
    int pos;
    if (!node) {
        printf("Product not found\n");
        return;
    }

    if (id < node->products[1].id) {
        pos = 0;
    } else {
        for (pos = node->count; (id < node->products[pos].id && pos > 1); pos--);
        if (id == node->products[pos].id) {
            *product = node->products[pos];
            return;
        }
    }
    search(product, id, node->link[pos]);
}

// Delete a product
void delete (Product product, BTreeNode *node) {
    printf("Deletion operation is not yet implemented\n");
}

// Print the B-tree
void print(BTreeNode *node) {
    int i;
    if (node) {
        for (i = 0; i < node->count; i++) {
            print(node->link[i]);
            printf("ID: %d | Name: %s | Price: %.2f | Stock: %d | Category: %s | Description: %s\n",
                   node->products[i + 1].id, node->products[i + 1].name, node->products[i + 1].price,
                   node->products[i + 1].stock, node->products[i + 1].category, node->products[i + 1].description);
        }
        print(node->link[i]);
    }
}

int main() {
    Product p1 = {1, "Laptop", 1000.0, 10, "Electronics", "High performance laptop"};
    Product p2 = {2, "Phone", 500.0, 20, "Electronics", "Smartphone with 4GB RAM"};
    Product p3 = {3, "Tablet", 300.0, 15, "Electronics", "Tablet with 10 inch display"};
    Product p4 = {4, "Monitor", 150.0, 25, "Electronics", "24 inch monitor"};
    Product p5 = {5, "Keyboard", 30.0, 50, "Accessories", "Mechanical keyboard"};

    root = NULL;
    
    insert(p1);
    insert(p2);
    insert(p3);
    insert(p4);
    insert(p5);

    printf("B-tree after insertion:\n");
    print(root);

    Product searchResult;
    search(&searchResult, 3, root);
    printf("\nSearch result:\nID: %d | Name: %s | Price: %.2f | Stock: %d | Category: %s | Description: %s\n",
           searchResult.id, searchResult.name, searchResult.price,
           searchResult.stock, searchResult.category, searchResult.description);

    return 0;
}
