#include <stdio.h>
#include <stdlib.h>
int w(char*header);
int h(char*header);
char* liniarizare(char*nume, int W, int H);
void fisier(char*nume, char*a, char*header, int W, int H);
char* headeR(char*nume);
unsigned int xorshift32(unsigned int seed[0]);
char* criptare(char*initial, char*nume, char*key, int W, int H, char* header);
void decriptare(char* header, int W, int H, char*b, char*initial, char*cript, char*key);
void chi_patrat(int W, int H, char*nume);

int main()
{ char*header=headeR("peppers.bmp");
int W=w(header);
int H=h(header);
    char*a=liniarizare("peppers.bmp", W, H);
    fisier("vector.bmp",a, header, W, H);
    char*b=criptare("peppers.bmp", "criptat.bmp", "secret_key.txt", W, H, header);
    decriptare(header, W, H, b, "peppers_decriptat.bmp", "criptat.bmp", "secret_key.txt");
    chi_patrat(W,H, "criptat.bmp");

    return 0;
}

char* headeR(char*nume)
{ FILE *f=fopen(nume, "rb");
char* header=(char*)malloc(55*sizeof(char));

fread(header, sizeof(char), 54, f);
fclose(f);
    return header;
}

int w(char*header)
{
    int W=*(int*)&header[18];
    return W;
}

int h(char*header)
{
    int H=*(int*)&header[22];
    return H;
}

char*liniarizare(char*nume, int W, int H)
{
    FILE *f=fopen(nume, "rb");
    char *a;
long int i;
fseek(f, 54, SEEK_SET);
a=(char*)malloc(3*W*H*sizeof(char));


long k=3*W*H;

    for(i=0; i<k; i++)
    fread(&a[i], 1, 1, f);
    fclose(f);
    return a;

}

void fisier(char*nume, char*a, char*header, int W, int H)
{
FILE *F=fopen(nume, "wb");
fwrite(header, sizeof(char), 54, F);
    long k=3*W*H;
int i;
 for(i=0; i<k; i++)
    fwrite(&a[i], 1, 1, F);
    fclose(F);
}
char* criptare(char*initial, char*nume, char*key, int W, int H, char* header)
{long int k=3*W*H, i, j;

    char *a=liniarizare(initial, W, H);
    FILE *c=fopen(key, "r");
unsigned int R0, SV;
fscanf(c, "%u", &R0);
fscanf(c, "%u", &SV);
char *b=(char*)malloc(k*sizeof(char));

unsigned int *x=(unsigned int*)malloc(k*sizeof(unsigned int));


 for(i=0; i<k-1; i++)
{
    x[i]=xorshift32(&R0);
    x[i]=x[i]%(k+1);



 //b este vectorul permutat
j=*(int*)&x[i];



if(a[j]!=NULL)
    {b[i]=a[j];
    a[j]=NULL;
    }
    }


FILE *p=fopen("vector_permutat.bmp", "wb");
fwrite(header, sizeof(char), 54, p);
for(i=0; i<k; i++)
    fwrite(&b[i], 1, 1, p);


    char *cript=(char*)malloc(k*sizeof(char));
cript[0]=SV^b[0]^x[0];


for(i=1; i<k-1; i++)
{
    cript[i]=cript[i-1]^b[i]^x[i];
}
FILE *crp=fopen(nume, "wb");
fwrite(header, sizeof(char), 54, crp);

for (i=0; i<k; i++)
    fwrite(&cript[i], 1, 1, crp);

fclose(crp);

fclose(p);
fclose(c);
return b;

}


void decriptare(char* header, int W, int H, char* b, char*initial, char*cript, char*key)
{
 FILE *z=fopen(cript, "rb");
fseek(z, 54, SEEK_SET);
long k=3*W*H;
char*r=(char*)malloc(k*sizeof(char));
long int i;
for(i=0; i<k; i++)
{
    fread(&r[i], sizeof(char), 1, z);
}
//fclose(f);
unsigned int SV, R0;
FILE *m=fopen(key, "r");
fscanf(m, "%u", &R0);
fscanf(m, "%u", &SV);

fclose(m);
unsigned int *x=(unsigned int*)malloc(k*sizeof(unsigned int));
for(i=0; i<k-1; i++)
{
    x[i]=xorshift32(&R0);
    x[i]=x[i]%(k+1);


}
char*decript=(char*)malloc(k*sizeof(char));
decript[0]=SV^r[0]^x[0];
for (i=1; i<k-1; i++)
    decript[i]=r[i-1]^r[i]^x[i];


    FILE *c=fopen("decriptat.bmp", "wb");
    fwrite(header, sizeof(char), 54, c);
    for(i=0; i<k; i++)
        fwrite(&decript[i], sizeof(char), 1, c);

fclose(c);
unsigned int j;
char*per=(char*)malloc(k*sizeof(char));
for(i=0; i<k-1; i++)
    {j=*(int*)&x[i];
   per[j]=b[i];
}
FILE *perm=fopen(initial, "wb");
fwrite(header, sizeof(char), 54, perm);
for(i=0; i<k; i++)
    fwrite(&per[i], sizeof(char), 1, perm);
    fclose(perm);


}
unsigned int xorshift32(unsigned int seed[0])
{


 unsigned int x = seed[0];
  x ^= x << 13;  //x=x^x<<13;
  x ^= x >> 17;
  x ^= x << 4;
 seed[0] = x;

  return x;
}
void chi_patrat(int W, int H, char*nume)
{ long k=3*W*H;
int i, j;
  //testul chi
    char*t=(char*)malloc(k*sizeof(char));
    FILE *test=fopen(nume, "rb");
    fseek(test, 54, SEEK_SET);
    for(i=0; i<k; i++)
   {fread(&t[i], sizeof(char), 1, test);
    t[i]=t[i]%255;
    }

int* fB=(int*)malloc(256*sizeof(int));
int*fG=(int*)malloc(256*sizeof(int)); int* fR=(int*)malloc(256*sizeof(int));

for(i=0; i<256; i++)
{ fB[i]=0; fG[i]=0; fR[i]=0;
}
for(j=0; j<3*W*H; j=j+3)
{for(i=0; i<256; i++)
if(t[j]==i) fB[i]=fB[i]+1;
if(t[j+1]==i) fG[i]=fG[i]+1;
if(t[j+2]==i) fR[i]=fR[i]+1;
}




float chiB=0, chiG=0, chiR=0;
    for(i=0; i<256; i++)
    {
        chiB=chiB+((fB[i]-(W*H/256))*(fB[i]-(W*H/256))/(W*H/256));
        chiG=chiG+((fG[i]-(W*H/256))*(fG[i]-(W*H/256))/(W*H/256));
        chiR=chiR+((fR[i]-(W*H/256))*(fR[i]-(W*H/256))/(W*H/256));

    }

printf("%.2f %.2f %.2f ", chiB, chiG, chiR);
fclose(test);


}
