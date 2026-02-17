int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    lowest_match(terms, nterms, "Mu");
    highest_match(terms, nterms, "Mu");
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Mu");
    //free allocated blocks here -- not required for the project, but good practice
    free(terms);
    free(answer);
    return 0;
}
