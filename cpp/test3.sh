list_bin="hw3_list_int hw3_list_big7 hw3_list_big15"
set_bin="hw3_set_int" #"hw3_set_big7 hw3_set_big15"
setopt_bin="hw3_setopt_int" #"hw3_setopt_big7 hw3_setopt_big15"
vector_bin="hw3_vector_int hw3_vector_big7 hw3_vector_big15"
all_bin="$vector_bin $list_bin $setopt_bin $set_bin"

small_sizes="100 200 500 1000 2000 5000 10000 20000 50000 100000"
med_sizes="200000 500000 1000000"
big_sizes="2000000 5000000"

seeds="1979 1991 2017"

for BIN in $all_bin
do
    for SIZE in $small_sizes
    do
        for SEED in $seeds
        do
            ./$BIN $SIZE $SEED
        done
    done
done

for SIZE in $med_sizes
do
    for BIN in hw3_vector_int hw3_list_int hw3_set_int hw3_setopt_int
    do
        for SEED in $seeds
        do
            ./$BIN $SIZE $SEED
        done
    done
done

