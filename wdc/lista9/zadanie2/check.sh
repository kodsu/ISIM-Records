for ((i = 0; i < 10000000; ++i)); do 
    ./gen > in
    ./wzo < in > git 
    ./moje < in > wyjxd
    diff -w wyjxd git || break; 
    echo "test $i OK" 
done
