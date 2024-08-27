# Quadratic Solver 1.0

Solves square equations.

## Contents

+ [Description](#description)
+ [Getting started](#getting-started)
  + [Installing](#installing)
+ [Modes of work](#modes-of-work)
+ [Test system](#test-system)
+ [Author](#author)
+ [Version history](#version-history)
+ [Example of work](#example-of-work)

## Description

In my program you can enter full equation for solve it. You can enter float numbers, numbers with exponential part. Also you can use multiplication, division, add and substraction. For writing x^2 you can use "xx".

## Getting started

### Installing

* Run makefile by writing "make" in folder with program.
* For introduction for my programyou can write:

~~~
.\boot.exe --help
~~~

## Modes of work

* Simple mode - mode with minimum output and opportunity to input a lot of equations.
* Detail mode - mode, that instructing you, but you can enter only one equation.
* Test mode - mode allowing to test how program solving equations. For developers.

For first use I recommend to try detail mode

For boot simple mode you can write:

~~~
.\boot.exe simple
~~~

For boot detail mode you can write:

~~~
.\boot.exe detail
~~~

For boot test mode you can write:

~~~
.\boot.exe test
~~~

## Test system

You can use file for testing solve system. For that you should boot makefile as:

~~~
make file=1
~~~

You can add tests at file at this form:

~~~
<Number of test> <a> <b> <c> <x1> <x2> <Number of roots>
~~~

* a - a-coefficient
* b - b-coefficient
* c - c-coefficient
* x1 - less root
* x2 - greater root

For writing, that equation has infinite number of roots you should use "3".
## Author

Alexey Kornilov

Contact info:

* Telegram [@alexa_573](https://t.me/alexa_573)

## Version History

* 1.0
  * Added test system
  * Added input of equation
  * Added solve system

## Example of work

![example of work](https://github.com/cat4rsys/quadraticsolver/blob/main/images/example.png)
