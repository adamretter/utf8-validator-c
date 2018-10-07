# UTF8 Validator (C edition)

This is a more basic but faster version of [UTF8 Validator](https://github.com/digital-preservation/utf8-validator). The C edition, uses the [fastvalidate-utf-8](https://github.com/lemire/fastvalidate-utf-8) library from [Daniel Lemire](https://github.com/lemire). The C edition only returns a pass or fail result. It does not provide information about the position at which validation fails or allow to continue validating further after the first error.

A UTF-8 Validation Tool which may be used as a command line tool, if you are looking for a C library to use with your own program see [fastvalidate-utf-8](https://github.com/lemire/fastvalidate-utf-8).

Released under the [Apache 2.0 Licence](https://opensource.org/licenses/Apache-2.0).

[![Build Status](https://travis-ci.org/adametter/utf8-validator-c.png?branch=master)](https://travis-ci.org/adamretter/utf8-validator-c)


## Use from the Command Line
You can [build from the source code](#building-from-source-code). You can then run `utf8validate` (Linux/Mac/Unix).

For example:
```
$ ./utf8validate
```

## Command Line Exit Codes
* **0** Success
* **1** Invalid Arguments provided to the application
* **2** File was not UTF-8 Valid
* **4** IO Error, e.g. could not read file


## Building from Source Code

### Prerequisite

* c99 compaitble compiler, e.g. modern GCC or Clang
* Make

### Steps
* Git clone the repository from https://github.com/adamretter/utf8-validator-c.git
* Build using Make, by running `make` in the cloned directory, you will then find a binary of the compiled application named `utf8validate`.
