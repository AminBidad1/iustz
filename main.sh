for file in libs/*.cpp 
    do filename=$(basename -- "$file"); filename="${filename%.*}"; make $filename.o; 
done