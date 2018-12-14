# ROOT/C++ Plotting template for DUNE plots
![C++](https://img.shields.io/badge/C++/ROOT-current-brightgreen.svg) ![Dependencies](https://img.shields.io/badge/dependencies-up%20to%20date-brightgreen.svg)      ![issues](https://img.shields.io/badge/issues-none_known-brightgreen.svg) ![Contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg) ![Licence](https://img.shields.io/badge/licence-to_thrill-brightgreen.svg) 

# Basic Overview:
  - Multi part library for formatting DUNE style plots 
  - Object oriented design, defining variables, plots, features into seperate objects for ease of use
  - Customizable but not fully automated, requiring various inputs such as TTree information and output directories

### Initialisation

This templated can be downloaded from  [here](https://github.com/AranBorkum/DUNE-Plot). Addionally, if you have a GitHub account you can get one [here](https://github.com/) and then clone the template directory using the command
```
$ cd /where/you/want/the/files/to/be/
$ git clone https://github.com/AranBorkum/DUNE-Plot.git
```
DUNE-plot is designed to use cmake so you will need this to be able to compile the module. This can be found [here](https://cmake.org/download/) if you don't have cmake installed already.
In order to initialise the module you will need a  `build/` directory. An output directory is also required such that plots can  be storred somewhere. Execute the following:

```sh
$ mkdir build
$ mkdir output
$ cd build/
$ cmake ../duneplot
$ make
```
This will execute all of the fancy cmake procedure and give you all of the executables required for use. Note: you must be in the `build/` directory to run the executables.

Once all of this is done the first thing to do is go into the file `Figure.hh` in the plotting directory and change the variable `OutputFilePath` to your desired directory. I recomend the output folder you just made.

### Issues and Development

Want to contribute? Awesome!

If you find any issues with DUNE-plot, or you have a stylistic feature you think the template would benifit from, feel free to contact me at A.Borkum@sussex.ac.uk and we can discuss additions and fixes further.


