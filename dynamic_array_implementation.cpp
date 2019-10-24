#include "../include/dynamic_array.hpp"

using namespace std;

//Given just for reference. Only the class name and function names should match.
class dynamic_array_implementation : public dynamic_array
{
private:
    int num_ele;
    int cap;
    int* arr;
    double increase_factor;
    double decrease_factor;

    void initialize(int from){
        for(size_t i = from; i<cap;i++){
            arr[i] = 0;
        }
    }


    void expand(){
        cap *=increase_factor;
        int *temp = new int[cap];
        for(size_t i=0;i<num_ele;i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr=temp;
        initialize(num_ele);
    }

    void exp_zero(){
        cap =1;
        int *temp = new int[cap];
        for(size_t i=0;i<num_ele;i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr=temp;
        initialize(num_ele);
    }
    
    int ceil(double n){
        if((n-(int)n)!=0.0){
            return((int)n +1);
        }
        return (int)n;
    }   

public:
    dynamic_array_implementation(){
        increase_factor=3;
        decrease_factor=0.25;
        cap = 0;
        num_ele =0;
        arr = new int[cap];
    }
    int get_size(){
        return(num_ele);
    }

    void set_increase_factor_table_size(double num){
        increase_factor=num;
    }
    
    int get_capacity(){
        return(cap);
    };

    void append(int el){
        if(cap==0){
            exp_zero();
        }
        if(num_ele>=cap){
            expand();
        }
        arr[num_ele++]=el;

    }
    
    void set_load_factor_reduction(double num){
        decrease_factor=num;
    }
    void pop(){
        if(num_ele==1){
            cap=0;
            num_ele--;
            int *temp = new int[cap];
            for(size_t i=0;i<num_ele;i++){
                temp[i] = arr[i];
            }
            delete[] arr;
            arr=temp;
            initialize(num_ele);
            return;
        }
        if(num_ele<=0){
            return;
            //throw("array empty arleady");
        }
        else{
            arr[--num_ele]=0;
            double load_factor = (double)num_ele / cap;
            if(load_factor<=decrease_factor){
                cap= ceil(decrease_factor*increase_factor*cap);
                int *temp = new int[cap];
                for(size_t i=0;i<num_ele;i++){
                    temp[i] = arr[i];
                }
                delete[] arr;
                arr=temp;
                initialize(num_ele);
            }
        }
        return;
    }
    int get(int index){
        if(index<0 || index>=num_ele){
            throw("out of Bounds error!");
        }
        return arr[index];
    }

    ~dynamic_array_implementation(){
        delete[]arr;
    }
};
