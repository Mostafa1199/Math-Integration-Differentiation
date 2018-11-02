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
float h;
float **calcs;
int row_index;
float u;
void Interface();
int Factorial(int n);
float Multibly_neg(float n,int counts);
int main(){
    Interface();
    h = Values[1].x-Values[0].x;
    //for initializing dynamic 2d array
    calcs = new float *[nOf_values];

    for(int i = 0;i<nOf_values;i++)
        calcs[i] = new float[nOf_values];
    //to fill the array with null values
    for(int i = 0 ;i<nOf_values; i++)
        for(int j = 0;j<nOf_values;j++)
            calcs[i][j] = NULL;
    //to fill th first column with F(x) values
    for(int i = 0;i<nOf_values;i++)
        calcs[i][0] = Values[i].Fx;
    //filling the row with calculations
    row_index = nOf_values-1;
    for(int i = 1;i<nOf_values;i++){
        for (int j = 0;j<row_index;j++)
            calcs[j][i] = calcs[j+1][i-1] - calcs[j][i-1];
        row_index--;
    }
    u = (demanded_value-Values[0].x)/h;
    for(int i=0;i<nOf_values;i++){
        result += (calcs[0][i]*Multibly_neg(u,i))/Factorial(i);
    }
    cout<<"L("<<demanded_value<<") = "<<result<<endl;
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
int Factorial(int n){
  return (n == 1 || n == 0) ? 1 : n*Factorial(n-1);
}
float Multibly_neg(float n,int counts){
    float rs = n;
    for(int i =0;i<(counts-1);i++)
        rs*=--n;
    if(counts == 0)
        return 1;
    else if(counts == 1)
        return n;
    else
        return rs;
}
