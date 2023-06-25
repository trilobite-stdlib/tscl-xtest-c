# Trilobite XUnit test framework

## overview

* * *

Please add relevant information about your package.

## tooling

* * *

The targeted audience we are building for is *Windows 10*, *MacOSX*, *ChromeOS*
and *Linux* users. This project uses [Meson](https://mesonbuild.com/) `1.0.0`
and newer, uses `c2x` standards for the initial implementation of the package. The
objective by far is usability, security, transparency, and lightweight, packages
for all your application development needs.

## Setup, Compile and Install

* * *

Using this package should be fairly simple just add the git wrap file
in your subprojects directory and include the dependency in your project.

```console
[wrap-git]
directory = trilo-xtest-c
url = https://github.com/trilobite-stdlib/trilo-xtest-c.git
revision = main

[provide]
trilo-xtest-c = trilo_xtest_c_dep
```


The next step should be to add the package to your Meson project:

```meson
trilo_dep = dependency('trilo-xtest-c')

executable('prog', 'main.c',
    dependencies : [trilo_dep])

```

And finally, we set up, and compile the project just like normal.

## usage

* * *

Here is a simple sample application that should get you up and
running with using this library as soon as possible but to learn
more please view the API documentation thanks.

**Usage in C**:

```c
/*
   under:   trilobite stdlib
   author:  Michael Gene Ridge Brockus
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.code.blog>
*/
#include <stdio.h>
#include <trilobite/xtest.h>


//
// main is where all good examples start
//
int main(void)
{
    printf("%s\n", greet());
    return 0;
} // end of func

```

## contact

If you want to contact me and have a few questions
regarding the solutions in the programming you can
find a method on my [website](https://trilobite.code.blog/contact/).
