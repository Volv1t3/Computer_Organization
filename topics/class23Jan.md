#Class #3 ― Signed and Unsigned Integer Representation ― Thursday Jan 23rd

> This document will contain information read on the Linda Null book about computer organization, as well as the 
> information presented during class in a presentation about computer airthmetic. This means that we will go down to 
<b>barebones knowledge of positional systems and their distinctions before heading into arithmetic</b>.

## Positional Systems
<p>Positional systems are those that are <code>strongly influenced by the position of a number in a sequence 
to determine its weight,</code><b><code>and therefore its importance,</code></b><code>to a number</code>. The idea 
in most systems based on this position concept is that a single number, by its own, knowing where it sits in a 
sequence of numbers can define its value to the overall amount.</p>
<p>This is how romans used to count <code>IV was four while VI was five, the I changed its value based on its position
</code>, and its how we understand most of our numeric systems today.</p>
<p>Base-10 (or more properly radix-10 decimal system), defines a set of characters accepted as numbers, namely 
<code>0 through 9</code>. These, in various combinations can mean different things based on the position that they 
take</p>

<note><p>Consider the number 238, although it contains the same as 283, by <b><code>positionality</code></b>, it 
does not mean the same. Interestingly, we can often break down these numbers as multiplications<br/>
<math>238 = 2x10^2 + 3x10^1 + 8x10^0</math>, compared to
<br/>
<math>283 = 2x10^2 + 8x10^1 + 3x10^0</math>
<br/><br/>
This then means that for us to understand the value of a number, we need <b><code>both the radix, and the 
position starting from the left on 0 towards the right to n-1 of its digits</code></b>
</p></note>
<p></p>

### Positional Systems ― Conversions
<p>The idea of converting numbers from one base to another is best realized through two methods, one is to convert 
from decimal to any base, and another is to convert from any base to decimal. The reason we use this stepping stone 
<code>decimal representation</code> is that it is most easy for us to go from one base to another (specially those 
that are not standard( through iterative and chained conversions with middle steps on decimals.</p>
<p>The idea here is that we have to paths of information, there is the going from decimal to a base, which can be 
defined as follows.</p>
<note><p>Conversion from <b><code>decimal to another base</code></b>, is best carried out as consecutive 
<b>whole divisions</b> of said number by the <b>base value</b>, the remainder being the converted 
representation when read <code>from bottom to top</code></p></note>
<p>On the other hand, the process to go back from one base to a decimal representation consists of the following.</p>
<note><p>Converions from <b><code>base-something to decimal</code></b>, involve multiplying each number in 
the <b>base representation</b>, by the <code>base raised to the power of the position of said number</code>, 
we begin from right to left with an initial exponent of 0.</p></note>

### Positional Systems ― Decimal Conversions
<p>Decimals are represented differently than most numbers in binary. Since these have to be represented through 
<b><code>negative sequences of exponents</code></b>. We mostly delve in consecutive <code>base-something 
multiplications of the decimal number, and grabbing the whole part as the representation of the decimal part 
in said base</code></p>
<p>For example, in the case of the number 0.567, our binary representation would say</p>
<procedure type="steps">
<step>Keep the 0 before the decimal point as the base of our base two number, i.e., 0. something else</step>
<step>Consecutively multiply the decimal part by the base until the desired accuracy (word size (number of bits)) 
has been achieved.
<list>
<li><math>0.567 * 2 = 1.134</math>, then we have 0.1(base 2) </li>
<li><math>.134 * 2 = 0.268</math>, then we have 0.10</li>
<li><math>.268 * 2 = 0.536 </math>, then we have 0.100</li>
<li><math>.536 * 2 = 1.072</math>, then we have 0.1001</li>
<li><math>.072 * 2 = 0.144</math>, then we have 0.10010...</li>
<li>and so on, usually we stop at some amount of bits to stop repeating fractions</li>
</list>
</step>
</procedure>
<warning><p>Although these techniques here developed can be used to convert from any base to one another, 
we should always go from <b><code>a non-standard base to decimal, before going to another 
non-standard base</code></b>. If we are working with standard bases it is no problem for us to simply 
change between them.</p></warning>
<p>Additionally, it is important for us to note the way we can convert between a base of 2 towards its cousins base 
16 and base 8. To do this we simply <b><code>group from right to left in either groups of four (base-16) 
or groups of three (base-8), using the respective characters of each to represent these groupings.</code></b></p>

## Signed Integer Representation
<p>Most programs, store values with a sign (for example C++ allowed you to store both unsigned and signed integers, 
shorts, or longs). The idea behind this separation is that <code>computers store numbers with a sign to 
identify whether it is negative or positive all the time, unless told to not do so with an unsigned 
declaration</code></p>
<p>Numbers are often stored as signed because that is how computers are architected to do. Signed integers can take 
one of three formats <b><code>signed magnitude, one's complement, and two's complmeent</code></b>. These three are 
ways to store a number with some information encoded in memory to show that it is either a positive or negative 
number</p>

<note>
<p>Before we delve into these representation analysis section, it would be wise for us recall what most significant 
and least significant bits were, as well as what a word is</p>

- In four-bit numbers, the most significant is the leftmost bit, and the rightmost is the least significant bit. 
- In eight bits, the same model happens.
- Generally, we require prior indication about, or should ask for, or review examples about the total number of bits to 
  use to 
  represent.
</note>
<p>Additionally, this section will introduce some keywords important for our development</p>
<deflist type="full">
<def title="Word">
In computer architecture, a word is the natural unit of data used by a particular processor design. It is a fixed-sized datum handled as a unit by the instruction set or the hardware of the processor. The number of bits or digits in a word (known as the word size, word width, or word length) is a crucial characteristic of any specific processor design
</def>
<def title="Carry in"></def>
<def title="Carry out"></def>
<def title="Truncation"></def>
<def title="Overflow"></def>
</deflist>

### Signed Integer Representation ― Signed Magnitude
<p>Signed integers, represent the whole <b><code>set of signed integers that a computer can represent</code></b>. 
These can be represented through a set of bits that encode the value and one bit that encodes the sign. The idea 
behind <b>signed magnitude representation</b>, is exactly that.</p>
<tldr>Signed magnitude representation <b>grabs a predefined word</b>, and uses the <b><code>leftmost 
, most significant bit, and encodes the sign of the number within it</code></b>, leaving the rest of the word (i.
e., word—1 bits) to encode the numerical value associated with the binary code</tldr>
<p>In this sense, signed magnitude effectively reduces our storage capacity by one <b>(word—1 bits for storage)</b>, 
and it additionally creates problems of its own.
</p>
<warning>

- In general, the one pitfall that we can find is that *there are two representations for 0 (+0 and -0)*. This 
  creates an issue in which two four-bit representations overlap to define zero on their own.
- Moreover, since we are taking a bit for the sign, **we effectively sacrifice part of our capacity**.
</warning>

#### Signed Magnitude ― Operations
<p>Like any other representation, signed magnitude allows us to do arithmetic operations on it. For example, if we 
were to carry out an addition in this system, depending on the number we are using we might want to isolate the sign,
bit
</p>

##### Addition
<note>
<p>Take a look at this example</p>
<math>0</math> <math>1 0 0 1 1 1 1 </math><br/>
<math>0</math>+<math>1 1 0 0 0 1 1 </math>
<p>If we were to execute the sum we would see that we have the base rules studied in other courses, however there is 
an extra one, that is going onto the sign bit <b><code>if there is such a case in our operations in this 
representation, we discard this bit</code></b>
</p>
<math>0</math> <math>0 1 1 0 0 1 0</math>
<p>As such, while our result is factually incorrect, this is the way we <code>truncate information on this 
representation</code></p>
</note>

##### Subtraction
<p>As with the basic representation of subtraction, we also have to represent each number based their symbol. The 
idea here is that at some point we will have to borrow numbers, <code>if we borrow these numbers we tally the 
positions we have carried them over above the numbers we move them over, effectively storing these values for actual 
calculations.
</code></p>
<p>Consider to numbers <math>01001111</math> (79), and <math>01100011</math> (99). If we were to be told to 
substract both, <b>without knowing their magnitudes, we follow these steps</b></p>
<procedure type="steps"> 
<step>Transform each number into decimal, figuring out the higher value.</step>
<step>Check the order of operands given (through this we can see if the result will be negative or positive)</step>
<step>Do the operation and only add the sign to the last line of the operation, i.e., only to the output.</step>
</procedure>
<p>In this system, there are various questions that we must ask before performing either addition or subtraction 
<b><code>which of the numbers is the largest?, what is the possible sign of the outcome?, in what order 
did they tell me to operate?</code></b></p>

### Signed Integer Representation ― One's Complement
<p>One's complement is a binary number representation that attempts to reduce the complexity in storage that is the 
signed magnitude representation by allowing us to find the complement to one (diminished radix approach) of a number 
by effectively flipping all of its bits <code>from zero to one, and from one to zero)</code>
</p>
<p>Effectively, the process of getting a one's complement from a number is straightforward; it is just switching the bits 
and there we have it, that is the <b><code>negative representation of any number</code>, whereas 
<code>positive numbers remain with their original representation</code></b></p>
<note><p>Keep in mind here that there isn't a concept of positive binary numbers requiring one's complement 
as the sign is not explicitly stored as a bit, rather it is inferred by the presence of a leftmost one or 
zero.</p></note>
<p>This method is useful as it is most used to transform subtraction into an addition of the one's complement of 
the subtraend. This then provides to key benefits <i><b><code>it provides a clear way to represent 
negative numbers but also to simplify subtraction through an addition of the complement</code></b></i> </p>
<p>Lets take an example of this, lets say we are asked to subtract 9 from 23, this then means we must do 23 - 9. 
However, we can consider this as 23 + (-9), which although in decimal maths means the same, in binary maths it means 
the complement.
</p>
<note>

```Text
Base 10 (23) = 0001 0111
Base 10 (9)  = 0000 1001

# One's complement of 9
Base 10-Com (9) = 1111 0110 (-9 now)

# Perform 10 + - 9
    0001 0111 
+   1111 0110
= 1 0000 1101

# The extra one must be added back into the mix
  0000 1101
+         1
= 0000 1110 (14)

# Therefore the output value is 14
```
</note>
<p>Had the example been the other way around, there would not be this <b><code>end carry-around process</code></b> 
that is adding the extra one after the word size into the mix. However, it is important to note that this is not 
only used to make subtraction simpler, it can also be used to represent binary numbers in their negative form from 
their positive form
</p>
<note><p>As per the previous example <math>00001110</math> is <math>14</math> in binary. Then its one's 
complement representation will give <math> 11110001</math>, whose numerical value might not be the exact same as 14 
in binary, however if we were to go back to normal representation we can figure things out from there
</p></note>
<warning><p>No one <b>guarantees that the value obtained from doing one or two's complement will be 
numerically equivalent to the exact value it is trying to represent</b>. Rather we are meant to perform 
the complement backwards to figure out the original value it came from.</p></warning>
<p>Lastly some of the pitfalls of this method are the same as those for <code>signed magnitude 
repreesentation</code>, <b>we still have two ways to represent 0</b> either +0 (<math>0000</math>), or -0 
(<math>1111</math>)</p>

### Signed Integer Representation ― Two's Complement
<p>Twos complement is an example of another method called <code>radix complement</code>. THis is the system that can 
be thought as <b><code>reflecive</code></b>, in the sense that our basic understanding of one's complement is kept, 
with a minor change that is <code>adding one to the one's complement of  a positive number.</code>
</p>
<p>In general, the idea is that in this representation, we need only convert all negative numbers, or those decimal 
negative numbers that we are asked to transform into binary, as this representation is more straightforward, and 
quick to understand. Moreover, we have to note that <b><code>there is no end carry-around method here, 
those bits are simply discarded if they go out of the word space</code></b></p>
<note>
<p>Consider the following example, lets attempt to substract 9 from 23 using two's complement notation</p>

```Text
# Original Representations
Binary (23) = 0001 0111 "Since it is positive we need not convert it
                         to two's complement representation"
Binary (-9) "Since it is a negative, we 
              need to go through these steps"
1. Grab original binary: 0000 1001
2. Perform one's complement: 1111 0110 (-9 in one's complement)
3. Add one to the result: 1111 0111 (-9 in two's complement)

#Performing the subtraction
  0001 0111
+ 1111 0111
= 0000 1110 "The last one that overflows is ignored"

# 0000 1110 == 14 in decimal                          

```
</note>
<p>The addition, subtraction and representation in two's complement is quite easy to understand. The way in which it 
works is simply transforming via a two step method numbers that are negative, and effectively leaving normally those 
numbers that are supposed to be positive (this information is inferred from the leftmost bit, it is not strictly 
written in). 
</p>
<p>Additionally, we must consider two important rules of this section</p>
<deflist>
<def title="Discard Carry: Overflow">
<p>In our previous examples, and writing for two's complement, we operated under the assumption that anything that 
overflowed did not affect the number. <b>Well that is not true at all</b>, the overflowing ones that can 
appear after the leftmost bit are important, as they can allow us to determine if we are in normal conditions 
or <b><code>overflow as occurred</code></b>.</p>
<p>Overflow, happens <i><b><code>if two positive numbers are added and the result
is negative, or if two negative numbers are added and the result is positive</code></b></i></p>
</def>
<def title="A simple rule for detecting overflow">
Overflow can be spotted if the carry in and carry out on the last bit are not equal. For example in some numbers we 
might have a <code>1-carry-in (the one that is meant to go after the word size is full</code>, while the last is of 
different value, (i.e., 0 in this case). If these two values do not match then there is overflow.
</def>
</deflist>
<p>The last thing to consider in this section is that <b><code>two's complement representation will 
always have one negative number more, by virtue of having one less representation for zero</code></b></p>

### Signed Integer Representation ― Numerical Ranges

- In general, the number of bytes and the representation we use determines how many numbers we can store, be it 
  through a signed integer representation, two's complement representation or unsigned integer representation. 
- Generally, as we get more bits, we can get more numbers for storage, and as long as we use unsigned storage we will get even more numbers.
- If a number has a similar representation for their positive or negative representations, then we can effectively go down to our base rule **if it has a 1 in front it is negative**

###  Numerical Ranges ― Formula for number representation

![imageForStorageCapacities.png](imageForStorageCapacities.png)


