#include <iostream>
using namespace std;
struct Pair{
    float Fx;
    float x;
};
int nOf_values;
Pair *Values;
float demanded_value;
float result = 0;
float Nominator = 1;
float Dominator = 1;
void Interface();
int main(){
    Interface();
    for(int i=0;i<nOf_values;i++){
        for(int j=0;j<nOf_values;j++){
            if(i!=j){
                Nominator *= (demanded_value-Values[j].x);
                Dominator *= (Values[i].x-Values[j].x);
            }
        }
        result +=((Nominator/Dominator)*Values[i].Fx);
        Nominator = 1;
        Dominator = 1;
    }
    cout<<"The result is " << result<<endl;
    return 0;
}
void Interface(){
    cout<<"How many Values will you Enter\n";
    cin>>nOf_values;
    Values = new Pair[nOf_values];
    for(int i=0;i<nOf_values;i++){
        cout<<"Enter x"<< i<<endl;
        cin>>Values[i].x;
        cout<<"Enter F"<< i<<endl;
        cin>>Values[i].Fx;
    }
    cout<<"What is the demanded value\n";
    cin>>demanded_value;
}