g++ ".\artclass.cpp" ".\grader.cpp" --std=c++11 -static-libstdc++ -o ".\artclass"
for i in {1..4}
do
    for j in {1..9}
    do
        echo "Run $i $j"
        cp "..\images\style-$i\style-$i-$j.txt" ".\artclass.txt"
        ".\artclass"
    done
done