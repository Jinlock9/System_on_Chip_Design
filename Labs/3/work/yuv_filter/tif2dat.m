lena_std = imread('lena_std.tif');
std_perm = permute(lena_std, [2 3 1]);
dlmwrite('input.dat', std_perm, 'delimiter', '\n')