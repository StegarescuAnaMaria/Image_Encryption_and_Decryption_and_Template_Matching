#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int w(char*nume);
int h(char*nume);
unsigned int** S_i_j(char*nume);
unsigned int**f_i_j(unsigned int**fereastra, char*nume);
double S_barat(char*nume, unsigned int**Sij);
double f_barat(char*nume, unsigned int**fij);
double zigmaS(char*nume, unsigned int**Sij, double mS);
double zigmaf(char*nume, unsigned int**fij, double mf);
unsigned int** fer(char*imagine,char*sablon, int x, int y);
double corelatie(char*nume_sablon, unsigned int**fereastra);
unsigned char* RGB(char*sablon_nume);
unsigned int** template_matching(char*sablon_nume, char*imagine_nume, double ps, int x, int y, char*nume_imagine_copie);
unsigned int** contur(char*imagine, unsigned int**fereastra, char*C, char*nume_sablon, int x, int y, char*nume_imagine_copie);
int comp(const void*a, const void*b);
void start(char*nume_sablon, char*nume_imagine_grayscale, char*nume_imagine_test, char*nume_imagine_copie);
int minim(int a, int b);
int maxim(int a, int b);
void eliminare_suprapuneri(unsigned int**D, int**coordonate, double*corelatii, int numar, char*nume_sablon, char*nume_imagine_copie);
void sortare_corelatii(unsigned int** D, double*corelatii, int**coordonate, int numar, char*nume_sablon, char*nume_imagine_copie);
int main()
{

start("cifra0_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
start("cifra1_grayscale.bmp", "test_grayscale.bmp", "test.bmp","test - Copy.bmp");
start("cifra2_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
start("cifra3_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
start("cifra4_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
start("cifra5_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
start("cifra6_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
start("cifra7_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
start("cifra8_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
start("cifra9_grayscale.bmp", "test_grayscale.bmp", "test.bmp", "test - Copy.bmp");
    return 0;
}

int w(char*nume)
{ int W;
 FILE *f=fopen(nume, "rb");
 fseek(f, 18, SEEK_SET);
 fread(&W, sizeof(int), 1, f);

 fclose(f);
 return W;
}

int h(char*nume)
{
    int H;
    FILE *f=fopen(nume, "rb");
    fseek(f, 22, SEEK_SET);
    fread(&H, sizeof(int), 1, f);

    fclose(f);
    return H;

}

char*head(char*nume)
{ int i;
    FILE *f=fopen(nume, "rb");
    char*header=(char*)malloc(55*sizeof(char));
    for(i=0; i<54; i++)
    fread(&header[i], sizeof(char), 1, f);
    fclose(f);
    return header;

}

 unsigned int** S_i_j(char*nume)
{ int W0=w(nume);
int H0=h(nume);

    char*header=head(nume);
    FILE *F=fopen(nume, "rb");
    int i, j;

   fseek(F, 54, SEEK_SET);


    int paddingW=4-(W0*3)%4, paddingH=4-(H0*3)%4;
if(W0%4==0) paddingW=0;
if(H0%4==0) paddingH=0;

char*padding_linie=(char*)malloc(paddingW*sizeof(char));
for (i=0; i<paddingW; i++)
    padding_linie[i]=0;


    int **a;
a=(int**)malloc(H0*sizeof(int*));
for(i=0; i<H0; i++)
a[i]=(int*)malloc(W0*sizeof(int));

    for(i=0; i<H0; i++)
{for(j=0; j<W0; j++)
fread(&a[i][j], sizeof(char), 3, F);
fseek(F, paddingW, SEEK_CUR);
}
FILE *f=fopen("pad.bmp", "wb");
for(i=0; i<54; i++)
fwrite(&header[i], sizeof(char), 1, f);

      for(i=0; i<H0; i++)
        {for(j=0; j<W0; j++)
         fwrite(&a[i][j], sizeof(char), 3, f);

for(int z=0; z<paddingW; z++)
    fwrite(&padding_linie[z], sizeof(char), 1, f);}


unsigned int **Sij=(unsigned int**)malloc(H0*sizeof(unsigned int*));
for(i=0; i<H0; i++)
Sij[i]=(unsigned int*)malloc(W0*sizeof(unsigned int));

for(i=0; i<H0; i++)
    {for(j=0; j<W0; j++)
{char P=*(char*)&a[i][j];
unsigned int p=*(unsigned int*)&P;
Sij[i][j]=p%255;

}}
rewind(F);
fclose(f);
fclose(F);
return Sij;

}

double S_barat(char*nume, unsigned int**Sij)
{
    int W0=w(nume);
    int H0=h(nume);
    double mS;
double suma=0;
int i, j;
for(i=0; i<H0 ;i++)
for(j=0; j<W0; j++)
    suma=suma+Sij[i][j];

    mS=suma/(double)(W0*H0);

    return mS;
}

double zigmaS(char*nume, unsigned int**Sij, double mS)
{ int W0=w(nume);
int H0=h(nume);
    int i, j;
    double sigmaS=0;
    double raport;
    raport=(double)1/(W0*H0-1);
    //double aux=(double)W0*H0-1;
    //double Aux=(double)1/aux;

    double sum=0.00;
    for(i=0; i<H0; i++)
    for(j=0; j<W0; j++)
        {sum=(double)sum+(double)((double)Sij[i][j]-(double)mS)*((double)Sij[i][j]-(double)mS);
//printf("%f \n", mS);
 //printf("%f %d %d \n", sum, i, j);
        }
        double sumabs=fabs(sum);
        //printf("%f\n", sumabs);

    sigmaS= (double)sqrt(raport*sumabs);
   //printf("%f\n", sigmaS);

return sigmaS;
}

unsigned int**f_i_j(unsigned int**fereastra, char*nume)
{ int W0=w(nume);
int H0=h(nume);
    int i, j;
    unsigned int **fij=(unsigned int**)malloc(H0*sizeof(unsigned int*));
for(i=0; i<H0; i++)
fij[i]=(unsigned int*)malloc(W0*sizeof(unsigned int));

for(i=0; i<H0; i++)
    {for(j=0; j<W0; j++)
{char P=*(char*)&fereastra[i][j];
unsigned int p=*(unsigned int*)&P;
fij[i][j]=p%255;
}
}
return fij;
}

double f_barat(char*nume_sablon, unsigned int**fij)
{int W0=w(nume_sablon);
int H0=h(nume_sablon);
     double mf;
double suma=0;
int i, j;
for(i=0; i<H0 ;i++)
for(j=0; j<W0; j++)
    suma=suma+fij[i][j];

    mf=suma/(double)(W0*H0);

    return mf;
}

double zigmaf(char*nume_sablon, unsigned int**fij, double mf)
{ int W0=w(nume_sablon);
int H0=h(nume_sablon);
    //printf("%d %d", W0, H0);

    int i, j;
    double sigmaf;
    double raport;
    raport=(double)1/(W0*H0-1);
    //printf("%f\n", raport);

    double sum=0.00;
    for(i=0; i<H0; i++)
    for(j=0; j<W0; j++)
        sum=sum+(double)((double)fij[i][j]-(double)mf)*(((double)fij[i][j]-(double)mf));

        //printf("%f\n", sum);
        double sumabs=fabs(sum);
    sigmaf= (double)sqrt(raport*sumabs);

return sigmaf;
}

unsigned int** fer(char*imagine,char*sablon, int x, int y)
{int W=w(imagine);
int H=h(imagine);
int W0=w(sablon);
int H0=h(sablon);
//printf("%d %d", W0, H0);
char*header=head(sablon);
    unsigned int** fereastra;
    fereastra=(unsigned int**)malloc(H0*sizeof(unsigned int*));
    int i, j;
for(i=0; i<H0; i++)
fereastra[i]=(unsigned int*)malloc(W0*sizeof(unsigned int));


int paddingW=4-(W0*3)%4, paddingH=4-(H0*3)%4;
if(W0%4==0) paddingW=0;
if(H0%4==0) paddingH=0;

char*padding_linie=(char*)malloc(paddingW*sizeof(char));
for (i=0; i<paddingW; i++)
    padding_linie[i]=0;

FILE *w=fopen(imagine, "rb");
fseek(w, 54, SEEK_SET);
fseek(w, 3*x*W, SEEK_CUR);
fseek(w, 3*y*H, SEEK_CUR);


FILE*fere=fopen("fereastra.bmp", "wb");
//for(i=0; i<54; i++)
//fwrite(&header[i], sizeof(char), 1, fere);
for(i=0; i<H0; i++)
    {for(j=0; j<W0; j++)
    {fread(&fereastra[i][j], sizeof(char), 3, w);
//fwrite(&fereastra[i][j], sizeof(char), 3, fere);
}
     //for(int z=0; z<paddingW; z++)
    //fwrite(&padding_linie[z], sizeof(char), 1, fere);
fseek(w, 3*(W-W0), SEEK_CUR);
}
fclose(fere); fclose(w);
return fereastra;
}


double corelatie(char*nume_sablon, unsigned int**fereastra)
{ int W0=w(nume_sablon);
int H0=h(nume_sablon);
unsigned int**Sij=S_i_j(nume_sablon);
//printf("%d ", Sij[20][100]);
double mS=S_barat(nume_sablon, Sij);
//printf(" \n %f \n",mS );
double sigmaS=zigmaS(nume_sablon, Sij, mS);
//printf("%f \n", sigmaS);
unsigned int**fij=f_i_j(fereastra, nume_sablon);
//printf("%d ", fij[0][9]);
double mf=f_barat(nume_sablon, fij);
//printf("%f \n", mf);
double sigmaf=zigmaf(nume_sablon, fij, mf);
//printf("%f \n", sigmaf);

    double sum=0.00;
   double raport=(double)1/(double)(W0*H0);
   double raport_sigma=(double)1/(double)(sigmaS*sigmaf);
   //printf("%f \n", raport_sigma);
   int i, j;
   for(i=0; i<H0; i++)
        for(j=0; j<W0; j++)
        sum=(double)sum+(double)raport_sigma*(double)((double)fij[i][j]-(double)mf)*(double)((double)Sij[i][j]-(double)mS);
//double sumabs=fabs(sum);
        double cor=(double)(raport*sum);
        //printf("%f \n", cor);
        for(i=0; i<H0; i++)
        {
            free(Sij[i]);
            free(fij[i]);
        }
        free(Sij); free(fij);
   return cor;

}

unsigned char* RGB(char*sablon_nume)
{
strcat(*sablon_nume, "\0");
unsigned char R=0, G=0, B=0;
//printf("%d %d %d \n", R, G, B);
//if(sablon_nume=="cifra0_grayscale.bmp")
    if(strncmp(sablon_nume, "cifra0_grayscale.bmp", 6)==0)
{
    R=255; G=0; B=0;
    //printf("%d %d %d \n", R, G, B);
}
else if(sablon_nume=="cifra1_grayscale.bmp")
{
    R=255; G=255; B=0;
}
else if(sablon_nume=="cifra2_grayscale.bmp")
{
    R=0; G=255; B=0;
}
else if(sablon_nume=="cifra3_grayscale.bmp")
{
    R=0; G=255; B=255;
}
else if(sablon_nume=="cifra4_grayscale.bmp")
{
    R=255; G=0; B=255;
}
else if(sablon_nume=="cifra5_grayscale.bmp")
{
    R=0; G=0; B=255;
}
else if(sablon_nume=="cifra6_grayscale.bmp")
{
    R=192; G=192; B=192;
}
else if(sablon_nume=="cifra7_grayscale.bmp")
{
    R=255; G=140; B=0;
}
else if(sablon_nume=="cifra8_grayscale.bmp")
{
  R=128; G=0; B=128;
}
else if(sablon_nume=="cifra9_grayscale.bmp")
{
   R=0; G=0; B=128;
}
//printf(sablon_nume);
unsigned char*C=(unsigned char*)malloc(4*sizeof(unsigned char));
C[0]=B;
C[1]=G;
C[2]=R;


return C;
}

unsigned int** template_matching(char*sablon_nume, char*imagine_nume, double ps, int x, int y, char*nume_imagine_copie)
{
int H0=h(sablon_nume);
    int i, j;

    unsigned char*C=RGB(sablon_nume);

unsigned int** fereastra=fer(imagine_nume, sablon_nume, x, y);
double cor=corelatie(sablon_nume, fereastra);

if ((double)cor>=(double)ps)

{ unsigned int** fereastra_color=contur(imagine_nume, fereastra, C, sablon_nume, x, y, nume_imagine_copie);
free(C);
for(i=0; i<H0; i++)
    free(fereastra[i]);
free(fereastra);
return fereastra_color;

}
else return NULL;

}

unsigned int** contur(char*imagine, unsigned int**fereastra, char*C, char*nume_sablon, int x, int y, char*nume_imagine_copie)
{
    int W0=w(nume_sablon);
int H0=h(nume_sablon);
char*header=head(nume_sablon);
int W=w(imagine);
int H=h(imagine);
    int i, j;


    int paddingW=4-(W0*3)%4, paddingH=4-(H0*3)%4;
if(W0%4==0) paddingW=0;
if(H0%4==0) paddingH=0;


char*padding_linie=(char*)malloc(paddingW*sizeof(char));
for (i=0; i<paddingW; i++)
    padding_linie[i]=0;


FILE *color=fopen("cifra_color.bmp", "wb");
for(i=0; i<54; i++)
fwrite(&header[i], sizeof(char), 1, color);

    for(j=0; j<W0; j++)
{for(i=0; i<3; i++)
    fwrite(&C[i],sizeof(char), 1, color);}
    for(int z=0; z<paddingW; z++)
    fwrite(&padding_linie[z], sizeof(char), 1, color);

      for(i=1; i<H0-1; i++)
       {for(int z=0; z<3; z++)
    fwrite(&C[z],sizeof(char), 1, color);

        for(j=1; j<W0-1; j++)
         fwrite(&fereastra[i][j], sizeof(char), 3, color);

for(int l=0; l<3; l++)
    fwrite(&C[l],sizeof(char), 1, color);
    for(int m=0; m<paddingW; m++)
    fwrite(&padding_linie[m], sizeof(char), 1, color);
    }

    for(j=0; j<W0; j++)
{for(i=0; i<3; i++)
    fwrite(&C[i],sizeof(char), 1, color);
    }
    for(int z=0; z<paddingW; z++)
    fwrite(&padding_linie[z], sizeof(char), 1, color);

fclose(color);
FILE *colour=fopen("cifra_color.bmp", "rb");
fseek(colour, 54, SEEK_SET);
unsigned int**fereastra_contur=(unsigned int**)malloc(H0*sizeof(unsigned int*));
for(i=0; i<H0; i++)
fereastra_contur[i]=(unsigned int*)malloc(W0*sizeof(unsigned int));

    for(i=0; i<H0; i++)
{for(j=0; j<W0; j++)
fread(&fereastra_contur[i][j], sizeof(char), 3, colour);
fseek(color, paddingW, SEEK_CUR);
}
FILE *w=fopen(imagine, "rb+");
fseek(w, 54, SEEK_SET);
fseek(w, 3*x*W, SEEK_CUR);
fseek(w, 3*y*H, SEEK_CUR);
for(i=0; i<H0; i++)
{for(j=0; j<W0; j++)
{
        fwrite(&fereastra_contur[i][j], sizeof(char), 3, w);

}
fseek(w, 3*(W-W0), SEEK_CUR);
}
fflush(w);
fclose(colour); fclose(w);
return fereastra_contur;
}

int comp(const void*a, const void*b)
{
    double va=*(double*)a;
    double vb=*(double*)b;
    if (va<vb) return 1;
    else if (va>vb) return -1;
    else return 0;
}

void sortare_corelatii(unsigned int** D, double*corelatii, int**coordonate, int numar, char*nume_sablon, char*nume_imagine_copie)
{ int*(*ptr);
int i, j;
int*variabila_pointer=&i; //pentru a afla sizeof(pointer)
*ptr=(int*)malloc(numar*sizeof(variabila_pointer));
for(i=0; i<numar; i++)
    ptr[i]=&corelatii[i];

qsort(&corelatii, numar, sizeof(double), comp);
int*schimb=(int*)calloc(numar, sizeof(int));
for(i=0; i<numar; i++)
    for(j=0; j<numar; j++)
{
    if(ptr[i]==&corelatii[j]) schimb[i]=j;
}
//alocam un noua matrice(patratica) pentru coordonate
int**coord_aux;
coord_aux=(int**)malloc(numar*sizeof(int*));
for(i=0; i<numar; i++)
coord_aux[i]=(int*)malloc(numar*sizeof(int));
//e nevoie de o matrice auxiliara, deoarece schimbarea pozitiilor in matrice a coordonatelor in functie de schimb[i]
//se poate implementa potrivit doar avand o matrice goala, interschimbarea nu da rezultatul dorit
for(i=0; i<numar; i++)
{coord_aux[i][0]=coordonate[schimb[i]][0];
    coord_aux[i][1]=coordonate[schimb[i]][1];
}
    //free(coordonate)

int W0=w(nume_sablon);
int H0=h(nume_sablon);
int z;
int**D_aux;
D_aux=(unsigned int**)malloc(numar*H0*sizeof(unsigned int*));
for(i=0; i<numar*H0; i++)
D_aux[i]=(unsigned int*)malloc(numar*W0*sizeof(unsigned int));

for(z=0; z<numar; z++)
for(i=0; i<H0; i++)
for(j=0; j<W0; j++)
    //D_aux[z*H0+i][z*W0+j]=D[schimb[z]*H0+i][schimb[z]*W0+j];
    D_aux[i][z*W0+j]=D[i][schimb[z]*W0+j];
   /* for(i=0; i<numar; i++)
    {
        free()
    }*/
free(ptr); free(schimb); //free()
eliminare_suprapuneri(D, coordonate, corelatii, numar, nume_sablon, nume_imagine_copie);
}

void eliminare_suprapuneri(unsigned int**D, int**coordonate, double*corelatii, int numar, char*nume_sablon, char*nume_imagine_copie)
{ int W0=w(nume_sablon);
int H0=h(nume_sablon);
    int i, j;
int x, y;
int** stanga_sus=(int**)malloc(numar*sizeof(int*));
for(i=0; i<numar; i++)
    stanga_sus[i]=(int*)malloc(2*sizeof(int));

int** stanga_jos=(int**)malloc(numar*sizeof(int*));
for(i=0; i<numar; i++)
    stanga_jos[i]=(int*)malloc(2*sizeof(int));

int** dreapta_sus=(int**)malloc(numar*sizeof(int*));
for(i=0; i<numar; i++)
    dreapta_sus[i]=(int*)malloc(2*sizeof(int));

int** dreapta_jos=(int**)malloc(numar*sizeof(int*));
for(i=0; i<numar; i++)
    dreapta_jos[i]=(int*)malloc(2*sizeof(int));

int stanga, dreapta, jos, sus;
    int W=w(nume_imagine_copie);
    int H=h(nume_imagine_copie);
    double suprapunere;
    int aria_intersectie;
    int aria_suprapunere;
    int aria_I=W0*H0, aria_II=aria_I;
        for(i=0; i<numar; i++)
            {
                stanga_sus[i][0]=coordonate[i][0];
                stanga_sus[i][1]=coordonate[i][1];

                dreapta_sus[i][0]=coordonate[i][0];
                dreapta_sus[i][1]=coordonate[i][1]+W0;

                stanga_jos[i][0]=coordonate[i][0]+H0;
                stanga_jos[i][1]=coordonate[i][1];

                dreapta_jos[i][0]=coordonate[i][0]+H0;
                dreapta_jos[i][1]=coordonate[i][1]+W0;

            }

            for(i=0; i<numar-2; i++)
                {if(corelatii[i]!=0)
                for(j=i+1; j<numar-1; j++)
                {if(corelatii[j]!=0)
               {
                   stanga=maxim(stanga_jos[i][1], stanga_jos[j][1]);
            dreapta=minim(dreapta_sus[i][1], dreapta_sus[j][1]);
            jos=maxim(dreapta_jos[i][0], dreapta_jos[j][0]);
            sus=minim(stanga_sus[i][0], stanga_sus[j][0]);

            aria_intersectie=(abs(dreapta-stanga))*(abs(jos-sus));
            aria_suprapunere=aria_I+aria_II-aria_intersectie;
            suprapunere=(double) aria_intersectie/(double)aria_suprapunere;
            if(suprapunere>0.20)
            {
                    corelatii[j]=0;
                    coordonate[j][0]=NULL;
                    coordonate[j][1]=NULL;
                    for(int z=0; z<H0; z++)
                    for(int q=0; q<W0; q++)
                    D[j*H0+z][j*W0+q]=NULL;
            }

               }
               }
                }
                FILE *img=fopen(nume_imagine_copie, "rb+");
                fseek(img, 54, SEEK_SET);
                for(int z=0; z<numar; z++)
                if(corelatii[z]!=0)
                {
                    x=coordonate[z][0];
                    y=coordonate[z][1];
                    fseek(img, 3*x*W, SEEK_CUR);
fseek(img, 3*y*H, SEEK_CUR);
for(i=0; i<H0; i++)
{for(j=0; j<W0; j++)
{
        fwrite(&D[i][z*W0+j], sizeof(char), 3, img);

}
fseek(img, 3*(W-W0), SEEK_CUR);
}
}
                fclose(img);

                for(i=0; i<numar; i++)
                {
                    free(D[i]);
                    free(coordonate[i]);
                    free(stanga_sus[i]); free(dreapta_jos[i]); free(dreapta_sus[i]); free(stanga_jos[i]);

                }
free(D); free(coordonate); free(corelatii); free(stanga_sus); free(stanga_jos); free(dreapta_sus); free(dreapta_jos);
}

int maxim(int a, int b)
{
if (a>b) return a;
else if(b>=a) return b;
}

int minim(int a, int b)
{
if (a>b) return b;
else if (b>=a) return a;
}

void start(char*nume_sablon, char*nume_imagine_grayscale, char*nume_imagine_test, char*nume_imagine_copie)
{
    int W0=w(nume_sablon);
int H0=h(nume_sablon);
int W=w(nume_imagine_test);
int H=h(nume_imagine_test);
unsigned int**detectii=NULL;
unsigned int** fereastra_color=NULL;
double* corelatie_detectii=NULL;
int**coordonate=NULL;
int d=0;
int cx=0;
int x;
int y;
int m=0;
int i, j;
double ps=0.50;
int numar=0;
for(x=0; x<(H-H0); x++)
    for(y=0; y<(W-W0); y++)
{fereastra_color=template_matching(nume_sablon, nume_imagine_grayscale, ps, x, y, nume_imagine_copie);

if (fereastra_color!=NULL)
{
    unsigned int**fereastra=fer(nume_imagine_grayscale, nume_sablon, x, y);
    double cor=corelatie(nume_sablon, fereastra);
int**aux=(int**)realloc(coordonate, (cx+1)*sizeof(int*));
for(i=0; i<(cx+1); i++)
aux[i]=(int*) realloc(coordonate, 2*sizeof(int));

    unsigned int**detectii_ferestre=(unsigned int**)realloc(detectii, H0*sizeof(unsigned int*));
    for(i=0; i<H0; i++)
        detectii_ferestre[i]=(unsigned int*)realloc(detectii, (W0+m)*sizeof(unsigned int));

 double* corelatie_detectii_II=(double*)realloc(corelatie_detectii, (d+1)*sizeof(double));
 numar++;
    if (detectii_ferestre!=NULL)
    {
    detectii=detectii_ferestre;

    for(i=0; i<H0; i++)
        for(j=0; j<W0; j++)
            detectii[i][m+j]=fereastra_color[i][j];
    m=m+W0;


}
if (corelatie_detectii_II!=NULL)
{
corelatie_detectii=corelatie_detectii_II;
corelatie_detectii[d]=cor;
d++;

}
if(aux!=NULL)
{
    coordonate=aux;
    coordonate[cx][0]=x;
    coordonate[cx][1]=y;
    cx++;

}

}
}
for(i=0; i<H0; i++)
{
    free(fereastra_color[i]);
    //free(fereastra[i]);

}
//free(fereastra);
free(fereastra_color);
sortare_corelatii(detectii, corelatie_detectii, coordonate, numar, nume_sablon, nume_imagine_copie);
}
