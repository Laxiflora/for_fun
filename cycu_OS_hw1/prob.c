#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH_LENGTH 64
#define DATA_LENGTH 500001
struct ThreadArgs{
    int* data;
    int start;
    int end;
};

struct Package{
    struct ThreadArgs* args;
    int* cutPoint;
};

void _bubbleSort(void* args){
    struct ThreadArgs* input = (struct ThreadArgs*)args;
    if(input->start > input-> end){  // no need to sort
        return;
    }
    int start = input->start;
    int end = input->end;
    for(int i=start;i<=end;i++){
        for(int j=start;j<=end;j++){
            if(input->data[i]<input->data[j]){
                int temp = input->data[i];
                input->data[i] = input->data[j];
                input->data[j] = temp;
            }
        }
    }
    // for(int i=start;i<=end;i++){
    //     for(int j=i+1;j<=end;j++){
    //         if(input->data[i]>input->data[j]){
    //             printf("Bubble Result Wrong!\n");
    //             return;
    //         }
    //     }
    // }
    return;
}

void* bubbleSort(void* args){
    struct ThreadArgs* input = (struct ThreadArgs*)args;
    if(input->start > input-> end){  // no need to sort
        pthread_exit(NULL);
    }
    int start = input->start;
    int end = input->end;
    for(int i=start;i<=end;i++){
        for(int j=start;j<=end;j++){
            if(input->data[i]<input->data[j]){
                int temp = input->data[i];
                input->data[i] = input->data[j];
                input->data[j] = temp;
            }
        }
    }
    // for(int i=start;i<=end;i++){
    //     for(int j=i+1;j<=end;j++){
    //         if(input->data[i]>input->data[j]){
    //             printf("Bubble Result Wrong!\n");
    //             pthread_exit(NULL);
    //         }
    //     }
    // }
    pthread_exit(NULL);

}



//in this function, we copy a new array from data, then perform merge, then copy the finisted
//data back to int* data;
void merge(int* data, int start , int middle , int end){
    if(start>middle){ //no need to sort
        return;
    }
    int temp[end-start+1];
    for(int i=start,j=0;i<=end;i++,j++){
        temp[j] = data[i];
       // printf("%d\t",temp[j]);
    }
    int mid = middle - start;
    int left = 0;
    int right = mid+1;
    int index = start;
    int tail = end-start;
    while(left<=mid && right <= tail){
        if(temp[left]<=temp[right]){
            data[index++] = temp[left++];
        }
        else{
            data[index++] = temp[right++];
        }
    }
    while(left<=mid){
        data[index++] = temp[left++];
    }
    while(right<=tail){
        data[index++] = temp[right++];
    }
    if(index-1 != end){
    }

}

int checkResult(int* data, int data_count){
    for(int i=0;i<data_count;i++){
        for(int j=i+1;j<data_count;j++){
            if(data[i]>data[j]){
                printf("Result Wrong! when i= %d, j=%d\n",i,j);
                return 0;
            }
        }
    }
    return 1;
}

void printArray(int* data,int data_count){
    FILE* fd = fopen("output/myout","w+");
    if(fd == NULL){
        perror("Error ");
        return;
    }
    for(int i=0;i<data_count;i++){
        char out[34] = {'\0'};
        sprintf(out,"%d",data[i]);
        fwrite(out, sizeof( char ), strlen( out ), fd);
        fwrite("\n", sizeof( char ), strlen( "\n" ), fd);
    }
    fclose(fd);
}
void mergeSort(int* data, int* cutPoint,int k, int data_count){
    int slice=0;  //we need this variable to fit the interval so it can merge perfectly
    int end=0;
    int start=0;
    int mid=0;
    for(int epoch = 2,i=1;i< k+1 ;i*=2,epoch*=2){
        slice=0;  //we need this variable to fit the interval so it can merge perfectly
        while((slice+2*i)<k+1){
            start = cutPoint[slice]+1;
            end = cutPoint[slice+2*i];
            mid = cutPoint[slice+i];
            printf("Args range from %d to %d , mid = %d\n",start,end,mid);
            merge(data,start,mid,end);
            slice+=epoch;
        }
    }
    mid = end;
    start = 0;
    end = data_count-1;
    printf("Args range from %d to %d , mid = %d\n",start,end,mid);
    merge(data,start,mid,end);
}


struct Package sliceData(int* data,int data_count,int k){
    int interval = data_count/k;
    struct Package _return;
    _return.cutPoint = malloc(sizeof(int)*(k+1));
    int * cutPoint = _return.cutPoint;
    cutPoint[0]=-1;
    _return.args = malloc(sizeof(struct ThreadArgs)*k);
    struct ThreadArgs* args = _return.args;
    int track = -1;
    //cut the data into k-1 part
    for(int i=0;i<k-1;i++){
        args[i].data = data;
        args[i].start = track+1;
      //  printf("Part %d args range from %d to ",i+1,track+1);
        track+=interval;
        args[i].end = track;
        cutPoint[i+1] = track;
    }
    //the remaining part
 //   printf("last part args range from %d to %d\n",track+1,data_count-1);
    args[k-1].data = data;
    args[k-1].start = track+1;
    args[k-1].end = data_count-1;
    cutPoint[k] = args[k-1].end;
    return _return;
}

void bubbleSortWithSingleProcess(int* temp,int data_count,int k){
    printf("select method: bubble sort using single process.\n");
    int* data = malloc(sizeof(int)*data_count);
    for(int i=0;i<data_count;i++){
        data[i] = temp[i];
    }
    struct Package processed_data = sliceData(data,data_count,k);
    processed_data.args[0].start = 0;
    processed_data.args[0].end = data_count-1;
    processed_data.args[0].data = data;
    _bubbleSort((void*)&processed_data.args[0]);
    // if(checkResult(data,data_count) == 1){
    //       printArray(data,data_count);
    // }
}

void sortWithSingleProcess(int* temp,int data_count,int k){
    printf("select method: k-way merge sort using single process.\n");
    int* data = malloc(sizeof(int)*data_count);
    for(int i=0;i<data_count;i++){
        data[i] = temp[i];
    }
    struct Package processed_data = sliceData(data,data_count,k);
    for(int i=0;i<k;i++){
        printf("bubble from %d to %d \n",processed_data.args[i].start,processed_data.args[i].end);
        _bubbleSort((void*)&processed_data.args[i]);
    }
    mergeSort(data,processed_data.cutPoint,k,data_count);
    // if(checkResult(data,data_count) == 1){
    //     printArray(data,data_count);
    // }
}





void sortWithThread(int* temp,int data_count,int k){
    printf("select method: k-way merge sort using %d multithread.\n",k);
    int* data = malloc(sizeof(int)*data_count);
    for(int i=0;i<data_count;i++){
        data[i] = temp[i];
    }
    pthread_t t[k];
    struct Package processed_data = sliceData(data,data_count,k);
    for(int i=0;i<k;i++){
        pthread_create(&(t[i]), NULL, bubbleSort, (void*)&processed_data.args[i]); // 建立子執行緒
    }
    for(int i=0;i<k;i++){
        pthread_join(t[i],NULL);
    }
    mergeSort(data,processed_data.cutPoint,k,data_count);
    // if(checkResult(data,data_count) == 1){
    //       printArray(data,data_count);
    // }
}

void sortWithProcess(int* temp,int data_count,int k){
    printf("select method: k-way merge sort using %d multiprocess.\n",k);
    int* data;
    data = (int*)mmap(NULL,sizeof(int)*data_count,PROT_WRITE | PROT_READ,MAP_SHARED | MAP_ANONYMOUS,-1,0);
    if(data == MAP_FAILED){
        perror("ERROR ");
        return;
    }
    for(int i=0;i<data_count;i++){
        data[i] = temp[i];
    }
    
    struct Package processed_data = sliceData(data,data_count,k);
    int pid[k];
    for(int i=0;i<k;i++){
        pid[i] = fork();
        if(pid[i]==0){
            bubbleSort((void*)&processed_data.args[i]);
            exit(0);
        }
        else{
            continue;
        }
    }
    for(int i=0;i<k;i++){
        wait(NULL);
    }
    mergeSort(data,processed_data.cutPoint,k,data_count);
    // if(checkResult(data,data_count) == 1){
    //       printArray(data,data_count);
    // }


}





int main(int argc,char** argv){
    char path[PATH_LENGTH+1];
    printf("file path:\n");
    scanf("%s",path);
    FILE* fd = fopen(path,"r");
    if(fd == NULL){
        perror("Error ");
        return 0;
    }
    int input[DATA_LENGTH];
    int data_count = 0;
    for(int i=0;!feof(fd);i++){
        fscanf(fd,"%d",&input[i]);
        data_count++;
    }
    printf("cut to k slice:\n");
    int k;
    scanf("%d",&k);
    printf("enter method number:\n");
    int method;
    scanf("%d",&method);
    switch(method){
        case 2:
            sortWithSingleProcess(input,data_count,k);
            break;
        case 1:
            bubbleSortWithSingleProcess(input,data_count,k);
            break;
        case 3:
            sortWithProcess(input,data_count,k);
            break;
        case 4:
            sortWithThread(input,data_count,k);
            break;
        default:
            printf("no.");
            break;
    }
    fclose(fd);
    return 0;


}