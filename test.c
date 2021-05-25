&img.pixels == (void*)&img + 0 // `(void*)` signifies "pointer of unspecified type"
&img.cols == (void*)&img + sizeof(uint8_t*)
&img.rows == (void*)&img + sizeof(uint8_t*) + sizeof(unsigned int)