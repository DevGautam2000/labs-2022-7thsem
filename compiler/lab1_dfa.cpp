/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Thu, August 04,2022 AT 19:45 
          DESCRIPTION:  dfa to accept a string of length less than equal to 
                        10 and containing a and b
*/

#include<iostream>
#include<string>

#define STRING_MAX_LEN 10

using namespace std;

struct state{
    int prev=0;
    char inp=' ';
};  

void printMessage(string msg){
    cout<<msg<<endl;
}

void checkValidDfa(string s){

    //check if length id valid
    if(s.size() > STRING_MAX_LEN){
        printMessage("Invalid string: Length is greater than "+to_string(STRING_MAX_LEN));
        return;
    }


    //check if string contains only a and b
    for(char c: s){
        if(c > 'b' or isdigit(c)){
            printMessage("Invalid string: Should only contain 'a' & 'b'. ");
            return;
        }
    }

    //check if valid dfa
    state st;

    for(char c: s){
        cout<<st.prev;

        if(c=='b')
            st.prev++;

        st.inp=c;
        cout<<" on input "<<st.inp<<" -> "<<st.prev<<endl;
    }


    printMessage("\nValid string : Accepted. The final state is: "+to_string(st.prev));
}

int main(){
    string s;
    cout<<"Enter a string: ";
    cin>>s;

    checkValidDfa(s);
    return 0;
}

/* 
INPUT/OUTPUT: 

Enter a string: abb

0 on input a -> 0
0 on input b -> 1
1 on input b -> 2

Valid string : Accepted. The final state is: 2

 */