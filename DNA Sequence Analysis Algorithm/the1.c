#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct CodonTable {
    char codon[4];
    char aminoacid;
};

struct CodonTable codon_table[] = {
    {"AUA", 'i'}, {"AUC", 'i'}, {"AUU", 'i'}, {"AUG", 'm'},
    {"ACA", 't'}, {"ACC", 't'}, {"ACG", 't'}, {"ACU", 't'},
    {"AAC", 'n'}, {"AAU", 'n'}, {"AAA", 'k'}, {"AAG", 'k'},
    {"AGC", 's'}, {"AGU", 's'}, {"AGA", 'r'}, {"AGG", 'r'},
    {"CUA", 'l'}, {"CUC", 'l'}, {"CUG", 'l'}, {"CUU", 'l'},
    {"CCA", 'p'}, {"CCC", 'p'}, {"CCG", 'p'}, {"CCU", 'p'},
    {"CAC", 'h'}, {"CAU", 'h'}, {"CAA", 'q'}, {"CAG", 'q'},
    {"CGA", 'r'}, {"CGC", 'r'}, {"CGG", 'r'}, {"CGU", 'r'},
    {"GUA", 'v'}, {"GUC", 'v'}, {"GUG", 'v'}, {"GUU", 'v'},
    {"GCA", 'a'}, {"GCC", 'a'}, {"GCG", 'a'}, {"GCU", 'a'},
    {"GAC", 'd'}, {"GAU", 'd'}, {"GAA", 'e'}, {"GAG", 'e'},
    {"GGA", 'g'}, {"GGC", 'g'}, {"GGG", 'g'}, {"GGU", 'g'},
    {"UCA", 's'}, {"UCC", 's'}, {"UCG", 's'}, {"UCU", 's'},
    {"UUC", 'f'}, {"UUU", 'f'}, {"UUA", 'l'}, {"UUG", 'l'},
    {"UAC", 'y'}, {"UAU", 'y'}, {"UAA", '_'}, {"UAG", '_'},
    {"UGC", 'c'}, {"UGU", 'c'}, {"UGA", '_'}, {"UGG", 'w'}
};

int main(){
    char input[6000];
    char dna[3005];
    char protein[2905];
    char right_aminoacid_2,right_aminoacid_3, right_aminoacid_5, right_aminoacid_6;
    int dot_count = 0;
    int dot_count_2 = 0;
    int input_index = 0;
    int dna_index = 0;
    int protein_index = 0;
    char mrna[3005];
    int i, j, k, l, m, s, d, b, e, a, y, r, p, n, u, f;
    int mrna_length, dna_length;
    int protein_length;
    int indice_1, indice_2, indice_3, indice_4;
    int struct_length = 64;

    char codon_seq_triple[1000][4];
    int num_triplecodons = 0;

    char codon_seq_triple_2[1000][4];
    int num_triplecodons_2 = 0;

    char codon_seq_one[3000][4];
    int num_onecodons = 0;

    char codon_seq_one_2[3000][4];
    int num_onecodons_2 = 0;    

    char aminoacid_seq[1000];
    int num_correct_amino_acids = 0;

    char last_three[4];

    int mismatch_indices[1];
    int num_mismatches = 0;

    int mismatch_indices_2[2];
    int num_mismatches_2 = 0;

    int mismatch_indices_3[1];
    int num_mismatches_3 = 0;

    int mismatch_indices_4[1];
    int num_mismatches_4 = 0;

    while (input_index < 6000) {
        scanf("%c", &input[input_index]);
        if (input[input_index] == '.') {
            dot_count++;
            if (dot_count == 2) {
                break;
            }
        }
        input_index++;
    }

    for (i = 0; i < input_index; i++) {
        if (input[i] == '\n'){
            continue;
        }
        else if (input[i] == ' '){
            continue;
        }
        else if (input[i] == '.'){
            dot_count_2++;
        }
        else if (dot_count_2 == 2){
            break;
        }
        else if (input[i] >= 'a' && input[i] <= 'z'){
            protein[protein_index++] = input[i];
        } 
        else if (input[i] >= 'A' && input[i] <= 'Z'){
            dna[dna_index++] = input[i];
        }
    }

    dna[dna_index] = '\0';
    protein[protein_index] = '\0';

    dna_length = strlen(dna);    

    for (i = 0; i < dna_length; i++) {
        switch (dna[i]) {
            case 'A':
                mrna[i] = 'U';
                break;
            case 'T':
                mrna[i] = 'A';
                break;
            case 'G':
                mrna[i] = 'C';
                break;
            case 'C':
                mrna[i] = 'G';
                break;
            default:
                mrna[i] = dna[i];
                break;
        }
    }
    
    mrna[dna_length] = '\0';

    memcpy(last_three, &mrna[dna_length-3], 3);
    last_three[3] = '\0';

    mrna_length = strlen(mrna);

    protein_length = strlen(protein);

    for(i = 0; i <= mrna_length; i += 3){
        codon_seq_triple[num_triplecodons][0] = mrna[i];
        codon_seq_triple[num_triplecodons][1] = mrna[i+1];
        codon_seq_triple[num_triplecodons][2] = mrna[i+2];
        codon_seq_triple[num_triplecodons][3] = '\0';
        num_triplecodons++;
    }

    for(l = 0; l < mrna_length - 2; l += 1){
        codon_seq_one[num_onecodons][0] = mrna[l];
        codon_seq_one[num_onecodons][1] = mrna[l+1];
        codon_seq_one[num_onecodons][2] = mrna[l+2];
        codon_seq_one[num_onecodons][3] = '\0';
        num_onecodons++;
    }

    for(j = 0; j < num_triplecodons; j++){
        char* controller_codon = codon_seq_triple[j];
        for(k = 0; k < struct_length; k++){
            if(strcmp(controller_codon, codon_table[k].codon) == 0){
                char right_aminoacid = codon_table[k].aminoacid;
                aminoacid_seq[num_correct_amino_acids++] = right_aminoacid;
            }   
        }
    } 

    for(m = 0; m < protein_length - 1; m++){
        if(protein[m] == aminoacid_seq[m]){
            continue;;
        }
        else{
            mismatch_indices[num_mismatches++] = 3 * m;
            break;
        }
    }

    indice_1 = mismatch_indices[0];

    
    for(s = mismatch_indices[0]; s < mrna_length - 6; s++){
        char* controller_codon_2 = codon_seq_one[s];
        char* controller_codon_3 = codon_seq_one[s+3];
        for(d = 0; d < struct_length; d++){
            if(strcmp(controller_codon_2, codon_table[d].codon) == 0){
                right_aminoacid_2 = codon_table[d].aminoacid;
            }
            if(strcmp(controller_codon_3, codon_table[d].codon) == 0){
                right_aminoacid_3 = codon_table[d].aminoacid;           
            }
        }
        if(right_aminoacid_2 == protein[mismatch_indices[0]/3] && right_aminoacid_3 == protein[(mismatch_indices[0]/3)+1]){
            mismatch_indices_2[num_mismatches_2++] = s-1;
        }
    }

    indice_2 = mismatch_indices_2[0];
    

    for(b = mismatch_indices_2[0] + 1; b < mrna_length - 2 ; b += 3){
        codon_seq_triple_2[num_triplecodons_2][0] = mrna[b];
        codon_seq_triple_2[num_triplecodons_2][1] = mrna[b+1];
        codon_seq_triple_2[num_triplecodons_2][2] = mrna[b+2];
        codon_seq_triple_2[num_triplecodons_2][3] = '\0';
        num_triplecodons_2++;
    }

    for(e = 0; e < num_triplecodons_2 && (mismatch_indices[0]/3) + e < protein_length; e++){
        char* controller_codon_4 = codon_seq_triple_2[e];
        for(a = 0; a < struct_length; a++){
            if(strcmp(controller_codon_4, codon_table[a].codon) == 0){
                char right_aminoacid_4 = codon_table[a].aminoacid;
                aminoacid_seq[num_correct_amino_acids++] = right_aminoacid_4;
                if(right_aminoacid_4 == protein[(mismatch_indices[0]/3) + e]){
                    continue;
                }
                else{
                    mismatch_indices_3[num_mismatches_3++] = mismatch_indices_2[0] + (e * 3) + 1;
                    break;
                }                
            }
        }
    }

    indice_3 = mismatch_indices_3[0];

    for(y = mismatch_indices_3[0]; y < mrna_length - 5 ; y++){
        char* controller_codon_5 = codon_seq_one[y];
        char* controller_codon_6 = codon_seq_one[y+3];
        for(u = 0; u < struct_length; u++){
            if(strcmp(controller_codon_5, codon_table[u].codon) == 0){
                right_aminoacid_5 = codon_table[u].aminoacid;
            }
        }
        for(f = 0; f < struct_length; f++){
            if(strcmp(controller_codon_6, codon_table[f].codon) == 0){
                right_aminoacid_6 = codon_table[f].aminoacid;
            }
        }
        if(right_aminoacid_5 == protein[(indice_3 - (indice_2 - indice_1 + 1))/3] && right_aminoacid_6 == protein[((indice_3 - (indice_2 - indice_1 + 1))/3)+1]){
            mismatch_indices_4[num_mismatches_4++] = y - 1;
            break;
        }
        else{
            continue;
        }
    }

    indice_4 = mismatch_indices_4[0];
    
    if(strcmp(last_three, "UAG") != 0 && strcmp(last_three, "UAA") != 0 && strcmp(last_three, "UGA") != 0) {
        printf("NONE");
    }

    else if(indice_1 > indice_2 || indice_2 > indice_3 || indice_3 > indice_4){
        printf("NONE");
    }
    
    else if(indice_1 == 0 || indice_2 == 0 || indice_3 == 0 || indice_4 == 0){
        printf("NONE");
    }
    else{
        printf("%d %d %d %d", indice_1, indice_2, indice_3, indice_4);
    
    }   
    return 0;
}