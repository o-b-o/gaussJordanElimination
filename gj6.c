#include<stdio.h>    
#include<stdlib.h>
#include<math.h>
#include<time.h>




double drand ( double low, double high )
{
    srand((unsigned int)clock());
     return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}





int main(){
  int n;
  printf("numero de filas (int)=");    
  scanf("%d",&n);    

  //// abrimos gnuplot para visualizar
  FILE *arch=fopen("mat.txt","w");
  FILE *gnuplot=popen("gnuplot","w");
  fprintf(gnuplot, "set pm3d\n");

  fprintf(gnuplot, "set cbrange [-2:2]\n");
  fprintf(gnuplot, "set view map\n");

  fprintf(gnuplot, "set term gif animate size 400,400 delay 1 \n");
  //  fprintf(gnuplot, "set size ratio -1\n");                         
    fprintf(gnuplot, "set size square\n");
  fprintf(gnuplot, "set output 'gj6.gif'\n");


  fprintf(gnuplot, "set title  ''\n");
  //  fprintf(gnuplot, "set pm3d interpolate 3,0\n"); 
  fprintf(gnuplot, " set pm3d corners2color c4\n"); 








  // lee una matriz
  double a[n][n],b[n],sc;
  int r,c,i,j,k;    
  double epsilon = pow(10,-20); 
  //  system("cls");  
  r = n;
  c = n;
  
  // printf("elementos de la primera matriz=\n");    
  for(i=0;i<r;i++)    
    {    
      for(j=0;j<c;j++)    
	{
	  //	  printf("a[%d][%d]= ",i,j); 
	  //scanf("%lf",&a[i][j]);
	  a[i][j]=drand(3.1,5);
	}    
    }    

  //printf("elementos del vector=\n");    
  for(i=0;i<r;i++)    
    {
      b[i]=drand(3.1,5);
      //  scanf("%lf",&b[i]);    
    }    


  int itercount=0;
  //////////////////////////////////////////////
  //////////////////////////////////////////////
  // inicio loop para matriz triangular superior


  /// w es el numero de la columna, repetimos por todas las columnas:
  for(int w=0; w<r; w++)
    {


      printf("//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n triangulacion renglon %d, numero de operaciones hasta ahora: %d",w, itercount);
      printf("la matriz aumentada a resolver en iteracion %d es: \n",w);

      fprintf(gnuplot, "splot '-' pt -1 ps 1.25\n");

      ///// imprimimos matriz
      for(i=0;i<r;i++)    
	{

	  for(j=0;j<c;j++)    
	    {
	      fprintf(gnuplot, "%d %d %lf\n",i,j,a[i][j]);

	      //fprintf(gnuplot, "%d %d %lf\n",j,i,a[i][j]);
	      //printf("%lf\t",a[i][j]);

	    }
	  fprintf(gnuplot, "%d %d %lf\n",i,r+1,b[i]);
	  fprintf(gnuplot, "\n");

	  //printf("|\t %lf ]\n", b[i]);

	}

      fprintf(gnuplot, "e\n");


  
      // ordenamos los vectores basandonos en su primera entrada


      for(int i =w; i<r;i++)
	{
	  if(abs(a[w][w])<abs(a[i][w]))
	    {
	      itercount++;
	      printf("cambiando filas %d con %d\n",w,i); 
		     for (j=0; j<c; j++)
		       {
			 a[i][j]-=a[w][j];
			 a[w][j]+=a[i][j];
			 a[i][j]=a[w][j]-a[i][j];
			 
			 b[i] -= b[w];
			 b[w] += b[i];
			 b[i] = b[w] - b[i];

		       }
		     }

	}

       
	
      //      if(abs(a[w][w]) <epsilon)
      if(a[w][w] == 0)
	{
	  printf("matriz no es invertible\n");
	  return 1;
	}



      //for printing result
      
      printf("despues de los cambios queda: \n");

      fprintf(gnuplot, "splot '-' pt -1 ps 1.25\n");
      for(i=0;i<r;i++)    
	{
	  ////printf("[");
	  for(j=0;j<c;j++)    
	    {
	      fprintf(gnuplot, "%d %d %lf\n",i,j,a[i][j]);
	      //  printf("%lf\t",a[i][j]);

	    }
	  fprintf(gnuplot, "%d %d %lf\n",i,r+1,b[i]);
	  fprintf(gnuplot, "\n");
	  // printf("|\t %lf ]\n", b[i]);

	}

      fprintf(gnuplot, "e\n");
      
      
      /// volvemos unitaria la primera fila de la matriz
      printf("volviendo unitario el primer elemento de la primera fila\n");
      sc=1/a[w][w];
      printf("fila a[%d][:] *= %lf\n",w,sc);
      itercount++;
      for (j=0; j<c; j++)
	{
	  a[w][j]*=sc;
	}
      b[w]*=sc;
      
      
      
      //for printing result
      
      //      printf("despues de los cambios queda: \n");

      fprintf(gnuplot, "splot '-' pt -1 ps 1.25\n");
      for(i=0;i<r;i++)    
	{
	  ////printf("[");
	  for(j=0;j<c;j++)    
	    {
	      fprintf(gnuplot, "%d %d %lf\n",i,j,a[i][j]);
	      //fprintf(gnuplot, "%d %d %lf\n",j,i,a[i][j]);
	      // printf("%lf\t",a[i][j]);

	    }
	  fprintf(gnuplot, "%d %d %lf\n",i,r+1,b[i]);
	  fprintf(gnuplot, "\n");
	  //printf("|\t %lf ]\n", b[i]);

	}

      fprintf(gnuplot, "e\n");
      
      
      // volvemos cero todas las primeras entradas de todas las otras filas
      // pivote
      printf("volviendo cero las entradas de los demas vectores bajo la diagonal\n");
      for (j=w+1; j<c; j++)
	{
	  sc = -a[j][w]; // tomamos el primer elemento de la fila

	  //	  printf("pivote fila %d con %d a[%d][:] += %lf a[%d][:]\n",w,j,w,sc,j);
	  itercount++;

	  for(k=0; k<c; k++)
	    {
	      //printf("a[%d][%d]+= %lf*a[%d][%d]",j,k,sc,w,k);
	      //printf("= %lf + %lf*%lf\n",a[j][k],sc,a[w][k]);
	      a[j][k]+= sc*a[w][k];
	      // printf("a[j][k]= %lf \n",a[j][k]); 
	    }
	  b[j]=b[j]+sc*b[w];
	}
      
      //for printing result
      
      printf("queda: \n");
      fprintf(gnuplot, "splot '-' pt -1 ps 1.25\n");
      for(i=0;i<r;i++)    
	{
	  //printf("[");
	  for(j=0;j<c;j++)    
	    {
	      fprintf(gnuplot, "%d %d %lf\n",i,j,a[i][j]);
	      //fprintf(gnuplot, "%d %d %lf\n",j,i,a[i][j]);

	      //printf("%lf\t",a[i][j]);

	    }
	  fprintf(gnuplot, "%d %d %lf\n",i,r+1,b[i]);
	  fprintf(gnuplot, "\n");
	  //printf("|\t %lf ]\n", b[i]);

	}

      fprintf(gnuplot, "e\n");
     
    }//// fin loop triangulacion
  //////////////////////////////
  //  ///  ///  ///  ///  ///  /
  // inicio loop diagonalizacion
  for (int q =r-1; q>-1; q--)
    {
      printf("//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n diagonalizacion renglon %d, numero de operaciones hasta ahora: %d",q, itercount);   
      // pivote
      printf("volviendo cero las entradas de los demas vectores arriba de la diagonal\n");
      for (j=q-1; j>-1; j--)
	{
	  sc = -a[j][q]; // tomamos el ultimo elemento de la fila
	  //	  printf("pivote fila %d con %d a[%d][:] += %lf a[%d][:]\n",j,q,j,sc,q); 
	  itercount++;

	  for(k=0; k<c; k++)
	    {

	      a[j][k]+= sc*a[q][k];
	      // printf("a[j][k]= %lf \n",a[j][k]); 
	    }
	  b[j]+=sc*b[q];
	}
      
      //for printing result
      
      printf("queda: \n");
      
      fprintf(gnuplot, "splot '-' pt -1 ps 1.25\n");
      for(i=0;i<r;i++)    
	{
	  //printf("[");
	  for(j=0;j<c;j++)    
	    {
	      fprintf(gnuplot, "%d %d %lf\n",i,j,a[i][j]);
	      //fprintf(gnuplot, "%d %d %lf\n",j,i,a[i][j]);
	      fprintf(arch, "%d %d %lf\n",i,j,a[i][j]);
	      //printf("%lf\t",a[i][j]);

	    }
	  fprintf(gnuplot, "%d %d %lf\n",i,r+1,b[i]);
	  fprintf(gnuplot, "\n");
	  printf("|\t %lf ]", b[i]);

	  fprintf(arch, "%d %d %lf\n",i,r+1,b[i]);
	  fprintf(arch, "\n");

	}

      fprintf(gnuplot, "e\n");
    }
  fclose(gnuplot);
  fclose(arch);

  return 0;  
}  

