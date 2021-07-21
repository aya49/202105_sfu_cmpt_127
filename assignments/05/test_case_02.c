// insert all your other codes here to make this program work up here!


// this is a sample test case for assignment 05 task 02.
// in addition to testing the outputs, it also requires you to test behaviour.
//
// STEP 0: read the function requirements.
// STEP 1: FOR EACH TEST create MOCK INPUT and call function to test input/output.
// STEP 2: FOR EACH TEST evaluate OUTPUT or BEHAVIOUR with if/else statement(s) (or assert) and print out results.
//
// And yes! You can use the same mock inputs and function calls to test multiple things ;)
//
// Keep in mind that my test cases are very verbose and detailed
// as this is an example, you will develop your own style,
// and your company will have their own guidelines.
//
// I will insert STEP 1 and STEP 2 below in comments for each of my tests, notice a pattern!


// STEP 0: read the function requirements:
// 
//    INPUT: the pointer of a imgr_t variable im, a boolean expand_row, and an integer val.
//    OUTPUT:
//        Return IMGR_OK if successful.
//        Return IMGR_BADALLOC if realloc() failed.
//    BEHAVIOUR: use preallocation!
//        Append val to the end of the 2D array pixels in im 
//        to the index with the smallest row index, and 
//        then the smallest col index e.g. if both indices [3]
//        [15] and [5][1] are empty, we append the value to [3][15], 
//        since it has the smaller row index. 
//        A very simple search will allow you get this behaviour.
//        If there is no more room left and if
//            expand_row != 0, double the size of the rows.
//            expand_row = 0, double the size of the cols.
//        Both of the above cases should be tested in t0.c


int main(void) {

    // I need to create test cases for OUTPUT and BEHAVIOUR
    // as per the instructions.
    //
    // OUTPUT: test returns a) IMGR_OK and b) IMGR_BADALLOC
    // REQUIREMENT: test a) when no realloc is needed and b) when realloc is needed.
    //
    // notice that the a) and b) above corresponds 
    // to the 2 bullet points under OUTPUT and REQUIREMENT 
    // in your assignment requirement.

    // create a generic MOCK INPUT
    printf("02 creating MOCK INPUT test_im by calling imgr_create(1,1)\n");
    imgr_t* im_test = imgr_create(1,1);

    printf("02 testing behaviour\n");

    // STEP 1 -------------------------
    printf("02 => test case 01: no preallocation");
    res = imgr_append(im_test, 0, 1); // does not preallocate

    // STEP 2
    printf("02 => test case 01.1 behaviour: ");
    if (im_test->cols==1 && im_test->reserved_cols==1 && 
        im_test->rows==1 && im_test->reserved_rows==1) {
        printf("successful, does not change dimensions\n");
    } else {
        printf("unsuccessful, changes dimensions\n");
    }

    printf("02 => test case 01.2 behaviour: ");
    if (im_test->pixels[1][1]==1) {
        printf("successful, appends value\n");
    } else {
        printf("unsuccessful, value not appended appropriately\n");
    }

    // STEP 1 -------------------------
    printf("02 => test case 02: preallocation");
    res = imgr_append(im_test, 0, 2); // does preallocate

    // STEP 2
    printf("02 => test case 02.1 output: ");
    if (res != IMGR_OK && res != IMGR_BADALLOC) {
        printf("unrecognized function output");
    } else {
        if (res == IMGR_OK) {
            printf("successful preallocation! following tests should all be successful:\n");
        } else if (res == IMGR_BADALLOC) {
            printf("unsuccessful preallocation :( following tests should all be unsuccessful:\n");
        }

        printf("02 => test case 02.3 behaviour: ");
        if (im_test->cols==2 && im_test->reserved_cols==2 && 
            im_test->rows==1 && im_test->reserved_rows==1) {
            printf("successful, dimensions changed\n");
        } else {
            printf("unsuccessful, dimensions unchanged\n");
        }

        printf("02 => test case 02.4 behaviour: ");
        if (im_test->pixels[1][2]==2) {
            printf("successful, appends value\n");
        } else {
            printf("unsuccessful, value not appended appropriately\n");
        }

        // could you think of better mock inputs?
        // can you complete the test cases for when expand_row != 0? (not implemented above)
    }

    return 0;
}