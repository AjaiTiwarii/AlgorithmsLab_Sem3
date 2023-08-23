#include<stdio.h>
#include<stdlib.h>



int maxsubarraynaive(int *a,int *n, int *m,int *l)
{
    int maxsum=a[0];
    for(int i=0;i<*n;i++)
    {
        int sum=0;
        for(int j=i;j<*n;j++)
        {
            sum+=a[j];
            if(sum>maxsum)
            {
                *m=i;
                *l=j;
                maxsum=sum;
                
            }
        }
    }
    return maxsum;
}

int maxcrossingsum(int *a,int *low,int *mid,int *high,int *maxleft,int *maxright)
{
    int leftsum=-9999;
    int sum=0,result;
    for(int i=*mid;i>=*low;i--)
    {
        sum+=a[i];
        if(sum>leftsum)
        {
            leftsum=sum;
            *maxleft=i;
        }
    }
    int rightsum=-9999;
    sum=0;
    for(int j=*mid+1;j<=*high;j++)
    {
        sum+=a[j];
        if(sum>rightsum)
        {
            rightsum=sum;
            *maxright=j;
        }
    }
    result = leftsum+rightsum;
    return result;
}


int maxsubarraysumdivcon(int *a, int low, int high, int *maxleft, int *maxright) {
    if (high == low) {
        *maxleft = low;
        *maxright = high;
        return a[low];
    } else {
        int mid = (low + high) / 2;
        int leftlow, lefthigh, leftsum;
        int rightlow, righthigh, rightsum;
        int crosslow, crosshigh, crosssum;

        leftsum = maxsubarraysumdivcon(a, low, mid, &leftlow, &lefthigh);
        rightsum = maxsubarraysumdivcon(a, mid + 1, high, &rightlow, &righthigh);
        crosssum = maxcrossingsum(a, &low, &mid, &high, &crosslow, &crosshigh);

        if (leftsum >= rightsum && leftsum >= crosssum) {
            *maxleft = leftlow;
            *maxright = lefthigh;
            return leftsum;
        } else if (rightsum >= leftsum && rightsum >= crosssum) {
            *maxleft = rightlow;
            *maxright = righthigh;
            return rightsum;
        } else {
            *maxleft = crosslow;
            *maxright = crosshigh;
            return crosssum;
        }
    }
}


int main()
{
    int n, k, choice,control, i, maxsum;
    int m,l,maxleft,maxright;
    printf("Enter the number of array elements-");
    scanf("%d", &n);
    int *a=(int *)malloc(n*sizeof(int));
    printf("Enter the array elements-");
    for(i=0;i<n;i++)
    {
        scanf("%d", &a[i]);
    }
    int low=0,high=n-1;
    int mid=(low+high)/2;
    do
    {
        printf("1.Find the maximum subarray using naive approach");
        printf("\n");
        printf("2.Find the maximum subarray using divide and conquer");
        printf("\n");
        printf("Enter your option:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                maxsum=maxsubarraynaive(a,&n,&m,&l);
                printf("The maximum sum is: %d", maxsum);
                printf("\n");
                printf("The maximum subarray is ");
                printf("\n");
                for(k=m;k<=l;k++)
                {
                    printf("A[%d] = %d ", k, a[k]);
                }
                break;
            case 2:
                maxsum = maxsubarraysumdivcon(a,low,high,&maxleft,&maxright);
                printf("The maximum sum is: %d", maxsum);
                printf("\n");
                printf("The maximum subarray is ");
                for(k=maxleft;k<=maxright;k++)
                {
                printf("A[%d] = %d ", k, a[k]);
                }
                break;
        }

        printf("\nyes[0]");
        scanf("%d",&control);
    }while(control == 0);
    return 0;
}