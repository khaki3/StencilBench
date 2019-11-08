./make_hybrid2.sh gradient2d.c "{kernel[i]->tile[6,3,256];kernel[i]->block[1,256]}" p100 &
./make_hybrid2.sh j2d5pt.c "{kernel[i]->tile[8,2,128];kernel[i]->block[1,128]}" p100 &
./make_hybrid2.sh j2d9pt.c "{kernel[i]->tile[4,7,128];kernel[i]->block[1,128]}" p100 &
./make_hybrid2.sh j2d9pt-gol.c "{kernel[i]->tile[8,2,128];kernel[i]->block[1,128]}" p100 &
./make_hybrid2.sh j3d27pt.c "{kernel[i]->tile[4,2,8,64];kernel[i]->block[1,8,64]}" p100 &
./make_hybrid2.sh star3d1r.c "{kernel[i]->tile[4,2,8,64];kernel[i]->block[1,8,64]}" p100 &
./make_hybrid2.sh star3d2r.c "{kernel[i]->tile[2,4,8,64];kernel[i]->block[1,8,64]}" p100 &
./make_hybrid2.sh gradient2d.c "{kernel[i]->tile[8,6,256];kernel[i]->block[1,256]}" v100 &
./make_hybrid2.sh j2d5pt.c "{kernel[i]->tile[8,6,256];kernel[i]->block[1,256]}" v100 &
./make_hybrid2.sh j2d9pt.c "{kernel[i]->tile[6,3,128];kernel[i]->block[1,128]}" v100 &
./make_hybrid2.sh j2d9pt-gol.c "{kernel[i]->tile[8,6,256];kernel[i]->block[1,256]}" v100 &
./make_hybrid2.sh j3d27pt.c "{kernel[i]->tile[4,1,16,32];kernel[i]->block[1,16,32]}" v100 &
./make_hybrid2.sh star3d1r.c "{kernel[i]->tile[4,2,8,128];kernel[i]->block[1,8,128]}" v100 &
./make_hybrid2.sh star3d2r.c "{kernel[i]->tile[2,2,8,64];kernel[i]->block[1,8,64]}" v100 &
