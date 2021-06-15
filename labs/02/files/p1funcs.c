// returns the larger of the two arguments
int max(int i1, int i2) {
    
    // if int2 isn't the larger integer, then int1 is the larger integer
    if (i1 > i2) {
        larger = i1;
    }
    return larger;
}

// returns the smaller of the two arguments
int min( int i1, int i2) {
  int smaller = i2;
  if (i1 < i2) {
    smaller = i1;
  } 
  return smaller;
}
