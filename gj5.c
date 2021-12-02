#include<stdio.h>    
#include<stdlib.h>  
#define n 1000
int main(){

  // lee una matriz
  double a[n][n],b[n],sc;
  int r,c,i,j,k;    
  //  system("cls");  
  printf("numero de filas=");    
  scanf("%d",&r);    
  printf("numero columnas=");    
  scanf("%d",&c);    
  printf("elementos de la primera matriz=\n");    
  for(i=0;i<r;i++)    
    {    
      for(j=0;j<c;j++)    
	{
	  printf("a[%d][%d]= ",i,j); 
	  scanf("%lf",&a[i][j]);    
	}    
    }    

  printf("elementos del vector=\n");    
  for(i=0;i<r;i++)    
    {    
      scanf("%lf",&b[i]);    
    }    
          

  
  // inicio loop para matriz triangular superior
  for(int w=0; w<r; w++)
    {
      // imprimimos la matriz en la iteracion

      printf("la matriz aumentada a resolver en iteracion %d es: \n",w);
      for(i=0;i<r;i++)    
	{
	  printf("[");
	  for(j=0;j<c;j++)    
	    {    
	      printf("%lf\t",a[i][j]);

	    }    
	  printf("|\t %lf ]\n", b[i]);

	}

      
      // refrescamos las matrices temporales
  
      // ordenamos los vectores basandonos en su primera entrada


      for(int i =w; i<r;i++)
	{
	  if(abs(a[w][w])<abs(a[i][w]))
	    {
	      printf("cambiando filas %d con %d\n",w,i); 
		     for (j=0; j<c; j++)
		       {
			 a[i][j]-=a[w][j];
			 a[w][j]+=a[i][j];
			 a[i][j]=a[w][j]-a[i][k];
			 
			 b[i] -= b[w];
			 b[w] += b[i];
			 b[i] = b[w] - b[i];

		       }
		     }

	}

       
	
      if(a[w][w] ==0)
	{
	  printf("matriz no es invertible\n");
	  return 1;
	}



      //for printing result
      
      printf("despues de los cambios queda: \n");
      for(i=0;i<r;i++)    
	{
	  printf("[");
	  for(j=0;j<c;j++)    
	    {    
	      printf("%lf\t",a[i][j]);
	  
	    }    
	  printf("|\t %lf ]\n", b[i]);
	  
	}
      
      
      /// volvemos unitaria la primera fila de la matriz
      printf("volviendo unitario el primer elemento de la primera fila\n");
      sc=1/a[w][w];
      for (j=0; j<c; j++)
	{
	  printf("%lf =a[%d][%d] *= %lf\n", a[w][j],w,j,sc); 
	  a[w][j]*=sc;
	}
      b[w]*=sc;
      
      
      
      //for printing result
      
      printf("despues de los cambios queda: \n");
      for(i=0;i<r;i++)    
	{
	  printf("[");
	  for(j=0;j<c;j++)    
	    {    
	      printf("%lf\t",a[i][j]);
	  
	    }    
	  printf("|\t %lf ]\n", b[i]);
	  
	}
      
      
      // volvemos cero todas las primeras entradas de todas las otras filas
      // pivote
      printf("volviendo cero las entradas de los demas vectores bajo la diagonal\n");
      for (j=w+1; j<c; j++)
	{
	  sc = -a[j][w]; // tomamos el primer elemento de la fila
	  for(k=0; k<c; k++)
	    {
	      printf("a[%d][%d]+= %lf*a[%d][%d]",j,k,sc,w,k);
	      printf("= %lf + %lf*%lf\n",a[j][k],sc,a[w][k]); 
	      a[j][k]+= sc*a[w][k];
	      // printf("a[j][k]= %lf \n",a[j][k]); 
	    }
	  b[j]=b[j]+sc*b[w];
	}
      
      //for printing result
      
      printf("queda: \n");
      
      for(i=0;i<r;i++)    
	{
	  printf("[");
	  for(j=0;j<c;j++)    
	    {    
	      printf("%lf\t",a[i][j]);
	      
	    }    
	  printf("|\t %lf ]\n", b[i]);
	  
	}
    }
  // inicio loop diagonalizacion
  for (int q =r-1; q>-1; q--)
    {
   
      // pivote
      printf("volviendo cero las entradas de los demas vectores arriba de la diagonal\n");
      for (j=q-1; j>-1; j--)
	{
	  sc = -a[j][q]; // tomamos el primer elemento de la fila
	  for(k=0; k<c; k++)
	    {
	      printf("a[%d][%d]+= %lf*a[%d][%d]",j,k,sc,q,k);
	      printf("= %lf + %lf*%lf\n",a[j][k],sc,a[q][k]); 
	      a[j][k]+= sc*a[q][k];
	      // printf("a[j][k]= %lf \n",a[j][k]); 
	    }
	  b[j]=b[j]+sc*b[q];
	}
      
      //for printing result
      
      printf("queda: \n");
      
      for(i=0;i<r;i++)    
	{
	  printf("[");
	  for(j=0;j<c;j++)    
	    {    
	      printf("%lf\t",a[i][j]);
	      
	    }    
	  printf("|\t %lf ]\n", b[i]);
	  
	}
    }
  return 0;  
}  

