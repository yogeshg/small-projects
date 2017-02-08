for BIN in hw3_vector_int hw3_list_int
do
    for SIZE in 100 200 500 1000 2000 5000 10000 20000 50000 100000 200000 500000 1000000 2000000 5000000
    do
        for SEED in 1979 1991 2017
        do
            ./$BIN $SIZE $SEED
        done
    done
done

for BIN in hw3_vector_big7 hw3_list_big7
do
    for SIZE in 100 200 500 1000 2000 5000 10000 20000 50000 100000 200000 500000
    do
        for SEED in 1979 1991 2017
        do
            ./$BIN $SIZE $SEED
        done
    done
done
for BIN in hw3_vector_big15 hw3_list_big15
do
    for SIZE in 100 200 500 1000 2000 5000 10000 20000 50000 100000
    do
        for SEED in 1979 1991 2017
        do
            ./$BIN $SIZE $SEED
        done
    done
done

