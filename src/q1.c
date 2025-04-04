#include "../include/vector.h"

int main(){
    srand(time(NULL));

    int len = 10000;
    int rep = 30;
    Vector rv = new_vector(len);
    randomize(rv, len);
    Vector ov = new_vector(len);
    sorted_arr(ov, len);
    

    bm_search(rv, len, rep, "sseq.txt",s_search);
    bm_search(ov, len, rep, "bsearch.txt",b_search);
    return 0;
}