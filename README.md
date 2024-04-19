# Termsort

This is a project to show a visual demonstration of how sorting algorithms work, based on the famous video by Timo Bingmann, https://youtu.be/kPRA0W1kECg.

![demo](./demo.gif)

## Contents

* [Installation](#Install)
* [Algorithms included](#Algorithms)

# Installation
```bash
git clone https://github.com/thegogy/termsort
cd termsort
rm demo.mp4

make clean install
```

By default, this will install the project to your `$HOME/.local/bin` directory. This can be changed by instead running the following command:

```bash
make install INSTALL_DIR=/path/to/custom/install/dir
```

#Algorithms

* bogosort
* bubble sort
* quicksort
* shellsort
* mergesort
* heapsort
* gnomesort
* cocktailsort
* insertionsort
* selectionsort
* oddevensort
* pancakesort
* pigeonholesort
* combsort
* stoogesort
* badsort
* dropsort

