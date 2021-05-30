/* Arnau Jutglar Puig NIUB niub20411311 */
/* Els vectors directors no sempre són iguals que els de l'exemple, però veiem que són proporcionals. */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    float v[3][2];
} Triangle;

typedef struct {
    float p[2];
    float v[2];
} Recta;


Recta bisectriu(float [2], float [2], float [2]);
void mitjanes3(Triangle, Recta *, Recta *, Recta *);
Recta mediatriu(float [2], float [2]);
Recta *altures3(Triangle );
int intersec2rectes(Recta, Recta, float [2]);
void escriure1recta(char *, Recta);
void escriure1punt(char *, float[2]);


int main(void) {
    Triangle tr;
    int i, j;
    float c[3], baric[2], circum[2], ortoc[2];
    float v[3][2], int_bisectrius3[3][2], int_mitjanes3[3][2], int_mediatrius3[3][2], int_altures3[3][2];
    float s, A, alineats;
    Recta bisectrius3[3], mitjanes_3[3], mediatrius3[3], *altures_3, euler;
    
    
    /* Comprovacions inicials de memòria */
    for (i=0; i < 3; i++) {
        if (v[i] == NULL) {
            printf("Problemes de memòria\n");
            exit(1);
        } else if (int_bisectrius3[i] == NULL) {
            printf("Problemes de memòria\n");
            exit(1);
        } else if (int_mitjanes3[i] == NULL) {
            printf("Problemes de memòria\n");
            exit(1);
        } else if (int_mediatrius3[i] == NULL) {
            printf("Problemes de memòria\n");
            exit(1);
        } else if (int_altures3[i] == NULL) {
            printf("Problemes de memòria\n");
            exit(1);
        }
    }
    
    /*
    if (bisectrius3 == NULL || mitjanes3 == NULL || mediatrius3 == NULL || altures3 == NULL) {
        printf("Problemes de memòria\n");
        exit(1);
    }*/
    
    
    printf("Entra els 3 vèrtexs x_j y_j:\n");
    for (j=0; j < 3; j++) {
        for (i=0; i < 2; i++) {
            scanf(" %f", &tr.v[j][i]);
        }
    }
    
    /* Comprovem que no és degenerat */
    
    v[0][0] = tr.v[0][0] - tr.v[1][0];
    v[0][1] = tr.v[0][1] - tr.v[1][1];
    
    v[1][0] = tr.v[1][0] - tr.v[2][0];
    v[1][1] = tr.v[1][1] - tr.v[2][1];
    
    v[2][0] = tr.v[2][0] - tr.v[0][0];
    v[2][1] = tr.v[2][1] - tr.v[0][1];
    
    for (i=0; i < 3; i++) {
        c[i] = sqrt( v[i][0] * v[i][0] + v[i][1] * v[i][1] );
    }
    
    s = (c[0] + c[1] + c[2]) / 2;
    
    A = s * (s - c[0]) * (s - c[1]) * (s - c[2]);
    
    if (A <= 0) {
        printf("Àrea no positiva. Triangle degenerat. \n");
        return 1;
    }
    
    A = sqrt(A);
    
    
    /* Fem els càlculs */
    
    /* Bisectrius */
    bisectrius3[0] = bisectriu(tr.v[0], tr.v[1], tr.v[2]);
    bisectrius3[1] = bisectriu(tr.v[1], tr.v[2], tr.v[0]);
    bisectrius3[2] = bisectriu(tr.v[2], tr.v[0], tr.v[1]);
    
    intersec2rectes(bisectrius3[0], bisectrius3[1], int_bisectrius3[0]);
    intersec2rectes(bisectrius3[1], bisectrius3[2], int_bisectrius3[1]);
    intersec2rectes(bisectrius3[2], bisectrius3[0], int_bisectrius3[2]);
    
    
    /* Mitjanes. Hem utilitzat mitjanes_3 per diferenciar el vector de mitjanes amb la funció mitjanes3. */
    mitjanes3(tr, &mitjanes_3[0], &mitjanes_3[1], &mitjanes_3[2]);
    
    intersec2rectes(mitjanes_3[0], mitjanes_3[1], int_mitjanes3[0]);
    intersec2rectes(mitjanes_3[1], mitjanes_3[2], int_mitjanes3[1]);
    intersec2rectes(mitjanes_3[2], mitjanes_3[0], int_mitjanes3[2]);
    
    baric[0] = int_mitjanes3[0][0];
    baric[1] = int_mitjanes3[0][1];
    
    
    /* Mediatrius */
    mediatrius3[0] = mediatriu(tr.v[0], tr.v[1]);
    mediatrius3[1] = mediatriu(tr.v[1], tr.v[2]);
    mediatrius3[2] = mediatriu(tr.v[2], tr.v[0]);
    
    intersec2rectes(mediatrius3[0], mediatrius3[1], int_mediatrius3[0]);
    intersec2rectes(mediatrius3[1], mediatrius3[2], int_mediatrius3[1]);
    intersec2rectes(mediatrius3[2], mediatrius3[0], int_mediatrius3[2]);
    
    circum[0] = int_mediatrius3[0][0];
    circum[1] = int_mediatrius3[0][1];


    /* Altures */
    altures_3 = altures3(tr);
    
    intersec2rectes(altures_3[0], altures_3[1], int_altures3[0]);
    intersec2rectes(altures_3[1], altures_3[2], int_altures3[1]);
    intersec2rectes(altures_3[2], altures_3[0], int_altures3[2]);
    
    ortoc[0] = int_altures3[0][0];
    ortoc[1] = int_altures3[0][1];
    
    
    /* Imprimim els resultats */
    printf("Comprovació de si el triangle és degenerat \n");
    printf("Àrea = %+.4f \n", A);
    
    /* Bisectrius */
    printf("Comprovacio que les 3 bisectrius son concurrents: incentre \n");
    escriure1recta("bisectriu 1", bisectrius3[0]);
    escriure1recta("bisectriu 2", bisectrius3[1]);
    escriure1recta("bisectriu 3", bisectrius3[2]);
    
    escriure1punt("interseccio de bisectrius 1-2", int_bisectrius3[0]);
    escriure1punt("interseccio de bisectrius 2-3", int_bisectrius3[1]);
    escriure1punt("interseccio de bisectrius 3-1", int_bisectrius3[2]);
    
    printf("\n");
    
    /* Mitjanes */
    printf("Comprovacio que les 3 mitjanes son concurrents: baricentre \n");
    escriure1recta("mitjana 1", mitjanes_3[0]);
    escriure1recta("mitjana 2", mitjanes_3[1]);
    escriure1recta("mitjana 3", mitjanes_3[2]);

    escriure1punt("interseccio de mitjanes 1-2", int_mitjanes3[0]);
    escriure1punt("interseccio de mitjanes 2-3", int_mitjanes3[1]);
    escriure1punt("interseccio de mitjanes 3-1", int_mitjanes3[2]);
    
    printf("\n");

    /* Mediatrius */
    printf("Comprovacio que les 3 mediatrius son concurrents: circumcentre \n");
    escriure1recta("mediatriu 1", mediatrius3[0]);
    escriure1recta("mediatriu 2", mediatrius3[1]);
    escriure1recta("mediatriu 3", mediatrius3[2]);
    
    escriure1punt("interseccio mediatrius 1-2", int_mediatrius3[0]);
    escriure1punt("interseccio mediatrius 2-3", int_mediatrius3[1]);
    escriure1punt("interseccio mediatrius 3-1", int_mediatrius3[2]);

    printf("\n");

    /* Altures */
    printf("Comprovacio que les 3 altures son concurrents: ortocentre \n");
    escriure1recta("altura 1", altures_3[0]);
    escriure1recta("altura 2", altures_3[1]);
    escriure1recta("altura 3", altures_3[2]);
    
    escriure1punt("interseccio d'altures 1-2", int_altures3[0]);
    escriure1punt("interseccio d'altures 2-3", int_altures3[1]);
    escriure1punt("interseccio d'altures 3-1", int_altures3[2]);

    
    /* Comprovem que el baricentre, el circumcentre i l'ortocentre estan alineats */
    printf("Comprovacio que baricentre, circumcentre i ortocentre estan alineats: \n");
    alineats = (circum[1] - baric[1]) * (ortoc[0] - baric[0]);
    alineats -= (circum[0] - baric[0]) * (ortoc[1] - baric[1]);
    printf("(cir1-bar1)*(ort0-bar0)-(cir0-bar0)*(ort1-bar1) = %+.4f \n \n", alineats);
    
    
    /* Recta d'Euler */
    euler.p[0] = baric[0];
    euler.p[1] = baric[1];
    
    euler.v[0] = ortoc[0] - circum[0];
    euler.v[1] = ortoc[1] - circum[1];
    
    escriure1recta("recta d'Euler", euler);
    
    return 0;
}


Recta bisectriu(float v[2], float v2[2], float v3[2]) {
    Recta r;
    float d1[2], d2[2];
    float m1, m2;
    
    /* L'origen de la recta és el punt a bisectar */
    r.p[0] = v[0];
    r.p[1] = v[1];
    
    /* El vector director és la suma dels vectors unitaris dels dos costats */
    d1[0] = v2[0] - v[0];
    d1[1] = v2[1] - v[1];
    
    d2[0] = v3[0] - v[0];
    d2[1] = v3[1] - v[1];
    
    m1 = sqrt( d1[0] * d1[0] + d1[1] * d1[1] );
    m2 = sqrt( d2[0] * d2[0] + d2[1] * d2[1] );
    
    r.v[0] = d1[0] / m1 + d2[0] / m2;
    r.v[1] = d1[1] / m1 + d2[1] / m2;
    
    
    return r;
}

void mitjanes3(Triangle tr, Recta *r1, Recta *r2, Recta *r3) {
    float pmig1[2], pmig2[2], pmig3[2];
    
    /* L'origen és cada vèrtex, el vector director és la resta entre el vèrtex i el punt mig oposat */
    
    /* Recta 1*/
    r1->p[0] = tr.v[0][0];
    r1->p[1] = tr.v[0][1];
    
    pmig1[0] = tr.v[1][0] / 2 + tr.v[2][0] / 2;
    pmig1[1] = tr.v[1][1] / 2 + tr.v[2][1] / 2;
    
    r1->v[0] = pmig1[0] - r1->p[0];
    r1->v[1] = pmig1[1] - r1->p[1];
    
    /* Recta 2*/
    r2->p[0] = tr.v[1][0];
    r2->p[1] = tr.v[1][1];
    
    pmig2[0] = tr.v[2][0] / 2 + tr.v[0][0] / 2;
    pmig2[1] = tr.v[2][1] / 2 + tr.v[0][1] / 2;
    
    r2->v[0] = pmig2[0] - r2->p[0];
    r2->v[1] = pmig2[1] - r2->p[1];
    
    /* Recta 3*/
    r3->p[0] = tr.v[2][0];
    r3->p[1] = tr.v[2][1];
    
    pmig3[0] = tr.v[0][0] / 2 + tr.v[1][0] / 2;
    pmig3[1] = tr.v[0][1] / 2 + tr.v[1][1] / 2;
    
    r3->v[0] = pmig3[0] - r3->p[0];
    r3->v[1] = pmig3[1] - r3->p[1];
    
    
    return;
}

Recta mediatriu(float v1[2], float v2[2]) {
    Recta r;
    float cost[2];
    
    /* L'orígen és la suma dels dos vèrtexs multiplicats per 1/2. El vector director és (1,-a/b) on (a,b) és la resta dels dos vèrtexs. Ho he trobat imposant que el producte escalar entre el vector (a,b) i (1,-a/b) sigui 0. Excepte si b=0, aleshores ha de ser vertical, per tant (0,1). */
    
    r.p[0] = v1[0] / 2 + v2[0] / 2;
    r.p[1] = v1[1] / 2 + v2[1] / 2;
    
    
    cost[0] = v2[0] - v1[0];
    cost[1] = v2[1] - v1[1];
    
    if (cost[1] != 0) {
        r.v[0] = 1;
        r.v[1] = - cost[0] / cost[1];
    } else {
        r.v[0] = 0;
        r.v[1] = 1;
    }
    
    
    return r;
}

Recta * altures3(Triangle tr) {
    Recta *r3;
    float cost1[2], cost2[2], cost3[2];
    
    r3 = (Recta *) calloc(3, sizeof(Recta *));
    if (r3 == NULL) {
        printf("Problemes de memòria.\n");
        exit(1);
    }
    
    /* Cada recta té per origen el vèrtex corresponent. I per vector director (1,-a/b), on (a,b) és el vector director igual a la diferència entre els dos altres vèrtexs (és a dir, el costat oposat. Excepte si b=0, alheshores el vector director serà (0,1). */
    
    /* Recta 1 */
    r3[0].p[0] = tr.v[0][0];
    r3[0].p[1] = tr.v[0][1];
    
    cost1[0] = tr.v[2][0] - tr.v[1][0];
    cost1[1] = tr.v[2][1] - tr.v[1][1];
    
    if (cost1[1] != 0) {
        r3[0].v[0] = 1;
        r3[0].v[1] = - cost1[0] / cost1[1];
    } else {
        r3[0].v[0] = 0;
        r3[0].v[1] = 1;
    }
    
    
    /* Recta 2 */
    r3[1].p[0] = tr.v[1][0];
    r3[1].p[1] = tr.v[1][1];
    
    cost2[0] = tr.v[0][0] - tr.v[2][0];
    cost2[1] = tr.v[0][1] - tr.v[2][1];
    
    if (cost2[1] != 0) {
        r3[1].v[0] = 1;
        r3[1].v[1] = - cost2[0] / cost2[1];
    } else {
        r3[1].v[0] = 0;
        r3[1].v[1] = 1;
    }
    
    /* Recta 3 */
    r3[2].p[0] = tr.v[2][0];
    r3[2].p[1] = tr.v[2][1];
    
    cost3[0] = tr.v[1][0] - tr.v[0][0];
    cost3[1] = tr.v[1][1] - tr.v[0][1];
    
    if (cost3[1] != 0) {
        r3[2].v[0] = 1;
        r3[2].v[1] = - cost3[0] / cost3[1];
    } else {
        r3[2].v[0] = 0;
        r3[2].v[1] = 1;
    }
    
    
    return r3;
}

int intersec2rectes(Recta r1, Recta r2 , float p[2]) {
    float lambda;
    
    if (r1.v[0] / r2.v[0] == r1.v[1] / r2.v[1]) {
        if (r1.p[0] == r2.p[0]  &&  r1.p[1] == r2.p[1]) {
            /* Aleshores són la mateixa recta, perquè tenen el mateix orígen i vector director. */
            return 1;
        } else {
            /* Aleshores són paral·leles perquè tenne orígens diferents. */
            return 2;
        }
    }
    
    /* Si són secants, podem resoldre el sistema paramètric per Cramer i arribem a que el punt on es creuaran és (x,y) = (a,b) + lambda(v1, v2), per un lambda que trobem de la manera que he dit. (a,b) és l'origen d'una de les rectes i (v1,v2) el vector director d'aquesta recta. */
    
    lambda = ((r1.p[0] - r2.p[0]) * r2.v[1] - r2.v[0] * (r1.p[1] - r2.p[1])) / (-r1.v[0] * r2.v[1] + r1.v[1] * r2.v[0]);
    
    p[0] = r1.p[0] + lambda * r1.v[0];
    p[1] = r1.p[1] + lambda * r1.v[1];
    
    return 0;
}

void escriure1recta(char *nom, Recta r) {
    
    printf("%s: ", nom);
    printf("(%+.4f, %+.4f) + t(%+.4f, %+.4f) \n", r.p[0], r.p[1], r.v[0], r.v[1]);
    
    return;
}

void escriure1punt(char *nom, float p[2]) {
    
    printf("%s: ", nom);
    printf("(%+.4f, %+.4f) \n", p[0], p[1]);
    
    return;
}
