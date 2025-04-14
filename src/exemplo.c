#include "../include/benchmark.h"

int main(){
    srand(time(NULL));
    
    //**QUESTÃO 01**
    int len = 10000;
    int rep = 30;

    Vector svetor = new_vector(len);
    Vector bvetor = new_vector(len);
    Vector keys = new_vector(rep);

    randomize(svetor, len);
    sorted_arr(bvetor, len);
    s_keys(keys,len,rep);

    //Busca binária no vetor
    bm_vec_fix(bvetor,keys,len,rep,"questao01_buscabinaria.txt",b_search);

    //Busca sequencial no vetor
    s_keys(keys,len,rep);
    bm_vec_fix(svetor,keys,len,rep,"questao01_buscasequencial.txt",s_search);

    //**QUESTÃO 02**
    List l = new_list();
    s_keys(keys,len,rep);
    bm_listvec_fix(l,svetor,keys,len,rep,"questao02_listavetor.txt");

    //**QUESTÃO 03**
    bm_sortalg(100,0,100,10,"questao03_ordenacao.txt");

    //**QUESTÃO 05**

    //Busca binária no vetor crescente (ref: questão 01)
    bm_vec_inc(10000,10000,100000,1,"questao05_buscabinaria.txt",1,b_search);

    //Busca sequencial no vetor crescente (ref: questão 01)
    bm_vec_inc(10000,10000,100000,1,"questao05_buscasequencial.txt",0,s_search);

    //Busca sequencial no vetor x lista crescente (ref: questão 02)
    bm_listvec_inc(10000,10000,100000,1,"questao05_listavetor.txt");

    //Ordenação no vetor crescente (ref: questão 03)
    bm_sortalg(100000,0,100000,1,"questao05_ordenacao.txt");

    return 0;
}
