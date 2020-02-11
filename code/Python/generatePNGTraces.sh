./clean.sh
python3 testLayers.py
convert generated_pgm/input.pgm -filter point -scale 10000% input.png
convert generated_pgm/inputCropped.pgm -filter point -scale 10000% inputCropped.png
convert generated_pgm/inputNormalized.pgm -filter point -scale 10000% inputNormalized.png
convert generated_pgm/convol1_62.pgm -filter point -scale 10000% convol1_62.png
convert generated_pgm/maxpool1_62.pgm -filter point -scale 10000% maxpool1_62.png
convert generated_pgm/convol1_2.pgm -filter point -scale 10000% convol1_2.png
convert generated_pgm/maxpool1_2.pgm -filter point -scale 10000% maxpool1_2.png
convert generated_pgm/convol1_8.pgm -filter point -scale 10000% convol1_8.png
convert generated_pgm/maxpool1_8.pgm -filter point -scale 10000% maxpool1_8.png
convert generated_pgm/convol1_13.pgm -filter point -scale 10000% convol1_13.png
convert generated_pgm/maxpool1_13.pgm -filter point -scale 10000% maxpool1_13.png
convert generated_pgm/convol2_29.pgm -filter point -scale 10000% convol2_29.png
convert generated_pgm/maxpool2_29.pgm -filter point -scale 10000% maxpool2_29.png
convert generated_pgm/convol3_5.pgm -filter point -scale 10000% convol3_5.png
convert generated_pgm/maxpool3_5.pgm -filter point -scale 10000% maxpool3_5.png
