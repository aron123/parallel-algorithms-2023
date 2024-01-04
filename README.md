# Optimizing median filter (parallel algorithms assignment)

This repository contains an implementation of median filter. The project aims to explore optimization possibilities for the algorithm.
This task was issued at the University of Miskolc, Hungary in 2023.

## Precautions

The project uses a custom naive BMP parser, which is not suitable for processing any BMP file.

BMPs with the following parameters can be used:
- Windows format
- 32-bit color depth
- uncompressed
- reversed line order
- [Photoshop-like channel order](https://en.wikipedia.org/wiki/BMP_file_format#/media/File:SLNotation44440.svg)

## Usage
Project is configured to build with MSVC, but the code itself is intended to be portable.

Executable binary (win-x64) and sample images can be downloaded from [Releases page](https://github.com/aron123/parallel-algorithms-2023/releases/tag/v1.0).

### Noise generation

To generate noise to an image, run:

```
parallel.exe generate-noise <percentage> <input-files> <output-folder>
```

**NOTE**, that the output directory must exist before running the command, otherwise the output will not be saved.
If the output file is already exists, the program will overwrite it.

E.g. to generate 15% noise to the input image, run:

```
parallel.exe generate-noise 0.15 ./img/0.bmp ./output
```

### Median filtering

To apply median filter to an image, run:

```
parallel.exe median-filter <kernel-size> <sorting-function> <thread-count> <input-files> <output-folder>
```

| Parameter | Description |
| --------- | ----------- |
| kernel-size | Size of the kernel to be used. It is a single number (e.g. input `3` produces a 3x3 kernel).<br>It is recommended to use an odd number. |
| sorting-function | Sorting method to be used. Possible values are: `bucket`, `bucket-parallel`, `quick`, `quick-parallel` |
| thread-count | Number of threads to be used. Possible values are:<br>`1`: serial execution,<br>`0`: dynamic parallel execution (OpenMP determines thread count),<br>greater than zero: fixed thread count |
| input-files | Images to process. It can be multiple files, delimited by `\|`, e.g. `pic0.bmp\|pic1.bmp\|pic2.bmp`. |
| output-folder | Path to a directory, where output files should be stored. The output files are named the same as the input. |

**NOTE**, that the output directory must exist before running the command, otherwise the output will not be saved.
If the output file is already exists, the program will overwrite it.

E.g. to filter multiple images using a 3x3 kernel, quicksort algorithm, and 8 threads, run:

```
parallel.exe median-filter 3 quick 8 pic0.bmp|pic1.bmp|pic2.bmp ./out
```

Examples can be found [here](https://github.com/aron123/parallel-algorithms-2023/blob/master/script/examples.ps1).

## Sample images used

Sample images are published under certain Creative Commons licenses. Check URLs for more information.

- Mathias Appel - [Siberian Tiger](https://commons.wikimedia.org/wiki/File:Siberian_Tiger_-_53220812820.jpg)
- Stewart Nimmo - [Fox Glacier, West Coast, New Zealand](https://commons.wikimedia.org/wiki/File:TWC_Fox_%E2%80%A2_Nimmo_%E2%80%A2_MRD_27.jpg)
- Andrew Shiva - [Hungarian Parliament Building](https://commons.wikimedia.org/wiki/File:HUN-2015-Budapest-Hungarian_Parliament_(Budapest)_2015-02.jpg)
- Andrey Gulivanov - [Red Fox](https://commons.wikimedia.org/wiki/File:Red_fox_(52543116115).jpg)
