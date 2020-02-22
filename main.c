#include <stdio.h>
#include <stdlib.h>

unsigned int xorshift32(unsigned int state[0]);
void liniarizare(char* nume);
int main()
{
    FILE *f=fopen("peppers.bmp", "rb");
char *a;
char header[54];
fread(header, sizeof(char), 54, f);
rewind(f);
char w[5];
fseek(f, 18, SEEK_SET);
fread(w, sizeof(char), 4, f);


char h[5];
fread(h, sizeof(char), 4, f);

int W=*(int*)&w;
int H=*(int*)&h;
rewind(f);
fseek(f, 54, SEEK_SET);

a=(char*)malloc(3*W*H*sizeof(char));

int i;
unsigned long int j;
long k=3*W*H;
/*for(i=0; i<H; i++)
for (j=0; j<W; j++)*/
    for(i=0; i<k; i++)
    fread(&a[i], 1, 1, f);

FILE *F=fopen("vector.bmp", "wb");
fwrite(header, sizeof(char), 54, F);
/*for(i=0; i<H; i++)
for(j=0; j<W; j++)*/
 for(i=0; i<k; i++)
    fwrite(&a[i], 1, 1, F);

FILE *c=fopen("secret_key.txt", "r");
unsigned int R0, SV;
fscanf(c, "%u", &R0);
fscanf(c, "%u", &SV);
//printf("%u %u \n", R0, SV);





//printf("%li", k);


//unsigned long int state[1] = {1};
    char *b=(char*)malloc(k*sizeof(char));
    char *v=(char*)malloc(k*sizeof(char));
    for(i=0; i<k; i++)
        v[i]=a[i];
unsigned int *x=(unsigned int*)malloc(k*sizeof(unsigned int));
    //printf("%li ", n);
 for(i=0; i<k-1; i++)
{
    x[i]=xorshift32(&R0);
    x[i]=x[i]%(k+1);
    //printf("%u \n", x[i]);
    //printf("%u \n", x[i]);
    //if (j>k) l=j/k;

    //printf("%d", l);
//printf("%li ", j);
j=*(int*)&x[i];
if(v[j]!=NULL)
    {b[i]=v[j];
    v[j]=NULL;
    }

/*for(int z=j; z<n-1; z++)
    v[i]=v[i+1];
n--;*/
}
//for (i=0; i<20; i++)



/*int aux;
//double ratio=k/4294967294;
uint32_t state[1] = {1};
for (i=0; i<k-1; i++)
{printf("%d %d", i, j);
j=xorshift32(state[0], k);
aux=a[i];
a[i]=a[j];
a[j]=aux;
}*/


FILE *p=fopen("vector_permutat.bmp", "wb");
fwrite(header, sizeof(char), 54, p);
/*for(i=0; i<H; i++)
{for (j=0; j<W; j++)
    fwrite(&a[j], 3, 1, p);
    fwrite("\n", 1, 1, p);
}*/
//printf("%li", k);
for(i=0; i<k; i++)
    fwrite(&b[i], 1, 1, p);

/*rewind(f);
unsigned char info[54];
fread(info, sizeof(unsigned char), 54, f);
int m_width=*(int *)&info[18];
int m_height=*(int*)&info[22];
printf("%d %d", m_width, m_height);*/
char *cript=(char*)malloc(k*sizeof(char));
cript[0]=SV^b[0]^x[0];
cript[1]=SV^b[1]^x[0];
cript[2]=SV^b[2]^x[0];

for(i=3; i<k-1; i++)
{
    cript[i]=cript[i-1]^b[i]^x[i];
}
FILE *crp=fopen("criptat.bmp", "wb");
fwrite(header, sizeof(char), 54, crp);
for (i=0; i<k; i++)
    fwrite(&cript[i], 1, 1, crp);



    //testul chi
    float chi=0;
    int*t=(int*)malloc(k*sizeof(int));
    FILE *test=fopen("criptat.bmp", "rb");
    fseek(test, 54, SEEK_SET);
    /*float Rtest=test(0,0,255);
    float Gtest=test(0, 255, 0);
    float Btest=test(255,0,0);
    for(i=0; i<256; i++)
      chi=chi+(Rtest-(W*H/256))*(i-(W*H/256))/(W*H/255);
    printf("%.2f", chi);*/
for(i=0; i<k; i++)
    fread(&t[i], sizeof(int), 1, test);



    /*int fR=0;
    char R[3];
    R[0]=255;
    R[1]=0;
    R[2]=0;
    for (i=0; i<k-2; i++)
    if((R[0]==t[i])&&(R[1]==t[i+1])&&(R[2]==t[i+2])) fR++;
    printf("%d", fR);*/

   /* int o=0;
    int q=0;
    int fB[256];
//for(j=0; j<k; j++)
    for(i=0; i<256; i++)
    {
        if (t[o]==i) q++;
        fB[i]=q;
        o=o+3;

    }
printf("%d ", fB[0]);*/
int fB[256], fG[256], fR[256];
for(i=0; i<256; i++)
{ fB[i]=0; fG[i]=0; fR[i]=0;
}
for(j=0; j<3*W*H; j=j+3)
{for(i=0; i<256; i++)
if(t[j]==i) fB[i]=fB[i]+1;
if(t[j+1]==i) fG[i]=fG[i]+1;
if(t[j+2]==i) fR[i]=fR[i]+1;
}


for(i=0; i<256; i++)
    {//printf(" %d %d %d %d \n",i, fB[i], fG[i], fR[i]);
    printf("%u \n", t[i]);
    }

float chiB=0, chiG=0, chiR=0;
    for(i=0; i<256; i++)
    {
        chiB=chiB+((fB[i]-(W*H/256))*(fB[i]-(W*H/256))/(W*H/256));
        chiG=chiG+((fG[i]-(W*H/256))*(fG[i]-(W*H/256))/(W*H/256));
        chiR=chiR+((fR[i]-(W*H/256))*(fR[i]-(W*H/256))/(W*H/256));

    }

printf("%.2f %.2f %.2f ", chiB, chiG, chiR);


    return 0;
}



unsigned int xorshift32(unsigned int state[0])
{


 unsigned int x = state[0];
  x ^= x << 13;  //x=x^x<<13;
  x ^= x >> 17;
  x ^= x << 4;
 state[0] = x;

  return x;
}
void liniarizare(char* nume)
{

}
