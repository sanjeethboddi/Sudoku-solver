#include <stdio.h>
#include <stdlib.h>

enum{false,true};
int size,min_x,min_y,v;
struct node{
	int num;
	int count;
};


int is_grid(){
	if(size==(min_x*min_y))return true;
	else return false;
}

int is_error(int A[size][size],int value,int y,int x){
	int i,j;
	if(A[y][x]!=0 || value<0 || value>size)return true;
	
	else {
		for(i=x,j=y;i<size;i++)if(A[j][i]==value && value!=0 ){return true;}
        for(i=x,j=y;j<size;j++)if(A[j][i]==value && value!=0){return true;}
        for(i=x,j=y;i>=0;i--)if(A[j][i]==value && value!=0){return true;}
        for(i=x,j=y;j>=0;j--)if(A[j][i]==value && value!=0){return true;}
        
		for(j=y-(y%min_y);j<y-(y%min_y)+min_y;j++){
			for(i=x-(x%min_x);i<x-(x%min_x)+min_x!=0;i++){
				if (A[j][i]==value && value!=0)return true;
			}
		}
	}
    return false;
}

void input(int A[size][size],struct node * B[size]){
	int i=0,j=0;
	int temp;
	for(;i<size;i++){
		for(;j<size;j++){
			scanf("%d",&temp);
			if(is_error(A,temp,i,j)){
				printf("This does not make up a Sodoku.!.!.!\n");
				printf("exiting...!!\n");
				exit(0);
			}
			A[i][j]=temp;
			if(temp >0 && temp<=size )((B[temp-1])->count)--;
		}
		j=0;
	}
}

void print(int A[size][size]){
	printf("\n");
	for(int i=0;i<size;i++){
		printf("==");
	}
	printf("\n");
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	for(int i=0;i<size;i++){
		printf("==");
	}
	printf("\n");

}
int solver(int A[size][size],int numb,int x,int y,struct node * counter[size]){
    while(counter[numb]->count==0 && numb<=size) numb++;
    if(numb==size)return true;
    
    int i=x,j=y;
    for(;i<size;i++){
        for(;j<size;j++){
            v=is_error(A,counter[numb]->num,i,j);
            if(v)continue;
            A[i][j]=counter[numb]->num;
            counter[numb]->count--;
            if(counter[numb]->count==0){
                numb++;
                if(numb==size)return true;
                if(solver(A,numb,0,0,counter))return true;
                else{
                    numb--;
                    counter[numb]->count++;
                    A[i][j]=0;
                }
            }
            else{
                if(solver(A,numb,i+1,0,counter))return true;
                else{
                A[i][j]=0;
                counter[numb]->count++;
                }
            }
        }
        j=0;
    }
    return 0;
}

int main(){
	printf("enter grid length:\n");
	scanf("%d",&size);
	printf("enter min x and min y:\n");
	scanf("%d %d",&min_x,&min_y);
	if(!is_grid()){
		printf("Given inputs does make a proper grid:\n");
		printf("exitting...\n");
		exit(0);
	}
	int box[size][size];
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			box[i][j]=0;
			}
	}
	struct node * counter[size];
	for(int i=0;i<size;i++){
		counter[i]=(struct node *)malloc(sizeof(struct node));
		counter[i]->num=i+1;
		counter[i]->count=size;
	}
	input(box,counter);
	printf("Question is:\n");
	print(box);
	solver(box,0,0,0,counter);
	printf("\n\nAnswer is:\n");
	print(box);
	


}
