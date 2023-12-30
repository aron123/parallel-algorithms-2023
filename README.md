# Optimizing median filter (parallel algorithms assignment)

This repository contains an implementation of median filter. The project aims to explore optimization possibilities for the algorithm.
This task was issued at the University of Miskolc, Hungary in 2023.

## Precautions

- custom, naive BMP parser
- 32 bit depth, uncompressed, Windows-BMP, reversed line order, alpha channel is not used, bitmask -> Photoshop

## Noise generation

- existence of input file is not checked
- output directory should exists
- file would be rewritten

```
parallel.exe generate-noise <percentage> <input-file> <output-file>
```

## Median filtering

- existence of input file is not checked
- output directory should exists
- file would be rewritten

- kernel size should be an even number (e.g. `3` -> 3x3 kernel is used)
- sorting: `bucket`, `bucket-parallel`, `quick`, `quick-parallel`
- thread: `-1`: serial, `0`: auto parallel, greater than zero: fixed thread count

```
parallel.exe median-filter <kernel-size> <sorting-function> <thread-count> <input-file> <output-file>
```

## Used images

- Mathias Appel - [Siberian Tiger](https://commons.wikimedia.org/wiki/File:Siberian_Tiger_-_53220812820.jpg)
- Stewart Nimmo - [Fox Glacier, West Coast, New Zealand](https://commons.wikimedia.org/wiki/File:TWC_Fox_%E2%80%A2_Nimmo_%E2%80%A2_MRD_27.jpg)
- Andrew Shiva - [Hungarian Parliament Building](https://commons.wikimedia.org/wiki/File:HUN-2015-Budapest-Hungarian_Parliament_(Budapest)_2015-02.jpg)
- Andrey Gulivanov - [Red Fox](https://commons.wikimedia.org/wiki/File:Red_fox_(52543116115).jpg)