//
// Created by arnau on 15/11/2023.
//

#ifndef M31_TD_H
#define M31_TD_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double rand_base();

int de(int nb_face);

void affiche_variabilite(int nb_face, int nb_lancer);

void with_replacement(unsigned int n, unsigned int N, unsigned int* drawing);

void without_replacement(unsigned int n, unsigned int N, unsigned int* drawing);

double yarbouough(int nb_tirage);

char bernouilli(double p);

unsigned int bernouilli_sheme(unsigned int n, double p, char *result);

double* binomial_distribution(unsigned int n, double p);

unsigned int geometric(double p);

double exp_density(double lambda);

double g_x(double x);

struct coordonnee{
    double x;
    double y;
};

double monteCarlo(int n);

double monteCarlo2(int n);

#endif //M31_TD_H
