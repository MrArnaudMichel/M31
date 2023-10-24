//
// Created by arnau on 21/09/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double rand_base(){
    return rand()/(double )(RAND_MAX);
}

int de(int nb_face){
    return (int)(rand_base()*nb_face)+1;
}

void affiche_variabilite(int nb_face, int nb_lancer){
    int i;
    double tab[nb_face];
    for (i = 0; i < nb_face; i++){
        tab[i] = 0;
    }
    for (i = 0; i < nb_lancer; i++){
        tab[de(nb_face)-1]++;
    }

    for (i = 0; i < nb_face; i++){
        printf("--------");
    }
    printf("\n");
    for (i = 0; i < nb_face; i++){
        printf("| %.3f ", tab[i]/nb_lancer);
    }
    printf("|\n");
    for (i = 0; i < nb_face; i++){
        printf("--------");
    }
    printf("\n");
}

void with_replacement(unsigned int n, unsigned int N, unsigned int* drawing){
    int i;
    for (i = 0; i < N; i++){
        drawing[i] = (int)(rand_base()*n);
    }
}

void without_replacement(unsigned int n, unsigned int N, unsigned int* drawing){
    int i;
    int j;
    int k;
    int tab[n];
    for (i = 0; i < n; i++){
        tab[i] = i;
    }
    for (i = 0; i < N; i++){
        j = (int)(rand_base()*(n-i));
        drawing[i] = tab[j];
        for (k = j; k < n-i-1; k++){
            tab[k] = tab[k+1];
        }
    }
}

double yarbouough(int nb_tirage){
    // Calcul la probabilité d'obtenir une main de Yarbourough (une main de 13 carte contenant au moins une carte de valeur supérieur à 9)
    int i, j, k;
    int tab[52];
    int main[13];
    int nb_yarbourough = 0;
    for (i = 0; i < 52; i++){
        tab[i] = i;
    }
    for (i = 0; i < nb_tirage; i++){
        for (j = 0; j < 13; j++){
            k = (int)(rand_base()*(52-j));
            main[j] = tab[k];
            for (k = k; k < 52-j-1; k++){
                tab[k] = tab[k+1];
            }
        }
        for (j = 0; j < 13; j++){
            if (main[j]%13 > 9){
                nb_yarbourough++;
                break;
            }
        }
    }
    return (double)nb_yarbourough/nb_tirage;
}

char bernouilli(double p){
    if (rand_base() < p){
        return 1;
    }
    return 0;
}

unsigned int bernouilli_sheme(unsigned int n, double p, char *result){
    int i;
    unsigned int nb_success = 0;
    for (i = 0; i < n; i++){
        result[i] = bernouilli(p);
        if (result[i] == 1){
            nb_success++;
        }
    }
    return nb_success;
}

double* binomial_distribution(unsigned int n, double p){
    double* result = malloc((n+1)*sizeof(double));
    int i;
    for (i = 0; i < n+1; i++){
        result[i] = 0;
    }
    char* bernouilli_result = malloc(n*sizeof(char));
    unsigned int nb_success = bernouilli_sheme(n, p, bernouilli_result);
    result[nb_success] = 1;
    for (i = 0; i < n; i++){
        if (bernouilli_result[i] == 1){
            nb_success--;
        }
        result[nb_success] += 1;
    }
    for (i = 0; i < n+1; i++){
        result[i] /= n;
    }
    return result;
}

unsigned int geometric(double p){
    unsigned int i = 0;
    while (bernouilli(p) == 0){
        i++;
    }
    return i + 1;
}

double exp_density(double lambda){
    return lambda * exp(-lambda);
}



int main(int argc, char* argv[]){
    printf("%f\n", exp_density(atof(argv[1])));
    return 0;
}