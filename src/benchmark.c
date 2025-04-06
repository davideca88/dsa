#include"../include/benchmark.h"

// código mais otimizado do mundo feito pelo mr.PAA e o Fábio Akita

/*
Benchmark para busca binária e sequencial (vetor com tamanho fixo) - questão 01-02
Funcionamento: A questão 02 especifica que o mesmo vetor utilizado para s_seq deve ser usado para
as execuções em lista.

*Função: Recebe um Vector v e keys, tamanho do vetor analisado, repetições, nome do arquivo a ser gerado, método(s_seq ou b_seq)
*/
void bm_vec_fix(Vector v, Vector keys, int len, int rep, const char* file_name, search method){
    FILE* file = fopen(file_name, "w");
    if (file == NULL)
    {
        printf("error creating file");
        return;
    }

    fprintf(file, "Execucao, tempo(s), pos, valor\n");

    clock_t beg, end;
    double times[rep];
    double sum = 0.0;

    for (unsigned i = 0; i < rep; i++)
    {
        int key = keys[i];

        beg = clock();
        method(v, len, key);
        end = clock();

        double time = ((double)(end-beg))/CLOCKS_PER_SEC;
        times[i] = time;
        sum += time;

        fprintf(file, "%d,     %.6f,  %d,  %d\n", i+1, time, key, v[key]);
    }

    double average = sum/rep;
    double variance = 0.0;

    for (unsigned i = 0; i < rep; i++)
    {
        variance += pow(times[i]-average,2);
    }

    double s_dev = sqrt(variance/(rep-1));

    fprintf(file,"media: %.6f\n",average);
    fprintf(file,"desvio padrao: %.7f\n", s_dev);

    fclose(file);
    printf("Arquivo salvo\n");
}
/*
Função: recebe tamanho inicial do vetor; de quanto em quanto ele cresce; 
tamanho máximo; repetições; nome do arquivo; 1-ordenado / 0-desordenado; método(s_seq ou b_seq) 
*/
void bm_vec_inc(int initial_size, int step, int max, int rep, const char* name, int ordered, search method){
    FILE *fd = fopen(name,"w");
    if (fd == NULL)
    {
        printf("error creating file");
        return;
    }
    int j = 1;
    fprintf(fd, "Execucao, tempo(s), pos, valor,  tamanho do vetor\n");

    for (int size = initial_size; size <= max; size = (step == 0 ? max+1 : size + step))
    {
        Vector v = new_vector(size);
        Vector keys = new_vector(rep);
        
        clock_t beg, end;

        if (ordered)
        {
            sorted_arr(v,size);
        }else{
            randomize(v,size);
        }

        s_keys(keys,size,rep);

        for (int i = 0; i < rep; i++)
        {
            int key = v[keys[i]];
            beg = clock();
            method(v, size, key);
            end = clock();
    
            double time = ((double)(end-beg))/CLOCKS_PER_SEC;
    
            fprintf(fd, "%d,     %.6f,  %d,  %d,  %d\n", j++, time, keys[i], v[keys[i]], size);
        }
        // TODO necessário?
        delete_vector(v);
        delete_vector(keys);
    }

    fclose(fd);
    printf("Arquivo salvo\n");
}
/*
Função: recebe uma lista; recebe vetor a ser analisado; vetor de chaves; tamanho do vetor; repetições; nome do arquivo
*/
void bm_listvec_fix(List l, Vector v, Vector keys, int len, int rep, const char* name){
    FILE *fd = fopen(name, "w");
    if (fd == NULL) {
        printf("Error creating file\n");
        return;
    }

    array_to_list(l, v, len);

    fprintf(fd, "Execucao,      pos,       valor,     tempo_vetor(s),      tempo_lista(s)\n");

    clock_t beg, end;
    double times_vec[rep];
    double times_list[rep];
    double sum_vec = 0.0;
    double sum_list = 0.0;

    for (unsigned i = 0; i < rep; i++) {
        int key = keys[i];

        beg = clock();
        s_search(v, len, key);
        end = clock();
        double t_vec = ((double)(end - beg)) / CLOCKS_PER_SEC;

        beg = clock();
        ls_search(l, key);
        end = clock();
        double t_list = ((double)(end - beg)) / CLOCKS_PER_SEC;

        times_vec[i] = t_vec;
        times_list[i] = t_list;
        sum_vec += t_vec;
        sum_list += t_list;

        fprintf(fd, "%d,     %d,      %d,      %.6f,      %.6f\n", i + 1, key, v[key], t_vec, t_list);
    }

    double avg_vec = sum_vec / rep;
    double avg_list = sum_list / rep;
    double var_vec = 0.0, var_list = 0.0;

    for (unsigned i = 0; i < rep; i++) {
        var_vec += pow(times_vec[i] - avg_vec, 2);
        var_list += pow(times_list[i] - avg_list, 2);
    }

    double sd_vec = sqrt(var_vec / (rep - 1));
    double sd_list = sqrt(var_list / (rep - 1));

    fprintf(fd, "\nMédia vetor: %.6f\n", avg_vec);
    fprintf(fd, "Desvio padrão vetor: %.7f\n", sd_vec);
    fprintf(fd, "Média lista: %.6f\n", avg_list);
    fprintf(fd, "Desvio padrão lista: %.7f\n", sd_list);

    fclose(fd);
    printf("Arquivo salvo\n");
}

/*
Função: recebe tamanho inicial; valor de incremento a cada iteração; tamanho máximo do vetor; repetições; nome do arquivo
*/
void bm_listvec_inc(int initial_size, int step, int max, int rep, const char* name){
    FILE *fd = fopen(name,"w");
    if (fd == NULL)
    {
        printf("error creating file");
        return;
    }
    int j = 1;
    fprintf(fd, "Execucao, pos, valor, tempo_vetor(s), tempo_lista(s),  tamanho\n");

    for (int size = initial_size; size <= max; size = (step == 0 ? max+1 : size + step))
    {
        Vector v = new_vector(size);
        Vector keys = new_vector(rep);
        List l = new_list();
        
        clock_t beg, end;

        randomize(v,size);
        array_to_list(l,v,size);
        s_keys(keys,size,rep);

        for (int i = 0; i < rep; i++)
        {
            int key = v[keys[i]];
            
            beg = clock();
            s_search(v, size, key);
            end = clock();
    
            double t_vec = ((double)(end-beg))/CLOCKS_PER_SEC;

            beg = clock();
            ls_search(l, key);
            end = clock();
            double t_list = ((double)(end - beg)) / CLOCKS_PER_SEC;
    
            fprintf(fd, "%d,   %d,  %d,  %.6f,    %.6f,  %d\n", j++, keys[i], v[keys[i]], t_vec, t_list, size);
        }
        // TODO necessário?
        delete_vector(v);
        delete_vector(keys);
        delete_list(l);
    }
    fclose(fd);
    printf("Arquivo salvo\n");
}

// Função: recebe tamanho inicial do vetor; valor de incremento a cada iteração; tamanho máximo do vetor; repetições; nome do arquivo
void bm_sortalg(int initial_size, int step, int max, int rep, const char*name){
    FILE *fd = fopen(name, "w");
    if (fd == NULL) {
        printf("Error creating file\n");
        return;
    }

    int j = 1;
    clock_t beg, end;

    fprintf(fd, "Rodada,    Tamanho,    Bubble(s),      Insertion(s),      Selection(s),      Quick(s),       Quickv2(s),      Merge(s)\n");

    for (int size = initial_size; size <= max; size = (step == 0 ? max+1 : size + step))
    {
        for (int i = 0; i < rep; i++)
        {
            Vector v = new_vector(size);
            Vector copy = new_vector(size);
        
            randomize(v, size);

            copy_vec(v, copy, size);
            beg = clock(), end = (b_sort(copy,size), clock());
            double t_bubble = ((double)(end-beg))/CLOCKS_PER_SEC;

            copy_vec(v, copy, size);
            beg = clock(), end = (i_sort(copy,size), clock());
            double t_insertion = ((double)(end-beg))/CLOCKS_PER_SEC;

            copy_vec(v, copy, size);
            beg = clock(), end = (s_sort(copy,size), clock());
            double t_selection = ((double)(end-beg))/CLOCKS_PER_SEC;

            copy_vec(v, copy, size);
            beg = clock(), end = (q_sort(copy,size), clock());
            double t_qsort = ((double)(end-beg))/CLOCKS_PER_SEC;

            copy_vec(v, copy, size);
            beg = clock(), end = (q_sortv2(copy,size), clock());
            double t_qsort2 = ((double)(end-beg))/CLOCKS_PER_SEC;

            copy_vec(v, copy, size);
            beg = clock(), end = (m_sort(copy,size), clock());
            double t_merge = ((double)(end-beg))/CLOCKS_PER_SEC;

            fprintf(fd, "%d,            %d,     %.6f,     %.6f,            %.6f,     %.6f,     %.6f,     %.6f\n", j++, size, t_bubble, t_insertion, t_selection, t_qsort, t_qsort2, t_merge);
        
            // TODO necessário? v2
            delete_vector(v);
            delete_vector(copy);
        }        
    }
    fclose(fd);
    printf("Arquivo salvo\n");
}

void s_keys(Vector keys, int len, int rep) {
    Vector v = new_vector(len);
    for (int i = 0; i < len; i++) {
        v[i] = i;
    }

    for (int i = len - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    for (int i = 0; i < rep; i++) {
        keys[i] = v[i];
    }

    v = delete_vector(v);
}
