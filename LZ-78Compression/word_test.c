uint8_t word1[5] = {104,101,108,108,111};
  uint64_t len = 5;
  uint8_t word2[5] = {119,111,114,108,100};
  //uint64_t len = 5;
  //for(uint8_t k = 0; k < 5; k++) {
    //printf("%c\n",word2[k]);
  //}
  Word *hello = word_create(word1, 5);
  Word *world = word_create(word2, 5);
  //word_print(world);
  Word *new1 = word_append_sym(world,115);
  //word_print(hello);
  //word_delete(hello);
  WordTable *wt = wt_create();
  //wt_print(wt);
 
  wt[2] = hello;
  wt[3] = world;
  wt[4] = new1;
  wt_reset(wt);
  wt_print(wt);
  wt_delete(wt);

  //word_print(new1);
  //word_delete(new1);
  //wt_reset(wt);
  //wt_print(wt);