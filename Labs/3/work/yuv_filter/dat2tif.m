output = dlmread('output.dat');
img_rec = reshape(output, 3, 512, 512);
img_rec_perm = permute(img_rec, [3 2 1]);
imwrite(uint8(img_rec_perm), 'lena_rec.tif');