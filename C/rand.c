#include <stdio.h>
//#include <math.h>
#include <windows.h>

#define PI 3.14
#define rad 0.59
#define eps 8.54

int main()
{
   	/*
    float rad,area,perm;
    printf("Input the radius for your circle:  ");
    scanf("%f", &rad);
    printf("radius  of  circle: %f \n",  rad);
    area=PI*rad*rad;
    perm=2*PI*rad;
    printf("Area of circle: %.4f \nPerimeter of circle: %.4f\n",area,perm);
    */

    
    float area, dist, cap, cap1, loss;
    scanf("%f %f", &area, &dist);
    printf("\n\nValue of Epsilon: %.6fe-12\n\n", eps);
    

    /*
    for(long i = 0; i<=5;i++)
    {
        cap = eps * area / dist/100.5;
        if(i == 0)
        {
            cap1 = cap;
        }
        printf("Current value of distanc=%0.6f\n", dist);
        printf("Current value of Area=%0.6f\n", area);
        printf("Cap value = %0.5fe-11 farads with d = %.4f m, A=%.5f m^2\n===============\n\n", cap, dist, area);
        area *= 1.05;
        dist *= 1.1;
    }
	*/
	
	
    cap = eps * area / dist/100.5;
    cap1 = cap;
    printf("Current value of distanc=%0.6f\n", dist);
    printf("Current value of Area=%0.6f\n", area);
    printf("Cap value = %0.5fe-11 farads with d = %.4f m, A=%.5f m^2\n===============\n\n", cap, dist, area);
    area *= 1.05;
    dist *= 1.1;

    cap = eps * area / dist/100.5;
    printf("Current value of distanc=%0.6f\n", dist);
    printf("Current value of Area=%0.6f\n", area);
    printf("Cap value = %0.5fe-11 farads with d = %.4f m, A=%.5f m^2\n===============\n\n", cap, dist, area);
    area *= 1.05;
    dist *= 1.1;

    cap = eps * area / dist/100.5;
    printf("Current value of distanc=%0.6f\n", dist);
    printf("Current value of Area=%0.6f\n", area);
    printf("Cap value = %0.5fe-11 farads with d = %.4f m, A=%.5f m^2\n===============\n\n", cap, dist, area);
    area *= 1.05;
    dist *= 1.1;

    cap = eps * area / dist/100.5;
    printf("Current value of distanc=%0.6f\n", dist);
    printf("Current value of Area=%0.6f\n", area);
    printf("Cap value = %0.5fe-11 farads with d = %.4f m, A=%.5f m^2\n===============\n\n", cap, dist, area);
    area *= 1.05;
    dist *= 1.1;

    cap = eps * area / dist/100.5;
    printf("Current value of distanc=%0.6f\n", dist);
    printf("Current value of Area=%0.6f\n", area);
    printf("Cap value = %0.5fe-11 farads with d = %.4f m, A=%.5f m^2\n===============\n\n", cap, dist, area);
    
    loss = (cap1 - cap)/cap1*100;
    printf("Percentage loss in Cap=%.6f with 10 percent cumulative increase in d and 5 percent cumulative increase in A\n", loss);
    

    system("pause");
    return  0;
}