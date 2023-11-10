/*
ECE 220 MP10

partners: hyunwoo6, crjung2, awinick2

This C program is designed to handle sparse matrices using a linked list. Sparse
matrices are matrices where most of the elements are zero. Storing all these
zero values is inefficient, so this program stores only the non-zero elements
using the functions: load_tuples() which loads the text file into a sparse
matrix using a linked list data structure, gv_tuples() which retrieves the value
of a specific element in the sparse matrix, set_tuples() which sets the value of
a specific element in the sparse matrix, save_tuples() which saves the sparse
matrix to a text file, add_tuples() which adds two sparse matrices together,
mult_tuples() which multiplies two sparse matrices together,
destroy_tuples() which deallocates the memory used by a sparse matrix.
*/
#include <stdio.h>
#include <stdlib.h>

#include "sparsemat.h"

/*
This function reads a sparse matrix from a file. The file should start with two
numbers representing the dimensions of the matrix. The rest of the file should
contain the row index, column index, and value of each non-zero element in the
matrix. The function creates a linked list of these non-zero elements (tuples)
and returns a pointer to the head of the list. The linked list nodes are
dynamically allocated, so they should be freed when no longer needed.
*/
sp_tuples* load_tuples(char* input_file) {
    // Open file
    FILE* file;
    file = fopen(input_file, "r");

    // allocate memory for the matrix
    sp_tuples* tuples = malloc(sizeof(sp_tuples));
    // Read in row and col
    fscanf(file, "%d %d\n", &tuples->m, &tuples->n);
    // Set nz to zero and head to NULL
    tuples->nz = 0;
    tuples->tuples_head = NULL;

    // Read in each line
    int row, col;
    double value;
    while (fscanf(file, "%d %d %lf\n", &row, &col, &value) == 3) {
        set_tuples(tuples, row, col, value);
    }

    // Close file
    fclose(file);
    return tuples;
}
/*
This function retrieves the value of a specific element in the sparse matrix. It
traverses the linked list until it finds a tuple with the given row and column
indices. If it finds such a tuple, it returns its value. If it doesn't, it
returns 0, indicating that the element is zero (as it's a sparse matrix).
*/
double gv_tuples(sp_tuples* mat_t, int row, int col) {
    // Create Pointer to check each node starting from head
    sp_tuples_node* current = mat_t->tuples_head;
    while (current != NULL) {  // Check if we reached the end of the linked list
        if (current->row == row && current->col == col) {
            return current
                ->value;  // Found the desired row and col, return value
        }
        // If not found, check next node
        current = current->next;
    }
    return 0;  // No node with row and col, meaning zero value
}

/*
The push_tuple() helper function designed to add a new node to the linked list
of non-zero elements in the sparse matrix, or update an existing node. It takes
a double pointer to a sp_tuples_node (**node), and the row index, column index,
and value of the element to be added or updated. If the node pointer is NULL, it
creates a new node, sets its fields, and returns 1. If the node pointer is not
NULL and the node's indices match the given indices, it updates the node's value
and returns 0.
*/
int push_tuple(sp_tuples_node** node, int row, int col, double value) {
    // check if it reached the end
    if (*node == NULL) {
        // create a new node
        *node = malloc(sizeof(sp_tuples_node));
        (*node)->col = col;
        (*node)->row = row;
        (*node)->value = value;
        (*node)->next = NULL;
        return 1;
    }
    // check if an existing node is found
    if ((*node)->row == row && (*node)->col == col) {
        // replace the value
        (*node)->value = value;
        return 0;
    }
    // else insert in the correct posistion
    if (((*node)->row == row && (*node)->col > col) || (*node)->row > row) {
        // create a new node and insert it before the current node
        sp_tuples_node* newNode = malloc(sizeof(sp_tuples_node));
        newNode->next = *node;
        *node = newNode;
        newNode->col = col;
        newNode->row = row;
        newNode->value = value;
        return 1;
    }
    // recursively move onto the next node
    return push_tuple(&((*node)->next), row, col, value);
}
/*
The pop_tuple() helper function is designed to remove a node from the linked
list of non-zero elements in the sparse matrix. It takes a double pointer to a
sp_tuples_node (**node), and the row and column indices of the element to be
removed. If the node pointer is NULL, it returns 0, indicating that the end of
the list has been reached without finding the node. If the node's indices match
the given indices, it removes the node by updating the pointer to skip over it,
and returns 1. If neither condition is met, it recursively calls itself with the
next field of the current node.
*/
int pop_tuple(sp_tuples_node** node, int row, int col) {
    // check if it reached the end
    if (*node == NULL) {
        return 0;
    }
    // check if an existing node is found
    if ((*node)->row == row && (*node)->col == col) {
        *node = (*node)->next;
        return 1;
    }
    return pop_tuple(&((*node)->next), row,
                     col);  // recursively move onto the next node
}
/*
The set_tuples() function is designed to set the value of a specific element in
the sparse matrix. It takes a pointer to a sp_tuples (*mat_t), and the row
index, column index, and value of the element to be set. If the value is zero,
it calls pop_tuple() to remove the corresponding node from the linked list, and
decrements the nz counter if a node is removed. If the value is not zero, it
calls push_tuple() to add a new node to the linked list or update an existing
node, and increments the nz counter if a new node is adde
*/
void set_tuples(sp_tuples* mat_t, int row, int col, double value) {
    // check if the value is zero
    if (value == 0) {
        // if it is, delete the node
        if (pop_tuple(&mat_t->tuples_head, row, col))
            mat_t->nz--;  // decrement nz counter if we delete an item
    } else {
        // else insert the value
        if (push_tuple(&mat_t->tuples_head, row, col, value))
            mat_t->nz++;  // increment only if the item has been inserted. Not
                          // replaced.
    }
}
/*
The save_tuples() function is designed to write the sparse matrix to a file. It
takes a filename and a pointer to a sp_tuples (*mat_t). It opens the file for
writing, writes the dimensions of the matrix, and then writes the row index,
column index, and value of each non-zero element in the matrix. The non-zero
elements are written in the order they appear in the linked list. After writing
all the elements, it closes the file.
*/
void save_tuples(char* file_name, sp_tuples* mat_t) {
    // Open file
    FILE* file;
    file = fopen(file_name, "w");
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);  // Print row col
    sp_tuples_node* current =
        mat_t->tuples_head;    // Set current starting with head
    while (current != NULL) {  // Until Node is at the end
        // Print out each node with tuple (row,col,val)
        fprintf(file, "%d %d %f\n", current->row, current->col, current->value);
        current = current->next;  // Next node
    }
    // Close file
    fclose(file);
}
/*
The add_tuples() function is designed to add two sparse matrices together. It
takes two pointers to sp_tuples (*matA and *matB). If the dimensions of the
matrices don't match, it returns NULL. Otherwise, it creates a new sp_tuples for
the result, initializes it with the same dimensions and an empty linked list,
and then iterates through the linked lists of matA and matB. For each non-zero
element in matA and matB, it adds the values together and uses set_tuples() to
set the corresponding element in the result. The function returns a pointer to
the result.
*/
sp_tuples* add_tuples(sp_tuples* matA, sp_tuples* matB) {
    // if the dimentions dont match, return NULL
    if (matA->m != matB->m || matA->n != matB->n) {
        return NULL;
    }

    // Create new matrix for the return matrix
    sp_tuples* retmat = malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;
    retmat->tuples_head = NULL;

    // Create pointers to iterate through both matrices
    sp_tuples_node* currentA = matA->tuples_head;
    sp_tuples_node* currentB = matB->tuples_head;

    // Iterate through matA
    while (currentA != NULL) {
        // Set the value of the return matrix to the sum of the two matrices at
        // the givn row and col
        set_tuples(
            retmat, currentA->row, currentA->col,
            currentA->value + gv_tuples(matB, currentA->row, currentA->col));
        currentA = currentA->next;
    }
    // Iterate through matB
    while (currentB != NULL) {
        // Set the value of the return matrix to the sum of the two matrices at
        // the givn row and col
        set_tuples(
            retmat, currentB->row, currentB->col,
            currentB->value + gv_tuples(matA, currentB->row, currentB->col));
        currentB = currentB->next;
    }
    return retmat;
}

// sp_tuples *mult_tuples(sp_tuples *matA, sp_tuples *matB)
// {
//     return retmat;
// }

/*
The destroy_tuples() function is designed to deallocate the memory used by a
sparse matrix. It takes a pointer to a sp_tuples (*mat_t). It creates two
pointers, current and next, to traverse the linked list of non-zero elements. It
iterates through the linked list, freeing each node and moving to the next one.
After freeing all the nodes, it frees the sp_tuples itself. This function is
used to prevent memory leaks when a sparse matrix is no longer needed.
*/
void destroy_tuples(sp_tuples* mat_t) {
    // Create pointer for current node and temp pointer of next node
    sp_tuples_node* current = mat_t->tuples_head;
    sp_tuples_node* next;
    // Iterate through all nodes
    while (current != NULL) {
        next = current->next;  // Store next node as the one after current
        free(current);         // Free current node
        current = next;        // Set current node to next node
    }
    free(mat_t);  // Free matrix
    return;
}