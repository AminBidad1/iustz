# for file in libs/*.cpp 
#     do filename=$(basename -- "$file"); filename="${filename%.*}"; make $filename.o; 
# done
make main -e objects="Value.o Item.o ConsumableItem.o Character.o views.o GameManager.o"