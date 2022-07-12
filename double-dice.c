#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//Berkay ÇAVUŞOĞLU - 040200616


// tek zarlı dizideki maksimumu bulmak için
int max_bul(int dizi[], int n)
{
	int max = 0;
	
	for(int i=0 ; i < 7; i ++)
	{
		if(dizi[i] > max)
		{
			max = dizi[i];
		}
	}
	return max;
}

// zar atmak için 

int zar()
{
		return rand()%6 + 1;
}


// 2 zarlı dizideki maksiumumu bulmak için

int max_bul2(int dizi2[], int n)
{
	int max = 0;
	
	for(int i=0 ; i < 12; i ++)
	{
		if(dizi2[i] > max)
		{
			max= dizi2[i];
		}
	}
	return max;
}

int main()
{
	srand(time(0));
	// başlangıçtaki n
	int n = 10000;
	int olcek = 100;
	
	// tek zarın toplamını saklamak için dizi
	int siklik[7] = {0};
	
	// n defa tekrarlanıyor ve toplanıyor
	
	for(int i=0 ; i<n; i++)
	{
		int a = zar();
		int sum = a;
		siklik[sum-1] += 1;
		
	}
	
	// maksimum değeri bulma
	int max = max_bul2(siklik,7);
	
	// histogramı çizdirme
	
	for(int i = max/olcek; i>=1; i--)
	{
		for(int j=0 ; j<6; j++)
		{
			if(siklik[j]/olcek>=i)
			{
				printf("*  ");
			}
			
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}
	
	printf("1  2  3  4  5  6\n");
	
	// iki zarın toplamını tutmak için dizi
	int siklik2[12] = {0};
	
	// n kez tekrarlanıyor ve toplanıyor
	
	for(int i=0 ; i<n; i++)
	{
		int a = zar();
		int b = zar();
		
		int sum = a+b;
		siklik2[sum-1] += 1;
		
	}
	
	// maksimum değeri bulma
	int max2 = max_bul2(siklik2,12);
	
	// histogramı çizdirme
	
	for(int i = max2/olcek; i>=1; i--)
	{
		for(int j=1 ; j<12; j++)
		{
			if(siklik2[j]/olcek>=i)
			{
				printf("*  ");
			}
			
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}
	
	printf("2  3  4  5  6  7  8  9 10 11 12\n");
		
	return 0;		
}
