#include <stdio.h>
#include <stdlib.h>

int transform_name(const char *name)
{
    int sum = 0;
    int i = 0;
    while(name[i] != '\0'){
        sum += (i+1) * (i+1) * ((int)name[i]);
        i++;
    }
    return sum;
}

int** initialize_storage(int IA_size, int DA_size, int** DA_sizes)
{
    int** storage = (int**)malloc(IA_size * sizeof(int*));
    int i, j;
    for(i = 0; i < IA_size; i++){
        storage[i] = (int*)malloc(DA_size * sizeof(int));
        for(j = 0; j < DA_size; j++){
            storage[i][j] = 0;
        }
    }
    *DA_sizes = (int*)malloc(IA_size * sizeof(int));
    for(i = 0; i < IA_size; i++){
        (*DA_sizes)[i] = DA_size;
    }
    return storage;
}

void print_storage(int** storage, int IA_size, int* DA_sizes){
    int i, j;
    for(i = 0; i < IA_size; i++){
        printf("%d -> ", i);
        for(j = 0; j < DA_sizes[i]; j++){
            if(j < DA_sizes[i] - 1){
                printf("%d ", storage[i][j]);
            } 
            else{
                printf("%d", storage[i][j]);
            }
        }
        printf("\n");
    }
}

void insert(int** storage, int IA_size, const char* name, int* DA_sizes){
    int name_code = transform_name(name);
    int index = (name_code % IA_size);
    int sayac = 0;
    int new_DA_size, i;
    int* new_row;

    if (DA_sizes[index] > 0){
        while(sayac < DA_sizes[index] && storage[index][sayac] != 0){
            sayac++;
        }

        if(sayac < DA_sizes[index]){
            storage[index][sayac] = name_code;
        }
        else{
            new_DA_size = DA_sizes[index] * 2;
            new_row = (int*)realloc(storage[index], new_DA_size * sizeof(int));
            if(new_row){
                storage[index] = new_row;
                for(i = DA_sizes[index]; i < new_DA_size; i++){
                    storage[index][i] = 0;
                }
                storage[index][DA_sizes[index]] = name_code;
                DA_sizes[index] = new_DA_size;
            } 
        }
    }
}

void insert2(int** storage, int IA_size, int name_code, int* DA_sizes)
{
    int index = (name_code % IA_size);
    int sayac = 0;
    int new_DA_size, i;
    int* new_row;

    if(DA_sizes[index] > 0){
        while(sayac < DA_sizes[index] && storage[index][sayac] != 0){
            sayac++;
        }

        if(sayac < DA_sizes[index]){
            storage[index][sayac] = name_code;
        }
        else{
            new_DA_size = DA_sizes[index] * 2;
            new_row = (int*)realloc(storage[index], new_DA_size * sizeof(int));
            if(new_row){
                storage[index] = new_row;
                for(i = DA_sizes[index]; i < new_DA_size; i++){
                    storage[index][i] = 0;
                }
                storage[index][DA_sizes[index]] = name_code;
                DA_sizes[index] = new_DA_size;
            } 
        }
    }
}

void fill_new_storage(int** storage, int IA_size, int** new_storage, int *DA_sizes, int** new_DA_sizes)
{
    int i, j;
    for(i = 0; i < IA_size; i++){
        for(j = 0; j < DA_sizes[i]; j++){
            if(storage[i][j] != 0){
                insert2(new_storage, IA_size * 2, storage[i][j], *new_DA_sizes);
            }
        }
    }
}

void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes)
{
    int total_DA_size = 0;
    int new_IA_size, i;
    int* new_DA_sizes;
    int** new_storage;
    
    for(i = 0; i < (*IA_size); i++){
        total_DA_size += (*DA_sizes)[i];
    }
    
    if(((*IA_size) * DA_size * 1.5) <= total_DA_size){
        new_IA_size = (*IA_size) * 2;
        new_storage = initialize_storage(new_IA_size, DA_size, &new_DA_sizes);
        fill_new_storage(*storage, *IA_size, new_storage, *DA_sizes, &new_DA_sizes);
        
        for(i = 0; i < *IA_size; i++){
            free((*storage)[i]);
        }
        
        free(*storage);
        free(*DA_sizes);
        
        *IA_size = new_IA_size;
        *storage = new_storage;
        *DA_sizes = new_DA_sizes;
    }
}


