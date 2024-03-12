### The BitHalo 201-204 by IAmGPIO of www.thesolomining.co

In the grand tapestry of the cosmos, where stars weave the stories of fate and fortune, the Almighty leaned over to the legendary IAmGpio, whispering through the winds of time, __'Let there be light.'__ With a smirk as wide as the horizon and the casual air of a cosmic pub regular, IAmGpio, the electric alchemist, declared with a mischievous twinkle, 'Hold my beer...' And thus, amidst a backdrop of chuckling constellations, the darkness scurried away, leaving behind a spectacle to be remembered.

During this celestial extravaganza, as the light began to weave and dance through the fabric of space, the Almighty paused, squinted through the cosmic kaleidoscope, and in a moment of divine epiphany, exclaimed in a cockney accent that resonated across the heavens, _'Oi, hold up, this looks a bit like a halo, don’t it?'_ The cosmos held its breath, the stars blinked in amusement, and in that whimsical pause, BitHalo was born. With a hearty chuckle and a nod of approval, the Lord mused, 'Well, ain’t that brilliant? BitHalo it is, then!' And the universe, in all its wonder and wit, echoed with laughter, forever cherishing the birth of BitHalo, a light that forever wears its halo with a determined grin, proving its sidekick, The Bitaxe's best efforts, to find that elusive block.

-Ok, this didn't happen _**exactly**_ like this. 

<img src="/BitHalo/Images/BitHalo+204.png" alt="Front isometric with logo" width="50%"/>

***   
### Anyway...!   

The BitHalo is a daughter board for the Bitaxe (https://bitaxe.org/) and is designed to fix to the rear of the Bitaxe with almost zero technical skill required.
Every time the Bitaxe submits a share to the pool, a pulse of light is emitted from the BitHalo. 

The BitHalo has an in-built ATMEGA328P chip (Arduino) with code uploded to simply read the debug serial data coming from a test pint (TP18) on the rear of the Bitaxe. When the serial string "accepted" is detected, the function "pulseLeds" is run.

The same applies to "BLOCK FOUND" (that would be nice, would't it!)
***


### The LEDS & Switch on the BitHalo:
On the BitHalo are 30 x RGB side emitting leds (WS protocol). Each LED is individually addressable.
Future revisions of the arduino sketch (BitHalo's firmware) could allow so much more animation options based on the serial stream.

On the BitHalo is a slide switch. This switch simply disables the LED lights on the BitHalo. Turning the LEDs off does not affect the function of the Bitaxe itself. It is just there to turn the ligths off if they annoy you at night or whatever.

<p align="center">
<img src="BitHalo/Images/Rear Render.png" alt="Rear Render" style="margin-right: 30px;"  width="30%"/>
<img src="BitHalo/Images/Front Render.png" alt="Rear Render" width="30%"/> 
</p>

***



### The External DC Jack (Do not use if using Bitaxe version 204)
The external DC jack that solders to the rear of the BitHalo was incorporated to allow the Bitaxe to be powered from the rear as opposed to being powered by the DC jack on the side. 

It involved soldering 2 wires on the rear of the BitHalo v201 to the rear of the DC jack on the Bitaxe (must be capabale of carrying at least 4a of current). Whilst this worked well on Bitaxe v201, I had to omit it for the v204 rollout due to the change in architecture and the way the DC jack was soldered on to the board. V201 had a through hole DC jack and 204 had a surface mount (SMD) variant which meant I couldnt solder on to the pins on the rear.

__Note:__ V205 of the Bitaxe has specific pads for accessories such as the BitHalo. On this, there will be new version of the BitHalo (in due course) which should work with all future versions of the Bitaxe, including the 400 series - "The Supra".

<p align="center">
  <img src="BitHalo/Images/Wires 2.png" alt="Wires + v201" width="25%"/> 
  <img src="BitHalo/Images/Wires.png" alt="Wires + v201" style="margin-right: 30px;" width="50%"/> 
</p>


***
### The 3d Printed Diffuser
To diffuse the pixellation from the individual LED's, I have designed a 5mm thick 3d printed opaque/opal diffuser.
This simply prints in 100% infill.

  <img src="BitHalo/Images/Rear Iso 2.png" alt="3d Printed Diffuser" width="70%"/> 


# This is a Heading h1
## This is a Heading h2
###### This is a Heading h6

## Emphasis

*This text will be italic*  
_This will also be italic_

**This text will be bold**  
__This will also be bold__

_You **can** combine them_

## Lists

# Unordered

* Item 1
* Item 2
* Item 2a
* Item 2b

### Ordered

1. Item 1
2. Item 2
3. Item 3
    1. Item 3a
    2. Item 3b

## Images

![This is an alt text.](/image/sample.webp "This is a sample image.")

## Links

You may be using [Markdown Live Preview](https://markdownlivepreview.com/).

## Blockquotes

> Markdown is a lightweight markup language with plain-text-formatting syntax, created in 2004 by John Gruber with Aaron Swartz.
>
>> Markdown is often used to format readme files, for writing messages in online discussion forums, and to create rich text using a plain text editor.

## Tables

|    Left columns     | Right columns |
|   ------------------- |:-------------:|
| left foo      | right foo     |
| left bar   d   | right bar     |
| left baz      | right baz     |

## Blocks of code

```
let message = 'Hello world';
alert(message);
```

## Inline code

This web site is using `markedjs/marked`.
