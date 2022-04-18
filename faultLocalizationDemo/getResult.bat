cd analysePro
gcc -o tfidf tfidf.c
tfidf.exe 0 componentinfo.txt error.txt covMatrix.txt
del -f tfidf.exe 

gcc -o idf idf.c
idf.exe componentinfo.txt error.txt covMatrix.txt IDF.txt IFnum.txt
del -f idf.exe

del -f IDF.txt
del -f IFnum.txt
cd ..

copy analysePro\componentinfo.txt result\componentinfo.txt
move analysePro\covMatrix1.txt result\covMatrix.txt
copy analysePro\error.txt result\error.txt

gcc -o sliceSfl analysePro\sliceSfl.c
sliceSfl.exe 0 result\componentinfo.txt result\error.txt result\covMatrix.txt sliceResult\sliceResult.txt
sliceSfl.exe 1 result\componentinfo.txt result\error.txt result\covMatrix.txt sliceResult\sliceResult.txt
sliceSfl.exe 2 result\componentinfo.txt result\error.txt result\covMatrix.txt sliceResult\sliceResult.txt
sliceSfl.exe 3 result\componentinfo.txt result\error.txt result\covMatrix.txt sliceResult\sliceResult.txt
sliceSfl.exe 4 result\componentinfo.txt result\error.txt result\covMatrix.txt sliceResult\sliceResult.txt
sliceSfl.exe 5 result\componentinfo.txt result\error.txt result\covMatrix.txt sliceResult\sliceResult.txt
sliceSfl.exe 6 result\componentinfo.txt result\error.txt result\covMatrix.txt sliceResult\sliceResult.txt
del sliceSfl.exe

copy 0_Russel_Rao.txt result\v1\
move 0_Russel_Rao.txt result\v1slice
copy 1_GP02.txt result\v1\
move 1_GP02.txt result\v1slice
copy 2_GP03.txt result\v1\
move 2_GP03.txt result\v1slice
copy 3_Dstar.txt result\v1\
move 3_Dstar.txt result\v1slice
copy 4_OPTIMAL_P.txt result\v1\
move 4_OPTIMAL_P.txt result\v1slice
copy 5_GP19.txt result\v1\
move 5_GP19.txt result\v1slice
copy 6_Ochiai.txt result\v1\
move 6_Ochiai.txt result\v1slice

cd result
del -f componentinfo.txt
del -f covMatrix.txt
del -f error.txt

gcc -o translate translate.c
translate.exe 0_Russel_Rao v1\0_Russel_Rao.txt v1slice\0_Russel_Rao.txt
translate.exe 1_GP02 v1\1_GP02.txt v1slice\1_GP02.txt
translate.exe 2_GP03 v1\2_GP03.txt v1slice\2_GP03.txt
translate.exe 3_Dstar v1\3_Dstar.txt v1slice\3_Dstar.txt
translate.exe 4_OPTIMAL_P v1\4_OPTIMAL_P.txt v1slice\4_OPTIMAL_P.txt
translate.exe 5_GP19 v1\5_GP19.txt v1slice\5_GP19.txt
translate.exe 6_Ochiai v1\6_Ochiai.txt v1slice\6_Ochiai.txt
del translate.exe 
cd..

move result\result.txt result.txt
pause