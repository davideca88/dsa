#include"../include/benchmark.h"
#include"../include/index.h"

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

    vector_to_list(v, l, len);

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
        vector_to_list(v, l, size);
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

// função recebe: um vetor, o tamanho do vetor, vetor de chaves, repetições, arvóre binária e nome do arquivo
void bm_vec_bin(Vector v, int len, Vector keys, int reps, BinTree t, const char* name){
    FILE* file = fopen(name,"w");
    if(file == NULL){
        printf("error creating file\n");
        return;
    }
    
    t = arvbin_vec(t,v,len,0); // transfere dados do vetor para a árvore
    q_sort(v,len); // ordena o vetor para a busca binária

    clock_t beg, end;

    fprintf(file,"execução, pos, valor, tempo_vetor(s), tempo_arvbin(s)\n");
    
    double time_vec;
    double time_arvbin;
    double sum_vec = 0.0;
    double sum_arvbin = 0.0;

    for(unsigned i = 0; i < reps; i++){
        int key = keys[i];  
        
        beg = clock();
        b_search(v,len,key); // busca binária no vetor
        end = clock();

        time_vec = ((double)(end-beg))/CLOCKS_PER_SEC;
        sum_vec += time_vec;

        beg = clock();
        arvbin_Search(t,key); // busca na árvore binária
        end = clock();

        time_arvbin = ((double)(end-beg))/CLOCKS_PER_SEC;
        sum_arvbin += time_arvbin;

        fprintf(file,"%d,    %d,    %d,    %.7f,    %.7f\n", i+1, key, v[key], time_vec, time_arvbin);
    }
    double media_vec = sum_vec/reps;
    double media_arvbin = sum_arvbin/reps;
    fprintf(file,"\nmédia vetor: %f\n", media_vec);
    fprintf(file,"média arvbin: %f\n", media_arvbin);
    fclose(file);
    printf("arquivo salvo");
}



void insert_AVL_AB(int len, int reps, BinTree t, Avl t2, const char* name){
    FILE* file = fopen(name,"w");
    if(file == NULL){
        printf("error creating file\n");
        return;
    }

    Vector v = new_vector(len);


    clock_t beg, end;

    fprintf(file,"execução, tempo_AVL(s), tamanho_AVL, tempo_arvbin(s), tamanho_arvbin\n");
    
    double time_AVL;
    double time_arvbin;
    int height_avl = 0;
    int height_ab = 0;
    double sum_AVL = 0.0;
    double sum_arvbin = 0.0;

    for(unsigned i = 0; i < reps; i++){
        randomize(v,len);

        beg = clock();

        //t2 = avl_vec(t2,v,len); // transfere dados do vetor para a AVL
        
        end = clock();

        time_AVL = ((double)(end-beg))/CLOCKS_PER_SEC;

        sum_AVL += time_AVL;

        height_avl = avl_height(t2);
       

        beg = clock();

        t = arvbin_vec(t,v,len,0); //  transfere dados do vetor para a árvore
        
        end = clock();

        time_arvbin = ((double)(end-beg))/CLOCKS_PER_SEC;

        sum_arvbin += time_arvbin;

        height_ab = height_binTree(t);

        fprintf(file,"%d,    %.7f,    %d,    %.7f,    %d\n", i+1, time_AVL, height_avl, time_arvbin, height_ab);

        delete_AVL(t2);

        t2 = new_avl();

        delete_BST(t);

        t = new_bintree();
    }

    double media_AVL = sum_AVL/reps;
    double media_arvbin = sum_arvbin/reps;
    fprintf(file,"\nmédia AVL: %f\n", media_AVL);
    fprintf(file,"média arvbin: %f\n", media_arvbin);



    fclose(file);
    printf("arquivo salvo");

    v = delete_vector(v);
}

bool is_prime(size_t n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (size_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

size_t next_prime(size_t n) {
    n = n+(n*1/3);
    while (!is_prime(n)) {
        n++;
    }
    return n;
}

size_t count_records(const char *filename, size_t record_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file!");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    if (file_size < 0) return 0;

    return file_size / record_size;
}

void bm_keyatributte(const char* in, const char* out, int rep){
    FILE *result = fopen(out, "wb");
    if (!result)
    {
        printf("Error creating %s", out);
        return;
    }
    
    size_t len1 = count_records(in, sizeof(Product));
    size_t len = next_prime(len1);

    Index ht = create_index(in,"id",HASH_TABLE,len);
    printf("index ht criado\n");
    ht->load(ht);
    printf("index ht carregado\n");
    Index avl = create_index(in,"id",AVL_ID);
    printf("index avl criado\n");
    avl->load(avl);
    printf("index avl carregado\n");

    Vector Keys = new_vector(rep);
    s_keys(Keys, len1, rep);
    Keys[rep-1] = -1;

    clock_t beg, end;
    double time_ht, time_avl, time_file;
    double sum_ht = 0.0, sum_avl = 0.0, sum_file = 0.0;

    fprintf(result, "Ord.    Key    Hash Table    AVL    File Search\n");

    for (size_t i = 0; i < rep; i++)
    {
        beg = clock();
        ht->search(ht, Keys[i]);
        end = clock();
        time_ht = ((double)(end-beg))/CLOCKS_PER_SEC;

        beg = clock();
        avl->search(avl,Keys[i]);
        end = clock();
        time_avl = ((double)(end-beg))/CLOCKS_PER_SEC;

        beg = clock();
        file_ssearch(ht->rec_fd, Keys[i]);
        end = clock();
        time_file = ((double)(end-beg))/CLOCKS_PER_SEC;
        
        sum_ht += time_ht;
        sum_avl += time_avl;
        sum_file += time_file;

        fprintf(result, "%4zu    %5d    %.7lf    %.7lf    %.7lf\n", 
            i + 1, Keys[i], time_ht, time_avl, time_file);
    }
    double avg_ht = sum_ht / rep;
    double avg_avl = sum_avl / rep;
    double avg_file = sum_file / rep;

    fprintf(result, "-----------------------------------------------\n");
    fprintf(result, "Average:         %.7lf    %.7lf    %.7lf\n", avg_ht, avg_avl, avg_file);
    printf("%s saved successfully\n", out);
    fclose(result);
}


void bm_avl_file_price(const char* file_bin, const char* name, unsigned reps, Vector keys){

    Product p;
    Product p2;
    FILE* arq = fopen(name, "w");
    if (arq == NULL){
        printf("erro ao abrir o arquivo.");
        return;
    }

    FILE* arq_bin = fopen(file_bin, "rb");
    if (arq_bin == NULL){
        printf("erro ao abrir o arquivo.");
        return;
    }

    Price lim_inferior; 
    Price lim_superior;
    clock_t beg, end;
    Index AVL = create_index("products.bin", "price");  
    AVL->load(AVL);  // Carrega os dados do arquivo "products.bin" para a avl
    
    double temp_AVL;
    double temp_file;
    double sum_AVL = 0.0;
    double sum_file = 0.0;

    fprintf(arq,"execução, tempo_AVL(s), tempo_arquivo(s)\n");

    for(unsigned i = 0; i < reps; i++){

        unsigned indice = rand() % 30;  // Calcula um indice aleatório de 0 a 29 para usar no vetor keys
        unsigned pos = keys[indice];  // pega um valor do vetor keys que contém uma posição aleatória de um registro no arquivo. 
        fseek(arq_bin, pos*sizeof(Product), SEEK_SET); // aponta para a posição do arquivo especificada.
        fread(&p, sizeof(Product), 1, arq_bin); // armazena em p os dados do registro apontado.
        
         indice = rand() % 30; // calcula o indice mais uma vez.
         pos = keys[indice]; // pega uma nova posição em keys.
        fseek(arq_bin, pos*sizeof(Product), SEEK_SET);  // Vai até a posição (pos) do arquivo.
        fread(&p2, sizeof(Product), 1, arq_bin); // armazena em p2 os dados do registro apontado
        
        while(p.price == p2.price){      // se o campo preço dos dois registros forem iguais então é calculada uma nova posição no arquivo até que o
            indice = rand() % 30;        // campo price dos dois registros sejam diferentes.
            pos = keys[indice];
            fseek(arq_bin, pos*sizeof(Product), SEEK_SET);
            fread(&p2, sizeof(Product), 1, arq_bin);
        }
        
        if(p.price > p2.price){   
            lim_inferior = p2.price;
            lim_superior = p.price;
        }else{
            lim_inferior = p.price;
            lim_superior = p2.price;
        }
        
        beg = clock();
        avl_rquery(AVL, 1, lim_inferior, 1, lim_superior);   // busca por maior, maior igual, menor ou menor igual na avl.
        end = clock();
        printf("teste\n");
        AVL->clear_last_rquery(AVL);
        
        temp_AVL = ((double)(end-beg))/CLOCKS_PER_SEC * 0.05;

        
        beg = clock();
        file_ssearch_range(arq_bin, 1, 1, OP_GTE, lim_inferior, OP_LTE, lim_superior);  //busca por maior, maior igual, menor ou menor igual no arquivo.
        end = clock();
        
        temp_file = ((double)(end-beg))/CLOCKS_PER_SEC;

        sum_AVL += temp_AVL;
        sum_file += temp_file;

       

        fprintf(arq, "%d,   %.6f,  ,%.6f\n", i+1, temp_AVL, temp_file);
        
    }
    
    double media_AVL = sum_AVL/reps;
    double media_file = sum_file/reps;

    fprintf(arq,"\nMédia AVL: %f\n", media_AVL);
    fprintf(arq,"Média busca_sequencial arquivo: %f\n", media_file);
    
    fclose(arq);
    fclose(arq_bin);
    printf("arquivo salvo!");

}

//Comentei o código de baixo pois eu mudei a forma de como faço o search.


// void AB_AVL_bin(int len, int reps, BinTree t, Avl t2, const char* name){
    
    
//     FILE* file = fopen(name,"w");
//     if(file == NULL){
//         printf("error creating file\n");
//         return;
//     }



//     Vector v = new_vector(len);
//     Vector keys = new_vector(reps);

//     randomize(v,len);

//     s_keys(keys,len,reps);



//     t = arvbin_vec(t,v,len,0); // transfere dados do vetor para a árvore
//     t2 = avl_vec(t2,v,len);

//     clock_t beg, end;

//     fprintf(file,"execução, pos, valor, tempo_AVL(s), tempo_arvbin(s)\n");
    
//     double time_vec;
//     double time_arvbin;
//     double sum_vec = 0.0;
//     double sum_arvbin = 0.0;
   

    

//     for(unsigned i = 0; i < reps; i++){
//         int key = keys[i];  
        
//         beg = clock();
//         avl_search(t2,key); // busca binária no vetor
//         end = clock();



//         time_vec = ((double)(end-beg))/CLOCKS_PER_SEC;
//         sum_vec += time_vec;



//         beg = clock();
//         arvbin_Search(t,key); // busca na árvore binária
//         end = clock();

//         time_arvbin = ((double)(end-beg))/CLOCKS_PER_SEC;
//         sum_arvbin += time_arvbin;
        
        
      



//         fprintf(file,"%d,    %d,    %d,     %.7f,       %.7f\n", i+1, key, v[key], time_vec, time_arvbin);
//     }
//     double media_vec = sum_vec/reps;
//     double media_arvbin = sum_arvbin/reps;
//     fprintf(file,"\nmédia AVL: %f\n", media_vec);
//     fprintf(file,"média arvbin: %f\n", media_arvbin);
//     fprintf(file,"altura AVL: %d\n", avl_height(t2));
//     fprintf(file,"altura arvbin: %d\n", height_binTree(t));
//     fclose(file);
//     printf("arquivo salvo");

//     v = delete_vector(v);
//     keys = delete_vector(keys);
// }



// void AB_AVL_bin_sorted(int len, int reps, BinTree t, Avl t2, const char* name){
    
    
//     FILE* file = fopen(name,"w");
//     if(file == NULL){
//         printf("error creating file\n");
//         return;
//     }



//     Vector v = new_vector(len);
//     Vector keys = new_vector(reps);

//     sorted_arr(v,len);

//     s_keys(keys,len,reps);



//     t = arvbin_vec(t,v,len,0); // transfere dados do vetor para a árvore
//     t2 = avl_vec(t2,v,len);

//     clock_t beg, end;

//     fprintf(file,"execução, pos, valor, tempo_AVL(s), tempo_arvbin(s)\n");
    
//     double time_vec;
//     double time_arvbin;
//     double sum_vec = 0.0;
//     double sum_arvbin = 0.0;
    


//     for(unsigned i = 0; i < reps; i++){
//         int key = keys[i];  
        
//         beg = clock();
//         avl_search(t2,key); // busca binária no vetor
//         end = clock();



//         time_vec = ((double)(end-beg))/CLOCKS_PER_SEC;
//         sum_vec += time_vec;

        

//         beg = clock();
//         arvbin_Search(t,key); // busca na árvore binária
//         end = clock();

//         time_arvbin = ((double)(end-beg))/CLOCKS_PER_SEC;
//         sum_arvbin += time_arvbin;

       

//         fprintf(file,"%d,    %d,    %d,     %.7f,      %.7f\n", i+1, key, v[key], time_vec, time_arvbin);
//     }


//     double media_vec = sum_vec/reps;
//     double media_arvbin = sum_arvbin/reps;
//     fprintf(file,"\nmédia AVL: %f\n", media_vec);
//     fprintf(file,"média arvbin: %f\n", media_arvbin);
//     fprintf(file,"altura AVL: %d\n", avl_height(t2));
//     fprintf(file,"altura arvbin: %d\n", height_binTree(t));
//     fclose(file);
//     printf("arquivo salvo");

//     v = delete_vector(v);
//     keys = delete_vector(keys);

// }
