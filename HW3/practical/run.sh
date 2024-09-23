#!/bin/bash
function endl () {
    for ((i=1; i<=$1; i++)); do
        echo
    done
}

function star_print () {
    for ((i=1; i<=$1; i++)); do
        for j in {1..35}; do
            echo -n "*"
        done
        echo
    done
    endl 1
}

clear
    endl 3
    echo -e "Enter The First Char of the File You Want to Compile:  \n"
    echo -e "1) C -> Cpp"
    echo -e "2) P -> Python"
    endl 5
    read -p "Enter Code : " name
    clear
    star_print 1
    if [ "$name" == "c" ] || [ "$name" == "1" ]; then
        echo "C++ File Choosed Successfully !!!"
    else 
        echo "Python File Choosed Successfully !!!"
    fi
    endl 1
    star_print 1
    endl 13


    echo -e "*** input ***\n"
    if [ "$name" == "c" ] || [ "$name" == "1" ]; then
        cat c++/test.txt
        endl 4
        echo -e "*** output ***\n"
        g++ c++/main.cpp -o c++/main.exe && ./c++/main.exe < c++/test.txt
        rm c++/main.exe
    else 
        cat python/test.txt
        endl 4
        echo -e "*** output ***\n"
        python3 python/code.py < python/test.txt
    fi 
    endl 4
