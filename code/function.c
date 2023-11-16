//
// Created by arnau on 21/09/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "function.h"

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

double g_x(double x){
    return sqrt(1 - x*x);
}

double monteCarlo(int n){
    int somme = 0;
    for (int i = 0; i < n; ++i) {
        struct coordonnee coordonnee;
        coordonnee.x = rand_base();
        coordonnee.y = rand_base();
        if (coordonnee.y < g_x(coordonnee.x)){
            somme++;
        }
    }
    return (double)somme/n;
}

double monteCarlo2(int n){
    double somme = 0;
    for (int i = 0; i < n; ++i) {
        somme += g_x(rand_base());
    }
    return (double)somme/n;
}

double monteCarlo_Exp(double lambda, int n){
    // Calcul une valeur approché de la probabilité qu'une variable aléatoire suivant une loi exponentielle de paramètre lambda prenne une valeur entre 0 et 1, au moyen de tirage de n points.
    double somme = 0;
    for (int i = 0; i < n; ++i) {
        somme += exp_density(rand_base());
    }
    return (double)somme/n;
}

void standard_normal(double* sample){
    int i;
    for (i = 0; i < 12; i++){
        sample[i] = rand_base();
    }
    double somme = 0;
    for (i = 0; i < 12; i++){
        somme += sample[i];
    }
    somme -= 6;
    for (i = 0; i < 12; i++){
        sample[i] = somme;
    }
}

double* normal_sample(double mu, double sigma, int n){
    double* sample = malloc(n*sizeof(double));
    int i;
    for (i = 0; i < n; i++){
        sample[i] = rand_base();
    }
    double somme = 0;
    for (i = 0; i < n; i++){
        somme += sample[i];
    }
    somme -= n/2;
    for (i = 0; i < n; i++){
        sample[i] = somme;
    }
    for (i = 0; i < n; i++){
        sample[i] = mu + sigma*sample[i];
    }
    return sample;
}

double *max_sample(unsigned int n){
    // Simulation la réalisation de la v.a T = max(T1, T2) où T1 et T2 sont deux variables définis sur le meme espace probabilisé.
    // P(T <= x)
    double* sample = malloc(n*sizeof(double));
    int i;
    for (i = 0; i < n; i++){
        sample[i] = rand_base();
    }
    double somme = 0;
    for (i = 0; i < n; i++){
        somme += sample[i];
    }
    somme -= n/2;
    for (i = 0; i < n; i++){
        sample[i] = somme;
    }
    return sample;
}