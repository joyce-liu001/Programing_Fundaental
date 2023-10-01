//z5271698
// copy all of the values in source1 which are also found in source2 into destination
// return the number of elements copied into destination

int common_elements(int length, int source1[length], int source2[length], int destination[length]) {
    // PUT YOUR CODE HERE (you must change the next line!)
    int i1 = 0;
    int elements = 0;
    while (i1 < length) {
        int i2 = 0;
        while (i2 < length && i1 < length) {
            if (source1[i1] == source2[i2]) {
                destination[elements] = source1[i1];
                elements++;
                i1++;
                i2 = -1;
            }
            i2++;
        }
        i1++;
    }
    
    
    return elements;
}

// You may optionally add a main function to test your common_elements function.
// It will not be marked.
// Only your common_elements function will be marked.
