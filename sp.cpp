#include <iostream>
using namespace std;

class sparseMatrix
{
public:
	int rows,cols,size;
	int **sp;
	void input();
	void display();
	void disp_matrix();
	sparseMatrix add(sparseMatrix b );
	sparseMatrix dif(sparseMatrix b);
} ;

void sparseMatrix::input()
{
	int i,j,m,n;
	int arr[10][10];
	cout<<"Enter row size: ";
	cin>>m;
	rows=m;
	cout<<"Enter column size";
	cin>>n;
	cols=n;
	cout<<"Enter elements"<<endl;
	for(i=0;i<m;i++)
		for (j=0;j<n;j++)
			cin>>arr[i][j];

	size=0;
	for (i=0;i<m;i++)
		for (j=0;j<n;j++)
			if(arr[i][j]!=0)
				size++;
	
	sp = new int*[3];
	for(i=0;i<3;i++)
		sp[i] = new int[size];
	int k=0;
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(arr[i][j] != 0)
			{
				sp[0][k] = i;
				sp[1][k] = j;
				sp[2][k] = arr[i][j];
				k++;
			}
		}
	}
}

void sparseMatrix::display()
{
	int k;
	for(k=0;k<size;k++)
		cout<<sp[0][k]<<"  ";
	cout<<endl;
	for(k=0;k<size;k++)
		cout<<sp[1][k]<<"  ";
	cout<<endl;
	for(k=0;k<size;k++)
		cout<<sp[2][k]<<"  ";
	cout<<endl;
}

void sparseMatrix::disp_matrix()
{
	int m = rows;
	int n = cols;
	int i,j,k=0;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(sp[0][k] == i && sp[1][k] == j)
			{
				cout<<sp[2][k]<<"   ";
				k++;
			}
			else
				cout<<0<<"   ";
		}
		cout<<endl;
	}
	cout<<endl;
}

sparseMatrix sparseMatrix::add(sparseMatrix b)
{
	int k;
	sparseMatrix c ;
	 // verify compatibility
   if (rows != b.rows || cols != b.cols)
   {
    	cout<<"dimensions does not match and hence cannot add"<<endl;
    	return c;          // incompatible matrices
   }

   // set characteristics of result c
   c.rows = rows;
   c.cols = cols;
   int cSize = 0;

   int i=0,j=0;

   // move through *this and b adding like terms

   while(i<size && j<b.size)
   {
     // row-major index plus cols of each term
     int tIndex = sp[0][i] * cols + sp[1][i];
     int bIndex = b.sp[0][j] * b.cols + b.sp[1][j];

     if (tIndex < bIndex)
     {// b term comes later
     	cSize++;
     	i++;

     }
     else {
      if (tIndex == bIndex)
           {// both in same position
           		cSize++;
           		i++;
           		j++;
           }
           else
           {
           		cSize++;
           		j++;

           }
          }

     }

   // copy over remaining terms
   for (; i < size; i++)
   {
       cSize++;
    }
   for (; j < b.size; j++)
   {
     cSize++;
   }
   c.size = cSize;

   c.sp = new int*[3];
	for(i=0;i<3;i++)
		c.sp[i] = new int[cSize];
	k=0;
   // move through *this and b adding like terms
	i=0;j=0;
   while(i<size && j<b.size)
   {
     // row-major index plus cols of each term
     int tIndex = sp[0][i] * cols + sp[1][i];
     int bIndex = b.sp[0][j] * cols + b.sp[1][j];

     if (tIndex < bIndex)
     {// b term comes later
     	c.sp[0][k] = sp[0][i];
     	c.sp[1][k] = sp[1][i];
     	c.sp[2][k] = sp[2][i];
     	i++;

     }
     else 
     {
      if (tIndex == bIndex)
           {// both in same position
           		c.sp[0][k] = sp[0][i];
           		c.sp[1][k] = sp[1][i];
           		c.sp[2][k] = sp[2][i]+b.sp[2][j];
           		i++;
           		j++;
           }
           else
           {
           		c.sp[0][k] = b.sp[0][j];
           		c.sp[1][k] = b.sp[1][j];
           		c.sp[2][k] = b.sp[2][j];
           		j++;

           }
       }
       k++;

     }

   // copy over remaining terms
   for (; i < size; i++)
   {
       c.sp[0][k] = sp[0][i];
     	c.sp[1][k] = sp[1][i];
     	c.sp[2][k] = sp[2][i];
     	k++;
    }
   for (; j < b.size; j++)
   {            c.sp[0][k] = b.sp[0][j];
           		c.sp[1][k] = b.sp[1][j];
           		c.sp[2][k] = b.sp[2][j];
           		k++;    
   }
   return c;

}


sparseMatrix sparseMatrix::dif(sparseMatrix b)
{
	int k;
	sparseMatrix c ;
	 // verify compatibility
   if (rows != b.rows || cols != b.cols)
   {
    	cout<<"dimensions does not match and hence cannot add"<<endl;
    	return c;          // incompatible matrices
   }

   // set characteristics of result c
   c.rows = rows;
   c.cols = cols;
   int cSize = 0;

   int i=0,j=0;

   // move through *this and b adding like terms

   while(i<size && j<b.size)
   {
     // row-major index plus cols of each term
     int tIndex = sp[0][i] * cols + sp[1][i];
     int bIndex = b.sp[0][j] * b.cols + b.sp[1][j];

     if (tIndex < bIndex)
     {// b term comes later
     	cSize++;
     	i++;

     }
     else {
      if (tIndex == bIndex)
           {// both in same position
           	  if(sp[2][i]-b.sp[2][j] != 0)
           	  		cSize++;
           	  
           	  	i++;
           	  	j++;
    
           }
           else
           {
           		cSize++;
           		j++;

           }
          }

     }

   // copy over remaining terms
   for (; i < size; i++)
   {
       cSize++;
    }
   for (; j < b.size; j++)
   {
     cSize++;
   }
   c.size = cSize;

   c.sp = new int*[3];
	for(i=0;i<3;i++)
		c.sp[i] = new int[cSize];
	k=0;
   // move through *this and b adding like terms
	i=0;j=0;
   while(i<size && j<b.size)
   {
     // row-major index plus cols of each term
     int tIndex = sp[0][i] * cols + sp[1][i];
     int bIndex = b.sp[0][j] * cols + b.sp[1][j];

     if (tIndex < bIndex)
     {// b term comes later
     	c.sp[0][k] = sp[0][i];
     	c.sp[1][k] = sp[1][i];
     	c.sp[2][k] = sp[2][i];
     	i++;
     	k++;

     }
     else 
     {
      if (tIndex == bIndex)
        {// both in same position
           	  if(sp[2][i]-b.sp[2][j] != 0 )
           	  {
           		c.sp[0][k] = sp[0][i];
           		c.sp[1][k] = sp[1][i];
           		c.sp[2][k] = sp[2][i]-b.sp[2][j];
           		k++;
           	  }
           		i++;
           		j++;
           }
           else
           {
           		c.sp[0][k] = b.sp[0][j];
           		c.sp[1][k] = b.sp[1][j];
           		c.sp[2][k] = -b.sp[2][j];
           		j++;
           		k++;

           }
       }
       

     }

   // copy over remaining terms
   for (; i < size; i++)
   {
       c.sp[0][k] = sp[0][i];
     	c.sp[1][k] = sp[1][i];
     	c.sp[2][k] = sp[2][i];
     	k++;
    }
   for (; j < b.size; j++)
   {            c.sp[0][k] = b.sp[0][j];
           		c.sp[1][k] = b.sp[1][j];
           		c.sp[2][k] = -b.sp[2][j];
           		k++;    
   }
   return c;

}

int main(){
	sparseMatrix A,B,sum,dif;

	A.input();
	B.input();

	sum =  A.add(B);
	dif = A.dif(B);

	cout<<"Entered A matrix is"<<endl;
	A.disp_matrix();
	cout<<"Entered B matrix is"<<endl;
	B.disp_matrix();
	cout<<"The resultant sum matrix is"<<endl;
	sum.disp_matrix();
	cout<<"The resultant dif matrix is"<<endl;
	dif.disp_matrix();

	cout<<"-----------------------------------------------------------"<<endl;
	cout<<"Sparse Matrix of A is"<<endl;
	A.display();
	cout<<"Sparse Matrix of B is"<<endl;
	B.display();
	cout<<"Sparse Matrix of sum is"<<endl;
	sum.display();
	cout<<"Sparse Matrix of dif is"<<endl;
	dif.display();
	
	return 0;
}