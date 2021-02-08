#include<stdio.h>

typedef char HData;
typedef int Priority;
typedef int PriorityComp(HData d1,HData d2);

typedef struct _heap{
    PriorityComp * comp;
    int numofData;  
    HData heapArr[100];  
}Heap;

void HeapInit(Heap * ph,PriorityComp pc){
    ph->numofData = 0;
    ph->comp = pc;
}


int HIsEmpty(Heap * ph){
    if(ph->numofData == 0)
        return 1;
    else
        return 0;
}

int GetParentIDX(int idx){
    return idx/2;
}

int GetLChildIDX(int idx){
    return idx*2;
}

int GETRChildIDX(int idx){
    return (idx*2)+1;
}

//두 개의 자식 노드 중 높은 우선순위의 자식 노드 인덱스 값 반환
int GetHiPriChildIDX(Heap * ph,int idx){
    if(GetLChildIDX(idx) > ph->numofData)   //왼쪽 노드의 인덱스가 노드의 개수(마지막 인덱스)보다 큰 경우
        return 0;
    
    else if(GetLChildIDX(idx) == ph->numofData) //왼쪽 노드의 인덱스가 마지막 인덱스인 경우
        return GetLChildIDX(idx);   //왼쪽 노드의 인덱스 리턴, 다음 인덱스에 저장하면 된다.
    
    else{      //왼쪽 노드의 인덱스 마지막 인덱스 보다 작은 경우
        if(ph->comp(ph->heapArr[GetLChildIDX(idx)],ph->heapArr[GETRChildIDX(idx)]) < 0)  //왼쪽 노드의 우선 순위가 오른쪽 노드의 우선 순위보다 큰 경우(우선순위가 낮다)
            return GETRChildIDX(idx);   //오른쪽 노드 리턴
    
        else    
            return GetLChildIDX(idx);   
    }
}


void HInsert(Heap * ph,HData data){
    int idx = ph->numofData+1;  //노드의 개수(마지막 인덱스)를 늘려 인덱스로 지정

    while(idx != 1){    //루트 노드 전까지
        //if(pr < (ph->heapArr[GetParentIDX(idx)].pr)){   //부모 노드의 우선순위가 새로 들어올 노드의 우선순위보다 클 경우(우선순위가 낮다)
        if(ph->comp(data,ph->heapArr[GetParentIDX(idx)]) > 0){  //우선순위 기준 함수의 결과가 0보다 크면(첫번째 인자의 우선순위가 높다)  
            ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];  //새로 들어올 노드의 자리를 만들고 부모 노드 자리에 위치 시킨다.
            idx = GetParentIDX(idx);    //새로운 노드를 부모자리에 넣기위해 인덱스 저장
        }
        else
            break;
    }
    ph->heapArr[idx] = data;   //새로운 노드의 값을 저장한다.
    ph->numofData+=1;   
    printf("%c is inserted\n",data);
}

HData HDelete(Heap * ph){    
    HData retData = ph->heapArr[1];  //부모 노드
    HData lastElem = ph->heapArr[ph->numofData]; 

    int parentIdx = 1;
    int childIdx = GetHiPriChildIDX(ph,parentIdx);  //자리 바꾼 노드와 자식 노드의 우선순위 비교를 위한 childIdx
    
    if(ph->numofData == 1){             //마지막 노드를 출력해주기 위해
        return ph->heapArr[parentIdx]; 
    }

    while(childIdx == GetHiPriChildIDX(ph,parentIdx)){   //왼쪽 노드와 비교,
        //if(lastElem.pr <= ph->heapArr[childIdx].pr) 
        if(ph->comp(lastElem,ph->heapArr[childIdx]) >= 0)   //우선순위 기준 함수의 결과값이 0보다 크거나 같으면
            break;
        ph->heapArr[parentIdx] = ph->heapArr[childIdx]; //마지막 노드보다 우선순위가 높으니, 비교대상 노드(자식 노드)의 위치정보를 한 레벨 올림
        parentIdx = childIdx;   //인덱스 변경
    }
    
    ph->heapArr[parentIdx] = lastElem;  //마지막 노드의 위치를 최종 변경
    ph->numofData -= 1;
    
    
    return retData;
    
}

int DataPriorityComp(char ch1,char ch2){
    return ch1-ch2;
}

int main(){
    Heap heap;
    HeapInit(&heap,DataPriorityComp);

    HInsert(&heap,'A');
    HInsert(&heap,'B');
    HInsert(&heap,'C');
    HInsert(&heap,'D');
    HInsert(&heap,'E');


    while(1){
        printf("%c \n",HDelete(&heap));
    }
    // printf("%c \n",HDelete(&heap));
    // printf("%c \n",HDelete(&heap));
    // printf("%c \n",HDelete(&heap));
    // printf("%c \n",HDelete(&heap));
    // printf("%c \n",HDelete(&heap));
    return 0;
}