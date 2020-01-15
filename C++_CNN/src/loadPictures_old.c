#include <stdio.h>
#include <stdlib.h>





int* loadFilePGM()
{
  char* taille=NULL;
  char* format=NULL;
  char* temp=NULL;
  int tx=0;
  int ty=0;
  int * image;
  size_t size=0;
  FILE* f;
  f=fopen("input.ppm","r");
  if (f!= NULL) printf("file opened\n");
  getline(&format,&size,f);

  /* Lit la ligne qui contient la taille */
  getline(&taille,&size, f);
  /* mais passe les commentaires */
  while (taille[0]=='#') getline(&taille,&size, f);
  // lit la taille dans la chaine
  sscanf(taille,"%d %d", &tx, &ty);
  printf("%s %s %d %d\n",format,taille,tx,ty);
  getline(&temp,&size,f);
  printf("%s",temp);
  image = (int*)calloc(tx*ty*3,sizeof(int));


  int i=0;
  int temp;
  while (i!=-1)
  {
    i=fscanf(f,"%d",temp);
    printf("%s",temp);
    image[i] = atoi(temp);
  }

  fclose(f);
  return(image);
}


void printMatrix(int* image)
{
  for(int i=0; i<(*ptx)*(*pty)*3; i++)
  {
    if(i%(*ptx)==0) printf("\n");
    printf("%d\t",image[i]);
  }
}

int main()
{
  int* image = loadFilePGM();
  //printMatrix(image);
  //free(image);
  return(0);
}
