# Image compression and decompression for PPM format
 Title is pretty self-explanatory. Made for a Uni assignment

# How it works?
 compresses and decompresses the image by storing the pixel's colors in a quad tree

 At this moment, the program can:
 - Check the image
 - Compress the image
 - Decompress the image

## Check
 Takes the image and outputs some info about said image:
  - How many levels the quad tree has
  - The number of zone that can be compressed
  - The size of the biggest zone

 Command
 
 `./quadtree -c1 [compression_level] [ppm_image_name] [output_file]`

## Compress
 Compresses the image and saves the pixel colors of each node of quad tree in binary format

 Command

 `./quadtree -c2 [compression_level] [ppm_image_name] [output_file]`

## Decompress
 Decompresses the image by using the information stored in the compress output file

 Command

 `./quadtree -d [compress_file] [new_ppm_image_name]`

# Restrictions
-Only works for PPM P6 images
-The image dimensions can only be NxN, where N is a power of 2

# Exemple

Image at 0 compression level

![initial image](https://i.imgur.com/pUtS0sf.png)

Image at 500 compression level

![image after compression](https://i.imgur.com/YAm1cw9.png)
