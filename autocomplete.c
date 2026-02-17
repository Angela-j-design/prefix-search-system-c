#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//comparison function for qsort
int my_cmp_lexicographic(const void*s1, const void*s2){
    //change type
    term *struct_s1 =(term *)s1;
    term *struct_s2 =(term *)s2;
    int sign = strcmp(struct_s1->term, struct_s2->term);
    return sign;

}


void read_in_terms(term **terms, int *pnterms, char *filename){
    // also deal with the first line

    FILE *fp = fopen(filename,"r");
    if(fp ==NULL)return;
    //task 1: count the terms
    int term_number=0;
    char cur_line[100000];
    
    while(fgets(cur_line, 100000-1,fp) != NULL){
        if (cur_line[0] == '\n' || cur_line[0] == '\r' || cur_line[0] == '\0')
        continue;
        term_number++;
    }
    fclose(fp);
    *pnterms = term_number; //number of terms
  
    //task 2
    *terms = malloc(sizeof(term) * (*pnterms));
    //task 3: read all terms, and put in malloc "temrs"
    // use read_in_line
    fp = fopen(filename,"r");
    if(fp ==NULL)return;
    
    int n;
    fscanf(fp, "%d%*c", &n);   
    *pnterms = n;

    int i =0;
    for(i=0;i<*pnterms;i++){
        int r = fscanf(fp, "%lf %199[^\n]",
                   &(*terms)[i].weight,
                   (*terms)[i].term);
    if (r != 2) break; 
    int c;
     while ((c = fgetc(fp)) != '\n' && c != EOF) {}
}
    *pnterms = i;
        // char this_line[100000];
        // fgets(this_line,100000-1,fp);
        // //read a new line every single time
        // (*terms)[i] = read_in_line(this_line);

    fclose(fp);
    // for debug purpose, remember to delete!!
    //qsort
    qsort(*terms,*pnterms,sizeof(term),my_cmp_lexicographic);
} 

int lowest_match(term *terms, int nterms, char *substr){
    //nterms is the number of terms in terms
    //the way to make the run time->binary search on sorted array
    //strncmp
    //task1: let the term be in lexicographic order
    // no need , u canuse them directly
    //task2:
    //check to the most left 
    
    
    int left =0;
    int right = nterms -1;
    int cur_index = -1;
    while(left <= right){
        int mid = (left+right)/2;
        int cmp = strncmp((terms)[mid].term, substr,strlen(substr)); // MUST store it!!!

    if(cmp ==0){
        //continue the go left
        //find the index and take the smallest one
        cur_index = mid;
        right = mid -1;
    }else if(cmp <0){
        left = mid +1;
    }else{
        right = mid -1;
    }

    }
    
    return cur_index;
}


int highest_match(term *terms, int nterms, char *substr){
    // strncmp, and binary search
    // search for the highest term
    int left = 0;
    int right = nterms -1;
    int cur_last_index = -1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        int cmp = strncmp(terms[mid].term, substr, strlen(substr));
        if(cmp==0){
            cur_last_index = mid;
            left = mid +1;
        }else if(cmp<0){
            left = mid +1;
        }else{
            right = mid -1;
        }
    }
    return cur_last_index;   
}

int part4_cmp(const void *thing1, const void *thing2){
    const term *struct1 = thing1;
    const term *struct2 = thing2;
   
    if(struct1->weight < struct2->weight){
        return 1;
    }else if(struct1->weight > struct2->weight){
        return -1;
    }else{
        return 0;
    }
}

void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr){
    //// places the answers in answer
    int j=0;
    int i;
    int low = lowest_match(terms, nterms, substr);
    int high =  highest_match(terms, nterms, substr);

    if (low == -1 || high == -1 || high < low) {
    *answer = NULL;
    *n_answer = 0;
    return;
}

    *n_answer = high -low +1;
    *answer = (term *)malloc(sizeof(term) * (*n_answer));
    for(i = low; i<=high ; i++){
        (*answer)[j] = terms[i];
        j++;
    }

    //task 2: sort (*answer)
    qsort(*answer, *n_answer, sizeof(term),part4_cmp);
    
}


