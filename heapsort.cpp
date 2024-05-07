#include<iostream>
using namespace std;

class heap{
  public:
    int arr[100];
    int size;
    
    heap()
    {
        arr[0]=-1;
        size=0;
    }
    void insert(int val)
    {
        size=size + 1;
        int index = size;
        arr[index] = val;
        
        while(index > 1)
        {
            int parent = index / 2;
            
            if(arr[parent] < arr[index])
            {
                int temp = arr[index];
                arr[index] = arr[parent];
                arr[parent] = temp;
                
                index = parent;
            }
            else
            {
                return;
            }
        }
    }
    
    void print()
    {
        for(int i=1;i<= size; i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
    
    void deleteheap()
    {
        if(size ==0)
        {
            return;
        }
        
        arr[1] = arr[size];
        size--;
        
        int i=1;
        
        while(i < size)
        {
            int leftchild= 2 * i;
            int rightchild= ( 2 * i) + 1;
            
            if(leftchild < size && arr[leftchild] > arr[i])
            {
                int temp = arr[i];
                arr[i] = arr[leftchild];
                arr[leftchild] = temp;
                
                i = leftchild;
            }
            else if(rightchild < size && arr[rightchild] > arr[i])
            {
                int temp = arr[i];
                arr[i] = arr[rightchild];
                arr[rightchild] = temp;
                
                i = rightchild;
            }
            else
            {
                return;
            }
        }
    }
};

void heapify(int arr[],int n,int i)
{
    int largest = i;
    int leftchild=2*i;
    int rightchild=(2*i)+1;
    
    if(leftchild < n && arr[leftchild] > arr[largest])
    {
        int temp = arr[largest];
        arr[largest] = arr[leftchild];
        arr[leftchild] = temp;
        
        largest= leftchild;
    }
    if(rightchild < n && arr[rightchild] > arr[largest])
    {
        int temp = arr[largest];
        arr[largest] = arr[rightchild];
        arr[rightchild] = temp;
        
        largest=rightchild;
    }
    if(largest !=i)
    {
        heapify( arr,n,largest);
    }
}
int main()
{
   heap h;
   h.insert(50);
   h.insert(55);
   h.insert(53);
   h.insert(52);
   h.insert(54);
   
   h.print();
   
   h.deleteheap();
   h.print();
   
   int arr[6]={-1,54,53,55,52,50};
   int n=5;
   for(int i=n/2;i>0;i--)
   {
       heapify(arr,n,i);
   }
   
    for(int i=1;i<=n;i++)
   {
       cout<<arr[i]<<" ";
   }
   
   
    return 0;
}
