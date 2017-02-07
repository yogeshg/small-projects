set -x
mkdir -p ./out/
for BIN in hw3_vector_int hw3_list_int hw3_set_int hw3_set_int_opt
do
    echo '' > ./out/$BIN.txt
    ./$BIN 10 1991 2>> ./out/$BIN.txt 1>/dev/null
    ./$BIN 10000 1991 1>> ./out/$BIN.txt 2>/dev/null
done
