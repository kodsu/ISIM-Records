

void factor(){ 
    int n; 
    int val; 
    int it; 
    cin >> n;
    val = n; 
    int = 2; 
    while(it*it <= n){ 
        while(val % it == 0){ /* (val/it)*it == val */
            cout << it << "\n"; 
            val = val / it; 
        } 
        it++; 
    }  
    if(val > 1)  
        cout << val; 
    else 
        /*pusta instrukcja*/ ;
    return; 
}