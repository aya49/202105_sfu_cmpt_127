// returns the larger of the two arguments
int max(int int1, int int2) {

    // let's assume int2 is the larger integer
    int larger = int2;
    
    // if int2 isn't the larger integer, then int1 is the larger integer
    if (int1 > int2) {
        larger = int1;
    }
    return larger;
}

// returns the smaller of the two arguments
int min( int int1, int int2) {
  int smaller = int2;
  if (int1 < int2) {
    smaller = int1;
  } 
  return smaller;
}
