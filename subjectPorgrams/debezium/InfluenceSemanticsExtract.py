import numpy as np

f1 = open('covMatrix.txt','r')
f2 = open('componentinfo.txt','r')
f3 = open('sliceResult.txt','r')
f4 = open('covMatrix_new.txt','w')

first_ele = True
for data in f1.readlines():
    data = data.strip('\n')
    nums = data.split()
    if first_ele:
        nums = [int(x) for x in nums]
        matrix_x = np.array(nums)
        first_ele = False
    else:
        nums = [int(x) for x in nums]
        matrix_x = np.c_[matrix_x,nums]
f1.close()


for data in f2.readlines():
    data = data.strip('\n')
    nums_compnent = data.split()
f2.close()

for data in f3.readlines():
    data = data.strip('\n')
    nums_slice = data.split()
f3.close()

matrix_x = matrix_x.transpose()


slice_num = []
matrix_y_row = []
#matrix_y = []
for item_slice in nums_slice:
    for i in range(len(nums_compnent)):
        if item_slice == nums_compnent[i]:
            slice_num.append(i)
for matrix_x_item in matrix_x:
    for item in slice_num:
        matrix_y_row.append(matrix_x_item[item])
        f4.write(str(matrix_x_item[item]))
        f4.write(' ')
    f4.write('\n')
    matrix_y_row = []
   
f4.close()