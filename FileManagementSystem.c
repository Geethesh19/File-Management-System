#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[100];
    int size;
    char type[20];
} File;

typedef struct Node {
    File info;
    struct Node* left;
    bool lthread;
    struct Node* right;
    bool rthread;
} Node;

typedef struct {
    Node* root;
} ThreadedBST;

Node* createNode(File file) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = file;
    newNode->left = NULL;
    newNode->lthread = true;
    newNode->right = NULL;
    newNode->rthread = true;
    return newNode;
}

Node* inSucc(Node* ptr) {
    if (ptr->rthread) {
        return ptr->right;
    }
    ptr = ptr->right;
    while (!ptr->lthread) {
        ptr = ptr->left;
    }
    return ptr;
}

Node* inPred(Node* ptr) {
    if (ptr->lthread) {
        return ptr->left;
    }
    ptr = ptr->left;
    while (!ptr->rthread) {
        ptr = ptr->right;
    }
    return ptr;
}

Node* caseA(Node* par, Node* ptr, ThreadedBST* tree) {
    if (!par) {
        tree->root = NULL;
    }
    else if (par->left == ptr) {
        par->lthread = true;
        par->left = ptr->left;
    }
    else {
        par->rthread = true;
        par->right = ptr->right;
    }
    free(ptr);
    return tree->root;
}

Node* caseB(Node* par, Node* ptr, ThreadedBST* tree) {
    Node* child = ptr->lthread ? ptr->right : ptr->left;

    if (!par) {
        tree->root = child;
    }
    else if (par->left == ptr) {
        par->left = child;
    }
    else {
        par->right = child;
    }

    Node* s = inSucc(ptr);
    Node* p = inPred(ptr);

    if (!ptr->lthread) {
        p->right = s;
    }
    else if (!ptr->rthread) {
        s->left = p;
    }

    free(ptr);
    return tree->root;
}

Node* caseC(Node* par, Node* ptr, ThreadedBST* tree) {
    Node* succ = ptr->right;
    Node* parsucc = ptr;

    while (!succ->lthread) {
        parsucc = succ;
        succ = succ->left;
    }

    ptr->info = succ->info;

    if (succ->lthread && succ->rthread) {
        tree->root = caseA(parsucc, succ, tree);
    }
    else {
        tree->root = caseB(parsucc, succ, tree);
    }

    return tree->root;
}

void displayFile(Node* node) {
    printf("\nFile Name: %s", node->info.name);
    printf("\nSize: %d KB", node->info.size);
    printf("\nType: %s\n", node->info.type);
}

void inorderTraversal(Node* node) {
    if (!node) {
        printf("\nTree is empty.\n");
        return;
    }

    Node* ptr = node;
    while (!ptr->lthread) {
        ptr = ptr->left;
    }

    while (ptr) {
        displayFile(ptr);
        ptr = inSucc(ptr);
    }
}

void insert(ThreadedBST* tree, File file) {
    Node* tmp = createNode(file);
    Node* ptr = tree->root;
    Node* par = NULL;

    while (ptr) {
        par = ptr;
        if (strcmp(file.name, ptr->info.name) == 0) {
            printf("\nFile \"%s\" already exists.\n", file.name);
            free(tmp);
            return;
        }
        if (strcmp(file.name, ptr->info.name) < 0) {
            if (!ptr->lthread) {
                ptr = ptr->left;
            }
            else {
                break;
            }
        }
        else {
            if (!ptr->rthread) {
                ptr = ptr->right;
            }
            else {
                break;
            }
        }
    }
    if (!par) {
        tree->root = tmp;
    }
    else if (strcmp(file.name, par->info.name) < 0) {
        tmp->left = par->left;
        tmp->right = par;
        par->lthread = false;
        par->left = tmp;
    }
    else {
        tmp->left = par;
        tmp->right = par->right;
        par->rthread = false;
        par->right = tmp;
    }
    printf("\nFile \"%s\" inserted successfully.\n", file.name);
}

void removeFile(ThreadedBST* tree, const char* fname) {
    Node* ptr = tree->root;
    Node* par = NULL;

    while (ptr) {
        if (strcmp(fname, ptr->info.name) == 0) {
            break;
        }
        par = ptr;
        if (strcmp(fname, ptr->info.name) < 0) {
            if (!ptr->lthread) {
                ptr = ptr->left;
            }
            else {
                break;
            }
        }
        else {
            if (!ptr->rthread) {
                ptr = ptr->right;
            }
            else {
                break;
            }
        }
    }

    if (!ptr || strcmp(ptr->info.name, fname) != 0) {
        printf("\nFile not found: \"%s\".\n", fname);
        return;
    }

    if (!ptr->lthread && !ptr->rthread) {
        tree->root = caseC(par, ptr, tree);
    }
    else if (!ptr->lthread || !ptr->rthread) {
        tree->root = caseB(par, ptr, tree);
    }
    else {
        tree->root = caseA(par, ptr, tree);
    }

    printf("\nFile \"%s\" deleted successfully.\n", fname);
}

void displayInorder(ThreadedBST* tree) {
    inorderTraversal(tree->root);
}

int main() {
    ThreadedBST tree = {NULL};
    int choice;
    File file;

    while (1) {
        printf("\nFile Management System\n");
        printf("1. Add File\n");
        printf("2. Delete File\n");
        printf("3. Display All Files (Inorder)\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter file name: ");
                scanf("%s", file.name);
                printf("Enter file size (in KB): ");
                scanf("%d", &file.size);
                printf("Enter file type: ");
                scanf("%s", file.type);
                insert(&tree, file);
                break;
            }
            case 2: {
                char fname[100];
                printf("Enter the file name to delete: ");
                scanf("%s", fname);
                removeFile(&tree, fname);
                break;
            }
            case 3: {
                displayInorder(&tree);
                break;
            }
            case 4: {
                printf("\nExiting...\n");
                return 0;
            }
            default: {
                printf("\nInvalid choice. Try again.\n");
            }
        }
    }
}s
