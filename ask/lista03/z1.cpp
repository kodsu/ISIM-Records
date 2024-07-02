#include<bits/stdc++.h> 

using namespace std; 

struct fp_num{ 
    int32_t v; 
}; 

fp_num operator * (fp_num A , fp_num B){ 
    int64_t res = A.v; 
    res = res * B.v; 
    res >>= 16; 
    fp_num ans; ans.v = res; 
    return ans; 
} 

fp_num create(short calk, short ulam){ 
    fp_num ans; ans.v = calk; 
    ans.v <<= 16; ans.v += ulam; 
    return ans; 
}

void print(fp_num x, string end){ 
    double val = (x.v >> 16); 
    double pot = (double)1/2; 
    for(int i = 15; i> -1; i--){ 
        if(x.v & (1 << i)) 
            val += pot; 
        pot /=2; 
    }  
    cout << fixed << setprecision(6); 
    cout << val << end; 
} 

void test_dziaba(){ 
    fp_num moj_ziomo = create(5, 16000);  
    fp_num beka_z_ciebie = create(13, 12345);  
    print(moj_ziomo, "\n"); 
    print(beka_z_ciebie, "\n"); 
    print(moj_ziomo * beka_z_ciebie, "\n");
    moj_ziomo = moj_ziomo * moj_ziomo; 
    print(moj_ziomo, "\n"); 
}

int32_t div3(int32_t n){ 
    int64_t base = 1;  
    // to jest tak naprawde wyliczenie stalej
    base <<= 31; base -= 1; base /= 3; base += 1; 
    base *= n; 
    base = (base >> 31); 
    return base; 
}
int main(){
    //cout << ((1LL << 31) -1)/3 << "\n";   
    int k; 
    while(1){ 
        cin >> k; 
        cout << div3(k) << "\n";
    }
    //cout << div3(1); 
}
